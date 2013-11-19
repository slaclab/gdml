//
#include "Processes/SolidTypeProcess.h"

#include "Schema/polyhedra.h"

class polyhedraProcess : public SolidTypeProcess
{
public:
  polyhedraProcess( const ProcessingContext* context = 0 )
    : SolidTypeProcess( context ) {
  }

  virtual ~polyhedraProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs ) 
  {  
    SAXObject** obj = Context()->GetTopObject();
    
    polyhedra* polyhedra_element = new polyhedra;
    
    polyhedra_element->set_startphi( attrs.getValue( "startphi" ) );
    polyhedra_element->set_deltaphi( attrs.getValue( "deltaphi" ) );
    polyhedra_element->set_numsides( attrs.getValue( "numsides" ) );
    
    m_obj = polyhedra_element;
    *obj  = polyhedra_element;
    
    SolidTypeProcess::StartElement( name, attrs );
  }
  
  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& name ) {
    SolidTypeProcess::EndElement( name );
  }
  
  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) 
  {
    SAXObject** so = Context()->GetTopObject();
    polyhedra* pobj = dynamic_cast<polyhedra*>( m_obj );
    pobj->add_content( name, *so );
    
    SolidTypeProcess::StackPopNotify( name );
  }
  
  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "polyhedra";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(polyhedraProcess)
