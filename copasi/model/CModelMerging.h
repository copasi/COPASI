// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelMerging.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2009/07/20 11:57:15 $
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
class CEvent;
class CEventAssignment;

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

  bool  addCompartmentsExpressions();
  bool  addMetabolitesExpressions();
  bool  addModelValuesExpressions();

  bool  addReactions(std::string name);
  bool  addEvents(std::string name);

  bool  copyEventAssignmentExpression(const CEventAssignment * sourceAssignment, CEventAssignment * newAssignment);
  bool  copyDelayExpression(const CEvent * sourceEvent, CEvent * newEvent);
  bool  copyTriggerExpression(const CEvent * sourceEvent, CEvent * newEvent);
  bool  copyExpression(const CModelEntity * sourceEntity, CModelEntity * newEntity);
  bool  copyInitialExpression(const CModelEntity * sourceEntity, CModelEntity * newEntity);

  bool  mergeMetabolites(std::string toKey, std::string key);
  bool mergeInExpression(std::string toKey, std::string key, CExpression *pExpression);

  /**
   * determine whether the one of the substrate, products, or modifiers of the reaction
   * is located in the given compartmen
   */
  static bool reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp);

  CModel * mpModel;
  CModel * mmModel;
};

#endif // CMODELMERGING_H
