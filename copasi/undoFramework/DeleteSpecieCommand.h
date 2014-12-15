// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
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

class UndoSpecieData;
class UndoReactionData;
class CQSpeciesDetail;

class DeleteSpecieCommand: public CCopasiUndoCommand
{
public:
  DeleteSpecieCommand(CQSpeciesDetail *pSpecieDetail);
  void redo();
  void undo();
  QString deleteSpecieText(std::string &name) const;
  UndoData *getUndoData() const;

  virtual ~DeleteSpecieCommand();

private:
  bool mFirstTime;
  UndoSpecieData *mpSpecieData;
  CQSpeciesDetail* mpSpecieDetail;
};

#endif /* DELETESPECIECOMMAND_H_ */
