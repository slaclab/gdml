// $Id: colorProcess.cpp,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#include "color.h"

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

// std
#include <iostream>

class colorProcess : public SAXStateProcess
{
public:

  colorProcess(const ProcessingContext* context = 0)
    : SAXStateProcess(context),
      m_obj(0)
  {}

  virtual ~colorProcess()
  {}

  virtual const SAXComponentObject* Build() const
  {
    return this;
  }
  
  virtual void StartElement(const std::string&, const ASCIIAttributeList& attrs)
  {
    std::cout << "colorProcess::StartElement()" << std::endl;

    SAXObject** obj = Context()->GetTopObject();
    
    color* c = new color;

    c->set_name( attrs.getValue("name") );
    c->set_R( attrs.getValue("R" ) );
    c->set_G( attrs.getValue("G" ) );
    c->set_B( attrs.getValue("B" ) );
    c->set_A( attrs.getValue("A" ) );
   
    m_obj = c;
    *obj = c;
  }

  virtual void EndElement(const std::string&)
  {}

  virtual void Characters(const std::string&)
  {}

  virtual void StackPopNotify(const std::string&)
  {}

  virtual const std::string& State() const
  {
    static std::string tag = "color";
    return tag;
  }

private:

  SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(colorProcess)
