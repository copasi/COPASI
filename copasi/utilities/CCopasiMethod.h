/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiMethod.h,v $
   $Revision: 1.31 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/12 13:21:04 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 *  CCopasiMethod class.
 *  This class is used to describe a method in COPASI. This class is
 *  intended to be used as the parent class for all methods whithin COPASI.
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#ifndef COPASI_CCopasiMethod
#define COPASI_CCopasiMethod

#include <string>

#include "CCopasiParameterGroup.h"
#include "CCopasiTask.h"
#include "CReadConfig.h"

class CProcessReport;

class CCopasiMethod : public CCopasiParameterGroup
  {
  public:
    /**
     * Enumeration of the sub types of methods known to COPASI.
     */
    enum SubType
    {
      unset = 0,
      RandomSearch,
      RandomSearchMaster,
      SimulatedAnnealing,
      GeneticAlgorithm,
      EvolutionaryProgram,
      SteepestDescent,
      HybridGASA,
      GeneticAlgorithmSR,
      HookeJeeves,
      LevenbergMarquardt,
      NelderMead,
      SRES,
      Statistics,
      Newton,
      deterministic,
      LSODAR,
      stochastic,
      hybrid,
      hybridLSODA,
      tauLeap,
      mcaMethodReder,
      scanMethod,
      lyapWolf,
      tssMethod,
      sensMethod,
#ifdef COPASI_EXTREMECURRENTS
      extremeCurrents,
#endif
      EFMAlgorithm
    };

    /**
     * String literals for the GUI to display sub type names of methods known
     * to COPASI.
     */
    static const std::string SubTypeName[];

    /**
     * XML sub type names of methods known to COPASI.
     */
    static const char* XMLSubType[];

    // Attributes
  private:
    /**
     * The type of the method
     */
    CCopasiTask::Type mType;

    /**
     * The type of the method
     */
    CCopasiMethod::SubType mSubType;

  protected:
    /**
     * a pointer to the callback
     */
    CProcessReport * mpCallBack;

    /**
     * A pointer to the report
     */
    //CReport * mpReport;

    // Operations

  private:
    /**
     * Default constructor
     */
    CCopasiMethod();

  protected:
    /**
     * Specific constructor
     * @param const CCopasiTask::Type & type
     * @param const CCopasiMethod::SubType & subType
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiMethod(const CCopasiTask::Type & taskType,
                  const SubType & subType,
                  const CCopasiContainer * pParent = NULL);

  public:
    /**
     * Convert a SubTypeName to the matching enum value.
     * Returns CCopasiMethod::unset if no match is found.
     * @param (const std::string & subTypeName)
     * @return CCopasiMethod::SubType type
     */
    static
    CCopasiMethod::SubType TypeNameToEnum(const std::string & subTypeName);

    /**
     * Copy constructor
     * @param const CCopasiMethodr & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiMethod(const CCopasiMethod & src,
                  const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CCopasiMethod();

    /**
     * Set the call back of the problem
     * @param CProcessReport * pCallBack
     * @result bool succes
     */
    virtual bool setCallBack(CProcessReport * pCallBack);

    /**
     * Retrieve the type of the method
     * @return  const string & type
     */
    const CCopasiTask::Type & getType() const;

    /**
     * Retrieve the sub type of the method
     * @return CCopasiMethod::SubType & subType
     */
    const CCopasiMethod::SubType & getSubType() const;

    /**
     * Check if the method is suitable for this problem
     * @return bool suitability of the method
     */
    virtual bool isValidProblem(const CCopasiProblem * pProblem);

    /**
     * Load a list of parameters
     * @param "CReadConfig &" configBuffer
     * @param "CReadConfig::Mode" mode Default(CReadConfig::SEARCH)
     */
    virtual void load(CReadConfig & configBuffer,
                      CReadConfig::Mode mode = CReadConfig::SEARCH);

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
     * @param const CCopasiMethod & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const CCopasiMethod & o);
  };

#endif // COPASI_CCopasiMethod
