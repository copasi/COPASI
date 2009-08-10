// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQPlotDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/08/10 15:15:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQPlotDM_H
#define CQPlotDM_H

#include "model/CModel.h"
#include "CQBaseDataModel.h"

#define COL_NAME_PLOTS   1
#define COL_CURVES_PLOTS 2
#define COL_ACTIVE_PLOTS 3
#define TOTAL_COLS_PLOTS 4

class CQPlotDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQPlotDM(QObject *parent = 0);
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

#endif //CQPlotDM_H
