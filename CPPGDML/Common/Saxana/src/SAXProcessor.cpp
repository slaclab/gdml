// $Id: SAXProcessor.cpp,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#include <xercesc/util/PlatformUtils.hpp>
#include <xercesc/util/XMLString.hpp>

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/SAXEvents.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXEventGun.h"
#include "Saxana/SAX2EventGun.h"
#include "Saxana/StateProcessMap.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXSubscriberPool.h"
#include "Saxana/SAXObjectHandle.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/ActionProcessingState.h"
#include "Saxana/SAXProcessor.h"

#include <iostream>

SAXProcessor::SAXProcessor()
  : fMap( 0 ), fPool( 0 ), fStack( 0 ), fNotifyStack( 0 ),
    fConfig( 0 ), fCurrentEvent( 0 ), fIgnoring( false )
{
  fMap         = new StateProcessMap();
  fPool        = new SAXSubscriberPool();
  fStack       = new StateStack();
  fNotifyStack = new StateStack();
}

SAXProcessor::~SAXProcessor()
{
  if( fMap != 0 )
  {
    delete fMap;
    fMap = 0;
  }  
  if( fPool != 0 )
  {
    delete fPool;
    fPool = 0;
  }  
  if( fStack != 0 )
  {
    delete fStack;
    fStack = 0;
  }
  if( fNotifyStack != 0 )
  {
    delete fNotifyStack;
    fStack = 0;
  }
}

const SAXSubscriberPool* SAXProcessor::GetSubscriberPool()
{
 return fPool;
}

// Mandatory interface from ProcessingContext
const StateStack* SAXProcessor::GetStack() const
{
  return fStack;
}

const SAXEvent* SAXProcessor::GetLastEvent() const
{
  return fCurrentEvent;
}

const SAXEventGun* SAXProcessor::GetSAXEventGun() const
{
  return fCurrentGun;
}
 
void SAXProcessor::SetSAXEventGun( const SAXEventGun* gun )
{
  fCurrentGun = gun;
}

const ProcessingConfigurator* SAXProcessor::GetConfig() const
{
  return fConfig;
}

SAXObject** SAXProcessor::GetTopObject() const
{
  SAXProcessingState* state = dynamic_cast<SAXProcessingState*>( fStack->Top() );
  SAXObject** obj = state->GetObjectRef();
  return obj;
}

const char* SAXProcessor::GetParentState() const
{
  const char* state = 0;

  if( !fNotifyStack->Empty() )
  {
    SAXProcessingState* proc_state = dynamic_cast<SAXProcessingState*>( fNotifyStack->Top() );
    state = const_cast<const char*>( proc_state->GetProcess()->State().c_str() );
  }
  
  return state;
}

StatusCode SAXProcessor::Initialize()
{
  StatusCode sc;
  
  fMap->Initialize();
  fPool->Initialize();
  
  // Initialize the Xerces-C system
  try
  {
    XMLPlatformUtils::Initialize();
  }
  catch( const XMLException& toCatch )
  {
    char* msg = XMLString::transcode( toCatch.getMessage() );
    std::cerr << "Error during initialization! :\n" << msg << std::endl;
    sc = StatusCode::eError;
    if( msg != 0 )
    {
      delete [] msg;
    }
  }
  
  return sc;
}

StatusCode SAXProcessor::Configure( ProcessingConfigurator* config )
{
  fConfig = config;
  return StatusCode::eOk;
}

StatusCode SAXProcessor::Run()
{
  StatusCode sc;
  //   SAXEventGun saxgun( this );
  SAX2EventGun saxgun( this );
  
  saxgun.Configure( fConfig );
  sc = saxgun.Run();
  
  return sc;
}

StatusCode SAXProcessor::Finalize()
{
  StatusCode sc;
  
  // And call the termination method
  XMLPlatformUtils::Terminate();
  
  return sc;
}

