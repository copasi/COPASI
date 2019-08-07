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

// Copyright (C) 2003 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *   CHybridNextReactionRKMethod
 *
 *   First approach to an hybrid algorithm. Gibson's Next Reaction method is
 *   combined with a RungeKutta numerical integrator.
 *
 *   File name: CHybridNextReactionRKMethod.h
 *   Author: Juergen Pahle
 *   Email: juergen.pahle@eml.villa-bosch.de
 *
 *   Last change: 21, January 2003
 *
 *   (C) European Media Lab 2003.
 */
#ifndef COPASI_CHybridNextReactionRKMethod
#define COPASI_CHybridNextReactionRKMethod

#include "copasi/trajectory/CHybridMethod.h"

class CHybridNextReactionRKMethod : public CHybridMethod
{
private:
  /**
   * Constructor.
   */
  CHybridNextReactionRKMethod();

  /**
   * Intialize the method parameter
   */
  void initializeParameter();

public:
  /**
   * Specific constructor
   * @param const CDataContainer * pParent
   * @param const CTaskEnum::Method & methodType (default: hybrid)
   * @param const CTaskEnum::Task & taskType (default: timeCourse)
   */
  CHybridNextReactionRKMethod(const CDataContainer * pParent,
                              const CTaskEnum::Method & methodType = CTaskEnum::Method::hybrid,
                              const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param const CHybridNextReactionRKMethod & src
   * @param const CDataContainer * pParent
   */
  CHybridNextReactionRKMethod(const CHybridMethod & src,
                              const CDataContainer * pParent);

public:
  /**
   *  This instructs the method to prepare for integration
   */
  virtual void start();

  /**
   *   Integrates the deterministic reactions of the system over the
   *   specified time interval.
   *
   *   @param ds A C_FLOAT64 specifying the stepsize.
   */
  virtual void integrateDeterministicPart(C_FLOAT64 ds);

protected:
  /**
   *   Does one 4th order RungeKutta step to integrate the system
   *   numerically.
   *
   *   @param dt A C_FLOAT64 specifying the stepsize
   *   @param result A reference to a vector, into which the result, that is
   *                 the increment vector, will be written
   */
  void rungeKutta(C_FLOAT64 dt);

private:
  /**
   *   Stepsize for the rungeKutta steps of the numerical integrator.
   */
  C_FLOAT64 mStepsize;

  CVector< C_FLOAT64 > temp;
  CVector< C_FLOAT64 > k1;
  CVector< C_FLOAT64 > k2;
  CVector< C_FLOAT64 > k3;
  CVector< C_FLOAT64 > k4;
};

#endif // COPASI_CHybridNextReactionRKMethod
