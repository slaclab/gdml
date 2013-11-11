//
// $Id: assemblyProcess.cpp,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/assembly.h"

class assemblyProcess : public SAXStateProcess
{
public:
  assemblyProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context ), m_obj( 0 ) {
  }
  
  virtual ~assemblyProcess() {
  }
  
  virtual const SAXComponentObject* Build() const {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs ) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    SAXObject** obj = Context()->GetTopObject();
    
    assembly* ao = new assembly;
    
    ao->set_name( attrs.getValue( "name" ) );
    
    m_obj = ao;
    *obj  = ao;
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << " " << std::endl;
  }

  // Analogical to SAX characters callback, it's called for ignorableWhitespace too!
  virtual void Characters( const std::string& ) {
  }
  
  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::assembly NOTIFIED AFTER THE TAG: " << name << std::endl;
    SAXObject** so = Context()->GetTopObject();
    assembly* aobj = dynamic_cast<assembly*>( m_obj );
    aobj->add_content( name, *so );
  }
  
  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "assembly";
    return tag;
  }

private:
  SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(assemblyProcess)
