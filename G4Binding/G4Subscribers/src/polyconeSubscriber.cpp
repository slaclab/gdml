//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/polycone.h"
#include "Schema/zplane.h"

#include "G4VSolid.hh"
#include "G4Polycone.hh"

#include <iostream>

class polyconeSubscriber : public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const
    {
      return this;
    }

  public:
    polyconeSubscriber() {
      Subscribe( "polycone" );
    }
    virtual ~polyconeSubscriber() {
    }
   
    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
      if( object != 0 ) {
        try {
          const polycone* obj = dynamic_cast<const polycone*>( object );
      
          GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
      
          std::string lunit = obj->get_lunit();
          std::string aunit = obj->get_aunit();
          const std::string& name = obj->get_name();
          std::string sval;
        
          sval = obj->get_startphi();
          sval += "*"+aunit;
          double startphi = calc->Eval( sval );
          sval = obj->get_deltaphi();
          sval += "*"+aunit;
          double deltaphi = calc->Eval( sval );

          const ContentSequence* seq = obj->get_content();

          int numberofz = seq->size();          

          double* zets = new double[numberofz] ;
          double* rmins = new double[numberofz] ;
          double* rmaxs = new double[numberofz] ;
          
          for( int i = 0; i < numberofz; i++ )
          {
            zplane* zpl = dynamic_cast<zplane*>( seq->content(i).object );

            zets[i] = calc->Eval( zpl->get_z() + "*" + lunit );
            rmins[i] = calc->Eval( zpl->get_rmin() + "*" + lunit );
            rmaxs[i] = calc->Eval( zpl->get_rmax() + "*" + lunit );
          }

          G4VSolid* newobj = new G4Polycone(Util::generateName(name), startphi, deltaphi,
                                            numberofz, zets, rmins, rmaxs);
      

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

DECLARE_SUBSCRIBER_FACTORY(polyconeSubscriber)

  
