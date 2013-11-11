#ifdef HAVE_G4TWISTEDTRD

//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/twistedtrd.h"

#include "G4Processor/GDMLProcessor.h"
////#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "G4VSolid.hh"
#include "G4TwistedTrd.hh"

#include <iostream>

class twistedtrdSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  twistedtrdSubscriber() {
    Subscribe( "twistedtrd" );
  }
  virtual ~twistedtrdSubscriber() {
  }

  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {
    if( object != 0 ) {
      try {
        const twistedtrd* obj = dynamic_cast<const twistedtrd*>( object );

        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

        const std::string& name = obj->get_name();

	std::string sval = obj->get_pDx1();
        sval += "*";
        sval += obj->get_lunit();
        double dx1 = calc->Eval( sval ); dx1 = dx1/2.;

	sval = obj->get_pDx2();
        sval += "*";
        sval += obj->get_lunit();
        double dx2 = calc->Eval( sval ); dx2 = dx2/2.;

	sval = obj->get_pDy1();
        sval += "*";
        sval += obj->get_lunit();
        double dy1 = calc->Eval( sval ); dy1 = dy1/2.;

	sval = obj->get_pDy2();
        sval += "*";
        sval += obj->get_lunit();
        double dy2 = calc->Eval( sval ); dy2 = dy2/2.;

        sval = obj->get_pDz();
        sval += "*";
        sval += obj->get_lunit();
        double dz = calc->Eval( sval ); dz = dz/2.;

	sval = obj->get_pPhiTwist();
        sval += "*";
        sval += obj->get_aunit();
        double dTw = calc->Eval( sval );

        G4VSolid* newobj = new G4TwistedTrd( Util::generateName(name), dx1, dx2, dy1, dy2, dz, dTw );

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

DECLARE_SUBSCRIBER_FACTORY(twistedtrdSubscriber)

#endif



