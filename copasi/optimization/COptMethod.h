// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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
#include "COptLog.h"

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

  /**
   * Define the current verbosity for the log
   */
  unsigned C_INT32 mLogVerbosity;

  /**
  * The Log created during parameter estimation
  */
  COptLog mMethodLog;

  /**
   * boolean indicating whether additional parameters ought to be available
   */
  bool mEnableAdditionalParameters;

  // Operations
private:
  /**
   * Default constructor.
   */
  COptMethod();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType
   * @param const CTaskEnum::Task & taskType (default: optimization)
   */
  COptMethod(const CDataContainer * pParent,
             const CTaskEnum::Method & methodType,
             const CTaskEnum::Task & taskType = CTaskEnum::Task::optimization);

  /**
   * Copy constructor
   * @param const COptMethod & src
   * @param const CDataContainer * pParent (default: NULL)
   */
  COptMethod(const COptMethod & src,
             const CDataContainer * pParent);

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
   * Set the problem to be optimized
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

  /**
   * Returns the maximum verbosity (0 - Basic; 1 - Iterative; 2 - Detailed) at which the method can log.
   */
  virtual unsigned C_INT32 getMaxLogVerbosity() const;

  /**
   * Retrieve the log of the solution
   */
  const COptLog &getMethodLog() const;

protected:
  /**
   * Cleanup arrays and pointers.
   * @return bool success
   */
  virtual bool cleanup();
};

#endif  // COPASI_COptMethod
