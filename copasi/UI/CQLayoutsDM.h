// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQLayoutsDM
#define COPASI_CQLayoutsDM

#include "CQBaseDataModel.h"

#define COL_ROW_NUMBER   0
#define COL_NAME         1
#define COL_SHOW         2
#define TOTAL_COLS_LAYOUT       3

class CListOfLayouts;

class CQLayoutsDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQLayoutsDM(QObject *parent = 0);
  virtual ~CQLayoutsDM();

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const override;
  bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole) override;
  bool isDefaultRow(const QModelIndex& i) const override;
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());
  void setListOfLayouts(CListOfLayouts * pListOfLayouts);

  bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;

protected:
  void resetCacheProtected() override;
  bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
  size_t size() const override;

private:
  CListOfLayouts * mpListOfLayouts;
  QString mNewName;
};

#endif // COPASI_CQLayoutsDM
