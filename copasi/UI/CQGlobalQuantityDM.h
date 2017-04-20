// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQGlobalQuantityDM_H
#define CQGlobalQuantityDM_H

#include "CQBaseDataModel.h"

class CModelValue;
template < class CType > class CDataVectorN;

class UndoGlobalQuantityData;
class UndoSpeciesData;
class UndoReactionData;

#define COL_NAME_GQ         1
#define COL_TYPE_GQ         2
#define COL_UNIT_GQ         3
#define COL_INITIAL_GQ      4
#define COL_TRANSIENT_GQ    5
#define COL_RATE_GQ         6
#define COL_IEXPRESSION_GQ  7
#define COL_EXPRESSION_GQ   8
#ifdef WITH_SDE_SUPPORT
# define COL_NEXPRESSION_GQ  9
# define TOTAL_COLS_GQ      10
#else
# define TOTAL_COLS_GQ       9
#endif

class CQGlobalQuantityDM : public CQBaseDataModel
{
  Q_OBJECT

  friend class GlobalQuantityDataChangeCommand;
  friend class InsertGlobalQuantityRowsCommand;

public:
  CQGlobalQuantityDM(QObject *parent = 0);
  const QStringList& getTypes();
  const std::vector< unsigned C_INT32 >& getItemToType();
  int virtual rowCount(const QModelIndex &parent = QModelIndex()) const;
  int virtual columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);

  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

  const QString& indexToStatus(int index) const;
  int statusToIndex(const QString& status) const;

  //TODO Undo
  bool globalQuantityDataChange(const QModelIndex &index, const QVariant &value);
  void insertNewGlobalQuantityRow(int position, int rows, const QModelIndex& index, const QVariant& value);
  void addGlobalQuantityRow(UndoGlobalQuantityData *pGlobalQuantityData);
  void deleteGlobalQuantityRow(UndoGlobalQuantityData *pGlobalQuantityData);
  bool removeGlobalQuantityRows(QModelIndexList rows, const QModelIndex&);
  bool insertGlobalQuantityRows(QList <UndoGlobalQuantityData *>& pGlobalQuatityData);
  void deleteGlobalQuantityRows(QList <UndoGlobalQuantityData *>& pGlobalQuantityData);
  bool removeAllGlobalQuantityRows();
  bool clear();

public slots:
  virtual void resetCache();

protected:
  QStringList mTypes;
  /**
    * A vector mapping the item index to a model valu type
    */
  std::vector< unsigned C_INT32 > mItemToType;
  CDataVectorN< CModelValue > * mpGlobalQuantities;

  // cache the pretty-printed unit strings
  mutable QMap< std::string, QVariant > mUnitCache;

  virtual bool insertRows(int position, int rows, const QModelIndex & source);
  virtual bool removeRows(int position, int rows);
};

#endif //CQGlobalQuantityDM_H
