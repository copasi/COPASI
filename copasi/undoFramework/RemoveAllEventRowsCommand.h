// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveAllEventRowsCommand.h
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#ifndef REMOVEALLEVENTROWSCOMMAND_H_
#define REMOVEALLEVENTROWSCOMMAND_H_

#include <set>

#include "CCopasiUndoCommand.h"

class RemoveAllEventRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveAllEventRowsCommand(CQEventDM * pEventDM, const QModelIndex&);
  void redo();
  void undo();

  QString removeAllEventRowsText() const;

  virtual ~RemoveAllEventRowsCommand();

private:
  CQEventDM *mpEventDM;
  QList <UndoEventData *> mpEventData;
};

#endif /* REMOVEALLEVENTROWSCOMMAND_H_ */
