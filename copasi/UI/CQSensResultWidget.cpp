/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSensResultWidget.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: ssahle $
   $Date: 2007/01/05 16:35:01 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//#include <qpushbutton.h>
#include <qlayout.h>
#include <qlineedit.h>
#include <qlabel.h>
#include <qtable.h>

#include "copasi.h"

#include "CQSensResultWidget.h"
//#include "StateSubwidget.h"
//#include "CTimeSeriesTable.h"
#include "qtUtilities.h"
#include "sensitivities/CSensTask.h"
#include "sensitivities/CSensProblem.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiVector.h"

#include "parametertable.h" //for color table item
//#include "report/CKeyFactory.h"
//#include "model/CModel.h"

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

  if (tmp < 0.5)
    {
      r = 255;
      g = 255 + (tmp - 0.5) * 220;
      b = 255 + (tmp - 0.5) * 220;
    }
  else
    {
      r = 255 - (tmp - 0.5) * 220;
      g = 255;
      b = 255 - (tmp - 0.5) * 220;
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
  ++mInt;
  mFloat += fabs(number);
}

//virtual
void CColorScaleAverage::finishAutomaticParameterCalculation()
{
  mMax = mFactor * mFloat / mInt;
  mMin = -mMax;
}

//******************************************************************
//******************************************************************

ArrayAnnotationsWidget::ArrayAnnotationsWidget(QWidget* parent, const char* name, WFlags fl)
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

ArrayAnnotationsWidget::~ArrayAnnotationsWidget()
{
  if (mpColorScale)
    delete mpColorScale;
}

void ArrayAnnotationsWidget::setArrayAnnotation(const CArrayAnnotation * pArray)
{
  mpArray = pArray;

  if (!mpArray)
    {
      clearWidget();
      return;
    }

  CCopasiAbstractArray::index_type index; index.resize(mpArray->dimensionality());

  if (mpArray->dimensionality() == 0)
  {}
  else if (mpArray->dimensionality() == 1)
    {
      mpSelectionTable->setReadOnly(true);
      mpSelectionTable->setNumRows(1);
      mpSelectionTable->setText(0, 0, "Rows: ");
      mpSelectionTable->setText(0, 1, FROM_UTF8(mpArray->getDimensionDescription(0)));
      mpSelectionTable->adjustColumn(0);

      fillTable(0, index);
    }
  else if (mpArray->dimensionality() == 2)
    {
      mpSelectionTable->setReadOnly(true);
      mpSelectionTable->setNumRows(2);
      mpSelectionTable->setText(0, 0, "Rows: ");
      mpSelectionTable->setText(0, 1, FROM_UTF8(mpArray->getDimensionDescription(0)));
      mpSelectionTable->setText(1, 0, "Columns: ");
      mpSelectionTable->setText(1, 1, FROM_UTF8(mpArray->getDimensionDescription(1)));
      mpSelectionTable->adjustColumn(0);

      fillTable(0, 1, index);
    }
  else
    {
      initSelectionTable();
      fillTable(0, 1, index);
    }
}

