// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQModifiedDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/09 21:05:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQModifiedDM_H
#define CQModifiedDM_H

#include <QAbstractTableModel>

#include  "MIRIAM/CModelMIRIAMInfo.h"

#define COL_DATE_MODIFIED      0
#define TOTAL_COLS_MODIFIEDS   1

class CQModifiedDM : public QAbstractTableModel
  {
    Q_OBJECT

  public:
    CQModifiedDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);
    bool insertRow();
    bool removeRow(int position);
    bool clear();

  protected:
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

  private:
    CMIRIAMInfo* mMIRIAMInfo;
  };

#endif //CQModifiedDM_H
