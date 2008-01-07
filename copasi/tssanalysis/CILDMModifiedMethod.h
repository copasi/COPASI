// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/tssanalysis/CILDMModifiedMethod.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: isurovts $
//   $Date: 2008/01/07 12:34:56 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CILDModMethod
#define COPASI_CILDModMethod

#include <sstream>
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"

#include "CTSSAMethod.h"

//#include "odepack++/CLSODA.h"

//#include "utilities/CMatrix.h"
//#include "utilities/CAnnotatedMatrix.h"

class CModel;
class CState;
//class CLSODA;

class CILDMModifiedMethod : public CTSSAMethod
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
    CILDMModifiedMethod(const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor.
     * @param "const CILDMMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CILDMModifiedMethod(const CILDMModifiedMethod & src,
                        const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CILDMModifiedMethod();

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

    void deuflhard_metab(C_INT & slow, C_INT & info);

    void newton_new(C_INT *index_metab, C_INT & slow, C_INT & info);

    void newton_for_timestep(C_INT metabolite_number, C_FLOAT64 &y_consistent, C_INT & info);

    void evalsort(C_FLOAT64 * reval, C_INT * index, const C_INT & dim_x);
  };
#endif // COPASI_CILDMMethod
