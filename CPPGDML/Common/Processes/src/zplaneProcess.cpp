// -*- C++ -*-
// $Id: zplaneProcess.cpp,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#ifndef GDML_PROCESS_ZPLANE_H
#define GDML_PROCESS_ZPLANE_H 1

#include "Saxana/ProcessingConfigurator.h"
#include "Saxana/ProcessingContext.h"
#include "Saxana/SAXProcessor.h"
#include "Saxana/StateStack.h"
#include "Saxana/SAXProcessingState.h"
#include "Saxana/SAXStateProcess.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/zplane.h"

class zplaneProcess : public SAXStateProcess
{
public:
  zplaneProcess( const ProcessingContext* context = 0 )
  : SAXStateProcess( context ) {
  }
  
  virtual ~zplaneProcess() {
  }
  
  virtual const SAXComponentObject* Build() const {
    return this;
  }

  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string&, const ASCIIAttributeList& attrs) 
  {
    SAXObject** obj = Context()->GetTopObject();

    zplane* zplane_element = new zplane;
    *obj  = zplane_element;    

    zplane_element->set_z(attrs.getValue("z"));
    zplane_element->set_rmin(attrs.getValue("rmin"));
    zplane_element->set_rmax(attrs.getValue("rmax"));
  }

  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& ) {
  }

  // Analogical to SAX characters callback, it's called for ignorableWhitespace too!
  virtual void Characters( const std::string& ) {
  }
  
  // Invoked whenever one of the daughter state processes has been popped-out of the state stack
  // The name passed-in as the argument is the name of the XML element for which that's been done
  virtual void StackPopNotify( const std::string&) 
  {
  }

  // The name of the state this object will process
  virtual const std::string& State() const
  {
    static std::string tag = "zplane";
    return tag;
  }

protected:
  SAXObject* m_obj;
};

DECLARE_PROCESS_FACTORY(zplaneProcess)

#endif // 
