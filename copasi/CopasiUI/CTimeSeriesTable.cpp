/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CTimeSeriesTable.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/30 09:22:14 $
   End CVS Header */

#include "CTimeSeriesTable.h"

void CTimeSeriesTable::setTimeSeries(const CTimeSeries & ts)
{
  mTS = &ts;
  setNumRows(mTS->getNumSteps());
  setNumCols(mTS->getNumVariables());

  QHeader *tableHeader = horizontalHeader();
  C_INT32 i, imax = mTS->getNumVariables();
  for (i = 0; i < imax; ++i)
    tableHeader->setLabel(i, mTS->getTitle(i).c_str());

  //TODO save old current cell and set afterwards
}

QString CTimeSeriesTable::textForCell(int row, int col)
{
  if (row > mTS->getNumSteps()) return "";
  if (col > mTS->getNumVariables()) return "";

  if (mFlagConc)
    return QString::number(mTS->getConcentrationData(row, col));
  else
    return QString::number(mTS->getData(row, col));
}

void CTimeSeriesTable::showConcentrations(bool conc)
{
  mFlagConc = conc;
  hide(); show(); //TODO: ugly!
}
