// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CILDMMethod.h,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: isurovts $
//   $Date: 2007/12/21 11:43:59 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CILDMMethod
#define COPASI_CILDMMethod

#include <sstream>
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"

#include "CTSSAMethod.h"

//#include "odepack++/CLSODA.h"

//#include "utilities/CMatrix.h"
//#include "utilities/CAnnotatedMatrix.h"

class CModel;
class CState;

class CILDMMethod : public CTSSAMethod
  {
    friend CTSSAMethod *
    CTSSAMethod::createTSSAMethod(CCopasiMethod::SubType subType,
                                  CTSSAProblem * pProblem);
    // Operations
  private:
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CILDMMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor.
     * @param "const CILDMMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CILDMMethod(const CILDMMethod & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CILDMMethod();

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
     *
     **/
    void newton(C_FLOAT64 *ys, C_INT & slow, C_INT & info);

    /**
       *
       **/

    void transformation_norm(C_INT & slow, C_INT & info);

    void deuflhard(C_INT & slow, C_INT & info);
  };
#endif // COPASI_CILDMMethod
