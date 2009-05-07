// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelExpansion.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2009/05/07 19:04:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMODELEXPANSION_H
#define CMODELEXPANSION_H

#include <string>
#include <map>

class CModel;
class CCompartment;
class CReaction;

class CModelExpansion
{
public:
  CModelExpansion(CModel* pModel);

  void setModel(CModel* pModel);

  ///just a simple method to call during development
  void simpleCall();

protected:

  class CompartmentInfo
  {
  public:
    CompartmentInfo() {};

    std::map<std::string, std::string> metabMap;
    std::string key;
  };

  CompartmentInfo copyCompartment(const CCompartment* source, std::string name) const;

  /**
   * determine whether the one of the substrate, products, or modifiers of the reaction
   * is located in the given compartmen
   */
  static bool reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp);

  CModel * mpModel;
};

#endif // CMODELEXPANSION_H
