// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQBaseDataModel_H
#define CQBaseDataModel_H

#include <QtCore/QAbstractTableModel>

#include "copasi/UI/listviews.h"

class QUndoStack;
class CCopasiDataModel;

#define COL_ROW_NUMBER   0

class CQBaseDataModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  CQBaseDataModel(QObject *parent, CCopasiDataModel * pDataModel);
  virtual QVariant data(const QModelIndex &index, int role) const = 0;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const = 0;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole) = 0;
  bool insertRow(int position, const QModelIndex & source);
  bool removeRow(int position);
  virtual bool clear();
  virtual bool isDefaultRow(const QModelIndex& i) const;

  QString createNewName(const QString name, const int nameCol);

  void setDataModel(CCopasiDataModel * pDataModel);
  void setUndoStack(QUndoStack* undoStack);
  QUndoStack* getUndoStack();
  CCopasiDataModel * getDataModel() const;

public slots:
  virtual void resetCache();

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex & source) = 0;
  virtual bool removeRows(int position, int rows) = 0;

  QUndoStack *mpUndoStack;
  CCopasiDataModel * mpDataModel;

signals:
  void notifyGUI(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");
};

#endif //CQBaseDataModel_H
