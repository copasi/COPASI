/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentSet.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/19 21:12:54 $
   End CVS Header */

#ifndef COPASI_CExperimentSet
 #define COPASI_CExperimentSet

#include <string>

#include "utilities/CCopasiParameterGroup.h"
 #include "utilities/CCopasiTask.h"
 #include "utilities/CMatrix.h"

class CExperiment;

class CExperimentSet: public CCopasiParameterGroup
  {
  public:
    /**
     * Default constructor
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExperimentSet(const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CExperimentSet & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExperimentSet(const CExperimentSet & src,
                   const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor used for reading copasi files
     * @param const CCopasiParameterGroup & group
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExperimentSet(const CCopasiParameterGroup & group,
                   const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CExperimentSet();

    /**
     * Add an experiment
     * @return CExperiment * experiment
     */
    CExperiment * addExperiment(const CExperiment & experiment);

    /**
     * Remove the indexed experiment
     * @param const unsigned C_INT32 & index,
     * @return bool success
     */
    bool removeExperiment(const unsigned C_INT32 & index);

    /**
     * Retrieve the indexed experiment
     * @param const unsigned C_INT32 & index,
     * @return CExperiment * experiment
     */
    CExperiment * getExperiment(const unsigned C_INT32 & index);

    /**
     * Retrieve the indexed experiment
     * @param const unsigned C_INT32 & index,
     * @return const CExperiment * experiment
     */
    const CExperiment * getExperiment(const unsigned C_INT32 & index) const;

    /**
     * Retrieve the indexed experiment type
     * @param const unsigned C_INT32 & index,
     * @return const CCopasiTasK::Type & experimentType
     */
    const CCopasiTask::Type & getExperimentType(const unsigned C_INT32 & index) const;

    /**
     * Retrieve the independent data of the indexed experiment.
     * @param const unsigned C_INT32 & index,
     * @return const CMatrix< C_FLOAT64 > & independentData
     */
    const CMatrix< C_FLOAT64 > & getIndependentData(const unsigned C_INT32 & index) const;

    /**
     * Retrieve the dependent data of the indexed experiment.
     * @param const unsigned C_INT32 & index,
     * @return const CMatrix< C_FLOAT64 > & dependentData
     */
    const CMatrix< C_FLOAT64 > & getDependentData(const unsigned C_INT32 & index) const;

  private:
    /**
     * Allocates all group parameters and assures that they are 
     * properly initialized.
     */
    void initializeParameter();

  private:
    // Attributes
    /**
     * This is realized a CCopasiParameter type GROUP
     */
    std::vector< CExperiment * > * mpExperiments;
  };

#endif // COPASI_CExperimentSet
