// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQReactionDM.h,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/05/15 19:36:28 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQReactionDM_H
#define CQReactionDM_H

#include "model/CModel.h"
#include "listviews.h"
#include "CQBaseDataModel.h"

#define COL_NAME_REACTIONS   1
#define COL_EQUATION         2
#define COL_RATE_LAW         3
#define COL_FLUX             4
#define COL_PARTICLE_FLUX    5
#define TOTAL_COLS_REACTIONS 6

class CQReactionDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQReactionDM(QObject *parent = 0);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;
  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);

protected:
  bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
  void setEquation(const CReaction *pRea, const QModelIndex& index, const QVariant &value);

signals:
  void notifyGUI(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key = "");
};

#endif //CQReactionDM_H
