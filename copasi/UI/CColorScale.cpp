// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <cmath>
#include <QtCore/qglobal.h>

#include <QPalette>

#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
#include <QGuiApplication>
#else
#include <QApplication>
#endif

#include "copasi/UI/CColorScale.h"
#include "copasi/UI/qtUtilities.h"

CColorScale::CColorScale()
  : mIsUsed(false)
  , mForeground()
  , mBackground()
  , mSmallNumbers()
  , mLargeNumbers()
  , mNaN(85, 85, 135)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  mForeground = Palette.color(QPalette::Active, QPalette::Text);
  mBackground = Palette.color(QPalette::Active, QPalette::Base);
    
  if (isLightMode())
    {
      mSmallNumbers = QColor(Qt::red);
      mLargeNumbers = QColor(Qt::green);
    }
  else
    {
      mSmallNumbers = QColor(Qt::darkRed);
      mLargeNumbers = QColor(Qt::darkGreen);
    }
};

CColorScaleDiscrete::CColorScaleDiscrete()
  : CColorScale()
  , m1(1e-4)
{}

//virtual
QColor CColorScaleDiscrete::getColor(const C_FLOAT64 & number) const
{
  if (fabs(number) < m1)
    return mBackground;

  if (number > 0)
    return mLargeNumbers;

  return mSmallNumbers;
}

//**************************

CColorScaleSimple::CColorScaleSimple()
  : CColorScale()
  , mMin(0.0)
  , mMax(1.0)
  , mLog(false)
  , mSym(false)
{}

//virtual
QColor CColorScaleSimple::getColor(const C_FLOAT64 & number) const
{
  //scale to 0..1
  C_FLOAT64 tmp;

  if (mLog)
    tmp = (log(number) - log(mMin)) / (log(mMax) - log(mMin));
  else
    tmp = (number - mMin) / (mMax - mMin);

  if (std::isnan(tmp))
    return mNaN;

  if (tmp > 1)
    tmp = 1;

  if (tmp < 0)
    tmp = 0;

  double red;
  double green;
  double blue;
  double alpha;

  if (tmp < 0.5)
    {
      tmp = 1.0 - 2.0 * tmp;
      red = mSmallNumbers.redF() * tmp + mBackground.redF() * (1.0 - tmp);
      green = mSmallNumbers.greenF() * tmp + mBackground.greenF() * (1.0 - tmp);
      blue = mSmallNumbers.blueF() * tmp + mBackground.blueF() * (1.0 - tmp);
      alpha = mSmallNumbers.alphaF() * tmp + mBackground.alphaF() * (1.0 - tmp);
    }
  else
    {
      tmp = 2.0 * tmp - 1.0;
      red = mLargeNumbers.redF() * tmp + mBackground.redF() * (1.0 - tmp);
      green = mLargeNumbers.greenF() * tmp + mBackground.greenF() * (1.0 - tmp);
      blue = mLargeNumbers.blueF() * tmp + mBackground.blueF() * (1.0 - tmp);
      alpha = mLargeNumbers.alphaF() * tmp + mBackground.alphaF() * (1.0 - tmp);
    }

  return QColor::fromRgbF(red, green, blue, alpha);
}

//virtual
void CColorScaleSimple::startAutomaticParameterCalculation()
{
  mMin = std::numeric_limits< C_FLOAT64 >::max();
  mMax = -std::numeric_limits< C_FLOAT64 >::max();
  mLog = false;
}

//virtual
void CColorScaleSimple::passValue(const C_FLOAT64 & number)
{
  //if (number != number) return; //NaN

  if (fabs(number) >= std::numeric_limits< C_FLOAT64 >::max())
    return; //Inf or max

  if (number > mMax)
    mMax = number;

  if (number < mMin)
    mMin = number;
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

      mMin = -tmp;
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
  mSmallNumbers = mBackground;
}

void CColorScaleAdvanced::setColorMin(QColor col)
{
  mSmallNumbers = col;
}

void CColorScaleAdvanced::setColorMax(QColor col)
{
  mLargeNumbers = col;
}

QColor CColorScaleAdvanced::getColor(const C_FLOAT64 & number) const
{
  //scale to 0..1
  C_FLOAT64 tmp;

  if (mLog && number > 0.0)
    tmp = (log(number) - log(mMin)) / (log(mMax) - log(mMin));
  else
    tmp = (number - mMin) / (mMax - mMin);

  if (std::isnan(tmp))
    return mNaN;

  if (tmp > 1)
    tmp = 1;

  if (tmp < 0)
    tmp = 0;

  int r = (int)(mSmallNumbers.red() * (1 - tmp) + mLargeNumbers.red() * tmp);
  int g = (int)(mSmallNumbers.green() * (1 - tmp) + mLargeNumbers.green() * tmp);
  int b = (int)(mSmallNumbers.blue() * (1 - tmp) + mLargeNumbers.blue() * tmp);
  int a = (int)(mSmallNumbers.alpha() * (1 - tmp) + mLargeNumbers.alpha() * tmp);

  return QColor(r, g, b, a);
}

