#ifdef HAVE_G4TWISTEDTUBS

//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/twistedtubs.h"

#include "G4VSolid.hh"
#include "G4TwistedTubs.hh"

#include <iostream>

class twistedtubsSubscriber : public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const {
      return this;
    }

  public:
    twistedtubsSubscriber() {
      Subscribe( "twistedtubs" );
    }
    virtual ~twistedtubsSubscriber() {
    }
   
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
      if( object != 0 ) {
        try {
          const twistedtubs* obj = dynamic_cast<const twistedtubs*>( object );    
      
          GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
      
          std::string lunit = obj->get_lunit();
          std::string aunit = obj->get_aunit();
          const std::string& name = obj->get_name();
        
          std::string sval = obj->get_PhiTwist();
          sval += "*"+aunit;
          double phitwist = calc->Eval( sval );

          sval = obj->get_InnerRadius();
          sval += "*"+lunit;
          double rinner = calc->Eval( sval );

          sval = obj->get_OuterRadius();
          sval += "*"+lunit;
          double router = calc->Eval( sval ); 

          sval = obj->get_ZHalfLength();
          sval += "*"+lunit;
          double halfz = calc->Eval( sval ); halfz = halfz/2.;

          sval = obj->get_DPhi();
          sval += "*"+aunit;
          double dphi = calc->Eval( sval );        

          G4VSolid* newobj = new G4TwistedTubs( Util::generateName(name), phitwist, rinner, router, halfz, dphi );
      
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

DECLARE_SUBSCRIBER_FACTORY(twistedtubsSubscriber)

#endif

  
