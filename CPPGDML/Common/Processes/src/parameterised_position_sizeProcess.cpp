//
// $Id: parameterised_position_sizeProcess.cpp,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#include "Processes/ParameterisationAlgTypeProcess.h"

#include "Schema/parameterised_position_size.h"

class parameterised_position_sizeProcess : public ParameterisationAlgTypeProcess
{
public:
  parameterised_position_sizeProcess( const ProcessingContext* context = 0 )
  : ParameterisationAlgTypeProcess( context ) {
  }

  virtual ~parameterised_position_sizeProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList&) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

    SAXObject** obj = Context()->GetTopObject();

    parameterised_position_size* parameterised_position_size_lement = new parameterised_position_size;

    m_obj = parameterised_position_size_lement;
    *obj  = parameterised_position_size_lement;

    
    //    std::string numb  = attrs.getValue( "number" );
    
    //    parameterised_position_size_lement->set_number(numb);

  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::parameterised_position_size NOTIFIED AFTER THE TAG: " << name << std::endl;
    ParameterisationAlgTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "parameterised_position_size";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(parameterised_position_sizeProcess)
