//
#ifndef LOGICALSURFACETYPETYPE_H
#define LOGICALSURFACETYPETYPE_H 1

#include <string>

class LogicalSurfaceType {
public:
  LogicalSurfaceType() {
  }
  ~LogicalSurfaceType() {
  }
  
  const std::string& get_surfaceproperty() const {
    return m_surfaceproperty;
  }
  const std::string& get_name() const {
    return m_name;
  }
  
  void set_surfaceproperty( const std::string& prop ) {
    m_surfaceproperty = prop;
  }
  void set_name( const std::string& name ) {
    m_name = name;
  }
  
private:
  std::string m_surfaceproperty;
  std::string m_name; 
};



#endif // LOGICALSURFACETYPETYPE_H
