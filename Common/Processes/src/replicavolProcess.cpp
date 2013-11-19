//
// $Id: replicavolProcess.cpp,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#include "Processes/ReplicaPlacementTypeProcess.h"

#include "Schema/replicavol.h"

class replicavolProcess : public ReplicaPlacementTypeProcess
{
public:
  replicavolProcess( const ProcessingContext* context = 0 )
  : ReplicaPlacementTypeProcess( context ) {
  }

  virtual ~replicavolProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

    SAXObject** obj = Context()->GetTopObject();

    replicavol* replicavol_lement = new replicavol;

    m_obj = replicavol_lement;
    *obj  = replicavol_lement;

    std::string numb  = attrs.getValue( "number" );
    std::string numb_start  = attrs.getValue( "copy_num_start" );
    std::string numb_step   = attrs.getValue( "copy_num_step" );    
    
    replicavol_lement->set_numb(numb);
    replicavol_lement->set_numb_start(numb_start);
    replicavol_lement->set_numb_step(numb_step);

  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::replicavol NOTIFIED AFTER THE TAG: " << name << std::endl;
    ReplicaPlacementTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "replicavol";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(replicavolProcess)
