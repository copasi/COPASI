// Copyright (C) 2019 - 2025 by Pedro Mendes, Rector and Visitors of the
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
  bool initialize() override;

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
