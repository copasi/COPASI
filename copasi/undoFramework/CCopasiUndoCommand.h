// Copyright (C) 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CCopasiUndoCommand.h
 *
 *  Created on: 3 Jul 2014
 *      Author: dada
 */

#include <QUndoCommand>
#include <QModelIndex>

#ifndef CCOPASIUNDOCOMMAND_H_
#define CCOPASIUNDOCOMMAND_H_

typedef QPair<int, int> PathItem;
typedef QList<PathItem> Path;
class CCopasiUndoCommand : public QUndoCommand
{
public:
  CCopasiUndoCommand();
  virtual ~CCopasiUndoCommand();
  virtual void undo() = 0;
  virtual void redo() = 0;
  Path pathFromIndex(const QModelIndex &index);
  QModelIndex pathToIndex(const Path &path, const QAbstractItemModel *model);
};

#endif /* CCOPASIUNDOCOMMAND_H_ */
