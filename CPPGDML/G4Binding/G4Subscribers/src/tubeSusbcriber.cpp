//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/tube.h"

#include "G4VSolid.hh"
#include "G4Tubs.hh"

#include <iostream>

class tubeSubscriber : public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const {
      return this;
    }

  public:
    tubeSubscriber() {
      Subscribe( "tube" );
    }
    virtual ~tubeSubscriber() {
    }
   
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
      if( object != 0 ) {
        try {
          const tube* obj = dynamic_cast<const tube*>( object );    
      
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
          sval = obj->get_z();
          sval += "*"+lunit;
          double dz = calc->Eval( sval ); dz = dz/2.;
          sval = obj->get_startphi();
          sval += "*"+aunit;
          double startphi = calc->Eval( sval );
          sval = obj->get_deltaphi();
          sval += "*"+aunit;
          double deltaphi = calc->Eval( sval );        

          G4VSolid* newobj = new G4Tubs( Util::generateName(name), rmin, rmax, dz, startphi, deltaphi );
      
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

DECLARE_SUBSCRIBER_FACTORY(tubeSubscriber)

  
