// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/moieties/CMoietiesMethod.h,v $
//   $Revision: 1.1.2.2 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/11 18:30:54 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_CMoietiesMethod
#define COPASI_CMoietiesMethod

#include "copasi/utilities/CCopasiMethod.h"

class CProcessReport;
class CMoietiesProblem;

class CMoietiesMethod : public CCopasiMethod
  {
  private:
    /**
     * Default constructor
     */
    CMoietiesMethod();

  protected:
    /**
     * Specific constructor
     * @param const CCopasiTask::Type & type
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoietiesMethod(const CCopasiTask::Type & taskType,
                    const SubType & subType,
                    const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a trajectory method for a special problem.
     * Note: the returned object has to be released after use with delete
     * a problem is also passed so that the method has a chance to choose an
     * appropriate simulation method.
     * @param const CCopasiMethod::SubType & subType (default: CCopasiMethod::Householder)
     * @return CMoietiesMethod *
     */
    static
    CMoietiesMethod * createMethod(const CCopasiMethod::SubType & subType = CCopasiMethod::Householder);

    /**
     * Copy constructor
     * @param const CMoietiesMethod & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CMoietiesMethod(const CMoietiesMethod & src,
                    const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CMoietiesMethod();

    /**
     * Determine the independent metabolites.
     */
    virtual bool process();

    /**
     * Set the problem
     * @param CMoietiesProblem * pProblem
     */
    void setProblem(CMoietiesProblem * pProblem);

    // Attributes
  protected:
    /**
     * The problem to be processed
     */
    CMoietiesProblem * mpProblem;
  };

#endif // COPASI_CMoietiesMethod
