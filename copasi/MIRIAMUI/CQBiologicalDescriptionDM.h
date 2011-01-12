// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/MIRIAMUI/CQBiologicalDescriptionDM.h,v $
//   $Revision: 1.5.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/01/12 19:03:34 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQBiologicalDescriptionDM_H
#define CQBiologicalDescriptionDM_H

#include "UI/CQBaseDataModel.h"

class CMIRIAMInfo;

#define COL_RELATIONSHIP                   1
#define COL_RESOURCE_BD                    2
#define COL_ID_BD                          3
#define TOTAL_COLS_BIOLOGICAL_DESCRIPTIONS 4

class CQBiologicalDescriptionDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQBiologicalDescriptionDM(CMIRIAMInfo* MIRIAMInfo, QObject *parent = 0);
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

#endif //CQBiologicalDescriptionDM_H
