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

#include <QList>

class CMetab;
class UndoSpeciesData;

class InsertSpecieRowsCommand: public CCopasiUndoCommand
{
public:
  InsertSpecieRowsCommand(int position, int rows, CQSpecieDM *pSpecieDM);
  InsertSpecieRowsCommand(int position, int rows, CQSpecieDM *pSpecieDM,
                          const QModelIndex& index, const QVariant& value);
  virtual ~InsertSpecieRowsCommand();

  void redo();
  void undo();

private:
  CQSpecieDM* mpSpecieDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  QList<UndoSpeciesData*> mpSpeciesData;
  QVariant mValue;

};

#endif /* INSERTSPECIEROWSCOMMAND_H_ */
