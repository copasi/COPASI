// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SpeciesInitialValueLostFocusCommand.h
 *
 *  Created on: 19 Sep 2014
 *      Author: dada
 */

#ifndef SpeciesInitialValueLostFocusCommand_H_
#define SpeciesInitialValueLostFocusCommand_H_

#include "CCopasiUndoCommand.h"

class CQSpeciesDetail;
class UndoSpeciesData;

class SpeciesInitialValueLostFocusCommand: public CCopasiUndoCommand
{
public:
  SpeciesInitialValueLostFocusCommand(CQSpeciesDetail *pSpecieDetail);
  void redo();
  void undo();
  QString specieInitialValueLostFocusText(std::string &name) const;

  virtual ~SpeciesInitialValueLostFocusCommand();

private:
  CQSpeciesDetail* mpSpecieDetail;
  UndoSpeciesData *mpSpeciesData;
  bool mFirstTime;
};

#endif /* SpeciesInitialValueLostFocusCommand_H_ */
