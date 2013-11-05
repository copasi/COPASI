// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CQSortFilterProxyModel_h
#define CQSortFilterProxyModel_h

#include <QtGui/QSortFilterProxyModel>

class CQSortFilterProxyModel : public QSortFilterProxyModel
{
public:
  CQSortFilterProxyModel();
  ~CQSortFilterProxyModel();
  virtual bool lessThan(const QModelIndex& left, const QModelIndex& right) const;
};
#endif // CQSortFilterProxyModel_h
