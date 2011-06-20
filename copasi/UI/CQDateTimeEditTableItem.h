// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQDateTimeEditTableItem.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/06/20 16:07:08 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CQDateTimeEditTableItem
#define COPASI_CQDateTimeEditTableItem

#include <QDateTimeEdit>
#include "CopasiTableWidget.h"

class CQDateTimeEditTableItem : public QDateTimeEdit
{
  Q_OBJECT
private:
  CopasiTableWidget* mpTable;
  int mRow, mCol;
  void init();

protected slots:
  virtual void slotValueChanged(const QDateTime &);

signals:
  void valueChanged(int, int);

public:
  CQDateTimeEditTableItem(CopasiTableWidget* table, int row, int col, QWidget * parent = 0, const char * name = 0);
  CQDateTimeEditTableItem(CopasiTableWidget* table, int row, int col, const QDateTime & datetime, QWidget * parent = 0, const char * name = 0);
public:
  ~CQDateTimeEditTableItem(void);
};

#endif // COPASI_CQDateTimeEditTableItem
