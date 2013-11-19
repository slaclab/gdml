#include "Processes/FacetTypeProcess.h"

#include "Schema/quadrangular.h"

class quadrangularProcess : public FacetTypeProcess
{
public:
  quadrangularProcess( const ProcessingContext* context = 0 )
  : FacetTypeProcess( context ) {
  }

  virtual ~quadrangularProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs ) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    
    SAXObject** obj = Context()->GetTopObject();

    quadrangular* quadrangular_element = new quadrangular;
    
    quadrangular_element->set_vertex1( attrs.getValue( "vertex1" ) );
    quadrangular_element->set_vertex2( attrs.getValue( "vertex2" ) );
    quadrangular_element->set_vertex3( attrs.getValue( "vertex3" ) );
    quadrangular_element->set_vertex4( attrs.getValue( "vertex4" ) );
    quadrangular_element->set_type( attrs.getValue( "type" ) );

    m_obj = quadrangular_element;
    *obj  = quadrangular_element;
    
    FacetTypeProcess::StartElement( name, attrs );
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& name ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
    FacetTypeProcess::EndElement( name );
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::" << name << " NOTIFIED AFTER THE TAG: " << name << std::endl;
    FacetTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "quadrangular";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(quadrangularProcess)
