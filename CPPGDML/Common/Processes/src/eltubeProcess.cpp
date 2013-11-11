//
#include "Processes/SolidTypeProcess.h"

#include "Schema/eltube.h"

class eltubeProcess : public SolidTypeProcess
{
public:
  eltubeProcess( const ProcessingContext* context = 0 )
    : SolidTypeProcess( context ) {
  }

  virtual ~eltubeProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs ) {
    
    SAXObject** obj = Context()->GetTopObject();

    eltube* eltube_element = new eltube;
    
    eltube_element->set_dx( attrs.getValue( "dx" ) );
    eltube_element->set_dy( attrs.getValue( "dy" ) );
    eltube_element->set_dz( attrs.getValue( "dz" ) );

    m_obj = eltube_element;
    *obj  = eltube_element;
    
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
    static std::string tag = "eltube";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(eltubeProcess)
