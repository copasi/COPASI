// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CPraxis.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: jdada $
//   $Date: 2008/01/23 11:46:52 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CPraxis
#define COPASI_CPraxis

#include <limits>

class FPraxis
  {
  public:
    virtual ~FPraxis(){};

    virtual const C_FLOAT64 operator()(C_FLOAT64 * C_UNUSED(value), C_INT * C_UNUSED(n))
    {return std::numeric_limits<C_FLOAT64>::quiet_NaN();}
  };

template <class CType> class FPraxisTemplate : public FPraxis
  {
  private:
    const C_FLOAT64 (CType::*mMethod)(C_FLOAT64 *, C_INT *); // pointer to member function
    CType * mpType;                                            // pointer to object

  public:

    // constructor - takes pointer to an object and pointer to a member and stores
    // them in two private variables
    FPraxisTemplate(CType * pType,
                    const C_FLOAT64 (CType::*method)(C_FLOAT64 *, C_INT*))
    {
      mpType = pType;
      mMethod = method;
    };

    virtual ~FPraxisTemplate(){};

    // override operator "()"
    virtual const C_FLOAT64 operator()(C_FLOAT64 *value, C_INT *n)
    {return (*mpType.*mMethod)(value, n);}    ;              // execute member function
  };

class CPraxis
  {
  public:

    struct Global
      {
        C_FLOAT64 fx, ldt, dmin__;
        C_INT nf, nl;
      };

    struct Q
      {
        C_FLOAT64 v[10000] /* was [100][100] */, q0[100], q1[100], qa, qb, qc, qd0,
        qd1, qf1;
      };

    CPraxis();
    ~CPraxis();

  private:

    Global global_1;
    Q q_1;

  public:

    C_FLOAT64 praxis_(C_FLOAT64 *t0,
                      C_FLOAT64 *machep,
                      C_FLOAT64 *h0,
                      C_INT *n,
                      C_INT *prin,
                      C_FLOAT64 *x,
                      FPraxis *f, // Functor for function under investigation
                      C_FLOAT64 *fmin);

    int min_(C_INT *, C_INT *, C_INT *,
             C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, bool *, FPraxis *f,
             C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *);
    C_FLOAT64 flin_(C_INT *, C_INT *, C_FLOAT64 *, FPraxis *, C_FLOAT64 *, C_INT *);
    int quad_(C_INT *, FPraxis *f, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *);
    int print_(C_INT *n, C_FLOAT64 *x, C_INT *prin, C_FLOAT64 *fmin);
    int minfit_(C_INT *, C_INT *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *);
  };

#endif // COAPSI_CPraxis
