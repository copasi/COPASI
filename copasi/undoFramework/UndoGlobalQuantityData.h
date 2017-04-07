// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

class CModelValue;
class CModel;

class UndoGlobalQuantityData: public UndoData
{
public:
  UndoGlobalQuantityData(const std::string &key = "",
                         const std::string &name = "",
                         const std::string &type = "");

  UndoGlobalQuantityData(const CModelValue* pModelValue, bool trackDependencies = true);

  virtual CCopasiObject* createObjectIn(CModel* pModel);

  virtual CCopasiObject* restoreObjectIn(CModel* pModel);

  virtual void fillObject(CModel* pModel);

  virtual ~UndoGlobalQuantityData();

  double getInitialValue() const;
  void setInitialValue(double initialValue);

  CModelEntity::Status getStatus() const;
  void setStatus(CModelEntity::Status status);

  const std::string & getExpression() const;
  void setExpression(const std::string & expression);

  const std::string &getInitialExpression() const;
  void setInitialExpression(const std::string &initialExpression);

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
};

#endif /* UNDOGLOBALQUANTITYDATA_H_ */
