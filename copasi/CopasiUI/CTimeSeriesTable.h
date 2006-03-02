/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CTimeSeriesTable.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/02 02:21:43 $
   End CVS Header */

#ifndef CTSTABLE
#define CTSTABLE

#include <qtable.h>

#include "copasi.h"

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
    const CTimeSeries* getTimeSeries();
    void showConcentrations(bool conc = true);
    bool doShowConcentrations() const;

  protected:

    QString textForCell(unsigned int row, unsigned int col);

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
