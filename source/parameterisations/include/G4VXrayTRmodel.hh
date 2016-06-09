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
// $Id: G4VXrayTRmodel.hh,v 1.5 2003/06/16 16:56:32 gunter Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
// 
///////////////////////////////////////////////////////////////////////////
// 
// base class for 'fast' parametrisation model describing X-ray transition
// created in some G4Envelope. Anglur distribuiton is very rough !!! (see DoIt
// method
// 
// History:
// 23.01.00 V. Grichine first version 
// 09.02.00 V. Grichine, DoIt was transformed from virtual
//


#ifndef G4VXrayTRmodel_h
#define G4VXrayTRmodel_h 1


#include <complex>
#include "globals.hh"

#include "G4PhysicsTable.hh"
#include "G4PhysicsLogVector.hh"
#include "G4Gamma.hh"

#include "G4VFastSimulationModel.hh"
// #include "G4ForwardXrayTR.hh"

class G4VXrayTRmodel : public G4VFastSimulationModel
// , public G4ForwardXrayTR
{
public:

   G4VXrayTRmodel (G4LogicalVolume *anEnvelope,G4double,G4double);
   virtual  ~G4VXrayTRmodel ();

  // Pure virtual functions from base class

  G4bool IsApplicable(const G4ParticleDefinition&);
 
  G4bool ModelTrigger(const G4FastTrack &);

  // Pure virtuals must be implemented in inherited particular TR radiators
 
  virtual  void DoIt(const G4FastTrack&, G4FastStep&) = 0  ;

  virtual  G4double GetStackFactor( G4double energy, G4double gamma,
                                                     G4double varAngle ) = 0  ;

  G4double OneBoundaryXTRNdensity( G4double energy,
                                   G4double gamma,
				   G4double varAngle ) const ;


  // for photon energy distribution tables

  G4double XTRNSpectralAngleDensity(G4double varAngle) ;
  G4double XTRNSpectralDensity(G4double energy) ;
  
  // for photon angle distribution tables

  G4double XTRNAngleSpectralDensity(G4double energy) ;
  G4double XTRNAngleDensity(G4double varAngle) ;

  void GetNumberOfPhotons() ;  

  void ExampleDoIt(const G4FastTrack&, G4FastStep&) ;

  // Auxiliary functions for plate/gas material parameters

  G4double  GetPlateFormationZone(G4double,G4double,G4double) ;
  G4complex GetPlateComplexFZ(G4double,G4double,G4double) ;
  void      ComputePlatePhotoAbsCof() ;
  G4double  GetPlateLinearPhotoAbs(G4double) ;
  void      GetPlateZmuProduct() ;
  G4double  GetPlateZmuProduct(G4double,G4double,G4double) ;

  G4double  GetGasFormationZone(G4double,G4double,G4double) ;
  G4complex GetGasComplexFZ(G4double,G4double,G4double) ;
  void      ComputeGasPhotoAbsCof() ;
  G4double  GetGasLinearPhotoAbs(G4double) ;
  void      GetGasZmuProduct() ;
  G4double  GetGasZmuProduct(G4double,G4double,G4double) ;

  G4double GetXTRrandomEnergy( G4double scaledTkin, G4int iTkin ) ;
  G4double GetXTRenergy( G4int iPlace, G4double position, G4int iTransfer  ) ;

protected:

  G4Gamma* fPtrGamma ;  // pointer to TR photon

  G4double* fGammaCutInKineticEnergy ; // TR photon cut in energy array
  G4double  fGammaTkinCut ;            // Tkin cut of TR photon in current mat.

  G4PhysicsTable* fAngleDistrTable ;
  G4PhysicsTable* fEnergyDistrTable ;

  static G4PhysicsLogVector* fProtonEnergyVector ;


  static G4double fTheMinEnergyTR ;            //  static min TR energy
  static G4double fTheMaxEnergyTR ;            //  static max TR energy
         G4double fMinEnergyTR ;               //  min TR energy in material
         G4double fMaxEnergyTR ;               //  max TR energy in material
  static G4double  fTheMaxAngle ;               //  max theta of TR quanta
  static G4double  fTheMinAngle ;               //  max theta of TR quanta
         G4double  fMaxThetaTR ;               //  max theta of TR quanta
  static G4int          fBinTR ;               //  number of bins in TR vectors

  static G4double fMinProtonTkin ;             // min Tkin of proton in tables
  static G4double fMaxProtonTkin ;             // max Tkin of proton in tables
  static G4int    fTotBin        ;             // number of bins in log scale
         G4double fGamma         ;             // current Lorentz factor
         G4double fEnergy ;                    // energy and
         G4double fVarAngle ;                  // angle squared

  static G4double fPlasmaCof ;               // physical consts for plasma energy
  static G4double fCofTR ;

  G4double fSigma1, fSigma2 ;               // plasma energy Sq of matter1/2

  G4int fMatIndex1, fMatIndex2 ;

  G4int fPlateNumber ;

  G4double** fPlatePhotoAbsCof ;
  G4int      fPlateIntervalNumber ;
  G4double   fPlateThick ;
 
  G4double** fGasPhotoAbsCof ;
  G4int      fGasIntervalNumber ;
  G4double   fGasThick ;     


};

#endif
