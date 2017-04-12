// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * DeleteSpecieCommand.h
 *
 *  Created on: 2 Sep 2014
 *      Author: dada
 */

#ifndef DELETESPECIECOMMAND_H_
#define DELETESPECIECOMMAND_H_

#include <set>

#include "CCopasiUndoCommand.h"

class UndoSpeciesData;
class UndoReactionData;
class CQSpeciesDetail;

class DeleteSpeciesCommand: public CCopasiUndoCommand
{
public:
  DeleteSpeciesCommand(CQSpeciesDetail *pSpecieDetail);
  virtual ~DeleteSpeciesCommand();

  void redo();
  void undo();

private:
  UndoSpeciesData *mpSpeciesData;
  CQSpeciesDetail* mpSpecieDetail;
};

#endif /* DELETESPECIECOMMAND_H_ */
