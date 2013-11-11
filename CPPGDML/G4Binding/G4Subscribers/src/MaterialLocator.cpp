// $Id: MaterialLocator.cpp,v 1.1.1.1 2010-07-13 15:18:49 jeremy Exp $
#include "G4Subscribers/MaterialLocator.h"

// geant4
#include "G4MaterialTable.hh"
#include "G4ElementTable.hh"

// NIST
#ifdef GDML_USE_NIST
#include "G4NistManager.hh"
#endif

G4Material* MaterialLocator::FindMaterial(const std::string& materialName, bool warnOnNotFound, bool useNist)
{
  G4Material* material = MaterialLocator::GetMaterial(materialName);

  if ( 0 == material && useNist ) {
#ifdef GDML_USE_NIST
    material = GetNistMaterial(materialName);
#else
    G4cerr << "ERROR: Your Geant4 version does not have NIST support." << G4endl;
#endif
  }

  if ( ( warnOnNotFound ) && ( 0 == material ) ) {
    G4cerr << "WARNING: MaterialLocator could not find the material <" << materialName << ">" << G4endl;
  }

  return material;
}

G4Element* MaterialLocator::FindElement(const std::string& elementName, bool warnOnNotFound, bool useNist)
{
  G4Element* element = MaterialLocator::GetElement(elementName);

  if ( 0 == element && useNist ) {
#ifdef GDML_USE_NIST
    element = GetNistElement(elementName);
#else
    G4cerr << "ERROR: Your Geant4 version does not have NIST support." << G4endl;
#endif
  }

  if ( ( warnOnNotFound ) && ( 0 == element ) ) {
    G4cerr << "WARNING: MaterialLocator could not find the element <" << elementName << ">" << G4endl;
  }

  return element;
}

G4Material* MaterialLocator::GetMaterial(const std::string& materialName)
{
  const G4MaterialTable* theMaterialTable = G4Material::GetMaterialTable();

  // search the material by its name
  for (size_t J=0 ; J<theMaterialTable->size() ; J++) {
    if ((*theMaterialTable)[J]->GetName() == ((G4String)materialName))
      return (*theMaterialTable)[J];
  }

  return 0;
}

G4Element* MaterialLocator::GetElement(const std::string& elementName)
{
  const G4ElementTable* theElementTable = G4Element::GetElementTable();

  // search the element by its name
  for (size_t J=0 ; J<theElementTable->size() ; J++ ) {
    if ((*theElementTable)[J]->GetName() == ((G4String)elementName))
      return (*theElementTable)[J];
  }

  return 0;
}

#ifdef GDML_USE_NIST
G4Element* MaterialLocator::GetNistElement(const std::string& elementName)
{
  return G4NistManager::Instance()->FindOrBuildElement(elementName);
}

G4Material* MaterialLocator::GetNistMaterial(const std::string& materialName)
{
  return G4NistManager::Instance()->FindOrBuildMaterial(materialName);
}
#endif

