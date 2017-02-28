// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQPLOTCOLORS_H
#define CQPLOTCOLORS_H

#include <QColor>
#include <string>
#include "copasi/plot/CPlotColors.h"

/*
 * This is for handling colors for plotting in COPASI in a QT context.
 * It is based on CPlotColors and adds the functionality that uses QT.
 */
class CQPlotColors : public CPlotColors
{
public:

  /*
   * returns a CColor. If colorstr is "auto" the color will be from a list of
   * predefined colors with index colorindex.
   * Otherwise colorstr is interpreted as RGBA in Hex.
   */
  static QColor getColor(std::string colorstr, size_t colorindex);
};

#endif // CQPLOTCOLORS_H
