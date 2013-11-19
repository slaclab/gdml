//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/box.h"

#include "G4Processor/GDMLProcessor.h"
////#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "G4VSolid.hh"
#include "G4Box.hh"

#include <iostream>

class boxSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  boxSubscriber() {
    Subscribe( "box" );
  }
  virtual ~boxSubscriber() {
  }

  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {
    if( object != 0 ) {
      try {
        const box* obj = dynamic_cast<const box*>( object );

        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

        const std::string& name = obj->get_name();
        std::string sval = obj->get_x();
        sval += "*";
        sval += obj->get_lunit();
        double dx = calc->Eval( sval ); dx = dx/2.;
        sval = obj->get_y();
        sval += "*";
        sval += obj->get_lunit();
        double dy = calc->Eval( sval ); dy = dy/2.;
        sval = obj->get_z();
        sval += "*";
        sval += obj->get_lunit();
        double dz = calc->Eval( sval ); dz = dz/2.;

        G4VSolid* newobj = new G4Box( Util::generateName(name), dx, dy, dz );

        GDMLProcessor::GetInstance()->AddSolid( name, newobj );
      } catch(...) {
        std::cerr << "GOT INTO BAD_CAST TROUBLE!" << std::endl;
      }
    } else {
      std::cerr << "GOT ZERO DATA POINTER!" << std::endl;
    }
    //delete object;
  }
};

DECLARE_SUBSCRIBER_FACTORY(boxSubscriber)



