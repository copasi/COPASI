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

#ifndef ODEPACK_CLSODAR
#define ODEPACK_CLSODAR

#include "copasi/odepack++/CInternalSolver.h"

class PJAC;
class SLVS;

class CLSODAR : public CInternalSolver
{
public:
  CLSODAR();
  ~CLSODAR();

  C_INT operator()(evalF f,        //  1. evaluate f
                   C_INT *neq,    //  2. number of equations
                   double *y,     //  3. y
                   double *t,     //  4. time
                   double *tout,  //  5. end time
                   C_INT *itol,   //  6. 1 common, 2 atol array, 3 rtol array, 4 both array
                   double *rtol,  //  7. relative tolerance
                   double *atol,  //  8. absolute tolerance
                   C_INT *itask,  //  9. 1
                   C_INT *istate, // 10. status
                   C_INT *iopt,   // 11. 0
                   double *rwork, // 12. work array 22 + neq * max(16, neq + 9)
                   C_INT *lrw,    // 13. size of rwork
                   C_INT *iwork,  // 14. work array 20 + neq
                   C_INT *liw,    // 15. size of iwork
                   evalJ jac,     // 16. evaluate j
                   C_INT *jt,     // 17. type of j evaluation 2 internal full matrix
                   evalG g,       // 18. evaluate constraint functions
                   C_INT *ng,     // 19. number of constraint functions g(i)
                   C_INT *jroot); // 20. integer array of length NG for output of root information

private:
  PJAC * mpPJAC;
  SLVS * mpSLVS;

  static const C_INT mxstp0;
  static const C_INT mxhnl0;
  static const C_INT mord[2];
};

#endif // ODEPACK_CLSODAR
