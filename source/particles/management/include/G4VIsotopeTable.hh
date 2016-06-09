//
// ********************************************************************
// * DISCLAIMER                                                       *
// *                                                                  *
// * The following disclaimer summarizes all the specific disclaimers *
// * of contributors to this software. The specific disclaimers,which *
// * govern, are listed with their locations in:                      *
// *   http://cern.ch/geant4/license                                  *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.                                                             *
// *                                                                  *
// * This  code  implementation is the  intellectual property  of the *
// * GEANT4 collaboration.                                            *
// * By copying,  distributing  or modifying the Program (or any work *
// * based  on  the Program)  you indicate  your  acceptance of  this *
// * statement, and all its terms.                                    *
// ********************************************************************
//
//
// $Id: G4VIsotopeTable.hh,v 1.5 2001/07/11 10:01:58 gunter Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
// 
// ------------------------------------------------------------
//	GEANT 4 class header file 
//
//----------------------------------------------------------
//      New design                               5 Oct. 99 H.Kurashige
#ifndef G4VIsotopeTable_h
#define G4VIsotopeTable_h 1

#include "G4ios.hh"
#include "globals.hh"
#include "G4IsotopeProperty.hh"
class G4VIsotopeTable
{
 // Class Description
 //  G4VIsotopeTable is the virtual class for acsess to an isotpe table
 //  which contains "stable" isotopes with their properties.
 //

 public:
  // constructor
  G4VIsotopeTable(const G4String& name = "");

 public:
  // destructor
  virtual ~G4VIsotopeTable();

 public: // With Description
  // pure virtual method
  virtual G4bool FindIsotope(G4IsotopeProperty* property) = 0;  
  virtual G4IsotopeProperty* GetIsotope(G4int Z, G4int A, G4double E) = 0;
  // Search the isotope in the G4VIsotopeTable. 
  // The isotope is desingated by 
  //    G4int    Z:  number of proton (Atomic number)
  //    G4int    A:  number of nucleon (Atomic mass)
  //      and
  //    G4double E:  excited energy
  // in the given G4IsotopeProperty.
  // If corresopnding isotope exist in the table, this method returns
  // 'true' as well as fills other properties such as spin, lifetime,
  // ,decay modes and precise excited energy in the given G4IsotopeProperty.
  // This method returns 'false' if no corresponding isotope is found 
  // without modification of property.
  //   

  // Set/Get verbose level
  G4int                GetVerboseLevel() const;
  void                 SetVerboseLevel(G4int level);  

 private:
  G4String             fName;
  G4int                verboseLevel;
};

inline
 G4VIsotopeTable::G4VIsotopeTable(const G4String& name)
  : fName(name), verboseLevel(0)
{
}

inline
 G4VIsotopeTable::~G4VIsotopeTable()
{
}

inline 
 G4int G4VIsotopeTable::GetVerboseLevel() const
{
  return verboseLevel;
}

inline 
 void G4VIsotopeTable::SetVerboseLevel(G4int level)
{
  verboseLevel = level;
}

#endif
