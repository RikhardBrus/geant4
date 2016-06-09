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
// $Id: positionrefProcess.cc,v 1.2 2002/06/03 12:09:32 radoone Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
// 
// --------------------------------------------------------------
// Comments
//
// --------------------------------------------------------------
//
#include "ReferenceTypeProcess.hh"

#include "BooleanSolidType.hh"

#include <cstdlib>
#include <iostream>

class positionrefProcess : public ReferenceTypeProcess
{
public:
  positionrefProcess( const ProcessingContext* context = 0 )
  : ReferenceTypeProcess( context ) {
  }
  
  virtual ~positionrefProcess() {
  }
  
  // Analogical to SAX startElement callback
  virtual void StartElement( const std::string& name, const ASCIIAttributeList& attrs )
  {    
    SAXObject** obj = Context()->GetTopObject();
    
    BooleanSolidType::positionref* co = new BooleanSolidType::positionref;
    
    *obj = co;
    m_obj = co;
    
    ReferenceTypeProcess::StartElement( name, attrs );
  }
  
  // Analogical to SAX endElement callback
  virtual void EndElement( const std::string& name ) {
    ReferenceTypeProcess::EndElement( name );
  }
  
  // The name of the state this object will process
  virtual const std::string& State() const {
    static std::string tag = "positionref";
    return tag;
  }
};

DECLARE_PROCESS_FACTORY(positionrefProcess)

