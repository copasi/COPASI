// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQArrayAnnotationsWidget.cpp,v $
//   $Revision: 1.45 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/08/22 21:39:54 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qlayout.h>
#include <q3table.h>
#include <qlabel.h>

#ifdef SunOS
#include <ieeefp.h>
#else
#include <math.h>
#endif

#include "copasi.h"

#include "CQArrayAnnotationsWidget.h"
#include "qtUtilities.h"
#include "CQComboDelegate.h"

#include "parametertable.h" //for color table item
#include <iostream>

#include "barChart/qwt3dPlot.h"

#ifdef DEBUG_UI
#include <QtDebug>
#endif

CQArrayAnnotationsWidget::CQArrayAnnotationsWidget(QWidget* parent, const char* name,
    bool /* barChart */ , bool slider) :
    QWidget(parent, name),
    mWithBarChart(false),
    mUseSliders(slider),
    data(NULL),
    mColors(),
    mpArray(NULL),
    mpColorScale(NULL),
    mAutomaticColorScaling(false),
    mRowIndex(C_INVALID_INDEX),
    mColIndex(C_INVALID_INDEX),
    mIndex(),
    mBarChartFilled(false),
    mOneDimensional(false),
    mComboEntries(),
    mpComboDelegate(NULL),
    combos()
{
#ifdef DEBUG_UI
  qDebug() << "-- in constructor -- \n";
#endif

  setupUi(this);

  //Setting values for Combo Box
  mpComboDelegate = new CQComboDelegate(&mComboEntries, this);
  mpSelectionTable->setItemDelegateForColumn(1, mpComboDelegate);

  // The bar charts are temporary disabled
  //  mWithBarChart = false;
  mWithBarChart = true;
  mUseSliders = slider;
  mBarChartFilled = false;
  //  mBarChartFilled = true;

  // if the 3D bar chart is activated, it needs a button to switch between table and bar chart
  if (mWithBarChart)
    {
      if (mUseSliders)
        {
          mpPlot3d->setSliderActive(true);
        }

      mBarChartFilled = false;

      connect(mpButton, SIGNAL(clicked()), this, SLOT(changeContents()));
    }

  connect(mpContentTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(tableDoubleClicked()));
  connect(mpSelectionTable, SIGNAL(cellChanged(int, int)), this, SLOT(selectionTableChanged(int, int)));
  connect(mpContentTable->horizontalHeader(), SIGNAL(sectionResized(int, int, int)), this, SLOT(setColumnSize(int, int, int)));
}

CQArrayAnnotationsWidget::~CQArrayAnnotationsWidget()
{
#ifdef DEBUG_UI
  qDebug() << "-- in destructor -- \n";
#endif

  if (mpColorScale)
    delete mpColorScale;
}

void CQArrayAnnotationsWidget::setColorCoding(CColorScale * cs)
{
#ifdef DEBUG_UI
  qDebug() << "-- in setColorCoding -- \n";
#endif

  if (cs && cs->isUsed())
    {
      cs = NULL; //don´t accept a scaler that is already used
    }

  if (mpColorScale)
    delete mpColorScale;

  mpColorScale = cs;

  if (cs) cs->setIsUsed(true);
}

