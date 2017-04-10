// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SpecieTypeChangeCommand.h
 *
 *  Created on: 4 Sep 2014
 *      Author: dada
 */

#ifndef SPECIETYPECHANGECOMMAND_H_
#define SPECIETYPECHANGECOMMAND_H_

#include "CCopasiUndoCommand.h"

class CQSpeciesDetail;
class UndoSpeciesData;

class SpeciesTypeChangeCommand: public CCopasiUndoCommand
{
public:
  SpeciesTypeChangeCommand(int type, int currentType, CQSpeciesDetail *pSpecieDetail);
  virtual ~SpeciesTypeChangeCommand();

  void redo();
  void undo();

private:
  int mNewType, mOldType;
  CQSpeciesDetail* mpSpeciesDetail;
  UndoSpeciesData *mpSpeciesData;
  bool useInitialExpression;
};

#endif /* SPECIETYPECHANGECOMMAND_H_ */
