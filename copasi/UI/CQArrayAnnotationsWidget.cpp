// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"

#include "CQArrayAnnotationsWidget.h"
#include "qtUtilities.h"
#include "CQComboDelegate.h"
#include "CQArrayAnnotationsWidgetDM.h"
#include "CQSortFilterProxyModel.h"
#include <copasi/core/CRootContainer.h>
#include <copasi/commandline/CConfigurationFile.h>

#include <iostream>

#include "copasi/resourcesUI/CQIconResource.h"  //icons for bars and table toggle button

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

#ifdef WITH_QT5_VISUALIZATION

#include <QMenu>

#include "copasi/barChart/CQ3DBarsModifier.h"

#  ifdef WITH_DATAVISUALIZATION_NAMESPACES
using namespace QtDataVisualization;
#endif

#else

#include "copasi/barChart/qwt3dPlot.h"

#endif // WITH_QT5_VISUALIZATION

CQArrayAnnotationsWidget::CQArrayAnnotationsWidget(QWidget* parent, bool slider)
  : QWidget(parent)
  , mWithBarChart(false)
  , mUseSliders(slider)
  , data(NULL)
  , mColors()
  , mpArray(NULL)
  , mpColorScale(NULL)
  , mAutomaticColorScaling(false)
  , mRowIndex(C_INVALID_INDEX)
  , mColIndex(C_INVALID_INDEX)
  , mSelectedCell()
  , mBarChartFilled(false)
  , mOneDimensional(false)
  , mComboEntries()
  , mpComboDelegate(NULL)
  , mpDataModel(NULL)
  , mpProxyModel(NULL)
#ifdef WITH_QT5_VISUALIZATION
  , m_graph(NULL)
  , m_modifier(NULL)
  , m_container(NULL)
  , m_contextMenu(NULL)
#else
  , mpPlot3d(NULL)
#endif
{
#ifdef DEBUG_UI
  qDebug() << "-- in constructor -- \n";
#endif

  setupUi(this);

  mpButtonReset->hide();

  //Setting values for Combo Box
  mpComboDelegate = new CQComboDelegate(this);
  mpSelectionTable->setItemDelegateForColumn(1, mpComboDelegate);

  // The bar charts are temporary disabled
  //  mWithBarChart = false;
  mWithBarChart = true;
  mUseSliders = slider;
  mBarChartFilled = false;
  //  mBarChartFilled = true;

  connect(mpButton, SIGNAL(clicked()), this, SLOT(changeContents()));

  mpDataModel = new CQArrayAnnotationsWidgetDM(this);
  mpProxyModel = new CQSortFilterProxyModel();
  mpProxyModel->setSourceModel(mpDataModel);
  mpContentTableView->setModel(mpProxyModel);
  mpContentTableView->verticalHeader()->setTextElideMode(Qt::ElideRight);
  mpContentTableView->horizontalHeader()->setTextElideMode(Qt::ElideRight);

  connect(mpContentTableView, SIGNAL(doubleClicked(const QModelIndex)), this, SLOT(slotContentDoubleClicked(const QModelIndex)));
  connect(mpContentTableView, SIGNAL(clicked(const QModelIndex)), this, SLOT(slotContentCellClicked(const QModelIndex)));
  connect(mpContentTableView->horizontalHeader(), SIGNAL(sectionResized(int, int, int)), this, SLOT(setColumnSize(int, int, int)));
  connect(mpButtonReset, SIGNAL(clicked(bool)), this, SLOT(slotResetSortOrder()));
  connect(mpComboDelegate, SIGNAL(currentIndexChanged(int, int)), this, SLOT(slotCurrentSelectionIndexChanged(int, int)));
}

CQArrayAnnotationsWidget::~CQArrayAnnotationsWidget()
{
#ifdef DEBUG_UI
  qDebug() << "-- in destructor -- \n";
#endif

  pdelete(mpColorScale);
  pdelete(mpProxyModel);
}

void CQArrayAnnotationsWidget::setColorCoding(CColorScale * cs)
{
#ifdef DEBUG_UI
  qDebug() << "-- in setColorCoding -- \n";
#endif

  if (cs && cs->isUsed())
    {
      cs = NULL; //don't accept a scaler that is already used
    }

  if (mpColorScale)
    delete mpColorScale;

  mpColorScale = cs;

  if (cs) cs->setIsUsed(true);
}

CColorScale *
CQArrayAnnotationsWidget::getColorCoding() const
{
  return mpColorScale;
}