void CQArrayAnnotationsWidget::setArrayAnnotation(const CArrayAnnotation * pArray)
{
#ifdef DEBUG_UI
  qDebug() << "-- in setArrayAnnotation -- \n";
#endif

  mpArray = pArray;

  if (!mpArray)
    {
      clearWidget();
      return;
    }

  CCopasiAbstractArray::index_type index; index.resize(mpArray->dimensionality());

  if (mpArray->dimensionality() == 0)
    {
      mpSelectionTable->hide();
      fillTable();

      return;
    }

  if (mpArray->dimensionality() == 1)
    {
      mpSelectionTable->setRowCount(1);
      mpSelectionTable->setColumnCount(2);

      QTableWidgetItem *pItem = new QTableWidgetItem("Rows: ");
      // pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      // pItem->setTextAlignment(Qt::AlignLeft | Qt::AlignVCenter);
      mpSelectionTable->setItem(0, 0, pItem);

      pItem = new QTableWidgetItem(FROM_UTF8(mpArray->getDimensionDescription(0)));
      mpSelectionTable->setItem(0, 1, pItem);

      fillTable(0, index);
    }
  else if (mpArray->dimensionality() == 2)
    {
      mpSelectionTable->setRowCount(2);
      mpSelectionTable->setColumnCount(2);

      QTableWidgetItem *pItem = new QTableWidgetItem("Rows: ");
      mpSelectionTable->setItem(0, 0, pItem);

      pItem = new QTableWidgetItem(FROM_UTF8(mpArray->getDimensionDescription(0)));
      mpSelectionTable->setItem(0, 1, pItem);

      pItem = new QTableWidgetItem("Columns: ");
      mpSelectionTable->setItem(1, 0, pItem);

      pItem = new QTableWidgetItem(FROM_UTF8(mpArray->getDimensionDescription(1)));
      mpSelectionTable->setItem(1, 1, pItem);

      fillTable(0, 1, index);
    }
  else
    {
      initSelectionTable();
      fillTable(0, 1, index);
    }

  mpSelectionTable->show();

  mpSelectionTable->resizeColumnsToContents();
  mpSelectionTable->resizeRowsToContents();

  mpSelectionTable->setMaximumHeight(mpSelectionTable->verticalHeader()->sectionSize(0) *(mpArray->dimensionality() + 1));
}

void CQArrayAnnotationsWidget::initSelectionTable()
{
#ifdef DEBUG_UI
  qDebug() << "-- in initSelectionTable -- \n";
#endif

  size_t i, imax = mpArray->dimensionality();

  mpSelectionTable->setRowCount((int) imax);
  mpSelectionTable->setColumnCount(2);

  for (i = 0; i < imax; ++i)
    {

      QTableWidgetItem *pItem = new QTableWidgetItem(FROM_UTF8(mpArray->getDimensionDescription(i)));
      mpSelectionTable->setItem((int) i, 0, pItem);

      //combo box
      vectorOfStrings2QStringList(mpArray->getAnnotationsString(i), mComboEntries);
      mComboEntries.prepend("In columns");
      mComboEntries.prepend("In rows");

      pItem = new QTableWidgetItem(FROM_UTF8(mpArray->getDimensionDescription(i)));
      mpSelectionTable->setItem((int) i, 0, pItem);


      //set first combobox to "In rows", second to "In columns" and all other to the
      //first object in the annotations list
      switch (i)
        {
          case 0:
            pItem = new QTableWidgetItem("In rows");
            break;

          case 1:
            pItem = new QTableWidgetItem("In columns");
            break;

          default:
            pItem = new QTableWidgetItem(mComboEntries[2]);
            break;
        }

      mpSelectionTable->setItem((int) i, 1, pItem);
    }

  mpSelectionTable->resizeColumnsToContents();

  storeCurrentCombos();
}

void CQArrayAnnotationsWidget::storeCurrentCombos()
{
#ifdef DEBUG_UI
  qDebug() << "-- in storeCurrentCombos -- \n";
#endif

  size_t i, imax = mpArray->dimensionality();
  combos.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      int tmp = currentItem((int) i);

      if (tmp >= 2)
        combos[i] = 2;
      else
        combos[i] = tmp;
    }
}

void CQArrayAnnotationsWidget::clearWidget()
{
#ifdef DEBUG_UI
  qDebug() << "-- in clearWidget -- \n";
#endif

  //mpSelectionTable->setColumnCount(2);
  mpSelectionTable->setRowCount(0);
  mpContentTable->setColumnCount(0);
  mpContentTable->setRowCount(0);

  if (mWithBarChart && mBarChartFilled)
    {
      if (mpPlot3d)
        mpPlot3d->emptyPlot();

      mBarChartFilled = false;
    }
}

