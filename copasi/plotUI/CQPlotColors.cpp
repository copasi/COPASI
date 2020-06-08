// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2012 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "copasi/copasi.h"
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
