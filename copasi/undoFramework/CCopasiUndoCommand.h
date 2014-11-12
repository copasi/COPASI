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

#include <set>

typedef QPair<int, int> PathItem;
typedef QList<PathItem> Path;

class UndoData;
class UndoSpecieData;
class UndoReactionData;
class UndoGlobalQuantityData;
class UndoEventData;

class CCopasiUndoCommand : public QUndoCommand
{
public:
  CCopasiUndoCommand();
  virtual ~CCopasiUndoCommand();
  virtual void undo() = 0;
  virtual void redo() = 0;
  Path pathFromIndex(const QModelIndex &index);
  QModelIndex pathToIndex(const Path &path, const QAbstractItemModel *model);
  void setDependentObjects(const std::set< const CCopasiObject * > & deletedObjects);

  QList<UndoReactionData*> *getReactionData() const;
  QList<UndoSpecieData*> *getSpecieData() const;
  void setReactionData(QList<UndoReactionData*> *reactionData);
  void setSpecieData(QList<UndoSpecieData*> *specieData);
  QList<UndoGlobalQuantityData*> *getGlobalQuantityData() const;
  void setGlobalQuantityData(QList<UndoGlobalQuantityData*> *globalQuantityData);
  QList<UndoEventData*> *getEventData() const;
  void setEventData(QList<UndoEventData*> *eventData);

protected:
  QList<UndoSpecieData*> *mpSpecieData;
  QList<UndoReactionData*> *mpReactionData;
  QList<UndoGlobalQuantityData*> *mpGlobalQuantityData;
  QList<UndoEventData*> *mpEventData;
};

#endif /* CCOPASIUNDOCOMMAND_H_ */
