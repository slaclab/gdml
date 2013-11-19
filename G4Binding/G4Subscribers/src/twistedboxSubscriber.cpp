#ifdef HAVE_G4TWISTEDBOX

//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/twistedbox.h"

#include "G4Processor/GDMLProcessor.h"
////#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "G4VSolid.hh"
#include "G4TwistedBox.hh"

#include <iostream>

class twistedboxSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  twistedboxSubscriber() {
    Subscribe( "twistedbox" );
  }
  virtual ~twistedboxSubscriber() {
  }

  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {
    if( object != 0 ) {
      try {
        const twistedbox* obj = dynamic_cast<const twistedbox*>( object );

        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

        const std::string& name = obj->get_name();

        std::string sval = obj->get_pDx();
        sval += "*";
        sval += obj->get_lunit();
        double dx = calc->Eval( sval ); dx = dx/2.;

        sval = obj->get_pDy();
        sval += "*";
        sval += obj->get_lunit();
        double dy = calc->Eval( sval ); dy = dy/2.;

        sval = obj->get_pDz();
        sval += "*";
        sval += obj->get_lunit();
        double dz = calc->Eval( sval ); dz = dz/2.;

        sval = obj->get_pPhiTwist();
        sval += "*";
        sval += obj->get_aunit();
        double dt = calc->Eval( sval ); dt = dt/2.;

        G4VSolid* newobj = new G4TwistedBox( Util::generateName(name), dt, dx, dy, dz );

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

DECLARE_SUBSCRIBER_FACTORY(twistedboxSubscriber)

#endif



