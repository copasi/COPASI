/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/ssa/Attic/CSSAProblem.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: tjohann $
   $Date: 2006/09/12 15:16:20 $
   End CVS Header */

// Copyright © 2006 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CSSAProblem
#define COPASI_CSSAProblem

#include <string>

#include "utilities/CCopasiProblem.h"
#include "model/CObjectLists.h"

class CSSAProblem: public CCopasiProblem
  {
  public:
    // Operations
    /**
     * Default constructor.
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CSSAProblem(const CCopasiContainer * pParent = NULL);

    /**
     *  Copy constructor.
     *  @param "const CSensProblem &" src
     * @paramconst CCopasiContainer * pParent (default: NULL)
     */
    CSSAProblem(const CSSAProblem & src,
                const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor.
     */
    virtual ~CSSAProblem();

  private:

    /**
     *  this sets up a problem for debugging purposes
     */
    void initDebugProblem();
  };

#endif // COPASI_CSSAProblem
