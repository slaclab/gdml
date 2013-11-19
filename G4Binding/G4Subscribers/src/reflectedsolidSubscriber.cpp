//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/reflectedSolid.h"

#include "G4Processor/GDMLProcessor.h"
#include "G4Evaluator/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "G4VSolid.hh"
#include "G4ReflectedSolid.hh"
#include "G4Transform3D.hh"

#include <iostream>

class reflectedSolidSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  reflectedSolidSubscriber() {
    Subscribe( "reflectedSolid" );
  }
  virtual ~reflectedSolidSubscriber() {
  }
   
  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {
    if( object != 0 ) {
      try {
        const reflectedSolid* obj = dynamic_cast<const reflectedSolid*>( object );        
        
        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
      
        const std::string& name = obj->get_name();
        
        std::string solidname = obj->get_solid();

        G4VSolid* solid = const_cast<G4VSolid*>
          (GDMLProcessor::GetInstance()->GetSolid(solidname));

        if( solid == 0 ) 
        {
          // We're in trouble we can't create reflected solid
          std::cerr << "REFLECTED SOLID SUBSCRIBER:: solid "
                    << solidname << " not found!" << std::endl;
          std::cerr << "Reflected solid " << obj->get_name() << " can't be created!" << std::endl;
          std::cerr << "Please, re-order your solids or add the missing one..."
                    << std::endl;
          G4Exception("", "", FatalException, "Shutting-down due to error(s) in GDML input...");
        }
        
        std::string sval = obj->get_sx();
        double sx = calc->Eval( sval );
        sval = obj->get_sy();
        double sy = calc->Eval( sval );
        sval = obj->get_sz();
        double sz = calc->Eval( sval );

        sval = obj->get_rx();
        sval += "*";
        sval += obj->get_aunit();
        double rx = calc->Eval( sval );
        sval = obj->get_ry();
        sval += "*";
        sval += obj->get_aunit();
        double ry = calc->Eval( sval );
        sval = obj->get_rz();
        sval += "*";
        sval += obj->get_aunit();
        double rz = calc->Eval( sval );

        sval = obj->get_dx();
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
        
	G4RotationMatrix rot;
        rot.rotateX(rx);
        rot.rotateY(ry);
        rot.rotateZ(rz);

        G4ThreeVector trans(dx, dy, dz);

        G4Scale3D scale(sx, sy, sz);

        G4Transform3D transform(rot, trans);
        transform = transform*scale;
          
        G4VSolid* newobj = new G4ReflectedSolid( Util::generateName(name), 
                                                 solid,
                                                 transform);
        
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

DECLARE_SUBSCRIBER_FACTORY(reflectedSolidSubscriber)

  
  
