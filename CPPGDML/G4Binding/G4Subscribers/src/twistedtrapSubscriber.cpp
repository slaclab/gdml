#ifdef HAVE_G4TWISTEDTRAP

//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/twistedtrap.h"

#include "G4Processor/GDMLProcessor.h"
////#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "G4VSolid.hh"
#include "G4TwistedTrap.hh"

#include <iostream>

class twistedtrapSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  twistedtrapSubscriber() {
    Subscribe( "twistedtrap" );
  }
  virtual ~twistedtrapSubscriber() {
  }

  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {
    if( object != 0 ) {
      try {
        const twistedtrap* obj = dynamic_cast<const twistedtrap*>( object );

        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

        const std::string& name = obj->get_name();

	std::string sval = obj->get_pPhiTwist();
        sval += "*";
        sval += obj->get_aunit();
        double dTw = calc->Eval( sval ); dTw = dTw/2.;

        sval = obj->get_pDz();
        sval += "*";
        sval += obj->get_lunit();
        double dz = calc->Eval( sval ); dz = dz/2.;

	sval = obj->get_pTheta();
        sval += "*";
        sval += obj->get_aunit();
        double dTh = calc->Eval( sval ); dTh = dTh/2.;

	sval = obj->get_pPhi();
        sval += "*";
        sval += obj->get_aunit();
        double dPh = calc->Eval( sval ); dPh = dPh/2.;

	sval = obj->get_pDy1();
        sval += "*";
        sval += obj->get_lunit();
        double dy1 = calc->Eval( sval ); dy1 = dy1/2.;

	sval = obj->get_pDx1();
        sval += "*";
        sval += obj->get_lunit();
        double dx1 = calc->Eval( sval ); dx1 = dx1/2.;

	sval = obj->get_pDx2();
        sval += "*";
        sval += obj->get_lunit();
        double dx2 = calc->Eval( sval ); dx2 = dx2/2.;

	sval = obj->get_pDy2();
        sval += "*";
        sval += obj->get_lunit();
        double dy2 = calc->Eval( sval ); dy2 = dy2/2.;

        sval = obj->get_pDx3();
        sval += "*";
        sval += obj->get_lunit();
        double dx3 = calc->Eval( sval ); dx3 = dx3/2.;

        sval = obj->get_pDx4();
        sval += "*";
        sval += obj->get_lunit();
        double dx4 = calc->Eval( sval ); dx4 = dx4/2.;

        sval = obj->get_pAlph();
        sval += "*";
        sval += obj->get_aunit();
        double dAl = calc->Eval( sval ); dAl = dAl/2.;

        G4VSolid* newobj = new G4TwistedTrap( Util::generateName(name), dTw, dz, dTh, dPh, dy1, dx1, dx2, dy2, dx3, dx4, dAl );

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

DECLARE_SUBSCRIBER_FACTORY(twistedtrapSubscriber)

#endif



