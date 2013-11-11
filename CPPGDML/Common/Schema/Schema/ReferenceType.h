// -*- C++ -*-
// $Id: ReferenceType.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_REFERENCETYPE_H
#define GDML_SCHEMA_REFERENCETYPE_H 1

#include <string>

class ReferenceType
{
  public:
    ReferenceType() { }
    virtual ~ReferenceType() { }
    void set_ref( const std::string& s )
    {
      m_ref = s;
    }
    void set_ref( const char* s )
    {
      m_ref = s;
    }
    const std::string& get_ref() const
    {
      return m_ref;
    }
 
  private:
    std::string m_ref;  ///< IDREF
};


#endif // GDML_SCHEMA_REFERENCETYPE_H
