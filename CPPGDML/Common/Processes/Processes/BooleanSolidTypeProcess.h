// -*- C++ -*-
// $Id: BooleanSolidTypeProcess.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
// GEANT4 tag $Name: not supported by cvs2svn $
#ifndef GDML_PROCESS_BOOLEANSOLIDTYPEPROCESS_H
#define GDML_PROCESS_BOOLEANSOLIDTYPEPROCESS_H 1

#include "Processes/SolidTypeProcess.h"

#include "Schema/BooleanSolidType.h"

class BooleanSolidTypeProcess : public SolidTypeProcess
{
  public:
    BooleanSolidTypeProcess( const ProcessingContext* context = 0 )
      : SolidTypeProcess( context ) {
    }
  
    virtual ~BooleanSolidTypeProcess() {
    }
  
    /// Invoked whenever one of the daughter state processes has been popped-out of the state stack
    /// The name passed-in as the argument is the name of the XML element for which that's been done
    virtual void StackPopNotify( const std::string& name ) {
    
      SAXObject** so = Context()->GetTopObject();
      BooleanSolidType* bsobj = dynamic_cast<BooleanSolidType*>( m_obj );
    
      if( name == "first" || name == "second" ) {
        // Add the first and second elements into content model
        bsobj->add_content( name, *so );
      } else {
        // Add either choice of position or rotation elements and their references
        ContentChoice* choice        = new ContentChoice;
        ContentGroup::ContentItem ci = { name, *so };
        choice->set_content( ci );
        //std::cout << "BOOLEAN SOLID PROCESS adding choice " << name << std::endl;
        bsobj->add_content( "choice", choice );
      }
    
      SolidTypeProcess::StackPopNotify( name );
    }
};

#endif // GDML_PROCESS_BOOLEANSOLIDTYPEPROCESS_H
