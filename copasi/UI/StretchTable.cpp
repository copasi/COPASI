/********************************************************
    Author: Liang Xu
    Version : 1.xx  <first>
    Description: 
    Date: 04/03 
    Comment : Provide automatic stretch for all tables as base class
    Contact: Please contact lixu1@vt.edu.
 *********************************************************/
#include <qmessagebox.h>
#include "StretchTable.h"

StretchTable::StretchTable (QWidget * parent, const char * name):
    QTable (parent, name),
    mProtected(false)
{
  numColumn = 0;
  minColWidth = NULL;
  binitialized = NULL;
  systemUpdate = false;
}

StretchTable::StretchTable(int numRows, int numCols,
                           QWidget * parent, const char * name):
    QTable (numRows, numCols, parent, name),
    mProtected(false)
{
  numColumn = 0;
  minColWidth = NULL;
  binitialized = NULL;
  systemUpdate = false;
  setNumCols(numCols);
  setNumRows(numRows);
}

StretchTable::~StretchTable()
{
  delete[] minColWidth;
  delete[] binitialized;
}

void StretchTable::DisableColWidthUpdate()
{
  systemUpdate = true;
}

void StretchTable::EnableColWidthUpdate()
{
  systemUpdate = false;
}

void StretchTable::columnWidthChanged (int col)
{
  QTable::columnWidthChanged(col);
  if (systemUpdate)
    return;
  if (numColumn == 0)
    return;
  if (binitialized[col])
    binitialized[col] = false;
  else
    minColWidth[col] = columnWidth(col);
}

void StretchTable::setNumCols (int c)
{
  QTable::setNumCols(c);
  if (numColumn > 0)
    {
      delete[] minColWidth;
      delete[] binitialized;
    }
  numColumn = c;
  if (numColumn == 0)
    {
      minColWidth = NULL;
      binitialized = NULL;
      return;
    }
  minColWidth = new int[numColumn];
  binitialized = new bool[numColumn];
  int i;
  for (i = 0; i < numColumn; i++)
    {
      binitialized[i] = true;
      minColWidth[i] = 3;
    }
}

void StretchTable::setNumRows(int r)
{
  if (mProtected)
    QTable::setNumRows(r);
  else
    {
      QTable::setNumRows(r + 1);
      if (r >= 0)
        QTable::setText(r, 0, "Click to add new item");
    }
}

void StretchTable::setProtected(const bool & pRotected)
{mProtected = pRotected;}

bool StretchTable::isProtected() const {return mProtected;}
