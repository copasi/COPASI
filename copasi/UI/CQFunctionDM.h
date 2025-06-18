// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CQFunctionDM_H
#define CQFunctionDM_H

#include "listviews.h"
#include "CQBaseDataModel.h"

#define COL_NAME_FUNCTIONS       1
#define COL_TYPE_FUNCTIONS       2
#define COL_MATH_DESC_FUNCTIONS  3
#define COL_SBML_ID_FUNCTIONS    4
#define TOTAL_COLS_FUNCTIONS     5

class CQFunctionDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQFunctionDM(QObject *parent, CDataModel * pDataModel);
  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole) override;
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());
  bool isFunctionReadOnly(const QModelIndex & index) const;

protected:
  void resetCacheProtected() override;
  bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
  size_t size() const override;

  QString mNewName;
};

#endif //CQFunctionDM_H
