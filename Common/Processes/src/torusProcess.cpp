//
#include "Processes/SolidTypeProcess.h"

#include "Schema/torus.h"

class torusProcess : public SolidTypeProcess
{
public:
  torusProcess( const ProcessingContext* context = 0 )
    : SolidTypeProcess( context ) {
  }

  virtual ~torusProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name,
                             const ASCIIAttributeList& attrs )
  {    
    SAXObject** obj = Context()->GetTopObject();

    torus* torus_element = new torus;
    
    torus_element->set_rmin( attrs.getValue( "rmin" ) );
    torus_element->set_rmax( attrs.getValue( "rmax" ) );
    torus_element->set_rtor( attrs.getValue( "rtor" ) );
    torus_element->set_startphi( attrs.getValue( "startphi" ) );
    torus_element->set_deltaphi( attrs.getValue( "deltaphi" ) );

    m_obj = torus_element;
    *obj  = torus_element;
    
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
    static std::string tag = "torus";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(torusProcess)
