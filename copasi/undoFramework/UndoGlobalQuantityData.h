// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoGlobalQuantityData.h
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#ifndef UNDOGLOBALQUANTITYDATA_H_
#define UNDOGLOBALQUANTITYDATA_H_

#include "qtUtilities.h"
#include "UndoData.h"

#include <copasi/model/CModelValue.h>

class UndoSpeciesData;
class UndoEventData;
class UndoReactionData;
class CModelValue;

class UndoGlobalQuantityData: public UndoData
{
public:
  UndoGlobalQuantityData(const std::string &key = "",
                         const std::string &name = "",
                         const std::string &type = "");
  virtual ~UndoGlobalQuantityData();

  double getInitialValue() const;
  void setInitialValue(double initialValue);

  CModelEntity::Status getStatus() const;
  void setStatus(CModelEntity::Status status);

  bool isFixed() const;
  void setFixed(bool mFixed);

  const std::string & getExpression() const;
  void setExpression(const std::string & expression);

  const CModelValue& getModelValue() const;
  void setModelValue(const CModelValue& mModelValue);

  const std::string &getInitialExpression() const;
  void setInitialExpression(const std::string &initialExpression);

  QList<UndoReactionData*> *getReactionDependencyObjects() const;
  void setReactionDependencyObjects(
    QList<UndoReactionData*> *reactionDependencyObjects);

  QList<UndoEventData*> *getEventDependencyObjects() const;
  void setEventDependencyObjects(
    QList<UndoEventData*> *eventDependencyObjects);

  QList<UndoSpeciesData*> *getSpecieDependencyObjects() const;
  void setSpecieDependencyObjects(
    QList<UndoSpeciesData*> *specieDependencyObjects);

private:
  CModelValue mModelValue;

  /**
   * For Checking whether the entity is FIXED or not.
   */
  bool mFixed;

  /**
   *  Initial value of the global quantity as double
   */
  double mInitialValue;

  /**
   * The status of the quantity
   */
  CModelEntity::Status mStatus;

  /**
   * The expression for non fixed value of quantity
   */
  std::string mExpression;

  /**
   * The initial expression for non fixed value of quantity
   */
  std::string mInitialExpression;

  /**
   * Pointer to species dependency objects
   */
  QList<UndoSpeciesData*> *mSpecieDependencyObjects;

  /**
   * Pointer to species dependency objects
   */
  QList<UndoReactionData*> *mReactionDependencyObjects;

  /**
   * Pointer to event dependency objects
   */
  QList<UndoEventData*> *mEventDependencyObjects;
};

#endif /* UNDOGLOBALQUANTITYDATA_H_ */
