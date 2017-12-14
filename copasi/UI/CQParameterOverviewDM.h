// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/undoFramework/ParameterOverviewDataChangeCommand.h"

class CModelParameterSet;
class CModelParameterGroup;
class CModelParameter;
class CValidatedUnit;
class QUndoStack;

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

  /**
   * Sets the key to the parameter set that is currently modified,
   * this will be used by the UNDO framework to activate the correct control
   *
   * @param key the key to the selected parameter set or empty to denote the
   *            current parameter overview
   */
  void setParameterSetKey(const std::string & key);
  const std::string getParameterSetKey() const;

  void setFramework(const int & framework);

  static CModelParameter * nodeFromIndex(const QModelIndex & index);

  void setUndoStack(QUndoStack* undoStack);
  QUndoStack* getUndoStack();
  /**
   * Helper functions going through all rows looking for the given CN
   *
   * @param cn the CN to look for
   * @param column the column to return in the index (if found)
   * @return the index for the CN with the given column if found, an
   *         invalid index otherwise.
   */
  bool parameterOverviewDataChange(const std::string& cn,
                                   const QVariant &value,
                                   const std::string& parameterSetKey, int column);

  virtual bool insertRows(int position, int rows, const QModelIndex & source);
  virtual bool removeRows(int position, int rows);

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
  CModelParameterGroup * mpModelParameterSet;

  int mFramework;

  QUndoStack *mpUndoStack;
  ParameterOverviewDataChangeCommand *mpLastCommand;

  // cache the unit strings, to make viewing the parameter overview table faster
  mutable std::set< CValidatedUnit > mUnitCache;

  // the key to the currently active parameter set
  std::string mParameterSetKey;
};

#endif // COPASI_CQParameterOverviewDM
