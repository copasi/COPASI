// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteGlobalQuantityCommand.h
 *
 *  Created on: 11 Sep 2014
 *      Author: dada
 */

#ifndef DELETEGLOBALQUANTITYCOMMAND_H_
#define DELETEGLOBALQUANTITYCOMMAND_H_

#include <set>

#include "CCopasiUndoCommand.h"

class UndoGlobalQuantityData;
class UndoReactionData;
class CQModelValue;

class DeleteGlobalQuantityCommand: public CCopasiUndoCommand
{
public:
  DeleteGlobalQuantityCommand(CQModelValue *pModelValue);
  virtual ~DeleteGlobalQuantityCommand();

  void redo();
  void undo();

private:
  UndoGlobalQuantityData *mpGlobalQuantityData;
  CQModelValue* mpModelValue;
};

#endif /* DELETEGLOBALQUANTITYCOMMAND_H_ */
