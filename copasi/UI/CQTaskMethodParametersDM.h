// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QtGui/QSortFilterProxyModel>

#include "copasi/UI/listviews.h"

class CCopasiMethod;
class CCopasiParameter;

#ifdef COPASI_UNDO
class QUndoStack;
#endif

class CQTaskMethodParametersDM : public QAbstractItemModel
{
  Q_OBJECT

#ifdef COPASI_UNDO
  friend class TaskMethodParametersDataChangeCommand;
#endif

public:
  CQTaskMethodParametersDM(QObject * pParent);

  virtual ~CQTaskMethodParametersDM();

  virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;

  virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

  virtual QModelIndex parent(const QModelIndex & index) const;

  virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole);

  void pushMethod(CCopasiMethod * pMethod);
  void popMethod(CCopasiMethod * pMethod);
  void clearMethods();

  void setFramework(const int & framework);

  void beginResetModel();
  void endResetModel();

  static CCopasiParameter * nodeFromIndex(const QModelIndex & index);

signals:
  void signalCreateComboBox(const QModelIndex &) const;
  void signalCreatePushButton(const QModelIndex &) const;
  void signalCloseEditor(const QModelIndex &) const;

private:
  QModelIndex index(CCopasiParameter * pNode) const;

  bool isMethod(CCopasiParameter * pNode) const;

  int getRow(const CCopasiParameter * pNode) const;

  static QVariant nameData(const CCopasiParameter * pNode, int role);

  static QVariant typeData(const CCopasiParameter * pNode, int role);

  static QVariant valueData(const CCopasiParameter * pNode, int role);

private:
  QVector< CCopasiMethod * > mMethods;

  int mFramework;
};

#endif // COPASI_CQTaskMethodParametersDM
