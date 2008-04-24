// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/CQCurrentValueTable.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: urost $
//   $Date: 2008/04/24 12:22:30 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <iostream>

#include <qheader.h>

#include "copasi.h"

#include "CQCurrentValueTable.h"

CQCurrentValueTable::CQCurrentValueTable(QWidget *parent, const char *name)
{
  QTable(parent, name);
  setNumRows(1);
  setNumCols(2);
  setColumnReadOnly(1, TRUE);
}

CQCurrentValueTable::CQCurrentValueTable(int numRows, int numCols, QWidget *parent, const char *name)
{
  QTable(parent, name);
  setNumRows(numRows);
  setNumCols(2);
  setColumnReadOnly(1, TRUE);
  QHeader *header = this->horizontalHeader();
  header->setLabel(0, "Metabolite");
  header->setLabel(1, "Concentration");
}

CQCurrentValueTable::~CQCurrentValueTable()
{}

// sets complete row: 1. name of reactant 2. concentration (or number of particles) value
void CQCurrentValueTable::setRowInTable(int row, std::string s, C_FLOAT64 val)
{
  std::string & t = s;
  this->setItem(row, 0, new QCheckTableItem(this, QString(t)));
  this->setText(row, 1, QString::number(val));
}

void CQCurrentValueTable::setValues(CDataEntity *dataSet)
{}

// sets (numerical) value as text into the second column of the corresponding reactant (given by row index)
void CQCurrentValueTable::setValue(int row, C_FLOAT64 val)
{
  this->setText(row, 1, QString::number(val));
}
