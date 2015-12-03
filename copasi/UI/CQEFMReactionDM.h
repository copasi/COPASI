// Copyright (C) 2010 - 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEFMReactionDM_H
#define CQEFMReactionDM_H

#include "CQBaseDataModel.h"

#include <vector>

class CFluxMode;
class CEFMTask;
class CReaction;

class CQEFMReactionDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQEFMReactionDM(QObject *parent = 0);
  virtual int rowCount(const QModelIndex &parent = QModelIndex()) const;
  virtual int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

  void setTask(const CEFMTask * pTask);

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);

  virtual bool isDefaultRow(const QModelIndex& i) const;

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex & source);
  virtual bool removeRows(int position, int rows);

private:
  const CEFMTask * mpTask;

  std::vector< CFluxMode >::const_iterator mBeginModes;
  size_t mModesSize;

  std::vector< const CReaction * >::const_iterator mBeginReactions;
  size_t mReactionsSize;
};

#endif //CQEFMReactionDM_H
