// -*- C++ -*-
// $Id: ContentGroup.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
// GEANT4 tag $Name:  $
#ifndef GDML_SCHEMA_CONTENTGROUP_H
#define GDML_SCHEMA_CONTENTGROUP_H 1

#include "Saxana/SAXObject.h"

#include <vector>

#include <iostream>

class ContentGroup : public SAXObject {
public:
  typedef enum {
    sequence,
    choice,
    all
  } ContentType;
  struct ContentItem {
    std::string tag;
    SAXObject*  object;
  };
public:
  ContentGroup() {
  }
  virtual ~ContentGroup() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::contentGroup;
  }
  virtual ContentGroup::ContentType content_type() const = 0;
  virtual bool               empty() = 0;
};

class ContentChoice : public ContentGroup {
public:
  ContentChoice() {
    m_choice.tag    = "";
    m_choice.object = 0;
  }
  virtual ~ContentChoice() {
    if( m_choice.object != 0 ) {
      //std::cout << "ContentChoice destructor deleting " << m_choice.tag << std::endl;
      delete m_choice.object;
    }
  }
  virtual ContentGroup::ContentType content_type() const {
    return ContentGroup::choice;
  }
  virtual bool empty() {
    return( m_choice.object == 0 );
  }
  void set_content( ContentItem& ci ) {
    m_choice = ci;
  }
  ContentItem& content() {
    return m_choice;
  }
  const ContentItem& content() const {
    return m_choice;
  }

private:
  ContentItem m_choice;
};

class ContentSequence : public ContentGroup {
public:
  ContentSequence() {
  }
  virtual ~ContentSequence() {
    for( unsigned int idx= 0; idx < m_sequence.size(); idx++ ) {
      if( m_sequence[idx].object != 0 ) {
        //std::cout << "ContentSequence destructor deleting " << m_sequence[idx].tag << std::endl;
        delete m_sequence[idx].object;
      }
    }
  }
  virtual ContentGroup::ContentType content_type() const {
    return ContentGroup::sequence;
  }
  virtual bool empty() {
    return( m_sequence.size() == 0 );
  }
  size_t size() const {
    return( m_sequence.size() );
  }
  void add_content( ContentItem& ci ) {
    m_sequence.push_back( ci );
  }
  ContentItem content( unsigned int idx ) const {
    return m_sequence[idx];
  }
  void clear() {
    for( unsigned int idx= 0; idx < m_sequence.size(); idx++ ) {
      if( m_sequence[idx].object != 0 ) {
        //std::cout << "ContentSequence destructor clearing " << m_sequence[idx].tag << std::endl;
        delete m_sequence[idx].object;
      }
    }
    m_sequence.clear();
  }
  
private:
  std::vector<ContentItem> m_sequence;
};

#endif // GDML_SCHEMA_CONTENTGROUP_H
