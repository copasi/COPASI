// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "CLGradientStops.h"

#include <cmath>
#include <assert.h>

#include "copasi/layout/CLGradientStop.h"
#include "copasi/layout/CLRelAbsVector.h"

CLGradientStops::CLGradientStops(const CLGradientBase* pGradient, const std::map<std::string, CLRGBAColor>& colormap)
  : mSpreadMethod(pGradient->getSpreadMethod()), mColorData(NULL), mIndex(0), mHelp(0.0)
{
  size_t i, iMax = pGradient->getNumGradientStops();

  if (iMax > 0)
    {
      this->mColorData = new unsigned char[4 * iMax];
      this->mIndex = 0;
      const CLGradientStop* pStop = NULL;
      std::string stopColor;
      std::map<std::string, CLRGBAColor>::const_iterator pos;
      double v = 0.0;
      std::list<std::pair<double, unsigned int> >::reverse_iterator last;

      for (i = 0; i < iMax; ++i)
        {
          pStop = pGradient->getGradientStop(i);
          assert(pStop != NULL);
          stopColor = pStop->getStopColor();
          assert(stopColor.find_first_not_of(" \t\n\r") != std::string::npos && stopColor != "none");
          pos = colormap.find(stopColor);
          assert(pos != colormap.end());
          // offsets can only be relative values, so we ignore the absolute part
          v = pStop->getOffset().getRelativeValue() / 100.0;

          // we cap at 0.0 and 1.0
          if (v < 0.0)
            {
              v = 0.0;
            }

          if (v > 1.0)
            {
              v = 1.0;
            }

          // make sure each stop has an offset
          // greater or equal to the preceeding
          // offset
          if (i != 0)
            {
              if (v < last->first)
                {
                  v = last->first;
                }
            }

          //std::cout << "adding stop: (" << v << "," << this->mIndex << ")" << std::endl;
          mStops.push_back(std::pair<double, unsigned int>(v, this->mIndex));
          last = this->mStops.rbegin();
          this->mColorData[this->mIndex] = pos->second.mR;
          this->mColorData[++this->mIndex] = pos->second.mG;
          this->mColorData[++this->mIndex] = pos->second.mB;
          this->mColorData[++this->mIndex] = pos->second.mA;
          ++this->mIndex;
          //std::cout << "stop color: (" << (unsigned int)pos->second.r << "," << (unsigned int)pos->second.g << "," << (unsigned int)pos->second.b << "," << (unsigned int)pos->second.a << ")" << std::endl;
        }
    }
  else
    {
      // we add one color which is completly transparent black
      this->mColorData = new unsigned char[4];
      this->mColorData[0] = 0;
      this->mColorData[1] = 0;
      this->mColorData[2] = 0;
      this->mColorData[3] = 0;
      this->mStops.push_back(std::pair<double, unsigned int>(0.0, 0));
    }

  this->mBegin = this->mStops.begin();
  this->mEnd = this->mStops.end();
  this->mCurrentPosition = this->mBegin;
}

CLGradientStops::~CLGradientStops()
{
  if (this->mColorData != NULL)
    {
      delete[] this->mColorData;
    }
}

/**
 * Given a relative value, this routine returns
 * a const pointer to an rgba value that is 4 unsigned char long.
 * If the gradient that was used to create the CLGradientStops object
 * didn't have any gradient stops, the color that is returned is completly
 * transparent black.
 */
