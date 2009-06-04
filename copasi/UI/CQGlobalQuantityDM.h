// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQGlobalQuantityDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/06/04 16:09:42 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQGlobalQuantityDM_H
#define CQGlobalQuantityDM_H

#include "model/CModel.h"
#include "CQBaseDataModel.h"

#define COL_NAME_GQ         1
#define COL_TYPE_GQ         2
#define COL_INITIAL_GQ      3
#define COL_TRANSIENT_GQ    4
#define COL_RATE_GQ         5
#define COL_IEXPRESSION_GQ  6
#define COL_EXPRESSION_GQ   7
#define TOTAL_COLS_GQ       8

class CQGlobalQuantityDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQGlobalQuantityDM(QObject *parent = 0);
  const QStringList& getTypes();
  const std::vector< unsigned C_INT32 >& getItemToType();
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

protected:
  QStringList mTypes;
  /**
    * A vector mapping the item index to a model valu type
    */
  std::vector< unsigned C_INT32 > mItemToType;
  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
};

#endif //CQGlobalQuantityDM_H
