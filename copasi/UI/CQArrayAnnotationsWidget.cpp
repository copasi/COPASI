// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQArrayAnnotationsWidget.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/04/02 20:18:01 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <qtable.h>

#include "copasi.h"

#include "CQArrayAnnotationsWidget.h"
#include "qtUtilities.h"

#include "parametertable.h" //for color table item

CColorScale1::CColorScale1()
    : m1(1e-4)
{}

//virtual
QColor CColorScale1::getColor(const C_FLOAT64 & number)
{
  QColor color;
  if (fabs(number) < m1)
    color = QColor(250, 250, 250);
  else if (number > 0)
    color = QColor(200, 255, 200);
  else
    color = QColor(255, 200, 200);
  return color;
}

//**************************

CColorScaleSimple::CColorScaleSimple()
    : mMin(0.0),
    mMax(1.0),
    mLog(false),
    mSym(false)
{}

//virtual
QColor CColorScaleSimple::getColor(const C_FLOAT64 & number)
{
  C_FLOAT64 tmp = (number - mMin) / (mMax - mMin); //scale to 0..1
  if (tmp > 1) tmp = 1;
  if (tmp < 0) tmp = 0;

  int r = 0;
  int g = 0;
  int b = 0;

  if (tmp != tmp)
    {
      r = 85;
      g = 85;
      b = 135;
    }
  else if (tmp < 0.5)
    {
      r = 255;
      g = 255 + (tmp - 0.5) * 260;
      b = 255 + (tmp - 0.5) * 260;
    }
  else
    {
      r = 255 - (tmp - 0.5) * 260;
      g = 255;
      b = 255 - (tmp - 0.5) * 260;
    }

  QColor color(r, g, b);
  return color;
}

//virtual
void CColorScaleSimple::startAutomaticParameterCalculation()
{
  mMin = DBL_MAX;
  mMax = -DBL_MAX;
}

//virtual
void CColorScaleSimple::passValue(const C_FLOAT64 & number)
{
  if (number > mMax) mMax = number;
  if (number < mMin) mMin = number;
}

//virtual
void CColorScaleSimple::finishAutomaticParameterCalculation()
{
  if (mSym)
    {
      C_FLOAT64 tmp;
      if (fabs(mMax) > fabs(mMin))
        tmp = fabs(mMax);
      else
        tmp = fabs(mMin);

      mMin = - tmp;
      mMax = tmp;
    }

  if (mMin == mMax)
    {
      mMin -= 1e-5;
      mMax += 1e-5;
    }
}

//**************************

CColorScaleAverage::CColorScaleAverage()
    : CColorScaleSimple(),
    mFactor(3.0),
    mFloat(0.0),
    mInt(0)
{}

//virtual
void CColorScaleAverage::startAutomaticParameterCalculation()
{
  mInt = 0;
  mFloat = 0;
}

//virtual
void CColorScaleAverage::passValue(const C_FLOAT64 & number)
{
  if (number != number) return; //NaN
  if (fabs(number) >= DBL_MAX) return; //Inf

  ++mInt;
  mFloat += fabs(number);
}

//virtual
void CColorScaleAverage::finishAutomaticParameterCalculation()
{
  if (mInt)
    mMax = mFactor * mFloat / mInt;
  else
    mMax = mFactor;
  mMin = -mMax;

  if (mMin == mMax)
    {
      mMin -= 1e-5;
      mMax += 1e-5;
    }
}

//**************************

CColorScaleBiLog::CColorScaleBiLog()
    : m1(-6.0),
    m2(2.0),
    mFloat(0.0),
    mInt(0)
{}

//virtual
QColor CColorScaleBiLog::getColor(const C_FLOAT64 & number)
{
  C_FLOAT64 logtmp = log(fabs(number));

  C_FLOAT64 tmp = (logtmp - m1) / (m2 - m1); //scale to 0..1
  if (tmp > 1) tmp = 1;
  if (tmp < 0) tmp = 0;

  if (number > 0)
    tmp = 0.5 + tmp * 0.5;
  else
    tmp = 0.5 - tmp * 0.5;

  int r = 0;
  int g = 0;
  int b = 0;

  if (tmp != tmp)
    {
      r = 85;
      g = 85;
      b = 135;
    }
  else if (tmp < 0.5)
    {
      r = 255;
      g = 255 + (tmp - 0.5) * 260;
      b = 255 + (tmp - 0.5) * 260;
    }
  else
    {
      r = 255 - (tmp - 0.5) * 260;
      g = 255;
      b = 255 - (tmp - 0.5) * 260;
    }

  QColor color(r, g, b);
  return color;
}

