// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;

  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;

  virtual QVariant data(const QModelIndex &index, int role) const;

  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;

  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole);

protected:
  virtual void resetCacheProtected() override;

  virtual bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());

  virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());

  virtual size_t size() const override;

  QVariant displayData(const QModelIndex &index) const;

  std::vector< std::string > changedProperties(const CUndoData & undoData) const;

private:
  CUndoStack * mpUndoStack;

  QTableView * mpTableView;

  std::set< std::string > mIgnoredProperties;
};

#endif // COPASI_CQUndoDM
