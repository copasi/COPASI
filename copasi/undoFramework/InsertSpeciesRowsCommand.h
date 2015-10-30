// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * InsertSpecieRowsCommand.h
 *
 *  Created on: 27 Aug 2014
 *      Author: dada
 */

#ifndef INSERTSPECIEROWSCOMMAND_H_
#define INSERTSPECIEROWSCOMMAND_H_

#include "CCopasiUndoCommand.h"

class CMetab;
class UndoSpeciesData;

class InsertSpecieRowsCommand: public CCopasiUndoCommand
{
public:
  InsertSpecieRowsCommand(int position, int rows, CQSpecieDM *pSpecieDM, const QModelIndex&);
  virtual ~InsertSpecieRowsCommand();

  void redo();
  void undo();

private:
  CQSpecieDM* mpSpecieDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  UndoSpeciesData* mpSpeciesData;

};

#endif /* INSERTSPECIEROWSCOMMAND_H_ */
