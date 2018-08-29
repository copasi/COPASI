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

#ifndef COPASI_CTruncatedNewton
#define COPASI_CTruncatedNewton

#include <limits>

// declare COptLog
class COptLog;

class FTruncatedNewton
{
public:
  virtual ~FTruncatedNewton() {};

  virtual C_INT operator()(C_INT * C_UNUSED(n), C_FLOAT64 * C_UNUSED(value),
                           C_FLOAT64 * C_UNUSED(value1), C_FLOAT64 * C_UNUSED(value2))
  {return std::numeric_limits<C_INT>::quiet_NaN();}
};

template <class CType> class FTruncatedNewtonTemplate : public FTruncatedNewton
{
private:
  C_INT(CType::*mMethod)(C_INT *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *);  // pointer to member function
  CType * mpType;                                            // pointer to object

public:

  // constructor - takes pointer to an object and pointer to a member and stores
  // them in two private variables
  FTruncatedNewtonTemplate(CType * pType,
                           C_INT(CType::*method)(C_INT *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *))
  {
    mpType = pType;
    mMethod = method;
  };

  virtual ~FTruncatedNewtonTemplate() {};

  // override operator "()"
  virtual C_INT operator()(C_INT * n, C_FLOAT64 * value, C_FLOAT64 * value1, C_FLOAT64 * value2)
  {return (*mpType.*mMethod)(n, value, value1, value2);}    ;  // execute member function
};

union subscr_
{
  struct
  {
    C_INT lgv, lz1, lzk, lv, lsk, lyk, ldiagb, lsr, lyr, loldg, lhg,
          lhyk, lpk, lemat, lwtest;
  }
  _1;
  struct
  {
    C_INT lgv, lz1, lzk, lv, lsk, lyk, ldiagb, lsr, lyr, lhyr, lhg,
          lhyk, lpk, lemat, lwtest;
  }
  _2;
  struct
  {
    C_INT lsub[14], lwtest;
  }
  _3;
};

class CTruncatedNewton
{

public:

  CTruncatedNewton();
  ~CTruncatedNewton();

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
            C_INT *,
            C_INT *,
            COptLog *);

  int tn_(C_INT *,
          C_INT *,
          C_FLOAT64 *,
          C_FLOAT64 *,
          C_FLOAT64 *,
          C_FLOAT64 *,
          C_INT *,
          FTruncatedNewton *,
          C_INT *,
          COptLog *);

  int getptc_(C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_INT *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_INT *, C_INT *);

  int linder_(C_INT *, FTruncatedNewton *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_INT *, C_INT *, C_FLOAT64 *, C_INT *,
              C_INT *, COptLog *);

  int gtims_(C_FLOAT64 *v, C_FLOAT64 *gv, C_INT *n,
             C_FLOAT64 *x, C_FLOAT64 *g, C_FLOAT64 *w, C_INT * /* lw */, FTruncatedNewton *sfun,
             C_INT *first, C_FLOAT64 *delta, C_FLOAT64 *accrcy, C_FLOAT64 *
             xnorm);

  int msolve_(C_FLOAT64 *,
              C_FLOAT64 *, C_INT *, C_FLOAT64 *, C_INT *, C_INT *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_INT *, C_INT *);

  int initpc_(C_FLOAT64 *, C_FLOAT64 *, C_INT *,
              C_FLOAT64 *, C_INT *, C_INT *, C_INT *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_INT *);

  int setucr_(C_FLOAT64 *, C_INT *, C_INT *,
              C_INT *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, FTruncatedNewton *, C_FLOAT64 *, C_FLOAT64 *);

  int setpar_(C_INT *);

  int modlnp_(C_INT *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_INT *, C_FLOAT64 *,
              C_INT *, C_INT *, C_INT *, C_INT *, C_INT *, C_INT *,
              C_INT *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_INT *,
              FTruncatedNewton *, C_INT *, C_INT *, C_FLOAT64 *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, COptLog *);

  int lmqnbc_(C_INT *, C_INT *, C_FLOAT64 *,
              C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_INT *, FTruncatedNewton *,
              C_FLOAT64 *, C_FLOAT64 *, C_INT *, C_INT *, C_INT *,
              C_INT *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, COptLog *);

  int lmqn_(C_INT *, C_INT *, C_FLOAT64 *,
            C_FLOAT64 *, C_FLOAT64 *, C_FLOAT64 *, C_INT *, FTruncatedNewton *,
            C_INT *, C_INT *, C_INT *, C_FLOAT64 *, C_FLOAT64 *,
            C_FLOAT64 *, C_FLOAT64 *, COptLog *);

private:
  subscr_ * mpsubscr_;
};

#endif // COAPSI_CTruncatedNewton
