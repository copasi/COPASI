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
#ifdef WITH_SDE_SUPPORT
# define COL_NOISE_EXPRESSION 6
# define TOTAL_COLS_REACTIONS 7
#else
# define TOTAL_COLS_REACTIONS 6
#endif

class CReactionInterface;
class CReaction;
template < class CType > class CDataVectorNS;

class CQReactionDM : public CQBaseDataModel
{
  Q_OBJECT

  friend class ReactionDataChangeCommand;

public:
  CQReactionDM(QObject *parent, CDataModel * pDataModel);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);

  bool updateReactionWithFunctionName(CReaction *pRea, QString &funcName);

  bool removeRows(QModelIndexList rows, const QModelIndex & parent = QModelIndex());
  bool clear();

private:
  void insertNewRows(int position, int rows,
                     int column = COL_NAME_REACTIONS,
                     const QVariant & value = "reaction");

public slots:
  virtual void resetCache();

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex & parent = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex & parent = QModelIndex());

private:
  bool setEquation(const CReaction & reaction, const QVariant & value, CUndoData & data);

  CDataVectorNS< CReaction > * mpReactions;
};

#endif //CQReactionDM_H
