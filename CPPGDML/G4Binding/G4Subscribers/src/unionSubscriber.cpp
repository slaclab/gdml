//
#include "G4Subscribers/BooleanSolidTypeSubscriber.h"
#include "G4Subscribers/Util.h"

#include "Schema/boolean_union.h"

#include "G4UnionSolid.hh"

class unionSubscriber : public BooleanSolidTypeSubscriber
{
  public:
    unionSubscriber() {
      Subscribe( "union" );
    }
    virtual ~unionSubscriber() {
    }
  
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
    
      const boolean_union* bu = dynamic_cast<const boolean_union*>( object );
    
      // First, let the base class extract the data
      BooleanSolidTypeSubscriber::Activate( object );
    
      // At this moment both constituent solids are ready
      // Let's check whether we need to apply any transformations
      G4VSolid* solid_union = 0;
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
        solid_union = new G4UnionSolid( Util::generateName(bu->get_name()), m_first, m_second, transform );
      } else {      
        solid_union = new G4UnionSolid( Util::generateName(bu->get_name()), m_first, m_second );
      }
    
      GDMLProcessor::GetInstance()->AddSolid( bu->get_name(), solid_union );
      //delete object;
    }
};

DECLARE_SUBSCRIBER_FACTORY(unionSubscriber)
