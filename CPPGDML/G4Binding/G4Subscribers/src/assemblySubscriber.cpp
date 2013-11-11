//
// $Id: assemblySubscriber.cpp,v 1.2 2012-02-01 12:10:23 jeremy Exp $
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
////#include "G4Processor/GDMLExpressionEvaluator.h"

#include "Schema/assembly.h"
#include "Schema/physvol.h"
#include "Schema/SinglePlacementType.h"

#include "G4Material.hh"
#include "G4AssemblyVolume.hh"

#include <iostream>
#include <sstream>

class assemblySubscriber : virtual public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const {
      return this;
    }

  public:
    assemblySubscriber() {
      Subscribe( "assembly" );
    }

    virtual ~assemblySubscriber() {
    }

    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object )
    {
      //std::cout << "ASSEMBLY VOLUME SUBSCRIBER:: " << std::endl;

      GDMLProcessor*           processor = GDMLProcessor::GetInstance();
      GDMLExpressionEvaluator* calc      = GDMLProcessor::GetInstance()->GetEvaluator();

      const assembly* obj = 0;

      if( object != 0 )
      {
        try
        {
          obj = dynamic_cast<const assembly*>( object );

          if( obj != 0 )
          {
            //std::cout << "GOT ASSEMBLY VOLUME " << obj->get_name() << std::endl;

            // Let's analyze content model if volume
            const ContentSequence* seq = obj->get_content();
            size_t count = seq->size();

            G4AssemblyVolume* anew = new G4AssemblyVolume;

            for( size_t i = 0; i < count; i++ )
            {
              if( seq->content(i).tag == "physvol" )
              {
                // Analyze each physvol's content
                physvol* c = dynamic_cast<physvol*>( seq->content(i).object );
                const ContentSequence* physvol_seq = c->get_content();
                size_t ccount = physvol_seq->size();

                SinglePlacementType::volumeref*   vr   = 0;
                SinglePlacementType::positionref* pr   = 0;
                SinglePlacementType::rotationref* rr   = 0;
                G4AssemblyTriplet*                ptrp = 0;
                G4LogicalVolume*                  plog = 0;
                G4ThreeVector*                    ppos = 0;
                G4RotationMatrix*                 prot = 0;

                for( size_t cidx = 0; cidx < ccount; cidx++ )
                {
                  if( physvol_seq->content(cidx).tag == "volumeref" )
                  {
                    // Check & retrieve volume
                    vr = dynamic_cast<SinglePlacementType::volumeref*>
                      ( physvol_seq->content(cidx).object );
                    plog = const_cast<G4LogicalVolume*>(processor->GetLogicalVolume( vr->get_ref()));
                    if( plog == 0 ) {
                      std::cerr << "ASSEMBLY VOLUME SUBSCRIBER:: physvol volume "
                                << vr->get_ref() << " not found!" << std::endl;
                      std::cerr << "Assembly volume " << obj->get_name() << " can't be created!" << std::endl;
                      std::cerr << "Please, re-order your volumes or add the missing one..." << std::endl;
                      std::cerr << "\nNOTE! Assembly can't contain another assembly!\n" << std::endl;
                      G4Exception("", "", FatalException, "Shutting-down due to error(s) in GDML input...");
                    }
                  }
                  else if( physvol_seq->content(cidx).tag == "choice" )
                  {
                    // Apparently we got the choices holding one of position, rotation,
                    // positionref or rotationref
                    const ContentChoice*
                      avchoice = dynamic_cast<const ContentChoice*>( physvol_seq->content(cidx).object );

                    if( avchoice->content().tag == "position" )
                    {
                      // We define::rotation as currently we keep all definitions global
                      // This might change in future if scoped defintions will be needed, if ever
                      define::position* p = dynamic_cast<define::position*>( avchoice->content().object );
//                       std::cout << "GOT position " << p->get_name() << " = ("
//                                 << p->get_x()    << "," << p->get_y()    << "," << p->get_z()    << ")"
//                                 << p->get_unit() << std::endl;
                      std::string expr = p->get_x() + "*" + p->get_unit();
                      double dx = calc->Eval( expr.c_str() );
                      expr = p->get_y() + "*" + p->get_unit();
                      double dy = calc->Eval( expr.c_str() );
                      expr = p->get_z() + "*" + p->get_unit();
                      double dz = calc->Eval( expr.c_str() );
                      ppos = new G4ThreeVector( dx, dy, dz );
                      GDMLProcessor::GetInstance()->AddPosition( p->get_name(), ppos );
                    }
                    else if( avchoice->content().tag == "rotation" ) {
                      // We define::rotation as currently we keep all definitions global
                      // This might change in future if scoped defintions will be needed, if ever
                      define::rotation* r = dynamic_cast<define::rotation*>( avchoice->content().object );
//                       std::cout << "GOT rotation " << r->get_name() << " = " << "("
//                                 << r->get_x() << "," << r->get_y() << "," << r->get_z() << ")"
//                                 << r->get_unit() << std::endl;
                      std::string expr = r->get_x() + "*" + r->get_unit();
                      double dx = calc->Eval( expr.c_str() );
                      expr = r->get_y() + "*" + r->get_unit();
                      double dy = calc->Eval( expr.c_str() );
                      expr = r->get_z() + "*" + r->get_unit();
                      double dz = calc->Eval( expr.c_str() );
                      G4RotationMatrix* prot = new G4RotationMatrix;
                      prot->rotateX( dx );
                      prot->rotateY( dy );
                      prot->rotateZ( dz );
                      GDMLProcessor::GetInstance()->AddRotation( r->get_name(), prot );
                    }
                    else if( avchoice->content().tag == "positionref" ) {
                      // Check & retrieve position
                      pr = dynamic_cast<SinglePlacementType::positionref*>( avchoice->content().object );
                      ppos = const_cast<G4ThreeVector*>( processor->GetPosition( pr->get_ref() ) );
                      if( ppos == 0 ) {
                        std::cerr << "ASSEMBLY VOLUME SUBSCRIBER:: physvol's position "
                                  << pr->get_ref() << " not found!" << std::endl;
                        std::cerr << "Assembly volume " << obj->get_name()
                                  << " can't be created!" << std::endl;
                        std::cerr << "Please, check your position definitions or add the missing one..."
                                  << std::endl;
                        G4Exception("", "", FatalException, "Shutting-down due to error(s) in GDML input...");
                      }
                    }
                    else if( avchoice->content().tag == "rotationref" ) {
                      // Check & retrieve rotation
                      rr = dynamic_cast<SinglePlacementType::rotationref*>( avchoice->content().object );
                      prot = const_cast<G4RotationMatrix*>( processor->GetRotation( rr->get_ref() ) );
                      if( prot == 0 ) {
                        std::cerr << "ASSEMBLY VOLUME SUBSCRIBER:: physvol's rotation "
                                  << rr->get_ref() << " not found!" << std::endl;
                        std::cerr << "Assembly volume " << obj->get_name()
                                  << " can't be created!" << std::endl;
                        std::cerr << "Please, check your rotation definitions or add the missing one..."
                                  << std::endl;
                        G4Exception("", "", FatalException, "Shutting-down due to error(s) in GDML input...");
                      }
                    } else { /* Should not happen */ } // end of ifs-over pos. and rot.
                  } else { /* Should not happen */ } // end of if-choice
                } // end of for(;;)

                // At this point we should have everything ready to create assembly triplet
                ptrp = new G4AssemblyTriplet( plog, *ppos, prot );
                anew->AddPlacedVolume( plog, *ppos, prot );
                processor->AddAssemblyVolume( obj->get_name(), anew );

              } else { /* Should not happen */ } // end of if-physvol
            } // end of for(;;) over assembly content model items
          } // end of if-obj
        } catch(...) { std::cerr << "ASSEMBLY VOLUME SUBSCRIBER:: GOT INTO BAD_CAST TROUBLE!" << std::endl; }
      } else { std::cerr << "ASSEMBLY VOLUME SUBSCRIBER:: GOT ZERO DATA POINTER!" << std::endl; }
      //delete object;
    } // end of Activate method
};

DECLARE_SUBSCRIBER_FACTORY(assemblySubscriber)
