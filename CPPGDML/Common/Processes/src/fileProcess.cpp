//
#include "Processes/FileReferenceTypeProcess.h"

#include "Schema/SinglePlacementType.h"

#include <cstdlib>
#include <iostream>

class fileProcess : public FileReferenceTypeProcess
{
  public:
    fileProcess( const ProcessingContext* context = 0 )
      : FileReferenceTypeProcess( context ) {
    }
  
    virtual ~fileProcess() {
    }
  
    // Analogical to SAX startElement callback
    virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs )
    {    
      SAXObject** obj = Context()->GetTopObject();
    
      SinglePlacementType::file* f = new SinglePlacementType::file;
    
      *obj  = f;
      m_obj = f;
    
      FileReferenceTypeProcess::StartElement( name, attrs );
    }
  
    // Analogical to SAX endElement callback
    virtual void EndElement( const std::string& name ) {
      FileReferenceTypeProcess::EndElement( name );
    }
  
    // The name of the state this object will process
    virtual const std::string& State() const {
      static std::string tag = "file";
      return tag;
    }
};

DECLARE_PROCESS_FACTORY(fileProcess)

  
