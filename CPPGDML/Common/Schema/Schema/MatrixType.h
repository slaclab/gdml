#ifndef MATRIXTYPE_H
#define MATRIXTYPE_H 1

#include <string>
#include <vector>
#include <sstream>
#include <iostream>
#include <stdlib.h>

class MatrixType
{
 public:
  MatrixType()
  {
  }
  ~MatrixType()
  {
  }
  void set_name( const std::string& s )
  {
   name = s;
  }
  void set_unit( const char* s )
  {
   name = s;
  }
  std::string get_name() const
  {
   return name;
  }
  void set_coldim( const std::string& s )
  {
   coldim = atoi(s.c_str());
  }
  void set_coldim( const char* s )
  {
   coldim = atoi(s);
  }
  void set_coldim( int n )
  {
   coldim = n;
  }
  int get_coldim() const
  {
   return coldim;
  }
  void set_values( const std::string& s )
  {
   std::istringstream ss(s);
   while(!ss.eof())
   {
    double temp;
    ss >> temp;
    values.push_back(temp);
   }
  }
  void set_values( const char* ca )
  {
   std::string s = ca;
   set_values(s);
  }
  std::vector<double> get_values() const
  {
   return values;
  }
  double get_value(int i) const
  {
   unsigned int index = i-1;
   if(index<values.size())
   {
    return values[index];
   }
   else
   {
    std::cout << "Index Error" << std::endl;
    return 0;
   }
  }
  double get_value(int i, int j) const
  {
   if(coldim<=0)
   {
    std::cout << "Index Error" << std::endl;
    return 0;
   }
   unsigned int index = ((i-1)*coldim)+(j-1);
   if(index<values.size())
   {
    return values[index];
   }
   else
   {
    std::cout << "Index Error" << std::endl;
    return 0;
   }
  }
  std::string get_value_str(int i) const
  {
   unsigned int index = i-1;
   if(index<values.size())
   {
    std::stringstream ss;
    std::string str;
    ss << values[index];
    ss >> str;
    return str;
   }
   else
   {
    std::cout << "Index Error" << std::endl;
    return "";
   }
  }
  std::string get_value_str(int i, int j) const
  {
   if(coldim<=0)
   {
    std::cout << "Index Error" << std::endl;
    return "";
   }
   unsigned int index = ((i-1)*coldim)+(j-1);
   if(index<values.size())
   {
    std::stringstream ss;
    std::string str;
    ss << values[index];
    ss >> str;
    return str;
   }
   else
   {
    std::cout << "Index Error" << std::endl;
    return "";
   }
  }
  void print_values()
  {
   for(unsigned int i=0; i<values.size(); i++)
   {
    std::cout << values[i] << std::endl;
   }
  }
  int size() const
  {
   return values.size();
  }
 private:
  std::string name;
  int coldim;
  std::vector<double> values;
};



#endif // MATRIXTYPE_H
