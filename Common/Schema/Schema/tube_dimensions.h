//
#ifndef TUBE_DIMENSIONS_H
#define TUBE_DIMENSIONS_H 1

#include "Saxana/SAXObject.h"

#include "Schema/DimensionsType.h"

class tube_dimensions : public SAXObject, public DimensionsType
{
public:
  tube_dimensions() {
  }
  virtual ~tube_dimensions() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }

  void setdp(std::string dp)
  {
    m_dp = dp;
  }
  void setinr(std::string inr)
  {
    m_inr = inr;
  }
  void setoutr(std::string outr)
  {
    m_outr = outr;
  }
  void setsphi(std::string sphi)
  {
    m_sphi = sphi;
  }
  void sethz(std::string hz)
  {
    m_hz = hz;
  }



  std::string getdp()
  {
    return m_dp;
  }
  std::string getinr()
  {
    return m_inr;
  }
  std::string getoutr()
  {
    return m_outr;
  }
  std::string getsphi()
  {
    return m_sphi;
  }
  std::string gethz()
  {
    return m_hz;
  }

private:
  std::string m_dp;
  std::string m_inr;
  std::string m_outr;
  std::string m_sphi;
  std::string m_hz;
  
};



#endif // TUBE_DIMENSIONS_H
