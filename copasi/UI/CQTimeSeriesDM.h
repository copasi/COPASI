// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTimeSeriesDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/23 18:39:00 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
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

  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  virtual QVariant data(const QModelIndex &index, int role = Qt::DisplayRole) const;

  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;

  virtual bool setData(const QModelIndex &index, const QVariant &value, int role = Qt::EditRole);

  virtual bool isDefaultRow(const QModelIndex& i) const;

  void setTimeSeries(const CTimeSeries * pTimeSeries);

  void setFramework(int framework);

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());


private:
  const CTimeSeries * mpTimeSeries;
  int mFramework;
};

#endif // COPASI_CQTimeSeriesDM
