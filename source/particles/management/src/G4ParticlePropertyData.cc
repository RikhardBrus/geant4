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
// $Id: G4ParticlePropertyData.cc,v 1.1 2003/06/11 07:20:06 kurasige Exp $
//
// class G4ParticlePropertyData
//
// Implementation
//
// History:
// first implementation by H Kurashige 9 June 2003

#include "G4ios.hh"
#include "globals.hh"
#include "G4ParticlePropertyData.hh"


/////////////////////////////////////////////////////////////
G4ParticlePropertyData::~G4ParticlePropertyData()
{
}

/////////////////////////////////////////////////////////////
G4ParticlePropertyData::G4ParticlePropertyData(const G4String& particleName):
  theParticleName(particleName),
  thePDGMass(0.0),
  thePDGWidth(0.0),
  thePDGCharge(0.0),
  thePDGiSpin(0),
  thePDGiParity(0),
  thePDGiConjugation(0),
  thePDGiGParity(0),
  thePDGiIsospin(0),
  thePDGiIsospin3(0),
  theLeptonNumber(0),
  theBaryonNumber(0),
  thePDGEncoding(0),
  theAntiPDGEncoding(0),
  fPDGMassModified(false),
  fPDGWidthModified(false),
  fPDGChargeModified(false),
  fPDGiSpinModified(false),
  fPDGiParityModified(false),
  fPDGiConjugationModified(false),
  fPDGiGParityModified(false),
  fPDGiIsospinModified(false),
  fPDGiIsospin3Modified(false),
  fPDGIsospinModified(false),
  fPDGIsospin3Modified(false),
  fLeptonNumberModified(false),
  fBaryonNumberModified(false),
  fPDGEncodingModified(false),
  fAntiPDGEncodingModified(false),
  fQuarkContentModified(false),
  fAntiQuarkContentModified(false),
  fPDGLifeTimeModified(false),
  verboseLevel(1)
{
  for (size_t flv=0; flv<NumberOfQuarkFlavor; ++flv) {
    theQuarkContent[flv] =0;
    theAntiQuarkContent[flv]=0;
  }
}


////////////////////////
G4ParticlePropertyData::G4ParticlePropertyData(const G4ParticlePropertyData &right):
  fPDGMassModified(false),
  fPDGWidthModified(false),
  fPDGChargeModified(false),
  fPDGiSpinModified(false),
  fPDGiParityModified(false),
  fPDGiConjugationModified(false),
  fPDGiGParityModified(false),
  fPDGiIsospinModified(false),
  fPDGiIsospin3Modified(false),
  fPDGIsospinModified(false),
  fPDGIsospin3Modified(false),
  fLeptonNumberModified(false),
  fBaryonNumberModified(false),
  fPDGEncodingModified(false),
  fAntiPDGEncodingModified(false),
  fQuarkContentModified(false),
  fAntiQuarkContentModified(false),
  fPDGLifeTimeModified(false)
{
  verboseLevel      = right.verboseLevel; 
  theParticleName   = right.theParticleName;
  thePDGMass        = right.thePDGMass;
  thePDGWidth       = right. thePDGWidth;
  thePDGCharge      = right.thePDGCharge;
  thePDGiSpin       = right.thePDGiSpin;
  thePDGiParity     = right.thePDGiParity;
  thePDGiConjugation   = right.thePDGiConjugation;
  thePDGiGParity    = right.thePDGiGParity;
  thePDGiIsospin    = right.thePDGiIsospin;
  thePDGiIsospin3   = right.thePDGiIsospin3;
  theLeptonNumber   = right.theLeptonNumber;
  theBaryonNumber   = right.theBaryonNumber;
  thePDGEncoding    = right.thePDGEncoding;
  theAntiPDGEncoding   = right.theAntiPDGEncoding;
  for (size_t flv=0; flv<NumberOfQuarkFlavor; ++flv) {
    theQuarkContent[flv]    = right.theQuarkContent[flv];
    theAntiQuarkContent[flv]= right.theAntiQuarkContent[flv];
  }
  thePDGLifeTime    = right.thePDGLifeTime;
}
      
