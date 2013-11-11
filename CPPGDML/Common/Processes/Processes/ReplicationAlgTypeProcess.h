#ifndef GDML_PROCESS_REPLICATIONALGTYPEPROCESS_H
#define GDML_PROCESS_REPLICATIONALGTYPEPROCESS_H 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/ReplicationAlgorithmType.h"

class ReplicationAlgTypeProcess : public SAXStateProcess
{
public:
  ReplicationAlgTypeProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context ) {
  }
  
  virtual ~ReplicationAlgTypeProcess() {
  }
  
  virtual const SAXComponentObject* Build() const {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList&) 
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
    ReplicationAlgorithmType* sptobj = dynamic_cast<ReplicationAlgorithmType*>( m_obj );

    sptobj->add_content( name, *so );

  }

protected:
  SAXObject* m_obj;
};

#endif 
