// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifdef SunOS
#include <ieeefp.h>
#else
#include <cmath>
#endif

#include "copasi.h"

#include "CQArrayAnnotationsWidget.h"
#include "qtUtilities.h"
#include "CQComboDelegate.h"

#include <iostream>

#include "barChart/qwt3dPlot.h"

#include "resourcesUI/CQIconResource.h"  //icons for bars and table toggle button

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

CQArrayAnnotationsWidget::CQArrayAnnotationsWidget(QWidget* parent, bool slider) :
  QWidget(parent),
  mWithBarChart(false),
  mUseSliders(slider),
  data(NULL),
  mColors(),
  mpArray(NULL),
  mpColorScale(NULL),
  mAutomaticColorScaling(false),
  mRowIndex(C_INVALID_INDEX),
  mColIndex(C_INVALID_INDEX),
  mSelectedCell(),
  mBarChartFilled(false),
  mOneDimensional(false),
  mComboEntries(),
  mpComboDelegate(NULL)
{
#ifdef DEBUG_UI
  qDebug() << "-- in constructor -- \n";
#endif

  setupUi(this);

  //Setting values for Combo Box
  mpComboDelegate = new CQComboDelegate(NULL, this);
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

  connect(mpContentTable, SIGNAL(cellDoubleClicked(int, int)), this, SLOT(slotContentDoubleClicked()));
  connect(mpContentTable, SIGNAL(cellClicked(int, int)), this, SLOT(slotContentCellClicked(int, int)));
  connect(mpContentTable->horizontalHeader(), SIGNAL(sectionResized(int, int, int)), this, SLOT(setColumnSize(int, int, int)));

  connect(mpComboDelegate, SIGNAL(currentIndexChanged(int, int)), this, SLOT(slotCurrentSelectionIndexChanged(int, int)));
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
      mSelectedCell.clear();
      clearWidget();
      return;
    }

  QStringList Items;
  size_t i = 0, imax = mpArray->dimensionality();

  for (; i != imax; i++)
    {
      Items.append(FROM_UTF8(mpArray->getDimensionDescription(i)));
    }

  mpComboRows->blockSignals(true);
  mpComboRows->clear();
  mpComboRows->addItems(Items);
  mpComboRows->blockSignals(false);

  mpComboColumns->blockSignals(true);
  mpComboColumns->clear();
  mpComboColumns->addItems(Items);
  mpComboColumns->blockSignals(false);

  // No practical use in allowing
  // axes swap when 2 or 1 . . .
  if (Items.size() < 3)
    {
      mpComboRows->setEnabled(false);
      mpComboColumns->setEnabled(false);
    }

  mSelectionIndex.resize(imax);
  CCopasiAbstractArray::index_type::iterator it = mSelectionIndex.begin();
  CCopasiAbstractArray::index_type::iterator end = mSelectionIndex.end();

  mSelectedCell.resize(imax);
  CCopasiAbstractArray::index_type::iterator itCell = mSelectedCell.begin();

  for (; it != end; ++it)
    {
      *it = 0;
      *itCell = 0;
    }

  switch (imax)
    {
      case 0:
        mpLblRows->hide();
        mpComboRows->hide();
        mpLblColumns->hide();
        mpComboColumns->hide();
        mpLblOther->hide();
        mpSelectionTable->hide();

        mRowIndex = C_INVALID_INDEX;
        mColIndex = C_INVALID_INDEX;

        fillTable0();
        break;

      case 1:
        mpLblRows->show();
        mpComboRows->show();
        mpLblColumns->hide();
        mpComboColumns->hide();
        mpLblOther->hide();
        mpSelectionTable->hide();

        slotRowSelectionChanged(0);
        break;

      case 2:
        mpLblRows->show();
        mpComboRows->show();
        mpLblColumns->show();
        mpComboColumns->show();
        mpLblOther->hide();
        mpSelectionTable->hide();

        slotRowSelectionChanged(0);
        break;

      default:
        mpLblRows->show();
        mpComboRows->show();
        mpLblColumns->show();
        mpComboColumns->show();
        mpLblOther->hide();
        mpSelectionTable->hide();

        // TODO CRITICAL We need to fill the selection table.
        slotRowSelectionChanged(0);
        break;
    }
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
      QStringList ComboEntries;
      vectorOfStrings2QStringList(mpArray->getAnnotationsString(i), ComboEntries);

      pItem = new QTableWidgetItem(ComboEntries[mSelectionIndex[i]]);
      pItem->setData(Qt::EditRole, ComboEntries);
      mpSelectionTable->setItem((int) i, 1, pItem);
    }

  mpSelectionTable->resizeColumnsToContents();

  mpSelectionTable->show();

  mpSelectionTable->resizeColumnsToContents();
  mpSelectionTable->resizeRowsToContents();

  mpSelectionTable->setMaximumHeight(mpSelectionTable->verticalHeader()->sectionSize(0) * (mpArray->dimensionality() + 1));
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