void
CQArrayAnnotationsWidget::setColorScalingAutomatic(bool s)
{
  mAutomaticColorScaling = s;
}

void CQArrayAnnotationsWidget::setArrayAnnotation(const CDataArray * pArray)
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
  CArrayInterface::index_type::iterator it = mSelectionIndex.begin();
  CArrayInterface::index_type::iterator end = mSelectionIndex.end();

  mSelectedCell.resize(imax);
  CArrayInterface::index_type::iterator itCell = mSelectedCell.begin();

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
        mpLblOther->show();
        mpSelectionTable->show();

        // TODO CRITICAL We need to fill the selection table.
        initSelectionTable();
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
      pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled);
      mpSelectionTable->setItem((int) i, 0, pItem);

      //combo box
      QStringList ComboEntries;
      vectorOfStrings2QStringList(mpArray->getAnnotationsString(i), ComboEntries);

      pItem = new QTableWidgetItem(ComboEntries[mSelectionIndex[i]]);
      pItem->setData(Qt::UserRole, ComboEntries);
      pItem->setFlags(Qt::ItemIsSelectable | Qt::ItemIsEnabled | Qt::ItemIsEditable);
      mpSelectionTable->setItem((int)i, 1, pItem);
    }

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpSelectionTable->resizeColumnsToContents();
    }

  mpSelectionTable->show();

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpSelectionTable->resizeColumnsToContents();
      mpSelectionTable->resizeRowsToContents();

      mpSelectionTable->setMaximumHeight(mpSelectionTable->verticalHeader()->sectionSize(0) * (mpArray->dimensionality() + 1));
    }
}

void CQArrayAnnotationsWidget::clearWidget()
{
#ifdef DEBUG_UI
  qDebug() << "-- in clearWidget -- \n";
#endif

  mpSelectionTable->setRowCount(0);
  mpDataModel->setContext(NULL, NULL, std::vector< size_t >(), C_INVALID_INDEX, C_INVALID_INDEX);

  if (mWithBarChart && mBarChartFilled)
    {
#ifdef WITH_QT5_VISUALIZATION

      if (m_container)
        m_modifier->clearData();

#else

      if (mpPlot3d)
        mpPlot3d->emptyPlot();

      mBarChartFilled = false;
#endif
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

void CQArrayAnnotationsWidget::setSortingEnabled(bool b)
{
  if (b)
    mpButtonReset->show();
  else
    mpButtonReset->hide();

  mpContentTableView->setSortingEnabled(b);
  mpProxyModel->sort(-1);
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
    const CArrayInterface::index_type & index)
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillTable0 A -- \n";
#endif

  if (!mpArray) return;

  assert(rowIndex < index.size());
  assert(colIndex < index.size());

  size_t i, imax = mpArray->size()[rowIndex];
  size_t j, jmax = mpArray->size()[colIndex];

  if (jmax == 0) return;

  CArrayInterface::index_type Index = index;

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

  int TableWidth = mpContentTableView->size().width();
  mpContentTableView->verticalHeader()->setMaximumWidth(TableWidth / std::min< size_t >(jmax, 5));

  mpDataModel->setContext(mpColorScale, mpArray, index, rowIndex, colIndex);

  mOneDimensional = false;

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpContentTableView->resizeRowsToContents();
      mpContentTableView->resizeColumnsToContents();
    }

  if (mpStack->currentIndex() != 0)
    fillBarChart();
}

void CQArrayAnnotationsWidget::fillTable1(size_t rowIndex,
    const CArrayInterface::index_type & index)
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillTable0 B -- \n";
#endif

  if (!mpArray) return;

  assert(rowIndex < index.size());

  size_t i, imax = mpArray->size()[rowIndex];

  CArrayInterface::index_type Index = index;

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

  mpDataModel->setContext(mpColorScale, mpArray, index, rowIndex, C_INVALID_INDEX);

  mOneDimensional = true;

  if (CRootContainer::getConfiguration()->resizeToContents())
    {
      mpContentTableView->resizeRowsToContents();
      mpContentTableView->resizeColumnsToContents();
    }

  if (mpStack->currentIndex() != 0)
    fillBarChart();
}

void CQArrayAnnotationsWidget::fillTable0()
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillTable0 C -- \n";
#endif

  if (!mpArray) return;

  CArrayInterface::index_type Index;
  mpColorScale->startAutomaticParameterCalculation();
  mpColorScale->passValue((*mpArray->array())[Index]);
  mpColorScale->finishAutomaticParameterCalculation();

  mpDataModel->setContext(mpColorScale, mpArray, Index, C_INVALID_INDEX, C_INVALID_INDEX);
}

