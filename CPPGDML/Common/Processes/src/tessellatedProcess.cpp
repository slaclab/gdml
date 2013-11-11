#include "Processes/SolidTypeProcess.h"

#include "Schema/tessellated.h"

class tessellatedProcess : public SolidTypeProcess
{
public:
  tessellatedProcess( const ProcessingContext* context = 0 )
  : SolidTypeProcess( context ) {
  }

  virtual ~tessellatedProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs ) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;
    
    SAXObject** obj = Context()->GetTopObject();

    tessellated* tessellated_element = new tessellated;    

    m_obj = tessellated_element;
    *obj  = tessellated_element;
    
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
    SAXObject** so = Context()->GetTopObject();
    tessellated* pobj = dynamic_cast<tessellated*>( m_obj );
    pobj->add_content( name, *so );

    SolidTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "tessellated";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(tessellatedProcess)
