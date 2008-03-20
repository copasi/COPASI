// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/miase/CMiaseOutput.cpp,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: aruff $
//   $Date: 2008/03/20 14:28:52 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CMiaseOutput.h"

CMiaseColumn::CMiaseColumn() : CMiaseBase()
{}

CMiaseColumn::~CMiaseColumn()
{}

std::string CMiaseColumn::getId()
{
  return mId;
}

std::string CMiaseColumn::getName()
{
  return mName;
}

void CMiaseColumn::setId(std::string id)
{
  mId = id;
}

void CMiaseColumn::setName(std::string name)
{
  mName = name;
}

//*****************************************************************************

CMiasePlot2D::CMiasePlot2D() : CMiaseBase()
{}

CMiasePlot2D::~CMiasePlot2D()
{}

std::string CMiasePlot2D::getId()
{
  return mId;
}

std::string CMiasePlot2D::getName()
{
  return mName;
}

void CMiasePlot2D::setId(std::string id)
{
  mId = id;
}

void CMiasePlot2D::setName(std::string name)
{
  mName = name;
}

std::string CMiasePlot2D::getXData()
{
  return mXData;
}

std::string CMiasePlot2D::getVData()
{
  return mVData;
}

void CMiasePlot2D::setXData(std::string xData)
{
  mXData = xData;
}

void CMiasePlot2D::setVData(std::string vData)
{
  mVData = vData;
}

//*****************************************************************************

CMiaseOutput::CMiaseOutput() : CMiaseBaseEnhanced()
{}

CMiaseOutput::~CMiaseOutput()
{
  mListOfColumns.clear();
}

void CMiaseOutput::addColumn (CMiaseColumn* column)
{
  mListOfColumns.push_back(column);
}

CMiaseColumn* CMiaseOutput::getColumn(int num)
{
  return mListOfColumns[ num ];
}

CMiaseColumn* CMiaseOutput::getLastColumn()
{
  return mListOfColumns[ mListOfColumns.size() ];
}

void CMiaseOutput::setPlot2D (CMiasePlot2D* plot2d)
{
  mPlot2D = plot2d;
}

CMiasePlot2D* CMiaseOutput::getPlot2D()
{
  return mPlot2D;
}
