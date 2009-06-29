// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelMerging.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2009/06/29 10:51:55 $
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

class CModelMerging
{
public:
  CModelMerging(CModel* pModel, CModel* mModel);

  void setModel(CModel* pModel, CModel* mModel);

  ///just a simple method to call during development
  void simpleCall();

protected:

  class MergingInfo
  {
  public:
    MergingInfo() {};

    std::map<std::string, std::string> metabMap;
    std::string key;
  };

  MergingInfo addCompartments(std::string name) const;
  MergingInfo addMetabolitesAndReactions(std::string name) const;

  /**
   * determine whether the one of the substrate, products, or modifiers of the reaction
   * is located in the given compartmen
   */
  static bool reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp);

  CModel * mpModel;
  CModel * mmModel;
};

#endif // CMODELMERGING_H
