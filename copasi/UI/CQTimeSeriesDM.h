// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQTimeSeriesDM
#define COPASI_CQTimeSeriesDM

#include "copasi/UI/CQBaseDataModel.h"

class CTimeSeries;

class CQTimeSeriesDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQTimeSeriesDM(QObject *parent = 0);
  virtual ~CQTimeSeriesDM();

  int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;

  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

  virtual bool isDefaultRow(const QModelIndex& i) const;

  void setTimeSeries(const CTimeSeries * pTimeSeries);

  void setFramework(int framework);

protected:
  void resetCacheProtected() override;
  virtual bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
  size_t size() const override;

private:
  const CTimeSeries * mpTimeSeries;
  int mFramework;
};

#endif // COPASI_CQTimeSeriesDM
