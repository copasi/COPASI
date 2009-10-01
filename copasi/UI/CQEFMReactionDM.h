// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMReactionDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/10/01 19:59:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

  void setTask(const CEFMTask * pTask);

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);

  virtual bool CQEFMReactionDM::isDefaultRow(const QModelIndex& i) const;

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
  const CEFMTask * mpTask;

  std::vector< CFluxMode >::const_iterator mBeginModes;
  int mModesSize;

  std::vector< const CReaction * >::const_iterator mBeginReactions;
  int mReactionsSize;
};

#endif //CQEFMReactionDM_H
