// -*- C++ -*-
// $Id: ParameterisedPlacementType.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_PARAMETERISEDPLACEMENTTYPE_H
#define GDML_SCHEMA_PARAMETERISEDPLACEMENTTYPE_H 1

#include "ContentGroup.h"
#include "ReferenceType.h"
#include "Schema/ParameterisationAlgorithmType.h"

class ParameterisedPlacementType
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

    class ParameterisationAlgorithm : public SAXObject, public ParameterisationAlgorithmType 
    {
    public:
      ParameterisationAlgorithm() {
        }
        virtual ~ParameterisationAlgorithm() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
  
public:
  ParameterisedPlacementType() {
  }
  ~ParameterisedPlacementType() {
  }
  
  const std::string& get_number() const
  {
    return m_number;
  }
  
  void set_number(const std::string& number)
  {
    m_number=number;
  }
  

  const ContentSequence* get_content() const {
    return &m_sequence;
  }
  
  void add_content( const std::string& tag, SAXObject* so ) {
    ContentGroup::ContentItem ci = { tag, so };
    m_sequence.add_content( ci );
  }
  
private:
  ContentSequence m_sequence;
  
  std::string m_number;

};


#endif // GDML_SCHEMA_PARAMETERISEDPLACEMENTTYPE_H
