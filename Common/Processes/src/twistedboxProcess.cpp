#include "Processes/SolidTypeProcess.h"

#include "Schema/twistedbox.h"

class twistedboxProcess : public SolidTypeProcess
{
public:
  twistedboxProcess( const ProcessingContext* context = 0 )
  : SolidTypeProcess( context ) {
  }

  virtual ~twistedboxProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs ) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    
    SAXObject** obj = Context()->GetTopObject();

    twistedbox* twistedbox_element = new twistedbox;
    
    twistedbox_element->set_pDx( attrs.getValue( "x" ) );
    twistedbox_element->set_pDy( attrs.getValue( "y" ) );
    twistedbox_element->set_pDz( attrs.getValue( "z" ) );
    twistedbox_element->set_pPhiTwist( attrs.getValue( "PhiTwist" ) );

    m_obj = twistedbox_element;
    *obj  = twistedbox_element;
    
    SolidTypeProcess::StartElement( name, attrs );
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& name ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
    SolidTypeProcess::EndElement( name );
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::" << name << " NOTIFIED AFTER THE TAG: " << name << std::endl;
    SolidTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "twistedbox";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(twistedboxProcess)
