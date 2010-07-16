/* Begin CVS Header
$Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanContainerWidget.cpp,v $
$Revision: 1.11 $
$Name:  $
$Author: shoops $
$Date: 2010/07/16 19:05:17 $
End CVS Header */

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"
#include <iostream>

#include <qapplication.h>
#include <QResizeEvent>

#include "CScanContainerWidget.h"

#include "CUpDownSubwidget.h"

CScanContainerWidget::CScanContainerWidget(QWidget* parent, const char* name)
    : Q3Table(parent, name)
{
  if (!name)
    setName("CScanContainerWidget");

  horizontalHeader()->hide();
  verticalHeader()->hide();
  setTopMargin(0);
  setLeftMargin(0);

  setShowGrid(false);

  setNumCols(2);

  setSelectionMode(Q3Table::NoSelection);
  setFocusStyle(Q3Table::FollowStyle);

  mCopyEnabled = false;
  //TODO maybe reemplement paintFocus() to make the focus completely invisible
  // (it is already invisible most of the time)
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
      tmpUD->enableCopy(mCopyEnabled);
      connect(tmpUD, SIGNAL(del(int)), this, SLOT(slotDel(int)));
      connect(tmpUD, SIGNAL(up(int)), this, SLOT(slotUp(int)));
      connect(tmpUD, SIGNAL(down(int)), this, SLOT(slotDown(int)));
      connect(tmpUD, SIGNAL(copy(int)), this, SLOT(slotCopy(int)));
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

//  updateTable();
  qApp->processEvents();
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
      tmpUD->enableCopy(mCopyEnabled);
      //tmpUD->setIndex(i, true);
      connect(tmpUD, SIGNAL(del(int)), this, SLOT(slotDel(int)));
      connect(tmpUD, SIGNAL(up(int)), this, SLOT(slotUp(int)));
      connect(tmpUD, SIGNAL(down(int)), this, SLOT(slotDown(int)));
      connect(tmpUD, SIGNAL(copy(int)), this, SLOT(slotCopy(int)));
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
  /*
    adjustRow(i);

    adjustColumn(0);
    setColumnStretchable(1, true);
  */
  updateIndices();
  updateTable();
  qApp->processEvents();
}

void CScanContainerWidget::slotUp(int index)
{
  if (index <= 0) return; //do nothing

//  swapCells(index, 1, index - 1, 1);
  slotDown(index - 1);

//  updateIndices();
//  updateTable();
}

void CScanContainerWidget::slotDown(int index)
{
  if (index >= numRows() - 1) return; //do nothing

//  swapCells(index, 1, index + 1, 1);

  insertRows(index + 2);
  swapRows(index, index + 2);

  updateTable();

  removeRow(index);

  updateIndices();
  updateTable();
}

void CScanContainerWidget::slotDel(int index)
{
//  clearCellWidget(index, 0);
//  clearCellWidget(index, 1);
  clearCell(index, 0);
  clearCell(index, 1);
  removeRow(index);

//  if (numRows() == 1) adjustColumn(0);

  updateIndices();
//  setCurrentCell(0, 1);

  updateTable();
//  emit itemDeleted();
}

void CScanContainerWidget::slotCopy(int index)
{emit copyWidget(index);}

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

// repaints the whole table
void CScanContainerWidget::updateTable()
{
  qApp->processEvents();

  int i;

  for (i = 0; i < numRows(); i++)
    adjustRow(i);

  adjustColumn(0);
//  if (numRows() == 1) adjustColumn(0);
  setColumnStretchable(1, true);

  qApp->processEvents();
}

void CScanContainerWidget::enableCopy(const bool & enable)
{mCopyEnabled = enable;}

void CScanContainerWidget::resizeEvent(QResizeEvent *e)
{
  Q3Table::resizeEvent(e);

  int i;

  for (i = 0; i < numRows(); i++)
    adjustRow(i);

  adjustColumn(0);
  setColumnStretchable(1, true);
}
