/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/elementaryFluxModes/CEFMMethod.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/29 20:15:14 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#ifndef COPASI_CEFMMethod
#define COPASI_CEFMMethod

#include <string>

#include "CFluxMode.h"

#include "utilities/CCopasiMethod.h"
#include "utilities/CVector.h"

class CEFMMethod : public CCopasiMethod
  {
    // Operations
  private:
    /**
     * Default constructor.
     */
    CEFMMethod();

  protected:
    /**
     * Specific constructor
     * @param const CCopasiTask::Type & type
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CEFMMethod(const CCopasiTask::Type & taskType,
               const SubType & subType,
               const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a EFM method.
     * Note: the returned object has to be released after use with delete
     */
    static CEFMMethod * createMethod(CCopasiMethod::SubType subType
                                     = CCopasiMethod::RandomSearch);

    /**
     * Copy constructor
     * @param const CEFMMethod & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CEFMMethod(const CEFMMethod & src,
               const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CEFMMethod();

    /**
     * Execute the optimization algorithm calling simulation routine
     * when needed. It is noted that this procedure can give feedback
     * of its progress by the callback function set with SetCallback.
     * @ return success;
     */
    virtual bool calculate();

    /**
     * Initialize arrays and pointer.
     * @return bool success
     */
    virtual bool initialize();

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

    const std::vector< CFluxMode > & getFluxModes() const;

    const CVector< unsigned C_INT32 > & getIndex() const;

    // Attributes
  protected:
    /**
     * The resulting elementary flux modes
     */
    std::vector< CFluxMode > mFluxModes;

    /**
     * Vector to keep track of the rearangements neccessary to put the
     * reversible reactions to the top of Stoi
     */
    CVector< unsigned C_INT32 > mIndex;
  };

#endif  // COPASI_CEFMMethod
