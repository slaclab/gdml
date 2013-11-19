//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/isotope.h"

#include "G4Isotope.hh"

#include <iostream>

class isotopeSubscriber : virtual public SAXSubscriber
{
  public:
    virtual const SAXComponentObject* Build() const
    {
      return this;
    }

  public:
    isotopeSubscriber() {
      Subscribe( "isotope" );
    }

    virtual ~isotopeSubscriber() {
    }

    // The activation callback invoked by SAXG4Processor whenever it has
    // a new object created from XML and a corresponding subcriber exists
    virtual void Activate( const SAXObject* object ) {
    
      const isotope* obj = 0;
    
      if( object != 0 ) {
        try {
          obj = dynamic_cast<const isotope*>(object);
        
          if( obj != 0 ) {

            GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
            // The big moment, we're gonna create an isotope
            int z = static_cast<int>(calc->Eval( obj->get_Z() ));
            int n = static_cast<int>(calc->Eval( obj->get_N() ));
            std::string sA = obj->get_atom().get_value();
            sA += "*";
            sA += obj->get_atom().get_unit();
            double a = calc->Eval( sA );

            G4Isotope* inew = new G4Isotope( Util::generateName(obj->get_name()), z, n, a );
#ifdef GDML_VERBOSE
            std::cout << *inew << std::endl;
#endif
          }
        } catch(...) {
          std::cerr << "GOT INTO BAD_CAST TROUBLE!" << std::endl;
        }
      } else {
        std::cerr << "GOT ZERO DATA POINTER!" << std::endl;
      }
      //delete obj;
    }
  
  private:
    double     m_z;
    double     m_n;
    double     m_a;
    // Geant4 does not require material properties to be specified for isotopes 
};

DECLARE_SUBSCRIBER_FACTORY(isotopeSubscriber)
