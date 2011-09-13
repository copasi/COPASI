// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQBrowserPane.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/13 19:21:58 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CQBrowserPane
#define COPASI_CQBrowserPane

#include <QtGui/QTreeView>

class CQBrowserPane: public QTreeView
{
  Q_OBJECT

public:
  CQBrowserPane(QWidget* parent = 0);

  virtual ~CQBrowserPane();

protected slots:
  virtual void currentChanged(const QModelIndex & current, const QModelIndex & previous);
  void slotUpdateScrollBar(const QModelIndex & index);
};

#endif // COPASI_CQBrowserPane
