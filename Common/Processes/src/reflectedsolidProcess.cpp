#include "Processes/SolidTypeProcess.h"

#include "Schema/reflectedSolid.h"

class reflectedSolidProcess : public SolidTypeProcess
{
public:
  reflectedSolidProcess( const ProcessingContext* context = 0 )
  : SolidTypeProcess( context ) {
  }

  virtual ~reflectedSolidProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs ) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    
    SAXObject** obj = Context()->GetTopObject();

    reflectedSolid* reflectedSolid_element = new reflectedSolid;

    reflectedSolid_element->set_solid( attrs.getValue( "solid" ) );
    
    reflectedSolid_element->set_sx( attrs.getValue( "sx" ) );
    reflectedSolid_element->set_sy( attrs.getValue( "sy" ) );
    reflectedSolid_element->set_sz( attrs.getValue( "sz" ) );

    reflectedSolid_element->set_rx( attrs.getValue( "rx" ) );
    reflectedSolid_element->set_ry( attrs.getValue( "ry" ) );
    reflectedSolid_element->set_rz( attrs.getValue( "rz" ) );

    reflectedSolid_element->set_dx( attrs.getValue( "dx" ) );
    reflectedSolid_element->set_dy( attrs.getValue( "dy" ) );
    reflectedSolid_element->set_dz( attrs.getValue( "dz" ) );

    m_obj = reflectedSolid_element;
    *obj  = reflectedSolid_element;
    
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
    static std::string tag = "reflectedSolid";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(reflectedSolidProcess)
