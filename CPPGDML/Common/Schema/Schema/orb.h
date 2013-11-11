//
#ifndef ORB_H
#define ORB_H 1

#include "Saxana/SAXObject.h"

#include "Schema/SolidType.h"

class orb : public SolidType
{
  public:
    orb() {
    }
    virtual ~orb() {
    }
    virtual SAXObject::Type type() {
      return SAXObject::element;
    }
  
    const std::string& get_r() const {
      return m_r;
    }
  
    void set_r( const std::string& r ) {
      m_r = r;
    }
  
  private:
    std::string m_r;
};



#endif // ORB_H
