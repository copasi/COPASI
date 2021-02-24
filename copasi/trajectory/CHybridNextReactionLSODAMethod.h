// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
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

/**
 *   CHybridNextReactionLSODAMethod
 *
 *   First approach to an hybrid algorithm. Gibson's Next Reaction method is
 *   combined with the LSODA numerical integrator.
 *
 *   File name: CHybridNextReactionLSODAMethod.h
 *   Author:
 *   Email:
 *
 *   Last change: 08, May 2006
 *
 *   (C) European Media Lab 2003.
 */
#ifndef COPASI_CHybridNextReactionLSODAMethod
#define COPASI_CHybridNextReactionLSODAMethod

#include "copasi/trajectory/CHybridMethod.h"
#include "copasi/trajectory/CLsodaMethod.h"

class CHybridNextReactionLSODAMethod : public CHybridMethod
{
  class LSODA : public CLsodaMethod
  {
  public:
    LSODA(const CHybridNextReactionLSODAMethod * pParent);
    LSODA(const LSODA & src, const CHybridNextReactionLSODAMethod * pParent);

    C_FLOAT64 * getTime()
    {
      return mpContainerStateTime;
    }

  protected:
    virtual void evalF(const C_FLOAT64 * t, const C_FLOAT64 * y, C_FLOAT64 * ydot);
  };

private:
  /**
   * Constructor.
   */
  CHybridNextReactionLSODAMethod();

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
  CHybridNextReactionLSODAMethod(const CDataContainer * pParent,
                                 const CTaskEnum::Method & methodType = CTaskEnum::Method::hybridLSODA,
                                 const CTaskEnum::Task & taskType = CTaskEnum::Task::timeCourse);

  /**
   * Copy constructor.
   * @param const CHybridNextReactionRKMethod & src
   * @param const CDataContainer * pParent
   */
  CHybridNextReactionLSODAMethod(const CHybridNextReactionLSODAMethod & src,
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

  /**
   * Inform the trajectory method that the state has changed outside
   * its control
   * @param const CMath::StateChange & change
   */
  virtual void stateChange(const CMath::StateChange & change);

  void evalF(C_FLOAT64 * ydot);

private:
  LSODA mLSODA;
};

#endif // COPASI_CHybridNextReactionLSODAMethod
