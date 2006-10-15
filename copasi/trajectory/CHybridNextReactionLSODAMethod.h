/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CHybridNextReactionLSODAMethod.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $
   $Date: 2006/10/15 08:31:13 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
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

#include "trajectory/CHybridMethodLSODA.h"

class CHybridNextReactionLSODAMethod : public CHybridMethodLSODA
  {
    friend CHybridMethodLSODA *
    CHybridMethodLSODA::createHybridMethodLSODA(CTrajectoryProblem *pProblem);

  private:
    // Lifecycle methods
    /**
     *   Default constructor
     */
    CHybridNextReactionLSODAMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     *   Do one iteration of the simulation
     *   @return Current simulation time or -1 in case of an error
     */
    C_FLOAT64 doSingleStep(C_FLOAT64 time, C_FLOAT64 endTime);
  };

#endif // COPASI_CHybridNextReactionLSODAMethod
