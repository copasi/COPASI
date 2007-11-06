// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CPraxis.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: jdada $
//   $Date: 2007/11/06 15:01:39 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CPraxis
#define COPASI_CPraxis

#include "copasi.h"

#include "f2c.h"

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

doublereal praxis_(doublereal *t0,
                   doublereal *machep,
                   doublereal *h0,
                   integer *n,
                   integer *prin,
                   doublereal *x,
                   FPraxis *f, // Functor for function under investigation
                   doublereal *fmin);

//these external C functions (normally included in f2ch.add header file)
//are required for the compilation of praxis
extern "C"
  {

    extern integer pow_ii(integer *, integer *);
    extern integer s_wsfe(cilist *);
    extern integer do_fio(integer *, char *, ftnlen);
    extern integer e_wsfe(void);
    double d_lg10(doublereal *);
  }

#endif // COAPSI_CPraxis
