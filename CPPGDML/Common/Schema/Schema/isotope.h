// -*- C++ -*-
// $Id: isotope.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_ISOTOPE_H
#define GDML_SCHEMA_ISOTOPE_H 1

#include "MaterialIsotopeType.h"

class isotope : public SAXObject,
                public MaterialIsotopeType
{
  public:
    isotope()
    {
    }
    ~isotope()
    {
    }
    virtual SAXObject::Type type()
    {
      return SAXObject::element;
    }
};

#endif // GDML_SCHEMA_ISOTOPE_H
