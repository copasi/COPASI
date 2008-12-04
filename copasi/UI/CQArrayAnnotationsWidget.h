// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQArrayAnnotationsWidget.h,v $
//   $Revision: 1.13.2.4 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/12/04 15:58:27 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQARRAYANN_H
#define CQARRAYANN_H

#include <qvbox.h>
#include <qhbox.h>
#include <qpushbutton.h>
#include <qwidgetstack.h>

#include <vector>

#include "copasi/utilities/CAnnotatedMatrix.h"
#include "CColorScale.h"

class QGridLayout;
class QTable;
class QLabel;

class CQBarChart;

/**
 * This Widget displays a CArrayAnnotation (no editing yet)
 */
class CQArrayAnnotationsWidget : public QVBox
  {
    Q_OBJECT

  public:

    CQArrayAnnotationsWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0, bool barChart = true, bool slider = true /*, bool barChartFirst = false*/);
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

  protected slots:

    void selectionTableChanged(int row, int col);

    void changeContents();

    void tableDoubleClicked();

    void setColumnSize(int col, int size0, int size);

  protected:

    void fillTable(unsigned C_INT32 rowIndex, unsigned C_INT32 colIndex,
                   CCopasiAbstractArray::index_type & index);
    void fillTable(unsigned C_INT32 rowIndex,
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

    void clearWidget();

    CQBarChart* mpPlot3d;

    QHBox* mpHBoxSelection;
    QHBox* mpHBoxContents;
    QWidgetStack* mpStack;

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
    void switchToTable();
    void switchToBarChart();

    QTable* mpSelectionTable;
    QTable* mpContentTable;

    const CArrayAnnotation * mpArray;

    CColorScale* mpColorScale;
    bool mAutomaticColorScaling;

    unsigned C_INT32 mRowIndex;
    unsigned C_INT32 mColIndex;
    CCopasiAbstractArray::index_type mIndex;
    bool mBarChartFilled;
    bool mOneDimensional;
    /**
     * the current active item of all the combo boxes
     */
    std::vector<C_INT32> combos;
  };

#endif
