// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#ifdef COPASI_UNDO
class UndoCompartmentData;
class UndoReactionData;
#endif

#define COL_NAME_COMPARTMENTS         1
#define COL_TYPE_COMPARTMENTS         2
#define COL_IVOLUME                   3
#define COL_VOLUME                    4
#define COL_RATE_COMPARTMENTS         5
#define COL_IEXPRESSION_COMPARTMENTS  6
#define COL_EXPRESSION_COMPARTMENTS   7
#define TOTAL_COLS_COMPARTMENTS       8

class CQCompartmentDM : public CQBaseDataModel
{
  Q_OBJECT

#ifdef COPASI_UNDO
  friend class CompartmentDataChangeCommand;
  friend class InsertCompartmentRowsCommand;
#endif

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
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

  //TODO Undo
#ifdef COPASI_UNDO
  bool compartmentDataChange(const QModelIndex &index, const QVariant &value, int role);
  void insertNewCompartmentRow(int position, int rows, const QModelIndex&);
  void addCompartmentRow(UndoCompartmentData *pCompartmentData);
  void deleteCompartmentRow(UndoCompartmentData *pCompartmentData);
  bool removeCompartmentRows(QModelIndexList rows, const QModelIndex&);
  bool insertCompartmentRows(QList <UndoCompartmentData *> pCompartmentData);
  void deleteCompartmentRows(QList <UndoCompartmentData *> pCompartmentData);
  bool removeAllCompartmentRows();
  bool clear();

signals:
  void changeWidget(const size_t & id);
#endif

protected:
  QStringList mTypes;
  /**
    * A vector mapping the item index to a model valu type
    */
  std::vector< unsigned C_INT32 > mItemToType;
  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());
};

#endif //CQCompartmentDM_H