//virtual
void CColorScaleBiLog::startAutomaticParameterCalculation()
{
  m1 = DBL_MAX;
  m2 = -DBL_MAX;
  mFloat = 0.0;
  mInt = 0;
}

//virtual
void CColorScaleBiLog::passValue(const C_FLOAT64 & number)
{
  if (number != number) return; //NaN
  if (fabs(number) >= DBL_MAX) return; //Inf
  if (number == 0.0) return;

  C_FLOAT64 tmp = log(fabs(number));

  //minmax
  if (tmp > m2) m2 = tmp;
  if (tmp < m1) m1 = tmp;

  //average
  ++mInt;
  mFloat += tmp;
}

//virtual
void CColorScaleBiLog::finishAutomaticParameterCalculation()
{
  if (mInt != 0)
    m1 = (mFloat / mInt) - 4;
  else
    m1 = -4.0;
  m2 -= 1.0;
}

//******************************************************************
//******************************************************************

CQArrayAnnotationsWidget::CQArrayAnnotationsWidget(QWidget* parent, const char* name, WFlags fl)
    : QVBox(parent, name, fl),
    mpColorScale(NULL)
{
  mpSelectionTable = new QTable(this);
  mpSelectionTable->verticalHeader()->hide();
  mpSelectionTable->setLeftMargin(0);
  mpSelectionTable->horizontalHeader()->hide();
  mpSelectionTable->setTopMargin(0);
  mpSelectionTable->setNumCols(2);
  mpSelectionTable->setColumnStretchable(1, true);

  mpSelectionTable->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Fixed);

  mpContentTable = new QTable(this);
  mpContentTable->setReadOnly(true);

  connect(mpSelectionTable, SIGNAL(valueChanged(int, int)),
          this, SLOT(selectionTableChanged(int, int)));
}

CQArrayAnnotationsWidget::~CQArrayAnnotationsWidget()
{
  if (mpColorScale)
    delete mpColorScale;
}

void CQArrayAnnotationsWidget::setColorCoding(CColorScale * cs)
{
  if (mpColorScale)
    delete mpColorScale;
  mpColorScale = cs;
}

void CQArrayAnnotationsWidget::setArrayAnnotation(const CArrayAnnotation * pArray)
{
  mpArray = pArray;

  if (!mpArray)
    {
      clearWidget();
      return;
    }

  CCopasiAbstractArray::index_type index; index.resize(mpArray->dimensionality());

  if (mpArray->dimensionality() == 0)
    {
      mpSelectionTable->setReadOnly(true);
      mpSelectionTable->setNumRows(0);
      fillTable();
    }
  else if (mpArray->dimensionality() == 1)
    {
      mpSelectionTable->setReadOnly(true);
      mpSelectionTable->setNumRows(0);
      mpSelectionTable->setNumRows(1);
      mpSelectionTable->setText(0, 0, "Rows: ");
      mpSelectionTable->setText(0, 1, FROM_UTF8(mpArray->getDimensionDescription(0)));
      mpSelectionTable->adjustColumn(0);

      fillTable(0, index);
    }
  else if (mpArray->dimensionality() == 2)
    {
      mpSelectionTable->setReadOnly(true);
      mpSelectionTable->setNumRows(0);
      mpSelectionTable->setNumRows(2);
      mpSelectionTable->setText(0, 0, "Rows: ");
      mpSelectionTable->setText(0, 1, FROM_UTF8(mpArray->getDimensionDescription(0)));
      mpSelectionTable->setText(1, 0, "Columns: ");
      mpSelectionTable->setText(1, 1, FROM_UTF8(mpArray->getDimensionDescription(1)));
      mpSelectionTable->adjustColumn(0);

      //std::cout << "width: " << mpSelectionTable->width()<< " height: " <<mpSelectionTable->height() << std::endl;
      //std::cout << "cwidth: " << mpSelectionTable->contentsWidth()<< " cheight: " <<mpSelectionTable->contentsHeight() << std::endl;
      //std::cout << "minH: " << mpSelectionTable->minimumHeight() << " maxH: " << mpSelectionTable->maximumHeight() << std::endl;
      //std::cout << "size hint: " << mpSelectionTable->sizeHint().height() << std::endl << std::endl;
      //mpSelectionTable->resize(5, 5);

      fillTable(0, 1, index);
    }
  else
    {
      initSelectionTable();
      fillTable(0, 1, index);
    }
}

