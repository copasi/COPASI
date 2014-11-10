// Copyright (C) 2012 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQParameterOverviewDM
#define COPASI_CQParameterOverviewDM

#include <QtGui/QSortFilterProxyModel>

#include "copasi/UI/listviews.h"

class CModelParameterSet;
class CModelParameterGroup;
class CModelParameter;

#ifdef COPASI_UNDO
class QUndoStack;
#endif

class CQParameterOverviewDM : public QAbstractItemModel
{
  Q_OBJECT

#ifdef COPASI_UNDO
  friend class ParameterOverviewDataChangeCommand;
#endif

public:
  CQParameterOverviewDM(QObject * pParent);

  virtual ~CQParameterOverviewDM();

  virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;

  virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  virtual QVariant headerData(int section, Qt::Orientation orientation, int role = Qt::DisplayRole) const;

  virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

  virtual QModelIndex parent(const QModelIndex & index) const;

  virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole);

  void setModelParameterset(CModelParameterSet * pModelParameterSet);

  void setFramework(const int & framework);

  static CModelParameter * nodeFromIndex(const QModelIndex & index);

#ifdef COPASI_UNDO
  void setUndoStack(QUndoStack* undoStack);
  QUndoStack* getUndoStack();
  bool parameterOverviewDataChange(const QModelIndex &_index, const QVariant &value, int role);
#endif

signals:
  void signalOpenEditor(const QModelIndex &) const;
  void signalCloseEditor(const QModelIndex &) const;

#ifdef COPASI_UNDO
  void changeWidget(const size_t & id);
#endif

private:
  QModelIndex index(CModelParameter * pNode) const;

  static int getRow(const CModelParameter * pNode);

  static QVariant nameData(const CModelParameter * pNode, int role);

  static QVariant diffData(const CModelParameter * pNode, int role);

  static QVariant typeData(const CModelParameter * pNode, int role);

  QVariant valueData(const CModelParameter * pNode, int role) const;

  QVariant unitData(const CModelParameter * pNode, int role) const;

  static QVariant assignmentData(const CModelParameter * pNode, int role);

private:
  CModelParameterGroup * mpModelParameterSet;

  int mFramework;

#ifdef COPASI_UNDO
  QUndoStack *mpUndoStack;
#endif
};

#endif // COPASI_CQParameterOverviewDM
