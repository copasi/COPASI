// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQArrayAnnotationsWidget.h,v $
//   $Revision: 1.21 $
//   $Name:  $
//   $Author: aekamal $
//   $Date: 2011/08/01 17:11:34 $
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

#ifndef CQARRAYANN_H
#define CQARRAYANN_H

#include <QLabel>
#include <QPushButton>
#include <QStackedWidget>

#include <vector>

#include "copasi/utilities/CAnnotatedMatrix.h"
#include "utilities/CAnnotatedMatrix.h"
#include "mathematics.h"
#include "CColorScale.h"

class Q3Table;
class QLabel;

class CQBarChart;

/**
 * This Widget displays a CArrayAnnotation (no editing yet)
 */
class CQArrayAnnotationsWidget : public QWidget
{
  Q_OBJECT

public:

  CQArrayAnnotationsWidget(QWidget* parent = 0, const char* name = 0, Qt::WFlags fl = 0, bool barChart = true, bool slider = true);
  ~CQArrayAnnotationsWidget();

  void setArrayAnnotation(const CArrayAnnotation * pArray);

  /**
   * set an algorithm for color coding. If cs=NULL no color coding is performed. The widget assumes
   * ownership of the scaler and will delete it in its destructor. This means a CColorScale
   * can only be used in one widget.
   */
  void setColorCoding(CColorScale * cs);

  /**
   * returns the color coding algorithm
   */
  CColorScale * getColorCoding() const {return mpColorScale;};

  /**
   * if true the parameters for the color coding are determined automatically
   */
  void setColorScalingAutomatic(bool s) {mAutomaticColorScaling = s;};

  /**
   * enable or disable the display of the dimensions annotation (the upper table)
   */
  void setLegendEnabled(bool b);

  void disableBarChart();

  void disableSlider();

  void setFocusOnTable();

  void setFocusOnBars();

  void switchToTable();

  void clearWidget();

protected slots:

  void selectionTableChanged(int row, int col);

  void changeContents();

  void tableDoubleClicked();

  void setColumnSize(int col, int size0, int size);

protected:

  void fillTable(size_t rowIndex, size_t colIndex,
                 CCopasiAbstractArray::index_type & index);
  void fillTable(size_t rowIndex,
                 CCopasiAbstractArray::index_type & index);
  void fillTable();

  void createBarChart();

  void fillBarChart();

  /**
   *  only for dimensionality > 2
   */
  void initSelectionTable();

  /**
   *  get the active item from the combo box in the specified
   *  row in the mpSelectionTable
   */
  C_INT32 currentItem(C_INT32 row);

  /**
   *  set the active item of the combo box in the specified
   *  row in the mpSelectionTable
   */
  void setCurrentItem(C_INT32 row, C_INT32 index);

  /**
   *  store the current state of all the combo boxes
   */
  void storeCurrentCombos();

  //void clearWidget();

  CQBarChart* mpPlot3d;

  QWidget* mpHBoxSelection;
  QWidget* mpHBoxContents;
//    Q3WidgetStack* mpStack;
  QStackedWidget* mpStack;

  /**
   * indicates whether 3d bar chart is activated
   */
  bool mWithBarChart;

  /**
   * indicates whether sliders are used in the 3d bar chart
   */
  bool mUseSliders;

  QPushButton* mpButton;
  double** data;
  std::vector< QColor > mColors;
  void enableBarChart(bool enable);
  //void switchToTable();
  void switchToBarChart();

  Q3Table* mpSelectionTable;
  Q3Table* mpContentTable;

  const CArrayAnnotation * mpArray;

  CColorScale* mpColorScale;
  bool mAutomaticColorScaling;

  size_t mRowIndex;
  size_t mColIndex;
  CCopasiAbstractArray::index_type mIndex;
  bool mBarChartFilled;
  bool mOneDimensional;
  /**
   * the current active item of all the combo boxes
   */
  std::vector<C_INT32> combos;
};

#endif
