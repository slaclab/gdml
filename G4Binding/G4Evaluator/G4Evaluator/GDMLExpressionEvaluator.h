#ifndef GDML_EXPRESSION_EVALUATOR_H
#define GDML_EXPRESSION_EVALUATOR_H 1

#include "CLHEP/Evaluator/Evaluator.h"

#include "Saxana/StatusCode.h"

//#include "G4Processor/GDMLDefineTable.h"
#include "G4Evaluator/GDMLDefineTable.h"

#include "string"
#include <vector>

class GDMLExpressionEvaluator
{
public:
  GDMLExpressionEvaluator();
  ~GDMLExpressionEvaluator();

//   StatusCode RegisterConstant( const GDMLConstant* const c );
//   StatusCode RegisterPhysConstant( const GDMLPhysicalConstant* const physc );
//   StatusCode RegisterExpression( const GDMLExpression* e );
  StatusCode RegisterConstant( const define::constant* const c );
  StatusCode RegisterPhysConstant( const define::quantity* const physc );
  StatusCode RegisterExpression( const define::expression* e );
  StatusCode RegisterMatrix( const define::matrix* const m );
  StatusCode RegisterVariable( const std::string& var_name, double value);
  
  double EvaluateString(const std::string& str);
  bool is_delimiter(char c);
  bool is_real_variable(const std::string& var_name);
  double Eval( const std::string& expr );
  double Eval( const char* expr );
  
  void setFileCurrentlyParsed(std::string set)
  {
   fileCurrentlyParsed = set;
  }

private:
  HepTool::Evaluator     fCalc;
  ConstantsTable         fCTable;
  PhysicalConstantsTable fPCTable;
  std::string fileCurrentlyParsed;
  std::vector<std::string> real_vars;
};

#endif // GDML_EXPRESSION_EVALUATOR_H

