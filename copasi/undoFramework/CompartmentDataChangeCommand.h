// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CompartmentDataChangeCommand.h
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#ifndef COMPARTMENTDATACHANGECOMMAND_H_
#define COMPARTMENTDATACHANGECOMMAND_H_

#include "CCopasiUndoCommand.h"

class CompartmentDataChangeCommand: public CCopasiUndoCommand
{
public:
  CompartmentDataChangeCommand(QModelIndex index, const QVariant value, int role, CQCompartmentDM *pCompartmentDM);
  void redo();
  void undo();
  QString compartmentDataChangeText() const;

  virtual ~CompartmentDataChangeCommand();

private:
  QVariant mNew, mOld;
  QModelIndex mIndex;
  CQCompartmentDM *mpCompartmentDM;
  int mRole;
  Path mPathIndex;
};

#endif /* COMPARTMENTDATACHANGECOMMAND_H_ */
