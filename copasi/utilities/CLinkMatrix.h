// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef COPASI_CLinkMatrix
#define COPASI_CLinkMatrix

#include "copasi/utilities/CVector.h"
#include "copasi/utilities/CMatrix.h"

class CLinkMatrix
{
public:
  /**
   * Default constructor
   */
  CLinkMatrix();

  /**
   * Destructor
   */
  virtual ~CLinkMatrix();

  /**
   * Build the link matrix for the given matrix
   * @param const CMatrix< C_FLOAT64 > & matrix
   * @return bool success
   */
  bool build(const CMatrix< C_FLOAT64 > & matrix);

  /**
   * Retrieve the core components of the link matrix
   * @return const CMatrix< C_FLOAT64 > & linkZero
   */
  const CMatrix< C_FLOAT64 > & getLinkZero() const;

  /**
   * Retrieve the pivot vector used to create the link matrix
   * @return const CVector< size_t > & rowPivots
   */
  const CVector< size_t > & getRowPivots() const;

  /**
   * Retrieve the number of linear independent rows of the input matrix
   * @return const size_t & numIndependent
   */
  const size_t & getNumIndependent() const;

  /**
   * Retrieve the number of linear dependent rows of the input matrix
   * @return const size_t & numDependent
   */
  const size_t & getNumDependent() const;

  /**
   * Apply the row pivot
   * @param CMatrix< C_FLOAT64 > & matrix
   * @return bool success
   */
  bool applyRowPivot(CMatrix< C_FLOAT64 > & matrix) const;

  /**
   * Apply the row pivot
   * @param CVectorCore< C_FLOAT64 > & vector
   * @return bool success
   */
  bool applyRowPivot(CVectorCore< C_FLOAT64 > & vector) const;

private:
  CMatrix< C_FLOAT64 > mL0;

  CVector< size_t > mRowPivots;

  size_t mIndependent;
};

#endif // COPASI_CLinkMatrix
