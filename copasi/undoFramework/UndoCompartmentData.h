// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoCompartmentData.h
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#ifndef UNDOCOMPARTMENTDATA_H_
#define UNDOCOMPARTMENTDATA_H_

#include "UndoData.h"

class UndoReactionData;
class UndoSpecieData;

class UndoCompartmentData : public UndoData
{
public:
  UndoCompartmentData();
  virtual ~UndoCompartmentData();
  QList<UndoData*> *getDependencyObjects() const;
  CModelEntity::Status getStatus() const;
  void setDependencyObjects(QList<UndoData*> *dependencyObjects);
  void setStatus(CModelEntity::Status status);
  QList<UndoReactionData*> *getReactionDependencyObjects() const;
  QList<UndoSpecieData*> *getSpecieDependencyObjects() const;
  void setReactionDependencyObjects(QList<UndoReactionData*> *reactionDependencyObjects);
  void setSpecieDependencyObjects(QList<UndoSpecieData*> *specieDependencyObjects);
  double getInitialValue() const;
  void setInitialValue(double initialValue);

private:
  /**
  Value() const;
  void setInitialValue(double initialValue);
  private:
  /**
   *  Initial volume of the compartment as double
   */
  double mInitialValue;
  /**
  * The status of the metabolite
  */
  CModelEntity::Status mStatus;
  /**
  * Pointer to species dependency objects
  */
  QList<UndoData*> *mDependencyObjects;
  /**
  * Pointer to species dependency objects
  */
  QList<UndoSpecieData*> *mSpecieDependencyObjects;
  /**
  * Pointer to species dependency objects
  */
  QList<UndoReactionData*> *mReactionDependencyObjects;
};

#endif /* UNDOCOMPARTMENTDATA_H_ */
