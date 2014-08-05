// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQBaseDataModel.h,v $
//   $Revision: 1.10 $
//   $Name:  $
//   $Author: bergmann $
//   $Date: 2012/04/10 15:19:37 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQBaseDataModel_H
#define CQBaseDataModel_H

#include <QtCore/QAbstractTableModel>

#include "copasi/UI/listviews.h"

class QUndoStack;

#define COL_ROW_NUMBER   0

class CQBaseDataModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  CQBaseDataModel(QObject *parent = 0);
  virtual QVariant data(const QModelIndex &index, int role) const = 0;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const = 0;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole) = 0;
  bool insertRow();
  bool removeRow(int position);
  virtual bool clear();
  virtual bool isDefaultRow(const QModelIndex& i) const;
  QString createNewName(const QString name, const int nameCol);

#ifdef COPASI_UNDO
  void setUndoStack(QUndoStack* undoStack);
  QUndoStack* getUndoStack();
#endif

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) = 0;
  virtual bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) = 0;

#ifdef COPASI_UNDO
  QUndoStack *mpUndoStack;
#endif

signals:
  void notifyGUI(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");


};

#endif //CQBaseDataModel_H
