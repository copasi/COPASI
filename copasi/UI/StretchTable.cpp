#include <qmessagebox.h>
#include "StretchTable.h"

StretchTable::StretchTable (QWidget * parent, const char * name)
    : QTable (parent, name)
{
  numColumn = 0;
  minColWidth = NULL;
  binitialized = NULL;
  systemUpdate = false;
}

StretchTable::StretchTable(int numRows, int numCols, QWidget * parent, const char * name)
    : QTable (numRows, numCols, parent, name)
{
  numColumn = 0;
  minColWidth = NULL;
  binitialized = NULL;
  systemUpdate = false;
  setNumCols(numCols);
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

void StretchTable::setNumCols (int r)
{
  QTable::setNumCols(r);
  if (numColumn > 0)
    {
      delete[] minColWidth;
      delete[] binitialized;
    }
  numColumn = r;
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
