//
#include "Processes/SolidTypeProcess.h"

#include "Schema/orb.h"

class orbProcess : public SolidTypeProcess
{
public:
  orbProcess( const ProcessingContext* context = 0 )
    : SolidTypeProcess( context ) {
  }

  virtual ~orbProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs )
  {
    SAXObject** obj = Context()->GetTopObject();

    orb* orb_element = new orb;
    
    orb_element->set_r( attrs.getValue( "r" ) );

    m_obj = orb_element;
    *obj  = orb_element;
    
    SolidTypeProcess::StartElement( name, attrs );
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& name )
  {
    SolidTypeProcess::EndElement( name );
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) 
  {
    SolidTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "orb";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(orbProcess)
