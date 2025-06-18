// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQUnitDM_H
#define CQUnitDM_H

#include "listviews.h"
#include "CQBaseDataModel.h"

class CUnitDefinition;

#define COL_NAME_UNITS         1
#define COL_SYMBOL_UNITS       2
#define COL_EXPRESSION_UNITS   3
#define TOTAL_COLS_UNITS       4

class CQUnitDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQUnitDM(QObject *parent, CDataModel * pDataModel);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;

public slots:
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

protected:
  void resetCacheProtected() override;
  bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
  size_t size() const override;

  // cache the pretty-printed unit strings
  mutable QMap< const CUnitDefinition *, QVariant > mUnitCache;

private:
  bool isFunctionReadOnly(const QModelIndex &index) const;
};

#endif //CQUnitDM_H
