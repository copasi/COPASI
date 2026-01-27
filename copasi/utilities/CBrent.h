// Copyright (C) 2019 - 2026 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2014 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CBrent
#define COPASI_CBrent

#include <functional>
class CBrent
{
public:
  typedef std::function< double(const double &) > Eval;

  /**
   * Brent root finding method.
   * @param double left
   * @param double right
   * @param Eval & function
   * @param double * pRoot
   * @param double * pRootValue
   * @param double tolerance
   * @return bool success
   */
  static bool findRoot(double left,
                       double right,
                       Eval & function,
                       double * pRoot,
                       double * pRootValue,
                       double tolerance);

  /**
   * Brent root finding method.
   * @param double left
   * @param double right
   * @param Eval & function
   * @param double * pLeftRoot
   * @param double * pLeftRootValue
   * @param double * pRightRoot
   * @param double * pRightRootValue
   * @param double tolerance
   * @return bool success
   */
  static bool findRootInterval(double left,
                               double right,
                               Eval & function,
                               double * pLeftRoot,
                               double * pLeftRootValue,
                               double * pRightRoot,
                               double * pRightRootValue,
                               double tolerance);

  /**
   * Brent minimum finding method.
   * @param double left
   * @param double right
   * @param Eval & function
   * @param double * pMin
   * @param double * pMinValue
   * @param double tolerance
   * @param int maxIterations
   * @return bool success
   */
  static bool findMinimum(double left,
                          double right,
                          Eval & function,
                          double * pMin,
                          double * pMinValue,
                          double tolerance,
                          int maxIterations);
};

#endif // COPASI_CBrent
