// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQReferenceDM.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/03/05 17:23:47 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQReferenceDM_H
#define CQReferenceDM_H

#include "MIRIAM/CModelMIRIAMInfo.h"
#include "UI/CQBaseDataModel.h"

#define COL_RESOURCE_REFERENCE 0
#define COL_ID_REFERENCE       1
#define COL_DESCRIPTION        2
#define TOTAL_COLS_REFERENCES  3

class CQReferenceDM : public CQBaseDataModel
  {
    Q_OBJECT

  public:
    CQReferenceDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent = 0);
    int rowCount(const QModelIndex &parent = QModelIndex()) const;
    int columnCount(const QModelIndex &parent = QModelIndex()) const;
    QVariant data(const QModelIndex &index, int role) const;
    QVariant headerData(int section, Qt::Orientation orientation,
                        int role = Qt::DisplayRole) const;
    bool setData(const QModelIndex &index, const QVariant &value,
                 int role = Qt::EditRole);

  protected:
    bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
    bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
    CMIRIAMInfo* mpMIRIAMInfo;
  };

#endif //CQReferenceDM_H