void CQArrayAnnotationsWidget::slotRowSelectionChanged(int row)
{
  // Assure that row and column dimension are not the same
  if (mpComboColumns->currentIndex() == row)
    {
      mpComboColumns->blockSignals(true);
      mpComboColumns->setCurrentIndex(row == 0 ? 1 : 0);
      mpComboColumns->blockSignals(false);

      mpSelectionTable->showRow(mColIndex);
      mColIndex = mpComboColumns->currentIndex();
      mpSelectionTable->hideRow(mColIndex);
    }

  mpSelectionTable->showRow(mRowIndex);
  mRowIndex = row;
  mpSelectionTable->hideRow(mRowIndex);

  fillTable();
}

void CQArrayAnnotationsWidget::slotColumnSelectionChanged(int col)
{
  // Assure that row and column dimension are not the same
  if (mpComboRows->currentIndex() == col)
    {
      mpComboRows->blockSignals(true);
      mpComboRows->setCurrentIndex(col == 0 ? 1 : 0);
      mpComboRows->blockSignals(false);

      mpSelectionTable->showRow(mRowIndex);
      mRowIndex = mpComboRows->currentIndex();
      mpSelectionTable->hideRow(mRowIndex);
    }

  mpSelectionTable->showRow(mColIndex);
  mColIndex = col;
  mpSelectionTable->hideRow(mColIndex);

  fillTable();
}

void CQArrayAnnotationsWidget::slotCurrentSelectionIndexChanged(int row, int index)
{
  mSelectionIndex[row] = index;
  fillTable();
}

void CQArrayAnnotationsWidget::fillTable()
{
  if (!mpArray) return;

  switch (mpArray->dimensionality())
    {
      case 0:
        fillTable0();
        break;

      case 1:
        fillTable1(mRowIndex, mSelectionIndex);
        break;

      default:
        fillTableN(mRowIndex, mColIndex, mSelectionIndex);
        break;
    }

  return;
}