void CQArrayAnnotationsWidget::setLegendEnabled(bool b)
{
#ifdef DEBUG_UI
  qDebug() << "-- in setLegendEnabled -- \n";
#endif

  if (b)
    mpSelectionTable->show();
  else
    mpSelectionTable->hide();
}

C_INT32 CQArrayAnnotationsWidget::currentItem(C_INT32 row)
{
#ifdef DEBUG_UI
  qDebug() << "-- in currentItem -- \n";
#endif

  Q3ComboTableItem * item = dynamic_cast<Q3ComboTableItem*>
                            (mpSelectionTable->item(row, 1));

  if (!item) return - 1;

  return item->currentItem();
}

void CQArrayAnnotationsWidget::setCurrentItem(C_INT32 row, C_INT32 index)
{
#ifdef DEBUG_UI
  qDebug() << "-- in setCurrentItem -- \n";
#endif

  storeCurrentCombos();
  Q3ComboTableItem * item = dynamic_cast<Q3ComboTableItem*>
                            (mpSelectionTable->item(row, 1));

  if (!item) return;

  item->setCurrentItem(index);
}

//slot
void CQArrayAnnotationsWidget::selectionTableChanged(int row, int col)
{
#ifdef DEBUG_UI
  qDebug() << "-- in selectionTableChanged -- \n";
#endif

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
      size_t i, imax = mpArray->dimensionality();

      for (i = 0; i < imax; ++i)
        if (combos[i] == 0)
          setCurrentItem((int) i, combos[row]);
    }

  if (newValue == 1) //new value is "column"
    {
      //find out which line was "col" before
      size_t i, imax = mpArray->dimensionality();

      for (i = 0; i < imax; ++i)
        if (combos[i] == 1)
          setCurrentItem((int) i, combos[row]);
    }

  if (newValue >= 2) //new value is neither "col" nor "row"
    {
      //find a line which was neither "col" nor "row"  before
      size_t i, imax = mpArray->dimensionality();

      for (i = 0; i < imax; ++i)
        if (combos[i] >= 2)
          {
            setCurrentItem((int) i, combos[row]);
            break;
          }
    }

finish:
  //call fillTable()
  {
    CCopasiAbstractArray::index_type index; index.resize(mpArray->dimensionality());
    size_t rowindex = 0, colindex = 0;
    size_t i, imax = mpArray->dimensionality();

    for (i = 0; i < imax; ++i)
      {
        int tmp = currentItem((int) i);

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

void CQArrayAnnotationsWidget::fillTable(size_t rowIndex, size_t colIndex,
    CCopasiAbstractArray::index_type & index)
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillTable A -- \n";
#endif

  if (!mpArray) return;

  assert(rowIndex < index.size());
  assert(colIndex < index.size());

  mpContentTable->setColumnCount((int) mpArray->size()[colIndex]);
  mpContentTable->setRowCount((int) mpArray->size()[rowIndex]);

  std::vector<std::string> rowdescr = mpArray->getAnnotationsString(rowIndex);
  std::vector<std::string> coldescr = mpArray->getAnnotationsString(colIndex);

  size_t i, imax = mpArray->size()[rowIndex];
  size_t j, jmax = mpArray->size()[colIndex];

  //annotations
  for (i = 0; i < imax; ++i)
    {
      QTableWidgetItem * pItem = new QTableWidgetItem(FROM_UTF8(rowdescr[i]));
      mpContentTable->setVerticalHeaderItem(i, pItem);
    }

  for (j = 0; j < jmax; ++j)
    {
      // :TODO: This is a hack we need a smarter way possibly using getObjectDisplayName.
      QTableWidgetItem * pItem = new QTableWidgetItem(FROM_UTF8(coldescr[j]).replace("; {", "\n{"));
      mpContentTable->setHorizontalHeaderItem((int) j, pItem);;

#ifdef DEBUG_UI
      qDebug() << "text on col " << j << " = " << FROM_UTF8(coldescr[j]).replace("; {", "\n{");
#endif
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

        QTableWidgetItem * pItem = new QTableWidgetItem(QString::number((*mpArray->array())[index]));
        mpContentTable->setItem((int) i, (int) j, pItem);

        if (mpColorScale != NULL)
          {
            pItem->setBackground(QBrush(mpColorScale->getColor((*mpArray->array())[index])));
          }
      }

  mRowIndex = rowIndex;
  mColIndex = colIndex;
  mIndex = index;

  mOneDimensional = false;

  mpContentTable->resizeRowsToContents();
  mpContentTable->resizeColumnsToContents();

//  if (mpStack->id(mpStack->visibleWidget()) == 1)
  if (mpStack->currentIndex() == 1)
    fillBarChart();
}

void CQArrayAnnotationsWidget::fillTable(size_t rowIndex,
    CCopasiAbstractArray::index_type & index)
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillTable B -- \n";
#endif

  if (!mpArray) return;

  assert(rowIndex < index.size());

  mpContentTable->setColumnCount(1);
  mpContentTable->setRowCount((int) mpArray->size()[rowIndex]);

  mpContentTable->setHorizontalHeaderItem(0, new QTableWidgetItem(""));

  size_t i, imax = mpArray->size()[rowIndex];

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
      QTableWidgetItem * pItem = new QTableWidgetItem(FROM_UTF8(rowdescr[i]));
      mpContentTable->setVerticalHeaderItem((int) i, pItem);

      pItem = new QTableWidgetItem(QString::number((*mpArray->array())[index]));
      mpContentTable->setItem((int) i, 0, pItem);

      if (mpColorScale != NULL)
        {
          pItem->setBackground(QBrush(mpColorScale->getColor((*mpArray->array())[index])));
        }

    }

  mRowIndex = rowIndex;
  mColIndex = 1;
  mIndex = index;

  mOneDimensional = true;

  mpContentTable->resizeRowsToContents();
  mpContentTable->resizeColumnsToContents();

  if (mpStack->currentIndex() == 1)
    fillBarChart();
}

