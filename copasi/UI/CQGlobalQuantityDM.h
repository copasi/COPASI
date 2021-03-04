// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CQGlobalQuantityDM_H
#define CQGlobalQuantityDM_H

#include "CQBaseDataModel.h"

class CModelValue;
template < class CType > class CDataVectorN;

#define COL_NAME_GQ         1
#define COL_TYPE_GQ         2
#define COL_UNIT_GQ         3
#define COL_INITIAL_GQ      4
#define COL_TRANSIENT_GQ    5
#define COL_RATE_GQ         6
#define COL_IEXPRESSION_GQ  7
#define COL_EXPRESSION_GQ   8
#define COL_NEXPRESSION_GQ  9
#define TOTAL_COLS_GQ      10

class CQGlobalQuantityDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQGlobalQuantityDM(QObject *parent = 0);
  const QStringList& getTypes();
  int virtual rowCount(const QModelIndex &parent = QModelIndex()) const;
  int virtual columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);

  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

private:
  void insertNewRows(int position, int rows,
                     int column = COL_NAME_GQ,
                     const QVariant & value = "quantity");

protected:
  virtual void resetCacheProtected() override;
  virtual bool insertRows(int position, int rows, const QModelIndex & parent = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex & parent = QModelIndex());
  virtual size_t size() const override;

  QStringList mTypes;
  CDataVectorN< CModelValue > * mpGlobalQuantities;

  // cache the pretty-printed unit strings
  mutable QMap< std::string, QVariant > mUnitCache;
};

#endif //CQGlobalQuantityDM_H
