//

#ifdef HAVE_G4TESSELLATEDSOLID

#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXComponentFactory.h"

#include "G4Processor/GDMLProcessor.h"
#include "G4Subscribers/Util.h"

#include "Schema/tessellated.h"
#include "Schema/triangular.h"
#include "Schema/quadrangular.h"

#include "G4VSolid.hh"
#include "G4TessellatedSolid.hh"
#include "G4TriangularFacet.hh"
#include "G4QuadrangularFacet.hh"

#include <iostream>

class tessellatedSubscriber : public SAXSubscriber {
public:
	tessellatedSubscriber() { Subscribe( "tessellated" ); }
	virtual ~tessellatedSubscriber() {}

	virtual const SAXComponentObject* Build() const { return this; }

// The activation callback invoked by SAXG4Processor whenever it has
// a new object created from XML and a corresponding subcriber exists

virtual void Activate( const SAXObject* object ) {

	if( object != 0 ) {
		
		try {
          
			const tessellated* obj = dynamic_cast<const tessellated*>( object );
            
			const std::string& name = obj->get_name();
			std::string sval;        
          
			const ContentSequence* seq = obj->get_content();
          
			G4VSolid* newobj = new G4TessellatedSolid(Util::generateName(name));
			GDMLProcessor* processor = GDMLProcessor::GetInstance();

			// add faces
			int numberOfFaces = seq->size();          
          
			for(int i=0;(i<numberOfFaces);i++) {
				
				G4VFacet* facet=0;
				G4FacetVertexType type = ABSOLUTE;
            
				// TRIANGULAR FACE	    
				if(seq->content(i).tag=="triangular") {

					triangular* face=dynamic_cast<triangular*>(seq->content(i).object);

					if(face->get_type()=="ABSOLUTE") type = ABSOLUTE;
					else if(face->get_type()=="RELATIVE") type = RELATIVE;
              
					const G4ThreeVector* pVertex1 = (G4ThreeVector*)(processor->GetPosition(face->get_vertex1()));
					const G4ThreeVector* pVertex2 = (G4ThreeVector*)(processor->GetPosition(face->get_vertex2()));
					const G4ThreeVector* pVertex3 = (G4ThreeVector*)(processor->GetPosition(face->get_vertex3()));

					if (pVertex1==0) {
					
						std::cout << "ERROR! Vertex '" << face->get_vertex1() << "' is not defined in '" << name << "'!" << std::endl;
						return;
					}

					if (pVertex2==0) {
					
						std::cout << "ERROR! Vertex '" << face->get_vertex2() << "' is not defined in '" << name << "'!" << std::endl;
						return;
					}

					if (pVertex3==0) {
					
						std::cout << "ERROR! Vertex '" << face->get_vertex3() << "' is not defined in '" << name << "'!" << std::endl;
						return;
					}

					facet = new G4TriangularFacet(*pVertex1,*pVertex2,*pVertex3,type);
				}

				// QUADRANGULAR FACE				
				else if(seq->content(i).tag=="quadrangular") {

					quadrangular* face=dynamic_cast<quadrangular*>(seq->content(i).object);

					if(face->get_type()=="ABSOLUTE") type = ABSOLUTE;
					else if(face->get_type()=="RELATIVE") type = RELATIVE;

					const G4ThreeVector* pVertex1 = (G4ThreeVector*)(processor->GetPosition(face->get_vertex1()));
					const G4ThreeVector* pVertex2 = (G4ThreeVector*)(processor->GetPosition(face->get_vertex2()));
					const G4ThreeVector* pVertex3 = (G4ThreeVector*)(processor->GetPosition(face->get_vertex3()));
					const G4ThreeVector* pVertex4 = (G4ThreeVector*)(processor->GetPosition(face->get_vertex4()));

					if (pVertex1==0) {
					
						std::cout << "ERROR! Vertex '" << face->get_vertex1() << "' is not defined in '" << name << "'!" << std::endl;
						return;
					}

					if (pVertex2==0) {
					
						std::cout << "ERROR! Vertex '" << face->get_vertex2() << "' is not defined in '" << name << "'!" << std::endl;
						return;
					}

					if (pVertex3==0) {
					
						std::cout << "ERROR! Vertex '" << face->get_vertex3() << "' is not defined in '" << name << "'!" << std::endl;
						return;
					}


					if (pVertex4==0) {
					
						std::cout << "ERROR! Vertex '" << face->get_vertex4() << "' is not defined in '" << name << "'!" << std::endl;
						return;
					}

   					facet = new G4QuadrangularFacet(*pVertex1,*pVertex2,*pVertex3,*pVertex4,type);
				}

				((G4TessellatedSolid*)newobj)->AddFacet(facet);
			}

				((G4TessellatedSolid*)newobj)->SetSolidClosed(true);
//				((G4TessellatedSolid*)newobj)->DumpInfo();
				processor->AddSolid(name,newobj);      
		} catch(...) {
		
			std::cerr << "GOT INTO BAD_CAST TROUBLE!" << std::endl;
        	}
	} else {
       
		std::cerr << "GOT ZERO DATA POINTER!" << std::endl;
	}
}
};

DECLARE_SUBSCRIBER_FACTORY(tessellatedSubscriber)

#endif

