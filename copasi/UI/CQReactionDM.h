// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQReactionDM_H
#define CQReactionDM_H

#include "model/CModel.h"
#include "CQBaseDataModel.h"

#define COL_NAME_REACTIONS   1
#define COL_EQUATION         2
#define COL_RATE_LAW         3
#define COL_FLUX             4
#define COL_PARTICLE_FLUX    5
#define TOTAL_COLS_REACTIONS 6

#ifdef COPASI_UNDO
class CReactionInterface;
class UndoReactionData;
#endif

class CQReactionDM : public CQBaseDataModel
{
  Q_OBJECT

#ifdef COPASI_UNDO
  friend class ReactionDataChangeCommand;
#endif

public:
  CQReactionDM(QObject *parent = 0);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);
  bool removeRows(QModelIndexList rows, const QModelIndex &index = QModelIndex());

  //TODO Undo
#ifdef COPASI_UNDO
  bool reactionDataChange(const QModelIndex &index, const QVariant &value, int role, QString &funcName);
  void insertNewReactionRow(int position, int rows, const QModelIndex&);
  void addReactionRow(CReaction *pReaction);
  void deleteReactionRow(CReaction *pReaction);
  bool updateReactionWithFunctionName(CReaction *pRea, QString &funcName);
  bool removeReactionRows(QModelIndexList rows, const QModelIndex&);
  bool insertReactionRows(QList <UndoReactionData *> pReaData);
  void deleteReactionRows(QList <UndoReactionData *> pReaData);
  bool removeAllReactionRows();
  bool clear();

signals:
  void changeWidget(const size_t & id, const std::string& key = "");
#endif

protected:
  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
  void setEquation(const CReaction *pRea, const QModelIndex& index, const QVariant &value);

  QString mNewEquation;
};

#endif //CQReactionDM_H
