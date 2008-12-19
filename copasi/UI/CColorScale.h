// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CColorScale.h,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/27 10:46:48 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef CCOLORSCALE_H
#define CCOLORSCALE_H

#include <qcolor.h>

#ifdef SunOS
# include <ieeefp.h>
#endif

#include "copasi.h"

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
    CColorScale(): mIsUsed(false){};

    virtual ~CColorScale(){};

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

    /**
     * this is called by the array annotation widget to indicate that the scaler is in use
     */
    void setIsUsed(bool f) {mIsUsed = f;};

    /**
     * if setIsUsed() was used isUsed() can be called to find out if the scaler is
     * already in use. One scaler must not be used in several widgets.
     */
    bool isUsed() const {return mIsUsed;};

  private:
    /**
     * This flag indicates whether the scaler is in use. The widget using the scaler must
     * call setIsUsed() to keep this up to date.
     */
    bool mIsUsed;
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
 * The same mapping as in the base class.
 * Option to set user defined colors for the min and
 * max value.
 */
class CColorScaleAdvanced : public CColorScaleSimple
  {
  public:

    CColorScaleAdvanced();

    virtual QColor getColor(const C_FLOAT64 & number);

    void setColorMin(QColor col);
    void setColorMax(QColor col);

  protected:

    QColor mColorMin;
    QColor mColorMax;
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
    void setWhitepoint(const C_FLOAT64 & n);

    /**
    *
    */
    void setMaxIntensityPoint(const C_FLOAT64 & n);

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

#endif
