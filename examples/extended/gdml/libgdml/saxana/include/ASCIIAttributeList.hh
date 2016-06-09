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
// $Id: ASCIIAttributeList.hh,v 1.2 2002/06/03 12:09:32 radoone Exp $
// GEANT4 tag $Name: geant4-06-00 $
//
// 
// --------------------------------------------------------------
// Comments
//
// --------------------------------------------------------------
//
#ifndef ASCIIATTRIBUTE_LIST_H
#define ASCIIATTRIBUTE_LIST_H 1

/// Include files
#include <string>
#include <vector>

/// Class simulating behavior of real SAX XML attribute list,
/// but using 8 bit ASCII encoding
class ASCIIAttributeList
{
public:

  std::string sEmpty;

  /// XML ASCII attribute
  struct _attrItem
  {
    std::string fName;
    std::string fValue;
    std::string fType;
  };
  
  /// Constructor
  ASCIIAttributeList()
  {
    sEmpty = "";
  }

  /// Desctructor
  ~ASCIIAttributeList()
  {
  }

  /// Add a whole attribute item into the list
  void add( const ASCIIAttributeList::_attrItem& item )
  {
    fList.push_back( item );
  }
  
  /// Add an attribute item into the list specified by its constituting parts
  void add( const char* const name, const char* const value, const char* const type )
  {
    struct _attrItem att;
    att.fName  = name;
    att.fValue = value;
    att.fType  = type;
    fList.push_back( att );
  }
  
  /// Get attribute parameters by the given index in the list
  const std::string& getName( unsigned int index )                          
  {
    return fList[index].fName;
  }
  
  /// Get attribute parameters by the given index in the list
  const std::string& getValue( unsigned int index )                         
  {
    return fList[index].fValue;
  }
  
  /// Get attribute parameters by the given index in the list
  const std::string& getType( unsigned int index )                          
  {
    return fList[index].fType;
  }

  /// Get attribute parameters by the attribute's name
  const std::string& getValue( const std::string& name ) const
  {
    std::vector<struct _attrItem>::const_iterator aiter;
    bool success = false;

    for( aiter = fList.begin(); aiter != fList.end(); aiter++ )           
    {
      if( (*aiter).fName == name)                                          
      {
        success = true;
        break;
      }
    }
    return( success ? (*aiter).fValue : sEmpty );
  }
  
  /// Get attribute parameters by the attribute's name
  const std::string& getValue( const char* name ) const              
  {
    std::vector<struct _attrItem>::const_iterator aiter;
    bool success = false;

    for( aiter = fList.begin(); aiter != fList.end(); aiter++ )           
    {
      if( (*aiter).fName == name)                                          
      {
        success = true;
        break;
      }
    }
    return( success ? (*aiter).fValue : sEmpty );
  }

  /// Get attribute parameters by the attribute's name
  const std::string& getType( const std::string& name )                     
  {
    std::vector<struct _attrItem>::iterator aiter;
    bool success = false;

    for( aiter = fList.begin(); aiter != fList.end(); aiter++ )           
    {
      if( (*aiter).fName == name)                                          
      {
        success = true;
        break;
      }
    }
    return( success ? (*aiter).fType : sEmpty );
  }
  
  /// Get attribute parameters by the attribute's name
  const std::string& getType( const char* name )                            
  {
    std::vector<struct _attrItem>::iterator aiter;
    bool success = false;

    for( aiter = fList.begin(); aiter != fList.end(); aiter++ )           
    {
      if( (*aiter).fName == name)                                          
      {
        success = true;
        break;
      }
    }
    return( success ? (*aiter).fType : sEmpty );
  }

  /// Get the number of attributes in the list
  unsigned int getLength()                                                  
  {
    return fList.size();
  }
  
private:
    
  /// Attribute List Container
  std::vector<struct _attrItem> fList;
};

#endif // ASCIIATTRIBUTE_LIST_H