void CQArrayAnnotationsWidget::fillTable()
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillTable C -- \n";
#endif

  if (!mpArray) return;

  mpContentTable->setColumnCount(0);
  mpContentTable->setRowCount(0);
  mpContentTable->setColumnCount(1);
  mpContentTable->setRowCount(1);

  mpContentTable->setHorizontalHeaderItem(0, new QTableWidgetItem(""));
  mpContentTable->setVerticalHeaderItem(0, new QTableWidgetItem(""));

  CCopasiAbstractArray::index_type index; index.resize(0);
  //mpContentTable->verticalHeader()->setLabel(i, FROM_UTF8(rowdescr[i]));
  mpContentTable->setItem(0, 0, new QTableWidgetItem(QString::number((*mpArray->array())[index])));
}

void CQArrayAnnotationsWidget::changeContents()
{
#ifdef DEBUG_UI
  qDebug() << "-- in changeContents -- \n";
#endif

//  if (mpStack->id(mpStack->visibleWidget()) == 0)
  if (mpStack->currentIndex() == 0)
    switchToBarChart();
  else
    switchToTable();
}

void CQArrayAnnotationsWidget::enableBarChart(bool enable)
{
#ifdef DEBUG_UI
  qDebug() << "-- in enableBarChart -- \n";
#endif

  if (mWithBarChart)
    {
      if (enable)
        {
          mpButton->setEnabled(true);
        }
      else
        {
//          if (mpStack->id(mpStack->visibleWidget()) == 1)
          if (mpStack->currentIndex() == 1)
            switchToTable();

          //mpStack->raiseWidget(0);
          mpButton->setEnabled(false);
        }
    }
}

/*!
    Function to switch the appearance to table
 */
void CQArrayAnnotationsWidget::switchToTable()
{
#ifdef DEBUG_UI
  qDebug() << "-- in switchToTable -- \n";

  qDebug() << "A mpStack->currentIndex() = " << mpStack->currentIndex();
#endif

//  mpStack->raiseWidget(0);
  mpStack->setCurrentWidget(mpContentTable);

#ifdef DEBUG_UI
  qDebug() << "B mpStack->currentIndex() = " << mpStack->currentIndex();
#endif

  if (mWithBarChart)
    {
      mpButton->setText("Bars");
      setFocusOnTable();
    }
}

