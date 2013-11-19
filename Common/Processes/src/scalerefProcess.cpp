#include "Processes/ReferenceTypeProcess.h"

#include "Schema/BooleanSolidType.h"
#include "Schema/SinglePlacementType.h"

#include <cstdlib>
#include <iostream>

class scalerefProcess : public ReferenceTypeProcess
{
  public:
    scalerefProcess( const ProcessingContext* context = 0 )
      : ReferenceTypeProcess( context ) {
    }
  
    virtual ~scalerefProcess() {
    }
  
    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs )
    {    
      SAXObject** obj = Context()->GetTopObject();
    
      std::string parent = Context()->GetParentState();

      if( parent == "physvol" )
      {
        SinglePlacementType::scaleref* co = new SinglePlacementType::scaleref;
        *obj = co;
        m_obj = co;    
      }
      else if( parent == "union" || parent == "subtraction" || parent == "intersection" )
      {
        BooleanSolidType::scaleref* co = new BooleanSolidType::scaleref;
        *obj = co;
        m_obj = co;
    
      }
    
      ReferenceTypeProcess::StartElement( name, attrs );
    }
  
    // Analogical to SAX endElement callback
    virtual void EndElement( const std::string& name ) {
      ReferenceTypeProcess::EndElement( name );
    }

    // The name of the state this object will process
    virtual const std::string& State() const {
      static std::string tag = "scaleref";
      return tag;
    }
};

DECLARE_PROCESS_FACTORY(scalerefProcess)
