//
// $Id: tube_dimensionsProcess.cpp,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#include "Processes/DimensionsTypeProcess.h"

#include "Schema/tube_dimensions.h"

class tube_dimensionsProcess : public DimensionsTypeProcess
{
public:
  tube_dimensionsProcess( const ProcessingContext* context = 0 )
  : DimensionsTypeProcess( context ) {
  }

  virtual ~tube_dimensionsProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

    SAXObject** obj = Context()->GetTopObject();

    tube_dimensions* tube_dimensions_lement = new tube_dimensions;

    m_obj = tube_dimensions_lement;
    *obj  = tube_dimensions_lement;

    std::string dp  = attrs.getValue( "DeltaPhi" );
    std::string inr = attrs.getValue("InR");
    std::string outr = attrs.getValue("OutR");
    std::string sphi = attrs.getValue("StartPhi");
    std::string hz = attrs.getValue("hz");

    tube_dimensions_lement->setdp(dp);
    tube_dimensions_lement->setinr(inr);
    tube_dimensions_lement->setoutr(outr);
    tube_dimensions_lement->setsphi(sphi);
    tube_dimensions_lement->sethz(hz);
    std::cout << "seting hz in tube dim ele " << hz << std::endl;
    
    
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::tube_dimensions NOTIFIED AFTER THE TAG: " << name << std::endl;
    DimensionsTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "tube_dimensions";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(tube_dimensionsProcess)
