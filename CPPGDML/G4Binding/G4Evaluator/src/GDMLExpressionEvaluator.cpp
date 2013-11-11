//
#include "G4Evaluator/GDMLExpressionEvaluator.h"
#include "CLHEP/Units/PhysicalConstants.h"
#include <string>
#include <vector>
#include <cstdlib>
#include <cctype>
#include <cstring>
#include <algorithm>

namespace CLHEP {}
using namespace CLHEP;

GDMLExpressionEvaluator::GDMLExpressionEvaluator()
{
  fCalc.clear();
  fCalc.setStdMath();                 // set standard constants and functions
  //fCalc.setSystemOfUnits();           // set SI units
  // Set Geant4 system of units
  fCalc.setSystemOfUnits(1.e+3, 1./1.60217733e-25, 1.e+9, 1./1.60217733e-10,1.0, 1.0, 1.0);
  fileCurrentlyParsed = "";
}

GDMLExpressionEvaluator::~GDMLExpressionEvaluator()
{
  fCTable.clear();
  fPCTable.clear();
  fCalc.clear();
}

//StatusCode GDMLExpressionEvaluator::RegisterConstant( const GDMLConstant* const c )
StatusCode GDMLExpressionEvaluator::RegisterConstant( const define::constant* const c )
{
  double value = EvaluateString( c->get_value() );

  if( fCalc.status() != HepTool::Evaluator::OK )
  {
    std::cerr << "Expression evaluator:: Error registering constant " << c->get_name() << std::endl;
    fCalc.print_error();
    std::cout << std::endl;
    return StatusCode::eError;
  }

#ifdef GDML_VERBOSE
  std::cout << "Expression evaluator:: Registering constant "
            << c->get_name() << ": " << value << std::endl;
#endif

  //RegisterVariable( c->get_name(), c->get_value() );
  RegisterVariable( c->get_name(), value );
  return StatusCode::eOk;
}
/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
StatusCode GDMLExpressionEvaluator::RegisterMatrix( const define::matrix* const m )
{  
  //std::cout << "Size: " << m->size() << " Coldim: "<< m->get_coldim() << std::endl;
  if(m->get_coldim()<=1)
  { 
   for(int i=1; i<=m->size(); i++)
   {
    double value = m->get_value(i);
    std::stringstream ss;
    std::string index;
    ss << i;
    ss >> index;
    std::string name = m->get_name()+"_"+index+"_";
    //std::cout << "setting variable: " << name << " with value: " << value << std::endl;
    RegisterVariable( name, value );       
   }
  }
  
  else
  {
   if((m->size())%(m->get_coldim())!=0)
   {
    std::cerr << "Expression evaluator:: Error registering matrix " << m->get_name() << " Matrix dimensions error" <<std::endl;
    return StatusCode::eError;
   } 
   for(int i=1; i<=((m->size())/(m->get_coldim())); i++)
   {
    for(int j=1; j<=m->get_coldim(); j++)
    {
     double value = m->get_value(i,j);
     std::stringstream ss;
     std::string index;
     ss << i;
     ss >> index;
     std::stringstream ssj;
     std::string jndex;
     ssj << j;
     ssj >> jndex;
     std::string name = m->get_name()+"_"+index+"_"+jndex+"_";
     //std::cout << "setting variable: " << name << " with value: " << value << std::endl;
     RegisterVariable( name, value );
    }
   }
  }
  return StatusCode::eOk;
}

StatusCode GDMLExpressionEvaluator::RegisterVariable( const std::string& var_name, double value)
{
 real_vars.push_back(var_name);
 std::string real_var_name = var_name + fileCurrentlyParsed;
 fCalc.setVariable( real_var_name.c_str(), value );
 return StatusCode::eOk;
}

bool GDMLExpressionEvaluator::is_real_variable(const std::string& var_name)
{
 
 std::vector<std::string>::iterator start = real_vars.begin();
 std::vector<std::string>::iterator end = real_vars.end();
 std::vector<std::string>::iterator iter;

 iter = find(start, end, var_name);
 
 if (iter == end)
 {
  return false;
 }
 else
 {
  return true;
 }
}

bool GDMLExpressionEvaluator::is_delimiter(char c)
{
 if(strchr(" ()|&=!><+-%*/^", c) || c==9 || c==0 || c=='\r' || c=='\n' || c=='\t' || c=='\0' || isspace(c)) return true;
 else return false;
}

double GDMLExpressionEvaluator::EvaluateString(const std::string& str)
{
 std::string str_mod = str;
 if(fileCurrentlyParsed != "")
 {
  const char* c_str_mod = str.c_str(); //string to be modified with file namespace! 
  std::vector<int> variable_ends;  //variable names to be changed
  int cur_variable_end = 0;
  while(*c_str_mod)
  {
   if(is_delimiter(*c_str_mod) || isdigit(*c_str_mod))
   {
    c_str_mod++;
    cur_variable_end++;
   }
   else if(isalpha(*c_str_mod))
   {
    char variable[80];
    char* token;
    token = variable;
    *token = '\0';
    while(!is_delimiter(*c_str_mod))
    {
     *token=*c_str_mod;
     token++;
     c_str_mod++;
     cur_variable_end++;
    }
    *token = '\0';
    std::string variable_to_check = variable;
    if(is_real_variable(variable_to_check))
    {
     variable_ends.push_back(cur_variable_end);
    }
   }
   else
   {
    c_str_mod++;
    cur_variable_end++;
   }
  }// variable ends stored in vector
  std::string::size_type shift = 0;
  std::string::size_type ns_length = fileCurrentlyParsed.size();
  for(unsigned int i=0; i<variable_ends.size(); i++)
  {
   str_mod.insert(shift+variable_ends[i],fileCurrentlyParsed);
   shift += ns_length;
  }
 }
 double result = fCalc.evaluate( str_mod.c_str() );
 return result;
}
/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/
/*********************************************************************************************************/

