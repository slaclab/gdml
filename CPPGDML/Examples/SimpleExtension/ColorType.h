// $Header: /nfs/slac/g/lcd/cvs/lcdroot/gdml2/CPPGDML/Examples/SimpleExtension/ColorType.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $

#ifndef COLORTYPE_H
#define COLORTYPE_H 1

#include "Schema/ReferenceType.h"

#include <string>

/**
   @class ColorType
   @brief ColorType from schema.
*/
class ColorType
{
 public:
  class colorref : public SAXObject, public ReferenceType 
  {
  public:
    colorref()
    {}
    
    virtual ~colorref()
    {}

    virtual SAXObject::Type type()
    {
      return SAXObject::element;
    }
  };

public:
  ColorType()
  {}

  virtual ~ColorType()
  {}

  void set_R(const std::string& r)
  {
    m_R = r;
  }

  void set_G(const std::string& g)
  {
    m_G = g;
  }


  void set_B(const std::string& b)
  {
    m_B = b;
  }

  void set_A(const std::string& a)
  {
    m_A = a;
  }

  void set_name(const std::string& name)
  {
    m_name = name;
  }

  const std::string& get_R() const
  {
    return m_R;
  }

  const std::string& get_G() const
  {
    return m_G;
  }

  const std::string& get_B() const
  {
    return m_B;
  }

  const std::string& get_A() const
  {
    return m_A;
  }

  const std::string& get_name() const
  {
    return m_name;
  }

private:
  std::string m_R;
  std::string m_G;
  std::string m_B;
  std::string m_A;
  std::string m_name;
};

#endif
