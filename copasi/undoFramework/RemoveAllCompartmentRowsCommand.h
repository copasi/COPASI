// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllCompartmentRowsCommand.h
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#ifndef REMOVEALLCOMPARTMENTROWSCOMMAND_H_
#define REMOVEALLCOMPARTMENTROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class UndoCompartmentData;

class RemoveAllCompartmentRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveAllCompartmentRowsCommand(CQCompartmentDM * pCompartmentDM, const QModelIndex&);
  void redo();
  void undo();

  QString removeAllCompartmentRowsText() const;

  virtual ~RemoveAllCompartmentRowsCommand();

private:
  CQCompartmentDM *mpCompartmentDM;
  QList <UndoCompartmentData *> mpCompartmentData;
};

#endif /* REMOVEALLCOMPARTMENTROWSCOMMAND_H_ */
