#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXObjectHandle.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/direction.h"

#include <cstdlib>
#include <iostream>

class directionProcess : public SAXStateProcess
{
  public:
    directionProcess( const ProcessingContext* context = 0 )
      : SAXStateProcess( context ) {
    }
  
    virtual ~directionProcess() {
    }
  
    virtual const SAXComponentObject* Build() const {
      return this;
    }

    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs )
    {    
      std::string pname = attrs.getValue( "name" );
      std::string ptype = attrs.getValue( "type" );
      std::string px    = attrs.getValue( "x" );
      std::string py    = attrs.getValue( "y" );
      std::string pz    = attrs.getValue( "z" );
      std::string punit = attrs.getValue( "unit" );

      SAXObject** obj = Context()->GetTopObject();
      *obj = new direction;
      direction* direction_element = dynamic_cast<direction*>(*obj);
      direction_element->set_name( pname );
      direction_element->set_type( ptype );
      direction_element->set_unit( punit );
      direction_element->set_x( px );
      direction_element->set_y( py );
      direction_element->set_z( pz );
    }
  
    // Analogical to SAX endElement callback
    virtual void EndElement( const std::string& name )
    {
      try
      {
        SAXObject** obj = Context()->GetTopObject();
        direction* saxobj = dynamic_cast<direction*>( *obj );
      
        if( saxobj == 0 )
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
      static std::string m_tag = "direction";
      return m_tag;
    }
};

DECLARE_PROCESS_FACTORY(directionProcess)

  
