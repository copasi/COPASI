// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQUnitDM_H
#define CQUnitDM_H

#include "model/CModel.h"
#include "listviews.h"
#include "CQBaseDataModel.h"

#define COL_NAME_UNITS         1
#define COL_SYMBOL_UNITS       2
#define COL_DEFINITION_UNITS   3
#define TOTAL_COLS_UNITS       4

class CQUnitDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQUnitDM(QObject *parent = 0);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

protected:
  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
  bool isFunctionReadOnly(const QModelIndex &index) const;
};

#endif //CQUnitDM_H
