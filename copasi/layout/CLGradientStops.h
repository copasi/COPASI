// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layout/CLGradientStops.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:20 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CLGradientStops_H__
#define CLGradientStops_H__

#include <list>
#include <map>
#include <string>

#include "CLRGBAColor.h"

#include "copasi/layout/CLGradientBase.h"

class CLGradientStops
{
protected:
  CLGradientBase::SPREADMETHOD mSpreadMethod;

  // an array of numStops RGBA values
  unsigned char* mColorData;

  // a list of stops, each stops has a relative value between 0 and 1
  // associated with an index into the color data
  std::list<std::pair<double, unsigned int> > mStops;

  // some iterators that are needed to calculate the color value
  std::list<std::pair<double, unsigned int> >::const_iterator mBegin;
  std::list<std::pair<double, unsigned int> >::const_iterator mEnd;
  std::list<std::pair<double, unsigned int> >::const_iterator mCurrentPosition;
  std::list<std::pair<double, unsigned int> >::const_iterator mTmp;

  // an index variable that saves us from instantiating one millions of times
  unsigned int mIndex;

  // a color object that allows us to return a reference to a color value
  // rather than having to copy a color millions of times
  CLRGBAColor mColor;

  // a double value that we need for each of the many calls to color
  // this way we don't need to reserve memory every time
  double mHelp;

public:
  // Construktor that creates a CLGradientStops object from
  // a gradient base object and a color map.
  CLGradientStops(const CLGradientBase* pGradient, const std::map<std::string, CLRGBAColor>& colormap);

  // Destructor
  ~CLGradientStops();

  void update_color(double val);

  const CLRGBAColor& color() const;

protected:
  /**
   * This method takes the given offset value and adjust it
   * if it is outside the rangr from 0.0 to 1.0 depending on
   * the spread method that has been set from the gradient.
   */
  void adjust_value(double& value) const;
};

#endif /* CLGradientStops_H__ */
