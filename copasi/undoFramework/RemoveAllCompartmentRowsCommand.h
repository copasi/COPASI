// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
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
class CQCompartmentDM;

class RemoveAllCompartmentRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveAllCompartmentRowsCommand(CQCompartmentDM * pCompartmentDM, const QModelIndex&);
  virtual ~RemoveAllCompartmentRowsCommand();

  void redo();
  void undo();

  QString removeAllCompartmentRowsText() const;


private:
  CQCompartmentDM *mpCompartmentDM;
  QList <UndoCompartmentData *> mpCompartmentData;
};

#endif /* REMOVEALLCOMPARTMENTROWSCOMMAND_H_ */
