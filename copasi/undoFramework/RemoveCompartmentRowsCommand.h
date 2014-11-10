// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveCompartmentRowsCommand.h
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#ifndef REMOVECOMPARTMENTROWSCOMMAND_H_
#define REMOVECOMPARTMENTROWSCOMMAND_H_

#include <set>

#include "CCopasiUndoCommand.h"

class CCopasiObject;

class RemoveCompartmentRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveCompartmentRowsCommand(QModelIndexList rows, CQCompartmentDM * pCompartmentDM, const QModelIndex&);
  void redo();
  void undo();

  QString removeCompartmentRowsText() const;
  virtual ~RemoveCompartmentRowsCommand();

private:
  CQCompartmentDM *mpCompartmentDM;
  QModelIndexList mRows;
  QList <UndoCompartmentData *> mpCompartmentData;

  bool mFirstTime;
};

#endif /* REMOVECOMPARTMENTROWSCOMMAND_H_ */
