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

#include "copasi.h"
#include "CQPlotColors.h"

//static
QColor CQPlotColors::getColor(std::string colorstr, size_t colorindex)
{
  if (colorstr == "auto")
    {
      return QColor(getCopasiColorStr(colorindex).c_str());
    }
  else
    {
      return QColor(colorstr.c_str());
    }
}
