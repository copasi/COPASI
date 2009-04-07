// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSortFilterProxyModel.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2009/04/07 23:14:25 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQSortFilterProxyModel_h
#define CQSortFilterProxyModel_h

#include <QSortFilterProxyModel>

class CQSortFilterProxyModel : public QSortFilterProxyModel
{
public:
  CQSortFilterProxyModel();
  ~CQSortFilterProxyModel();
  virtual bool lessThan(const QModelIndex& left, const QModelIndex& right) const;
};
#endif // CQSortFilterProxyModel_h
