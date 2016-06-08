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
// $Id: XrayFluoSteppingVerbose.hh
// GEANT4 tag $Name:  xray_fluo-V03-02-00
//
// Author: Elena Guardincerri (Elena.Guardincerri@ge.infn.it)
//
// History:
// -----------
//  28 Nov 2001  Elena Guardincerri   Created
//
// -------------------------------------------------------------------


class XrayFluoSteppingVerbose;

#ifndef XrayFluoSteppingVerbose_h
#define XrayFluoSteppingVerbose_h 1

#include "G4SteppingVerbose.hh"

class XrayFluoSteppingVerbose : public G4SteppingVerbose {

public: 
 
// Constructor/Destructor
  XrayFluoSteppingVerbose();
 ~XrayFluoSteppingVerbose();

  void StepInfo();
  void TrackingStarted();



};

#endif
