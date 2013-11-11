// -*- C++ -*-
// $Id: VolumeType.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#ifndef GDML_SCHEMA_VOLUMETYPE_H
#define GDML_SCHEMA_VOLUMETYPE_H 1

#include "IdentifiableVolumeType.h"
#include "ReferenceType.h"
#include "SinglePlacementType.h"
#include "ContentGroup.h"

class VolumeType : public IdentifiableVolumeType
{
  public:
  
    class materialref : public SAXObject,
                        public ReferenceType
    {
      public:
        materialref() { }
        ~materialref() { }
        virtual SAXObject::Type type() { return SAXObject::element; }
    };
  
    class solidref : public SAXObject,
                     public ReferenceType
    {
      public:
        solidref() { }
        ~solidref() { }
        virtual SAXObject::Type type() { return SAXObject::element; }
    };
  
  public:
    VolumeType() { }
    virtual ~VolumeType() { }
  
    const ContentSequence* get_content() const
    {
      return &m_sequence;
    }
    void add_content( const std::string& tag, SAXObject* so )
    {
      ContentGroup::ContentItem ci = { tag, so };
      m_sequence.add_content( ci );
      if(tag=="solidref")
      {
       sol_ref=so;
      }
    }
    SAXObject* get_sol_ref() const
    {
     return sol_ref;
    }
    
  private:
    ContentSequence m_sequence;
    SAXObject *sol_ref;
};

#endif // GDML_SCHEMA_VOLUMETYPE_H
