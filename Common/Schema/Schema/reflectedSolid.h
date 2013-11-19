#ifndef REFLECTEDSOLID_H
#define REFLECTEDSOLID_H 1

#include "Saxana/SAXObject.h"
#include "Schema/SolidType.h"

class reflectedSolid : public SolidType {
public:
  reflectedSolid() {
  }
  virtual ~reflectedSolid() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }

  const std::string& get_solid() const {
    return m_solid;
  }
  
  const std::string& get_sx() const {
    return m_sx;
  }
  const std::string& get_sy() const {
    return m_sy;
  }
  const std::string& get_sz() const {
    return m_sz;
  }

  const std::string& get_rx() const {
    return m_rx;
  }
  const std::string& get_ry() const {
    return m_ry;
  }
  const std::string& get_rz() const {
    return m_rz;
  }
  
  const std::string& get_dx() const {
    return m_dx;
  }
  const std::string& get_dy() const {
    return m_dy;
  }
  const std::string& get_dz() const {
    return m_dz;
  }

  void set_solid(const std::string& solid)
  {
    m_solid = solid;
  }

  void set_sx(const std::string& xx) 
  {
    m_sx = xx;
  }
  void set_sy(const std::string& xy) 
  {
    m_sy = xy;
  }
  void set_sz(const std::string& xz) 
  {
    m_sz = xz;
  }
  
  void set_rx(const std::string& yx)  
  {
    m_rx = yx;
  }
  void set_ry(const std::string& yy) 
  {
    m_ry = yy;
  }
  void set_rz(const std::string& yz)  
  {  
    m_rz = yz;
  }

  void set_dx(const std::string& dx) 
  {
    m_dx = dx;
  }
  void set_dy(const std::string& dy) 
  {
    m_dy = dy;
  }
  void set_dz(const std::string& dz)  
  {
    m_dz = dz;
  }  
  
private:
  std::string m_solid;
  
  std::string m_sx;
  std::string m_sy;
  std::string m_sz;

  std::string m_rx;
  std::string m_ry;
  std::string m_rz;

  std::string m_dx;
  std::string m_dy;
  std::string m_dz;
};



#endif // REFLECTEDSOLID_H
