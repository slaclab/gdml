//
#ifndef LOOP_H
#define LOOP_H 1

#include <string>
#include <vector>
#include <utility>
#include <sstream>
#include <iostream>
#include <stdlib.h>

#include "Saxana/SAXObject.h"
#include "physvol.h"

class loop : public SAXObject
{
 public:
  loop() 
  {
   finished=false;
   current_step=0;
   from_set=false;
  }
  ~loop()
  {
  } 
  virtual SAXObject::Type type()
  {
   return SAXObject::element;
  }
  bool is_from_set()
  {
   return from_set;
  }
  void set_var( const std::string& set )
  {
   var = set;
  }
  void set_var( const char* s )
  {
   var = s;
  }  
  const std::string& get_var() const
  {
   return var;
  } 
  void set_from( const std::string& s )
  {
   if(!from_set)
   {
    from = atoi(s.c_str());
    current = from;
    from_set = true;
   }
  }
  void set_from( const char* s )
  {
   if(!from_set)
   {
    from = atoi(s);
    current = from;
    from_set = true;
   }
  }
  void set_from( unsigned int n )
  {
   if(!from_set)
   {
    from = n;
    current = from;
    from_set = true;
   }
  }
  unsigned int get_from() const
  {
   return from;
  }
  unsigned int get_current() const
  {
   return current;
  }
  unsigned int get_current_step() const
  {
   return current_step;
  }
  void reset()
  {
   current = from;
   current_step = 0;
  }
  void next()
  {
   if(finished==false && current+step<=to)
   {
    current = current+step;
    current_step++;
    return;
   }
   else if(finished==false && current+step>to)
   {
    finished=true;
    return;
   }
   else //finished == true
   {
    return;
   }
  }
  bool is_finished() const
  {
   return finished;
  }
  void set_to( const std::string& s )
  {
   to = atoi(s.c_str());
  }
  void set_to( const char* s )
  {
   to = atoi(s);
  }
  void set_to( unsigned int n )
  {
   to = n;
  }
  unsigned int get_to() const
  {
   return to;
  }
  void set_step( const std::string& s )
  {
   step = atoi(s.c_str());
  }
  void set_step( const char* s )
  {
   step = atoi(s);
  }
  void set_step( unsigned int n )
  {
   step = n;
  }
  unsigned int get_step() const
  {
   return step;
  }
  void add_to_content( std::string tag, SAXObject*& so )
  {   
   content.push_back( std::make_pair(tag,so) );
  }
  void add_to_physvols( SAXObject* so )
  {   
   physvols.push_back( so );
  }
  SAXObject* get_physvol(unsigned int i) const
  {
   return physvols[i];
  }
  void print_physvol_names()
  {
   for(unsigned int i=0; i<physvols.size(); i++)
   {
    physvol* temp = (physvol*)physvols[i];
    SinglePlacementType::volumeref* vol_ref = dynamic_cast<SinglePlacementType::volumeref*>(temp->get_vol_ref());
    std::cout<<"NAME ("<<i<<"): "<<vol_ref->get_ref()<<std::endl;
   }
  }
  unsigned int get_physvols_size() const
  {
   return physvols.size();
  }
  unsigned int get_content_size() const
  {
   return content.size();
  }
  const std::pair<std::string, SAXObject*> & get_object(unsigned int i) const
  {
   return content[i];
  }
 private:
  std::string var;
  unsigned int from;
  unsigned int to;
  unsigned int step;
  std::vector<std::pair<std::string, SAXObject*> > content;
  std::vector<SAXObject*> physvols;
  unsigned int current;
  unsigned int current_step;
  bool finished;
  bool from_set; 
};

#endif // LOOP_H
