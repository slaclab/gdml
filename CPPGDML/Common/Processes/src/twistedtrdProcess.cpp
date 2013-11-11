#include "Processes/SolidTypeProcess.h"

#include "Schema/twistedtrd.h"

class twistedtrdProcess : public SolidTypeProcess
{
public:
  twistedtrdProcess( const ProcessingContext* context = 0 )
  : SolidTypeProcess( context ) {
  }

  virtual ~twistedtrdProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs ) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    
    SAXObject** obj = Context()->GetTopObject();

    twistedtrd* twistedtrd_element = new twistedtrd;
    
    twistedtrd_element->set_pDx1( attrs.getValue( "x1" ) );
    twistedtrd_element->set_pDx2( attrs.getValue( "x2" ) );
    twistedtrd_element->set_pDy1( attrs.getValue( "y1" ) );
    twistedtrd_element->set_pDy2( attrs.getValue( "y2" ) );
    twistedtrd_element->set_pDz( attrs.getValue( "z" ) );
    twistedtrd_element->set_pPhiTwist( attrs.getValue( "PhiTwist" ) );

    m_obj = twistedtrd_element;
    *obj  = twistedtrd_element;
    
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
    static std::string tag = "twistedtrd";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(twistedtrdProcess)
