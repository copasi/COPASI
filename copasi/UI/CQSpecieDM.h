// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQSpecieDM_H
#define CQSpecieDM_H

#include "model/CModel.h"
#include "listviews.h"
#include "CQBaseDataModel.h"

class UndoSpeciesData;
class UndoReactionData;

#define COL_NAME_SPECIES          1
#define COL_COMPARTMENT           2
#define COL_TYPE_SPECIES          3
#define COL_ICONCENTRATION        4
#define COL_INUMBER               5
#define COL_CONCENTRATION         6
#define COL_NUMBER                7
#define COL_CRATE                 8
#define COL_NRATE                 9
#define COL_IEXPRESSION_SPECIES  10
#define COL_EXPRESSION_SPECIES   11
#define COL_NEXPRESSION_SPECIES  12
#define TOTAL_COLS_SPECIES       13

class CQSpecieDM : public CQBaseDataModel
{
  Q_OBJECT

  friend class SpecieDataChangeCommand;
  friend class InsertSpecieRowsCommand;

public:
  CQSpecieDM(QObject *parent = 0);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  const QStringList& getTypes();
  void setFlagConc(bool flag);
  const std::vector< unsigned C_INT32 >& getItemToType();
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

  //TODO Undo
  bool specieDataChange(const QModelIndex &index, const QVariant &value, int role);
  QList <UndoSpeciesData *> insertNewSpecieRow(int position, int rows, const QModelIndex& index, const QVariant& value);
  void addSpecieRow(UndoSpeciesData *pSpecieData);
  void deleteSpecieRow(UndoSpeciesData *pSpecieData);
  bool removeSpecieRows(QModelIndexList rows, const QModelIndex&);
  bool insertSpecieRows(QList <UndoSpeciesData *>& pReaData);
  void deleteSpecieRows(QList <UndoSpeciesData *>& pReaData);
  bool removeAllSpecieRows();
  bool clear();

protected:
  bool mFlagConc;
  QStringList mTypes;

  /**
   * A vector mapping the item index to a model value type
   */
  std::vector< unsigned C_INT32 > mItemToType;

  /**
   * A pointer to the selected species
   */
  mutable CMetab * mpSpecies;

  bool mNotify;

  virtual bool insertRows(int position, int rows, const QModelIndex & source);
  virtual bool removeRows(int position, int rows);
};

#endif //CQSpecieDM_H
