// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CreateNewCompartmentCommand.h
 *
 *  Created on: 16 Sep 2014
 *      Author: dada
 */

#ifndef CREATENEWCOMPARTMENTCOMMAND_H_
#define CREATENEWCOMPARTMENTCOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQCompartment;
class UndoCompartmentData;

class CreateNewCompartmentCommand: public CCopasiUndoCommand
{
public:
  CreateNewCompartmentCommand(CQCompartment *pCompartment);
  void redo();
  void undo();
  QString createNewCompartmentText() const;
  virtual ~CreateNewCompartmentCommand();
  void setType(const CreateNewCompartmentCommand::Type & type);
  CreateNewCompartmentCommand * getCreateNewCompartmentCommand() {return this; };
  UndoData *getUndoData() const;

private:
  UndoCompartmentData *mpCompartmentData;
  CQCompartment* mpCompartment;
};

#endif /* CREATENEWCOMPARTMENTCOMMAND_H_ */
