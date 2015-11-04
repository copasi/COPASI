// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include <copasi/model/CModelValue.h>

class CMetab;

class UndoSpeciesData: public UndoData
{
public:
  UndoSpeciesData(const std::string &key = "",
                  const std::string &name = "",
                  const std::string &type = "");

  UndoSpeciesData(const CMetab* metab, bool trackDependencies = true);

  virtual ~UndoSpeciesData();

  virtual CMetab* createObjectIn(CModel* pModel);

  virtual CMetab* restoreObjectIn(CModel* pModel);

  virtual void fillObject(CModel* pModel);

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

};

#endif /* UNDOSPECIEDATA_H_ */
