// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/CMoietiesProblem.h,v $
//   $Revision: 1.1.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/11 18:30:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
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
     * @param const CCopasiTask::Type & type (default: moieties)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoietiesProblem(const CCopasiTask::Type & type = CCopasiTask::moieties,
                     const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor.
     * @param const CMoietiesProblem & src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CMoietiesProblem(const CMoietiesProblem & src,
                     const CCopasiContainer * pParent = NULL);

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