void SAXProcessor::ProcessEvent( const SAXEvent* const event )
{
  fCurrentEvent = event;
  SAXProcessingState* top = 0;
  SAXProcessingState* notifytop = 0;
  SAXObject** objectRef = 0;
    
  if( !fStack->Empty() )
  {
    //top = dynamic_cast<SAXProcessingState*>( (fStack->Top())() );
    top = dynamic_cast<SAXProcessingState*>( fStack->Top() );
  }
  
  if( !fNotifyStack->Empty() )
  {
    //top = dynamic_cast<SAXProcessingState*>( (fStack->Top())() );
    notifytop = dynamic_cast<SAXProcessingState*>( fNotifyStack->Top() );
  }
  
  if( SAXEvent::eStartElement == event->Type() )
  {
    const SAXEventStartElement* ev = dynamic_cast<const SAXEventStartElement*>(event);

    std::string tagname = ev->Name();
    //    std::cout << "SXP::PE:: Got start element event for tag: " << tagname << std::endl;
        
    if( fMap->Check( ev->Name() ) )
    {
      fIgnoring = false;
      
      // We've got the state process in place, let's activate it
      objectRef = new SAXObject*;
      StateProcessMap::Process process = fMap->GetProcess( tagname );
      process->SetContext( this );
      const StateStack::State state   = new SAXProcessingState( objectRef, process() );
      
      // Setup properly the stacks
      if( fStack->Empty() && fNotifyStack->Empty() )
      {
        fStack->Push( state );
      }
      else
      {
        StateStack::State notifystate = top;
        fNotifyStack->Push( notifystate );
        fStack->Push( state );
      }

      process->StartElement( tagname, ev->Attributes() );
    }
    else
    {
      fIgnoring = true;
    }
  }
  else if( SAXEvent::eEndElement == event->Type() )
  {
    const SAXEventEndElement* ev = dynamic_cast<const SAXEventEndElement*>(event);

    std::string name = ev->Name();
    //  std::cout << "SXP::PE:: Got end element event for tag: " << name << std::endl;

    if( !fStack->Empty() ) {
      if( ev->Name() == top->GetProcess()->State() ) {
        // Activate state process
        SAXStateProcess* process = top->GetProcess();
        process->EndElement( ev->Name() );

        // Grab a new object from the stack and play with it a bit
        objectRef = top->GetObjectRef();

        //        std::cout << "*objectRef: " << *objectRef << std::endl;

        // Locate the subcriber(s) and send them the created object
        const SAXSubscriberPool::Subscribers* actors = fPool->GetSubscribers( ev->Name() );

        bool didSub = false;

        if( actors != 0 ) {
          // There are some guys waiting out there for a gift
          SAXSubscriberPool::Subscribers::const_iterator subscriberRef;

          for( subscriberRef = actors->begin(); subscriberRef != actors->end(); subscriberRef++ ) {
            // Now we call only subscribers processing only this single element
            if( (*subscriberRef)->GetSubscriptions()->size() == 1 ) {
              //              std::cout << "SXP::PE:: Executing subscriber(s) for element: " << ev->Name() << std::endl;              
              (*subscriberRef)->Activate( *objectRef );	      	      
              didSub = true;
            }
          } 
          delete actors;

        }

        if( !fNotifyStack->Empty() ) {
          // Let the parent process know about its child element
          notifytop->GetProcess()->StackPopNotify( ev->Name() );

          // Now we call only the subscribers who need to know about their children elements
          // This workaround is here due to the single-type tree grammar. This type of tree grammar
          // forbids conflicting non-terminal symbols in its productions and this is here to remove
          // the ambiguity caused by the conflicting non-terminals
          // In other words it means whenever we have to process two XML elements which have the same
          // child element in their content models we notify only the one whose child is now created
          SAXSubscriber::Subscription ParentTag = notifytop->GetProcess()->State();
          const SAXSubscriberPool::Subscribers* actors = fPool->GetSubscribers( ParentTag );
          if( actors != 0 ) {
            SAXSubscriberPool::Subscribers::const_iterator subscriberRef;

            for( subscriberRef = actors->begin(); subscriberRef != actors->end(); subscriberRef++ ) {
              if( (*subscriberRef)->IsSubscribedTo( ev->Name() ) ) {
                //                std::cout << "SXP::PE:: Executing PARENT subscriber(s) for: "
                //                         << ParentTag << " for element: " << ev->Name() << std::endl;
                (*subscriberRef)->Activate( *objectRef );
                didSub = true;
              }
            }
            
            delete actors;
          }

          // Pop this guy from notify stack
          fNotifyStack->Pop();
        }

        // delete the object because all subscribers should have been called 
        if ( didSub ) {
          //	  std::cout << "deleting object <" << ev->Name() << "> = *objectRef: " << *objectRef << std::endl;	
          //delete *objectRef;
        }

        // delete the object reference
        if( objectRef != 0 ) {
          //	  std::cout << "deleting objectRef: " << objectRef << std::endl;
          delete objectRef;
        }

        fStack->Pop();
        //        std::cout << "--------------------------------------------------------------" << std::endl;
      }
    }
  }
  else
  {
    switch( event->Type() )
    {
    case SAXEvent::eCharacters :
      {
        if( !fIgnoring ) {
          const SAXEventCharacters* ev = dynamic_cast<const SAXEventCharacters*>(event);
          //          std::cout << "SXP::PE:: Got characters event >>" << ev->Data() << "<<" << std::endl;
          if( !fStack->Empty() ) {
            top->GetProcess()->Characters( ev->Data() );
          }
        }
      }
    break;
    case SAXEvent::ePI         :
      {
      }
    break;
    case SAXEvent::eWarning    :
    case SAXEvent::eError      :
    case SAXEvent::eFatalError :
      {
        const SAXErrorEventBase* ev = dynamic_cast<const SAXErrorEventBase*>(event);
        std::cerr << ev->Message() << std::endl;
      }
    break;
    default                    :
      break;
    };
  }
}



