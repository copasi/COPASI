// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include "model/CCompartment.h"
#include "UndoData.h"

#include <QList>

class UndoReactionData;
class UndoSpeciesData;
class UndoGlobalQuantityData;
class UndoEventData;

class UndoCompartmentData : public UndoData
{
public:
  UndoCompartmentData();

  UndoCompartmentData(const CCompartment* compartment, bool trackDependencies = true);

  virtual ~UndoCompartmentData();

  virtual CCompartment* createObjectIn(CModel* pModel);

  virtual CCompartment* restoreObjectIn(CModel* pModel);

  virtual void fillObject(CModel* pModel);

  CModelEntity::Status getStatus() const;
  void setStatus(CModelEntity::Status status);

  double getInitialValue() const;
  void setInitialValue(double initialValue);

  const std::string& getInitialExpression() const;
  void setInitialExpression(const std::string &initialExpression);

  const std::string& getExpression() const;
  void setExpression(const std::string &expression);

private:

  /**
   *  Initial volume of the compartment as double
   */
  double mInitialValue;

  /**
   * initial expression of the compartment
   */
  std::string mInitialExpression;

  /**
   * expression of the compartment
   */
  std::string mExpression;

  /**
   * The status of the metabolite
   */
  CModelEntity::Status mStatus;
};

#endif /* UNDOCOMPARTMENTDATA_H_ */
