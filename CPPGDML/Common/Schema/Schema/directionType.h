#ifndef DIRECTIONTYPE_H
#define DIRECTIONTYPE_H 1


#include "IdentifiableQuantityVectorType.h"


class directionType : public IdentifiableQuantityVectorType {
public:
  directionType() {
    set_unit( "mm" );
    set_type( "cartesian" );
  }
  ~directionType() {
  }
};



#endif // DIRECTIONTYPE_H
