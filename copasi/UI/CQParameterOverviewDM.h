// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQParameterOverviewDM
#define COPASI_CQParameterOverviewDM

#include <QSortFilterProxyModel>

#include "copasi/UI/listviews.h"
#include "copasi/UI/CQBaseDataModel.h"

class CModelParameterSet;
class CModelParameterGroup;
class CModelParameter;
class CValidatedUnit;

#include <set>

#define COL_VALUE      3

class CQParameterOverviewDM : public CQBaseDataModel
{
  Q_OBJECT

  friend class ParameterOverviewDataChangeCommand;

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

  void setModelParameterSet(CModelParameterSet * pModelParameterSet);

  void setFramework(const int & framework);

  static CModelParameter * nodeFromIndex(const QModelIndex & index);

  virtual bool insertRows(int position, int rows, const QModelIndex & source);
  virtual bool removeRows(int position, int rows, const QModelIndex & parent = QModelIndex());

public slots:
  virtual void resetCache();

signals:
  void signalOpenEditor(const QModelIndex &) const;
  void signalCloseEditor(const QModelIndex &) const;

private:
  QModelIndex index(CModelParameter * pNode, int column) const;

  static int getRow(const CModelParameter * pNode);

  static QVariant nameData(const CModelParameter * pNode, int role);

  static QVariant diffData(const CModelParameter * pNode, int role);

  static QVariant typeData(const CModelParameter * pNode, int role);

  QVariant valueData(const CModelParameter * pNode, int role) const;

  QVariant unitData(const CModelParameter * pNode, int role) const;

  static QVariant assignmentData(const CModelParameter * pNode, int role);

private:
  CModelParameterSet * mpModelParameterSet;

  int mFramework;

  // cache the unit strings, to make viewing the parameter overview table faster
  mutable std::set< CValidatedUnit > mUnitCache;

  // the key to the currently active parameter set
  std::string mParameterSetKey;
};

#endif // COPASI_CQParameterOverviewDM
