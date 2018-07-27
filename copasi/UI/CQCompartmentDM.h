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

#ifndef CQCompartmentDM_H
#define CQCompartmentDM_H

#include <vector>

#include "copasi/UI/CQBaseDataModel.h"

class UndoCompartmentData;
class UndoReactionData;
class CCompartment;
template < class CType > class CDataVectorNS;

#define COL_NAME_COMPARTMENTS         1
#define COL_TYPE_COMPARTMENTS         2
#define COL_UNIT_COMPARTMENTS         3
#define COL_IVOLUME                   4
#define COL_VOLUME                    5
#define COL_RATE_COMPARTMENTS         6
#define COL_IEXPRESSION_COMPARTMENTS  7
#define COL_EXPRESSION_COMPARTMENTS   8
#ifdef WITH_SDE_SUPPORT
# define COL_NEXPRESSION_COMPARTMENTS  9
# define TOTAL_COLS_COMPARTMENTS       10
#else
# define TOTAL_COLS_COMPARTMENTS       9
#endif

class CQCompartmentDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQCompartmentDM(QObject *parent = 0);
  const QStringList& getTypes();
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole);
  bool removeRows(QModelIndexList rows, const QModelIndex & parent = QModelIndex());
  bool clear();

private:
  void insertNewRows(int position, int rows,
                     int column = COL_NAME_COMPARTMENTS,
                     const QVariant & value = "compartment");

protected:
  virtual void resetCacheProtected();
  virtual bool insertRows(int position, int rows, const QModelIndex & parent = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex & parent = QModelIndex());

  QStringList mTypes;
  QStringList mUnits;
  CDataVectorNS< CCompartment > * mpCompartments;
};

#endif //CQCompartmentDM_H
