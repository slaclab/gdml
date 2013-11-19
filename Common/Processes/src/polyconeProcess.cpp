//
#include "Processes/SolidTypeProcess.h"

#include "Schema/polycone.h"

class polyconeProcess : public SolidTypeProcess
{
public:
  polyconeProcess( const ProcessingContext* context = 0 )
  : SolidTypeProcess( context ) {
  }

  virtual ~polyconeProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs ) 
  {  
    SAXObject** obj = Context()->GetTopObject();
    
    polycone* polycone_element = new polycone;
    
    polycone_element->set_startphi( attrs.getValue( "startphi" ) );
    polycone_element->set_deltaphi( attrs.getValue( "deltaphi" ) );
    
    m_obj = polycone_element;
    *obj  = polycone_element;
    
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
    polycone* pobj = dynamic_cast<polycone*>( m_obj );
    pobj->add_content( name, *so );
    
    SolidTypeProcess::StackPopNotify( name );
  }
  
  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "polycone";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(polyconeProcess)