/*!
    Function to switch the appearance to bar chart
 */
void CQArrayAnnotationsWidget::switchToBarChart()
{
#ifdef DEBUG_UI
  qDebug() << "-- in switchToBarChart -- \n";
#endif

  if (mWithBarChart)
    {
      if (!mpPlot3d)
        createBarChart();

//      setFocusOnBars();

      if (!mBarChartFilled)
        fillBarChart();

//      setFocusOnBars();
      setFocusOnBars();

//      mpStack->raiseWidget(1);
      mpStack->setCurrentWidget(mpPlot3d);
      mpPlot3d->show();

      mpButton->setText("Table");
    }
}

void CQArrayAnnotationsWidget::disableBarChart()
{
#ifdef DEBUG_UI
  qDebug() << "-- in disableBarChart -- \n";
#endif

  switchToTable();
  mpButton->hide();
}

void CQArrayAnnotationsWidget::disableSlider()
{
#ifdef DEBUG_UI
  qDebug() << "-- in disableSlider -- \n";
#endif

  if (mpPlot3d && mpPlot3d->isSliderActive())
    {
      mpPlot3d->setSliderActive(false);
    }
}

/*!
    Function to set the appearance focus on table
 */
void CQArrayAnnotationsWidget::setFocusOnTable()
{
#ifdef DEBUG_UI
  qDebug() << "-- in setFocusOnTable -- \n";

  qDebug() << "boolean mWithBarChart = " << mWithBarChart;
  qDebug() << "boolean mpPlot3d = " << mpPlot3d;
  qDebug() << "boolean mpPlot3d->sliderActive() = " << mpPlot3d->sliderActive();
#endif

  if (mWithBarChart && mpPlot3d && mpPlot3d->isSliderActive())
    {
      int col = mpPlot3d->mpSliderColumn->value() / mpPlot3d->scaleFactor();
      int row = mpPlot3d->mpSliderRow->value() / mpPlot3d->scaleFactor();

#ifdef DEBUG_UI
      qDebug() << "col = " << col << " - row = " << row;
#endif

      mpContentTable->clearSelection();

      if (col < mpContentTable->columnCount())
        {
          if (row < mpContentTable->rowCount())
            {
              mpContentTable->setCurrentCell(row, col);
              mpContentTable->scrollToItem(mpContentTable->item(mpContentTable->currentRow(), mpContentTable->currentColumn()));
              mpContentTable->setFocus();
            }
          else
            {
              mpContentTable->selectColumn(col);
              mpContentTable->setFocus();
            }
        }
      else
        {
          if (row < mpContentTable->rowCount())
            {
              mpContentTable->selectRow(row);
              mpContentTable->setFocus();
            }
          else
            {
              mpContentTable->setCurrentCell(-1, -1);
            }
        }

#ifdef DEBUG_UI
      qDebug() << "label at col = " << mpContentTable->horizontalHeader()->label(col);
#endif
      /*
          if (mpContentTable->horizontalHeader()->label(col).isEmpty())
            mpContentTable->horizontalHeader()->setLabel(col, FROM_UTF8((mpArray->getAnnotationsString(1))[col]).replace("; {", "\n{"));
      */
    }

//  mpContentTable->horizontalHeader()->repaint();
//  mpContentTable->update();
#ifdef DEBUG_UI
  qDebug() << "at the end of setFocusOnTable";
#endif
}

/*!
    Function to set the appearance focus on bars
 */
