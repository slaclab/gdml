// $Id: MaterialLocator.h,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#ifndef G4PROCESSOR_MATERIALLOCATOR_H
#define G4PROCESSOR_MATERIALLOCATOR_H 1

// geant4
#include "G4Element.hh"
#include "G4Material.hh"
#include "G4ElementTable.hh"
#include "G4MaterialTable.hh"

#include <string>

/**
 * @class MaterialLocator
 * @author Jeremy McCormick
 * @date 2005-11-23
 *
 * Find materials in Geant4's G4MaterialTable.
 * Secondarily, materials are looked up in Geant4's
 * NIST database, if this was enabled by configure.
 */
class MaterialLocator
{

  // These are just for correctness.  All methods on this class are static, so construction is not necessary.
 public:
  MaterialLocator() {}
  virtual ~MaterialLocator() {}

 public:

  /**
   * Find a material in the G4MaterialTable or NIST database.
   *
   * @param materialName name of the material to lookup or build
   * @param warnOnNotFound turn warning on/off if the material is not found; DEFAULT=false
   * @param useNist look in Geant4's NIST database if the material is not found; DEFAULT=true (if NIST is enabled)
   * @return G4Material or null if not found
   */
  static G4Material* FindMaterial(const std::string& materialName,
				  bool warnOnNotFound=false,
#ifdef GDML_USE_NIST
				  bool useNist=true
#else
				  bool useNist=false
#endif
				  );

  /**
   * Find an element in the G4ElementTable or NIST database.
   *
   * @param elementName name of the element to lookup or build
   * @param warnOnNotFound turn warning on/off if the element is not found; DEFAULT=false
   * @param useNist look in Geant4's NIST database if the element is not found; DEFAULT=true (if NIST is enabled)
   * @return G4Element or null if not found
   */
  static G4Element* FindElement(const std::string& elementName,
				bool warnOnNotFound=false,
#ifdef GDML_USE_NIST
				bool useNist=true
#else
				bool useNist=false
#endif
				);

 public:

  /**
   * Find a material in the G4MaterialTable.
   *
   * @param materialName name of the material to lookup
   * @return G4Material or null if not found
   * @note Copied from Geant4's G4Material::GetMaterial(), but removed the warning message.
   */
  static G4Material* GetMaterial(const std::string& materialName);

  /**
   * Find a material in the G4ElementTable.
   *
   * @param elementName name of the element to lookup
   * @return G4Element or null if not found
   * @note Copied from Geant4's G4Element::GetElement(), but removed the warning message.
   */
  static G4Element* GetElement(const std::string& elementName);

#ifdef GDML_USE_NIST
  /**
   * Find or build a material from Geant4's NIST database.
   * @param elementName name of the element to build or find
   * @return G4Element or null if not found
   */
  static G4Element* GetNistElement(const std::string& elementName);

  /**
   * Find or build an element from Geant4's NIST database.
   * @param materialName name of the material to build or find
   * @return G4Material or null if not found
   */
  static G4Material* GetNistMaterial(const std::string& materialName);
#endif
};

#endif
