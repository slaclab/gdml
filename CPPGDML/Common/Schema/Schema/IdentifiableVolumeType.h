// -*- C++ -*-
// $Id: IdentifiableVolumeType.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#ifndef GDML_SCHEMA_IDENTIFIABLEVOLUMETYPE_H
#define GDML_SCHEMA_IDENTIFIABLEVOLUMETYPE_H 1

#include <string>

class IdentifiableVolumeType {
public:
  IdentifiableVolumeType() {
  }
  virtual ~IdentifiableVolumeType() {
  }
  const std::string& get_name() const {
    return m_ID;
  }
  void set_name( const std::string& n ) {
    m_ID = n;
  }
private:
  std::string m_ID;
};



#endif // GDML_SCHEMA_IDENTIFIABLEVOLUMETYPE_H
