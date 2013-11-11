//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/torus.h"

#include "G4VSolid.hh"
#include "G4Torus.hh"

#include <iostream>

class torusSubscriber : public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const {
      return this;
    }

  public:
    torusSubscriber() {
      Subscribe( "torus" );
    }
    virtual ~torusSubscriber() {
    }
   
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
      if( object != 0 ) {
        try {
          const torus* obj = dynamic_cast<const torus*>( object );
      
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
          sval = obj->get_rtor();
          sval += "*"+lunit;
          double rtor = calc->Eval( sval );
          sval = obj->get_startphi();
          sval += "*"+aunit;
          double startphi = calc->Eval( sval );
          sval = obj->get_deltaphi();
          sval += "*"+aunit;
          double deltaphi = calc->Eval( sval );
          
          G4VSolid* newobj = new G4Torus( Util::generateName(name), rmin, rmax, rtor,
                                          startphi, deltaphi );
          
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

DECLARE_SUBSCRIBER_FACTORY(torusSubscriber)

  
