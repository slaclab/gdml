//
#include "Processes/ReferenceTypeProcess.h"

#include "Schema/physvolref.h"

#include <cstdlib>
#include <iostream>

class physvolrefProcess : public ReferenceTypeProcess
{
  public:
    physvolrefProcess( const ProcessingContext* context = 0 )
      : ReferenceTypeProcess( context ) {
    }
  
    virtual ~physvolrefProcess() {
    }
  
    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs )
    {    
      SAXObject** obj = Context()->GetTopObject();
    
      physvolref* vo = new physvolref;
    
      *obj  = vo;
      m_obj = vo;
    
      ReferenceTypeProcess::StartElement( name, attrs );
    }
  
    // Analogical to SAX endElement callback
    virtual void EndElement( const std::string& name ) {
      ReferenceTypeProcess::EndElement( name );
    }
  
    // The name of the state this object will process
    virtual const std::string& State() const {
      static std::string tag = "physvolref";
      return tag;
    }
};

DECLARE_PROCESS_FACTORY(physvolrefProcess)

  
