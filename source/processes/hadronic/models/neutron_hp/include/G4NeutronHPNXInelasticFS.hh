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
// $Id: G4NeutronHPNXInelasticFS.hh,v 1.7 2003/07/01 15:58:37 hpw Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
#ifndef G4NeutronHPNXInelasticFS_h
#define G4NeutronHPNXInelasticFS_h 1

#include "globals.hh"
#include "G4HadProjectile.hh"
#include "G4HadFinalState.hh"
#include "G4NeutronHPInelasticBaseFS.hh"
#include "G4NeutronHPAngular.hh"
#include "G4NeutronHPEnergyDistribution.hh"
#include "G4NeutronHPEnAngCorrelation.hh"
#include "G4NeutronHPPhotonDist.hh"

class G4NeutronHPNXInelasticFS : public G4NeutronHPInelasticBaseFS
{
  public:
  
  G4NeutronHPNXInelasticFS(){}
  ~G4NeutronHPNXInelasticFS(){}
  void Init (G4double A, G4double Z, G4String & dirName, G4String & aFSType);
  G4HadFinalState * ApplyYourself(const G4HadProjectile & theTrack);
  G4NeutronHPFinalState * New() 
  {
   G4NeutronHPNXInelasticFS * theNew = new G4NeutronHPNXInelasticFS;
   return theNew;
  }
  
  private:
  
};
#endif
