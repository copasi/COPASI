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

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

//
// This C++ code is based on an f2c conversion of the Fortran
// library ODEPACK available at: http://www.netlib.org/odepack/

#include "copasi/copasi.h"

#include "common.h"

PJAC::PJAC(): mpMethod(NULL) {}

PJAC::PJAC(C_INT(*pMethod)(C_INT *neq, double *y, double *yh,
                           C_INT *nyh, double *ewt, double *ftem,
                           double *savf, double *wm, C_INT *iwm,
                           evalF f, evalJ jac)) : mpMethod(pMethod) {}

PJAC::~PJAC() {}

C_INT PJAC::operator()(C_INT *neq, double *y, double *yh,
                       C_INT *nyh, double *ewt, double *ftem,
                       double *savf, double *wm, C_INT *iwm,
                       evalF f, evalJ jac)
{return (*mpMethod)(neq, y, yh, nyh, ewt, ftem, savf, wm, iwm, f, jac);}

SLVS::SLVS() : mpMethod(NULL) {}

SLVS::SLVS(C_INT(*pMethod)(double *wm, C_INT *iwm, double *x, double *tem)):
  mpMethod(pMethod)
{}

SLVS::~SLVS() {}

C_INT SLVS::operator()(double *wm, C_INT *iwm, double *x,
                       double *tem)
{return (*mpMethod)(wm, iwm, x, tem);}
