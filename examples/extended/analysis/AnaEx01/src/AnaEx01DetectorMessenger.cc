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
// $Id: AnaEx01DetectorMessenger.cc,v 1.4 2002/12/05 00:24:22 asaim Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
// 

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

#include "AnaEx01DetectorMessenger.hh"

#include "AnaEx01DetectorConstruction.hh"
#include "G4UIdirectory.hh"
#include "G4UIcmdWithAString.hh"
#include "G4UIcmdWithAnInteger.hh"
#include "G4UIcmdWithADoubleAndUnit.hh"
#include "G4UIcmdWithoutParameter.hh"

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

AnaEx01DetectorMessenger::AnaEx01DetectorMessenger(AnaEx01DetectorConstruction * AnaEx01Det)
:AnaEx01Detector(AnaEx01Det)
{ 
  AnaEx01detDir = new G4UIdirectory("/calor/");
  AnaEx01detDir->SetGuidance("AnaEx01 detector control.");
      
  AbsMaterCmd = new G4UIcmdWithAString("/calor/setAbsMat",this);
  AbsMaterCmd->SetGuidance("Select Material of the Absorber.");
  AbsMaterCmd->SetParameterName("choice",false);
  AbsMaterCmd->AvailableForStates(G4State_Idle);
  
  GapMaterCmd = new G4UIcmdWithAString("/calor/setGapMat",this);
  GapMaterCmd->SetGuidance("Select Material of the Gap.");
  GapMaterCmd->SetParameterName("choice",false);
  GapMaterCmd->AvailableForStates(G4State_Idle);
    
  AbsThickCmd = new G4UIcmdWithADoubleAndUnit("/calor/setAbsThick",this);
  AbsThickCmd->SetGuidance("Set Thickness of the Absorber");
  AbsThickCmd->SetParameterName("Size",false);
  AbsThickCmd->SetRange("Size>=0.");
  AbsThickCmd->SetUnitCategory("Length");
  AbsThickCmd->AvailableForStates(G4State_Idle);
  
  GapThickCmd = new G4UIcmdWithADoubleAndUnit("/calor/setGapThick",this);
  GapThickCmd->SetGuidance("Set Thickness of the Gap");
  GapThickCmd->SetParameterName("Size",false);
  GapThickCmd->SetRange("Size>=0.");
  GapThickCmd->SetUnitCategory("Length");  
  GapThickCmd->AvailableForStates(G4State_Idle);
  
  SizeYZCmd = new G4UIcmdWithADoubleAndUnit("/calor/setSizeYZ",this);
  SizeYZCmd->SetGuidance("Set tranverse size of the calorimeter");
  SizeYZCmd->SetParameterName("Size",false);
  SizeYZCmd->SetRange("Size>0.");
  SizeYZCmd->SetUnitCategory("Length");    
  SizeYZCmd->AvailableForStates(G4State_Idle);
  
  NbLayersCmd = new G4UIcmdWithAnInteger("/calor/setNbOfLayers",this);
  NbLayersCmd->SetGuidance("Set number of layers.");
  NbLayersCmd->SetParameterName("NbLayers",false);
  NbLayersCmd->SetRange("NbLayers>0 && NbLayers<500");
  NbLayersCmd->AvailableForStates(G4State_Idle);

  UpdateCmd = new G4UIcmdWithoutParameter("/calor/update",this);
  UpdateCmd->SetGuidance("Update calorimeter geometry.");
  UpdateCmd->SetGuidance("This command MUST be applied before \"beamOn\" ");
  UpdateCmd->SetGuidance("if you changed geometrical value(s).");
  UpdateCmd->AvailableForStates(G4State_Idle);
      
  MagFieldCmd = new G4UIcmdWithADoubleAndUnit("/calor/setField",this);  
  MagFieldCmd->SetGuidance("Define magnetic field.");
  MagFieldCmd->SetGuidance("Magnetic field will be in Z direction.");
  MagFieldCmd->SetParameterName("Bz",false);
  MagFieldCmd->SetUnitCategory("Magnetic flux density");
  MagFieldCmd->AvailableForStates(G4State_Idle);  
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

AnaEx01DetectorMessenger::~AnaEx01DetectorMessenger()
{
  delete NbLayersCmd;
  delete AbsMaterCmd; delete GapMaterCmd;
  delete AbsThickCmd; delete GapThickCmd;
  delete SizeYZCmd;   delete UpdateCmd;
  delete MagFieldCmd;
  delete AnaEx01detDir;
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....

void AnaEx01DetectorMessenger::SetNewValue(G4UIcommand* command,G4String newValue)
{ 
  if( command == AbsMaterCmd )
   { AnaEx01Detector->SetAbsorberMaterial(newValue);}
   
  if( command == GapMaterCmd )
   { AnaEx01Detector->SetGapMaterial(newValue);}
  
  if( command == AbsThickCmd )
   { AnaEx01Detector->SetAbsorberThickness(AbsThickCmd->GetNewDoubleValue(newValue));}
   
  if( command == GapThickCmd )
   { AnaEx01Detector->SetGapThickness(GapThickCmd->GetNewDoubleValue(newValue));}
   
  if( command == SizeYZCmd )
   { AnaEx01Detector->SetCalorSizeYZ(SizeYZCmd->GetNewDoubleValue(newValue));}
   
  if( command == NbLayersCmd )
   { AnaEx01Detector->SetNbOfLayers(NbLayersCmd->GetNewIntValue(newValue));}
  
  if( command == UpdateCmd )
   { AnaEx01Detector->UpdateGeometry(); }

  if( command == MagFieldCmd )
   { AnaEx01Detector->SetMagField(MagFieldCmd->GetNewDoubleValue(newValue));}
}

//....oooOO0OOooo........oooOO0OOooo........oooOO0OOooo........oooOO0OOooo....
