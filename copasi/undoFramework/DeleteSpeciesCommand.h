// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
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
  void redo();
  void undo();
  QString deleteSpecieText(const std::string &name) const;
  UndoData *getUndoData() const;

  virtual ~DeleteSpeciesCommand();

private:
  bool mFirstTime;
  UndoSpeciesData *mpSpeciesData;
  CQSpeciesDetail* mpSpecieDetail;
};

#endif /* DELETESPECIECOMMAND_H_ */
