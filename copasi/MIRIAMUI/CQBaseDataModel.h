// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/Attic/CQBaseDataModel.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/23 05:12:36 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQBaseDataModel_H
#define CQBaseDataModel_H

#include <QAbstractTableModel>

#include  "MIRIAM/CModelMIRIAMInfo.h"

class CQBaseDataModel : public QAbstractTableModel
  {
    Q_OBJECT

  public:
    CQBaseDataModel(CMIRIAMInfo* MIRIAMInfo, QObject *parent = 0);
    virtual QVariant data(const QModelIndex &index, int role) const = 0;
    virtual QVariant headerData(int section, Qt::Orientation orientation,
                                int role = Qt::DisplayRole) const = 0;
    Qt::ItemFlags flags(const QModelIndex &index) const;
    virtual bool setData(const QModelIndex &index, const QVariant &value,
                         int role = Qt::EditRole) = 0;
    bool insertRow();
    bool removeRow(int position);
    bool clear();

  protected:
    virtual bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex()) = 0;
    virtual bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex()) = 0;
    CMIRIAMInfo* mMIRIAMInfo;
  };

#endif //CQBaseDataModel_H
