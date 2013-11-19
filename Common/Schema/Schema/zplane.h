#ifndef ZPLANE_H
#define ZPLANE_H 1

#include "Saxana/SAXObject.h"

class zplane : public SAXObject
{
public:
  zplane() 
  {
  }
  virtual ~zplane() 
  {
  }
  virtual SAXObject::Type type() 
  {
    return SAXObject::element;
  }
  
  void set_z(const std::string& z) 
  {
    m_z = z;
  }
  void set_rmin(const std::string& rmin)
  {
    m_rmin = rmin;
  }
  void set_rmax(const std::string& rmax)
  {
    m_rmax = rmax;
  }
  const std::string& get_z()
  {
    return m_z;
  }
  const std::string& get_rmin()
  {
    return m_rmin;
  }
  const std::string& get_rmax()
  {
      return m_rmax;
  }
private:
  std::string m_z;
  std::string m_rmin;
  std::string m_rmax;
};

#endif // ZPLANE_H