void CQArrayAnnotationsWidget::fillTableN(size_t rowIndex, size_t colIndex,
    const CCopasiAbstractArray::index_type & index)
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillTable0 A -- \n";
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

  if (jmax == 0) return;

  int TableWidth = mpContentTable->size().width();
  mpContentTable->verticalHeader()->setMaximumWidth(TableWidth / std::min< size_t >(jmax, 5));
  mpContentTable->verticalHeader()->setTextElideMode(Qt::ElideRight);
  mpContentTable->horizontalHeader()->setTextElideMode(Qt::ElideRight);

  QString DisplayName;

  //annotations
  for (i = 0; i < imax; ++i)
    {
      DisplayName = FROM_UTF8(rowdescr[i]);
      QTableWidgetItem * pItem = new QTableWidgetItem(DisplayName);
      pItem->setToolTip(DisplayName);
      mpContentTable->setVerticalHeaderItem(i, pItem);
    }

  for (j = 0; j < jmax; ++j)
    {
      // :TODO: This is a hack we need a smarter way possibly using getObjectDisplayName.
      DisplayName = FROM_UTF8(coldescr[j]).replace("; {", "\n{");
      QTableWidgetItem * pItem = new QTableWidgetItem(DisplayName);
      pItem->setToolTip(DisplayName);
      mpContentTable->setHorizontalHeaderItem((int) j, pItem);;

#ifdef DEBUG_UI
      qDebug() << "text on col " << j << " = " << FROM_UTF8(coldescr[j]).replace("; {", "\n{");
#endif
    }

  CCopasiAbstractArray::index_type Index = index;

  //automatic color scaling
  if (mAutomaticColorScaling)
    {
      mpColorScale->startAutomaticParameterCalculation();

      for (i = 0; i < imax; ++i)
        for (j = 0; j < jmax; ++j)
          {
            Index[rowIndex] = i;
            Index[colIndex] = j;
            mpColorScale->passValue((*mpArray->array())[Index]);
          }

      mpColorScale->finishAutomaticParameterCalculation();
    }

  //table contents
  for (i = 0; i < imax; ++i)
    for (j = 0; j < jmax; ++j)
      {
        Index[rowIndex] = i;
        Index[colIndex] = j;

        QTableWidgetItem * pItem = new QTableWidgetItem(QVariant::Double);
        pItem->setData(Qt::DisplayRole, (*mpArray->array())[Index]);
        mpContentTable->setItem((int) i, (int) j, pItem);

        if (mpColorScale != NULL)
          {
            pItem->setBackground(QBrush(mpColorScale->getColor((*mpArray->array())[Index])));
          }
      }

  mOneDimensional = false;

  mpContentTable->resizeRowsToContents();
  mpContentTable->resizeColumnsToContents();

//  if (mpStack->id(mpStack->visibleWidget()) == 1)
  if (mpStack->currentIndex() == 1)
    fillBarChart();
}

void CQArrayAnnotationsWidget::fillTable1(size_t rowIndex,
    const CCopasiAbstractArray::index_type & index)
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillTable0 B -- \n";
#endif

  if (!mpArray) return;

  assert(rowIndex < index.size());

  mpContentTable->setColumnCount(1);
  mpContentTable->setRowCount((int) mpArray->size()[rowIndex]);

  mpContentTable->setHorizontalHeaderItem(0, new QTableWidgetItem(""));

  size_t i, imax = mpArray->size()[rowIndex];

  CCopasiAbstractArray::index_type Index = index;

  //automatic color scaling
  if (mAutomaticColorScaling)
    {
      mpColorScale->startAutomaticParameterCalculation();

      for (i = 0; i < imax; ++i)
        {
          Index[rowIndex] = i;
          mpColorScale->passValue((*mpArray->array())[Index]);
        }

      mpColorScale->finishAutomaticParameterCalculation();
    }

  //table contents and annotations
  const std::vector<std::string> & rowdescr = mpArray->getAnnotationsString(rowIndex);

  for (i = 0; i < imax; ++i)
    {
      Index[rowIndex] = i;
      QTableWidgetItem * pItem = new QTableWidgetItem(FROM_UTF8(rowdescr[i]));
      mpContentTable->setVerticalHeaderItem((int) i, pItem);

      pItem = new QTableWidgetItem(QString::number((*mpArray->array())[Index]));
      mpContentTable->setItem((int) i, 0, pItem);

      if (mpColorScale != NULL)
        {
          pItem->setBackground(QBrush(mpColorScale->getColor((*mpArray->array())[Index])));
        }
    }

  mOneDimensional = true;

  mpContentTable->resizeRowsToContents();
  mpContentTable->resizeColumnsToContents();

  if (mpStack->currentIndex() == 1)
    fillBarChart();
}

void CQArrayAnnotationsWidget::fillTable0()
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillTable0 C -- \n";
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
      mpButton->setIcon(CQIconResource::icon(CQIconResource::bars));
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

      mpButton->setIcon(CQIconResource::icon(CQIconResource::table));
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

