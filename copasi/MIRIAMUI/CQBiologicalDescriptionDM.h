// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQBiologicalDescriptionDM_H
#define CQBiologicalDescriptionDM_H

#include "copasi/UI/CQBaseDataModel.h"

class CMIRIAMInfo;

#define COL_RELATIONSHIP                   1
#define COL_RESOURCE_BD                    2
#define COL_ID_BD                          3
#define TOTAL_COLS_BIOLOGICAL_DESCRIPTIONS 4

class CQBiologicalDescriptionDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQBiologicalDescriptionDM(QObject *parent = 0);
  void setMIRIAMInfo(CMIRIAMInfo * pMiriamInfo);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const override;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

protected:
  virtual void resetCacheProtected() override;
  bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
  virtual size_t size() const override;

  CMIRIAMInfo* mpMIRIAMInfo;
};

#endif //CQBiologicalDescriptionDM_H
