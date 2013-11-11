//
#ifndef GDML_DEFINE_TABLE
#define GDML_DEFINE_TABLE 1

#include "Schema/define.h"

#include <map>

typedef std::map< std::string, define::constant >         ConstantsTable;
typedef std::map< std::string, define::quantity >         PhysicalConstantsTable;
typedef std::map< std::string, define::expression >       ExpressionsTable;
typedef std::map< std::string, define::position >         PositionsTable;
typedef std::map< std::string, define::rotation >         RotationsTable;
typedef std::map< std::string, define::matrix >           MatricesTable;

#endif // GDML_DEFINE_TABLE