//**************************

CColorScaleAuto::CColorScaleAuto()
  : CColorScaleAdvanced()
  , mData()
{
  QColor Tmp = mLargeNumbers;
  mLargeNumbers = QColor(mSmallNumbers.red(), mSmallNumbers.green(), mSmallNumbers.blue(), 80);
  mSmallNumbers = QColor(Tmp.red(), Tmp.green(), Tmp.blue(), 80);
}

//virtual
void CColorScaleAuto::startAutomaticParameterCalculation()
{
  CColorScaleSimple::startAutomaticParameterCalculation();
  mData.resize(0);
}

//virtual
void CColorScaleAuto::passValue(const C_FLOAT64 & number)
{
  CColorScaleSimple::passValue(number);

  if (std::find(mData.begin(), mData.end(), number) == mData.end())
    mData.push_back(number);
}

//virtual
void CColorScaleAuto::finishAutomaticParameterCalculation()
{
  CColorScaleSimple::finishAutomaticParameterCalculation();

  if (mData.size() >= 5)
    {
      C_INT32 q = mData.size() / 5;

      std::nth_element(mData.begin(), mData.end() - q - 1, mData.end());
      mMax = *(mData.end() - q - 1);
    }

  if (mMin > 0 && mMax > 0 && mMax / mMin > 100)
    {
      mLog = true;
    }

  if (mMin == mMax)
    {
      mMin -= 1e-5;
      mMax += 1e-5;
      mLog = false;
    }
}

//**************************

CColorScaleAverage::CColorScaleAverage()
  : CColorScaleSimple()
  , mFactor(3.0)
  , mFloat(0.0)
  , mInt(0)
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
  if (number != number)
    return; //NaN

  if (fabs(number) >= std::numeric_limits< C_FLOAT64 >::max())
    return; //Inf

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
  : CColorScale()
  , m1(-6.0)
  , m2(2.0)
  , mFloat(0.0)
  , mInt(0)
{}

//virtual
QColor CColorScaleBiLog::getColor(const C_FLOAT64 & number) const
{
  C_FLOAT64 logtmp = log(fabs(number));
  C_FLOAT64 tmp = (logtmp - m1) / (m2 - m1); //scale to 0..1

  if (std::isnan(tmp))
    return mNaN;

  if (tmp > 1)
    tmp = 1;

  if (tmp < 0)
    tmp = 0;

  double red;
  double green;
  double blue;
  double alpha;

  if (number < 0)
    {
      red = mSmallNumbers.redF() * tmp + mBackground.redF() * (1.0 - tmp);
      green = mSmallNumbers.greenF() * tmp + mBackground.greenF() * (1.0 - tmp);
      blue = mSmallNumbers.blueF() * tmp + mBackground.blueF() * (1.0 - tmp);
      alpha = mSmallNumbers.alphaF() * tmp + mBackground.alphaF() * (1.0 - tmp);
    }
  else
    {
      red = mLargeNumbers.redF() * tmp + mBackground.redF() * (1.0 - tmp);
      green = mLargeNumbers.greenF() * tmp + mBackground.greenF() * (1.0 - tmp);
      blue = mLargeNumbers.blueF() * tmp + mBackground.blueF() * (1.0 - tmp);
      alpha = mLargeNumbers.alphaF() * tmp + mBackground.alphaF() * (1.0 - tmp);
    }

  return QColor::fromRgbF(red, green, blue, alpha);
}

//virtual
void CColorScaleBiLog::startAutomaticParameterCalculation()
{
  m1 = std::numeric_limits< C_FLOAT64 >::max();
  m2 = -std::numeric_limits< C_FLOAT64 >::max();
  mFloat = 0.0;
  mInt = 0;
}

//virtual
void CColorScaleBiLog::passValue(const C_FLOAT64 & number)
{
  if (number != number)
    return; //NaN

  if (fabs(number) >= std::numeric_limits< C_FLOAT64 >::max())
    return; //Inf

  if (number == 0.0)
    return;

  C_FLOAT64 tmp = log(fabs(number));

  //minmax
  if (tmp > m2)
    m2 = tmp;

  if (tmp < m1)
    m1 = tmp;

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

void CColorScaleBiLog::setWhitepoint(const C_FLOAT64 & n)
{
  m1 = log(n);
}

void CColorScaleBiLog::setMaxIntensityPoint(const C_FLOAT64 & n)
{
  m2 = log(n);
}
