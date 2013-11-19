// -*- C++ -*-
// $Id: property.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_PROPERTY_H
#define GDML_SCHEMA_PROPERTY_H 1

#include "ReferenceType.h"

class property : public SAXObject,
                 public ReferenceType
{
  public:
    property()
    {
    }
    ~property()
    {
    }
    virtual SAXObject::Type type()
    {
      return SAXObject::element;
    }
    const std::string& get_name() const
    {
      return m_name;
    }
    void set_name( const std::string& name )
    {
      m_name = name;
    }
  
  private:
    std::string m_name;  
};

#endif // GDML_SCHEMA_PROPERTY_H
