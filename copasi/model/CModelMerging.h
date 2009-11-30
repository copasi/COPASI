// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelMerging.h,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2009/11/30 13:17:58 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CMODELMERGING_H
#define CMODELMERGING_H

#include <string>
#include <map>
#include <vector>

class CModel;
class CCompartment;
class CReaction;
class CMetab;
class CModelEntity;
class CExpression;
class CEvent;
class CEventAssignment;

class CModelAdd
{
public:
  CModelAdd(CModel* pModel, CModel* mModel);

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

  /**
   * determine whether the one of the substrate, products, or modifiers of the reaction
   * is located in the given compartment
   */
  static bool reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp);

  CModel * mpModel;
  CModel * mmModel;
};

class CModelMerging
{
public:
  CModelMerging(CModel* pModel);

  void setModel(CModel* pModel);

  ///just a simple method to call during development
  void simpleCall(std::vector< std::string > & toKey, std::vector< std::string > & objectKey);

  /**
  ** Enumeration of the types of columns known to COPASI.
  **/
  enum Type
  {
    ignore = 0,
    merge
  };

  /**
  ** String literals for the GUI to display type names of columns known
  ** to COPASI.
  **/
  static const std::string TypeName[];

protected:

  bool  mergeMetabolites(std::string toKey, std::string key);
  bool  mergeInExpression(std::string toKey, std::string key, CExpression *pExpression);

  CModel * mpModel;
};

#endif // CMODELMERGING_H
