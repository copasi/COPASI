// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteCompartmentCommand.h
 *
 *  Created on: 16 Sep 2014
 *      Author: dada
 */

#ifndef DELETECOMPARTMENTCOMMAND_H_
#define DELETECOMPARTMENTCOMMAND_H_

#include "CCopasiUndoCommand.h"

class UndoCompartmentData;
class CQCompartment;

class DeleteCompartmentCommand: public CCopasiUndoCommand
{
public:
  DeleteCompartmentCommand(CQCompartment *pCompartment);
  virtual ~DeleteCompartmentCommand();

  void redo();
  void undo();

private:
  bool mFirstTime;
  UndoCompartmentData *mpCompartmentData;
  CQCompartment* mpCompartment;
};

#endif /* DELETECOMPARTMENTCOMMAND_H_ */
