// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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
class UndoSpecieData;

class InsertSpecieRowsCommand: public CCopasiUndoCommand
{
public:
  InsertSpecieRowsCommand(int position, int rows, CQSpecieDM *pSpecieDM, const QModelIndex&);
  virtual ~InsertSpecieRowsCommand();
  void redo();
  void undo();
  QString insertRowsText() const;

private:
  CQSpecieDM* mpSpecieDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  UndoSpecieData* mpSpecieData;
  int firstTime;
};

#endif /* INSERTSPECIEROWSCOMMAND_H_ */
