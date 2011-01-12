// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQReferenceDM.h,v $
//   $Revision: 1.8.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:03:35 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQReferenceDM_H
#define CQReferenceDM_H

#include "UI/CQBaseDataModel.h"

class CMIRIAMInfo;

#define COL_RESOURCE_REFERENCE 1
#define COL_ID_REFERENCE       2
#define COL_DESCRIPTION        3
#define TOTAL_COLS_REFERENCES  4

class CQReferenceDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQReferenceDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent = 0);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
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

#endif //CQReferenceDM_H
