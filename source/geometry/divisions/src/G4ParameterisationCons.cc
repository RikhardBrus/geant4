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
// $Id: G4ParameterisationCons.cc,v 1.6 2003/11/19 11:51:23 gcosmo Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
// class G4ParameterisationCons Implementation file
//
// 26.05.03 - P.Arce Initial version
// ********************************************************************

#include "G4ParameterisationCons.hh"

#include <iomanip>
#include "G4ThreeVector.hh"
#include "G4RotationMatrix.hh"
#include "G4VPhysicalVolume.hh"
#include "G4LogicalVolume.hh"
#include "G4Cons.hh"

//--------------------------------------------------------------------------
G4ParameterisationConsRho::
G4ParameterisationConsRho( EAxis axis, G4int nDiv,
                           G4double width, G4double offset,
                           G4VSolid* msolid, DivisionType divType )
  :  G4VDivisionParameterisation( axis, nDiv, width, offset, divType, msolid )
{
  CheckParametersValidity();
  SetType( "DivisionConsRho" );

  G4Cons* msol = (G4Cons*)(msolid);
  if( msol->GetInnerRadiusPlusZ() == 0. )
  {
    G4cerr << "WARNING - G4ParameterisationConsRho, OuterRadiusMinusZ = 0. "
           << G4endl 
           << "          Width is calculated as that of OuterRadiusMinusZ !"
           << G4endl;
  } 

  if( divType == DivWIDTH )
  {
    fnDiv = CalculateNDiv( msol->GetOuterRadiusMinusZ()
                         - msol->GetInnerRadiusMinusZ(), width, offset );
  }
  else if( divType == DivNDIV )
  {
    G4Cons* msol = (G4Cons*)(msolid);
    fwidth = CalculateWidth( msol->GetOuterRadiusMinusZ()
                           - msol->GetInnerRadiusMinusZ(), nDiv, offset );
  }

#ifdef G4DIVDEBUG
  if( verbose >= 1 )
  {
    G4cout << " G4ParameterisationConsRho - no divisions " << fnDiv << " = "
           << nDiv << G4endl
           << " Offset " << foffset << " = " << offset
           << " - Width " << fwidth << " = " << width << G4endl;
  }
#endif
}

//--------------------------------------------------------------------------
G4ParameterisationConsRho::~G4ParameterisationConsRho()
{
}

//------------------------------------------------------------------------
G4double G4ParameterisationConsRho::GetMaxParameter() const
{
  G4Cons* msol = (G4Cons*)(fmotherSolid);
  return msol->GetOuterRadiusMinusZ() - msol->GetInnerRadiusMinusZ();
}

//--------------------------------------------------------------------------
void
G4ParameterisationConsRho::
ComputeTransformation( const G4int, G4VPhysicalVolume *physVol ) const
{
  //----- translation 
  G4ThreeVector origin(0.,0.,0.); 
  //----- set translation 
  physVol->SetTranslation( origin );

  //----- calculate rotation matrix: unit

#ifdef G4DIVDEBUG
  if( verbose >= 2 )
  {
    G4cout <<  " G4ParameterisationConsRho " << G4endl
           << " Offset: " << foffset
           << " - Width: " << fwidth << G4endl;
  }
#endif

  ChangeRotMatrix( physVol );

#ifdef G4DIVDEBUG
  if( verbose >= 2 )
  {
    G4cout << std::setprecision(8) << " G4ParameterisationConsRho" << G4endl
           << " Position: " << origin << " - Width: " << fwidth
           << " - Axis: " << faxis  << G4endl;
  }
#endif
}

//--------------------------------------------------------------------------
void
G4ParameterisationConsRho::
ComputeDimensions( G4Cons& cons, const G4int copyNo,
                   const G4VPhysicalVolume* ) const
{
  G4Cons* msol = (G4Cons*)(fmotherSolid);

  G4double pRMin1 = msol->GetInnerRadiusMinusZ() + foffset + fwidth * copyNo;
  G4double pRMax1 = msol->GetInnerRadiusMinusZ() + foffset + fwidth * (copyNo+1);
 
  //width at Z Plus
  //- G4double fwidthPlus =
  //   fwidth * ( msol->GetOuterRadiusPlusZ()/ msol->GetInnerRadiusPlusZ())
  //-         / ( msol->GetOuterRadiusMinusZ() - msol->GetInnerRadiusMinusZ());
  G4double fwidthPlus = CalculateWidth( msol->GetOuterRadiusPlusZ()
                           - msol->GetInnerRadiusPlusZ(), fnDiv, foffset );
  G4double pRMin2 = msol->GetInnerRadiusPlusZ()
                  + foffset + fwidthPlus * copyNo;
  G4double pRMax2 = msol->GetInnerRadiusPlusZ()
                  + foffset + fwidthPlus * (copyNo+1);
  G4double pDz = msol->GetZHalfLength();

  //- already rotated  double pSR = foffset + copyNo*fwidth;
  G4double pSPhi = msol->GetStartPhiAngle();
  G4double pDPhi = msol->GetDeltaPhiAngle();;

  cons.SetInnerRadiusMinusZ( pRMin1 );
  cons.SetOuterRadiusMinusZ( pRMax1 );
  cons.SetInnerRadiusPlusZ( pRMin2 );
  cons.SetOuterRadiusPlusZ( pRMax2 );
  cons.SetZHalfLength( pDz );
  cons.SetStartPhiAngle( pSPhi );
  cons.SetDeltaPhiAngle( pDPhi );

#ifdef G4DIVDEBUG
  if( verbose >= 2 )
  {
    G4cout << " G4ParameterisationConsRho::ComputeDimensions()" << G4endl
           << " pRMin: " << pRMin1 << " - pRMax: " << pRMax1 << G4endl;
    if( verbose >= 4 ) cons.DumpInfo();
  }
#endif
}