//StatusCode GDMLExpressionEvaluator::RegisterPhysConstant( const GDMLPhysicalConstant* const physc )
StatusCode GDMLExpressionEvaluator::RegisterPhysConstant( const define::quantity* const physc )
{
  std::string expr = physc->get_value();
  expr += "*(";
  expr += physc->get_unit();
  expr += ")";

  //std::cout << "Expression evaluator:: evaluating string: " << expr << std::endl;

  double value      = EvaluateString( expr );
  double unit_value = EvaluateString( physc->get_unit() );

  if( fCalc.status() != HepTool::Evaluator::OK )
  {
    std::cerr << "Expression evaluator:: Error registering quantity "
              << physc->get_name() << std::endl;
    fCalc.print_error();
    std::cout << std::endl;
    return StatusCode::eError;
  }

#ifdef GDML_VERBOSE
  std::cout << "Expression evaluator:: Registering quantity "
            << physc->get_name() << ": " << (value/unit_value) << physc->get_unit() << std::endl;
#endif

  //RegisterVariable( physc->get_name(), expr );
  RegisterVariable( physc->get_name(), value );
  return StatusCode::eOk;
}

//StatusCode GDMLExpressionEvaluator::RegisterExpression( const GDMLExpression* e )
StatusCode GDMLExpressionEvaluator::RegisterExpression( const define::expression* e )
{
  std::string expr = "(";
  expr += e->get_text();
  expr += ")";
  double value = EvaluateString( expr );

  if( fCalc.status() != HepTool::Evaluator::OK )
  {
    std::cerr << "Expression evaluator:: Error registering expression " << e->get_name() << std::endl;
    fCalc.print_error();
    std::cout << std::endl;
    return StatusCode::eError;
  }

#ifdef GDML_VERBOSE
  std::cout << "Expression evaluator:: Registering expression "
            << e->get_name() << ": " << value << std::endl;
#endif

  //RegisterVariable( e->get_name(), e->get_text() );
  RegisterVariable( e->get_name(), value );
  return StatusCode::eOk;
}

double GDMLExpressionEvaluator::Eval( const std::string& expr )
{
  return Eval( expr.c_str() );
}

double GDMLExpressionEvaluator::Eval( const char* expr_mod )
{
  
  std::string expr = expr_mod;
  std::string::size_type start_index = 0;
  std::string::size_type end_index = 0;
  while(true)
  {
   start_index = expr.find('[', start_index);   
   if(start_index == std::string::npos) break;
   std::string::size_type boundary_index = expr.find(']', start_index);
   expr.replace(start_index,1,1,'_');
   end_index = expr.find(',', start_index);
   if(end_index != std::string::npos && end_index < boundary_index)
   {
    start_index++;
    std::string var1 = expr.substr(start_index, end_index-start_index);
    double eval1 = EvaluateString( var1 );
    //std::cout<<"Evaluated "<<var1<<" to: "<<eval1<<std::endl;
    std::stringstream ss1;
    std::string str1;
    ss1 << eval1;
    ss1 >> str1;
    expr.replace(start_index, end_index-start_index, str1, 0, str1.size());
   }
   else
   {
    end_index = boundary_index;
    if(end_index != std::string::npos)
    {
     start_index++;
     std::string var1 = expr.substr(start_index, end_index-start_index);
     double eval1 = EvaluateString( var1 );
     //std::cout<<"Evaluated "<<var1<<" to: "<<eval1<<std::endl;
     std::stringstream ss1;
     std::string str1;
     ss1 << eval1;
     ss1 >> str1;
     expr.replace(start_index, end_index-start_index, str1, 0, str1.size());
    }
   }
  }
  start_index = 0;
  end_index = 0;
  while(true)
  {
   start_index = expr.find(',', start_index);
   if(start_index == std::string::npos) break;
   expr.replace(start_index,1,1,'_');
   end_index = expr.find(']', start_index);
   start_index++;
   std::string var2 = expr.substr(start_index, end_index-start_index);
   double eval2 = EvaluateString( var2 );
   //std::cout<<"Evaluated "<<var2<<" to: "<<eval2<<std::endl;
   std::stringstream ss2;
   std::string str2;
   ss2 << eval2;
   ss2 >> str2;
   expr.replace(start_index, end_index-start_index, str2, 0, str2.size());
  }
  start_index = 0;
  end_index = 0;
  while(true)
  {
   start_index = expr.find(']', start_index);
   if(start_index == std::string::npos) break;
   expr.replace(start_index,1,1,'_');
  }
    
  double result = EvaluateString( expr );
  if( fCalc.status() != HepTool::Evaluator::OK )
  {
    std::cerr << expr << std::endl;
    //std::cerr << "------";
    for (int i=0; i<fCalc.error_position(); i++)
    {
      std::cerr << "-";
    }
    std::cerr << "^\a" << std::endl;
    fCalc.print_error();
    std::cerr << std::endl;
  }
  return result;
}


