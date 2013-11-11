//
// $Id: replicate_along_axisProcess.cpp,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#include "Processes/ReplicationAlgTypeProcess.h"

#include "Schema/replicate_along_axis.h"

class replicate_along_axisProcess : public ReplicationAlgTypeProcess
{
public:
  replicate_along_axisProcess( const ProcessingContext* context = 0 )
  : ReplicationAlgTypeProcess( context ) {
  }

  virtual ~replicate_along_axisProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList&) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

    SAXObject** obj = Context()->GetTopObject();

    replicate_along_axis* replicate_along_axis_lement = new replicate_along_axis;

    m_obj = replicate_along_axis_lement;
    *obj  = replicate_along_axis_lement;

    
    //    std::string numb  = attrs.getValue( "number" );
    
    //    replicate_along_axis_lement->set_number(numb);

  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::replicate_along_axis NOTIFIED AFTER THE TAG: " << name << std::endl;
    ReplicationAlgTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "replicate_along_axis";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(replicate_along_axisProcess)
