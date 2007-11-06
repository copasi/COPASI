// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CTruncatedNewton.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: jdada $
//   $Date: 2007/11/06 15:01:39 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CTruncatedNewton
#define COPASI_CTruncatedNewton

#include "copasi.h"

#include "f2c.h"
#include "../blaswrap.h"

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

int tnbc_(integer *,
          integer *,
          doublereal *,
          doublereal *,
          doublereal *,
          doublereal *,
          integer *,
          FTruncatedNewton *, // Functor for function under investigation
          doublereal *,
          doublereal *,
          integer *);

int tn_(integer *,
        integer *,
        doublereal *,
        doublereal *,
        doublereal *,
        doublereal *,
        integer *,
        FTruncatedNewton *);

//these external C functions (normally included in f2ch.add header file)
//are required for the compilation of praxis
extern "C"
  {
    extern double pow_dd(doublereal *, doublereal *);
    extern integer pow_ii(integer *, integer *);
    extern integer s_wsfe(cilist *);
    extern integer do_fio(integer *, char *, ftnlen);
    extern integer e_wsfe(void);
    double d_lg10(doublereal *);
  }

#endif // COAPSI_CTruncatedNewton
