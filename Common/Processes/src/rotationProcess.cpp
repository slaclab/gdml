//
// $Id: rotationProcess.cpp,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXObjectHandle.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/define.h"

#include <cstdlib>
#include <iostream>

class rotationProcess : public SAXStateProcess
{
  public:
    rotationProcess( const ProcessingContext* context = 0 )
      : SAXStateProcess( context ) {
    }

    virtual ~rotationProcess() {
    }

    virtual const SAXComponentObject* Build() const {
      return this;
    }

    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs ) {
      //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

      std::string rname  = attrs.getValue( "name" );
      std::string rtype  = attrs.getValue( "type" );
      std::string runit  = attrs.getValue( "unit" );
      std::string rx = attrs.getValue( "x" );
      std::string ry = attrs.getValue( "y" );
      std::string rz = attrs.getValue( "z" );

      SAXObject** obj = Context()->GetTopObject();
      *obj = new define::rotation;
      define::rotation* rotation_element = dynamic_cast<define::rotation*>(*obj);
      rotation_element->set_name( rname );
      rotation_element->set_type( rtype );
      rotation_element->set_unit( runit );
      rotation_element->set_x( rx );
      rotation_element->set_y( ry );
      rotation_element->set_z( rz );
    }

    // Analogical to SAX endElement callback
    virtual void EndElement( const std::string& name ) {
      //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
      try
      {
        SAXObject** obj = Context()->GetTopObject();
        define::rotation* saxobj = dynamic_cast<define::rotation*>( *obj );

        if( saxobj != 0 )
        {
          //std::cout << "PROCESS END OF TAG:: rotation " << saxobj->get_name() << " looks OK" << std::endl;
          ;
        }
        else
        {
          std::cerr << "PROCESS END OF TAG:: GOT ZERO DATA POINTER! " << std::endl;
        }
      } catch( ... ) {
        std::cerr << "PROCESS END OF TAG " << name << " ERROR: "
                  << " Cannot cast properly the data object!" << std::endl;
      }
    }
  
    // Analogical to SAX characters callback, it's called for ignorableWhitespace too!
    virtual void Characters( const std::string& )
    {
    }
  
    // Invoked whenever one of the daughter state processes has been popped-out of the state stack
    // The name passed-in as the argument is the name of the XML element for which that's been done
    virtual void StackPopNotify( const std::string& )
    {
    }
  
    // The name of the state this object will process
    virtual const std::string& State() const
    {
      static std::string m_tag = "rotation";
      return m_tag;
    }
};

DECLARE_PROCESS_FACTORY(rotationProcess)

  
