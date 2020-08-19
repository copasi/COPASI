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

#ifndef CQEFMSpeciesDM_H
#define CQEFMSpeciesDM_H

#include "copasi/UI/CQBaseDataModel.h"

#include <vector>

class CFluxMode;
class CEFMTask;
class CMetab;
class CModel;

class CQEFMSpeciesDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQEFMSpeciesDM(QObject *parent = 0);

  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;

  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

  virtual bool isDefaultRow(const QModelIndex& i) const;

  void setTask(const CEFMTask * pTask);

protected:
  virtual void resetCacheProtected() override;
  virtual bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
  virtual size_t size() const override;

private:
  const CEFMTask * mpTask;

  std::vector< CFluxMode >::const_iterator mBeginModes;

  const CModel * mpModel;
  std::vector< CMetab * >::const_iterator mBeginSpecies;
  size_t mSpeciesSize;
};

#endif //CQEFMSpeciesDM_H
