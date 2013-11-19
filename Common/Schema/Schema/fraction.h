// -*- C++ -*-
// $Id: fraction.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_FRACTION_H
#define GDML_SCHEMA_FRACTION_H 1

#include "ReferenceType.h"

class fraction : public SAXObject,
                 public ReferenceType
{
  public:
    fraction()
    {
    }
    ~fraction()
    {
    }
    virtual SAXObject::Type type()
    {
      return SAXObject::element;
    }
    const std::string& get_n() const
    {
      return m_n;
    }
    void set_n( const std::string& n )
    {
      m_n = n;
    }
  
  private:
    std::string m_n;  ///< xs:double
};

#endif // GDML_SCHEMA_FRACTION_H
