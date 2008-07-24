// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tex/CMathMLToTeX.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: pwilly $
//   $Date: 2008/07/24 10:56:50 $
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

    // mtr
    static void mtrNode(QString &text, QString &allignment);

    // mtd
    static void mtdNode(QString &text);

    // frac
    static void mfracNode(QString &text);

    // row
    static void mrowNode(QString &text);

    // fence
    static void mfencedNode(QString &text);

    // identifier, eg. variable, constant, function.
    static void miNode(QString &text);

    // operator (eg. '+'), fence (eg. '{'), or separator (eg. ',')
    static void moNode(QString &text);

    // sub
    static void msubNode(QString &text);
  };

#endif