void CQArrayAnnotationsWidget::changeContents()
{
#ifdef DEBUG_UI
  qDebug() << "-- in changeContents -- \n";
#endif

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
          if (mpStack->currentIndex() != 0)
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
  mpStack->setCurrentWidget(mpContentTableView);

#ifdef DEBUG_UI
  qDebug() << "B mpStack->currentIndex() = " << mpStack->currentIndex();
#endif

  if (mWithBarChart)
    {
      mpButton->setIcon(CQIconResource::icon(CQIconResource::bars));
      setFocusOnTable();
    }

  if (mpContentTableView->isSortingEnabled())
    {
      mpButtonReset->show();
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

#ifdef WITH_QT5_VISUALIZATION

      if (!m_container)
        createBarChart();

      fillBarChart();

      mpStack->setCurrentWidget(m_container);

      setFocusOnBars();
#else

      if (!mpPlot3d)
        createBarChart();

      if (!mBarChartFilled)
        fillBarChart();

      setFocusOnBars();

      mpStack->setCurrentWidget(mpPlot3d);
      mpPlot3d->show();

#endif // WITH_QT5_VISUALIZATION

      mpButton->setIcon(CQIconResource::icon(CQIconResource::table));
      mpButtonReset->hide();
    }
}

#ifdef WITH_QT5_VISUALIZATION

void CQArrayAnnotationsWidget::slotShowContextMenu(const QPoint &pos)
{
  if (mpStack->currentWidget() == m_container)
    {
      QWidget* pSender = qobject_cast<QWidget*>(sender());

      if (pSender != NULL)
        m_contextMenu->popup(mapToGlobal(pos));
      else
        m_contextMenu->popup(m_container->mapToGlobal(pos));
    }
}

#endif // WITH_QT5_VISUALIZATION

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

#ifndef WITH_QT5_VISUALIZATION

  if (mpPlot3d && mpPlot3d->isSliderActive())
    {
      mpPlot3d->setSliderActive(false);
    }

#endif
}

/*!
    Function to set the appearance focus on table
 */
void CQArrayAnnotationsWidget::setControlsEnabled(bool b)
{
  mpControls->setVisible(b);
}

void CQArrayAnnotationsWidget::setFocusOnTable()
{
  if (!mWithBarChart) return;

#ifdef WITH_QT5_VISUALIZATION

  if (!m_graph)
    return;

  auto* series = m_graph->selectedSeries();

  if (series)
    {
      QPoint bar = series->selectedBar();
      selectTableCell(bar.rx(), bar.ry());
    }

#else

  if (mpPlot3d && mpPlot3d->isSliderActive())
    {
      int row = mpPlot3d->mpSliderRow->value() / mpPlot3d->scaleFactor();
      int col = mpPlot3d->mpSliderColumn->value() / mpPlot3d->scaleFactor();

      selectTableCell(row, col);
    }

#endif
}

void CQArrayAnnotationsWidget::selectTableCell(int row, int col)
{

  if (mpStack->currentIndex() != 0)
    mpStack->setCurrentIndex(0);

  mpContentTableView->clearSelection();

  if (col < mpDataModel->columnCount())
    {
      if (row < mpDataModel->rowCount())
        {
          QModelIndex Index = mpProxyModel->mapFromSource(mpDataModel->index(row, col));
          mpContentTableView->setCurrentIndex(Index);
          mpContentTableView->scrollTo(Index);
          mpContentTableView->setFocus();
        }
      else
        {
          mpContentTableView->selectColumn(col);
          mpContentTableView->setFocus();
        }
    }
  else
    {
      if (row < mpDataModel->rowCount())
        {
          mpContentTableView->selectRow(row);
          mpContentTableView->setFocus();
        }
      else
        {
          mpContentTableView->scrollTo(QModelIndex());
        }
    }
}

/*!
    Function to set the appearance focus on bars
 */
