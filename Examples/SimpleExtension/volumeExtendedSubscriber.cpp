// $Id: volumeExtendedSubscriber.cpp,v 1.2 2013/04/09 21:21:43 jeremy Exp $
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"
#include "G4Processor/GDMLProcessor.h"
#include "Schema/volume.h"
#include "Schema/physvol.h"

#include "ColorType.h"
#include "SimpleExtensionProcessor.h"

#include "G4LogicalVolume.hh"
#include "G4VisAttributes.hh"

// std
#include <iostream>

class volumeExtendedSubscriber : virtual public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  volumeExtendedSubscriber()
  {
    Subscribe( "volume" );
  }

  virtual ~volumeExtendedSubscriber()
  {}

  virtual void Activate( const SAXObject* object)
  {
    std::cout << "volumeExtendedSubscriber::Activate" << std::endl;

    SimpleExtensionProcessor* proc = SimpleExtensionProcessor::instance();

    const volume* vobj = 0;
    G4LogicalVolume* lv;
    int nchildren = 0;

    if ( object ) {
      vobj = dynamic_cast<const volume*>( object );

      if ( vobj ) {

	// get LV
	lv = const_cast<G4LogicalVolume*>
	  ( GDMLProcessor::GetInstance()->GetLogicalVolume(vobj->get_name() ) );

	if ( lv ) {

	  // get content
	  const ContentSequence* seq = vobj->get_content();

	  // get size of content
	  size_t count = seq->size();

	  // iterate over and process content
	  for ( size_t i =0; i < count; i++ ) {

	    std::cout << "proc tag: " << seq->content(i).tag << std::endl;

	    // handle colorref
	    if ( seq->content(i).tag == "colorref" ) {
	      
	      std::cout << "handling colorref" << std::endl;
	      
	      ColorType::colorref* colorref =
		dynamic_cast<ColorType::colorref*> ( seq->content(i).object );
	      
	      G4VisAttributes* vis =
		dynamic_cast<G4VisAttributes*> ( proc->getVisAttributes( colorref->get_ref() ) );

	      if ( vis ) {
		std::cout << "assigning color: " << colorref->get_ref() << std::endl;
		lv->SetVisAttributes( vis );
	      }
	      else {
		std::cerr << "FATAL ERROR: color element not found - " << colorref->get_ref() << std::endl;
                G4Exception("", "", FatalException, "vis element not found.");
	      }
	    }
	  }
	}
	else {
          G4Exception("", "", FatalException, "Failed cast to LogicalVolume.");
	}
      }
      else {
        G4Exception("", "", FatalException, "Failed cast to volume!");
      }
    }
  }
};

DECLARE_SUBSCRIBER_FACTORY(volumeExtendedSubscriber)
