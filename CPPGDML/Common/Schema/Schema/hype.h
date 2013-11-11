//
#ifndef HYPE_H
#define HYPE_H 1

#include "Saxana/SAXObject.h"

#include "Schema/SolidType.h"

class hype : public SolidType
{
  public:
    hype() {
    }
    virtual ~hype() {
    }
    virtual SAXObject::Type type() {
      return SAXObject::element;
    }
  
    const std::string& get_rmin() const {
      return m_rmin;
    }
    const std::string& get_rmax() const {
      return m_rmax;
    }
    const std::string& get_inst() const {
      return m_inst;
    }
    const std::string& get_outst() const {
      return m_outst;
    }
    const std::string& get_z() const {
      return m_z;
    }
  
    void set_rmin( const std::string& rmin ) {
      m_rmin = rmin;
    }
    void set_rmax( const std::string& rmax ) {
      m_rmax = rmax;
    }
    void set_inst( const std::string& inst ) {
      m_inst = inst;
    }
    void set_outst( const std::string& outst ) {
      m_outst = outst;
    }
    void set_z( const std::string& z ) {
      m_z = z;
    }
  
  private:
    std::string m_rmin;
    std::string m_rmax;
    std::string m_inst;
    std::string m_outst;
    std::string m_z;
};

#endif // HYPE_H
