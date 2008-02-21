// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CTimeSeriesTable.cpp,v $
//   $Revision: 1.7.4.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/21 19:12:55 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CTimeSeriesTable.h"
#include "qtUtilities.h"

void CTimeSeriesTable::setTimeSeries(const CTimeSeries * pTS)
{
  mpTS = pTS;
  if (mpTS != NULL)
    {
      setNumRows(mpTS->getNumSteps());
      setNumCols(mpTS->getNumVariables());

      QHeader *tableHeader = horizontalHeader();
      C_INT32 i, imax = mpTS->getNumVariables();
      for (i = 0; i < imax; ++i)
        tableHeader->setLabel(i, FROM_UTF8(mpTS->getTitle(i)));
    }
  else
    {
      setNumRows(0);
      setNumCols(0);
    }
  // :TODO: save old current cell and set afterwards
}

QString CTimeSeriesTable::textForCell(unsigned int row, unsigned int col)
{
  if (mpTS == NULL) return "";
  if (row > mpTS->getNumSteps()) return "";
  if (col > mpTS->getNumVariables()) return "";

  if (mFlagConc)
    return QString::number(mpTS->getConcentrationData(row, col));
  else
    return QString::number(mpTS->getData(row, col));
}

void CTimeSeriesTable::showConcentrations(bool conc)
{
  mFlagConc = conc;
  hide(); show(); //TODO: ugly!
}

const CTimeSeries* CTimeSeriesTable::getTimeSeries()
{
  return mpTS;
}

bool CTimeSeriesTable::doShowConcentrations() const
  {
    return this->mFlagConc;
  }
