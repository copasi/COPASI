// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewEventCommand.h
 *
 *  Created on: 14 Oct 2014
 *      Author: dada
 */

#ifndef CREATENEWEVENTCOMMAND_H_
#define CREATENEWEVENTCOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQEventWidget1;
class UndoEventData;

class CreateNewEventCommand: public CCopasiUndoCommand
{
public:
  CreateNewEventCommand(CQEventWidget1 *pEventsWidget);
  virtual ~CreateNewEventCommand();

  void redo();
  void undo();


private:
  UndoEventData *mpEventData;
  CQEventWidget1* mpEventWidget;
};

#endif /* CREATENEWEVENTCOMMAND_H_ */
