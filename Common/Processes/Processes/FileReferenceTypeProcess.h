#ifndef GDML_PROCESS_FILEREFERENCETYPEPROCESS_H
#define GDML_PROCESS_FILEREFERENCETYPEPROCESS_H 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXObjectHandle.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/FileReferenceType.h"

#include <cstdlib>
#include <iostream>

class FileReferenceTypeProcess : public SAXStateProcess
{
public:
  FileReferenceTypeProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context ), m_obj( 0 ) {
  }
  
  virtual ~FileReferenceTypeProcess() {
  }
  
  virtual const SAXComponentObject* Build() const {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs ) {    
    
    
    std::string name  = attrs.getValue( "name" );
    //std::cout << "FILEReferenceTypeProcess PROCESS::START OF TAG  : " << name << std::endl;
    std::string volname  = attrs.getValue( "volname" );
    FileReferenceType* frefobj = dynamic_cast<FileReferenceType*>(m_obj);
    frefobj->set_name( name );
    frefobj->set_volname( volname );
  }
  
  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& name )
  {
    //std::cout << "FILEReferenceTypeProcess PROCESS::END OF TAG  : " << name << std::endl;
    try {
      FileReferenceType* saxobj = dynamic_cast<FileReferenceType*>( m_obj );
      
      if( saxobj != 0 ) {
        //std::cout << "PROCESS END OF TAG:: "
        //          << name << " name: " << saxobj->get_name() << " volname: " << saxobj->get_volname()
        //          << " looks OK" << std::endl;
      } else  {
        std::cerr << "PROCESS END OF TAG:: GOT ZERO DATA POINTER! " << std::endl;
      }
    } catch( ... ) {
      std::cerr << "PROCESS END OF TAG " << name << " ERROR: "
                << " Cannot cast properly the data object!" << std::endl;
    }
  }
  
  // Analogical to SAX characters callback, it's called for ignorableWhitespace too!
  virtual void Characters( const std::string& )
  {
  }
  
  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& )
  {
  }
  
protected:
  SAXObject* m_obj;
};

#endif // GDML_PROCESS_FILEREFERENCETYPEPROCESS_H
