// Copyright (C) 2020 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_CLeastSquareSolution
#define COPASI_CLeastSquareSolution

#include "copasi/core/CVector.h"
#include "copasi/core/CMatrix.h"

class CLeastSquareSolution
{
public:
  struct ResultInfo
  {
    size_t rank;
    C_FLOAT64 relativeError;
    C_FLOAT64 absoluteError;
  };

  /**
   * Computes the minimum-norm solution to a linear least squares problem:
   *      minimize || aMatrix * xVector - bVector ||
   * @param const CMatrix< C_FLOAT64 > & aMatrix
   * @param const CVectorCore< C_FLOAT64 > & bVector
   * @param CVector< C_FLOAT64 > & xVector
   * @return ResultInfo info
   */
  static size_t solve(const CMatrix< C_FLOAT64 > & aMatrix,
                      const CVectorCore< C_FLOAT64 > & bVector,
                      CVector< C_FLOAT64 > & xVector);

  /**
   * Computes the minimum-norm solution to a linear least squares problem:
   *      minimize || aMatrix * xVector - bVector ||
   * @param const CMatrix< C_FLOAT64 > & aMatrix
   * @param const CVectorCore< C_FLOAT64 > & bVector
   * @param const CVectorCore< C_FLOAT64 > & absoluteTolerances
   * @param const CVector< C_FLOAT64 * > & compartmentVolumes
   * @param const C_FLOAT64 & quantity2NumberFactor
   * @param CVector< C_FLOAT64 > & xVector
   * @return ResultInfo info
   */
  static ResultInfo solve(const CMatrix< C_FLOAT64 > & aMatrix,
                          const CVectorCore< C_FLOAT64 > & bVector,
                          const CVectorCore< C_FLOAT64 > & absoluteTolerances,
                          const CVector< C_FLOAT64 * > & compartmentVolumes,
                          const C_FLOAT64 & quantity2NumberFactor,
                          CVector< C_FLOAT64 > & xVector);
};

#endif // COPASI_CLeastSquareSolution