void CLGradientStops::update_color(double val)
{
  this->adjust_value(val);
  this->mTmp = this->mCurrentPosition;

  //double v=this->mCurrentPosition->first;
  if (val >= this->mCurrentPosition->first)
    {
      while (mTmp != mEnd && this->mTmp->first <= val)
        {
          ++this->mTmp;
          //v=this->mTmp->first;
        }

      this->mCurrentPosition = this->mTmp;

      if (this->mCurrentPosition == this->mEnd || this->mCurrentPosition->first > val)
        {
          --this->mCurrentPosition;
        }

      //v=this->mCurrentPosition->first;
      this->mIndex = this->mCurrentPosition->second;
      this->mColor.mR = this->mColorData[this->mIndex];
      this->mColor.mG = this->mColorData[++this->mIndex];
      this->mColor.mB = this->mColorData[++this->mIndex];
      this->mColor.mA = this->mColorData[++this->mIndex];

      if (this->mCurrentPosition->first < val && this->mTmp != this->mEnd)
        {
          // we need to calculate the exact color value from mTmp and mCurrentPosition
          //v=this->mTmp->first;
          mHelp = (val - this->mCurrentPosition->first) / (this->mTmp->first - this->mCurrentPosition->first);
          this->mColor.mR += (unsigned char)(mHelp * (double)(this->mColorData[++this->mIndex] - this->mColor.mR));
          this->mColor.mG += (unsigned char)(mHelp * (double)(this->mColorData[++this->mIndex] - this->mColor.mG));
          this->mColor.mB += (unsigned char)(mHelp * (double)(this->mColorData[++this->mIndex] - this->mColor.mB));
          this->mColor.mA += (unsigned char)(mHelp * (double)(this->mColorData[++this->mIndex] - this->mColor.mA));
        }
    }
  else
    {
      // the value must be smaller than the value at the current position
      while (this->mTmp != this->mBegin && val < this->mTmp->first)
        {
          //v=this->mTmp->first;
          --this->mTmp;
        }

      this->mCurrentPosition = this->mTmp;
      //v=this->mCurrentPosition->first;
      this->mIndex = this->mCurrentPosition->second;
      this->mColor.mR = this->mColorData[this->mIndex];
      this->mColor.mG = this->mColorData[++this->mIndex];
      this->mColor.mB = this->mColorData[++this->mIndex];
      this->mColor.mA = this->mColorData[++this->mIndex];

      if (val > this->mTmp->first)
        {
          // we need to calculate the correct value
          ++this->mTmp;
          //v=this->mTmp->first;
          mHelp = (val - this->mCurrentPosition->first) / (this->mTmp->first - this->mCurrentPosition->first);
          this->mColor.mR += (unsigned char)(mHelp * (double)(this->mColorData[++this->mIndex] - this->mColor.mR));
          this->mColor.mG += (unsigned char)(mHelp * (double)(this->mColorData[++this->mIndex] - this->mColor.mG));
          this->mColor.mB += (unsigned char)(mHelp * (double)(this->mColorData[++this->mIndex] - this->mColor.mB));
          this->mColor.mA += (unsigned char)(mHelp * (double)(this->mColorData[++this->mIndex] - this->mColor.mA));
        }
    }
}

const CLRGBAColor& CLGradientStops::color() const
{
  return this->mColor;
}

void CLGradientStops::adjust_value(double& value) const
{
  if (value < 0.0)
    {
      switch (this->mSpreadMethod)
        {
          case CLGradientBase::PAD:
            value = 0.0;
            break;

          case CLGradientBase::REFLECT:
            // if the part of the distance before the decimal point
            // is devisible by 2, we just remove it
            // otherwise, we remove it and subtract the result from
            // 1.0
            value = fabs(value);

            if (((unsigned int)floor(value)) % 2 != 0)
              {
                value = 1.0 - (value - floor(value));
              }
            else
              {
                value = value - floor(value);
              }

            break;

          case CLGradientBase::REPEAT:
            // we only need everything after the decimal point
            // and we need to subtract from 1.0
            value = value - floor(value);
            break;
        }
    }
  else if (value > 1.0)
    {
      switch (this->mSpreadMethod)
        {
          case CLGradientBase::PAD:
            value = 1.0;
            break;

          case CLGradientBase::REFLECT:

            // if the part of the distance before the decimal point
            // is devisible by 2, we just remove it
            // otherwise, we remove it and subtract the result from
            // 1.0
            if (((unsigned int)floor(value)) % 2 != 0)
              {
                value = 1.0 - (value - floor(value));
              }
            else
              {
                value = value - floor(value);
              }

            break;

          case CLGradientBase::REPEAT:
            // we only need everything after the decimal point
            value = value - floor(value);
            break;
        }
    }
}
