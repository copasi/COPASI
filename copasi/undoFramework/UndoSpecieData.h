// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * UndoSpecieData.h
 *
 *  Created on: 26 Aug 2014
 *      Author: dada
 */

#ifndef UNDOSPECIEDATA_H_
#define UNDOSPECIEDATA_H_

#include <string>

#include "qtUtilities.h"
#include "UndoData.h"

class CMetab;
class UndoReactionData;
class UndoGlobalQuantityData;
class UndoEventData;

class UndoSpecieData: public UndoData
{
public:
  UndoSpecieData();
  virtual ~UndoSpecieData();

  std::string getCompartment() const;
  double getIConc() const;
  void setCompartment(std::string compartment);
  void setIConc(double iConc);
  const std::string & getExpression() const;
  const std::string &getInitialExpression() const;
  void setExpression(const std::string & expression);
  void setInitialExpression(const std::string &initialExpression);
  CModelEntity::Status getStatus() const;
  void setStatus(CModelEntity::Status status);
  QList<UndoReactionData*> *getReactionDependencyObjects() const;
  void setReactionDependencyObjects(QList<UndoReactionData*> *reactionDependencyObjects);
  double getINumber() const;
  void setINumber(double iNumber);
  QList<UndoGlobalQuantityData*> *getGlobalQuantityDependencyObjects() const;
  void setGlobalQuantityDependencyObjects(QList<UndoGlobalQuantityData*> *globalQuantityDependencyObjects);
  QList<UndoEventData*> *getEventDependencyObjects() const;
  void setEventDependencyObjects(QList<UndoEventData*> *eventDependencyObjects);

private:
  /**
   *  Initial concentration of the species as double
   */
  double mIConc;
  /**
   *  Initial particle numbers of the species as double
   */
  double mINumber;
  /**
   *  The compartment the species is located in.
   */
  std::string mCompartment;
  /**
   * The status of the metabolite
   */
  CModelEntity::Status mStatus;
  /**
   * the initial expression if it exist
   */
  std::string mInitialExpression;
  /**
   *  the expression if it exist
   */
  std::string mExpression;
  /**
   * Pointer to species dependency objects
   */
  QList<UndoReactionData*> *mReactionDependencyObjects;
  /**
   * Pointer to global quantity dependency objects
   */
  QList<UndoGlobalQuantityData*> *mGlobalQuantityDependencyObjects;
  /**
   * Pointer to event dependency objects
   */
  QList<UndoEventData*> *mEventDependencyObjects;
};

#endif /* UNDOSPECIEDATA_H_ */