void CQArrayAnnotationsWidget::setFocusOnBars()
{
  if (mWithBarChart && mpPlot3d && mpPlot3d->isSliderActive())
    {
      QList<QTableWidgetSelectionRange> Ranges = mpContentTable->selectedRanges();

      if (Ranges.size() == 1)
        {
          int SliderColumn = Ranges[0].leftColumn() * mpPlot3d->scaleFactor();
          int SliderRow = Ranges[0].topRow() * mpPlot3d->scaleFactor();

          if (Ranges[0].leftColumn() == Ranges[0].rightColumn() &&
              Ranges[0].topRow() == Ranges[0].bottomRow())
            {
              mpPlot3d->mpSliderColumn->setValue(SliderColumn);
              mpPlot3d->mpSliderRow->setValue(SliderRow);
              mpPlot3d->sliderMoved(Ranges[0].leftColumn(), Ranges[0].topRow());
              mpPlot3d->setSlider();

              return;
            }
          else if (Ranges[0].leftColumn() == Ranges[0].rightColumn())
            {
              mpPlot3d->mpSliderColumn->setValue(SliderColumn);
              mpPlot3d->mpSliderRow->setValue(-1);
              mpPlot3d->sliderMoved(Ranges[0].leftColumn(), mpContentTable->rowCount());
              mpPlot3d->setSlider();

              return;
            }
          else if (Ranges[0].topRow() == Ranges[0].bottomRow())
            {
              mpPlot3d->mpSliderColumn->setValue(-1);
              mpPlot3d->mpSliderRow->setValue(SliderRow);
              mpPlot3d->sliderMoved(mpContentTable->columnCount(), Ranges[0].topRow());
              mpPlot3d->setSlider();

              return;
            }
        }

      mpPlot3d->mpSliderColumn->setValue(-1);
      mpPlot3d->mpSliderRow->setValue(-1);
      mpPlot3d->sliderMoved(mpContentTable->columnCount(), mpContentTable->rowCount());
      mpPlot3d->setSlider();
    }

  return;
}

void CQArrayAnnotationsWidget::tableDoubleClicked()
{
#ifdef DEBUG_UI
  qDebug() << "-- in tableDoubleClicked -- \n";
#endif

  if (mpPlot3d && mpPlot3d->isSliderActive())
    switchToBarChart();
}

void CQArrayAnnotationsWidget::setColumnSize(int col, int /*size0*/, int /*size*/)
{
  disconnect(mpContentTable->horizontalHeader(), SIGNAL(sectionResized(int, int, int)), this, SLOT(setColumnSize(int, int, int)));

#ifdef DEBUG_UI
  qDebug() << "-- in setColumnSize -- \n";
#endif

  C_INT32 i;
  C_FLOAT64 sum = 0;

  for (i = 0; i <= col; ++i)
    sum += mpContentTable->horizontalHeader()->sectionSize(i);

  C_FLOAT64 newSize = sum / (col + 1);

  if (newSize < 5) newSize = 5;

  for (i = 0; i < mpContentTable->columnCount(); i++)
    mpContentTable->setColumnWidth(i, ((int)(newSize*(i + 1))) - ((int)(newSize*i)));

  mpContentTable->horizontalHeader()->repaint();

  connect(mpContentTable->horizontalHeader(), SIGNAL(sectionResized(int, int, int)), this, SLOT(setColumnSize(int, int, int)));
}

void CQArrayAnnotationsWidget::fillBarChart()
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillBarChart -- \n";
#endif

  if (!mWithBarChart)
    return;

  if (!mpPlot3d)
    createBarChart();

//  mBarChartFilled = true;

  if (!mpArray) return;

  mBarChartFilled = true;

#ifdef DEBUG_UI
  qDebug() << "mRowIndex = " << mRowIndex << " - mIndex.size() = " << mIndex.size();
#endif

  assert(mRowIndex < mIndex.size());

  if (!mOneDimensional)
    assert(mColIndex < mIndex.size());

  mpContentTable->setRowCount((int) mpArray->size()[mRowIndex]);

  if (mOneDimensional)
    mpContentTable->setColumnCount(1);
  else
    mpContentTable->setColumnCount((int) mpArray->size()[mColIndex]);

