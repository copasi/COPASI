// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CQUndoDM
#define COPASI_CQUndoDM

#include "copasi/UI/CQBaseDataModel.h"

#include <set>

class CUndoData;
class CUndoStack;
class QTableView;

class CQUndoDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  enum struct ColumnType
  {
    Apply,
    ObjectType,
    ObjectName,
    Action,
    Property,
    NewValue,
    OldValue,
//    Author,
//    Time,
    __SIZE
  };

  CQUndoDM(QObject *parent, CDataModel * pDataModel, QTableView * pTableView);

  virtual ~CQUndoDM();

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  QVariant data(const QModelIndex &index, int role) const override;

  QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const override;

  Qt::ItemFlags flags(const QModelIndex &index) const override;

  bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole) override;

protected:
  void resetCacheProtected() override;

  bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

  bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

  size_t size() const override;

  QVariant displayData(const QModelIndex &index) const;

  std::vector< std::string > changedProperties(const CUndoData & undoData) const;

private:
  CUndoStack * mpUndoStack;

  QTableView * mpTableView;

  std::set< std::string > mIgnoredProperties;
};

#endif // COPASI_CQUndoDM
