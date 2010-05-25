// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQCreatorDM.h,v $
//   $Revision: 1.7.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/05/25 21:26:30 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQCreatorDM_H
#define CQCreatorDM_H

#include "UI/CQBaseDataModel.h"

class CMIRIAMInfo;

#define COL_FAMILY_NAME        1
#define COL_GIVEN_NAME         2
#define COL_EMAIL              3
#define COL_ORG                4
#define TOTAL_COLS_CREATORS    5

class CQCreatorDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQCreatorDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent = 0);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

protected:
  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
  CMIRIAMInfo* mpMIRIAMInfo;
};

#endif //CQCreatorDM_H
