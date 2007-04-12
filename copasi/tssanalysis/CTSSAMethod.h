// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CTSSAMethod.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2007/04/12 12:47:49 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CTSSAMethod class.
 *  This class describes the interface to all time scale separation analysis methods.
 *  The variaous method like ILDM or CSP have to be derived from
 *  this class.
 *
 */

#ifndef COPASI_CTSSAMethod
#define COPASI_CTSSAMethod

#include <string>

#include "utilities/CCopasiMethod.h"
#include "utilities/CVector.h"

class CTSSAProblem;
class CState;

class CTSSAMethod : public CCopasiMethod
  {
  protected:
    /**
     *  A pointer to the current state. This is set from outside
     *  with the setState() method and never changed anywhere else.
     *  It´s used to report the results
     *  to the calling TSSATask
     */
    CState * mpCurrentState;

    /**
     *  A pointer to the time scale separation analysis problem.
     */
    CTSSAProblem * mpProblem;

    // Operations
  private:
    /**
     * Default constructor.
     */
    CTSSAMethod();

  protected:
    /**
     * Default constructor.
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTSSAMethod(const CCopasiMethod::SubType & subType,
                const CCopasiContainer * pParent = NULL);

  public:

    /**
     * Create a time scale separation analysis method for a special problem.
     * Note: the returned object has to be released after use with delete
     * a problem is also passed so that the method has a chance to choose an
     * appropriate simulation method.
     */
    static CTSSAMethod *
    createTSSAMethod(CCopasiMethod::SubType subType
                     = CCopasiMethod::unset,
                     CTSSAProblem * pProblem = NULL);

    /**
     * Copy constructor.
     * @param "const CTSSAMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTSSAMethod(const CTSSAMethod & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CTSSAMethod();

    /**
     *  Set a pointer to the current state.
     *  This method is used by CTSSATask::process()
     *  The results of the simulation are passed via this CState variable
     *  @param "CState *" currentState
     */
    void setCurrentState(CState * currentState);

    /**
     *  Set a pointer to the problem.
     *  This method is used by CTSSA
     *  @param "CTSSAProblem *" problem
     */
    void setProblem(CTSSAProblem * problem);

    /**
     *  This instructs the method to calculate a time step of deltaT
     *  starting with the current state, i.e., the result of the previous
     *  step.
     *  The new state (after deltaT) is expected in the current state.
     *  The return value is the actual timestep taken.
     *  @param "const double &" deltaT
     */
    virtual void step(const double & deltaT);

    /**
     *  This instructs the method to prepare for integration
     *  starting with the initialState given.
     *  @param "const CState *" initialState
     */
    virtual void start(const CState * initialState);

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);
  };

#endif // COPASI_CTSSAMethod
