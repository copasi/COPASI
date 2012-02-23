// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQParameterOverviewDM.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/02/23 17:44:59 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQParameterOverviewDM
#define COPASI_CQParameterOverviewDM

#include <QtGui/QSortFilterProxyModel>

#include "copasi/UI/listviews.h"

class CQParameterOverviewDM : public QAbstractItemModel
{
  Q_OBJECT

public:
  CQParameterOverviewDM();
  virtual ~CQParameterOverviewDM();
};

#endif // COPASI_CQParameterOverviewDM
