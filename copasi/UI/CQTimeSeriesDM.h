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
  Qt::ItemFlags flags(const QModelIndex &index) const override;

  QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const override;

  QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const override;

  bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole) override;

  bool isDefaultRow(const QModelIndex& i) const override;

  void setTimeSeries(const CTimeSeries * pTimeSeries);

  void setFramework(int framework) override;

protected:
  void resetCacheProtected() override;
  bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
  bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex()) override;
  size_t size() const override;

private:
  const CTimeSeries * mpTimeSeries;
  int mFramework;
};

#endif // COPASI_CQTimeSeriesDM
