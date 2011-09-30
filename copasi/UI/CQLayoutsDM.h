// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQLayoutsDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:00 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQLayoutsDM
#define COPASI_CQLayoutsDM

#include "CQBaseDataModel.h"

#define COL_ROW_NUMBER   0
#define COL_NAME         1
#define COL_SHOW         2
#define TOTAL_COLS       3

class CListOfLayouts;

class CQLayoutsDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQLayoutsDM(QObject *parent = 0);
  virtual ~CQLayoutsDM();

  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole);
  virtual bool isDefaultRow(const QModelIndex& i) const;
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());
  void setListOfLayouts(CListOfLayouts * pListOfLayouts);

  virtual bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());

protected:
  virtual bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
  CListOfLayouts * mpListOfLayouts;
};

#endif // COPASI_CQLayoutsDM
