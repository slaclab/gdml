//
#ifndef BOX_DIMENSIONS_H
#define BOX_DIMENSIONS_H 1

#include "Saxana/SAXObject.h"

#include "Schema/DimensionsType.h"

class box_dimensions : public SAXObject, public DimensionsType
{
public:
  box_dimensions() {
  }
  virtual ~box_dimensions() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }

  void setx(std::string x)
  {
    m_x = x;
  }
  void sety(std::string y)
  {
    m_y = y;
  }
  void setz(std::string z)
  {
    m_z = z;
  }
  std::string getx()
  {
    return m_x;
  }
  std::string gety()
  {
    return m_y;
  }
  std::string getz()
  {
    return m_z;
  }

private:
  std::string m_x;
  std::string m_y;
  std::string m_z;
};



#endif // BOX_DIMENSIONS_H
