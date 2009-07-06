// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEventDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/07/06 12:12:14 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEventDM_H
#define CQEventDM_H

#include "model/CModel.h"
#include "CQBaseDataModel.h"

#define COL_NAME_EVENTS             1
#define COL_ORDER_EVENTS            2
#define COL_TRIGGER_EVENTS          3
#define COL_DELAYED_EVENTS          4
#define COL_DELAY_EXPRESSION_EVENTS 5
#define COL_ASSIGNTARGET_EVENTS     6
#define COL_ASSIGNEXPRESSION_EVENTS 7
#define TOTAL_COLS_EVENTS           8

class CQEventDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQEventDM(QObject *parent = 0);
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
  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
};

#endif //CQEventDM_H