void ArrayAnnotationsWidget::initSelectionTable()
{
  mpSelectionTable->setReadOnly(false);
  mpSelectionTable->setColumnReadOnly(0, true);
  mpSelectionTable->setColumnReadOnly(1, false);

  C_INT32 i, imax = mpArray->dimensionality();
  mpSelectionTable->setNumRows(imax);

  for (i = 0; i < imax; ++i)
    {
      mpSelectionTable->setText(i, 0, FROM_UTF8(mpArray->getDimensionDescription(i)));

      //combo box
      QStringList combolist;
      vectorOfStrings2QStringList(mpArray->getAnnotationsDisplay(i), combolist);
      combolist.prepend("In columns");
      combolist.prepend("In rows");

      mpSelectionTable->setItem(i, 1, new QComboTableItem(mpSelectionTable, combolist));

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

void ArrayAnnotationsWidget::storeCurrentCombos()
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

void ArrayAnnotationsWidget::clearWidget()
{
  //mpSelectionTable->setNumCols(2);
  mpSelectionTable->setNumRows(0);
  mpContentTable->setNumCols(0);
  mpContentTable->setNumRows(0);
}

C_INT32 ArrayAnnotationsWidget::currentItem(C_INT32 row)
{
  QComboTableItem * item = dynamic_cast<QComboTableItem*>
                           (mpSelectionTable->item(row, 1));

  if (!item) return - 1;

  return item->currentItem();
}

void ArrayAnnotationsWidget::setCurrentItem(C_INT32 row, C_INT32 index)
{
  storeCurrentCombos();
  QComboTableItem * item = dynamic_cast<QComboTableItem*>
                           (mpSelectionTable->item(row, 1));

  if (!item) return;

  item->setCurrentItem(index);
}

//slot
void ArrayAnnotationsWidget::selectionTableChanged(int row, int col)
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

void ArrayAnnotationsWidget::fillTable(unsigned C_INT32 rowIndex, unsigned C_INT32 colIndex,
                                       CCopasiAbstractArray::index_type & index)
{
  if (!mpArray) return;
  assert(rowIndex < index.size());
  assert(colIndex < index.size());

  mpContentTable->setNumCols(mpArray->size()[colIndex]);
  mpContentTable->setNumRows(mpArray->size()[rowIndex]);

  std::vector<std::string> rowdescr = mpArray->getAnnotationsDisplay(rowIndex);
  std::vector<std::string> coldescr = mpArray->getAnnotationsDisplay(colIndex);

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

void ArrayAnnotationsWidget::fillTable(unsigned C_INT32 rowIndex,
                                       CCopasiAbstractArray::index_type & index)
{
  if (!mpArray) return;
  assert(rowIndex < index.size());

  mpContentTable->setNumCols(1);
  mpContentTable->setNumRows(mpArray->size()[rowIndex]);

  const std::vector<std::string> & rowdescr = mpArray->getAnnotationsDisplay(rowIndex);

  unsigned C_INT32 i, imax = mpArray->size()[rowIndex];
  for (i = 0; i < imax; ++i)
    {
      index[rowIndex] = i;
      mpContentTable->verticalHeader()->setLabel(i, FROM_UTF8(rowdescr[i]));
      mpContentTable->setText(i, 0, QString::number((*mpArray->array())[index]));
    }
}

//*******************************************************************************************

#include <qtabwidget.h>

/*
 *  Constructs a CQSensResultWidget which is a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQSensResultWidget::CQSensResultWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    mpResult(NULL)
{
  if (!name)
    setName("CQSensResultWidget");
  setCaption("CQSensResultWidget");

  mWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "CQSensResultWidgetLayout");

  // **********  Label **************
  mLabelTitle = new QLabel(this, "SensLabel");
  mLabelTitle->setText("Sensitivities");
  mLabelTitle->setAlignment(int(QLabel::AlignVCenter
                                | QLabel::AlignLeft));
  mLabelTitle->setSizePolicy(QSizePolicy::Fixed, QSizePolicy::Fixed);
  mWidgetLayout->addWidget(mLabelTitle, 0, 0);

  // tab widget
  mpTab = new QTabWidget(this, "TabWidget");
  mWidgetLayout->addMultiCellWidget(mpTab, 1, 2, 0, 2);

  // unscaled array
  mArrayWidget = new ArrayAnnotationsWidget(mpTab, "ArrayWidget");
  //mArrayWidget->setColorCoding(new CColorScale1());
  CColorScaleAverage * tcs = new CColorScaleAverage();
  mArrayWidget->setColorCoding(tcs);
  //tcs->setMinMax(-1,1);
  //tcs->setSymmetric(true);
  tcs->setFactor(3.0);
  mArrayWidget->setColorScalingAutomatic(true);
  mpTab->addTab(mArrayWidget, "unscaled");

  //scaled array
  mArrayWidgetScaled = new ArrayAnnotationsWidget(mpTab, "ArrayWidget2");
  //mArrayWidgetScaled->setColorCoding(new CColorScale1());
  tcs = new CColorScaleAverage();
  mArrayWidgetScaled->setColorCoding(tcs);
  //tcs->setMinMax(-1,1);
  //tcs->setSymmetric(true);
  tcs->setFactor(3.0);
  mArrayWidgetScaled->setColorScalingAutomatic(true);
  mpTab->addTab(mArrayWidgetScaled, "scaled");
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQSensResultWidget::~CQSensResultWidget()
{}

void CQSensResultWidget::newResult()
{
  CSensTask * pTask =
    dynamic_cast<CSensTask*>((*CCopasiDataModel::Global->getTaskList())["Sensitivities"]);
  if (!pTask)
    {
      clearArrays();
      return;
    }

  CSensProblem * pProblem = dynamic_cast< CSensProblem * >(pTask->getProblem());
  if (!pProblem)
    {
      clearArrays();
      return;
    }

  mpResult = pProblem->getResultAnnotated();
  mpScaledResult = pProblem->getScaledResultAnnotated();

  mArrayWidget->setArrayAnnotation(mpResult);
  mArrayWidgetScaled->setArrayAnnotation(mpScaledResult);
}

void CQSensResultWidget::clearArrays()
{
  mArrayWidget->setArrayAnnotation(NULL);
  mArrayWidgetScaled->setArrayAnnotation(NULL);
}

//*************************************

bool CQSensResultWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action
                                C_UNUSED(action), const std::string & C_UNUSED(key))
{
  /*  if (this->isShown())
      return loadFromBackend();
    else
      return true;*/
  return true;
}

bool CQSensResultWidget::leave()
{
  return true;
}

bool CQSensResultWidget::enter(const std::string & C_UNUSED(key))
{
  //clear the widget if the pointer to the result has changed
  CSensTask * pTask =
    dynamic_cast<CSensTask*>((*CCopasiDataModel::Global->getTaskList())["Sensitivities"]);
  if (!pTask)
    {
      clearArrays();
      return false;
    }

  CSensProblem * pProblem = dynamic_cast< CSensProblem * >(pTask->getProblem());
  if (!pProblem)
    {
      clearArrays();
      return false;
    }

  if (mpResult != pProblem->getResultAnnotated())
    {
      clearArrays();
      return false;
    }

  return true;
}
