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
// $Id: G4NeutronHPInterpolator.hh,v 1.15 2003/11/03 17:54:36 hpw Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
#ifndef G4NeutronHPInterpolator_h
#define G4NeutronHPInterpolator_h 1

#include "globals.hh"
#include "G4InterpolationScheme.hh"
#include "Randomize.hh"
#include "G4ios.hh"
#include "G4HadronicException.hh"


class G4NeutronHPInterpolator
{
  public:
  
  G4NeutronHPInterpolator(){}
  ~G4NeutronHPInterpolator()
   {
    //  G4cout <<"deleted the interpolator"<<G4endl;
   }
  
  inline G4double Lin(G4double x,G4double x1,G4double x2,G4double y1,G4double y2)
  {
    G4double slope=0, off=0;
    if(x2-x1==0) return (y2+y1)/2.;
    slope = (y2-y1)/(x2-x1);
    off = y2-x2*slope;
    G4double y = x*slope+off;
    return y;
  }
  
  inline G4double Interpolate(G4InterpolationScheme aScheme,
                              G4double x, G4double x1, G4double x2,
                                          G4double y1, G4double y2) const;       
  
  G4double 
  GetBinIntegral(const G4InterpolationScheme & aScheme, 
                const G4double x1,const G4double x2,const G4double y1,const G4double y2);

  G4double 
  GetWeightedBinIntegral(const G4InterpolationScheme & aScheme, 
                const G4double x1,const G4double x2,const G4double y1,const G4double y2);

  private:
  
  inline G4double Histogram(G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const;
  inline G4double LinearLinear(G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const;
  inline G4double LinearLogarithmic(G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const;
  inline G4double LogarithmicLinear(G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const;
  inline G4double LogarithmicLogarithmic(G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const;
  inline G4double Random(G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const;

};

inline G4double G4NeutronHPInterpolator::
Interpolate(G4InterpolationScheme aScheme,
            G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const
{
  G4double result(0);
  G4int theScheme = aScheme;
  theScheme = theScheme%CSTART;
  switch(theScheme)
  {
    case 1:
      result = Histogram(x, x1, x2, y1, y2);
      break;
    case 2:
      result = LinearLinear(x, x1, x2, y1, y2);
      break;
    case 3:
      result = LinearLogarithmic(x, x1, x2, y1, y2);
      break;
    case 4:
      result = LogarithmicLinear(x, x1, x2, y1, y2);
      break;
    case 5:
      result = LogarithmicLogarithmic(x, x1, x2, y1, y2);
      break;
    case 6:
      result = Random(x, x1, x2, y1, y2);
      break;
    default:
      G4cout << "theScheme = "<<theScheme<<G4endl;
      throw G4HadronicException(__FILE__, __LINE__, "G4NeutronHPInterpolator::Carthesian Invalid InterpolationScheme");
      break;
  }
  return result;
}

inline G4double G4NeutronHPInterpolator::
Histogram(G4double , G4double , G4double , G4double y1, G4double ) const
{
  G4double result;
  result = y1;
  return result;
}

inline G4double G4NeutronHPInterpolator::
LinearLinear(G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const
{
  G4double slope=0, off=0;
  if(x2-x1==0) return (y2+y1)/2.;
  slope = (y2-y1)/(x2-x1);
  off = y2-x2*slope;
  G4double y = x*slope+off;
  return y;
}

inline G4double G4NeutronHPInterpolator::
LinearLogarithmic(G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const
{
  G4double result;
  if(x==0) result = y1+y2/2.;
  else if(x1==0) result = y1;
  else if(x2==0) result = y2;
  else result = LinearLinear(log(x), log(x1), log(x2), y1, y2);
  return result;
}
  
inline G4double G4NeutronHPInterpolator::
LogarithmicLinear(G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const
{
  G4double result;
  if(y1==0||y2==0) result = 0;
  else 
  {
    result = LinearLinear(x, x1, x2, log(y1), log(y2));
    result = exp(result);
  }
  return result;
}
  
inline G4double G4NeutronHPInterpolator::
LogarithmicLogarithmic(G4double x, G4double x1, G4double x2, G4double y1, G4double y2) const
{
  G4double result;
  if(x==0) result = y1+y2/2.;
  else if(x1==0) result = y1;
  else if(x2==0) result = y2;
  if(y1==0||y2==0) result = 0;
  else 
  {
    result = LinearLinear(log(x), log(x1), log(x2), log(y1), log(y2));
    result = exp(result);
  }
  return result;
}

inline G4double G4NeutronHPInterpolator::
Random(G4double , G4double , G4double , G4double y1, G4double y2) const
{
  G4double result;
  result = y1+G4UniformRand()*(y2-y1);
  return result;
}

#endif
