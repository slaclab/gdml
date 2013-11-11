// $Id: Utils.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef WRITERG4_UTILS_H 
#define WRITERG4_UTILS_H 1

// Include files
#include <iostream>
#include <sstream>
#include <map>
#include <vector>

#include "G4LogicalVolume.hh"
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4VSolid.hh"


/** @class Utils Utils.h WriterG4/Utils.h
 *  
 *
 *  @author Witold POKORSKI
 *  @date   2004-10-18
 */

class Utils 
{
private:
  std::map<std::string, const G4Element*> elements;
  std::map<std::string, const G4Material*> materials;
  std::map<std::string, const G4VSolid*> solids;
  std::map<std::string, const G4VPhysicalVolume*> pvolumes;
  std::map<std::string, const G4LogicalVolume*> lvolumes;
  
  int nameFormat;

  int elenumb;
  std::string elename;
  int matnumb;
  std::string matname;
  int solnumb;
  std::string solname;
  int pvolnumb;
  std::string pvolname;
  int lvolnumb;
  std::string lvolname;

public:

  Utils(int format = 0) 
  {
   if(format == 0 || format == 1 || format == 2)
   /*
     NAME SUFFIX:
   
     0: Hexadecimal addresses (stripping - POSSIBLY UNSAFE);
     1: Long addresses (no stripping - SAFE);
     2: No suffix (no stripping - VERY UNSAFE);
     
     DEFAULT: 0
   */
   {
    nameFormat = format;
   }
   else nameFormat = 0;
  }
  ~Utils() {};
  
  // The method below is to filter out some bad characters or redundant bits of the names coming from 
  // the G4 objects. 
  // TODO: make it configurable, so users can provide it with characters or strings 'to be filtered out'

  std::string filter(const std::string& name)
  {
    std::string cname(name);  
    std::string::size_type p=cname.find('/');
  
    while(p!=std::string::npos)
      {
	cname.replace(p,1,"");
	p=cname.find('/',p);
      }
  
    p=cname.find(" ");
  
    while(p!=std::string::npos)
      {
	cname.replace(p,1,"");
	p=cname.find(" ",p);
      }

    p=cname.find("+");
  
    while(p!=std::string::npos)
      {
	cname.replace(p,1,"");
	p=cname.find("+",p);
      }

    p=cname.find("-");
  
    while(p!=std::string::npos)
      {
	cname.replace(p,1,"");
	p=cname.find("-",p);
      }

    p=cname.find(":");
  
    while(p!=std::string::npos)
      {
	cname.replace(p,1,"");
	p=cname.find(":",p);
      }

    p=cname.find("#");
  
    while(p!=std::string::npos)
      {
	cname.replace(p,1,"");
	p=cname.find("#",p);
      }

    p=cname.find("ddGeometry");
    if (p!=std::string::npos) cname.replace(p,10,"");

    p=cname.find("ddMaterials");
    if (p!=std::string::npos) cname.replace(p,10,"");

    p=cname.find("ddStructureLHCb");
    if (p!=std::string::npos) cname.replace(p,10,"");

    return cname;
  }
  //  
  std::string name(const G4Element* ptr/*, std::string oname=""*/)
  {
    elename = ptr->GetName();
    elename = filter(elename);
    std::ostringstream os;
    if(nameFormat == 0)
    {
     os << ptr;
    }
    else if (nameFormat == 1)
    {
     os << "_" << (long int)ptr;
    }
    else if (nameFormat == 2)
    {
     os << "";
    }
    std::string ssn = os.str();
     
    return elename+ssn;

    /*
    if(oname=="")
      {  
	elename = ptr->GetName();
	elename = filter(elename);
	oname = elename;
	elenumb = 0;
      }
      
    if (elements.find(oname) == elements.end())
      elements[oname] = ptr;
    else if (elements[oname] != ptr)
      {
	std::ostringstream os;

	elenumb++;

	os << elenumb;      
	std::string sen = os.str();
	oname = elename+sen;
	oname = name(ptr,oname);
      }
    return oname;
    */
  };
  
