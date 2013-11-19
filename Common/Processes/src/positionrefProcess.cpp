// 
// $Id: positionrefProcess.cpp,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#include "Processes/ReferenceTypeProcess.h"

#include "Schema/BooleanSolidType.h"
#include "Schema/SinglePlacementType.h"

#include <cstdlib>
#include <iostream>

class positionrefProcess : public ReferenceTypeProcess
{
  public:
    positionrefProcess( const ProcessingContext* context = 0 )
      : ReferenceTypeProcess( context ) {
    }
  
    virtual ~positionrefProcess() {
    }
  
    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs )
    {    
      SAXObject** obj = Context()->GetTopObject();

      std::string parent = Context()->GetParentState();

      if( parent == "physvol" )
      {
        SinglePlacementType::positionref* co = new SinglePlacementType::positionref;
        *obj = co;
        m_obj = co;    
      }
      else if( parent == "union" || parent == "subtraction" || parent == "intersection" )
      {
        BooleanSolidType::positionref* co = new BooleanSolidType::positionref;
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
      static std::string tag = "positionref";
      return tag;
    }
};

DECLARE_PROCESS_FACTORY(positionrefProcess)

  
