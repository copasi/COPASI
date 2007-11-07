// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CTruncatedNewton.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/11/07 14:09:33 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CTruncatedNewton
#define COPASI_CTruncatedNewton

#include "copasi.h"

#include "copasi/blaswrap.h"

class FTruncatedNewton
  {
  public:
    virtual ~FTruncatedNewton(){};

    virtual C_INT operator()(C_INT * C_UNUSED(n), C_FLOAT64 * C_UNUSED(value),
                             C_FLOAT64 * C_UNUSED(value1), C_FLOAT64 * C_UNUSED(value2))
    {return std::numeric_limits<C_INT>::quiet_NaN();}
  };

template <class CType> class FTruncatedNewtonTemplate : public FTruncatedNewton
  {
  private:
    C_INT (CType::*mMethod)(C_INT *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *); // pointer to member function
    CType * mpType;                                            // pointer to object

  public:

    // constructor - takes pointer to an object and pointer to a member and stores
    // them in two private variables
    FTruncatedNewtonTemplate(CType * pType,
                             C_INT (CType::*method)(C_INT *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *))
    {
      mpType = pType;
      mMethod = method;
    };

    virtual ~FTruncatedNewtonTemplate(){};

    // override operator "()"
    virtual C_INT operator()(C_INT * n, C_FLOAT64 * value, C_FLOAT64 * value1, C_FLOAT64 * value2)
    {return (*mpType.*mMethod)(n, value, value1, value2);}    ;  // execute member function
  };

int tnbc_(C_INT *,
          C_INT *,
          C_FLOAT64 *,
          C_FLOAT64 *,
          C_FLOAT64 *,
          C_FLOAT64 *,
          C_INT *,
          FTruncatedNewton *, // Functor for function under investigation
          C_FLOAT64 *,
          C_FLOAT64 *,
          C_INT *);

int tn_(C_INT *,
        C_INT *,
        C_FLOAT64 *,
        C_FLOAT64 *,
        C_FLOAT64 *,
        C_FLOAT64 *,
        C_INT *,
        FTruncatedNewton *);

#ifdef MUST_BE_REMOVED
//these external C functions (normally included in f2ch.add header file)
//are required for the compilation of praxis
extern "C"
  {
    extern double pow_dd(C_FLOAT64 *, C_FLOAT64 *);
    extern C_INT pow_ii(C_INT *, C_INT *);
    extern C_INT s_wsfe(cilist *);
    extern C_INT do_fio(C_INT *, char *, ftnlen);
    extern C_INT e_wsfe(void);
    double d_lg10(C_FLOAT64 *);
  }
#endif // MUST_BE_REMOVED

#endif // COAPSI_CTruncatedNewton
