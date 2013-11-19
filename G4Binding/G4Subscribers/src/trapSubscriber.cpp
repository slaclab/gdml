//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/trap.h"

#include "G4VSolid.hh"
#include "G4Trap.hh"

#include <iostream>

class trapSubscriber : public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const {
      return this;
    }

  public:
    trapSubscriber() {
      Subscribe( "trap" );
    }
    virtual ~trapSubscriber() {
    }
   
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
      //std::cout << "GENERAL TRAPEZOID SUBSCRIBER:: ";
      if( object != 0 ) {
        try {
          const trap* obj = dynamic_cast<const trap*>( object );    
        
          // std::cout << "GOT GENERAL TRAPEZOID " << obj->get_name() << std::endl;
      
          GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
      
          const std::string& name = obj->get_name();
          std::string lunit = obj->get_lunit();
          std::string aunit = obj->get_aunit();
        
          std::string sval = obj->get_x1();
          sval += "*"+lunit;
          double dx1 = calc->Eval( sval ); dx1 = dx1/2.;
          sval = obj->get_x2();
          sval += "*"+lunit;
          double dx2 = calc->Eval( sval ); dx2 = dx2/2.;
          sval = obj->get_x3();
          sval += "*"+lunit;
          double dx3 = calc->Eval( sval ); dx3 = dx3/2.;
          sval = obj->get_x4();
          sval += "*"+lunit;
          double dx4 = calc->Eval( sval ); dx4 = dx4/2.;
          sval = obj->get_y1();
          sval += "*"+lunit;
          double dy1 = calc->Eval( sval ); dy1 = dy1/2.;
          sval = obj->get_y2();
          sval += "*"+lunit;
          double dy2 = calc->Eval( sval ); dy2 = dy2/2.;
          sval = obj->get_z();
          sval += "*"+lunit;
          double dz = calc->Eval( sval ); dz = dz/2.;
        
          sval = obj->get_theta();
          sval += "*"+aunit;
          double dtheta = calc->Eval( sval );
          sval = obj->get_phi();
          sval += "*"+aunit;
          double dphi = calc->Eval( sval );
          sval = obj->get_alpha1();
          sval += "*"+aunit;
          double dalpha1 = calc->Eval( sval );
          sval = obj->get_alpha2();
          sval += "*"+aunit;
          double dalpha2 = calc->Eval( sval );        
          
          G4VSolid* newobj = new G4Trap( Util::generateName(name), dz, dtheta, dphi, dy1, dx1, dx2, dalpha1,
                                         dy2, dx3, dx4, dalpha2);
      
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

DECLARE_SUBSCRIBER_FACTORY(trapSubscriber)

  
