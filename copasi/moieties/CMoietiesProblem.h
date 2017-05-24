// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

#ifndef COPASI_CMoietiesProblem
#define COPASI_CMoietiesProblem

#include "copasi/utilities/CCopasiProblem.h"

class CMoietiesProblem : public CCopasiProblem
{
  // Implementation

public:

  /**
   * Default constructor
   * @param const CTaskEnum::Task & type (default: moieties)
   * @param const CDataContainer * pParent (default: NULL)
   */
  CMoietiesProblem(const CTaskEnum::Task & type = CTaskEnum::Task::moieties,
                   const CDataContainer * pParent = NO_PARENT);

  /**
   * Copy constructor.
   * @param const CMoietiesProblem & src
   * @paramconst CDataContainer * pParent (default: NULL)
   */
  CMoietiesProblem(const CMoietiesProblem & src,
                   const CDataContainer * pParent);

  /**
   * Destructor
   */
  virtual ~CMoietiesProblem();

  /**
   * This is the output method for any result of a problem. The default implementation
   * provided with CCopasiProblem. Does only print "Not implmented." To overide this
   * default behaviour one needs to reimplement the virtual printResult function.
   * @param std::ostream * pOstream
   */
  virtual void printResult(std::ostream * pOstream) const;
};

#endif  // COPASI_CMoietiesProblem
