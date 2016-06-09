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
// $Id: G4RTSteppingAction.hh,v 1.4 2001/07/11 10:09:02 gunter Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
//

// class description:
//
//  This is a concrete class of G4UserSteppingAction. This class is used
// by G4RayTracer for managing a ray tracked through volumes. An object
// of this class is constructed by G4RayTracer and set to G4SteppingManager
// with replacement of user defined stepping action during the period of
// ray tracing.
//

//////////////////////
//G4RTSteppingAction
/////////////////////


#ifndef G4RTSteppingAction_h
#define G4RTSteppingAction_h 1


#include "G4UserSteppingAction.hh"
#include "globals.hh"

class G4RTSteppingAction : public G4UserSteppingAction
{
  public:
    G4RTSteppingAction();
    virtual ~G4RTSteppingAction(){;}

    virtual void UserSteppingAction(const G4Step*);

  private:
    G4bool ignoreTransparency;

  public:
    inline void SetIgnoreTransparency(G4bool val)
    { ignoreTransparency = val; }
    inline G4bool GetIgnoreTransparency() const
    { return ignoreTransparency; }
};

#endif
