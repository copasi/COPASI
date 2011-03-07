// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQTableView.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:37:51 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * CQTableView.h
 *
 *  Created on: Nov 23, 2010
 *      Author: shoops
 */

#ifndef COPASI_QTableView
#define COPASI_QTableView

#include <QtGui/QTableView>

class QTimer;

class CQTableView : public QTableView
{
  Q_OBJECT

public:
  CQTableView(QWidget * pParent = NULL);
  virtual ~CQTableView();

  virtual void setModel(QAbstractItemModel * model);

protected:
  virtual void keyPressEvent(QKeyEvent * pEvent);

  virtual void mousePressEvent(QMouseEvent * pEvent);

protected slots:
  void slotSingleClick();
  void slotMoveDown();

private:
  QTimer * mpTimer;
  QMouseEvent * mpMouseEvent;
  bool mMoveDown;
  QAbstractItemModel * mpModel;
};

#endif // COPASI_QTableView
