//
// $Id: physvolProcess.cpp,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#include "Processes/SinglePlacementTypeProcess.h"

#include "Schema/physvol.h"

class physvolProcess : public SinglePlacementTypeProcess
{
public:
  physvolProcess( const ProcessingContext* context = 0 )
  : SinglePlacementTypeProcess( context ) {
  }

  virtual ~physvolProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

    SAXObject** obj = Context()->GetTopObject();

    physvol* physvol_lement = new physvol;
    physvol_lement->set_name( attrs.getValue( "name" ) );

    m_obj = physvol_lement;
    *obj  = physvol_lement;
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::physvol NOTIFIED AFTER THE TAG: " << name << std::endl;
    SinglePlacementTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "physvol";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(physvolProcess)
