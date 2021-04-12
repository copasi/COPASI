// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

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

#include "copasi/core/CCore.h"
#include "copasi/undo/CUndoStack.h"

class CDataModel;

#define COL_ROW_NUMBER   0

class CQBaseDataModel : public QAbstractTableModel
{
  Q_OBJECT

public:
  CQBaseDataModel(QObject *parent, CDataModel * pDataModel);
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
  virtual void setFramework(int framework);
  QString createNewName(const QString name, const int nameCol);

  void setDataModel(CDataModel * pDataModel);
  CDataModel * getDataModel() const;

  void beginResetModel();
  void endResetModel();

  bool canFetchMore(const QModelIndex &parent) const override;
  void fetchMore(const QModelIndex &parent) override;

public slots:
  void resetCache();

protected:
  virtual void resetCacheProtected() = 0;
  virtual bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) = 0;
  virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) = 0;
  virtual size_t size() const = 0;

  CDataModel * mpDataModel;
  int mFramework;
  size_t mFetched;
  size_t mFetchLimit;
  bool mFetchDisabled;

signals:
  void notifyGUI(ListViews::ObjectType objectType, ListViews::Action action, const CCommonName & cn);
  void signalNotifyChanges(const CUndoData::CChangeSet & changes);
};

#endif //CQBaseDataModel_H
