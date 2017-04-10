// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteEventCommand.h
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#ifndef DELETEEVENTCOMMAND_H_
#define DELETEEVENTCOMMAND_H_

#include "CCopasiUndoCommand.h"

class UndoEventData;
class CQEventWidget1;

class DeleteEventCommand: public CCopasiUndoCommand
{
public:
  DeleteEventCommand(CQEventWidget1 *pEventWidget1);
  virtual ~DeleteEventCommand();

  void redo();
  void undo();

private:
  UndoEventData *mpEventData;
  CQEventWidget1* mpEVentWidget1;
};

#endif /* DELETEEVENTCOMMAND_H_ */
