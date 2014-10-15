// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2002 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  File name: COptMethod.h
 *
 *  Programmer: Yongqun He
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the interface (.h file) of the COptMethod class.
 *           It contains the designed abstract interaction between a simulation
 *           subsystem and optimization algorithms. This base class defines
 *           methods by which the simulation subsystem accesses several
 *           optimization algorithms.
 *  Note: This is an abstract class

 ****** Modified by Liang Xu
 */

#ifndef COPASI_COptMethod
#define COPASI_COptMethod

#include <string>

#include "utilities/CCopasiMethod.h"

class COptProblem;
class COptItem;
class COptTask;
template < class CType > class CVector;

// YOHE: this is an abstract class that contains many virtual functions
// without definitions
//
/** @dia:pos 36.4,4.15 */
class COptMethod : public CCopasiMethod
{
public:
  //    static const std::string TypeName[];

  // Attributes
public:

  //data member
protected:
  /** @dia:route 0,2; h,36.4,4.15,33.95,4.15,23.0576 */
  COptProblem * mpOptProblem;        // pointer to remote problem

  COptTask * mpParentTask;

  const bool mBounds;            // True if method accepts bounds on the parameters

  /**
   * A vector of pointers to the update methods for the optimization parameters
   */
  CVectorCore< C_FLOAT64 * > mContainerVariables;

  /**
   * A vector of pointers to the optimization parameter
   */
  const std::vector< COptItem * > * mpOptItem;

  /**
   * A vector of pointers to the functional constraints
   */
  const std::vector< COptItem * > * mpOptContraints;

  // Operations
private:
  /**
   * Default constructor.
   */
  COptMethod();

public:
  /**
   * Specific constructor
   * @param const CCopasiContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethod(const CCopasiContainer * pParent,
             const CTaskEnum::Method & methodType,
             const CTaskEnum::Task & taskType = CTaskEnum::optimization);

  /**
   * Copy constructor
   * @param const COptMethod & src
   * @param const CCopasiContainer * pParent (default: NULL)
   */
  COptMethod(const COptMethod & src,
             const CCopasiContainer * pParent = NULL);

  /**
   * Destructor
   */
  virtual ~COptMethod();

  /**
   * Execute the optimization algorithm calling simulation routine
   * when needed. It is noted that this procedure can give feedback
   * of its progress by the callback function set with SetCallback.
   * @ return success;
   */
  virtual bool optimise();

  /**
   * Returns True if this method is capable of handling adjustable parameter
   * boundary constraints, False otherwise
   */
  bool isBounded(void);

  /**
   * Set the problem to be optmised
   * @param "COptProblem *" problem
   */
  void setProblem(COptProblem * problem);

  /**
   * Initialize arrays and pointer.
   * @return bool success
   */
  virtual bool initialize();

  /**
   * Check if the method is suitable for this problem
   * @return bool suitability of the method
   */
  virtual bool isValidProblem(const CCopasiProblem * pProblem);

protected:
  /**
   * Cleanup arrays and pointers.
   * @return bool success
   */
  virtual bool cleanup();
};

#endif  // COPASI_COptMethod
