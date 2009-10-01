// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQEFMSpeciesDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/10/01 19:59:21 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQEFMSpeciesDM_H
#define CQEFMSpeciesDM_H

#include "CQBaseDataModel.h"

#include <vector>

class CFluxMode;
class CEFMTask;
class CMetab;

class CQEFMSpeciesDM : public CQBaseDataModel
{
  Q_OBJECT

public:
  CQEFMSpeciesDM(QObject *parent = 0);
  int rowCount(const QModelIndex &parent = QModelIndex()) const;
  int columnCount(const QModelIndex &parent = QModelIndex()) const;
  Qt::ItemFlags flags(const QModelIndex &index) const;
  QVariant data(const QModelIndex &index, int role) const;
  QVariant headerData(int section, Qt::Orientation orientation,
                      int role = Qt::DisplayRole) const;

  void setTask(const CEFMTask * pTask);

  bool setData(const QModelIndex &index, const QVariant &value,
               int role = Qt::EditRole);

  virtual bool CQEFMSpeciesDM::isDefaultRow(const QModelIndex& i) const;

protected:
  virtual bool insertRows(int position, int rows, const QModelIndex &index = QModelIndex());
  virtual bool removeRows(int position, int rows, const QModelIndex &index = QModelIndex());

private:
  const CEFMTask * mpTask;

  std::vector< CFluxMode >::const_iterator mBeginModes;
  int mModesSize;

  std::vector< CMetab * >::const_iterator mBeginSpecies;
  int mSpeciesSize;
};

#endif //CQEFMSpeciesDM_H
