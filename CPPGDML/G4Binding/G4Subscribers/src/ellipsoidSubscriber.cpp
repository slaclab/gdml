#ifdef HAVE_G4ELLIPSOID

// --------------------------------------------------------------
// Comments
//                G.GUERRIERI - 26.06.2005
// --------------------------------------------------------------
//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"

#include "Schema/ellipsoid.h"

#include "G4VSolid.hh"
#include "G4Ellipsoid.hh"

#include <iostream>

class ellipsoidSubscriber : public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const {
      return this;
    }

public:
    ellipsoidSubscriber() {
      Subscribe( "ellipsoid" );
    }
    virtual ~ellipsoidSubscriber() {
    }
   
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
      //      std::cout << "ELLIPSOID SUBSCRIBER:: ";
      if( object != 0 ) {
        try {
          const ellipsoid* obj = dynamic_cast<const ellipsoid*>( object );    
        
          //  std::cout << "GOT ELLIPSOID " << obj->get_name() << std::endl;
      
          GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
      
          std::string lunit = obj->get_lunit();
          std::string aunit = obj->get_aunit();
          const std::string& name = obj->get_name();
          
          std::string sval = obj->get_ax();
          sval += "*"+lunit;
          double ax = calc->Eval( sval );
          sval = obj->get_by();
          sval += "*"+lunit;
          double by = calc->Eval( sval );
          sval = obj->get_cz();
          sval += "*"+aunit;
          double cz = calc->Eval( sval );
          sval = obj->get_zcut1();
          sval += "*"+aunit;
          double zcut1 = calc->Eval( sval );
          sval = obj->get_zcut2();
          sval += "*"+aunit;
          double zcut2 = calc->Eval( sval );
        
          G4VSolid* newobj = new G4Ellipsoid( name, ax, by, cz,
                                              zcut1, zcut2);
          GDMLProcessor::GetInstance()->AddSolid( name, newobj );      

        } catch(...) {
          std::cerr << "GOT INTO BAD_CAST TROUBLE!" << std::endl;
        }
      } else {
        std::cerr << "GOT ZERO DATA POINTER!" << std::endl;
      }
    }
};

DECLARE_SUBSCRIBER_FACTORY(ellipsoidSubscriber)

#endif  
