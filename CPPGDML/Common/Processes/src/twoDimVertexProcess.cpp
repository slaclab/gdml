#ifndef GDML_PROCESS_TWODIMVERTEX_H
#define GDML_PROCESS_TWODIMVERTEX_H 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/twoDimVertexType.h"

class twoDimVertexProcess : public SAXStateProcess {
public:
	twoDimVertexProcess(const ProcessingContext* context = 0) : SAXStateProcess( context ) {}
  	virtual ~twoDimVertexProcess() {}
  
  virtual const SAXComponentObject* Build() const { return this; }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs) {

		SAXObject** obj = Context()->GetTopObject();

		twoDimVertexType* twoDimVertex = new twoDimVertexType;
		*obj  = twoDimVertex;    

		twoDimVertex->set_x(attrs.getValue("x"));
		twoDimVertex->set_y(attrs.getValue("y"));
	}

	virtual void EndElement( const std::string& ) {}

	virtual void Characters( const std::string& ) {}

	virtual void StackPopNotify( const std::string&) {}

	virtual const std::string& State() const {

		static std::string tag = "twoDimVertex";
		return tag;
	}

protected:
	SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(twoDimVertexProcess)

#endif
