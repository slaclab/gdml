//
#ifndef FACETTYPEPROCESS_H
#define FACETTYPEPROCESS_H 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXObjectHandle.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/FacetType.h"

#include <cstdlib>
#include <iostream>

class FacetTypeProcess : public SAXStateProcess
{
public:
  FacetTypeProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context ), m_obj( 0 ) {
  }
  
  virtual ~FacetTypeProcess() {
  }
  
  virtual const SAXComponentObject* Build() const {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList&  )
  {        
    //    FacetType* sobj  = dynamic_cast<FacetType*>( m_obj );    
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

#endif // FACETTYPEPROCESS_H
