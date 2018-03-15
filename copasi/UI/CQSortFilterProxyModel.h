// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQSortFilterProxyModel_h
#define CQSortFilterProxyModel_h

#include <QSortFilterProxyModel>

class CQSortFilterProxyModel : public QSortFilterProxyModel
{
public:
  CQSortFilterProxyModel(QObject *parent = 0);
  ~CQSortFilterProxyModel();
  virtual bool lessThan(const QModelIndex& left, const QModelIndex& right) const;
};
#endif // CQSortFilterProxyModel_h
