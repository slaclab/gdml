//
// $Id: divisionvolProcess.cpp,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#include "Processes/DivisionPlacementTypeProcess.h"

#include "Schema/divisionvol.h"

class divisionvolProcess : public DivisionPlacementTypeProcess
{
public:
  divisionvolProcess( const ProcessingContext* context = 0 )
  : DivisionPlacementTypeProcess( context ) {
  }

  virtual ~divisionvolProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

    SAXObject** obj = Context()->GetTopObject();

    divisionvol* divisionvol_lement = new divisionvol;

    divisionvol_lement->set_axis(attrs.getValue("axis"));
    divisionvol_lement->set_number(attrs.getValue("number"));
    divisionvol_lement->set_width(attrs.getValue("width"));
    divisionvol_lement->set_offset(attrs.getValue("offset"));
    divisionvol_lement->set_unit(attrs.getValue("unit"));


    m_obj = divisionvol_lement;
    *obj  = divisionvol_lement;
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::divisionvol NOTIFIED AFTER THE TAG: " << name << std::endl;
    DivisionPlacementTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "divisionvol";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(divisionvolProcess)
