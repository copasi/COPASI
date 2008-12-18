// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQDateTimeEditTableItem.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:56:20 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CQDateTimeEditTableItem
#define COPASI_CQDateTimeEditTableItem

#include <q3datetimeedit.h>
#include "CopasiTableWidget.h"

class CQDateTimeEditTableItem : public Q3DateTimeEdit
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
    CQDateTimeEditTableItem (CopasiTableWidget* table, int row, int col, const QDateTime & datetime, QWidget * parent = 0, const char * name = 0);
  public:
    ~CQDateTimeEditTableItem(void);
  };

#endif // COPASI_CQDateTimeEditTableItem
