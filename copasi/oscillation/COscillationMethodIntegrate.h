// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/oscillation/COscillationMethodIntegrate.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/11/11 16:47:54 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_COSCINT
#define COPASI_COSCINT

#include "COscillationMethod.h"

class COptProblem;

class COscillationMethodIntegrate : public COscillationMethod
  {
    friend COscillationMethod * COscillationMethod::createMethod(CCopasiMethod::SubType subType);

  private:
    /**
     * Default Constructor
     */
    COscillationMethodIntegrate();

    /**
        * Initialize arrays and pointer.
        * @return bool success
        */
    virtual bool initialize();

    /**
     * Initialize contained objects.
     */
    void initObjects();

  public:
    /**
     * Copy Constructor
     * @param const COscillationMethodIntegrate & src
     */
    COscillationMethodIntegrate(const COscillationMethodIntegrate & src);

    /**
     * Destructor
     */
    virtual ~COscillationMethodIntegrate();

    /**
     * Execute the algorithm
     */
    virtual bool run();
  };

#endif  // COPASI_COscillationMethodIntegrate
