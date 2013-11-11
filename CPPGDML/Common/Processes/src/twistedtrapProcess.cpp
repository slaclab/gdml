#include "Processes/SolidTypeProcess.h"

#include "Schema/twistedtrap.h"

class twistedtrapProcess : public SolidTypeProcess
{
public:
  twistedtrapProcess( const ProcessingContext* context = 0 )
  : SolidTypeProcess( context ) {
  }

  virtual ~twistedtrapProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs ) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    
    SAXObject** obj = Context()->GetTopObject();

    twistedtrap* twistedtrap_element = new twistedtrap;
    
    twistedtrap_element->set_pPhiTwist( attrs.getValue( "PhiTwist" ) );
    twistedtrap_element->set_pDz( attrs.getValue( "z" ) );
    twistedtrap_element->set_pTheta( attrs.getValue( "Theta" ) );
    twistedtrap_element->set_pPhi( attrs.getValue( "Phi" ) );
    twistedtrap_element->set_pDy1( attrs.getValue( "y1" ) );
    twistedtrap_element->set_pDx1( attrs.getValue( "x1" ) );
    twistedtrap_element->set_pDx2( attrs.getValue( "x2" ) );
    twistedtrap_element->set_pDy2( attrs.getValue( "y2" ) );
    twistedtrap_element->set_pDx3( attrs.getValue( "x3" ) );
    twistedtrap_element->set_pDx4( attrs.getValue( "x4" ) );
    twistedtrap_element->set_pAlph( attrs.getValue( "Alph" ) );

    m_obj = twistedtrap_element;
    *obj  = twistedtrap_element;
    
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
    static std::string tag = "twistedtrap";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(twistedtrapProcess)
