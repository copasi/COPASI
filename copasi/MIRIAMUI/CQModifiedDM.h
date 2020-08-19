// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CQModifiedDM_H
#define CQModifiedDM_H

#include "copasi/UI/CQBaseDataModel.h"

class CMIRIAMInfo;

#define COL_DATE_MODIFIED      1
#define TOTAL_COLS_MODIFIEDS   2

class CQModifiedDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQModifiedDM(QObject *parent = 0);
  void setMIRIAMInfo(CMIRIAMInfo * pMiriamInfo);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
  virtual void resetCacheProtected() override;
  virtual size_t size() const override;

  CMIRIAMInfo* mpMIRIAMInfo;
};

#endif //CQModifiedDM_H
