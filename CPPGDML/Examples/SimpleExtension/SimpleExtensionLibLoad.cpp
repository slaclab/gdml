#include "Saxana/SAXComponentFactory.h"

#include <iostream>

extern "C" {

  void SimpleExtensionLibLoad()
  {
    LOAD_COMPONENT(colorProcess);
    LOAD_COMPONENT(colorrefProcess);
    LOAD_COMPONENT(colorSubscriber);    
    LOAD_COMPONENT(volumeExtendedSubscriber);
  }
}
