// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQCurrentValueTable.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/04/28 12:05:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <iostream>

#include <qheader.h>

#include "copasi.h"

#include "UI/qtUtilities.h"

#include "CQCurrentValueTable.h"

CQCurrentValueTable::CQCurrentValueTable(QWidget *parent, const char *name)
{
  QTable(parent, name);

  init();
  this->show();
}

void CQCurrentValueTable::init()
{
  setNumRows(1);
  setNumCols(2);
  // set default entry
  QHeader *header = this->horizontalHeader();
  header->setLabel(0, "Metabolite");
  header->setLabel(1, "Concentration");
  setText(0, 0, "*** no time series load ***");
  setText(0, 1, "NaN");
  setColumnReadOnly(1, TRUE);
  connect(this, SIGNAL(clicked(int, int, int, const QPoint &)), this, SLOT(mouseClickedOverTable(int, int, int, const QPoint &)));
}

CQCurrentValueTable::~CQCurrentValueTable()
{}

// sets complete row: 1. name of reactant 2. concentration (or number of particles) value
void CQCurrentValueTable::setRowInTable(int row, std::string s, C_FLOAT64 val)
{
  this->setItem(row, 0, new QCheckTableItem(this, FROM_UTF8(s)));
  this->setText(row, 1, QString::number(val));
}

void CQCurrentValueTable::setValues(CDataEntity *dataSet)
{}

// sets (numerical) value as text into the second column of the corresponding reactant (given by row index)
void CQCurrentValueTable::setValue(int row, C_FLOAT64 val)
{
  this->setText(row, 1, QString::number(val));
}

void CQCurrentValueTable::setAllBoxesChecked()
{
  int i;
  for (i = 0;i < numRows();i++)
    {
      QTableItem *cell = this->item(i, 0);
      if (cell->rtti() == 2)
        {// is cell a QCheckTableItem?
          QCheckTableItem *checkItem = dynamic_cast<QCheckTableItem *> (cell);
          // set checkbox item checked
          checkItem->setChecked(true);
        }
    }
}

void CQCurrentValueTable::setAllBoxesUnchecked()
{
  int i;
  for (i = 0;i < numRows();i++)
    {
      QTableItem *cell = this->item(i, 0);
      if (cell->rtti() == 2)
        {// is cell a QCheckTableItem?
          QCheckTableItem *checkItem = dynamic_cast<QCheckTableItem *> (cell);
          // set checkbox item checked
          checkItem->setChecked(false);
        }
    }
}

void CQCurrentValueTable::mouseClickedOverTable(int row, int col , int button, const QPoint & mousepos)
{
  std::cout << "mouseClickedOverTable" << std::endl;
}
