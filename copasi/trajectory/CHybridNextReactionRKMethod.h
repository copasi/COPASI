/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/trajectory/CHybridNextReactionRKMethod.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: jpahle $ 
   $Date: 2004/12/17 12:31:54 $
   End CVS Header */

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

#include "CHybridMethod.h"

class CHybridNextReactionRKMethod : public CHybridMethod
  {
    friend CHybridMethod *
    CHybridMethod::createHybridMethod(CTrajectoryProblem *pProblem);

  private:
    // Lifecycle methods
    /**
     *   Default constructor
     */
    CHybridNextReactionRKMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     *   Do one iteration of the simulation
     *   @return Current simulation time or -1 in case of an error
     */
    C_FLOAT64 doSingleStep(C_FLOAT64 time, C_FLOAT64 endTime);
  };

#endif // COPASI_CHybridNextReactionRKMethod
