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
class CModel;

class UndoGlobalQuantityData: public UndoData
{
public:
  UndoGlobalQuantityData(const std::string &key = "",
                         const std::string &name = "",
                         const std::string &type = "");

  UndoGlobalQuantityData(const CModelValue* pModelValue);

  CModelValue* createQuantityFromData(CModel* pModel);

  virtual ~UndoGlobalQuantityData();

  double getInitialValue() const;
  void setInitialValue(double initialValue);

  CModelEntity::Status getStatus() const;
  void setStatus(CModelEntity::Status status);

  const std::string & getExpression() const;
  void setExpression(const std::string & expression);

  const std::string &getInitialExpression() const;
  void setInitialExpression(const std::string &initialExpression);

  QList<UndoReactionData*> *getReactionDependencyObjects() const;

  QList<UndoEventData*> *getEventDependencyObjects() const;

  QList<UndoSpeciesData*> *getSpecieDependencyObjects() const;

private:

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