  std::string name(const G4Material* ptr/*, std::string oname=""*/)
  {
    matname = ptr->GetName();
    matname = filter(matname);
    std::ostringstream os;
    if(nameFormat == 0)
    {
     os << ptr;
    }
    else if (nameFormat == 1)
    {
     os << "_" << (long int)ptr;
    }
    else if (nameFormat == 2)
    {
     os << "";
    }
    std::string ssn = os.str();
     
    return matname+ssn;

    /*
    if(oname=="")
      {
	matname = ptr->GetName();
	matname = filter(matname);
	oname = matname;
	matnumb = 0;
      }
    
    if (materials.find(oname) == materials.end())
      materials[oname] = ptr;
    else if (materials[oname] != ptr)
      {    
	std::ostringstream os;

	matnumb++;

	os << matnumb;
	std::string smn = os.str();
	oname = matname + smn;
	oname = name(ptr,oname);
      }    
    return oname;
    */
  };
    
  std::string name(const G4VSolid* ptr)
  {
    solname = ptr->GetName();
    solname = filter(solname);
    std::ostringstream os;
    if(nameFormat == 0)
    {
     os << ptr;
    }
    else if (nameFormat == 1)
    {
     os << "_" << (long int)ptr;
    }
    else if (nameFormat == 2)
    {
     os << "";
    }
    std::string ssn = os.str();
     
    return solname+ssn;
  };
    
//   std::string name(const G4VSolid* ptr/*, std::string oname=""*/)
//   {
//     if(oname=="")
//       {
// 	solname = ptr->GetName();
// 	solname = filter(solname);
// 	oname = solname;
// 	solnumb = 0;
//       }
    
//     if (solids.find(oname) == solids.end())
//       solids[oname] = ptr;
//     else if (solids[oname] != ptr)
//       {
// 	std::ostringstream os;

// 	solnumb++;      

// 	os << solnumb;
// 	std::string ssn = os.str();
// 	oname = solname + ssn;
// 	oname = name(ptr,oname);
//       }
//     return oname;
//   };
    
  std::string name(const G4VPhysicalVolume* ptr/*, std::string oname=""*/)
  {
    //    std::stringstream cpnb;
    //    cpnb << ptr->GetCopyNo();
    //    std::string scpnb(cpnb.str());

    pvolname = ptr->GetName();
    pvolname = filter(pvolname);    
    std::ostringstream os;
    if(nameFormat == 0)
    {
     os << ptr;
    }
    else if (nameFormat == 1)
    {
     os << "_" << (long int)ptr;
    }
    else if (nameFormat == 2)
    {
     os << "";
    }
    std::string ssn = os.str();
     
    return pvolname+ssn;

    /*
    if(oname=="")
      {  
	pvolname = ptr->GetName();
	pvolname = filter(pvolname);   //+scpnb;
	oname = pvolname;
	pvolnumb = 0;
      }    

    if (pvolumes.find(oname) == pvolumes.end())
      pvolumes[oname] = ptr;
    else if (pvolumes[oname] != ptr)
      {    
	std::ostringstream os;

	pvolnumb++;

	os << pvolnumb;
	std::string spv = os.str();
	oname = pvolname + spv;
	oname = name(ptr,oname);
      }    
    return oname;
    */ 
  };
    
  std::string name(const G4LogicalVolume* ptr/*, std::string oname=""*/)
  {
    lvolname = ptr->GetName();
    lvolname = filter(lvolname);
    std::ostringstream os;
    if(nameFormat == 0)
    {
     os << ptr;
    }
    else if (nameFormat == 1)
    {
     os << "_" << (long int)ptr;
    }
    else if (nameFormat == 2)
    {
     os << "";
    }
    std::string ssn = os.str();
     
    return lvolname+ssn;

    /*
    if(oname=="")
      {
	lvolname = ptr->GetName();
	lvolname = filter(lvolname);  
	oname = lvolname;
	lvolnumb = 0;
      }    

    if (lvolumes.find(oname) == lvolumes.end())
      lvolumes[oname] = ptr;
    else if (lvolumes[oname] != ptr)
      {
	std::ostringstream os;

	lvolnumb++;
      
	os << lvolnumb;
	std::string slv = os.str();
	oname = lvolname + slv;
	oname = name(ptr,oname);
      }    
    return oname;
    */
  };  
  //
};


#endif // WRITERG4_UTILS_H
