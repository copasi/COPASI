// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "UndoData.h"

#include <copasi/model/CModelValue.h>

class CMetab;

class UndoSpeciesData: public UndoData
{
public:
  UndoSpeciesData(const CMetab* metab, bool trackDependencies = true);

  virtual ~UndoSpeciesData();

  virtual CCopasiObject* createObjectIn(CModel* pModel);

  virtual CCopasiObject* restoreObjectIn(CModel* pModel);

  virtual void fillObject(CModel* pModel);

  virtual void createDependentObjects(CModel* pModel);

  const std::string& getCompartment() const;
  void setCompartment(const std::string& compartment);

  double getIConc() const;
  void setIConc(double iConc);

  const std::string & getExpression() const;
  void setExpression(const std::string & expression);

  const std::string &getInitialExpression() const;
  void setInitialExpression(const std::string &initialExpression);

  CModelEntity::Status getStatus() const;
  void setStatus(CModelEntity::Status status);

  double getINumber() const;
  void setINumber(double iNumber);

  bool getCreatedCompartment() const;
  void setCreatedCompartment(bool createdCompartment);

  /**
   * @param pModel the model to use as base for the search
   * @returns the resolved object (from CN) if found,
   *          if it is not found the index of the metabolite in the
   *          models list of metabolites will be used, otherwise NULL is returned.
   */
  virtual CCopasiObject * getObject(CModel* pModel);

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

  bool mCreatedCompartment;

  /**
   * @the index of this metabolite in the models list of metabolites mIndex
   */
  std::size_t mIndex;
};

#endif /* UNDOSPECIEDATA_H_ */
