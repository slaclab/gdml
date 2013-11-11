//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/cone.h"

#include "G4VSolid.hh"
#include "G4Cons.hh"

#include <iostream>

class coneSubscriber : public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const
    {
      return this;
    }

  public:
    coneSubscriber() {
      Subscribe( "cone" );
    }
    virtual ~coneSubscriber() {
    }
   
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
      //std::cout << "CONE SUBSCRIBER:: ";
      if( object != 0 ) {
        try {
          const cone* obj = dynamic_cast<const cone*>( object );    
        
          //std::cout << "GOT CONE " << obj->get_name() << std::endl;
      
          GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
      
          std::string lunit = obj->get_lunit();
          std::string aunit = obj->get_aunit();
          const std::string& name = obj->get_name();
        
          std::string sval = obj->get_rmin1();
          sval += "*"+lunit;
          double rmin1 = calc->Eval( sval );
          sval = obj->get_rmin2();
          sval += "*"+lunit;
          double rmin2 = calc->Eval( sval );
          sval = obj->get_rmax1();
          sval += "*"+lunit;
          double rmax1 = calc->Eval( sval );
          sval = obj->get_rmax2();
          sval += "*"+lunit;
          double rmax2 = calc->Eval( sval );
          sval = obj->get_z();
          sval += "*"+lunit;
          double dz = calc->Eval( sval ); dz = dz/2.;
          sval = obj->get_startphi();
          sval += "*"+aunit;
          double startphi = calc->Eval( sval );
          sval = obj->get_deltaphi();
          sval += "*"+aunit;
          double deltaphi = calc->Eval( sval );

          G4VSolid* newobj = new G4Cons( Util::generateName(name), rmin1, rmax1, rmin2, rmax2, dz, startphi, deltaphi );
      
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

DECLARE_SUBSCRIBER_FACTORY(coneSubscriber)

  