void CQArrayAnnotationsWidget::initSelectionTable()
{
  mpSelectionTable->setReadOnly(false);
  mpSelectionTable->setColumnReadOnly(0, true);
  mpSelectionTable->setColumnReadOnly(1, false);

  C_INT32 i, imax = mpArray->dimensionality();
  mpSelectionTable->setNumRows(0);
  mpSelectionTable->setNumRows(imax);

  for (i = 0; i < imax; ++i)
    {
      mpSelectionTable->setText(i, 0, FROM_UTF8(mpArray->getDimensionDescription(i)));

      //combo box
      QStringList combolist;
      vectorOfStrings2QStringList(mpArray->getAnnotationsString(i), combolist);
      combolist.prepend("In columns");
      combolist.prepend("In rows");

      mpSelectionTable->setItem(i, 1, new QComboTableItem(mpSelectionTable, combolist));
      //mpSelectionTable->adjustRow(i);

      //set first combobox to "In rows", second to "In colums" and all other to the
      //first object in the annotations list
      if (i < 2)
        setCurrentItem(i, i);
      else
        setCurrentItem(i, 2);
    }

  mpSelectionTable->adjustColumn(0);
  //mpSelectionTable->adjustColumn(1);

  //store the active item of all combo boxes
  storeCurrentCombos();
}

void CQArrayAnnotationsWidget::storeCurrentCombos()
{
  C_INT32 i, imax = mpArray->dimensionality();
  combos.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      C_INT32 tmp = currentItem(i);
      if (tmp >= 2)
        combos[i] = 2;
      else
        combos[i] = tmp;
    }
}

void CQArrayAnnotationsWidget::clearWidget()
{
  //mpSelectionTable->setNumCols(2);
  mpSelectionTable->setNumRows(0);
  mpContentTable->setNumCols(0);
  mpContentTable->setNumRows(0);
}

C_INT32 CQArrayAnnotationsWidget::currentItem(C_INT32 row)
{
  QComboTableItem * item = dynamic_cast<QComboTableItem*>
                           (mpSelectionTable->item(row, 1));

  if (!item) return - 1;

  return item->currentItem();
}

void CQArrayAnnotationsWidget::setCurrentItem(C_INT32 row, C_INT32 index)
{
  storeCurrentCombos();
  QComboTableItem * item = dynamic_cast<QComboTableItem*>
                           (mpSelectionTable->item(row, 1));

  if (!item) return;

  item->setCurrentItem(index);
}

//slot
void CQArrayAnnotationsWidget::selectionTableChanged(int row, int col)
{
  //std::cout << row << " " << col << std::endl;

  if (col != 1) return;

  C_INT32 newValue = currentItem(row);

  //no combobox
  if (-1 == newValue) goto finish;

  //no change
  if (newValue == combos[row]) goto finish;

  //neither "row" nor "column"
  if ((newValue >= 2) && (combos[row] >= 2)) goto finish;

  if (newValue == 0) //new value is "row"
    {
      //find out which line was "row" before
      C_INT32 i, imax = mpArray->dimensionality();
      for (i = 0; i < imax; ++i)
        if (combos[i] == 0)
          setCurrentItem(i, combos[row]);
    }

  if (newValue == 1) //new value is "column"
    {
      //find out which line was "col" before
      C_INT32 i, imax = mpArray->dimensionality();
      for (i = 0; i < imax; ++i)
        if (combos[i] == 1)
          setCurrentItem(i, combos[row]);
    }

  if (newValue >= 2) //new value is neither "col" nor "row"
    {
      //find a line which was neither "col" nor "row"  before
      C_INT32 i, imax = mpArray->dimensionality();
      for (i = 0; i < imax; ++i)
        if (combos[i] >= 2)
          {
            setCurrentItem(i, combos[row]);
            break;
          }
    }

finish:
  //call fillTable()
  {
    CCopasiAbstractArray::index_type index; index.resize(mpArray->dimensionality());
    C_INT32 rowindex, colindex;
    C_INT32 i, imax = mpArray->dimensionality();
    for (i = 0; i < imax; ++i)
      {
        C_INT32 tmp = currentItem(i);

        //set index
        if (tmp < 2)  //row or column
          index[i] = 0;
        else
          index[i] = tmp - 2;

        //set rowindex
        if (0 == tmp)
          rowindex = i;

        //set colindex
        if (1 == tmp)
          colindex = i;
      }

    fillTable(rowindex, colindex, index);
  }

  storeCurrentCombos();
}

