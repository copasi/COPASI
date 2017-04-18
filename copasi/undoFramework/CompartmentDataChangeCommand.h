// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CompartmentDataChangeCommand.h
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#ifndef COMPARTMENTDATACHANGECOMMAND_H_
#define COMPARTMENTDATACHANGECOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQCompartmentDM;
class UndoCompartmentData;

class CompartmentDataChangeCommand: public CCopasiUndoCommand
{
public:
  CompartmentDataChangeCommand(const QModelIndex& index,
                               const QVariant& value,
                               CQCompartmentDM *pCompartmentDM);
  virtual ~CompartmentDataChangeCommand();

  void redo();
  void undo();

private:
  QVariant mNew, mOld;
  QModelIndex mIndex;
  CQCompartmentDM *mpCompartmentDM;
  UndoCompartmentData* mpCompartmentUndoData;
};

#endif /* COMPARTMENTDATACHANGECOMMAND_H_ */
