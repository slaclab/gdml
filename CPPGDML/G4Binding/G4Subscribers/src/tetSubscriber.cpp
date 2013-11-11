//
#ifdef HAVE_G4TET

#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
#include "G4Subscribers/Util.h"

#include "Schema/tet.h"

#include "G4VSolid.hh"
#include "G4Tet.hh"

#include <iostream>

class tetSubscriber : public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const {
      return this;
    }

  public:
    tetSubscriber() {
      Subscribe( "tet" );
    }
    virtual ~tetSubscriber() {
    }
   
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
      if( object != 0 ) {
        try {
          const tet* obj = dynamic_cast<const tet*>( object );    
          GDMLProcessor* processor = GDMLProcessor::GetInstance();
      
          const std::string& name = obj->get_name();

          G4VSolid* newobj = new G4Tet( Util::generateName(name), 
                                        *const_cast<G4ThreeVector*>(processor->GetPosition(obj->get_vertex1())),
                                        *const_cast<G4ThreeVector*>(processor->GetPosition(obj->get_vertex2())),
                                        *const_cast<G4ThreeVector*>(processor->GetPosition(obj->get_vertex3())),
                                        *const_cast<G4ThreeVector*>(processor->GetPosition(obj->get_vertex4())));
          
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

DECLARE_SUBSCRIBER_FACTORY(tetSubscriber)

#endif

  
