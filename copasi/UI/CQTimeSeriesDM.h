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

  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;

  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

  virtual bool isDefaultRow(const QModelIndex& i) const;

  void setTimeSeries(const CTimeSeries * pTimeSeries);

  void setFramework(int framework);

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex & source);
  virtual bool removeRows(int position, int rows);

private:
  const CTimeSeries * mpTimeSeries;
  int mFramework;
};

#endif // COPASI_CQTimeSeriesDM
