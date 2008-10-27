// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CColorScale.cpp,v $
//   $Revision: 1.1.2.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/10/27 10:46:48 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CColorScale.h"
#include <float.h>

#include "copasi/mathematics.h"

CColorScale1::CColorScale1()
    : m1(1e-4)
{}

//virtual
QColor CColorScale1::getColor(const C_FLOAT64 & number)
{
  QColor color;
  if (fabs(number) < m1)
    color = QColor(250, 250, 250);
  else if (number > 0)
    color = QColor(200, 255, 200);
  else
    color = QColor(255, 200, 200);
  return color;
}

//**************************

CColorScaleSimple::CColorScaleSimple()
    : mMin(0.0),
    mMax(1.0),
    mLog(false),
    mSym(false)
{}

//virtual
QColor CColorScaleSimple::getColor(const C_FLOAT64 & number)
{
  C_FLOAT64 tmp = (number - mMin) / (mMax - mMin); //scale to 0..1
  if (tmp > 1) tmp = 1;
  if (tmp < 0) tmp = 0;

  int r = 0;
  int g = 0;
  int b = 0;

  if (tmp != tmp)
    {
      r = 85;
      g = 85;
      b = 135;
    }
  else if (tmp < 0.5)
    {
      r = 255;
      g = (int) (255 + (tmp - 0.5) * 260);
      b = (int) (255 + (tmp - 0.5) * 260);
    }
  else
    {
      r = (int) (255 - (tmp - 0.5) * 260);
      g = 255;
      b = (int) (255 - (tmp - 0.5) * 260);
    }

  QColor color(r, g, b);
  return color;
}

//virtual
void CColorScaleSimple::startAutomaticParameterCalculation()
{
  mMin = DBL_MAX;
  mMax = -DBL_MAX;
}

//virtual
void CColorScaleSimple::passValue(const C_FLOAT64 & number)
{
  if (number > mMax) mMax = number;
  if (number < mMin) mMin = number;
}

//virtual
void CColorScaleSimple::finishAutomaticParameterCalculation()
{
  if (mSym)
    {
      C_FLOAT64 tmp;
      if (fabs(mMax) > fabs(mMin))
        tmp = fabs(mMax);
      else
        tmp = fabs(mMin);

      mMin = - tmp;
      mMax = tmp;
    }

  if (mMin == mMax)
    {
      mMin -= 1e-5;
      mMax += 1e-5;
    }
}

//**************************

CColorScaleAdvanced::CColorScaleAdvanced()
    : CColorScaleSimple()
{
  mColorMax = QColor(0, 255, 0);
  mColorMin = QColor(240, 240, 240);
}

void CColorScaleAdvanced::setColorMin(QColor col)
{
  mColorMin = col;
}

void CColorScaleAdvanced::setColorMax(QColor col)
{
  mColorMax = col;
}

QColor CColorScaleAdvanced::getColor(const C_FLOAT64 & number)
{
  C_FLOAT64 tmp = (number - mMin) / (mMax - mMin); //scale to 0..1
  if (tmp > 1) tmp = 1;
  if (tmp < 0) tmp = 0;

  int r = (int) (mColorMin.red() * (1 - tmp) + mColorMax.red() * tmp);
  int g = (int) (mColorMin.green() * (1 - tmp) + mColorMax.green() * tmp);
  int b = (int) (mColorMin.blue() * (1 - tmp) + mColorMax.blue() * tmp);

  QColor color(r, g, b);
  return color;
}

//**************************

CColorScaleAverage::CColorScaleAverage()
    : CColorScaleSimple(),
    mFactor(3.0),
    mFloat(0.0),
    mInt(0)
{}

//virtual
void CColorScaleAverage::startAutomaticParameterCalculation()
{
  mInt = 0;
  mFloat = 0;
}

//virtual
void CColorScaleAverage::passValue(const C_FLOAT64 & number)
{
  if (number != number) return; //NaN
  if (fabs(number) >= DBL_MAX) return; //Inf

  ++mInt;
  mFloat += fabs(number);
}

//virtual
void CColorScaleAverage::finishAutomaticParameterCalculation()
{
  if (mInt)
    mMax = mFactor * mFloat / mInt;
  else
    mMax = mFactor;
  mMin = -mMax;

  if (mMin == mMax)
    {
      mMin -= 1e-5;
      mMax += 1e-5;
    }
}

//**************************

CColorScaleBiLog::CColorScaleBiLog()
    : m1(-6.0),
    m2(2.0),
    mFloat(0.0),
    mInt(0)
{}

//virtual
QColor CColorScaleBiLog::getColor(const C_FLOAT64 & number)
{
  C_FLOAT64 logtmp = log(fabs(number));

  C_FLOAT64 tmp = (logtmp - m1) / (m2 - m1); //scale to 0..1
  if (tmp > 1) tmp = 1;
  if (tmp < 0) tmp = 0;

  if (number > 0)
    tmp = 0.5 + tmp * 0.5;
  else
    tmp = 0.5 - tmp * 0.5;

  int r = 0;
  int g = 0;
  int b = 0;

  if (tmp != tmp)
    {
      r = 85;
      g = 85;
      b = 135;
    }
  else if (tmp < 0.5)
    {
      r = 255;
      g = (int) (255 + (tmp - 0.5) * 260);
      b = (int) (255 + (tmp - 0.5) * 260);
    }
  else
    {
      r = (int) (255 - (tmp - 0.5) * 260);
      g = 255;
      b = (int) (255 - (tmp - 0.5) * 260);
    }

  QColor color(r, g, b);
  return color;
}

//virtual
void CColorScaleBiLog::startAutomaticParameterCalculation()
{
  m1 = DBL_MAX;
  m2 = -DBL_MAX;
  mFloat = 0.0;
  mInt = 0;
}

//virtual
void CColorScaleBiLog::passValue(const C_FLOAT64 & number)
{
  if (number != number) return; //NaN
  if (fabs(number) >= DBL_MAX) return; //Inf
  if (number == 0.0) return;

  C_FLOAT64 tmp = log(fabs(number));

  //minmax
  if (tmp > m2) m2 = tmp;
  if (tmp < m1) m1 = tmp;

  //average
  ++mInt;
  mFloat += tmp;
}

//virtual
void CColorScaleBiLog::finishAutomaticParameterCalculation()
{
  if (mInt != 0)
    m1 = (mFloat / mInt) - 4;
  else
    m1 = -4.0;
  m2 -= 1.0;
}

void CColorScaleBiLog::setWhitepoint(const C_FLOAT64 & n) {m1 = log(n);}

void CColorScaleBiLog::setMaxIntensityPoint(const C_FLOAT64 & n) {m2 = log(n);}
