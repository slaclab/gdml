// -*- C++ -*-
// $Id: DivisionPlacementType.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_DIVISIONPLACEMENTTYPE_H
#define GDML_SCHEMA_DIVISIONPLACEMENTTYPE_H 1

#include "ContentGroup.h"
#include "ReferenceType.h"
#include "Schema/positionType.h"
#include "Schema/rotationType.h"

class DivisionPlacementType
{
  public:
    
    class volumeref : public SAXObject, public ReferenceType {
      public:
        volumeref() {
        }
        virtual ~volumeref() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
    
  public:
    DivisionPlacementType() {
    }
    ~DivisionPlacementType() {
    }
  
    const ContentSequence* get_content() const {
      return &m_sequence;
    }

    void add_content( const std::string& tag, SAXObject* so ) {
      ContentGroup::ContentItem ci = { tag, so };
      m_sequence.add_content( ci );
    }

  const std::string& get_axis() const
  {
    return m_axis;
  }

  const std::string& get_number() const
  {
    return m_number;
  }
  
  const std::string& get_width() const
  {
    return m_width;
  }

  const std::string& get_offset() const
  {
    return m_offset;
  }

  const std::string& get_unit() const
  {
    return m_unit;
  }

  void set_axis(const std::string& axis)
  {
    m_axis = axis;
  }

  void set_number(const std::string& number)
  {
    m_number = number;
  }

  void set_width(const std::string& width)
  {
    m_width = width;
  }

  void set_offset(const std::string& offset)
  {
    m_offset = offset;
  }

  void set_unit(const std::string& unit)
  {
    m_unit = unit;
  }

private:
  ContentSequence m_sequence;
  
  std::string m_axis;
  std::string m_number;
  std::string m_width;
  std::string m_offset;
  std::string m_unit;

};


#endif // GDML_SCHEMA_DIVISIONPLACEMENTTYPE_H
