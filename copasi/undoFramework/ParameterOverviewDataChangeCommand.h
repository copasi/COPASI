// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * ParameterOverviewDataChangeCommand.h
 *
 *  Created on: 19 Sep 2014
 *      Author: dada
 */

#ifndef PARAMETEROVERVIEWDATACHANGECOMMAND_H_
#define PARAMETEROVERVIEWDATACHANGECOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQParameterOverviewDM;
class CModelParameterGroup;

class ParameterOverviewDataChangeCommand: public CCopasiUndoCommand
{
public:
  ParameterOverviewDataChangeCommand(const QModelIndex &index,
                                     const std::string& name,
                                     const QVariant &newValue,
                                     const QVariant &oldValue,
                                     CQParameterOverviewDM *pParameterOverviewDM,
                                     const std::string& parametersetKey);
  virtual ~ParameterOverviewDataChangeCommand();

  void redo();
  void undo();

private:
  QVariant mNew, mOld;
  QModelIndex mIndex;
  CQParameterOverviewDM *mpParameterOverviewDM;
  Path mPathIndex;
  std::string mParametersetKey;
};

#endif /* PARAMETEROVERVIEWDATACHANGECOMMAND_H_ */
