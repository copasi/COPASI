// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/CPraxis.h,v $
//   $Revision: 1.4 $
//   $Name:  $
//   $Author: jdada $
//   $Date: 2007/12/11 13:19:31 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CPraxis
#define COPASI_CPraxis

#include "copasi.h"

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

C_FLOAT64 praxis_(C_FLOAT64 *t0,
                  C_FLOAT64 *machep,
                  C_FLOAT64 *h0,
                  C_INT *n,
                  C_INT *prin,
                  C_FLOAT64 *x,
                  FPraxis *f, // Functor for function under investigation
                  C_FLOAT64 *fmin);

#endif // COAPSI_CPraxis
