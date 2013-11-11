//
#ifndef SURFACEPROPERTYTYPE_H
#define SURFACEPROPERTYTYPE_H 1

#include <string>

class SurfacePropertyType {
public:
  SurfacePropertyType() {
  }
  ~SurfacePropertyType() {
  }
  
  const std::string& get_name() const {
    return m_name;
  }
  
  void set_name( const std::string& name ) {
    m_name = name;
  }

  const std::string& get_type() const {
    return m_type;
  }
  
  void set_type( const std::string& type ) {
    m_type = type;
  }
  
private:
  std::string m_name; 
  std::string m_type; 
};



#endif // SURFACEPROPERTYTYPE_H
