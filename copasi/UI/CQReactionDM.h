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

#ifndef CQReactionDM_H
#define CQReactionDM_H

#include <vector>
#include <string>

#include "CQBaseDataModel.h"

#define COL_NAME_REACTIONS   1
#define COL_EQUATION         2
#define COL_RATE_LAW         3
#define COL_FLUX             4
#define COL_PARTICLE_FLUX    5
#define COL_NOISE_EXPRESSION 6
#define TOTAL_COLS_REACTIONS 7

class CReactionInterface;
class CReaction;
template < class CType > class CDataVectorNS;

class CQReactionDM : public CQBaseDataModel
{
  Q_OBJECT

  friend class ReactionDataChangeCommand;

public:
  CQReactionDM(QObject *parent, CDataModel * pDataModel);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const override;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const override;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);

  bool updateReactionWithFunctionName(CReaction *pRea, QString &funcName);

  bool removeRows(QModelIndexList rows, const QModelIndex & parent = QModelIndex());

private:
  void insertNewRows(int position, int rows,
                     int column = COL_NAME_REACTIONS,
                     const QVariant & value = "reaction");

protected:
  virtual void resetCacheProtected() override;
  virtual bool insertRows(int position, int rows, const QModelIndex & parent = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex & parent = QModelIndex());
  virtual size_t size() const override;

private:
  bool setEquation(const CReaction & reaction, const QVariant & value, CUndoData & data);

  CDataVectorNS< CReaction > * mpReactions;
};

#endif //CQReactionDM_H
