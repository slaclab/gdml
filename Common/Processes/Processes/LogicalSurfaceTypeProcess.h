//
#ifndef LOGICALSURFACETYPEPROCESS_H
#define LOGICALSURFACETYPEPROCESS_H 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXObjectHandle.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/LogicalSurfaceType.h"

#include <cstdlib>
#include <iostream>

class LogicalSurfaceTypeProcess : public SAXStateProcess
{
public:
  LogicalSurfaceTypeProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context ), m_obj( 0 ) {
  }
  
  virtual ~LogicalSurfaceTypeProcess() {
  }
  
  virtual const SAXComponentObject* Build() const {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs )
  {    
    std::string sprop  = attrs.getValue( "surfaceproperty" );
    std::string sname   = attrs.getValue( "name" );
    LogicalSurfaceType* sobj  = dynamic_cast<LogicalSurfaceType*>( m_obj );
    
    sobj->set_surfaceproperty( sprop );
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

#endif // LOGICALSURFACETYPEPROCESS_H
