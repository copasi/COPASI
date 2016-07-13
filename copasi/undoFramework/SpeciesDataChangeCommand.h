// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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
class CMetab;

class SpecieDataChangeCommand: public CCopasiUndoCommand
{
public:
  SpecieDataChangeCommand(const CMetab* pMetab,
                          const QVariant& newValue,
                          const QVariant& oldValue,
                          int column,
                          CQSpecieDM *pSpecieDM);
  virtual ~SpecieDataChangeCommand();

  void redo();
  void undo();

private:
  UndoSpeciesData* mpSpeciesData;
  QVariant mNew, mOld;
  int mColumn;
  CQSpecieDM *mpSpecieDM;
};

#endif /* SPECIEDATACHANGECOMMAND_H_ */
