// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

class UndoReactionData;
class ReactionsWidget1;

class CreateNewReactionCommand: public CCopasiUndoCommand
{
public:
  CreateNewReactionCommand(ReactionsWidget1 *pReactionWidget);
  virtual ~CreateNewReactionCommand();

  void redo();
  void undo();

private:
  ReactionsWidget1* mpReactionWidget;
  UndoReactionData *mpReactionData;
};

#endif /* CREATENEWREACTIONCOMMAND_H_ */
