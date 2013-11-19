// $Id: colorSubscriber.cpp,v 1.1.1.1 2010/07/13 15:18:49 jeremy Exp $
#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "color.h"
#include "SimpleExtensionProcessor.h"

#include <iostream>
#include <sstream>

class colorSubscriber : virtual public SAXSubscriber
{
public:
  virtual const SAXComponentObject* Build() const
  {
    return this;
  }

public:
  colorSubscriber()
  {
    Subscribe("color");
  }

  virtual ~colorSubscriber() 
  {}

  virtual void Activate(const SAXObject* object)
  {
    std::cout << "colorSubscriber::Activate()" << std::endl;
    
    if ( object != 0 ) {
      const color* c = dynamic_cast<const color*> ( object );

      if ( c ) {

	const std::string& name = c->get_name();       
	std::stringstream ss;
	
	ss << c->get_R() << " " << c->get_G() << " " << c->get_B() << " " << c->get_A();
	double r,g,b,a;
	ss >> r >> g >> b >> a;
	std::cout << "r g b a = " << r << " " << g << " " << b << " " << a << std::endl;

	G4VisAttributes* vis = new G4VisAttributes;
	vis->SetColor(r,g,b,a);
		
	SimpleExtensionProcessor::instance()->addVisAttributes( name, vis );
      }
    }
  }
};

DECLARE_SUBSCRIBER_FACTORY(colorSubscriber)
