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

class scaleProcess : public SAXStateProcess
{
  public:
    scaleProcess( const ProcessingContext* context = 0 )
      : SAXStateProcess( context ) {
    }

    virtual ~scaleProcess() {
    }

    virtual const SAXComponentObject* Build() const {
      return this;
    }

    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs ) {
      //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

      std::string rname  = attrs.getValue("name");
      std::string sx = attrs.getValue("x");
      std::string sy = attrs.getValue("y");
      std::string sz = attrs.getValue("z");

      SAXObject** obj = Context()->GetTopObject();
      *obj = new define::scale;

      define::scale* scale_element = dynamic_cast<define::scale*>(*obj);

      scale_element->set_name(rname);
      scale_element->set_x(sx);
      scale_element->set_y(sy);
      scale_element->set_z(sz);
    }

    // Analogical to SAX endElement callback
    virtual void EndElement( const std::string& name ) {
      //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
      try
      {
        SAXObject** obj = Context()->GetTopObject();
        define::scale* saxobj = dynamic_cast<define::scale*>( *obj );

        if( saxobj != 0 )
        {
          //std::cout << "PROCESS END OF TAG:: scale " << saxobj->get_name() << " looks OK" << std::endl;
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
      static std::string m_tag = "scale";
      return m_tag;
    }
};

DECLARE_PROCESS_FACTORY(scaleProcess)