//  mpContentTable->horizontalHeader()->setLabel(0, "");  --> ???

  std::vector<std::string> rowdescr = mpArray->getAnnotationsString(mRowIndex);

  if (!mOneDimensional)
    std::vector<std::string> coldescr = mpArray->getAnnotationsString(mColIndex);

  size_t i, imax = mpArray->size()[mRowIndex];
  size_t j, jmax;

  if (mOneDimensional)
    jmax = 1;
  else
    jmax = mpArray->size()[mColIndex];

  if (jmax > 0 && imax > 0)
    {
      //create a new array data, witch holds the hole numeric data
      size_t columns = jmax;
      size_t rows = imax;
      data = new double * [columns];

      for (i = 0; i < columns; ++i)
        data[i] = new double[rows];

      //minValue and maxValue help to figure out the min and max value
      mIndex[mRowIndex] = 0;

      if (!mOneDimensional)
        mIndex[mColIndex] = 0;

      double maxValue = (double)(*mpArray->array())[mIndex];
      double minValue = (double)(*mpArray->array())[mIndex];

      //fill array data with values and figure out min/max value
      for (i = 0; i < imax; ++i)
        for (j = 0; j < jmax; ++j)
          {
            mIndex[mRowIndex] = i;

            if (!mOneDimensional)
              mIndex[mColIndex] = j;

            if (isnan((double)(*mpArray->array())[mIndex]) ||
                !finite((double)(*mpArray->array())[mIndex]))
              {
                data[j][i] = 0;

                if (0 > maxValue) maxValue = 0;

                if (0 < minValue) minValue = 0;
              }
            else
              {
                data[j][i] = (double)(*mpArray->array())[mIndex];

                if ((double)(*mpArray->array())[mIndex] > maxValue)
                  maxValue = (double)(*mpArray->array())[mIndex];

                if ((double)(*mpArray->array())[mIndex] < minValue)
                  minValue = (double)(*mpArray->array())[mIndex];
              }
          }

      //figure out the min/max print section
      double minZ, maxZ;

      if ((minValue < 0) && (maxValue < 0))
        {//(all values < 0)
          minZ = minValue;
          maxZ = 0;
        }
      else
        {
          if ((minValue > 0) && (maxValue > 0))
            {//(all values > 0)
              minZ = 0;
              maxZ = maxValue;
            }
          else
            {//(values <> 0)
              minZ = minValue;
              maxZ = maxValue;
            }
        }

      //fill vector mColor with 100 colors, evenly distributed over relevant print section
      double holeSection = maxZ - minZ;
      double step = holeSection / 99;

      for (i = 0; i < 100; i++)
        {
          mColors.push_back((int) i);
          mColors[i] = mpColorScale->getColor(minZ + i * step);
        }

      //deliver plot3D contents, colors and annotations
      if ((maxValue == 0) && (minValue == 0))
        {
          mpPlot3d->emptyPlot();
          mBarChartFilled = false;
          return;
        }
      else
        {

          mpPlot3d->setPlotTitle(QString(""));
          mpPlot3d->setColors(mColors, minZ, maxZ);
          mColors.erase(mColors.begin(), mColors.end());
          mpPlot3d->showColorLegend(true);

          if (mOneDimensional)
            mpPlot3d->setDescriptions(NULL, &mpArray->getAnnotationsString(mRowIndex));
          else
            mpPlot3d->setDescriptions(&mpArray->getAnnotationsString(mColIndex), &mpArray->getAnnotationsString(mRowIndex));

          mpPlot3d->setData(data, (int) columns, (int) rows, holeSection);
          enableBarChart(true);
        }
    }
  else
    {
      mpPlot3d->emptyPlot();
      mBarChartFilled = false;
      return;
    }
}

/*!
    Function to create the 3D bar chart
 */
void CQArrayAnnotationsWidget::createBarChart()
{
#ifdef DEBUG_UI
  qDebug() << "-- in createBarChart -- \n";
#endif

  mpPlot3d = new CQBarChart();
  mpPlot3d->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

  if (mUseSliders) mpPlot3d->setSliderActive(true);

//  mpStack->addWidget(mpPlot3d, 1);
  mpStack->addWidget(mpPlot3d);
  mpButton->setText("Bars");
  mBarChartFilled = false;
}
