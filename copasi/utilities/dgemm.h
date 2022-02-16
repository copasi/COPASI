// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASI_dgemm_h
#define COPASI_dgemm_h

#include "copasi/core/CVector.h"
#include "copasi/core/CMatrix.h"

struct dgemm
{
  typedef CVectorCore< C_FLOAT64 > Vector;
  typedef CMatrix< C_FLOAT64 > Matrix;

  /**
   * Compute C:= alpha A B + beta C
   *
   * @param const C_FLOAT64 & alpha
   * @param const Matrix & A
   * @param const Matrix & B
   * @param const C_FLOAT64 & beta
   * @param Matrix & C
   * @return bool success
   */
  static bool eval(const C_FLOAT64 & alpha, const Matrix & A, const Matrix & B, const C_FLOAT64 & beta, Matrix & C);

  /**
   * Compute C:= alpha A B + beta C
   *
   * @param const C_FLOAT64 & alpha
   * @param const Matrix & A
   * @param const Vector & B
   * @param const C_FLOAT64 & beta
   * @param Vector & C
   * @return bool success
   */
  static bool eval(const C_FLOAT64 & alpha, const Matrix & A, const Vector & B, const C_FLOAT64 & beta, Vector & C);

  /**
   * Compute C:= alpha A B + beta C
   *
   * @param const C_FLOAT64 & alpha
   * @param const Vector & A
   * @param const Matrix & B
   * @param const C_FLOAT64 & beta
   * @param Vector & C
   * @return bool success
   */
  static bool eval(const C_FLOAT64 & alpha, const Vector & A, const Matrix & B, const C_FLOAT64 & beta, Vector & C);

  /**
   * Compute C:= alpha A B + beta C
   *
   * @param const C_FLOAT64 & alpha
   * @param const Vector & A
   * @param const Vector & B
   * @param const C_FLOAT64 & beta
   * @param C_FLOAT64 & C
   * @return bool success
   */
  static bool eval(const C_FLOAT64 & alpha, const Vector & A, const Vector & B, const C_FLOAT64 & beta, C_FLOAT64 & C);

private:
  dgemm();
};

#endif // COAPSI_dgemm_h
