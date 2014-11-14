// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

class UndoSpecieData;
class UndoEventData;
class UndoReactionData;
class CModelValue;

class UndoGlobalQuantityData: public UndoData
{
public:
  UndoGlobalQuantityData();
  virtual ~UndoGlobalQuantityData();
  double getInitialValue() const;
  CModelEntity::Status getStatus() const;
  void setInitialValue(double initialValue);
  void setStatus(CModelEntity::Status status);
  QList<UndoReactionData*> *getReactionDependencyObjects() const;
  void setReactionDependencyObjects(QList<UndoReactionData*> *reactionDependencyObjects);
  bool isFixed() const;
  void setFixed(bool fixed);

  const std::string & getExpression() const;
  void setExpression(const std::string & expression);
  CModelValue getModelValue() const;

  void setModelValue(CModelValue modelValue);
  const std::string &getInitialExpression() const;
  void setInitialExpression(const std::string &initialExpression);
  QList<UndoEventData*> *getEventDependencyObjects() const;
  QList<UndoSpecieData*> *getSpecieDependencyObjects() const;
  void setEventDependencyObjects(QList<UndoEventData*> *eventDependencyObjects);
  void setSpecieDependencyObjects(QList<UndoSpecieData*> *specieDependencyObjects);

private:
  CModelValue modelValue;
  /**
   * For Checking whether the entity is FIXED or not.
   */
  bool fixed;
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
  QList<UndoSpecieData*> *mSpecieDependencyObjects;
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
