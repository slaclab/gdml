#include "Processes/QuantityTypeProcess.h"

#include "Schema/width.h"

class widthProcess : public QuantityTypeProcess
{
public:
  widthProcess( const ProcessingContext* context = 0 )
  : QuantityTypeProcess( context ) {
  }

  virtual ~widthProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

    SAXObject** obj = Context()->GetTopObject();

    width* width_lement = new width;

    m_obj = width_lement;
    *obj  = width_lement;

    std::string value  = attrs.getValue( "value" );
    std::string unit = attrs.getValue("unit");

    width_lement->set_value(value);
    width_lement->set_unit(unit);    
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::width NOTIFIED AFTER THE TAG: " << name << std::endl;
    QuantityTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "width";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(widthProcess)
