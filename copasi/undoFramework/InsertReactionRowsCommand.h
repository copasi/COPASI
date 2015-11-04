// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * insertReactionRowsCommand.h
 *
 *  Created on: 5 Aug 2014
 *      Author: dada
 */

#ifndef INSERTREACTIONROWSCOMMAND_H_
#define INSERTREACTIONROWSCOMMAND_H_

#include <vector>
#include <string>

#include "CCopasiUndoCommand.h"

class UndoReactionData;
class CQReactionDM;
class CReaction;
class CReactionInterface;

class InsertReactionRowsCommand: public CCopasiUndoCommand
{
public:
  InsertReactionRowsCommand(int position, int rows, CQReactionDM *pReactionDM);
  InsertReactionRowsCommand(int position, int rows, CQReactionDM *pReactionDM, const QModelIndex& index, const QVariant& value);
  virtual ~InsertReactionRowsCommand();

  void redo();
  void undo();

  const QVariant& value() const;
  void setValue(const QVariant &value);

  const QModelIndex& index() const;
  void setIndex(const QModelIndex &index);

  int position() const;
  void setPosition(int position);

  int rows() const;
  void setRows(int rows);

  void initializeUndoData(CReaction * reaction, const std::vector<std::string> &createdKeys);

private:
  CQReactionDM* mpReactionDM;
  int mRows, mPosition;
  QModelIndex mIndex;
  CReaction *mpReaction;
  CReactionInterface *mpRi;
  UndoReactionData *mpReactionData;
  QVariant mValue;
};

#endif /* INSERTREACTIONROWSCOMMAND_H_ */
