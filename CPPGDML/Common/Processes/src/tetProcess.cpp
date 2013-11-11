//
#include "Processes/SolidTypeProcess.h"

#include "Schema/tet.h"

class tetProcess : public SolidTypeProcess
{
  public:
    tetProcess( const ProcessingContext* context = 0 )
      : SolidTypeProcess( context ) {
    }

    virtual ~tetProcess() {
    }

    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string& name,
                               const ASCIIAttributeList& attrs )
    {
      //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    
      SAXObject** obj = Context()->GetTopObject();

      tet* tet_element = new tet;
    
      tet_element->set_vertex1( attrs.getValue( "vertex1" ) );
      tet_element->set_vertex2( attrs.getValue( "vertex2" ) );
      tet_element->set_vertex3( attrs.getValue( "vertex3" ) );
      tet_element->set_vertex4( attrs.getValue( "vertex4" ) );

      m_obj = tet_element;
      *obj  = tet_element;
    
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
      static std::string tag = "tet";
      return tag;
    }
};

DECLARE_PROCESS_FACTORY(tetProcess)
