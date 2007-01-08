/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSensResultWidget.h,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: ssahle $
   $Date: 2007/01/08 14:49:21 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQSENSRESULT_H
#define CQSENSRESULT_H

#include <qvbox.h>
#include "UI/copasiWidget.h"
#include "utilities/CAnnotatedMatrix.h"
#include "mathematics.h"

class QGridLayout;
class QLineEdit;
class QLabel;
class QTable;

/**
 * Base class for color scales. The derived classes provide algorithms
 * to map a double number to a QColor.
 * The scaling parameters can either be set automatically (by using methods
 * provided by the derived classes) or be determined automatically.
 * For automatic scaling all numbers that are to be displayed (or at least
 * a typical sample) have to be passed to the passValue() method before the
 * getColor() method is used.
 * This class is used by ArrayAnnotationWidget.
 */
class CColorScale
  {
  public:
    /**
     * this method maps a number to a color.
     */
    virtual QColor getColor(const C_FLOAT64 & number) = 0;

    /**
     * this method starts the calculation of the scaling parameters.
     */
    virtual void startAutomaticParameterCalculation() {};

    /**
     * with this method numbers are passed to the automatic scaling algorithm.
     */
    virtual void passValue(const C_FLOAT64 & /*number*/) {};

    /**
     * this finishes the calculation of the scaling parameters.
     */
    virtual void finishAutomaticParameterCalculation() {};
  };

/**
 * This returns white, if the absolute value of the number is smaller than the
 * threshold. Otherwise if it is positive, the color is green, if negative red.
 */
class CColorScale1 : public CColorScale
  {
  public:
    CColorScale1();

    void setThreshold(const C_FLOAT64 & n) {m1 = n;};

    virtual QColor getColor(const C_FLOAT64 & number);

  protected:
    C_FLOAT64 m1;
  };

/**
 * This maps a range of numbers to a range of colors.
 * Automatic scaling looks for minimum and maximum of
 * the provided numbers
 */
class CColorScaleSimple : public CColorScale
  {
  public:
    CColorScaleSimple();

    /**
    * Set minimum and maximum of number range
    */
    void setMinMax(const C_FLOAT64 & min, const C_FLOAT64 & max)
    {mMin = min; mMax = max;};

    /**
    * Log scaling is not yet implemented
    */
    void setLog(bool l) {mLog = l;}    ; //log not implemented yet!

    /**
    * If this is true, the number range (if automatically determined)
    * is centered around 0.0.
    */
    void setSymmetric(bool s) {mSym = s;};

    virtual QColor getColor(const C_FLOAT64 & number);

    virtual void startAutomaticParameterCalculation();
    virtual void passValue(const C_FLOAT64 & number);
    virtual void finishAutomaticParameterCalculation();

  protected:
    C_FLOAT64 mMin;
    C_FLOAT64 mMax;
    bool mLog;
    bool mSym;
  };

/**
 * the same mapping as in the base class. However the automatic scaling
 * is done using the average of the absolute values of the provided numbers.
 * The average of the absolute values is multiplied by the factor to give the
 * range.
 */
class CColorScaleAverage : public CColorScaleSimple
  {
  public:
    CColorScaleAverage();

    /**
    *
    */
    void setFactor(C_FLOAT64 f) {mFactor = f;};

    virtual void startAutomaticParameterCalculation();
    virtual void passValue(const C_FLOAT64 & number);
    virtual void finishAutomaticParameterCalculation();

  protected:
    C_FLOAT64 mFactor;
    C_FLOAT64 mFloat;
    C_INT32 mInt;
  };

class CColorScaleBiLog : public CColorScale
  {
  public:
    CColorScaleBiLog();

    /**
    *
    */
    void setWhitepoint(const C_FLOAT64 & n) {m1 = log(n);};

    /**
    *
    */
    void setMaxIntensityPoint(const C_FLOAT64 & n) {m2 = log(n);};

    virtual QColor getColor(const C_FLOAT64 & number);

    virtual void startAutomaticParameterCalculation();
    virtual void passValue(const C_FLOAT64 & number);
    virtual void finishAutomaticParameterCalculation();

  protected:
    C_FLOAT64 m1;
    C_FLOAT64 m2;

    C_FLOAT64 mFloat;
    C_INT32 mInt;
  };

//*********************************************************************

/**
 * This Widget displays a CArrayAnnotation (no editing yet)
 */
class ArrayAnnotationsWidget : public QVBox
  {
    Q_OBJECT

  public:
    ArrayAnnotationsWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ArrayAnnotationsWidget();

    void setArrayAnnotation(const CArrayAnnotation * pArray);

    /**
     * set an algorithm for color coding. If cs=NULL no color coding is performed
     */
    void setColorCoding(CColorScale * cs) {mpColorScale = cs;};

    /**
     * returns the color coding algorithm
     */
    CColorScale * getColorCoding() const {return mpColorScale;};

    /**
     * if true the parameters for the color coding are determined automatically
     */
    void setColorScalingAutomatic(bool s) {mAutomaticColorScaling = s;};

  protected slots:

    void selectionTableChanged(int row, int col);

  protected:

    void fillTable(unsigned C_INT32 rowIndex, unsigned C_INT32 colIndex,
                   CCopasiAbstractArray::index_type & index);
    void fillTable(unsigned C_INT32 rowIndex,
                   CCopasiAbstractArray::index_type & index);
    void fillTable();

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

    QTable* mpSelectionTable;
    QTable* mpContentTable;

    const CArrayAnnotation * mpArray;

    CColorScale* mpColorScale;
    bool mAutomaticColorScaling;

    /**
     * the current active item of all the combo boxes
     */
    std::vector<C_INT32> combos;
  };

//*****************************************************

class QTabWidget;

class CQSensResultWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    CQSensResultWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CQSensResultWidget();

    void newResult();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:

  protected:
    //bool loadFromBackend();
    void clearArrays();

    QGridLayout* mWidgetLayout;

    QLabel* mLabelTitle;

    QTabWidget* mpTab;

    ArrayAnnotationsWidget* mArrayWidget;
    ArrayAnnotationsWidget* mArrayWidgetScaled;

    const CArrayAnnotation * mpResult;
    const CArrayAnnotation * mpScaledResult;
  };

#endif
