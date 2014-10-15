// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_COSCINT
#define COPASI_COSCINT

#include "COscillationMethod.h"

class COptProblem;

class COscillationMethodIntegrate : public COscillationMethod
{
  friend COscillationMethod * COscillationMethod::createMethod(CTaskEnum::Method subType);

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
