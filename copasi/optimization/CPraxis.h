// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CPraxis
#define COPASI_CPraxis

#include <limits>
#include "copasi/copasi.h"

class CRandom;

class FPraxis
{
public:
  virtual ~FPraxis() {};

  virtual const C_FLOAT64 & operator()(C_FLOAT64 * /* value */, C_INT32 & /* n */)
  {
    static C_FLOAT64 NaN = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
    return NaN;
  }
};

template < class CType >
class FPraxisTemplate : public FPraxis
{
private:
  const C_FLOAT64 & (CType::*mMethod)(C_FLOAT64 *, C_INT32 &); // pointer to member function
  CType * mpType;                                              // pointer to object

public:
  // constructor - takes pointer to an object and pointer to a member and stores
  // them in two private variables
  FPraxisTemplate(CType * pType,
                  const C_FLOAT64 & (CType::*method)(C_FLOAT64 *, C_INT32 &))
  {
    mpType = pType;
    mMethod = method;
  };

  virtual ~FPraxisTemplate() {};

  // override operator "()"
  virtual const C_FLOAT64 & operator()(C_FLOAT64 * value, C_INT32 & n)
  {
    return (*mpType.*mMethod)(value, n);
  }; // execute member function
};

class CPraxis
{
public:
  CPraxis();

  ~CPraxis();

  C_FLOAT64 operator()(C_FLOAT64 t0,
                       C_FLOAT64 h0,
                       C_INT32 n,
                       C_INT32 prin,
                       C_FLOAT64 x[],
                       FPraxis * f);

private:
  C_FLOAT64 flin(C_INT32 n,
                 C_INT32 j,
                 C_FLOAT64 l,
                 FPraxis * f,
                 C_FLOAT64 x[],
                 C_INT32 & nf,
                 C_FLOAT64 v[],
                 C_FLOAT64 q0[],
                 C_FLOAT64 q1[],
                 C_FLOAT64 & qd0,
                 C_FLOAT64 & qd1,
                 C_FLOAT64 & qa,
                 C_FLOAT64 & qb,
                 C_FLOAT64 & qc);

  void minfit(C_INT32 n,
              C_FLOAT64 tol,
              C_FLOAT64 a[],
              C_FLOAT64 q[]);

  void minny(C_INT32 n,
             C_INT32 j,
             C_INT32 nits,
             C_FLOAT64 & d2,
             C_FLOAT64 & x1,
             C_FLOAT64 & f1,
             bool fk,
             FPraxis * f,
             C_FLOAT64 x[],
             C_FLOAT64 t,
             C_FLOAT64 h,
             C_FLOAT64 v[],
             C_FLOAT64 q0[],
             C_FLOAT64 q1[],
             C_INT32 & nl,
             C_INT32 & nf,
             C_FLOAT64 dmin,
             C_FLOAT64 ldt,
             C_FLOAT64 & fx,
             C_FLOAT64 & qa,
             C_FLOAT64 & qb,
             C_FLOAT64 & qc,
             C_FLOAT64 & qd0,
             C_FLOAT64 & qd1);

  void prC_INT322(C_INT32 n,
                  C_FLOAT64 x[],
                  C_INT32 prin,
                  C_FLOAT64 fx,
                  C_INT32 nf,
                  C_INT32 nl);

  void quad(C_INT32 n,
            FPraxis * f,
            C_FLOAT64 x[],
            C_FLOAT64 t,
            C_FLOAT64 h,
            C_FLOAT64 v[],
            C_FLOAT64 q0[],
            C_FLOAT64 q1[],
            C_INT32 & nl,
            C_INT32 & nf,
            C_FLOAT64 dmin,
            C_FLOAT64 ldt,
            C_FLOAT64 & fx,
            C_FLOAT64 & qf1,
            C_FLOAT64 & qa,
            C_FLOAT64 & qb,
            C_FLOAT64 & qc,
            C_FLOAT64 & qd0,
            C_FLOAT64 & qd1);

  C_FLOAT64 r8_hypot(C_FLOAT64 x, C_FLOAT64 y);

  C_FLOAT64 r8_uniform_01(C_INT32 & seed);

  void r8mat_prC_INT32(C_INT32 m, C_INT32 n, C_FLOAT64 a[], std::string title);

  void r8mat_prC_INT32_some(C_INT32 m, C_INT32 n, C_FLOAT64 a[], C_INT32 ilo, C_INT32 jlo, C_INT32 ihi, C_INT32 jhi, std::string title);

  void r8mat_transpose_in_place(C_INT32 n, C_FLOAT64 a[]);

  void r8vec_copy(C_INT32 n, C_FLOAT64 a1[], C_FLOAT64 a2[]);

  C_FLOAT64 r8vec_max(C_INT32 n, C_FLOAT64 r8vec[]);

  C_FLOAT64 r8vec_min(C_INT32 n, C_FLOAT64 r8vec[]);

  C_FLOAT64 r8vec_norm(C_INT32 n, C_FLOAT64 a[]);

  void r8vec_prC_INT32(C_INT32 n, C_FLOAT64 a[], std::string title);

  void svsort(C_INT32 n, C_FLOAT64 d[], C_FLOAT64 v[]);

  void timestamp();

private:
  CRandom * mpRandom;
};

#endif // COPASI_CPraxis
