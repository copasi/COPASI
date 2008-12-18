// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTimeSeriesTable.h,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/12/18 19:57:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CTSTABLE
#define CTSTABLE

#include <q3table.h>

#include "copasi.h"

#include "trajectory/CTimeSeries.h"

class CTimeSeriesTable : public Q3Table
  {
  public:

    CTimeSeriesTable(QWidget* p, const char * name = 0);
    ~CTimeSeriesTable();

    void setTimeSeries(const CTimeSeries & TS);
    const CTimeSeries * getTimeSeries();
    void showConcentrations(bool conc = true);
    bool doShowConcentrations() const;

  protected:

    QString textForCell(unsigned int row, unsigned int col);

    virtual void paintCell (QPainter * p, int row, int col, const QRect & cr, bool selected)
    {
      mItem->setText(textForCell(row, col));
      Q3Table::paintCell(p, row, col, cr, selected);
    }

    //basically do nothing in the following overloaded methods
    void resizeData(int) {}
    Q3TableItem *item(int , int) const {return mItem;}
    void setItem(int , int , Q3TableItem *) {}
    void clearCell(int , int) {}
    void takeItem(Q3TableItem *) {}
    void insertWidget(int , int , QWidget *) {}
    QWidget *cellWidget(int , int) const {return NULL;}
    void clearCellWidget(int , int) {}

  private:
    Q3TableItem * mItem;
    const CTimeSeries * mpTS;
    bool mFlagConc;
  };

#endif