void CQArrayAnnotationsWidget::slotContentCellClicked(int row, int col)
{
  switch (mSelectedCell.size())
    {
      case 0:
        break;

      case 1:
        mSelectedCell[mRowIndex] = row;
        break;

      default:
        mSelectedCell[mRowIndex] = row;
        mSelectedCell[mColIndex] = col;
        break;
    }

  return;
}

void CQArrayAnnotationsWidget::slotContentDoubleClicked()
{
#ifdef DEBUG_UI
  qDebug() << "-- in slotContentDoubleClicked -- \n";
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
    mpContentTable->setColumnWidth(i, ((int)(newSize * (i + 1))) - ((int)(newSize * i)));

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
  qDebug() << "mRowIndex = " << mRowIndex << " - mIndex.size() = " << mSelectedCell.size();
#endif

  std::vector<size_t> types = mpArray->size();
  size_t imax =  types.size() > mRowIndex ? types[mRowIndex] : 0;
  size_t jmax = mOneDimensional ? 1 : types.size() > mColIndex ? types[mColIndex] : 0;

  if (imax == 0 || jmax == 0)
    {
      mpPlot3d->emptyPlot();
      mBarChartFilled = false;
      return;
    }

  mpContentTable->setRowCount((int) imax);

  if (mOneDimensional)
    mpContentTable->setColumnCount(1);
  else
    mpContentTable->setColumnCount((int) jmax);

//  mpContentTable->horizontalHeader()->setLabel(0, "");  --> ???

  std::vector<std::string> rowdescr = mpArray->getAnnotationsString(mRowIndex);

  if (!mOneDimensional)
    std::vector<std::string> coldescr = mpArray->getAnnotationsString(mColIndex);

  size_t i;
  size_t j;

  if (jmax > 0 && imax > 0)
    {
      //create a new array data, witch holds the hole numeric data
      size_t columns = jmax;
      size_t rows = imax;
      data = new double * [columns];

      for (i = 0; i < columns; ++i)
        data[i] = new double[rows];

      //minValue and maxValue help to figure out the min and max value
      mSelectedCell[mRowIndex] = 0;

      if (!mOneDimensional)
        mSelectedCell[mColIndex] = 0;

      double maxValue = (double)(*mpArray->array())[mSelectedCell];
      double minValue = (double)(*mpArray->array())[mSelectedCell];

      //fill array data with values and figure out min/max value
      for (i = 0; i < imax; ++i)
        for (j = 0; j < jmax; ++j)
          {
            mSelectedCell[mRowIndex] = i;

            if (!mOneDimensional)
              mSelectedCell[mColIndex] = j;

            if (isnan((double)(*mpArray->array())[mSelectedCell]) ||
                !finite((double)(*mpArray->array())[mSelectedCell]))
              {
                data[j][i] = 0;

                if (0 > maxValue) maxValue = 0;

                if (0 < minValue) minValue = 0;
              }
            else
              {
                data[j][i] = (double)(*mpArray->array())[mSelectedCell];

                if ((double)(*mpArray->array())[mSelectedCell] > maxValue)
                  maxValue = (double)(*mpArray->array())[mSelectedCell];

                if ((double)(*mpArray->array())[mSelectedCell] < minValue)
                  minValue = (double)(*mpArray->array())[mSelectedCell];
              }
          }

      //figure out the min/max print section
      double minZ, maxZ;

      if ((minValue < 0) && (maxValue < 0))
        {
          //(all values < 0)
          minZ = minValue;
          maxZ = 0;
        }
      else
        {
          if ((minValue > 0) && (maxValue > 0))
            {
              //(all values > 0)
              minZ = 0;
              maxZ = maxValue;
            }
          else
            {
              //(values <> 0)
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
  mpButton->setIcon(CQIconResource::icon(CQIconResource::bars));
  mBarChartFilled = false;
}
