// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQParameterOverviewDM.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/03/30 18:01:35 $
// End CVS Header

// Copyright (C) 2012 - 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQParameterOverviewDM
#define COPASI_CQParameterOverviewDM

#include <QtGui/QSortFilterProxyModel>

#include "copasi/UI/listviews.h"

class CModelParameterSet;
class CModelParameterGroup;
class CModelParameter;

class CQParameterOverviewDM : public QAbstractItemModel
{
  Q_OBJECT

public:
  CQParameterOverviewDM(QObject * pParent);

  virtual ~CQParameterOverviewDM();

  virtual int columnCount(const QModelIndex & parent = QModelIndex()) const;

  virtual QVariant data(const QModelIndex & index, int role = Qt::DisplayRole) const;

  virtual Qt::ItemFlags flags(const QModelIndex &index) const;

  virtual QModelIndex index(int row, int column, const QModelIndex & parent = QModelIndex()) const;

  virtual QModelIndex parent(const QModelIndex & index) const;

  virtual int rowCount(const QModelIndex & parent = QModelIndex()) const;

  virtual bool setData(const QModelIndex &index, const QVariant &value,
                       int role = Qt::EditRole);

  void setModelParameterset(CModelParameterSet * pModelParameterSet);

  void setFramework(const int & framework);

private:
  QModelIndex index(CModelParameter * pNode) const;

  static CModelParameter * nodeFromIndex(const QModelIndex & index);

  static int getRow(const CModelParameter * pNode);

  static QVariant nameData(const CModelParameter * pNode, int role);

  static QVariant diffData(const CModelParameter * pNode, int role);

  static QVariant typeData(const CModelParameter * pNode, int role);

  QVariant valueData(const CModelParameter * pNode, int role) const;

  static QVariant unitData(const CModelParameter * pNode, int role);

  static QVariant assignmentData(const CModelParameter * pNode, int role);

private:
  CModelParameterGroup * mpModelParameterSet;

  int mFramework;
};

#endif // COPASI_CQParameterOverviewDM
