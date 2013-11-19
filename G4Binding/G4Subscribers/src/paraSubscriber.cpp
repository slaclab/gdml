//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/para.h"

#include "G4VSolid.hh"
#include "G4Para.hh"

#include <iostream>

class paraSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const {
    return this;
  }

public:
  paraSubscriber() {
    Subscribe( "para" );
  }
  virtual ~paraSubscriber() {
  }
   
  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {
    if( object != 0 ) {
      try {
        const para* obj = dynamic_cast<const para*>( object );        
      
        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
      
        const std::string& name = obj->get_name();
        std::string lunit = obj->get_lunit();
        std::string aunit = obj->get_aunit();
        
        std::string sval = obj->get_x();
        sval += "*"+lunit;
        double dx = calc->Eval( sval ); dx = dx/2.;
        sval = obj->get_y();
        sval += "*"+lunit;
        double dy = calc->Eval( sval ); dy = dy/2.;
        sval = obj->get_z();
        sval += "*"+lunit;
        double dz = calc->Eval( sval ); dz = dz/2.;
        sval = obj->get_alpha();
        sval += "*"+aunit;
        double dalpha = calc->Eval( sval );
        sval = obj->get_theta();
        sval += "*"+aunit;
        double dtheta = calc->Eval( sval );
        sval = obj->get_phi();
        sval += "*"+aunit;
        double dphi = calc->Eval( sval );
        G4VSolid* newobj = new G4Para( Util::generateName(name), dx, dy, dz, dalpha, dtheta, dphi);
      
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

DECLARE_SUBSCRIBER_FACTORY(paraSubscriber)

