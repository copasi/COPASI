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

#ifndef CQSpecieDM_H
#define CQSpecieDM_H

#include "listviews.h"
#include "CQBaseDataModel.h"

class CMetab;
template < class CType > class CDataVector;

#define COL_NAME_SPECIES          1
#define COL_COMPARTMENT           2
#define COL_TYPE_SPECIES          3
#define COL_UNIT_SPECIES          4
#define COL_ICONCENTRATION        5
#define COL_INUMBER               6
#define COL_CONCENTRATION         7
#define COL_NUMBER                8
#define COL_CRATE                 9
#define COL_NRATE                10
#define COL_COUNT_REACTIONS      11
#define COL_IEXPRESSION_SPECIES  12
#define COL_EXPRESSION_SPECIES   13
#define COL_NEXPRESSION_SPECIES  14
#define TOTAL_COLS_SPECIES       15

class CQSpecieDM : public CQBaseDataModel
{
  Q_OBJECT

  friend class SpecieDataChangeCommand;
  friend class InsertSpecieRowsCommand;

public:
  CQSpecieDM(QObject *parent = 0);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  const QStringList& getTypes();

  bool removeRows(QModelIndexList rows, const QModelIndex & parent = QModelIndex());

private:
  void insertNewRows(int position, int rows,
                     int column = COL_NAME_SPECIES,
                     const QVariant & value = "species");

protected:
  virtual void resetCacheProtected() override;
  virtual bool insertRows(int position, int rows, const QModelIndex &parent = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex &parent = QModelIndex());
  virtual size_t size() const override;

  QStringList mTypes;

  /**
   * A pointer to a vector of all metabolites in this model
   */

  CDataVector< CMetab > * mpMetabolites;

  bool mNotify;

  QStringList mUnits;
};

#endif //CQSpecieDM_H
