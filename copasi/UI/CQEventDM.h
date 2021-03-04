// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

#ifndef CQEventDM_H
#define CQEventDM_H

#include "CQBaseDataModel.h"

class CEvent;
template < class CType > class CDataVectorN;

#define COL_NAME_EVENTS             1
#define COL_TRIGGER_EVENTS          2
#define COL_DELAYED_EVENTS          3
#define COL_DELAY_EXPRESSION_EVENTS 4
#define COL_ASSIGNTARGET_EVENTS     5
#define COL_ASSIGNEXPRESSION_EVENTS 6
#define TOTAL_COLS_EVENTS           7

class CQEventDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQEventDM(QObject *parent, CDataModel * pDataModel);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

private:
  void insertNewRows(int position, int rows,
                     int column = COL_NAME_EVENTS,
                     const QVariant & value = "event");

protected:
  virtual void resetCacheProtected() override;
  virtual bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
  virtual size_t size() const override;

  CDataVectorN< CEvent > * mpEvents;
};

#endif //CQEventDM_H
