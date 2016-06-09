//
// ********************************************************************
// * License and Disclaimer                                           *
// *                                                                  *
// * The  Geant4 software  is  copyright of the Copyright Holders  of *
// * the Geant4 Collaboration.  It is provided  under  the terms  and *
// * conditions of the Geant4 Software License,  included in the file *
// * LICENSE and available at  http://cern.ch/geant4/license .  These *
// * include a list of copyright holders.                             *
// *                                                                  *
// * Neither the authors of this software system, nor their employing *
// * institutes,nor the agencies providing financial support for this *
// * work  make  any representation or  warranty, express or implied, *
// * regarding  this  software system or assume any liability for its *
// * use.  Please see the license in the file  LICENSE  and URL above *
// * for the full disclaimer and the limitation of liability.         *
// *                                                                  *
// * This  code  implementation is the result of  the  scientific and *
// * technical work of the GEANT4 collaboration.                      *
// * By using,  copying,  modifying or  distributing the software (or *
// * any work based  on the software)  you  agree  to acknowledge its *
// * use  in  resulting  scientific  publications,  and indicate your *
// * acceptance of all terms of the Geant4 Software license.          *
// ********************************************************************
//
//
// $Id: G4ChargeExchange.hh,v 1.2 2006/06/29 20:08:55 gunter Exp $
// GEANT4 tag $Name: geant4-08-01 $
//
//
// G4 Model: Charge and strangness exchange based on G4LightMedia model
//           28 May 2006 V.Ivanchenko
//
// Modified:
//
//

#ifndef G4ChargeExchange_h
#define G4ChargeExchange_h 1

// Class Description
// Final state production model for hadron nuclear coherent charge exchange;
// Class Description - End

#include "globals.hh"
#include "G4HadronicInteraction.hh"
#include "G4HadProjectile.hh"
#include "G4Nucleus.hh"

class G4ParticleDefinition;
class G4VQCrossSection;
class G4ElasticHadrNucleusHE;
class G4HadronElastic;

class G4ChargeExchange : public G4HadronicInteraction
{
public:

  G4ChargeExchange(G4HadronElastic* hel = 0,
                   G4double elim = 100.*keV,
	           G4double plow = 200.*MeV,
		   G4double ehigh= GeV);

  virtual ~G4ChargeExchange();

  virtual G4HadFinalState * ApplyYourself(
                   const G4HadProjectile & aTrack,
                   G4Nucleus & targetNucleus);

  void SetMomentumLow(G4double value);

  void SetKinEnergyHigh(G4double value);

private:

  G4VQCrossSection*           qCManager;
  G4ElasticHadrNucleusHE*     hElastic;
  G4HadronElastic*            fElastic;
  G4bool                      native;

  G4ParticleDefinition* theProton;
  G4ParticleDefinition* theNeutron;
  G4ParticleDefinition* theAProton;
  G4ParticleDefinition* theANeutron;
  G4ParticleDefinition* thePiPlus;
  G4ParticleDefinition* thePiMinus;
  G4ParticleDefinition* thePiZero;
  G4ParticleDefinition* theKPlus;
  G4ParticleDefinition* theKMinus;
  G4ParticleDefinition* theK0S;
  G4ParticleDefinition* theK0L;
  G4ParticleDefinition* theL;
  G4ParticleDefinition* theAntiL;
  G4ParticleDefinition* theSPlus;
  G4ParticleDefinition* theASPlus;
  G4ParticleDefinition* theSMinus;
  G4ParticleDefinition* theASMinus;
  G4ParticleDefinition* theS0;
  G4ParticleDefinition* theAS0;
  G4ParticleDefinition* theXiMinus;
  G4ParticleDefinition* theXi0;
  G4ParticleDefinition* theAXiMinus;
  G4ParticleDefinition* theAXi0;
  G4ParticleDefinition* theOmega;
  G4ParticleDefinition* theAOmega;
  G4ParticleDefinition* theD;
  G4ParticleDefinition* theT;
  G4ParticleDefinition* theA;
  G4ParticleDefinition* theHe3;

  G4double ekinlim;  // in MeV
  G4double plablow;  // in MeV/c
  G4double ekinhigh;  // in MeV/c
};

inline void G4ChargeExchange::SetMomentumLow(G4double value)
{
  plablow = value;
}

inline void G4ChargeExchange::SetKinEnergyHigh(G4double value)
{
  ekinhigh = value;
}

#endif