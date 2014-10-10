// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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
class UndoSpecieData;

class SpecieTypeChangeCommand: public CCopasiUndoCommand
{
public:
  SpecieTypeChangeCommand(int type, int currentType, CQSpeciesDetail *pSpecieDetail);
  void redo();
  void undo();
  QString specieTypeChangeText(std::string &name) const;

  virtual ~SpecieTypeChangeCommand();

private:
  int mNewType, mOldType;
  CQSpeciesDetail* mpSpecieDetail;
  UndoSpecieData *mpSpecieData;
  bool mFirstTime;
  bool useInitialExpression;
};

#endif /* SPECIETYPECHANGECOMMAND_H_ */
