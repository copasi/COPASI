// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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
  void redo();
  void undo();
  QString deleteEventText(std::string &name) const;
  UndoData *getUndoData() const;
  virtual ~DeleteEventCommand();

private:
  bool mFirstTime;
  UndoEventData *mpEventData;
  CQEventWidget1* mpEVentWidget1;
};

#endif /* DELETEEVENTCOMMAND_H_ */
