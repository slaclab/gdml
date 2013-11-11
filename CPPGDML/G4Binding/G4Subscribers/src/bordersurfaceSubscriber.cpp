//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/bordersurface.h"
#include "Schema/physvolref.h"

#include "G4Processor/GDMLProcessor.h"
#include "G4Subscribers/Util.h"

#include "G4VSolid.hh"
#include "G4LogicalBorderSurface.hh"

#include <iostream>

class bordersurfaceSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  bordersurfaceSubscriber() {
    Subscribe( "bordersurface" );
  }
  virtual ~bordersurfaceSubscriber() {
  }

  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {

    GDMLProcessor*  processor = GDMLProcessor::GetInstance();
    
    if( object != 0 ) {
      try {
        const bordersurface* obj = dynamic_cast<const bordersurface*>( object );
        
        const ContentSequence* seq = obj->get_content();

        std::string name = obj->get_name();
        std::string prop = obj->get_surfaceproperty();

        physvolref* vr1 = dynamic_cast<physvolref*>( seq->content(0).object );
        physvolref* vr2 = dynamic_cast<physvolref*>( seq->content(1).object );

        G4VPhysicalVolume* pvol1 = const_cast<G4VPhysicalVolume*>
          (processor->GetPhysicalVolume(vr1->get_ref()));
        
        G4VPhysicalVolume* pvol2 = const_cast<G4VPhysicalVolume*>
          (processor->GetPhysicalVolume(vr2->get_ref()));
        
        //        G4LogicalSurface* newobj = 
        new G4LogicalBorderSurface( Util::generateName(name), 
                                    pvol1, pvol2, processor->GetSurfaceProperty(prop) );
        
      } catch(...) {
        std::cerr << "GOT INTO BAD_CAST TROUBLE!" << std::endl;
      }
    } else {
      std::cerr << "GOT ZERO DATA POINTER!" << std::endl;
    }
  }
};

DECLARE_SUBSCRIBER_FACTORY(bordersurfaceSubscriber)



