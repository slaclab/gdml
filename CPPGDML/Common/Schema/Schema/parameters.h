// -*- C++ -*-
// $Id: parameters.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_PARAMETERS_H
#define GDML_SCHEMA_PARAMETERS_H 1

#include "ContentGroup.h"


class parameters : public SAXObject
{
public:
  parameters()
  {
  }
  ~parameters()
  {
  }
  virtual SAXObject::Type type()
  {
    return SAXObject::element;
  }

public:  
  void set_number(std::string numb)
  {
    m_number = numb;
  }
  
  std::string get_number()
  {
    return m_number;
  }
  
  const ContentSequence* get_content() const {
    return &m_sequence;
  }
  
  void add_content( const std::string& tag, SAXObject* so ) {
    ContentGroup::ContentItem ci = { tag, so };
    m_sequence.add_content( ci );
  }
  
private:
  std::string m_number;
  ContentSequence m_sequence;

};

#endif // PARAMETERS_H