//--------------------------------------------------------------------------
G4ParameterisationConsPhi::
G4ParameterisationConsPhi( EAxis axis, G4int nDiv,
                           G4double width, G4double offset,
                           G4VSolid* msolid, DivisionType divType )
  :  G4VDivisionParameterisation( axis, nDiv, width, offset, divType, msolid )
{ 
  CheckParametersValidity();
  SetType( "DivisionConsPhi" );

  if( divType == DivWIDTH )
  {
    G4Cons* msol = (G4Cons*)(msolid);
    fnDiv = CalculateNDiv( msol->GetDeltaPhiAngle(), width, offset );
  }
  else if( divType == DivNDIV )
  {
    G4Cons* msol = (G4Cons*)(msolid);
    fwidth = CalculateWidth( msol->GetDeltaPhiAngle(), nDiv, offset );
  }

#ifdef G4DIVDEBUG
  if( verbose >= 1 )
  {
    G4cout << " G4ParameterisationConsPhi no divisions " << fnDiv << " = "
           << nDiv << G4endl
           << " Offset " << foffset << " = " << offset << G4endl
           << " Width " << fwidth << " = " << width << G4endl;
  }
#endif
}

//--------------------------------------------------------------------------
G4ParameterisationConsPhi::~G4ParameterisationConsPhi()
{
}

//------------------------------------------------------------------------
G4double G4ParameterisationConsPhi::GetMaxParameter() const
{
  G4Cons* msol = (G4Cons*)(fmotherSolid);
  return msol->GetDeltaPhiAngle();
}

//--------------------------------------------------------------------------
void
G4ParameterisationConsPhi::
ComputeTransformation( const G4int copyNo, G4VPhysicalVolume *physVol ) const
{
  //----- translation 
  G4ThreeVector origin(0.,0.,0.); 
  //----- set translation 
  physVol->SetTranslation( origin );

  //----- calculate rotation matrix (so that all volumes point to the centre)
  G4double posi = foffset  + copyNo*fwidth;

#ifdef G4DIVDEBUG
  if( verbose >= 2 )
  {
    G4cout << " G4ParameterisationConsPhi - position: " << posi/deg << G4endl
           << " Origin: " << origin << " copyNo: " << copyNo
           << " - foffset: " << foffset/deg
           << " - fwidth: " << fwidth/deg << G4endl
           << " - Axis: " << faxis << G4endl;
  }
#endif

  ChangeRotMatrix( physVol, -posi );
}

//--------------------------------------------------------------------------
void
G4ParameterisationConsPhi::
ComputeDimensions( G4Cons& cons, const G4int,
                   const G4VPhysicalVolume* ) const
{
  G4Cons* msol = (G4Cons*)(fmotherSolid);

  G4double pRMin1 = msol->GetInnerRadiusMinusZ();
  G4double pRMax1 = msol->GetOuterRadiusMinusZ();
  G4double pRMin2 = msol->GetInnerRadiusPlusZ();
  G4double pRMax2 = msol->GetOuterRadiusPlusZ();
  G4double pDz = msol->GetZHalfLength();

  //- already rotated  double pSPhi = foffset + copyNo*fwidth;
  G4double pSPhi = foffset + msol->GetStartPhiAngle();
  G4double pDPhi = fwidth;

  cons.SetInnerRadiusMinusZ( pRMin1 );
  cons.SetOuterRadiusMinusZ( pRMax1 );
  cons.SetInnerRadiusPlusZ( pRMin2 );
  cons.SetOuterRadiusPlusZ( pRMax2 );
  cons.SetZHalfLength( pDz );
  cons.SetStartPhiAngle( pSPhi );
  cons.SetDeltaPhiAngle( pDPhi );

#ifdef G4DIVDEBUG
  if( verbose >= 2 )
  {
    G4cout << " G4ParameterisationConsPhi::ComputeDimensions" << G4endl
           << " pSPhi: " << pSPhi << " - pDPhi: " << pDPhi << G4endl;
    if( verbose >= 4 ) cons.DumpInfo();
  }
#endif
}

