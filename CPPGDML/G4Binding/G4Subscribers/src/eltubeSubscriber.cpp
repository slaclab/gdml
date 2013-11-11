//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/eltube.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "G4VSolid.hh"
#include "G4EllipticalTube.hh"

#include <iostream>

class eltubeSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  eltubeSubscriber() {
    Subscribe( "eltube" );
  }
  virtual ~eltubeSubscriber() {
  }
   
  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {
    if( object != 0 ) {
      try {
        const eltube* obj = dynamic_cast<const eltube*>( object );        
      
        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
        
        const std::string& name = obj->get_name();
        std::string sval = obj->get_dx();
        sval += "*";
        sval += obj->get_lunit();
        double dx = calc->Eval( sval );
        sval = obj->get_dy();
        sval += "*";
        sval += obj->get_lunit();
        double dy = calc->Eval( sval );
        sval = obj->get_dz();
        sval += "*";
        sval += obj->get_lunit();
        double dz = calc->Eval( sval );
        
        G4VSolid* newobj = new G4EllipticalTube( Util::generateName(name), dx, dy, dz );
        
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

DECLARE_SUBSCRIBER_FACTORY(eltubeSubscriber)

  
  
