//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/hype.h"

#include "G4VSolid.hh"
#include "G4Hype.hh"

#include <iostream>

class hypeSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const {
    return this;
  }

public:
  hypeSubscriber() {
    Subscribe( "hype" );
  }
  virtual ~hypeSubscriber() {
  }
   
  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {
    if( object != 0 ) {
      try {
        const hype* obj = dynamic_cast<const hype*>( object );        
      
        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
      
        std::string lunit = obj->get_lunit();
        std::string aunit = obj->get_aunit();
        const std::string& name = obj->get_name();
        
        std::string sval = obj->get_rmin();
        sval += "*"+lunit;
        double rmin = calc->Eval( sval );

        sval = obj->get_rmax();
        sval += "*"+lunit;
        double rmax = calc->Eval( sval );

        sval = obj->get_inst();
        sval += "*"+aunit;
        double inst = calc->Eval( sval );

        sval = obj->get_outst();
        sval += "*"+aunit;
        double outst = calc->Eval( sval );

        sval = obj->get_z();
        sval += "*"+lunit;
        double z = calc->Eval( sval );

        G4VSolid* newobj = new G4Hype( Util::generateName(name), rmin, rmax,
                                       inst, outst, z/2.0);

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

DECLARE_SUBSCRIBER_FACTORY(hypeSubscriber)
