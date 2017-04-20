// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef UNDODEPENDENTDATA_H_
#define UNDODEPENDENTDATA_H_

#include <QList>
#include <set>

class CModelEntity;
class CDataObject;
class UndoCompartmentData;
class UndoReactionData;
class UndoSpeciesData;
class UndoGlobalQuantityData;
class UndoEventData;
class CReaction;
class CModel;
/**
 * @brief The UndoDependentData class holds additional dependencies
 *
 * UndoDependentData is there for the species, compartment, parameter
 * classes, such that all dependent model elements can be reverted when
 * necessary.
 *
 */
class UndoDependentData
{
public:
  UndoDependentData();
  UndoDependentData(const CModelEntity* pObject);

  virtual ~UndoDependentData();

  void initializeFrom(const std::set< const CDataObject * > & deletedObjects);
  void initializeFrom(const CModelEntity* pObject);
  void initializeFrom(const CReaction* pObject);

  void fillIn(CModel* pModel);
  void createIn(CModel* pModel);
  void restoreIn(CModel* pModel);

  void freeUndoData();

  static void restoreDependentObjects(CModel* pModel,
                                      QList <UndoGlobalQuantityData *> *pGlobalQuantityData);
  static void restoreDependentObjects(CModel* pModel,
                                      QList <UndoReactionData *> *pReactionData);
  static void restoreDependentObjects(CModel* pModel,
                                      QList <UndoEventData *> *pEventData);
  static void restoreDependentObjects(CModel* pModel,
                                      QList <UndoSpeciesData *> *pSpeciesData);
  static void restoreDependentObjects(CModel* pModel,
                                      QList <UndoCompartmentData *> *pCompartmentData);

  static void createDependentObjects(CModel* pModel,
                                     QList <UndoGlobalQuantityData *> *pGlobalQuantityData);
  static void createDependentObjects(CModel* pModel,
                                     QList <UndoReactionData *> *pReactionData);
  static void createDependentObjects(CModel* pModel,
                                     QList <UndoEventData *> *pEventData);
  static void createDependentObjects(CModel* pModel,
                                     QList <UndoSpeciesData *> *pSpeciesData);
  static void createDependentObjects(CModel* pModel,
                                     QList <UndoCompartmentData *> *pCompartmentData);

  static void fillDependentObjects(CModel* pModel,
                                   QList <UndoGlobalQuantityData *> *pGlobalQuantityData);
  static void fillDependentObjects(CModel* pModel,
                                   QList <UndoReactionData *> *pReactionData);
  static void fillDependentObjects(CModel* pModel,
                                   QList <UndoEventData *> *pEventData);
  static void fillDependentObjects(CModel* pModel,
                                   QList <UndoSpeciesData *> *pSpeciesData);
  static void fillDependentObjects(CModel* pModel,
                                   QList <UndoCompartmentData *> *pCompartmentData);

protected:
  QList<UndoCompartmentData*> mCompartmentData;
  QList<UndoReactionData*> mReactionData;
  QList<UndoSpeciesData*> mSpeciesData;
  QList<UndoGlobalQuantityData*> mParameterData;
  QList<UndoEventData*> mEventData;
};

#endif /* UNDODEPENDENTDATA_H_ */
