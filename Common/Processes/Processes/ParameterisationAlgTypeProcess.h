// -*- C++ -*-
// $Id: ParameterisationAlgTypeProcess.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#ifndef GDML_PROCESS_PARAMETERISATIONALGTYPEPROCESS_H
#define GDML_PROCESS_PARAMETERISATIONALGTYPEPROCESS_H 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/ParameterisationAlgorithmType.h"

class ParameterisationAlgTypeProcess : public SAXStateProcess
{
public:
  ParameterisationAlgTypeProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context ) {
  }
  
  virtual ~ParameterisationAlgTypeProcess() {
  }
  
  virtual const SAXComponentObject* Build() const {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& ) 
  {
    //????????????????
    //    std::string numb  = attrs.getValue( "number" );
    //    ParameterisationAlgType* sobj  = dynamic_cast<ParameterisationAlgType*>( m_obj );
    //    sobj->set_number(numb);
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
    ParameterisationAlgorithmType* sptobj = dynamic_cast<ParameterisationAlgorithmType*>( m_obj );

    sptobj->add_content( name, *so );

    //std::cout << "PARAMETERISED PLACEMENT PROCESS NOTIFY GOT: " << name << std::endl;
  }

protected:
  SAXObject* m_obj;
};

#endif // GDML_PROCESS_PARAMETERISEDPLACEMENTTYPEPROCESS_H
