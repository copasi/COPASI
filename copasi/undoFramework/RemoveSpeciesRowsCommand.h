// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * RemoveSpecieRowsCommand.h
 *
 *  Created on: 28 Aug 2014
 *      Author: dada
 */

#ifndef REMOVESPECIEROWSCOMMAND_H_
#define REMOVESPECIEROWSCOMMAND_H_

#include <set>

#include "CCopasiUndoCommand.h"

class CCopasiObject;
class UndoReactionData;
class CQSpecieDM;

class RemoveSpecieRowsCommand: public CCopasiUndoCommand
{
public:
  RemoveSpecieRowsCommand(QModelIndexList rows, CQSpecieDM * pSpecieDM);
  virtual ~RemoveSpecieRowsCommand();

  void redo();
  void undo();

private:
  CQSpecieDM *mpSpecieDM;
  QList <UndoSpeciesData *> mpSpeciesData;
};

#endif /* REMOVESPECIEROWSCOMMAND_H_ */
