// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelMerging.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2009/07/07 09:44:50 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMODELMERGING_H
#define CMODELMERGING_H

#include <string>
#include <map>

class CModel;
class CCompartment;
class CReaction;
class CMetab;
class CModelEntity;
class CExpression;

class CModelMerging
{
public:
  CModelMerging(CModel* pModel, CModel* mModel);

  void setModel(CModel* pModel, CModel* mModel);

  ///just a simple method to call during development
  void simpleCall();

protected:

  std::map<std::string, std::string> keyMap;
  std::map<std::string, std::string> nameMap;

  bool  addCompartments(std::string name);
  bool  addMetabolites(std::string name);
  bool  addModelValues(std::string name);
  bool  addReactions(std::string name);
  bool  copyExpression(const CModelEntity * sourceEntity, CModelEntity * newEntity);

  /**
   * determine whether the one of the substrate, products, or modifiers of the reaction
   * is located in the given compartmen
   */
  static bool reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp);

  CModel * mpModel;
  CModel * mmModel;
};

#endif // CMODELMERGING_H
