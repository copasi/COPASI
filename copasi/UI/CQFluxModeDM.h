// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFluxModeDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/09/29 16:36:23 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQFluxModeDM_H
#define CQFluxModeDM_H

#include "CQBaseDataModel.h"

#include <vector>

class CFluxMode;
class CEFMTask;

#define COL_REVERSIBILITY             1
#define COL_REACTION_NAME             2
#define COL_REACTION_EQUATION         3
#define TOTAL_COLUMS                  4

class CQFluxModeDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQFluxModeDM(QObject *parent = 0);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

  void setTask(const CEFMTask * pTask);

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);

  virtual bool CQFluxModeDM::isDefaultRow(const QModelIndex& i) const;

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
  const CEFMTask * mpTask;
  std::vector< CFluxMode >::const_iterator mBeginModes;
  int mModesSize;
};

#endif //CQFluxModeDM_H
