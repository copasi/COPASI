// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQBiologicalDescriptionDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/02/23 05:12:36 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQBiologicalDescriptionDM_H
#define CQBiologicalDescriptionDM_H

#include "CQBaseDataModel.h"

#define COL_RELATIONSHIP                   0
#define COL_RESOURCE_BD                    1
#define COL_ID_BD                          2
#define TOTAL_COLS_BIOLOGICAL_DESCRIPTIONS 3

class CQBiologicalDescriptionDM : public CQBaseDataModel
  {
    Q_OBJECT

  public:
    CQBiologicalDescriptionDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent = 0);
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
  };

#endif //CQBiologicalDescriptionDM_H
