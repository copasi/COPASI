// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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

  QString removeCompartmentRowsText() const;

  UndoData *getUndoData() const;



private:
  QModelIndexList mRows;
  CQCompartmentDM *mpCompartmentDM;
  QList <UndoCompartmentData *> mpCompartmentData;

  bool mFirstTime;
};

#endif /* REMOVECOMPARTMENTROWSCOMMAND_H_ */
