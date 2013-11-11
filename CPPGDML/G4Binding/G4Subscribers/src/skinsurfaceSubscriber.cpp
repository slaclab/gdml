//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/skinsurface.h"
#include "Schema/SinglePlacementType.h"

#include "G4Processor/GDMLProcessor.h"
#include "G4Subscribers/Util.h"

#include "G4VSolid.hh"
#include "G4LogicalSkinSurface.hh"

#include <iostream>

class skinsurfaceSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  skinsurfaceSubscriber() {
    Subscribe( "skinsurface" );
  }
  virtual ~skinsurfaceSubscriber() {
  }

  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {

    GDMLProcessor*  processor = GDMLProcessor::GetInstance();
    
    if( object != 0 ) {
      try {
        const skinsurface* obj = dynamic_cast<const skinsurface*>( object );
        
        const ContentSequence* seq = obj->get_content();
        
        std::string name = obj->get_name();
        std::string prop = obj->get_surfaceproperty();
        
        SinglePlacementType::volumeref* vr = dynamic_cast<SinglePlacementType::volumeref*>
          ( seq->content(0).object );

        G4LogicalVolume* lvol = const_cast<G4LogicalVolume*>
          (processor->GetLogicalVolume(vr->get_ref()));
                
        //G4LogicalSurface* newobj = 
        new G4LogicalSkinSurface( Util::generateName(name), 
                                  lvol, processor->GetSurfaceProperty(prop) );

      } catch(...) {
        std::cerr << "GOT INTO BAD_CAST TROUBLE!" << std::endl;
      }
    } else {
      std::cerr << "GOT ZERO DATA POINTER!" << std::endl;
    }
  }
};

DECLARE_SUBSCRIBER_FACTORY(skinsurfaceSubscriber)



