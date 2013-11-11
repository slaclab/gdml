#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/sectionType.h"

class sectionProcess : public SAXStateProcess {
public:
	sectionProcess(const ProcessingContext* context = 0) : SAXStateProcess( context ) {}
  	virtual ~sectionProcess() {}
  
  virtual const SAXComponentObject* Build() const { return this; }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs) {

		SAXObject** obj = Context()->GetTopObject();

		sectionType* section = new sectionType;
		*obj  = section;    

		section->set_zOrder(attrs.getValue("zOrder"));
		section->set_zPosition(attrs.getValue("zPosition"));
		section->set_xOffset(attrs.getValue("xOffset"));
		section->set_yOffset(attrs.getValue("yOffset"));
		section->set_scalingFactor(attrs.getValue("scalingFactor"));
	
	}

	virtual void EndElement( const std::string& ) {}

	virtual void Characters( const std::string& ) {}

	virtual void StackPopNotify( const std::string&) {}

	virtual const std::string& State() const {

		static std::string tag = "section";
		return tag;
	}

protected:
	SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(sectionProcess)
