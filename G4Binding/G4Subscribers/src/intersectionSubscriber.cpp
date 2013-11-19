//
#include "G4Subscribers/BooleanSolidTypeSubscriber.h"
#include "G4Subscribers/Util.h"

#include "Schema/boolean_intersection.h"

#include "G4IntersectionSolid.hh"

class intersectionSubscriber : public BooleanSolidTypeSubscriber
{
  public:
    intersectionSubscriber() {
      Subscribe( "intersection" );
    }
    virtual ~intersectionSubscriber() {
    }
  
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
    
      const boolean_intersection* bi = dynamic_cast<const boolean_intersection*>( object );
    
      // First, let the base class extract the data
      BooleanSolidTypeSubscriber::Activate( object );
    
      // At this moment both constituent solids are ready
      // Let's check whether we need to apply any transformations
      G4VSolid* solid_intersection = 0;
      bool useTransform = false;
      G4ThreeVector translat;
      G4RotationMatrix transrot;
    
      if( m_translation != 0 ) {
        translat = *m_translation;
        useTransform = true;
      }
    
      if( m_rotation != 0 ) {
        transrot = *m_rotation;
        useTransform = true;
      }

      if( useTransform ) {    
        G4Transform3D transform( transrot, translat );
        solid_intersection = new G4IntersectionSolid( Util::generateName(bi->get_name()), m_first, m_second, transform );
      } else {      
        solid_intersection = new G4IntersectionSolid( Util::generateName(bi->get_name()), m_first, m_second );
      }
    
      GDMLProcessor::GetInstance()->AddSolid( bi->get_name(), solid_intersection );
      //delete object;
    }
};

DECLARE_SUBSCRIBER_FACTORY(intersectionSubscriber)
