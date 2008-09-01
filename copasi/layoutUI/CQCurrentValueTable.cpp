// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQCurrentValueTable.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/09/01 09:45:48 $
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
#include "layoutUI/CQLayoutMainWindow.h"

CQCurrentValueTable::CQCurrentValueTable(QWidget *parent, const char *name)
    : QTable(parent, name)
{
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
  header = this->verticalHeader();
  header->hide();
  setLeftMargin(0);
  setText(0, 0, "*** no time series load ***");
  setText(0, 1, "NaN");
  setColumnReadOnly(1, TRUE);
  //connect(this, SIGNAL(clicked(int, int, int, const QPoint &)), this, SLOT(mouseClickedOverTable(int, int, int, const QPoint &)));
  connect(this, SIGNAL(valueChanged(int, int)), this, SLOT(valChanged(int, int)));
  resize(QSize(202, 143).expandedTo(minimumSizeHint()));
}

CQCurrentValueTable::~CQCurrentValueTable()
{}

// sets complete row: 1. name of reactant 2. concentration (or number of particles) value
void CQCurrentValueTable::setRowInTable(int row, std::string key, std::string s, C_FLOAT64 val)
{
  QCheckTableItem * checkItem = new QCheckTableItem(this, FROM_UTF8(s));
  checkItem->setChecked(true); // initially checked
  this->setItem(row, 0, checkItem);
  this->setText(row, 1, QString::number(val));
  this->setKeyIndex(key, row); // remember which node key is in which row
}

// changes the value in a given row (value in second column is replaced)
void CQCurrentValueTable::updateRowInTable(int row, C_FLOAT64 val)
{
  this->setText(row, 1, QString::number(val));
}

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
          CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
          assert(tmp);
          if (tmp)
            tmp->addItemInAnimation(this->getKeyForRow(i));
          //tmp->addItemInAnimation(checkItem->text());
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
          // set checkbox item unchecked
          checkItem->setChecked(false);
          CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
          assert(tmp);
          if (tmp)
            tmp->removeItemInAnimation(this->getKeyForRow(i));
          //tmp->removeItemInAnimation(checkItem->text());
        }
    }
}

// void CQCurrentValueTable::mouseClickedOverTable(int row, int col , int button, const QPoint & mousepos)
// {
//   //std::cout << row << "  :  " << col << std::endl;
//   if (col == 0)
//     {
//       QTableItem *cell = this->item(row, 0);
//       if (cell->rtti() == 2)
//         {// is cell a QCheckTableItem?
//           QCheckTableItem *checkItem = dynamic_cast<QCheckTableItem *> (cell);
//    std::cout << checkItem->text() << std::endl;
//}
//}
//}

void CQCurrentValueTable::valChanged(int row, int col)
{
  if (col == 0)
    {
      QTableItem *cell = this->item(row, 0);
      if (cell->rtti() == 2)
        {// is cell a QCheckTableItem?
          QCheckTableItem *checkItem = dynamic_cast<QCheckTableItem *> (cell);
          //std::cout << checkItem->text() << std::endl;
          CQLayoutMainWindow * tmp = dynamic_cast<CQLayoutMainWindow *>(parentWidget()->parentWidget()->parentWidget()->parentWidget());
          assert(tmp);
          if (tmp)
            {
              if (checkItem->isChecked())
                tmp->addItemInAnimation(this->getKeyForRow(row));
              //tmp->addItemInAnimation(checkItem->text());
              else
                tmp->removeItemInAnimation(this->getKeyForRow(row));
              //tmp->removeItemInAnimation(checkItem->text());
            }
        }
    }
}

//store row index for every node key
void CQCurrentValueTable::setKeyIndex(std::string key, int row)
{
  indexMap.insert(std::pair<int, std::string>
                  (row,
                   key));
}

std::string CQCurrentValueTable::getKeyForRow(int row)
{
  std::string s = "";

  std::map<int, std::string>::iterator itIndexObj = indexMap.find(row);
  if (itIndexObj != indexMap.end())
    s = (*itIndexObj).second;

  return s;
}
