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

#ifndef CPLOTCOLORS_H
#define CPLOTCOLORS_H

#include <string>

/*
 * Class for handling the colors in plots.
 * Provides the predefined colors in COPASI and other
 * utility functionality
 * This class does not depend on QT and is used in the backend.
 * The colors are mainly handled as hex strings
 */
class CPlotColors
{
public:
  static std::string getCopasiColorStr(size_t index);
  static size_t getNumCopasiColors();
private:
};

#endif // CPLOTCOLORS_H
