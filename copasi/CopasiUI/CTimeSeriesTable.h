/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CTimeSeriesTable.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/30 09:22:15 $
   End CVS Header */

#ifndef CTSTABLE
#define CTSTABLE

#include <qtable.h> 
//#include <iostream>

#include "trajectory/CTimeSeries.h"

class CTimeSeriesTable : public QTable
  {
  public:

    CTimeSeriesTable(QWidget* p, const char * name = 0)
        : QTable(3, 3, p, name),
        mFlagConc(true)
    {
      //setCaption("TimeSeries Table");
      //setLeftMargin(fontMetrics().width("W999999W"));
      setLeftMargin(0);
      mItem = new QTableItem(this, QTableItem::Never);
    }

    void setTimeSeries(const CTimeSeries & ts);
    void showConcentrations(bool conc = true);

  protected:

    QString textForCell(int row, int col);

    virtual void paintCell (QPainter * p, int row, int col, const QRect & cr, bool selected)
    {
      mItem->setText(textForCell(row, col));
      QTable::paintCell(p, row, col, cr, selected);
    }

    //basically do nothing in the following overloaded methods
    void resizeData(int) {}
    QTableItem *item(int , int) const {return mItem;}
    void setItem(int , int , QTableItem *) {}
    void clearCell(int , int) {}
    void takeItem(QTableItem *) {}
    void insertWidget(int , int , QWidget *) {}
    QWidget *cellWidget(int , int) const {return NULL;}
    void clearCellWidget(int , int) {}

  private:
    QTableItem * mItem;
    const CTimeSeries * mTS;
    bool mFlagConc;
  };

#endif
