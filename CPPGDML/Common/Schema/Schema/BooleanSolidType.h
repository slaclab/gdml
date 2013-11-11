// -*- C++ -*-
// $Id: BooleanSolidType.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#ifndef GDML_SCHEMA_BOOLEANSOLIDTYPE_H
#define GDML_SCHEMA_BOOLEANSOLIDTYPE_H 1

#include "Saxana/SAXObject.h"

#include "Schema/SolidType.h"
#include "Schema/ContentGroup.h"
#include "Schema/ReferenceType.h"
#include "Schema/positionType.h"
#include "Schema/rotationType.h"
#include "Schema/scaleType.h"

class BooleanSolidType : public SolidType
{
  public:
    class first : public SAXObject, public ReferenceType
    {
      public:
        first() {
        }
        virtual ~first() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
  
    class second : public SAXObject, public ReferenceType
    {
      public:
        second() {
        }
        virtual ~second() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
  
    class position : public SAXObject, public positionType {
      public:
        position() {
        }
        virtual ~position() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
  
    class positionref : public SAXObject, public ReferenceType {
      public:
        positionref() {
        }
        virtual ~positionref() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
  
    class rotation : public SAXObject, public rotationType {
      public:
        rotation() {
        }
        virtual ~rotation() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
  
    class rotationref : public SAXObject, public ReferenceType {
      public:
        rotationref() {
        }
        virtual ~rotationref() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };

    class scale : public SAXObject, public scaleType {
      public:
        scale() {
        }
        virtual ~scale() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };

    class scaleref : public SAXObject, public ReferenceType {
      public:
        scaleref() {
        }
        virtual ~scaleref() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };

    class firstposition : public SAXObject, public positionType {
      public:
        firstposition() {
        }
        virtual ~firstposition() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
  
    class firstpositionref : public SAXObject, public ReferenceType {
      public:
        firstpositionref() {
        }
        virtual ~firstpositionref() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
  
    class firstrotation : public SAXObject, public rotationType {
      public:
        firstrotation() {
        }
        virtual ~firstrotation() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };
  
    class firstrotationref : public SAXObject, public ReferenceType {
      public:
        firstrotationref() {
        }
        virtual ~firstrotationref() {
        }
        virtual SAXObject::Type type() {
          return SAXObject::element;
        }
    };  
  
  public:
    BooleanSolidType() {
    }
  
    virtual ~BooleanSolidType() {
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
};

#endif // GDML_SCHEMA_BOOLEANSOLIDTYPE_H
