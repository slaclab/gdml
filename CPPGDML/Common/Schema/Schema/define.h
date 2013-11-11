//
#ifndef DEFINE_H
#define DEFINE_H 1


#include "Saxana/SAXObject.h"

#include "Schema/defineType.h"
#include "Schema/IdentifiableConstantType.h"
#include "Schema/IdentifiableVariableType.h"
#include "Schema/IdentifiableQuantityType.h"
#include "Schema/IdentifiableExpressionType.h"
#include "Schema/positionType.h"
#include "Schema/rotationType.h"
#include "Schema/scaleType.h"
#include "Schema/MatrixType.h"

class define : public SAXObject, public defineType
{
public:
  define() {
  }
  virtual ~define() {
  }
  virtual SAXObject::Type type() {
    return SAXObject::element;
  }
public:
    class constant : public SAXObject, public IdentifiableConstantType
    {
    public:
      constant() {
      }
      virtual ~constant() {
      }
      virtual SAXObject::Type type() {
        return SAXObject::element;
      }
    };
    class variable : public SAXObject, public IdentifiableVariableType
    {
    public:
      variable() {
      }
      virtual ~variable() {
      }
      virtual SAXObject::Type type() {
        return SAXObject::element;
      }
    };
    class quantity : public SAXObject, public IdentifiableQuantityType
    {
    public:
      quantity() {
      }
      virtual ~quantity() {
      }
      virtual SAXObject::Type type() {
        return SAXObject::element;
      }
    };
    class expression : public SAXObject, public IdentifiableExpressionType
    {
      public:
        expression() {
      }
      virtual ~expression() {
      }
      virtual SAXObject::Type type() {
        return SAXObject::element;
      }
    };
    class position : public SAXObject, public positionType
    {
    public:
      position() {
      }
      virtual ~position() {
      }
      virtual SAXObject::Type type() {
        return SAXObject::element;
      }
    };
    class rotation : public SAXObject, public rotationType
    {
    public:
      rotation() {
      }
      virtual ~rotation() {
      }
      virtual SAXObject::Type type() {
        return SAXObject::element;
      }
    };
    class scale : public SAXObject, public scaleType
    {
    public:
      scale() {
      }
      virtual ~scale() {
      }
      virtual SAXObject::Type type() {
        return SAXObject::element;
      }
    };
    class matrix : public SAXObject, public MatrixType
    {
     public:
       matrix() {
       }
       virtual ~matrix() {
       }
       virtual SAXObject::Type type() {
         return SAXObject::element;
       }
    };

};

#endif // DEFINE_H
