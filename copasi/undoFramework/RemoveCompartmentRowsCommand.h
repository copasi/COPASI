// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
class UndoCompartmentData;
class CQCompartmentDM;

class RemoveCompartmentRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveCompartmentRowsCommand(
    const QModelIndexList& rows,
    CQCompartmentDM* pCompartmentDM);
  virtual ~RemoveCompartmentRowsCommand();

  void redo();
  void undo();

private:
  QModelIndexList mRows;
  CQCompartmentDM *mpCompartmentDM;
  QList <UndoCompartmentData *> mpCompartmentData;
};

#endif /* REMOVECOMPARTMENTROWSCOMMAND_H_ */