////////////////////////
const G4ParticlePropertyData & G4ParticlePropertyData::operator=(const G4ParticlePropertyData &right)
{
  if (this != &right) {
    verboseLevel      = right.verboseLevel; 
    theParticleName   = right.theParticleName;
    thePDGMass        = right.thePDGMass;
    thePDGWidth       = right. thePDGWidth;
    thePDGCharge      = right.thePDGCharge;
    thePDGiSpin       = right.thePDGiSpin;
    thePDGiParity     = right.thePDGiParity;
    thePDGiConjugation  = right.thePDGiConjugation;
    thePDGiGParity    = right.thePDGiGParity;
    thePDGiIsospin    = right.thePDGiIsospin;
    thePDGiIsospin3   = right.thePDGiIsospin3;
    theLeptonNumber   = right.theLeptonNumber;
    theBaryonNumber   = right.theBaryonNumber;
    thePDGEncoding    = right.thePDGEncoding;
    theAntiPDGEncoding  = right.theAntiPDGEncoding;
    for (size_t flv=0; flv<NumberOfQuarkFlavor; ++flv) {
      theQuarkContent[flv]    = right.theQuarkContent[flv];
      theAntiQuarkContent[flv]= right.theAntiQuarkContent[flv];
    }
    thePDGLifeTime    = right.thePDGLifeTime;
    fPDGMassModified          = true;
    fPDGWidthModified         = true;  
    fPDGChargeModified        = true;
    fPDGiSpinModified         = true;
    fPDGiParityModified       = true;    
    fPDGiConjugationModified  = true;  
    fPDGiGParityModified      = true;
    fPDGiIsospinModified      = true; 
    fPDGiIsospin3Modified     = true;
    fPDGIsospinModified       = true; 
    fPDGIsospin3Modified      = true;
    fLeptonNumberModified     = true;
    fBaryonNumberModified     = true;
    fPDGEncodingModified      = true;
    fAntiPDGEncodingModified  = true;
    fQuarkContentModified     = true;
    fAntiQuarkContentModified = true;
    fPDGLifeTimeModified      = true;   
  }
  return *this;
}
  
////////////////////////
G4int G4ParticlePropertyData::operator==(const G4ParticlePropertyData &right) const
{
  return (this == &right);
}

////////////////////////
G4int G4ParticlePropertyData::operator!=(const G4ParticlePropertyData &right) const
{
  return (this != &right);
}

////////////////////////
void G4ParticlePropertyData::Print() const
{
  G4cout << " Particle Name : " << theParticleName << G4endl;
  G4cout << " PDG particle code : " << thePDGEncoding;
  G4cout << " [PDG anti-particle code: " << this->GetAntiPDGEncoding() << "]"<< G4endl;
  G4cout << " Mass [GeV/c2] : " << thePDGMass/GeV ;
  G4cout << "     Width : " << thePDGWidth/GeV << G4endl;
  G4cout << " Lifetime [nsec] : " << thePDGLifeTime/ns << G4endl;
  G4cout << " Charge [e]: " << thePDGCharge/eplus << G4endl;
  G4cout << " Spin : " << thePDGiSpin << "/2" << G4endl;
  G4cout << " Parity : " << thePDGiParity << G4endl;
  G4cout << " Charge conjugation : " << thePDGiConjugation << G4endl;
  G4cout << " Isospin : (I,Iz): (" << thePDGiIsospin <<"/2";
  G4cout << " , " << thePDGiIsospin3 << "/2 ) " << G4endl;
  G4cout << " GParity : " << thePDGiGParity << G4endl;
  G4cout << " Lepton number : " << theLeptonNumber;
  G4cout << " Baryon number : " << theBaryonNumber << G4endl;  
  G4cout << " Quark contents     (d,u,s,c,b,t) : " << theQuarkContent[0];
  G4cout << ", " << theQuarkContent[1];
  G4cout << ", " << theQuarkContent[2];
  G4cout << ", " << theQuarkContent[3];
  G4cout << ", " << theQuarkContent[4];
  G4cout << ", " << theQuarkContent[5] << G4endl;
  G4cout << " AntiQuark contents               : " << theAntiQuarkContent[0];
  G4cout << ", " << theAntiQuarkContent[1];
  G4cout << ", " << theAntiQuarkContent[2];
  G4cout << ", " << theAntiQuarkContent[3];
  G4cout << ", " << theAntiQuarkContent[4];
  G4cout << ", " << theAntiQuarkContent[5] << G4endl;
}









