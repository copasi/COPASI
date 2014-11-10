// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewReactionCommand.h
 *
 *  Created on: 23 Jul 2014
 *      Author: dada
 */

#ifndef CREATENEWREACTIONCOMMAND_H_
#define CREATENEWREACTIONCOMMAND_H_

#include "CCopasiUndoCommand.h"

class CreateNewReactionCommand: public CCopasiUndoCommand
{
public:
  CreateNewReactionCommand(ReactionsWidget1 *pReactionWidget);
  void redo();
  void undo();
  QString createNewReactionText() const;
  virtual ~CreateNewReactionCommand();

private:
  ReactionsWidget1* mpReactionWidget;
  CReaction *mpReaction;
};

#endif /* CREATENEWREACTIONCOMMAND_H_ */
