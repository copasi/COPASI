// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQArrayAnnotationsWidget.h,v $
//   $Revision: 1.23 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/10/07 11:56:32 $
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

#include "copasi/UI/ui_CQArrayAnnotationsWidget.h"

// #include <QLabel>
// #include <QPushButton>
// #include <QStackedWidget>

// #include <vector>

#include "copasi/utilities/CAnnotatedMatrix.h"
#include "utilities/CAnnotatedMatrix.h"
#include "mathematics.h"
#include "CColorScale.h"

class Q3Table;
class QLabel;

class CQBarChart;
class CQComboDelegate;

/**
 * This Widget displays a CArrayAnnotation (no editing yet)
 */
class CQArrayAnnotationsWidget : public QWidget, public Ui::CQArrayAnnotationsWidget
{
  Q_OBJECT

public:

  CQArrayAnnotationsWidget(QWidget* parent = 0, const char* name = 0, bool barChart = true, bool slider = true);

  virtual ~CQArrayAnnotationsWidget();

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

  void slotRowSelectionChanged(int row);

  void slotColumnSelectionChanged(int col);

  void slotCurrentSelectionIndexChanged(int row, int index);

  void slotContentCellClicked(int row, int col);

  void slotContentDoubleClicked();

  void changeContents();

  void setColumnSize(int col, int size0, int size);

protected:
  void fillTable();

  void fillTableN(size_t rowIndex, size_t colIndex,
                  const CCopasiAbstractArray::index_type & index);

  void fillTable1(size_t rowIndex,
                  const CCopasiAbstractArray::index_type & index);

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

  const CArrayAnnotation * mpArray;

  CColorScale* mpColorScale;
  bool mAutomaticColorScaling;

  size_t mRowIndex;
  size_t mColIndex;
  CCopasiAbstractArray::index_type mSelectionIndex;

  CCopasiAbstractArray::index_type mSelectedCell;

  bool mBarChartFilled;
  bool mOneDimensional;

  QStringList mComboEntries;
  CQComboDelegate* mpComboDelegate;
};

#endif
