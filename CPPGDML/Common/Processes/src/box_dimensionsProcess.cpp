//
// $Id: box_dimensionsProcess.cpp,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#include "Processes/DimensionsTypeProcess.h"

#include "Schema/box_dimensions.h"

class box_dimensionsProcess : public DimensionsTypeProcess
{
public:
  box_dimensionsProcess( const ProcessingContext* context = 0 )
  : DimensionsTypeProcess( context ) {
  }

  virtual ~box_dimensionsProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

    SAXObject** obj = Context()->GetTopObject();

    box_dimensions* box_dimensions_lement = new box_dimensions;

    m_obj = box_dimensions_lement;
    *obj  = box_dimensions_lement;

    std::string x  = attrs.getValue( "x" );
    std::string y = attrs.getValue("y");
    std::string z = attrs.getValue("z");

    box_dimensions_lement->setx(x);
    box_dimensions_lement->sety(y);
    box_dimensions_lement->setz(z);


    
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::box_dimensions NOTIFIED AFTER THE TAG: " << name << std::endl;
    DimensionsTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "box_dimensions";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(box_dimensionsProcess)
