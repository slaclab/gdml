//
#ifndef SURFACEPROPERTYTYPEPROCESS_H
#define SURFACEPROPERTYTYPEPROCESS_H 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXObjectHandle.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/SurfacePropertyType.h"

#include <cstdlib>
#include <iostream>

class SurfacePropertyTypeProcess : public SAXStateProcess
{
public:
  SurfacePropertyTypeProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context ), m_obj( 0 ) {
  }
  
  virtual ~SurfacePropertyTypeProcess() {
  }
  
  virtual const SAXComponentObject* Build() const {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs )
  {    
    std::string stype  = attrs.getValue( "type" );
    std::string sname   = attrs.getValue( "name" );
    
    SurfacePropertyType* sobj  = dynamic_cast<SurfacePropertyType*>( m_obj );
    
    sobj->set_type( stype );
    sobj->set_name( sname );
  }
  
  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& )
  {
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

#endif // SURFACEPROPERTYTYPEPROCESS_H
