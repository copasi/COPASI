// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * CQMethodParametersDM.h
 *
 *  Created on: Oct 9, 2015
 *      Author: shoops
 */

#ifndef COPASI_CQTaskMethodParametersDM
#define COPASI_CQTaskMethodParametersDM

#include <QSortFilterProxyModel>

#include "copasi/UI/listviews.h"

class CCopasiParameterGroup;
class CCopasiParameter;

class CQParameterGroupDM : public QAbstractItemModel
{
  Q_OBJECT

  friend class TaskMethodParametersDataChangeCommand;

public:
  CQParameterGroupDM(QObject * pParent);

  virtual ~CQParameterGroupDM();

  virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;

  virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

  virtual QModelIndex parent(const QModelIndex & index) const;

  virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole);

  void setAdvanced(const bool & advanced);

  void pushGroup(CCopasiParameterGroup * pMethod);
  void popGroup(CCopasiParameterGroup * pMethod);
  void clearGroups();

  void beginResetModel();
  void endResetModel();

  static CCopasiParameter * nodeFromIndex(const QModelIndex & index);

signals:
  void signalCreateComboBox(const QModelIndex &) const;
  void signalCreatePushButton(const QModelIndex &) const;
  void signalCloseEditor(const QModelIndex &) const;

private:
  QModelIndex index(CCopasiParameter * pNode) const;

  bool isTopLevelGroup(CCopasiParameter * pNode) const;

  int getRow(const CCopasiParameter * pNode) const;

  static QVariant nameData(const CCopasiParameter * pNode, int role);
  static QVariant typeData(const CCopasiParameter * pNode, int role);
  static QVariant valueData(const CCopasiParameter * pNode, int role);

private:
  QVector< CCopasiParameterGroup * > mTopLevelGroups;
  bool mAdvanced;
};

#endif // COPASI_CQTaskMethodParametersDM
