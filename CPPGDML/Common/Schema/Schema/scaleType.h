//
#ifndef SCALETYPE_H
#define SCALETYPE_H 1

#include "IdentifiableQuantityVectorType.h"

class scaleType : public IdentifiableQuantityVectorType {
public:
	scaleType() {
	
		set_x("1.0");
		set_y("1.0");
		set_z("1.0");
	}
	~scaleType() {}
};

#endif 
