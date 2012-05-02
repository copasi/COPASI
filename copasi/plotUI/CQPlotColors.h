// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/cvs_admin/addHeader,v $
//   $Revision: 1.18 $
//   $Name: HEAD $
//   $Author: shoops $
//   $Date: 2012/03/07 20:49:51 $
// End CVS Header

// Copyright (C) 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CQPLOTCOLORS_H
#define CQPLOTCOLORS_H

#include <qcolor.h>
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
