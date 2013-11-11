#include "Processes/SolidTypeProcess.h"
#include "Schema/xtru.h"

class xtruProcess : public SolidTypeProcess {
public:
	xtruProcess( const ProcessingContext* context = 0 ) : SolidTypeProcess(context) {}
	virtual ~xtruProcess() {}

	virtual void StartElement(const std::string& name,const ASCIIAttributeList& attrs) {  

		SAXObject** obj = Context()->GetTopObject();
    
		xtru* xtru_element = new xtru;
    
   		m_obj = xtru_element;
		*obj  = xtru_element;
    
		SolidTypeProcess::StartElement(name,attrs);
	}

	virtual void EndElement(const std::string& name) {
    	
		SolidTypeProcess::EndElement(name);
  	}

	virtual void StackPopNotify( const std::string& name) {

	    	SAXObject** so = Context()->GetTopObject();
		xtru* pobj = dynamic_cast<xtru*>(m_obj);
		pobj->add_content(name,*so);
   		SolidTypeProcess::StackPopNotify(name);
	}

	virtual const std::string& State() const {

		static std::string tag = "xtru";
	    	return tag;
	}
};

DECLARE_PROCESS_FACTORY(xtruProcess)


