// -*- C++ -*-
// $Id: ReplicaPlacementTypeProcess.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#ifndef GDML_PROCESS_REPLICAPLACEMENTTYPEPROCESS_H
#define GDML_PROCESS_REPLICAPLACEMENTTYPEPROCESS_H 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/ReplicaPlacementType.h"

class ReplicaPlacementTypeProcess : public SAXStateProcess
{
public:
  ReplicaPlacementTypeProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context ) {
  }
  
  virtual ~ReplicaPlacementTypeProcess() {
  }
  
  virtual const SAXComponentObject* Build() const {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList&) 
  {
    // this is not needed....?
    // it's all in replicavolProcess .....

//     std::string numb  = attrs.getValue( "number" );
//     std::string numb_start  = attrs.getValue( "copy_num_start" );
//     std::string numb_step   = attrs.getValue( "copy_num_step" );
    
//     ReplicaPlacementType* sobj  = dynamic_cast<ReplicaPlacementType*>( m_obj );
    
//     sobj->set_numb(numb);
//     sobj->set_numb_start(numb_start);
//     sobj->set_numb_step(numb_step);
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
  }

  // Analogical to SAX characters callback, it's called for ignorableWhitespace too!
  virtual void Characters( const std::string& ) {
  }
  
  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    SAXObject** so = Context()->GetTopObject();
    ReplicaPlacementType* sptobj = dynamic_cast<ReplicaPlacementType*>( m_obj );

    sptobj->add_content( name, *so );

    //std::cout << "REPLICA PLACEMENT PROCESS NOTIFY GOT: " << name << std::endl;
  }

protected:
  SAXObject* m_obj;
};

#endif // GDML_PROCESS_REPLICAPLACEMENTTYPEPROCESS_H