//--------------------------------------------------------------------------
G4ParameterisationConsZ::
G4ParameterisationConsZ( EAxis axis, G4int nDiv,
                         G4double width, G4double offset,
                         G4VSolid* msolid, DivisionType divType )
  :  G4VDivisionParameterisation( axis, nDiv, width, offset, divType, msolid )
{ 
  CheckParametersValidity();
  SetType( "DivisionConsZ" );

  if( divType == DivWIDTH )
  {
    G4Cons* msol = (G4Cons*)(msolid);
    fnDiv = CalculateNDiv( 2*msol->GetZHalfLength(), width, offset );
  }
  else if( divType == DivNDIV )
  {
    G4Cons* msol = (G4Cons*)(msolid);
    fwidth = CalculateWidth( 2*msol->GetZHalfLength(), nDiv, offset );
  }

#ifdef G4DIVDEBUG
  if( verbose >= 1 )
  {
    G4cout << " G4ParameterisationConsZ: # divisions " << fnDiv << " = "
           << nDiv << G4endl
           << " Offset " << foffset << " = " << offset << G4endl
           << " Width " << fwidth << " = " << width << G4endl
           << " - Axis: " << faxis << G4endl;
  }
#endif
}

//--------------------------------------------------------------------------
G4ParameterisationConsZ::~G4ParameterisationConsZ()
{
}

//------------------------------------------------------------------------
G4double G4ParameterisationConsZ::GetMaxParameter() const
{
  G4Cons* msol = (G4Cons*)(fmotherSolid);
  return 2*msol->GetZHalfLength();
}

//--------------------------------------------------------------------------
void
G4ParameterisationConsZ::
ComputeTransformation( const G4int copyNo, G4VPhysicalVolume* physVol ) const
{
  //----- set translation: along Z axis
  G4Cons* motherCons = (G4Cons*)(GetMotherSolid());
  G4double posi = - motherCons->GetZHalfLength() + foffset
                  + fwidth/2 + copyNo*fwidth;
  G4ThreeVector origin(0.,0.,posi); 
  physVol->SetTranslation( origin );

  //----- calculate rotation matrix: unit

#ifdef G4DIVDEBUG
  if( verbose >= 2 )
  {
    G4cout << " G4ParameterisationConsZ::ComputeTransformation()" << G4endl
           << " Origin: " << origin << " - copyNo: " << copyNo << G4endl
           << " foffset: " << foffset << " - fwidth: " << fwidth
           << G4endl;
  }
#endif

  ChangeRotMatrix( physVol );
}


//--------------------------------------------------------------------------
void
G4ParameterisationConsZ::
ComputeDimensions( G4Cons& cons, const G4int copyNo,
                   const G4VPhysicalVolume* ) const
{
  G4Cons* msol = (G4Cons*)(fmotherSolid);

  G4double mHalfLength = msol->GetZHalfLength();
  G4double aRInner = (msol->GetInnerRadiusPlusZ()
                   - msol->GetInnerRadiusMinusZ()) / (2*mHalfLength);
  G4double bRInner = (msol->GetInnerRadiusPlusZ()
                   + msol->GetInnerRadiusMinusZ()) / 2;
  G4double aROuter = (msol->GetOuterRadiusPlusZ()
                   - msol->GetOuterRadiusMinusZ()) / (2*mHalfLength);
  G4double bROuter = (msol->GetOuterRadiusPlusZ()
                   + msol->GetOuterRadiusMinusZ()) / 2;
  G4double xMinusZ = -mHalfLength + foffset + fwidth*copyNo;
  G4double xPlusZ  = -mHalfLength + foffset + fwidth*(copyNo+1);
  cons.SetInnerRadiusMinusZ( aRInner * xMinusZ + bRInner );
  cons.SetOuterRadiusMinusZ( aROuter * xMinusZ + bROuter );
  cons.SetInnerRadiusPlusZ( aRInner * xPlusZ + bRInner );
  cons.SetOuterRadiusPlusZ( aROuter * xPlusZ + bROuter );
 
  G4double pDz = fwidth / 2.;
  G4double pSPhi = msol->GetStartPhiAngle();
  G4double pDPhi = msol->GetDeltaPhiAngle();

  cons.SetZHalfLength( pDz );
  cons.SetStartPhiAngle( pSPhi );
  cons.SetDeltaPhiAngle( pDPhi );

#ifdef G4DIVDEBUG
  if( verbose >= 2 )
  {
    G4cout << " G4ParameterisationConsZ::ComputeDimensions()" << G4endl
           << " pDz: " << pDz << G4endl;
    if( verbose >= 4 ) cons.DumpInfo();
  }
#endif
}