void CQArrayAnnotationsWidget::setFocusOnBars()
{
#ifdef WITH_QT5_VISUALIZATION

  if (mWithBarChart && m_graph)
    {

      auto current = mpContentTableView->currentIndex();

      if (current.isValid())
        {
          m_modifier->selectBar(current.row(), current.column());
          m_modifier->zoomToSelectedBar();
          return;
        }
    }

#else

  if (mWithBarChart && mpPlot3d && mpPlot3d->isSliderActive())
    {

      auto it = mpContentTableView->currentIndex();

      int LeftColumn = std::numeric_limits< int >::max();
      int RightColumn = -1;
      int TopRow = std::numeric_limits< int >::max();
      int BottomRow = -1;

      if (!it.isValid())
        {
          // when we don't have entries, we reset the left / top to -1
          LeftColumn = -1;
          TopRow = -1;
        }

      if (it.column() < LeftColumn) LeftColumn = it.column();

      if (it.column() > RightColumn) RightColumn = it.column();

      if (it.row() < TopRow) TopRow = it.row();

      if (it.row() > BottomRow) BottomRow = it.row();

      int SliderColumn = LeftColumn * mpPlot3d->scaleFactor();
      int SliderRow = TopRow * mpPlot3d->scaleFactor();

      if (LeftColumn == RightColumn &&
          TopRow == BottomRow)
        {
          mpPlot3d->mpSliderColumn->setValue(SliderColumn);
          mpPlot3d->mpSliderRow->setValue(SliderRow);
          mpPlot3d->sliderMoved(LeftColumn, TopRow);
          mpPlot3d->setSlider();

          return;
        }

      if (LeftColumn == RightColumn)
        {
          mpPlot3d->mpSliderColumn->setValue(SliderColumn);
          mpPlot3d->mpSliderRow->setValue(-1);
          mpPlot3d->sliderMoved(LeftColumn, mpDataModel->rowCount());
          mpPlot3d->setSlider();

          return;
        }

      if (TopRow == BottomRow)
        {
          mpPlot3d->mpSliderColumn->setValue(-1);
          mpPlot3d->mpSliderRow->setValue(SliderRow);
          mpPlot3d->sliderMoved(mpDataModel->columnCount(), TopRow);
          mpPlot3d->setSlider();

          return;
        }

      mpPlot3d->mpSliderColumn->setValue(-1);
      mpPlot3d->mpSliderRow->setValue(-1);
      mpPlot3d->sliderMoved(mpDataModel->columnCount(), mpDataModel->rowCount());
      mpPlot3d->setSlider();
    }

#endif
}

void CQArrayAnnotationsWidget::slotContentCellClicked(const QModelIndex & index)
{
  QModelIndex SourceIndex = index;

  while (SourceIndex.model()->inherits("QSortFilterProxyModel"))
    {
      SourceIndex = static_cast< const QSortFilterProxyModel * >(SourceIndex.model())->mapToSource(SourceIndex);
    }

  switch (mSelectedCell.size())
    {
      case 0:
        break;

      case 1:
        mSelectedCell[mRowIndex] = SourceIndex.row();
        break;

      default:
        mSelectedCell[mRowIndex] = SourceIndex.row();
        mSelectedCell[mColIndex] = SourceIndex.column();
        break;
    }

  return;
}

void CQArrayAnnotationsWidget::slotContentDoubleClicked(const QModelIndex & index)
{
  slotContentCellClicked(index);

  if (mWithBarChart)
    switchToBarChart();
}

void CQArrayAnnotationsWidget::setColumnSize(int col, int /*size0*/, int /*size*/)
{
  disconnect(mpContentTableView->horizontalHeader(), SIGNAL(sectionResized(int, int, int)), this, SLOT(setColumnSize(int, int, int)));

#ifdef DEBUG_UI
  qDebug() << "-- in setColumnSize -- \n";
#endif

  C_INT32 i;
  C_FLOAT64 sum = 0;

  for (i = 0; i <= col; ++i)
    sum += mpContentTableView->horizontalHeader()->sectionSize(i);

  C_FLOAT64 newSize = sum / (col + 1);

  if (newSize < 5) newSize = 5;

  for (i = 0; i < mpDataModel->columnCount(); i++)
    mpContentTableView->setColumnWidth(i, ((int)(newSize * (i + 1))) - ((int)(newSize * i)));

  mpContentTableView->horizontalHeader()->repaint();

  connect(mpContentTableView->horizontalHeader(), SIGNAL(sectionResized(int, int, int)), this, SLOT(setColumnSize(int, int, int)));
}

void CQArrayAnnotationsWidget::slotResetSortOrder()
{
  mpProxyModel->sort(-1);
}

