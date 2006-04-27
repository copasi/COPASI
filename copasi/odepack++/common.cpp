/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/odepack++/common.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:29:35 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "common.h"

PJAC::PJAC(): mpMethod(NULL) {}

PJAC::PJAC(C_INT (*pMethod)(C_INT *neq, double *y, double *yh,
                            C_INT *nyh, double *ewt, double *ftem,
                            double *savf, double *wm, C_INT *iwm,
                            evalF f, evalJ jac)) : mpMethod(pMethod) {}

PJAC::~PJAC() {}

C_INT PJAC::operator() (C_INT *neq, double *y, double *yh,
                        C_INT *nyh, double *ewt, double *ftem,
                        double *savf, double *wm, C_INT *iwm,
                        evalF f, evalJ jac)
{return (*mpMethod)(neq, y, yh, nyh, ewt, ftem, savf, wm, iwm, f, jac);}

SLVS::SLVS() : mpMethod(NULL) {}

SLVS::SLVS(C_INT (*pMethod)(double *wm, C_INT *iwm, double *x, double *tem)):
    mpMethod(pMethod)
{}

SLVS::~SLVS() {}

C_INT SLVS::operator() (double *wm, C_INT *iwm, double *x,
                        double *tem)
{return (*mpMethod)(wm, iwm, x, tem);}
