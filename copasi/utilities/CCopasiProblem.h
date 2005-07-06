/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiProblem.h,v $
   $Revision: 1.13 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/07/06 17:14:24 $
   End CVS Header */

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

#include "CCopasiParameterGroup.h"
#include "CVector.h"
#include "CCopasiTask.h"
#include "model/CState.h"

class CModel;
class CProcessReport;
class CReport;

class CDefaultPlotDescription
  {
  public:
    C_INT32 id;
    std::string name;
    std::string description;
    bool isPlot;
  };

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

    virtual std::vector<CDefaultPlotDescription> getListOfDefaultPlotDescriptions() const;
    virtual bool createDefaultPlot(C_INT32 id) const;

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
    virtual bool calculate();

    /**
     * calculate function for optimization
     * @result bool fullfilled
     */
    virtual bool checkParametricConstraints();

    /**
     * calculate function for optimization
     * @result bool fullfilled
     */
    virtual bool checkFunctionalConstraints();
  };

#endif // COPASI_CCopasiProblem
