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
template < class CType > class CCopasiVectorNS;

#define COL_NAME_COMPARTMENTS         1
#define COL_TYPE_COMPARTMENTS         2
#define COL_UNIT                      3
#define COL_IVOLUME                   4
#define COL_VOLUME                    5
#define COL_RATE_COMPARTMENTS         6
#define COL_IEXPRESSION_COMPARTMENTS  7
#define COL_EXPRESSION_COMPARTMENTS   8
#define TOTAL_COLS_COMPARTMENTS       9

class CQCompartmentDM : public CQBaseDataModel
{
  Q_OBJECT

  friend class CompartmentDataChangeCommand;
  friend class InsertCompartmentRowsCommand;

public:
  CQCompartmentDM(QObject *parent = 0);
  const QStringList& getTypes();
  const std::vector< unsigned C_INT32 >& getItemToType();
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  virtual Qt::ItemFlags flags(const QModelIndex &index) const;
  virtual QVariant data(const QModelIndex &index, int role) const;
  virtual QVariant headerData(int section, Qt::Orientation orientation,
                              int role = Qt::DisplayRole) const;
  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole);
  virtual void resetCache();

  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

  //TODO Undo
  bool compartmentDataChange(const QModelIndex& index,
                             const QVariant &value,
                             UndoCompartmentData *pUndoData);

  void insertNewCompartmentRow(int position, int rows, const QModelIndex& index,
                               const QVariant& value);
  void addCompartmentRow(UndoCompartmentData *pCompartmentData);
  void deleteCompartmentRow(UndoCompartmentData *pCompartmentData);
  bool removeCompartmentRows(QModelIndexList& rows, const QModelIndex&);
  bool insertCompartmentRows(QList <UndoCompartmentData *>& pCompartmentData);
  void deleteCompartmentRows(QList <UndoCompartmentData *>& pCompartmentData);
  bool removeAllCompartmentRows();
  bool clear();

protected:
  QStringList mTypes;
  /**
    * A vector mapping the item index to a model value type
    */
  std::vector< unsigned C_INT32 > mItemToType;
  virtual bool insertRows(int position, int rows, const QModelIndex & source);
  virtual bool removeRows(int position, int rows);

  QStringList mUnits;
  CCopasiVectorNS< CCompartment > * mpCompartments;
};

#endif //CQCompartmentDM_H
