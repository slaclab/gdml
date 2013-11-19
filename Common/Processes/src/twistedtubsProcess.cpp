//
#include "Processes/SolidTypeProcess.h"

#include "Schema/twistedtubs.h"

class twistedtubsProcess : public SolidTypeProcess
{
  public:
    twistedtubsProcess( const ProcessingContext* context = 0 )
      : SolidTypeProcess( context ) {
    }

    virtual ~twistedtubsProcess() {
    }

    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string& name,
                               const ASCIIAttributeList& attrs )
    {
      //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    
      SAXObject** obj = Context()->GetTopObject();

      twistedtubs* twistedtubs_element = new twistedtubs;
    
      twistedtubs_element->set_PhiTwist( attrs.getValue( "twistedangle" ) );
      twistedtubs_element->set_InnerRadius( attrs.getValue( "endinnerrad" ) );
      twistedtubs_element->set_OuterRadius( attrs.getValue( "endouterrad" ) );
      twistedtubs_element->set_ZHalfLength( attrs.getValue( "zlen" ) );
      twistedtubs_element->set_DPhi( attrs.getValue( "phi" ) );

      m_obj = twistedtubs_element;
      *obj  = twistedtubs_element;
    
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
      static std::string tag = "twistedtubs";
      return tag;
    }
};

DECLARE_PROCESS_FACTORY(twistedtubsProcess)
