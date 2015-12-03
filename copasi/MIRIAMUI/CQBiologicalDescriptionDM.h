// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
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
  bool insertRows(int position, int rows, const QModelIndex & source);
  bool removeRows(int position, int rows);
  CMIRIAMInfo* mpMIRIAMInfo;
};

#endif //CQBiologicalDescriptionDM_H
