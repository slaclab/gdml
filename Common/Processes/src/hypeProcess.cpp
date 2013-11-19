//
#include "Processes/SolidTypeProcess.h"

#include "Schema/hype.h"

class hypeProcess : public SolidTypeProcess
{
public:
  hypeProcess( const ProcessingContext* context = 0 )
    : SolidTypeProcess( context ) {
  }

  virtual ~hypeProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name,
                             const ASCIIAttributeList& attrs )
  {    
    SAXObject** obj = Context()->GetTopObject();

    hype* hype_element = new hype;
    
    hype_element->set_rmin( attrs.getValue( "rmin" ) );
    hype_element->set_rmax( attrs.getValue( "rmax" ) );
    hype_element->set_inst( attrs.getValue( "inst" ) );
    hype_element->set_outst( attrs.getValue( "outst" ) );
    hype_element->set_z( attrs.getValue( "z" ) );

    m_obj = hype_element;
    *obj  = hype_element;
    
    SolidTypeProcess::StartElement( name, attrs );
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& name ) {
    SolidTypeProcess::EndElement( name );
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    SolidTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "hype";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(hypeProcess)
