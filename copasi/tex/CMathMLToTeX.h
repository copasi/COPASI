// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tex/CMathMLToTeX.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/07/25 08:09:00 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// written by pwilly on 07.07.08

#ifndef CMATHMLTOTEX_H
#define CMATHMLTOTEX_H

#include "copasi.h"

class CMathMLToTeX
  {
  public:
    CMathMLToTeX(){};
    ~CMathMLToTeX(){};

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
