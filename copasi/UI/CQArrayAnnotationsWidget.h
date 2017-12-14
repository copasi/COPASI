// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef CQARRAYANN_H
#define CQARRAYANN_H

#include <QtCore/QVariant>

#include "copasi/UI/ui_CQArrayAnnotationsWidget.h"
#include "copasi/UI/CColorScale.h"

#include "copasi/core/CDataArray.h"

class QLabel;

class CQBarChart;
class CQComboDelegate;
class CQArrayAnnotationsWidgetDM;
class CQSortFilterProxyModel;

/**
 * This Widget displays a CArrayAnnotation (no editing yet)
 */
class CQArrayAnnotationsWidget : public QWidget, public Ui::CQArrayAnnotationsWidget
{
  Q_OBJECT

public:

  CQArrayAnnotationsWidget(QWidget* parent = 0, bool slider = true);

  virtual ~CQArrayAnnotationsWidget();

  void setArrayAnnotation(const CDataArray * pArray);

  /**
   * set an algorithm for color coding. If cs=NULL no color coding is performed. The widget assumes
   * ownership of the scaler and will delete it in its destructor. This means a CColorScale
   * can only be used in one widget.
   */
  void setColorCoding(CColorScale * cs);

  /**
   * returns the color coding algorithm
   */
  CColorScale * getColorCoding() const;

public slots:

  /**
   * if true the parameters for the color coding are determined automatically
   */
  void setColorScalingAutomatic(bool s);

  /**
   * Enable or disable the display of the dimensions annotation (the upper table)
   */
  void setLegendEnabled(bool b);

  /**
   * Enable or disable the display of sorting by columns
   */
  void setSortingEnabled(bool b);

  /**
   * Disables the bar chart 
   */
  void disableBarChart();

  /**
   * disable the slider
   */
  void disableSlider();

  /**
   * Show / Hide controls 
   * @param b boolean indicating whether the controls should be visible or not
   */
  void setControlsEnabled(bool b);

  void setFocusOnTable();

  void setFocusOnBars();

  void switchToTable();

  void clearWidget();

  void slotRowSelectionChanged(int row);

  void slotColumnSelectionChanged(int col);
  
  void slotCurrentSelectionIndexChanged(int row, int index);

  void slotContentCellClicked(const QModelIndex & index);

  void slotContentDoubleClicked(const QModelIndex & index);

  void changeContents();

  void setColumnSize(int col, int size0, int size);

  void slotResetSortOrder();

protected:
  void fillTable();

  void fillTableN(size_t rowIndex, size_t colIndex,
                  const CArrayInterface::index_type & index);

  void fillTable1(size_t rowIndex,
                  const CArrayInterface::index_type & index);

  void fillTable0();

  void createBarChart();

  void fillBarChart();

  /**
   *  only for dimensionality > 2
   */
  void initSelectionTable();

  /**
   * indicates whether 3d bar chart is activated
   */
  bool mWithBarChart;

  /**
   * indicates whether sliders are used in the 3d bar chart
   */
  bool mUseSliders;

  double** data;
  std::vector< QColor > mColors;
  void enableBarChart(bool enable);
  //void switchToTable();
  void switchToBarChart();

  const CDataArray * mpArray;

  CColorScale* mpColorScale;
  bool mAutomaticColorScaling;

  size_t mRowIndex;
  size_t mColIndex;
  CArrayInterface::index_type mSelectionIndex;

  CArrayInterface::index_type mSelectedCell;

  bool mBarChartFilled;
  bool mOneDimensional;

  QStringList mComboEntries;
  CQComboDelegate* mpComboDelegate;

  CQArrayAnnotationsWidgetDM * mpDataModel;
  CQSortFilterProxyModel * mpProxyModel;
};

#endif
