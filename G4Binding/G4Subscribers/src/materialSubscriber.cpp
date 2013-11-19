//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/MaterialLocator.h"
#include "G4Subscribers/MaterialLocator.h"
#include "G4Subscribers/Util.h"

#include "Schema/material.h"
#include "Schema/composite.h"
#include "Schema/fraction.h"

#include "G4Material.hh"

#include <iostream>

extern const double defaultTemp;
extern const double defaultPress;

class materialSubscriber : virtual public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const {
    return this;
  }

public:
  materialSubscriber() {
    Subscribe( "material" );
  }

  virtual ~materialSubscriber() {
  }

  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {

    GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

    const material* obj = 0;

    if( object != 0 ) {
      try {
        // Try the element type first
        obj = dynamic_cast<const material*>(object);

        if( obj != 0 ) {
          G4Material* mnew = 0;

          double      z = 0.0;
          double      a = 0.0;
          double      d = 0.0;
          double      t = defaultTemp;
          double      p = defaultPress;

          G4State     s = kStateUndefined;
          std::string f, str;

          // We need to check the emptyness as the Z and formula attributes are optional
          str = obj->get_Z();
          if( !str.empty() ) {
            z = calc->Eval( str );
          }

          // enum G4State { kStateUndefined, kStateSolid, kStateLiquid, kStateGas };
          str = obj->get_state();
          if( str == "gas" )
            s = kStateGas;
          else if( str == "liquid" )
            s = kStateLiquid;
          else if( str == "solid" )
            s = kStateSolid;
          else {
            // Can't happen
            ;
          }

          f = obj->get_formula();
          if( f.empty() ) {
            f=obj->get_name();
          }

          // Retrieve density
          const ContentChoice* dchoice = dynamic_cast<const ContentChoice*>( obj->get_DorDref() );

          if( dchoice->content().tag == "D" ) {
            // Inlined definition of density
            D* density = dynamic_cast<D*>( dchoice->content().object );
            str  = density->get_value();
            str += "*";
            str += density->get_unit();
            d    = calc->Eval( str );
          } else {
            // Reference to already defined density quantity
            Dref* dref = dynamic_cast<Dref*>( dchoice->content().object );
            str = dref->get_ref();
            d   = calc->Eval( str );
          }
          // Retrieve temperature if any
          const SAXObject* tso = obj->get_TorTref();
          if( tso != 0 ) {
            const ContentChoice* tchoice = dynamic_cast<const ContentChoice*>( tso );
            if( tchoice->content().tag == "T" ) {
              // Inlined definition of density
              T* temperature = dynamic_cast<T*>( tchoice->content().object );
              str  = temperature->get_value();
              str += "*";
              str += temperature->get_unit();
              t    = calc->Eval( str );
            } else {
              // Reference to already defined density quantity
              Tref* tref = dynamic_cast<Tref*>( tchoice->content().object );
              str = tref->get_ref();
              t   = calc->Eval( str );
            }
          }

          // Retrieve pressure if any
          const SAXObject* pso = obj->get_PorPref();
          if( pso != 0 ) {
            const ContentChoice* pchoice = dynamic_cast<const ContentChoice*>( pso );
            if( pchoice->content().tag == "P" ) {
              // Inlined definition of density
              P* pressure = dynamic_cast<P*>( pchoice->content().object );
              str  = pressure->get_value();
              str += "*";
              str += pressure->get_unit();
              p    = calc->Eval( str );
            } else {
              // Reference to already defined density quantity
              Pref* pref = dynamic_cast<Pref*>( pchoice->content().object );
              str = pref->get_ref();
              p   = calc->Eval( str );
            }
          }

          std::string tag;
          size_t count = 0;

          const ContentChoice* cc = obj->get_choice();
          if( cc->content().object->type() == SAXObject::element ) {
            // Must be an atom
            tag = cc->content().tag;
            atom* am = dynamic_cast<atom*>( cc->content().object );
            std::string sA = am->get_value();
            sA += "*";
            sA += am->get_unit();
            a = calc->Eval( sA );
            G4Material* existing = MaterialLocator::FindMaterial(Util::generateName(obj->get_name() ) );
            if(!existing)
            {
              mnew = new G4Material( Util::generateName(obj->get_name()), z, a, d, s, t, p );	      
            }
          } else {
            // Must be a sequence of composites or fractions
            const ContentSequence* cseq = dynamic_cast<const ContentSequence*>( cc->content().object );
            count = cseq->size();
            std::string tag = cseq->content( 0 ).tag;
            if( tag == "composite" ) {
              // Composition by atoms of elements
              G4Material* existing = MaterialLocator::FindMaterial(Util::generateName(obj->get_name() ) );
              if(!existing)
              {
                mnew = new G4Material( Util::generateName(obj->get_name()), d, count, s, t, p );
		
                for( unsigned int i = 0; i < count; i++ ) {
                  composite* ci = dynamic_cast<composite*>( cseq->content( i ).object );
                  int     natom = (int)calc->Eval( ci->get_n().c_str() );

                  // Find the element
                  G4Element*  etoadd = 0;
                  if ( ( etoadd = MaterialLocator::FindElement( ci->get_ref() ) ) != 0 )
                  {
                    mnew->AddElement( etoadd, natom );
                  }
                  else
                  {
                    std::cerr << "MATERIAL SUBSCRIBER:: element "
                              << ci->get_ref() << " not found!" << std::endl;
                    std::cerr << "Material " << obj->get_name() << " can't be created!" << std::endl;
                    std::cerr << "Please, re-order your materials or add the missing one..."
                              << std::endl;
                    G4Exception("", "", FatalException, "Shutting-down due to error(s) in GDML input...");
                  }
                }
              }
            }
            else
            {
              // Composition by fraction of mass
              G4Material* existing = MaterialLocator::FindMaterial(Util::generateName(obj->get_name() ) );
              if(!existing)
              {
                mnew = new G4Material( Util::generateName(obj->get_name()), d, count, s, t, p );
		
                for( unsigned int i = 0; i < count; i++ ) {
                  fraction* fi = dynamic_cast<fraction*>( cseq->content( i ).object );
                  double      frac = calc->Eval( fi->get_n().c_str() );

                  // Find the material or element
                  G4Material* mtoadd = 0;
                  G4Element*  etoadd = 0;

                  if ( ( mtoadd = MaterialLocator::FindMaterial( Util::generateName(fi->get_ref() ) ) ) != 0 )
                  {
                    mnew->AddMaterial( mtoadd, frac );
                  }
                  else if ( ( etoadd = MaterialLocator::FindElement( Util::generateName(fi->get_ref() ) ) ) != 0 )
                  {
                    mnew->AddElement( etoadd, frac );
                  }
                  else
                  {
                    std::cerr << "MATERIAL SUBSCRIBER:: material or element "
                              << fi->get_ref() << " not found!" << std::endl;
                    std::cerr << "Material " << obj->get_name() << " can't be created!" << std::endl;
                    std::cerr << "Please, re-order your materials or add the missing one..."
                              << std::endl;
                    G4Exception("", "", FatalException, "Shutting-down due to error(s) in GDML input...");
                  }
                }
              }
            }
          }
          // here we check whether there are any material properties tables associated
          for(unsigned i=0;i<obj->get_properties().size();i++)
          {
            G4MaterialPropertiesTable* matprop = mnew->GetMaterialPropertiesTable();
            if(!matprop) 
            {
              matprop = new G4MaterialPropertiesTable();
              mnew->SetMaterialPropertiesTable(matprop);
            }

            const MatrixType& matrix =
              GDMLProcessor::GetInstance()->GetMatrix(obj->get_properties()[i]->get_ref());
                        
            G4MaterialPropertyVector* propvect = new G4MaterialPropertyVector(0,0,0);
            
            int numbofentries = matrix.size()/matrix.get_coldim();

            for(int p=1;p<numbofentries+1;p++)
              //propvect->AddElement(matrix.get_value(p,1), matrix.get_value(p,2));           
              propvect->InsertValues(matrix.get_value(p,1), matrix.get_value(p,2));           

            matprop->AddProperty((obj->get_properties()[i]->get_name()).c_str(), propvect);
          }
        } else {
          // We're notified about one of our children
          // We've chosen content model based processing model here, so do nothing here
          ;
        }
      } catch(...) {
        std::cerr << "MATERIAL SUBSCRIBER:: GOT INTO BAD_CAST TROUBLE!" << std::endl;
      }
    } else {
      std::cerr << "MATERIAL SUBSCRIBER:: GOT ZERO DATA POINTER!" << std::endl;
    }
  }
};

DECLARE_SUBSCRIBER_FACTORY(materialSubscriber)
