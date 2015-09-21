// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SpecieDataChangeCommand.h
 *
 *  Created on: 27 Aug 2014
 *      Author: dada
 */

#ifndef SPECIEDATACHANGECOMMAND_H_
#define SPECIEDATACHANGECOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQSpecieDM;
class SpecieDataChangeCommand: public CCopasiUndoCommand
{
public:
  SpecieDataChangeCommand(const QModelIndex& index,
                          const QVariant& value,
                          int role,
                          CQSpecieDM *pSpecieDM);

  void redo();
  void undo();

  QString specieDataChangeText() const;

  virtual ~SpecieDataChangeCommand();

private:
  QVariant mNew, mOld;
  QModelIndex mIndex;
  CQSpecieDM *mpSpecieDM;
  int mRole;
  Path mPathIndex;
};

#endif /* SPECIEDATACHANGECOMMAND_H_ */
