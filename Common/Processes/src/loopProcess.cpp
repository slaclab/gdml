//
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/loop.h"
#include "Schema/box.h"
#include "Schema/SolidType.h"

#include <cstdlib>
#include <iostream>

class loopProcess : public SAXStateProcess
{
public:
  loopProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context )
  {
  }

  virtual ~loopProcess()
  {
  }

  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs )
  {
    //ProcessingConfigurator* conf = fContext->GetConfig();
    //std::string file_name = conf->URI();
    //std::string::size_type loc = file_name.find_last_of('.');
    //file_name = file_name.substr(0,loc);
    std::string var    = attrs.getValue( "for"   );
    std::string to     = attrs.getValue( "to"    );
    std::string step   = attrs.getValue( "step"  );
      
    SAXObject** obj = Context()->GetTopObject();
    m_loop = new loop;
    *obj = m_loop;
    loop* loop_element = dynamic_cast<loop*>(*obj);
      
    loop_element->set_var ( var  );
    loop_element->set_to  ( to   );
    loop_element->set_step( step );
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& )
  {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
    try
    {
      SAXObject** obj = Context()->GetTopObject();
      loop* saxobj = dynamic_cast<loop*>( *obj );

      if( saxobj != 0 )
      {
      }
      else
      {
        std::cerr << "PROCESS END OF TAG:: loop:: GOT ZERO DATA POINTER! " << std::endl;
      }
    }
    catch( ... )
    {
      std::cerr << "PROCESS END OF TAG:: loop:: BAD CAST exception caught...\a" << std::endl;
    }
  }

  // Analogical to SAX characters callback, it's called for ignorableWhitespace too!
  virtual void Characters( const std::string& )
  {
    // Irrelevant in this process
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name )
  {
    loop* loop_element = dynamic_cast<loop*>( m_loop );
    SAXObject** so = Context()->GetTopObject();
    loop_element->add_to_content( name, *so );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string m_tag = "loop";
    return m_tag;
  }

private:
  loop*     m_loop;
};

DECLARE_PROCESS_FACTORY(loopProcess)

