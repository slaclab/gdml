//
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXObjectHandle.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/parameters.h"

#include <cstdlib>
#include <iostream>

class parametersProcess : public SAXStateProcess
{
  public:
    parametersProcess( const ProcessingContext* context = 0 )
      : SAXStateProcess( context ) {
    }
  
    virtual ~parametersProcess() {
    }
  
    virtual const SAXComponentObject* Build() const {
      return this;
    }

    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs )
    {    
      //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    
      std::string number = attrs.getValue( "number" );

      SAXObject** obj = Context()->GetTopObject();
      *obj = new parameters;

      parameters* parameters_element = dynamic_cast<parameters*>(*obj);
      m_obj = *obj;

      parameters_element->set_number(number);
    }
  
    // Analogical to SAX endElement callback
    virtual void EndElement( const std::string& name )
    {
      //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
      try
      {
        SAXObject** obj = Context()->GetTopObject();
        parameters* saxobj = dynamic_cast<parameters*>( *obj );
      
        if( saxobj != 0 )
        {
          //std::cout << "PROCESS END OF TAG:: position " << saxobj->get_name() << " looks OK" << std::endl;
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
  virtual void StackPopNotify( const std::string& name)
  {
    SAXObject** so = Context()->GetTopObject();
    parameters* pobj = dynamic_cast<parameters*>( m_obj );
    pobj->add_content( name, *so );
  }
  
    // The name of the state this object will process
    virtual const std::string& State() const
    {
      static std::string m_tag = "parameters";
      return m_tag;
    }

private:
  SAXObject* m_obj;

};

DECLARE_PROCESS_FACTORY(parametersProcess)

  
