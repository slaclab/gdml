//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/trd.h"

#include "G4VSolid.hh"
#include "G4Trd.hh"

#include <iostream>

class trdSubscriber : public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const {
      return this;
    }

  public:
    trdSubscriber() {
      Subscribe( "trd" );
    }
    virtual ~trdSubscriber() {
    }
   
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
      if( object != 0 ) {
        try {
          const trd* obj = dynamic_cast<const trd*>( object );        
      
          GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
      
          const std::string& name = obj->get_name();
          std::string lunit = obj->get_lunit();
        
          std::string sval = obj->get_x1();
          sval += "*"+lunit;
          double dx1 = calc->Eval( sval ); dx1 = dx1/2.;
          sval = obj->get_y1();
          sval += "*"+lunit;
          double dy1 = calc->Eval( sval ); dy1 = dy1/2.;
          sval = obj->get_x2();
          sval += "*"+lunit;
          double dx2 = calc->Eval( sval ); dx2 = dx2/2.;
          sval = obj->get_y2();
          sval += "*"+lunit;
          double dy2 = calc->Eval( sval ); dy2 = dy2/2.;
          sval = obj->get_z();
          sval += "*"+lunit;
          double dz = calc->Eval( sval ); dz = dz/2.;        

          G4VSolid* newobj = new G4Trd( Util::generateName(name), dx1, dx2, dy1, dy2, dz);
        
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

DECLARE_SUBSCRIBER_FACTORY(trdSubscriber)

  
