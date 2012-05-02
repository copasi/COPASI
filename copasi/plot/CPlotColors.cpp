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

#include "CPlotColors.h"

//static
std::string CPlotColors::getCopasiColorStr(size_t index)
{
  index = index % 6;

  switch (index)
    {
      case 0: return "#FF0000";
      case 1: return "#0000FF";
      case 2: return "#00E600";
      case 3: return "#00BEF0";
      case 4: return "#F000FF";
      case 5: return "#F0C800";

    }

  return "auto";
}



//QColor curveColours[6] = {QColor(255, 0, 0), QColor(0, 0, 255), QColor(0, 230, 0), QColor(0, 190, 240), QColor(240, 0, 255), QColor(240, 200, 0)} ; //TODO
