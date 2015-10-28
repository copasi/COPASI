// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.


#ifndef UNDODEPENDENTDATA_H_
#define UNDODEPENDENTDATA_H_

#include <QList>
#include <set>

class CModelEntity;
class CCopasiObject;
class UndoCompartmentData;
class UndoReactionData;
class UndoSpeciesData;
class UndoGlobalQuantityData;
class UndoEventData;

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
  UndoDependentData(CModelEntity* pObject);

  virtual ~UndoDependentData();

  void initializeFrom(const std::set< const CCopasiObject * > & deletedObjects);

protected:
  QList<UndoCompartmentData*> mCompartmentData;
  QList<UndoReactionData*> mReactionData;
  QList<UndoSpeciesData*> mSpeciesData;
  QList<UndoGlobalQuantityData*> mParameterData;
  QList<UndoEventData*> mEventData;
};

#endif /* UNDODEPENDENTDATA_H_ */
