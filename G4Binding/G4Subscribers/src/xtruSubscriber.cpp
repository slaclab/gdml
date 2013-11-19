#ifdef HAVE_G4EXTRUDEDSOLID

#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
//#include "G4Processor/GDMLExpressionEvaluator.h"
#include "G4Subscribers/Util.h"

#include "Schema/xtru.h"
#include "Schema/twoDimVertexType.h"
#include "Schema/sectionType.h"

#include "G4VSolid.hh"
#include "G4ExtrudedSolid.hh"
#include <iostream>

class xtruSubscriber : public SAXSubscriber {
public:
	virtual const SAXComponentObject* Build() const {
	
		return this;
	}

	xtruSubscriber() {
	
		Subscribe("xtru");
	}
	
	virtual ~xtruSubscriber() {}

	virtual void Activate( const SAXObject* object ) {
      
      		if( object != 0 ) {
        		try {
				const xtru* obj = dynamic_cast<const xtru*>(object);

				GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();

				std::string lunit = obj->get_lunit();
          			std::string aunit = obj->get_aunit();
	          		const std::string& name = obj->get_name();

				const ContentSequence* seq = obj->get_content();
				int SequenceSize = seq->size();  

				std::vector<G4TwoVector>  VertexList;
				std::vector<G4ExtrudedSolid::ZSection> ZSectionList;

				for (int i=0;i<SequenceSize;i++) {

					if (seq->content(i).tag=="twoDimVertex") {
						
						twoDimVertexType* GDML_vertex = dynamic_cast<twoDimVertexType*>(seq->content(i).object);
							
						G4double x = calc->Eval(GDML_vertex->get_x()+"*"+lunit);
						G4double y = calc->Eval(GDML_vertex->get_y()+"*"+lunit);

						G4TwoVector G4_vertex(x,y);
							
						VertexList.push_back(G4_vertex);
							
						continue;
					}
						
					if (seq->content(i).tag=="section") {
						
						sectionType* GDML_section = dynamic_cast<sectionType*>(seq->content(i).object);

						G4double zOrder = calc->Eval(GDML_section->get_zOrder()+"*"+lunit);	// Not used in Geant4!!!
						G4double zPosition = calc->Eval(GDML_section->get_zPosition()+"*"+lunit);
						G4double xOffset = calc->Eval(GDML_section->get_xOffset()+"*"+lunit);
						G4double yOffset = calc->Eval(GDML_section->get_yOffset()+"*"+lunit);
						G4double scalingFactor = calc->Eval(GDML_section->get_scalingFactor()); // Scaling factor is without dimension!!!

						G4TwoVector Offset(xOffset,yOffset);
						
						G4ExtrudedSolid::ZSection G4_section(zPosition,Offset,scalingFactor);						
						
						ZSectionList.push_back(G4_section);
							
						continue;
					}
				}
					
				G4VSolid *newobj = new G4ExtrudedSolid(Util::generateName(name),VertexList,ZSectionList);
				GDMLProcessor::GetInstance()->AddSolid(name,newobj); 
					
			}  catch(...) {
				
				std::cerr << "GOT INTO BAD_CAST TROUBLE!" << std::endl;
			}
		} else {
			
		std::cerr << "GOT ZERO DATA POINTER!" << std::endl;
		}
	}
};

DECLARE_SUBSCRIBER_FACTORY(xtruSubscriber)

#endif