void CQArrayAnnotationsWidget::fillTable(unsigned C_INT32 rowIndex, unsigned C_INT32 colIndex,
    CCopasiAbstractArray::index_type & index)
{
  if (!mpArray) return;
  assert(rowIndex < index.size());
  assert(colIndex < index.size());

  mpContentTable->setNumCols(mpArray->size()[colIndex]);
  mpContentTable->setNumRows(mpArray->size()[rowIndex]);

  std::vector<std::string> rowdescr = mpArray->getAnnotationsString(rowIndex);
  std::vector<std::string> coldescr = mpArray->getAnnotationsString(colIndex);

  unsigned C_INT32 i, imax = mpArray->size()[rowIndex];
  unsigned C_INT32 j, jmax = mpArray->size()[colIndex];

  //annotations
  for (i = 0; i < imax; ++i)
    {
      mpContentTable->verticalHeader()->setLabel(i, FROM_UTF8(rowdescr[i]));
    }
  for (j = 0; j < jmax; ++j)
    {
      mpContentTable->horizontalHeader()->setLabel(j, FROM_UTF8(coldescr[j]));
    }

  //automatic color scaling
  if (mAutomaticColorScaling)
    {
      mpColorScale->startAutomaticParameterCalculation();

      for (i = 0; i < imax; ++i)
        for (j = 0; j < jmax; ++j)
          {
            index[rowIndex] = i;
            index[colIndex] = j;
            mpColorScale->passValue((*mpArray->array())[index]);
          }

      mpColorScale->finishAutomaticParameterCalculation();
    }

  //table contents
  for (i = 0; i < imax; ++i)
    for (j = 0; j < jmax; ++j)
      {
        index[rowIndex] = i;
        index[colIndex] = j;

        if (!mpColorScale)
          {
            mpContentTable->setText(i, j, QString::number((*mpArray->array())[index]));
          }
        else
          {
            C_FLOAT64 number = (*mpArray->array())[index];
            QColor color = mpColorScale->getColor(number);
            mpContentTable->setItem(i, j, new ColorTableItem(mpContentTable, QTableItem::Never, color,
                                    QString::number(number)));
          }
      }
}

void CQArrayAnnotationsWidget::fillTable(unsigned C_INT32 rowIndex,
    CCopasiAbstractArray::index_type & index)
{
  if (!mpArray) return;
  assert(rowIndex < index.size());

  mpContentTable->setNumCols(1);
  mpContentTable->setNumRows(mpArray->size()[rowIndex]);

  mpContentTable->horizontalHeader()->setLabel(0, "");

  unsigned C_INT32 i, imax = mpArray->size()[rowIndex];

  //automatic color scaling
  if (mAutomaticColorScaling)
    {
      mpColorScale->startAutomaticParameterCalculation();

      for (i = 0; i < imax; ++i)
        {
          index[rowIndex] = i;
          mpColorScale->passValue((*mpArray->array())[index]);
        }

      mpColorScale->finishAutomaticParameterCalculation();
    }

  //table contents and annotations
  const std::vector<std::string> & rowdescr = mpArray->getAnnotationsString(rowIndex);
  for (i = 0; i < imax; ++i)
    {
      index[rowIndex] = i;
      mpContentTable->verticalHeader()->setLabel(i, FROM_UTF8(rowdescr[i]));
      if (!mpColorScale)
        {
          mpContentTable->setText(i, 0, QString::number((*mpArray->array())[index]));
        }
      else
        {
          C_FLOAT64 number = (*mpArray->array())[index];
          QColor color = mpColorScale->getColor(number);
          mpContentTable->setItem(i, 0, new ColorTableItem(mpContentTable, QTableItem::Never, color,
                                  QString::number(number)));
        }
    }
}

void CQArrayAnnotationsWidget::fillTable()
{
  if (!mpArray) return;

  mpContentTable->setNumCols(0);
  mpContentTable->setNumRows(0);
  mpContentTable->setNumCols(1);
  mpContentTable->setNumRows(1);

  mpContentTable->horizontalHeader()->setLabel(0, "");
  mpContentTable->verticalHeader()->setLabel(0, "");

  CCopasiAbstractArray::index_type index; index.resize(0);
  //mpContentTable->verticalHeader()->setLabel(i, FROM_UTF8(rowdescr[i]));
  mpContentTable->setText(0, 0, QString::number((*mpArray->array())[index]));
}
