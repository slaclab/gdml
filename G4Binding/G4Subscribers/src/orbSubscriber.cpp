//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/orb.h"

#include "G4VSolid.hh"
#include "G4Orb.hh"

#include <iostream>

class orbSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const {
    return this;
  }

public:
  orbSubscriber() {
    Subscribe( "orb" );
  }
  virtual ~orbSubscriber() {
  }
   
  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {
    if( object != 0 ) {
      try {
        const orb* obj = dynamic_cast<const orb*>( object );    
        
        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
      
        std::string lunit = obj->get_lunit();
        std::string aunit = obj->get_aunit();
        const std::string& name = obj->get_name();
        
        std::string sval = obj->get_r();
        sval += "*"+lunit;
        double r = calc->Eval( sval );
          
        G4VSolid* newobj = new G4Orb( Util::generateName(name), r );
          
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

DECLARE_SUBSCRIBER_FACTORY(orbSubscriber)

  
  
