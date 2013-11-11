// $Id: Util.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef G4SUBSCRIBERS_GENNAME_H 
#define G4SUBSCRIBERS_GENNAME_H 1

// Include files
#include <iostream>

/** @class genName genName.h G4Subscribers/genName.h
 *  
 *
 *  @author Witold POKORSKI
 *  @date   2005-06-09
 */
class Util {
public: 
  /// Standard constructor
  Util( ){}; 

  virtual ~Util( ){}; ///< Destructor

  static std::string generateName(std::string name)
  {
    std::string::size_type i = name.find("0x");
    if ( i != std::string::npos) name.replace(i, 10, "");
    
    return name;
  }
};

#endif // G4SUBSCRIBERS_GENNAME_H
