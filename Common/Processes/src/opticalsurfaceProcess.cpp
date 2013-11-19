#include "Processes/SurfacePropertyTypeProcess.h"

#include "Schema/opticalsurface.h"

class opticalsurfaceProcess : public SurfacePropertyTypeProcess
{
public:
  opticalsurfaceProcess( const ProcessingContext* context = 0 )
  : SurfacePropertyTypeProcess( context ) {
  }

  virtual ~opticalsurfaceProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs ) {
    
    SAXObject** obj = Context()->GetTopObject();

    opticalsurface* opticalsurface_element = new opticalsurface;
    
    opticalsurface_element->set_model( attrs.getValue( "model" ) );
    opticalsurface_element->set_finish( attrs.getValue( "finish" ) );
    opticalsurface_element->set_value( attrs.getValue( "value" ) );

    m_obj = opticalsurface_element;
    *obj  = opticalsurface_element;
    
    SurfacePropertyTypeProcess::StartElement( name, attrs );
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& name ) {
    SurfacePropertyTypeProcess::EndElement( name );
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    SurfacePropertyTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "opticalsurface";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(opticalsurfaceProcess)
