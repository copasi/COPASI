// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

%{

#include "trajectory/CTrajectoryMethod.h"

%}

%newobject CTrajectoryMethod::createTrajectoryMethod(CCopasiMethod::SubType subType = CCopasiMethod::deterministic,CTrajectoryProblem * pProblem = NULL);


class CTrajectoryMethod : public CCopasiMethod
{
  public:
    static CTrajectoryMethod *
    createTrajectoryMethod(CCopasiMethod::SubType subType
                           = CCopasiMethod::deterministic,
                           CTrajectoryProblem * pProblem = NULL);

    /**
     * Copy constructor.
     * @param "const CTrajectoryMethod &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CTrajectoryMethod(const CTrajectoryMethod & src,
                      const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    ~CTrajectoryMethod();


};


