// -*- C++ -*-
// $Id: ReplicaPlacementType.h,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#ifndef GDML_SCHEMA_REPLICAPLACEMENTTYPE_H
#define GDML_SCHEMA_REPLICAPLACEMENTTYPE_H 1

#include "ContentGroup.h"
#include "ReferenceType.h"
#include "Schema/ReplicationAlgorithmType.h"

class ReplicaPlacementType
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

    class ReplicationAlgorithm : public SAXObject, public ReplicationAlgorithmType 
    {
    public:
      ReplicationAlgorithm() {
        }
        virtual ~ReplicationAlgorithm() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
  
public:
  ReplicaPlacementType() {
  }
  ~ReplicaPlacementType() {
  }
  
  const std::string& get_numb() const
  {
    return m_numb;
  }
  const std::string& get_numb_start() const
  {
    return m_numb_start;
  }
  const std::string& get_numb_step() const
  {
    return m_numb_step;
  }
  
  void set_numb(const std::string& num)
  {
    m_numb=num;
  }
  void set_numb_start(const std::string& nstart)
  {
    m_numb_start=nstart;
  }
  void set_numb_step(const std::string& nstep)
  {
   m_numb_step=nstep;
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
  
  std::string m_numb;
  std::string m_numb_start;
  std::string m_numb_step ;

};


#endif // GDML_SCHEMA_REPLICAPLACEMENTTYPE_H
