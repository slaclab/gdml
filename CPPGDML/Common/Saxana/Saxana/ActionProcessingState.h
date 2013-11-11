//
#ifndef ACTION_PROCESING_STATE_H
#define ACTION_PROCESING_STATE_H 1

#include "ProcessingState.h"
#include "SAXEventGun.h"

class ActionProcessingState : virtual public ProcessingState
{
public:
  //typedef RCObjectHandle<SAXEventGun> EventGun;
  typedef SAXEventGun* EventGun;
  
  ActionProcessingState();
  virtual ~ActionProcessingState();

  virtual ProcessingState::EType Type() const
  {
    return ProcessingState::eAction;
  }

private:
  EventGun fPrevious;
};

#endif // ACTION_PROCESING_STATE_H

