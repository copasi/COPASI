// Copyright (C) 2025 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#pragma once

#include "copasi/odepack++/CInternalSolver.h"
#include "copasi/trajectory/CRootFinder.h"

class CRootCheck : public CInternalSolver
{
public:
  CRootCheck() = delete;

  CRootCheck(const CRootCheck & src) = delete;

  CRootCheck(CInternalSolver & solver);

  ~CRootCheck();

  void initialize(const C_FLOAT64 & relativeTolerance, const CVectorCore< const RootMask > & mRootMask);

  C_INT operator()(const C_INT * job,
                   evalG g,
                   C_INT *neq,
                   double *y,
                   double *yh,
                   C_INT *nyh,
                   double *g0,
                   double *g1,
                   double *gx,
                   C_INT *jroot,
                   C_INT *irt);

protected:
  void calculateRootValues(const double & time,
                           CVectorCore< C_FLOAT64 > & rootValues);

  CRootFinder mRootFinder;
  CRootFinder::Eval mEvalRoots;
  const CVectorCore< const RootMask > * mpRootMask;
  C_FLOAT64 mRelativeTolerance;

  struct {
    evalG g;
    C_INT * neq;
    double * y;
    double * yh;
    C_INT * nyh;
  } mData;
};
