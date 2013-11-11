#include "Saxana/SAXSubscriber.h"
#include "Saxana/SAXSubscriberPool.h"
#include "Saxana/SAXComponentFactory.h"
#include "Saxana/SAXProcessor.h"

#include "Schema/loop.h"
#include "Schema/physvol.h"
#include "Schema/volume.h"
#include "Schema/SolidType.h"
#include "Schema/ContentGroup.h"

#include "G4Processor/GDMLProcessor.h"

#include "G4LogicalVolume.hh"

#include <iostream>
#include <sstream>
#include <string>
#include <utility>
#include <typeinfo>

class loopSubscriber : virtual public SAXSubscriber
{
 private:
  SAXSubscriberPool* fPool;
  
 public:
  virtual const SAXComponentObject* Build() const
  {
   return this;
  }

 public:
  loopSubscriber()
  {
   Subscribe( "loop" );
  }
  virtual ~loopSubscriber()
  {
  }

  virtual void Activate( const SAXObject* object )
  {
   fPool = new SAXSubscriberPool();
   fPool->Initialize();
   const loop* loop_element;
   if( object != 0 )
   {
    try
    {
     loop_element = dynamic_cast<const loop*>(object);
     run(loop_element);
    }
    catch(...)
    {
     std::cerr << "GOT INTO BAD_CAST TROUBLE!" << std::endl;
    }
   }
  }
  
