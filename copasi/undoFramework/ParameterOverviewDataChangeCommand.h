// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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
  ParameterOverviewDataChangeCommand(const QModelIndex &index, const QVariant &value, int role, CQParameterOverviewDM *pParameterOverviewDM);
  void redo();
  void undo();
  QString parameterOverviewDataChangeText() const;
  virtual ~ParameterOverviewDataChangeCommand();

private:
  QVariant mNew, mOld;
  QModelIndex mIndex;
  CQParameterOverviewDM *mpParameterOverviewDM;
  int mRole;
  Path mPathIndex;
  bool mFirstTime;
};

#endif /* PARAMETEROVERVIEWDATACHANGECOMMAND_H_ */
