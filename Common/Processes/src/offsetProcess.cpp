#include "Processes/QuantityTypeProcess.h"

#include "Schema/offset.h"

class offsetProcess : public QuantityTypeProcess
{
public:
  offsetProcess( const ProcessingContext* context = 0 )
  : QuantityTypeProcess( context ) {
  }

  virtual ~offsetProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

    SAXObject** obj = Context()->GetTopObject();

    offset* offset_lement = new offset;

    m_obj = offset_lement;
    *obj  = offset_lement;

    std::string value  = attrs.getValue( "value" );
    std::string unit = attrs.getValue("unit");

    offset_lement->set_value(value);
    offset_lement->set_unit(unit);    
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::offset NOTIFIED AFTER THE TAG: " << name << std::endl;
    QuantityTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "offset";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(offsetProcess)
