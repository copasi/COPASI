// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi/copasi.h"
#include <iostream>

#include <QApplication>
#include <QResizeEvent>
#include <QHeaderView>

#include "CScanContainerWidget.h"
#include "CScanWidgetScan.h"
#include "CScanWidgetRepeat.h"
#include "CScanWidgetRandom.h"
#include "CUpDownSubwidget.h"

#include <copasi/core/CRootContainer.h>
#include <copasi/commandline/CConfigurationFile.h>

CScanContainerWidget::CScanContainerWidget(QWidget * parent, const char * name) :
  QTableWidget(parent)
{
  if (!name)
    setObjectName("CScanContainerWidget");

  horizontalHeader()->setStretchLastSection(true);

  horizontalHeader()->hide();
  verticalHeader()->hide();

  setShowGrid(false);

  setColumnCount(2);
  setAutoScroll(true);

  setSelectionMode(QAbstractItemView::NoSelection);

  setTabKeyNavigation(false);

  mCopyEnabled = false;
  //TODO maybe reimplement paintFocus() to make the focus completely invisible
  // (it is already invisible most of the time)
}

CScanContainerWidget::~CScanContainerWidget()
{}

std::vector<QWidget*> CScanContainerWidget::getWidgetList() const
{
  std::vector< QWidget * > ret;
  QWidget* tmpWidget;

  int i, imax = rowCount();

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
  setRowCount(0);
}

void CScanContainerWidget::addWidget(QWidget * widget, bool controls)
{
  setRowCount(rowCount() + 1);

  int i = rowCount() - 1;

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

  updateIndices();
  updateTable();
}

void CScanContainerWidget::insertWidget(QWidget* widget, int row)
{
  if (row == -1)
    {
      if (rowCount() == 0)
        row = 0;
      else
        row = rowCount() - 1;
    }

  insertRow(row);

  unsigned C_INT32 i = row;

  if (true) //add control widget
    {
      CUpDownSubwidget * tmpUD = new CUpDownSubwidget(this);
      tmpUD->enableCopy(mCopyEnabled);

      connect(tmpUD, SIGNAL(del(int)), this, SLOT(slotDel(int)));
      connect(tmpUD, SIGNAL(up(int)), this, SLOT(slotUp(int)));
      connect(tmpUD, SIGNAL(down(int)), this, SLOT(slotDown(int)));
      connect(tmpUD, SIGNAL(copy(int)), this, SLOT(slotCopy(int)));

      setCellWidget(i, 0, tmpUD);
    }

  setCellWidget(i, 1, widget);

  updateIndices();
  updateTable();
}

void CScanContainerWidget::slotUp(int index)
{
  if (index <= 0) return; //do nothing

  slotDown(index - 1);
}

void CScanContainerWidget::slotDown(int index)
{
  if (index >= rowCount() - 1) return; //do nothing

  QWidget * pWidget = cellWidget(index, 1);
  QWidget * pNewWidget = NULL;

  if (pWidget->objectName() == "CScanWidgetScan")
    {
      static_cast< CScanWidgetScan * >(pWidget)->save(NULL);
      pNewWidget = new CScanWidgetScan(*static_cast< CScanWidgetScan * >(pWidget), this);
    }
  else if (pWidget->objectName() == "CScanWidgetRandom")
    {
      static_cast< CScanWidgetRandom * >(pWidget)->save(NULL);
      pNewWidget = new CScanWidgetRandom(*static_cast< CScanWidgetRandom * >(pWidget), this);
    }
  else if (pWidget->objectName() == "CScanWidgetRepeat")
    {
      static_cast< CScanWidgetRepeat * >(pWidget)->save(NULL);
      pNewWidget = new CScanWidgetRepeat(*static_cast< CScanWidgetRepeat * >(pWidget), this);
    }

  if (pNewWidget != NULL)
    {
      removeRow(index);
      insertWidget(pNewWidget, index + 1);
    }
}

void CScanContainerWidget::slotDel(int index)
{
  removeRow(index);

  updateIndices();
  updateTable();
}

void CScanContainerWidget::slotCopy(int index)
{emit copyWidget(index);}

void CScanContainerWidget::updateIndices()
{
  //update the indices of the updown widgets
  CUpDownSubwidget* tmp, *tmp_last, *tmp_next;

  C_INT32 i, imax = rowCount();

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

  resizeRowsToContents();
  resizeColumnsToContents();
}

void CScanContainerWidget::enableCopy(const bool & enable)
{mCopyEnabled = enable;}

void CScanContainerWidget::resizeEvent(QResizeEvent *e)
{
  QTableWidget::resizeEvent(e);

  resizeRowsToContents();
  resizeColumnsToContents();
}