void CQArrayAnnotationsWidget::fillBarChart()
{
#ifdef DEBUG_UI
  qDebug() << "-- in fillBarChart -- \n";
#endif

  if (!mWithBarChart)
    return;

  if (!mpArray) return;

#ifdef WITH_QT5_VISUALIZATION

  m_modifier->loadData(mpArray, mRowIndex, mColIndex);

#else

  if (!mpPlot3d)
    createBarChart();

  //  mBarChartFilled = true;

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

            if (std::isnan((double)(*mpArray->array())[mSelectedCell]) ||
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

#endif
}

void CQArrayAnnotationsWidget::createBarChart()
{
  if (!mWithBarChart) return;

#ifdef WITH_QT5_VISUALIZATION

  m_graph = new Q3DBars();

  m_container = QWidget::createWindowContainer(m_graph);
  mpStack->addWidget(m_container);

  if (m_graph->hasContext())
    {
      m_modifier = new CQ3DBarsModifier(this, m_graph);

      m_contextMenu = new QMenu(this);

      QMenu* menu = new QMenu("Theme", m_contextMenu);
      menu->addAction(new QAction("Qt", menu));
      menu->addAction(new QAction("Primary Colors", menu));
      menu->addAction(new QAction("Digia", menu));
      menu->addAction(new QAction("Stone Moss", menu));
      menu->addAction(new QAction("Army Blue", menu));
      menu->addAction(new QAction("Retro", menu));
      menu->addAction(new QAction("Ebony", menu));
      menu->addAction(new QAction("Isabelle", menu));
      m_contextMenu->addMenu(menu); // theme

      menu = new QMenu("Selection Mode", m_contextMenu);
      menu->addAction(new QAction("None", menu));
      menu->addAction(new QAction("Bar", menu));
      menu->addAction(new QAction("Row", menu));
      menu->addAction(new QAction("Bar and Row", menu));
      menu->addAction(new QAction("Column", menu));
      menu->addAction(new QAction("Bar and Column", menu));
      menu->addAction(new QAction("Row and Column", menu));
      menu->addAction(new QAction("Bar, Row and Column", menu));
      menu->addAction(new QAction("Slice into Row", menu));
      menu->addAction(new QAction("Slice into Row and Item", menu));
      menu->addAction(new QAction("Slice into Column", menu));
      menu->addAction(new QAction("Slice into Column and Item", menu));
      m_contextMenu->addMenu(menu); // selection mode

      menu = new QMenu("Style", m_contextMenu);
      menu->addAction(new QAction("Bar", menu));
      menu->addAction(new QAction("Pyramid", menu));
      menu->addAction(new QAction("Cone", menu));
      menu->addAction(new QAction("Cylinder", menu));
      menu->addAction(new QAction("Bevel bar", menu));
      menu->addAction(new QAction("Sphere", menu));
      m_contextMenu->addMenu(menu); // style

      menu = new QMenu("Shadow", m_contextMenu);
      menu->addAction(new QAction("None", menu));
      menu->addAction(new QAction("Low", menu));
      menu->addAction(new QAction("Medium", menu));
      menu->addAction(new QAction("High", menu));
      menu->addAction(new QAction("Low Soft", menu));
      menu->addAction(new QAction("Medium Soft", menu));
      menu->addAction(new QAction("High Soft", menu));
      m_contextMenu->addMenu(menu); // style

      m_contextMenu->addSeparator();

      m_contextMenu->addAction(new QAction("Change label style"));
      m_contextMenu->addAction(new QAction("Smooth bars"));
      m_contextMenu->addAction(new QAction("Change camera preset"));
      m_contextMenu->addAction(new QAction("Zoom to selected bar"));
      m_contextMenu->addAction(new QAction("Show background"));
      m_contextMenu->addAction(new QAction("Show grid"));
      m_contextMenu->addAction(new QAction("Show reflections"));
      m_contextMenu->addAction(new QAction("Show Gradients"));

      connect(m_contextMenu, SIGNAL(triggered(QAction*)), m_modifier, SLOT(actionTriggered(QAction*)));

      setContextMenuPolicy(Qt::CustomContextMenu);
      connect(this, SIGNAL(customContextMenuRequested(const QPoint &)), this, SLOT(slotShowContextMenu(const QPoint &)));
    }

#else
  mpPlot3d = new CQBarChart();
  mpPlot3d->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);

  if (mUseSliders)
    {
      mpPlot3d->setSliderActive(true);
    }

  mpStack->addWidget(mpPlot3d);

  mBarChartFilled = false;

#endif // WITH_QT5_VISUALIZATION
}
