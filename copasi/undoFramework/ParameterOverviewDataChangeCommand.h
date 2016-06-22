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
  ParameterOverviewDataChangeCommand(const std::string& cn,
                                     const std::string& name,
                                     const QVariant &newValue,
                                     const QVariant &oldValue,
                                     CQParameterOverviewDM *pParameterOverviewDM,
                                     const std::string& parametersetKey,
                                     int column);

  virtual ~ParameterOverviewDataChangeCommand();

  void redo();
  void undo();

  bool matches(const std::string &cn,
               const std::string& name,
               const QVariant &newValue,
               const QVariant &oldValue,
               const std::string& parametersetKey) const;

private:
  QVariant mNew, mOld;
  std::string mCN;
  CQParameterOverviewDM *mpParameterOverviewDM;
  std::string mParametersetKey;
  int mColumn;
};

#endif /* PARAMETEROVERVIEWDATACHANGECOMMAND_H_ */
