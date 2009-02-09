// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQCreatorDM.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/09 21:05:34 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQCreatorDM_H
#define CQCreatorDM_H

#include <QAbstractTableModel>

#include  "MIRIAM/CModelMIRIAMInfo.h"

#define COL_FAMILY_NAME        0
#define COL_GIVEN_NAME         1
#define COL_EMAIL              2
#define COL_ORG                3
#define TOTAL_COLS_CREATORS    4

class CQCreatorDM : public QAbstractTableModel
  {
    Q_OBJECT

  public:
    CQCreatorDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent = 0);
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

#endif //CQCreatorDM_H
