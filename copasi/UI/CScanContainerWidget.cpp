/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanContainerWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/22 15:26:29 $
   End CVS Header */

#include "CScanContainerWidget.h"

#include "copasi.h"

#include "CUpDownSubwidget.h"

CScanContainerWidget::CScanContainerWidget(QWidget* parent, const char* name, WFlags fl)
    : QTable(parent, name)
{
  if (!name)
    setName("CScanContainerWidget");

  horizontalHeader()->hide();
  verticalHeader()->hide();
  setTopMargin(0);
  setLeftMargin(0);

  setShowGrid(false);

  setNumCols(2);
}

CScanContainerWidget::~CScanContainerWidget()
{}

std::vector<QWidget*> CScanContainerWidget::getWidgetList() const
  {
    std::vector<QWidget*> ret;
    QWidget* tmpWidget;

    C_INT32 i, imax = numRows();
    for (i = 0; i < imax; ++i)
      {
        tmpWidget = cellWidget(i, 1);
        if (tmpWidget)
          ret.push_back(tmpWidget);
      }
    return ret;
  }

void CScanContainerWidget::clearWidgetList()
{
  setNumRows(0);
}

void CScanContainerWidget::addWidget(QWidget* widget, bool controls /*=true*/)
{
  //mWL.push_back(widget);

  setNumRows(numRows() + 1);

  unsigned C_INT32 i = numRows() - 1;

  if (controls) //add control widget
    {
      CUpDownSubwidget * tmpUD = new CUpDownSubwidget(this);
      tmpUD->setIndex(i, false, true); //assumes...
      connect(tmpUD, SIGNAL(del(int)), this, SLOT(slotDel(int)));
      connect(tmpUD, SIGNAL(up(int)), this, SLOT(slotUp(int)));
      connect(tmpUD, SIGNAL(down(int)), this, SLOT(slotDown(int)));
      setCellWidget(i, 0, tmpUD);

      //tell the widget above that it is not the last anymore
      if (i > 0)
        {
          CUpDownSubwidget* tmpWidget = dynamic_cast<CUpDownSubwidget*>(cellWidget(i - 1, 0));
          if (tmpWidget)
            tmpWidget->setIndex(i - 1, false, false); //assumes...
        }
    }
  setCellWidget(i, 1, widget);
  adjustRow(i);

  adjustColumn(0);
  setColumnStretchable(1, true);
}

void CScanContainerWidget::insertWidget(QWidget* widget, int row)
{
  //setNumRows(numRows()+1);
  if (row == -1)
  {if (numRows() == 0) row = 0; else row = numRows() - 1;}
  insertRows(row);

  unsigned C_INT32 i = row;

  if (true) //add control widget
    {
      CUpDownSubwidget * tmpUD = new CUpDownSubwidget(this);
      //tmpUD->setIndex(i, true);
      connect(tmpUD, SIGNAL(del(int)), this, SLOT(slotDel(int)));
      connect(tmpUD, SIGNAL(up(int)), this, SLOT(slotUp(int)));
      connect(tmpUD, SIGNAL(down(int)), this, SLOT(slotDown(int)));
      setCellWidget(i, 0, tmpUD);

      //tell the widget above that it is not the last anymore
      /*if (i>0)
        {
          CUpDownSubwidget* tmpWidget = dynamic_cast<CUpDownSubwidget*>(cellWidget(i-1,0));
          if (tmpWidget)
            tmpWidget->setIndex(i-1, false);
        }*/
    }
  setCellWidget(i, 1, widget);
  adjustRow(i);

  adjustColumn(0);
  setColumnStretchable(1, true);

  updateIndices();
}

void CScanContainerWidget::slotUp(int index)
{
  //std::cout << "***up*** " << index << std::endl;
  if (index <= 0) return; //do nothing

  swapCells(index, 1, index - 1, 1);
  adjustRow(index);
  adjustRow(index - 1);
  //updateIndices();
}

void CScanContainerWidget::slotDown(int index)
{
  //std::cout << "***down*** " << index << std::endl;
  if (index >= numRows() - 1) return; //do nothing

  swapCells(index, 1, index + 1, 1);
  adjustRow(index);
  adjustRow(index + 1);
  //updateIndices();
}

void CScanContainerWidget::slotDel(int index)
{
  //std::cout << "***del*** " << index << std::endl;
  removeRow(index);
  updateIndices();
}

void CScanContainerWidget::updateIndices()
{
  //update the indices of the updown widgets
  CUpDownSubwidget* tmp, *tmp_last, *tmp_next;

  C_INT32 i, imax = numRows();
  for (i = 0; i < imax; ++i)
    {
      tmp_last = dynamic_cast<CUpDownSubwidget*>(cellWidget(i - 1, 0));
      tmp = dynamic_cast<CUpDownSubwidget*>(cellWidget(i, 0));
      tmp_next = dynamic_cast<CUpDownSubwidget*>(cellWidget(i + 1, 0));
      if (tmp)
        {
          tmp->setIndex(i, (tmp_last == NULL), (tmp_next == NULL));
        }
    }
}
