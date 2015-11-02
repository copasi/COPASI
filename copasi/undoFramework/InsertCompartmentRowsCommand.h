// Copyright (C) 2014 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertCompartmentRowsCommand.h
 *
 *  Created on: 15 Sep 2014
 *      Author: dada
 */

#ifndef INSERTCOMPARTMENTROWSCOMMAND_H_
#define INSERTCOMPARTMENTROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class UndoCompartmentData;
class CQCompartmentDM;

class InsertCompartmentRowsCommand: public CCopasiUndoCommand
{
public:
  /**
   * Creates a new compartment at the indicated position
   */
  InsertCompartmentRowsCommand(int position,
                               int rows,
                               CQCompartmentDM *pCompartmentDM);

  InsertCompartmentRowsCommand(int position,
                               int rows,
                               CQCompartmentDM *pCompartmentDM,
                               const QModelIndex& index,
                               const QVariant& value);


  virtual ~InsertCompartmentRowsCommand();

  void redo();
  void undo();

private:
  CQCompartmentDM* mpCompartmentDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  UndoCompartmentData* mpCompartmentData;
  QVariant mValue;
};

#endif /* INSERTCOMPARTMENTROWSCOMMAND_H_ */
