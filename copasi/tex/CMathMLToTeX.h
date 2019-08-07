// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// written by pwilly on 07.07.08

#ifndef CMATHMLTOTEX_H
#define CMATHMLTOTEX_H

#include "copasi/copasi.h"

class CMathMLToTeX
{
public:
  CMathMLToTeX() {};
  ~CMathMLToTeX() {};

  // replace other operators (eg. .)
  static void replaceOtherOperators(QString &text);

  // replace logic operators (eg. <=, <, >=, >, and, or)
  static void replaceLogicOperators(QString &text);

  // replace mathematical operators (eg. inf, log)
  static void replaceMathOperators(QString &text);

  // replace trigonometrical operators (eg. inf, log)
  static void replaceTrigoOperators(QString &text);

  // convert to TeX
  static void convert(QString &text);

  // normal
  static void mNode(QString &text);

  // table
  static void mtableNode(QString &text);
};

#endif