  void run(const loop* loop_e)
  {
   loop* loop_el = const_cast<loop*>(loop_e);
   GDMLExpressionEvaluator* calc = GDMLProcessor::GetInstance()->GetEvaluator();
   std::string loop_variable = loop_el->get_var();
   unsigned int initial_loop_var_value = (unsigned int)(calc->Eval(loop_variable));
   if(!(loop_el->is_from_set()))
   {
    loop_el->set_from(initial_loop_var_value);
   }
   loop_el->reset();
   loop_el->next(); //this is done to prevent the first event of the loop to be duplicated!
   bool first_physvol_done = false;
   for (; !loop_el->is_finished(); loop_el->next())
   {
    calc->RegisterVariable( loop_el->get_var(), loop_el->get_current() );
    for (unsigned int i=0; i<loop_el->get_content_size(); i++)
    {     
     std::pair<std::string, SAXObject*> temp = loop_el->get_object(i);
     std::string temp_tag = temp.first;
     SAXObject * temp_so = temp.second;
     if(temp_tag=="volume")
     {
      volume* vol = dynamic_cast<volume*>(temp_so);
      std::stringstream ss;
      std::string str;
      ss << loop_el->get_current_step();
      ss >> str;
      std::string vol_name = vol->get_name();
      std::string::size_type loc = vol_name.find_last_of('_');
      vol_name = vol_name.substr(0,loc);
      vol->set_name(vol_name+"_"+str);

      VolumeType::solidref* sol_ref = dynamic_cast<VolumeType::solidref*> (vol->get_sol_ref());
      std::string sol_refName = sol_ref->get_ref();
      std::string::size_type loc2 = sol_refName.find_last_of('_');
      sol_refName = sol_refName.substr(0,loc2);
      sol_ref->set_ref(sol_refName+"_"+str); 

      const SAXSubscriberPool::Subscribers* actors = fPool->GetSubscribers( temp_tag );

      if( actors != 0 )
      {
       SAXSubscriberPool::Subscribers::const_iterator subscriberRef;
       for( subscriberRef = actors->begin(); subscriberRef != actors->end(); subscriberRef++ )
       {
        if( (*subscriberRef)->GetSubscriptions()->size() == 1 )
        {
	 GDMLProcessor* temp = GDMLProcessor::GetInstance();
	 temp->AddLoopNum(str);
         (*subscriberRef)->Activate( temp_so );	     
	 temp->AddLoopNum("0");
        }
       } 
       delete actors;
      }
     }
     else if(temp_tag=="physvol")
     {
      //TODOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOOO
      if(!first_physvol_done)
      {
       calc->RegisterVariable( loop_el->get_var(), initial_loop_var_value );
       physvol* ph_vol_pointer = dynamic_cast<physvol*>(temp_so);
       physvol* ph_vol_new = new physvol;
       ContentSequence* contents = const_cast<ContentSequence*>(ph_vol_pointer->get_content());
       for (unsigned int ii=0; ii<contents->size(); ii++)
       {
        ContentGroup::ContentItem temp_item = contents->content(ii);
        if(temp_item.tag=="file")
        {
         SinglePlacementType::file* p = dynamic_cast<SinglePlacementType::file*>(temp_item.object);
	 std::string name = p->get_name();
	 std::string vol_name = p->get_volname();
	 SinglePlacementType::file* to_add = new SinglePlacementType::file;
	 to_add->set_name(name);
	 to_add->set_volname(vol_name);
	 ph_vol_new->add_content( temp_item.tag, to_add );
        }
        else if(temp_item.tag=="volumeref")
        {
         SinglePlacementType::volumeref* p = dynamic_cast<SinglePlacementType::volumeref*>(temp_item.object);
	 std::string ref = p->get_ref();
	 SinglePlacementType::volumeref* to_add = new SinglePlacementType::volumeref;
	 to_add->set_ref(ref);
 	 ph_vol_new->add_content( temp_item.tag, to_add );
        }
        else if(temp_item.tag=="positionref")
        {
         SinglePlacementType::positionref* p = dynamic_cast<SinglePlacementType::positionref*>(temp_item.object);
	 std::string ref = p->get_ref();
	 SinglePlacementType::positionref* to_add = new SinglePlacementType::positionref;
	 to_add->set_ref(ref);
	 ph_vol_new->add_content( temp_item.tag, to_add );
        }
        else if(temp_item.tag=="position")
        {
	 double x_val;
	 double y_val;
	 double z_val;
 	 SinglePlacementType::position* p = dynamic_cast<SinglePlacementType::position*>(temp_item.object);
	 std::string name = p->get_name();
	 std::string unit = p->get_unit();
	 std::string type = p->get_type();
	
	 std::string x = p->get_x();
	 x_val = calc->Eval(x);
	 std::stringstream ss_x;
         std::string str_x;
         ss_x << x_val;
         ss_x >> str_x;
	 x = str_x;
	 
	 std::string y = p->get_y();
	 y_val = calc->Eval(y);
	 std::stringstream ss_y;
         std::string str_y;
         ss_y << y_val;
         ss_y >> str_y;
	 y = str_y;
	 
	 std::string z = p->get_z();
	 z_val = calc->Eval(z);
	 std::stringstream ss_z;
         std::string str_z;
         ss_z << z_val;
         ss_z >> str_z;
	 z = str_z;
	 
	 SinglePlacementType::position* to_add = new SinglePlacementType::position;
	 to_add->set_name(name);
	 to_add->set_unit(unit);
	 to_add->set_type(type);
	 to_add->set_x(x);
	 to_add->set_y(y);
	 to_add->set_z(z);
	 ph_vol_new->add_content( temp_item.tag, to_add );
        }
        else if(temp_item.tag=="rotation")
        {
         double x_val;
	 double y_val;
	 double z_val;
	 SinglePlacementType::rotation* p = dynamic_cast<SinglePlacementType::rotation*>(temp_item.object);
	 std::string name = p->get_name();
	 std::string unit = p->get_unit();
	 std::string type = p->get_type();
	
	 std::string x = p->get_x();
	 x_val = calc->Eval(x);
	 std::stringstream ss_x;
         std::string str_x;
         ss_x << x_val;
         ss_x >> str_x;
	 x = str_x;
	 
	 std::string y = p->get_y();
	 y_val = calc->Eval(y);
	 std::stringstream ss_y;
         std::string str_y;
         ss_y << y_val;
         ss_y >> str_y;
	 y = str_y;
	 
	 std::string z = p->get_z();
	 z_val = calc->Eval(z);
	 std::stringstream ss_z;
         std::string str_z;
         ss_z << z_val;
         ss_z >> str_z;
	 z = str_z;
	 
	 SinglePlacementType::rotation* to_add = new SinglePlacementType::rotation;
	 to_add->set_name(name);
	 to_add->set_unit(unit);
	 to_add->set_type(type);
	 to_add->set_x(x);
	 to_add->set_y(y);
	 to_add->set_z(z);
	 ph_vol_new->add_content( temp_item.tag, to_add );
        }
        else if(temp_item.tag=="rotationref")
        {
         SinglePlacementType::rotationref* p = dynamic_cast<SinglePlacementType::rotationref*>(temp_item.object);
	 std::string ref = p->get_ref();
	 SinglePlacementType::rotationref* to_add = new SinglePlacementType::rotationref;
	 to_add->set_ref(ref);
 	 ph_vol_new->add_content( temp_item.tag, to_add );
        }
        else if(temp_item.tag=="choice")
        {
         ContentChoice* p = dynamic_cast<ContentChoice*>(temp_item.object);
	 ContentChoice* choice_to_add = new ContentChoice;
	 ContentGroup::ContentItem choice_content = p->content();
	 ContentGroup::ContentItem choice_content_to_add;	
	 if(choice_content.tag=="position")
         {
	  double x_val;
	  double y_val;
	  double z_val;
	  define::position* p = dynamic_cast<define::position*>(choice_content.object);
	  std::string name = p->get_name();
	  std::string unit = p->get_unit();
	  std::string type = p->get_type();
	 
	  std::string x = p->get_x();
	  x_val = calc->Eval(x);
	  std::stringstream ss_x;
          std::string str_x;
          ss_x << x_val;
          ss_x >> str_x;
	  x = str_x;
	 
	  std::string y = p->get_y();
	  y_val = calc->Eval(y);
	  std::stringstream ss_y;
          std::string str_y;
          ss_y << y_val;
          ss_y >> str_y;
	  y = str_y;
	 
	  std::string z = p->get_z();
	  z_val = calc->Eval(z);
	  std::stringstream ss_z;
          std::string str_z;
          ss_z << z_val;
          ss_z >> str_z;
	  z = str_z;
	 
	  define::position* to_add = new define::position;
	  to_add->set_name(name);
	  to_add->set_unit(unit);
	  to_add->set_type(type);
	  to_add->set_x(x);
	  to_add->set_y(y);
	  to_add->set_z(z);
	  choice_content_to_add.tag=choice_content.tag;
	  choice_content_to_add.object=to_add;
	  choice_to_add->set_content(choice_content_to_add);
	  ph_vol_new->add_content( temp_item.tag, choice_to_add );
         }
         else if(choice_content.tag=="rotation")
         {
          double x_val;
	  double y_val;
	  double z_val;
	  define::rotation* p = dynamic_cast<define::rotation*>(choice_content.object);
 	  std::string name = p->get_name();
 	  std::string unit = p->get_unit();
	  std::string type = p->get_type();
	 
	  std::string x = p->get_x();
	  x_val = calc->Eval(x);
	  std::stringstream ss_x;
          std::string str_x;
          ss_x << x_val;
          ss_x >> str_x;
	  x = str_x;
	 
	  std::string y = p->get_y();
	  y_val = calc->Eval(y);
	  std::stringstream ss_y;
          std::string str_y;
          ss_y << y_val;
          ss_y >> str_y;
	  y = str_y;
	 
	  std::string z = p->get_z();
	  z_val = calc->Eval(z);
	  std::stringstream ss_z;
          std::string str_z;
          ss_z << z_val;
          ss_z >> str_z;
	  z = str_z;
	 
	  define::rotation* to_add = new define::rotation;
	  to_add->set_name(name);
 	  to_add->set_unit(unit);
	  to_add->set_type(type);
	  to_add->set_x(x);
	  to_add->set_y(y);
	  to_add->set_z(z);
	  choice_content_to_add.tag=choice_content.tag;
	  choice_content_to_add.object=to_add;
	  choice_to_add->set_content(choice_content_to_add);
	  ph_vol_new->add_content( temp_item.tag, choice_to_add );
         }
  	 else
         {
          std::cout<<"Unknown TAG! "<< choice_content.tag << " of type: " << typeid(*(choice_content.object)).name() <<std::endl;
         }	
        }
        else
        {
         std::cout<<"Unknown TAG! "<< temp_item.tag << " of type: " << typeid(*(temp_item.object)).name() <<std::endl;
        }
       }
       SinglePlacementType::volumeref* vol_ref = dynamic_cast<SinglePlacementType::volumeref*>(ph_vol_new->get_vol_ref());
       std::string vol_refName = vol_ref->get_ref();
       std::string::size_type loc2 = vol_refName.find_last_of('_');
       vol_refName = vol_refName.substr(0,loc2);
       vol_ref->set_ref(vol_refName);
       //this command above is the one that sets the final physvol name OF THE FIRST ONE
       ph_vol_new->set_vol_ref(vol_ref);
       loop_el->add_to_physvols( ph_vol_new );
      
       first_physvol_done = true;
      }//FIRST PHYSVOL!!!

      calc->RegisterVariable( loop_el->get_var(), loop_el->get_current() );
      physvol* ph_vol_pointer = dynamic_cast<physvol*>(temp_so);
      physvol* ph_vol_new = new physvol;
      ContentSequence* contents = const_cast<ContentSequence*>(ph_vol_pointer->get_content());
      for (unsigned int ii=0; ii<contents->size(); ii++)
      {
       ContentGroup::ContentItem temp_item = contents->content(ii);
       if(temp_item.tag=="file")
       {
        SinglePlacementType::file* p = dynamic_cast<SinglePlacementType::file*>(temp_item.object);
	std::string name = p->get_name();
	std::string vol_name = p->get_volname();
	SinglePlacementType::file* to_add = new SinglePlacementType::file;
	to_add->set_name(name);
	to_add->set_volname(vol_name);
	ph_vol_new->add_content( temp_item.tag, to_add );
       }
       else if(temp_item.tag=="volumeref")
       {
        SinglePlacementType::volumeref* p = dynamic_cast<SinglePlacementType::volumeref*>(temp_item.object);
	std::string ref = p->get_ref();
	SinglePlacementType::volumeref* to_add = new SinglePlacementType::volumeref;
	to_add->set_ref(ref);
	ph_vol_new->add_content( temp_item.tag, to_add );
       }
       else if(temp_item.tag=="positionref")
       {
        SinglePlacementType::positionref* p = dynamic_cast<SinglePlacementType::positionref*>(temp_item.object);
	std::string ref = p->get_ref();
	SinglePlacementType::positionref* to_add = new SinglePlacementType::positionref;
	to_add->set_ref(ref);
	ph_vol_new->add_content( temp_item.tag, to_add );
       }
       else if(temp_item.tag=="position")
       {
	double x_val;
	double y_val;
	double z_val;
	SinglePlacementType::position* p = dynamic_cast<SinglePlacementType::position*>(temp_item.object);
	std::string name = p->get_name();
	std::string unit = p->get_unit();
	std::string type = p->get_type();
	
	std::string x = p->get_x();
	x_val = calc->Eval(x);
	std::stringstream ss_x;
        std::string str_x;
        ss_x << x_val;
        ss_x >> str_x;
	x = str_x;
	 
	std::string y = p->get_y();
	y_val = calc->Eval(y);
	std::stringstream ss_y;
        std::string str_y;
        ss_y << y_val;
        ss_y >> str_y;
	y = str_y;
	 
	std::string z = p->get_z();
	z_val = calc->Eval(z);
	std::stringstream ss_z;
        std::string str_z;
        ss_z << z_val;
        ss_z >> str_z;
	z = str_z;
	 
	SinglePlacementType::position* to_add = new SinglePlacementType::position;
	to_add->set_name(name);
	to_add->set_unit(unit);
	to_add->set_type(type);
	to_add->set_x(x);
	to_add->set_y(y);
	to_add->set_z(z);
	ph_vol_new->add_content( temp_item.tag, to_add );
       }
       else if(temp_item.tag=="rotation")
       {
        double x_val;
	double y_val;
	double z_val;
	SinglePlacementType::rotation* p = dynamic_cast<SinglePlacementType::rotation*>(temp_item.object);
	std::string name = p->get_name();
	std::string unit = p->get_unit();
	std::string type = p->get_type();
	
	std::string x = p->get_x();
	x_val = calc->Eval(x);
	std::stringstream ss_x;
        std::string str_x;
        ss_x << x_val;
        ss_x >> str_x;
	x = str_x;
	 
	std::string y = p->get_y();
	y_val = calc->Eval(y);
	std::stringstream ss_y;
        std::string str_y;
        ss_y << y_val;
        ss_y >> str_y;
	y = str_y;
	 
	std::string z = p->get_z();
	z_val = calc->Eval(z);
	std::stringstream ss_z;
        std::string str_z;
        ss_z << z_val;
        ss_z >> str_z;
	z = str_z;
	 
	SinglePlacementType::rotation* to_add = new SinglePlacementType::rotation;
	to_add->set_name(name);
	to_add->set_unit(unit);
	to_add->set_type(type);
	to_add->set_x(x);
	to_add->set_y(y);
	to_add->set_z(z);
	ph_vol_new->add_content( temp_item.tag, to_add );
       }
       else if(temp_item.tag=="rotationref")
       {
        SinglePlacementType::rotationref* p = dynamic_cast<SinglePlacementType::rotationref*>(temp_item.object);
	std::string ref = p->get_ref();
	SinglePlacementType::rotationref* to_add = new SinglePlacementType::rotationref;
	to_add->set_ref(ref);
	ph_vol_new->add_content( temp_item.tag, to_add );
       }
       else if(temp_item.tag=="choice")
       {
        ContentChoice* p = dynamic_cast<ContentChoice*>(temp_item.object);
	ContentChoice* choice_to_add = new ContentChoice;
	ContentGroup::ContentItem choice_content = p->content();
	ContentGroup::ContentItem choice_content_to_add;	
	if(choice_content.tag=="position")
        {
	 double x_val;
	 double y_val;
	 double z_val;
	 define::position* p = dynamic_cast<define::position*>(choice_content.object);
	 std::string name = p->get_name();
	 std::string unit = p->get_unit();
	 std::string type = p->get_type();
	 
	 std::string x = p->get_x();
	 x_val = calc->Eval(x);
	 std::stringstream ss_x;
         std::string str_x;
         ss_x << x_val;
         ss_x >> str_x;
	 x = str_x;
	 
	 std::string y = p->get_y();
	 y_val = calc->Eval(y);
	 std::stringstream ss_y;
         std::string str_y;
         ss_y << y_val;
         ss_y >> str_y;
	 y = str_y;
	 
	 std::string z = p->get_z();
	 z_val = calc->Eval(z);
	 std::stringstream ss_z;
         std::string str_z;
         ss_z << z_val;
         ss_z >> str_z;
	 z = str_z;
	 
	 define::position* to_add = new define::position;
	 to_add->set_name(name);
	 to_add->set_unit(unit);
	 to_add->set_type(type);
	 to_add->set_x(x);
	 to_add->set_y(y);
	 to_add->set_z(z);
	 choice_content_to_add.tag=choice_content.tag;
	 choice_content_to_add.object=to_add;
	 choice_to_add->set_content(choice_content_to_add);
	 ph_vol_new->add_content( temp_item.tag, choice_to_add );
        }
        else if(choice_content.tag=="rotation")
        {
         double x_val;
	 double y_val;
	 double z_val;
	 define::rotation* p = dynamic_cast<define::rotation*>(choice_content.object);
 	 std::string name = p->get_name();
 	 std::string unit = p->get_unit();
	 std::string type = p->get_type();
	 
	 std::string x = p->get_x();
	 x_val = calc->Eval(x);
	 std::stringstream ss_x;
         std::string str_x;
         ss_x << x_val;
         ss_x >> str_x;
	 x = str_x;
	 
	 std::string y = p->get_y();
	 y_val = calc->Eval(y);
	 std::stringstream ss_y;
         std::string str_y;
         ss_y << y_val;
         ss_y >> str_y;
	 y = str_y;
	 
	 std::string z = p->get_z();
	 z_val = calc->Eval(z);
	 std::stringstream ss_z;
         std::string str_z;
         ss_z << z_val;
         ss_z >> str_z;
	 z = str_z;
	 
	 define::rotation* to_add = new define::rotation;
	 to_add->set_name(name);
 	 to_add->set_unit(unit);
	 to_add->set_type(type);
	 to_add->set_x(x);
	 to_add->set_y(y);
	 to_add->set_z(z);
	 choice_content_to_add.tag=choice_content.tag;
	 choice_content_to_add.object=to_add;
	 choice_to_add->set_content(choice_content_to_add);
	 ph_vol_new->add_content( temp_item.tag, choice_to_add );
        }
	else
        {
         std::cout<<"Unknown TAG! "<< choice_content.tag << " of type: " << typeid(*(choice_content.object)).name() <<std::endl;
        }	
       }
       else
       {
        std::cout<<"Unknown TAG! "<< temp_item.tag << " of type: " << typeid(*(temp_item.object)).name() <<std::endl;
       }
      }
      SinglePlacementType::volumeref* vol_ref = dynamic_cast<SinglePlacementType::volumeref*>(ph_vol_new->get_vol_ref());
      std::string vol_refName = vol_ref->get_ref();
      std::string::size_type loc2 = vol_refName.find_last_of('_');
      vol_refName = vol_refName.substr(0,loc2);
      std::stringstream ss;
      std::string str;
      ss << loop_el->get_current_step();
      ss >> str;

      //PHYSVOL NAME USED HERE
      GDMLProcessor* processor = GDMLProcessor::GetInstance();
      G4LogicalVolume* plog = 0;      
      plog = const_cast<G4LogicalVolume*>(processor->GetLogicalVolume(vol_refName+"_"+str));
      
      //CHECK TO SEE IF THE VOLUME EXISTS, IF IT DOESNT - USE THE UN-APPENDED VOLUME NAME

      if(plog != 0)
	{
	  vol_ref->set_ref(vol_refName+"_"+str);
	}
      else
	{
	  vol_ref->set_ref(vol_refName);
	}

      ph_vol_new->set_vol_ref(vol_ref);
      loop_el->add_to_physvols( ph_vol_new );
     }
     else //temp_tag=="solid"
     {
      SolidType* solid = dynamic_cast<SolidType*>(temp_so);
      std::stringstream ss;
      std::string str;
      ss << loop_el->get_current_step();
      ss >> str;
      std::string solid_name = solid->get_name();
      std::string::size_type loc = solid_name.find_last_of('_');
      solid_name = solid_name.substr(0,loc);
      solid->set_name(solid_name+"_"+str);
      const SAXSubscriberPool::Subscribers* actors = fPool->GetSubscribers( temp_tag );
      if( actors != 0 )
      {
       SAXSubscriberPool::Subscribers::const_iterator subscriberRef;
       for( subscriberRef = actors->begin(); subscriberRef != actors->end(); subscriberRef++ )
       {
        if( (*subscriberRef)->GetSubscriptions()->size() == 1 )
        {
         (*subscriberRef)->Activate( temp_so );	      	      
        }
       } 
       delete actors;
      }
     }
    }
   }
  }
};

DECLARE_SUBSCRIBER_FACTORY(loopSubscriber)

  
