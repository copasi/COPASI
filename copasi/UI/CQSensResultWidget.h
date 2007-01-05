/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQSensResultWidget.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: ssahle $
   $Date: 2007/01/05 16:35:01 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef CQSENSRESULT_H
#define CQSENSRESULT_H

#include "qvbox.h"
#include "UI/copasiWidget.h"
//#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CAnnotatedMatrix.h"

class QGridLayout;
class QLineEdit;
class QLabel;
class QTable;

class CColorScale
  {
  public:
    virtual QColor getColor(const C_FLOAT64 & number) = 0;

    virtual void startAutomaticParameterCalculation() {};
    virtual void passValue(const C_FLOAT64 & /*number*/) {};
    virtual void finishAutomaticParameterCalculation() {};
  };

class CColorScale1 : public CColorScale
  {
  public:
    CColorScale1();

    void setThreshold(const C_FLOAT64 & n) {m1 = n;};

    virtual QColor getColor(const C_FLOAT64 & number);

  protected:
    C_FLOAT64 m1;
  };

class CColorScaleSimple : public CColorScale
  {
  public:
    CColorScaleSimple();

    void setMinMax(const C_FLOAT64 & min, const C_FLOAT64 & max)
    {mMin = min; mMax = max;};

    void setLog(bool l) {mLog = l;}    ; //log not implemented yet!

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

class CColorScaleAverage : public CColorScaleSimple
  {
  public:
    CColorScaleAverage();

    void setFactor(C_FLOAT64 f) {mFactor = f;};

    virtual void startAutomaticParameterCalculation();
    virtual void passValue(const C_FLOAT64 & number);
    virtual void finishAutomaticParameterCalculation();

  protected:
    C_FLOAT64 mFactor;
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

    void setColorCoding(CColorScale * cs) {mpColorScale = cs;};

    CColorScale * getColorCoding() const {return mpColorScale;};

    void setColorScalingAutomatic(bool s) {mAutomaticColorScaling = s;};

  protected slots:

    void selectionTableChanged(int row, int col);

  protected:

    void fillTable(unsigned C_INT32 rowIndex, unsigned C_INT32 colIndex,
                   CCopasiAbstractArray::index_type & index);
    void fillTable(unsigned C_INT32 rowIndex,
                   CCopasiAbstractArray::index_type & index);

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

    //QLabel* mLabelSum;
    //QLabel* mLabelDivergence;
    //QLabel* mLabelComment;

    //QTable* mTableExponents;
    //QLineEdit* mLineEditSum;
    //QLineEdit* mLineEditDivergence;
  };

#endif
