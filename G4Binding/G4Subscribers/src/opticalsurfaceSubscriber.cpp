//
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "Schema/opticalsurface.h"

#include "G4Processor/GDMLProcessor.h"
#include "G4Subscribers/Util.h"

#include "G4VSolid.hh"
#include "G4OpticalSurface.hh"

#include <iostream>

class opticalsurfaceSubscriber : public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  opticalsurfaceSubscriber() {
    Subscribe( "opticalsurface" );
  }
  virtual ~opticalsurfaceSubscriber() {
  }

  // The activation callback invoked by SAXG4Processor whenever it has
  // a new object created from XML and a corresponding subcriber exists
  virtual void Activate( const SAXObject* object ) {
    if( object != 0 ) {
      try {
        const opticalsurface* obj = dynamic_cast<const opticalsurface*>( object );

        GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

        const std::string& name = obj->get_name();

        const std::string& smodel = obj->get_model();
        G4OpticalSurfaceModel model;        
        if(smodel=="unified")
        {
          model = unified;
        }
        else 
        {
          model = glisur;
        }

        const std::string& sfinish = obj->get_finish();
        G4OpticalSurfaceFinish finish;

        if(sfinish=="polishedfrontpainted")
        {
          finish = polishedfrontpainted;
        }
        else if(sfinish=="polishedbackpainted")
        {
          finish = polishedbackpainted;
        }
        else if(sfinish=="ground")
        {
          finish = ground;
        }
        else if(sfinish=="groundfrontpainted")
        {
          finish = groundfrontpainted;
        }
        else if(sfinish=="groundbackpainted")
        {
          finish = groundbackpainted;
        }      
        else 
        {
          finish=polished;
        }
   
        const std::string& stype = obj->get_type();
        G4SurfaceType type;
        if(stype=="dielectric_metal")
        {
          type = dielectric_metal;
        }
        else if(stype=="x_ray")
        {
          type = x_ray;
        }
        else if(stype=="firsov")
        {
          type = firsov;
        }
        else
        {
          type = dielectric_dielectric;
        }

        const std::string& svalue = obj->get_value();
        double value = calc->Eval(svalue);

        G4SurfaceProperty* newobj = new G4OpticalSurface( Util::generateName(name), model, 
                                                 finish, type, value );

        GDMLProcessor::GetInstance()->AddSurfaceProperty( name, newobj );
      } catch(...) {
        std::cerr << "GOT INTO BAD_CAST TROUBLE!" << std::endl;
      }
    } else {
      std::cerr << "GOT ZERO DATA POINTER!" << std::endl;
    }
  }
};

DECLARE_SUBSCRIBER_FACTORY(opticalsurfaceSubscriber)



