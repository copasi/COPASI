// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

#include "CPlotColors.h"

//static
std::string CPlotColors::getCopasiColorStr(size_t index)
{
  index = index % getNumCopasiColors();

  switch (index)
    {
      case 0:
        return "#FF0000"; //red

      case 1:
        return "#0000FF"; //blue

      case 2:
        return "#00E600"; //green

      case 3:
        return "#00BEF0"; //deep sky blue

      case 4:
        return "#F000FF"; //magenta

      case 5:
        return "#F0C800"; //supernova

      case 6:
        return "#000000"; // black

      case 7:
        return "#7051A7"; //purple

      case 8:
        return "#FD8D3C"; //orange

      case 9:
        return "#1B9E77"; //dark teal
    }

  return "auto";
}

//static
size_t CPlotColors::getNumCopasiColors()
{
  return 10;
}

//QColor curveColours[6] = {QColor(255, 0, 0), QColor(0, 0, 255), QColor(0, 230, 0), QColor(0, 190, 240), QColor(240, 0, 255), QColor(240, 200, 0)} ; //TODO
