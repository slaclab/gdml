// -*- C++ -*-
// $Id: DivisionPlacementTypeProcess.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_PROCESS_DIVISIONPLACEMENTTYPEPROCESS_H
#define GDML_PROCESS_DIVISIONPLACEMENTTYPEPROCESS_H 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/DivisionPlacementType.h"

class DivisionPlacementTypeProcess : public SAXStateProcess
{
public:
  DivisionPlacementTypeProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context ) {
  }
  
  virtual ~DivisionPlacementTypeProcess() {
  }
  
  virtual const SAXComponentObject* Build() const {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& ) {
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
  }

  // Analogical to SAX characters callback, it's called for ignorableWhitespace too!
  virtual void Characters( const std::string& ) {
  }
  
  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string& name ) {
    SAXObject** so = Context()->GetTopObject();
    DivisionPlacementType* sptobj = dynamic_cast<DivisionPlacementType*>( m_obj );

    if( name == "volumeref" )
    {
      // The volume reference came so simply add it into content model of the child
      sptobj->add_content( name, *so );
    }
  }

protected:
  SAXObject* m_obj;
};

#endif // GDML_PROCESS_DIVISIONPLACEMENTTYPEPROCESS_H
