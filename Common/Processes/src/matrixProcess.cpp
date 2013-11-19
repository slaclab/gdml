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

class matrixProcess : public SAXStateProcess
{
  public:
    matrixProcess( const ProcessingContext* context = 0 )
      : SAXStateProcess( context ) {
    }

    virtual ~matrixProcess() {
    }

    virtual const SAXComponentObject* Build() const {
      return this;
    }

    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string& elementname, const ASCIIAttributeList& attrs ) {
      //std::cout << "PROCESS::START OF TAG  : " << elementname << std::endl;

      std::string name    = attrs.getValue( "name"   );
      std::string coldim  = attrs.getValue( "coldim" );
      std::string values  = attrs.getValue( "values" );

      SAXObject** obj = Context()->GetTopObject();
      *obj = new define::matrix;
      define::matrix* matrix_element = dynamic_cast<define::matrix*>(*obj);
      
      matrix_element->set_name( name );
      matrix_element->set_coldim( coldim );
      matrix_element->set_values( values );
    }

    // Analogical to SAX endElement callback
    virtual void EndElement( const std::string& name ) {
      //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
      try
      {
        SAXObject** obj = Context()->GetTopObject();
        define::matrix* saxobj = dynamic_cast<define::matrix*>( *obj );

        if( saxobj != 0 )
        {
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
      static std::string m_tag = "matrix";
      return m_tag;
    }
};

DECLARE_PROCESS_FACTORY(matrixProcess)
