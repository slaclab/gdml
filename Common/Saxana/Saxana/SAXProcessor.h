// -*- C++ -*-
// $Id: SAXProcessor.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#ifndef GDML_SAXANA_SAX_PROCESSOR_H
#define GDML_SAXANA_SAX_PROCESSOR_H 1

#include "ProcessingContext.h"
#include "StatusCode.h"

class SAXEvent;
class SAXEventGun;
class StateStack;
class StateProcessMap;
class SAXSubscriberPool;
class ProcessingConfigurator;
class SAXObject;

class SAXProcessor : virtual public ProcessingContext
{
public:
  SAXProcessor();
  virtual ~SAXProcessor();
  
  ///> Mandatory interface from ProcessingContext
  virtual const StateStack*             GetStack() const;
  virtual const SAXEvent*               GetLastEvent() const;
  virtual const SAXEventGun*            GetSAXEventGun() const; 
  virtual void                          SetSAXEventGun( const SAXEventGun* gun );
  virtual const ProcessingConfigurator* GetConfig() const;
  virtual SAXObject**                   GetTopObject() const;
  virtual const char*                   GetParentState() const;
  
  const SAXSubscriberPool* GetSubscriberPool();
  
  StatusCode Initialize();
  StatusCode Configure( ProcessingConfigurator* config );
  StatusCode Run();
  StatusCode Finalize();
  
  void ProcessEvent( const SAXEvent* const event );
  
private:
  StateProcessMap*        fMap;
  SAXSubscriberPool*      fPool;
  StateStack*             fStack;
  StateStack*             fNotifyStack;
  ProcessingConfigurator* fConfig;
  const SAXEvent*         fCurrentEvent;
  const SAXEventGun*      fCurrentGun;
  bool                    fIgnoring;
};

#endif // GDML_SAXANA_SAX_PROCESSOR_H

