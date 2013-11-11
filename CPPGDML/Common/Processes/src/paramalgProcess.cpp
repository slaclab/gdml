//
// $Id: paramalgProcess.cpp,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#include "Processes/ParameterisationAlgTypeProcess.h"

#include "Schema/paramalg.h"

class paramalgProcess : public ParameterisationAlgTypeProcess
{
public:
  paramalgProcess( const ProcessingContext* context = 0 )
  : ParameterisationAlgTypeProcess( context ) {
  }

  virtual ~paramalgProcess() {
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList&) {
    //std::cout << "PROCESS::START OF TAG  : " << name << std::endl;

    SAXObject** obj = Context()->GetTopObject();

    paramalg* paramalg_lement = new paramalg;

    m_obj = paramalg_lement;
    *obj  = paramalg_lement;

    
    //    std::string numb  = attrs.getValue( "number" );
    
    //    paramalg_lement->set_number(numb);

  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
    //std::cout << "PROCESS::END OF TAG  : " << name << std::endl;
  }

  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    //std::cout << "PROCESS::paramalg NOTIFIED AFTER THE TAG: " << name << std::endl;
    ParameterisationAlgTypeProcess::StackPopNotify( name );
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "paramalg";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(paramalgProcess)
