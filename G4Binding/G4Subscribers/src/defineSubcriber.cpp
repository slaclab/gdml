#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"

#include "Schema/define.h"

#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"

#include <iostream>
#include <string>

class defineSubscriber : virtual public SAXSubscriber {
public:
	defineSubscriber()  { Subscribe("define"); }

	virtual const SAXComponentObject* Build() const { return this; }
	virtual ~defineSubscriber()  {}

	virtual void Activate( const SAXObject* object )  {

	// The activation callback invoked by SAXG4Processor whenever it has
	// a new object created from XML and a corresponding subcriber exists

	GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
	
	const define* define_element = 0;

	if (object != 0) {
		
		try {
			define_element = dynamic_cast<const define*>(object);

			if (define_element->size()>0) {
				
				unsigned int num = define_element->size();

				for (unsigned int idx = 0; idx < num; idx++) {

					if (define_element->get_content(idx)->type() == SAXObject::contentGroup) {
						
						// Fine that's what's expected here
						ContentChoice* choice = dynamic_cast<ContentChoice*>(define_element->get_content(idx));
						ContentGroup::ContentItem item = choice->content();

						if (item.tag == "constant") {
						
							define::constant* c = dynamic_cast<define::constant*>(item.object);
							//std::cout << "GOT constant " << c->get_name() << " = " << c->get_value() << std::endl;
							calc->RegisterConstant(c);
						}
						else if (item.tag == "variable") {
							
							define::variable* v = dynamic_cast<define::variable*>(item.object);
							double vvalue = calc->EvaluateString(v->get_value());
							calc->RegisterVariable(v->get_name(),vvalue);
						}
						else if (item.tag == "quantity") {
							
							define::quantity* q = dynamic_cast<define::quantity*>(item.object);
							//std::cout << "GOT quantity " << q->get_name() << " = " << q->get_value() << q->get_unit() << std::endl;
							calc->RegisterPhysConstant(q);
						}
						else if (item.tag == "expression") {
							
							define::expression* e = dynamic_cast<define::expression*>(item.object);
							calc->RegisterExpression(e);
						}
						else if(item.tag == "position") {

							define::position* p = dynamic_cast<define::position*>(item.object);
							std::string expr = p->get_x() + "*" + p->get_unit();
							double dx = calc->Eval( expr.c_str() );
							expr = p->get_y() + "*" + p->get_unit();
							double dy = calc->Eval( expr.c_str() );
							expr = p->get_z() + "*" + p->get_unit();
							double dz = calc->Eval( expr.c_str() );
							G4ThreeVector* posobj = new G4ThreeVector( dx, dy, dz );
							GDMLProcessor::GetInstance()->AddPosition( p->get_name(), posobj );
						}
						else if (item.tag == "rotation") {

							define::rotation* r = dynamic_cast<define::rotation*>(item.object);
							std::string expr = r->get_x() + "*" + r->get_unit();
							double dx = calc->Eval( expr.c_str() );
							expr = r->get_y() + "*" + r->get_unit();
							double dy = calc->Eval( expr.c_str() );
							expr = r->get_z() + "*" + r->get_unit();
							double dz = calc->Eval( expr.c_str() );
							G4RotationMatrix* rotobj = new G4RotationMatrix;
							rotobj->rotateX( dx );
							rotobj->rotateY( dy );
							rotobj->rotateZ( dz );
							GDMLProcessor::GetInstance()->AddRotation( r->get_name(), rotobj );
						} 
						else if (item.tag=="scale") {
		
							define::scale* s = dynamic_cast<define::scale*>(item.object);
								
							double sx = calc->Eval(s->get_x().c_str());
							double sy = calc->Eval(s->get_y().c_str());
							double sz = calc->Eval(s->get_z().c_str());

							G4ThreeVector *sclobj = new G4ThreeVector(sx,sy,sz);
							GDMLProcessor::GetInstance()->AddScale(s->get_name(),sclobj);
						} 
						else if( item.tag == "matrix" ) {		

							std::cout << "define - handling matrix element" << std::endl;
  	  		  
							MatrixType* mt = dynamic_cast<MatrixType*>(item.object);
							define::matrix* m = dynamic_cast<define::matrix*>(item.object);
							GDMLProcessor::GetInstance()->AddMatrix(m->get_name(), *mt);
							calc->RegisterMatrix(m);
						} 
						else 
							std::cerr << "define SUBSCRIBER:: Incorrect content model found!\a" << std::endl;
					} 
					else if( define_element->get_content(idx)->type() == SAXObject::element ) {
                
						// Whoops, this should not happen as the only content of define element is 0 or more choices
						std::cerr << "define SUBSCRIBER:: Incorrect content model found!\a" << std::endl;
					}
				}
			}
		} 
		catch(...) {
			std::cerr << "GOT INTO BAD_CAST TROUBLE!" << std::endl;
		}
	}
}
};

DECLARE_SUBSCRIBER_FACTORY(defineSubscriber)
