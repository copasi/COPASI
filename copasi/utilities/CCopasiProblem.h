// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiProblem.h,v $
//   $Revision: 1.20.14.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/02/09 00:56:12 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiProblem class.
 *  This class is used to describe a problem in COPASI. This class is
 *  intended to be used as the parent class for all problems whithin COPASI.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiProblem
#define COPASI_CCopasiProblem

#include <string>

#include "utilities/CCopasiParameterGroup.h"
#include "utilities/CVector.h"
#include "utilities/CCopasiTask.h"
//#include "model/CState.h"

class CModel;
class CProcessReport;
class CReport;

class CCopasiProblem : public CCopasiParameterGroup
  {
    // Attributes
  private:
    /**
     * The type of the problem
     */
    CCopasiTask::Type mType;

  protected:
    /**
     * The model of the problem
     */
    CModel * mpModel;

    /**
     * a pointer to the callback
     */
    CProcessReport * mpCallBack;

    /**
     * A pointer to the report
     */
    CReport * mpReport;

    // propably for optimization only
#ifdef XXXX
    /**
     * A vector of variables for calculate
     */
    CVector< C_FLOAT64 > mCalculateVariables;

    /**
     * A vector of results for calculate
     */
    CVector< C_FLOAT64 > mCalculateResults;

    /**
     * A vector of solution variables
     */
    CVector< C_FLOAT64 > mSolutionVariables;

    /**
     * A vector of solution results
     */
    CVector< C_FLOAT64 > mSolutionResults;
#endif // XXXX

    // Operations
  private:
    /**
     * Default constructor
     */
    CCopasiProblem();

  protected:
    /**
     * Specific constructor
     * @param const CCopasiTask::Type & type
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiProblem(const CCopasiTask::Type & type,
                   const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Copy constructor
     * @param const CCopasiProblemr & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiProblem(const CCopasiProblem & src,
                   const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CCopasiProblem();

    /**
     * Retrieve the type of the problem
     * @return  const string & type
     */
    const CCopasiTask::Type & getType() const;

    /**
     * Set the model of the problem
     * @param CModel * pModel
     * @result bool succes
     */
    virtual bool setModel(CModel * pModel);

    /**
     * Retrieve the model of the problem
     * @result CModel * pModel
     */
    CModel * getModel() const;

    /**
     * Set the call back of the problem
     * @param CProcessReport * pCallBack
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

    /**
     * Sets the initial value (in case this applies to the specific problem)
     */
    //virtual void setInitialState(const CState & initialState);

    // propably for optimization only

    /**
     * Do all neccessary initialization so that calls to caluclate will
     * be successful. This is called once from CCopasiTask::process()
     * @result bool succes
     */
    virtual bool initialize();

    /**
     * Do the calculatting based on CalculateVariables and fill
     * CalculateResults with the results.
     * @result bool succes
     */
    // virtual bool calculate();

    /**
     * Do all neccessary restore procedures so that the
     * model is in the same state as before
     * @parem const bool & updateModel
     * @result bool succes
     */
    virtual bool restore(const bool & updateModel);

    /**
     * calculate function for optimization
     * @result bool fullfilled
     */
    // virtual bool checkParametricConstraints();

    /**
     * calculate function for optimization
     * @result bool fullfilled
     */
    // virtual bool checkFunctionalConstraints();

    /**
     * This is the output method for any object. The default implementation
     * provided with CCopasiObject uses the ostream operator<< of the object
     * to print the object.To overide this default behaviour one needs to
     * reimplement the virtual print function.
     * @param std::ostream * ostream
     */
    virtual void print(std::ostream * ostream) const;

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CCopasiProblem & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const CCopasiProblem & o);

    /**
     * This is the output method for any rsult of a problem. The default implementation
     * provided with CCopasiProblem. Does only print "Not implmented." To overide this
     * default behaviour one needs to reimplement the virtual printResult function.
     * @param std::ostream * ostream
     */
    virtual void printResult(std::ostream * ostream) const;
  };

#endif // COPASI_CCopasiProblem
