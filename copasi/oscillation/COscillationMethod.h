// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/oscillation/COscillationMethod.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2008/11/11 16:47:54 $
// End CVS Header
// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef COPASI_COscMethod
#define COPASI_COscMethod

#include "utilities/CCopasiMethod.h"

class COscillationProblem;
class COscillationTask;

class COscillationMethod : public CCopasiMethod
  {
  public:

  protected:

    COscillationProblem * mpOscProblem;

    //    COptTask * mpParentTask;

  private:
    /**
     * Default constructor.
     */
    COscillationMethod();

  protected:
    /**
     * Specific constructor
     * @param const CCopasiTask::Type & type
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COscillationMethod(const CCopasiTask::Type & taskType,
                       const SubType & subType,
                       const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Create a optimization method.
     * Note: the returned object has to be released after use with delete
     */
    static COscillationMethod * createMethod(CCopasiMethod::SubType subType
        = CCopasiMethod::oscillationIntegrate);

    /**
     * Copy constructor
     * @param const COscillationMethod & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    COscillationMethod(const COscillationMethod & src,
                       const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~COscillationMethod();

    /**
     * Execute the algorithm
     * @ return success;
     */
    virtual bool run() = 0;

    /**
     * Set the problem to be optmised
     * @param "COscillationProblem *" problem
     */
    void setProblem(COscillationProblem * problem);

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

  protected:
    /**
     * Cleanup arrays and pointers.
     * @return bool success
     */
    virtual bool cleanup();
  };

#endif  // COPASI_COscillationMethod
