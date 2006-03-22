/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CExperimentSet.h,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/22 16:52:17 $
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
     * @param const std::string & name (default: Experiment Set)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CExperimentSet(const std::string & name = "Experiment Set",
                   const CCopasiContainer * pParent = NULL);

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
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     * Compile the experiment set. This function must be called 
     * before any evaluations can be performed.
     * @param const std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    bool compile(const std::vector< CCopasiContainer * > listOfContainer =
                   CCopasiContainer::EmptyList);

    /**
     * Calculate statistics across all experiments.
     * @return bool success
     */
    bool calculateStatistics();

    /**
     * Add an experiment
     * @return CExperiment * experiment
     */
    CExperiment * addExperiment(const CExperiment & experiment);

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
     * Retrieve the indexed experiment
     * @param const std::string & name,
     * @return CExperiment * experiment
     */
    CExperiment * getExperiment(const std::string & name);

    /**
     * Retrieve the indexed experiment
     * @param const std::string & name,
     * @return const CExperiment * experiment
     */
    const CExperiment * getExperiment(const std::string & name) const;

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

    /**
     * Convert an experiment key to an index
     * @param const std::string & key
     * @return unsigned C_INT32 index
     */
    unsigned C_INT32 keyToIndex(const std::string & key) const;

    /**
     * Sort the experiments in the set
     */
    void sort();

    /**
     * Retrieve the list of file names
     * @return std::vector< std::string > fileNames
     */
    std::vector< std::string > getFileNames() const;

    /**
     * Retreive the number of data points of all experiments combined.
     * @return unsigned C_INT32 dataPointCount
     */
    unsigned C_INT32 getDataPointCount() const;

    /**
     * Retrieve the list of dependent data objects
     * @return const std::vector< CCopasiObject * > & dependentObjects
     */
    const CVector< CCopasiObject * > & getDependentObjects() const;

    /**
     * Retrieve all dependent data objective values.
     * @return const CVector< C_FLOAT64 > & dependentObjectiveValues
     */
    const CVector< C_FLOAT64 > & getDependentObjectiveValues() const;

    /**
     * Retrieve all dependent data objective values.
     * @return const CVector< C_FLOAT64 > & dependentRMS
     */
    const CVector< C_FLOAT64 > & getDependentRMS() const;

    /**
     * Retrieve all dependent data error mean values.
     * @return const CVector< C_FLOAT64 > & dependentErrorMean
     */
    const CVector< C_FLOAT64 > & getDependentErrorMean() const;

    /**
     * Retrieve all dependent data error mean std. deviations.
     * @return const CVector< C_FLOAT64 > & dependentErrorMeanSD
     */
    const CVector< C_FLOAT64 > & getDependentErrorMeanSD() const;

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

    /**
     * A set of all dependent data objects;
     */
    CVector< CCopasiObject * > mDependentObjects;

    /**
     * A list of all dependent data objective values;
     */
    CVector< C_FLOAT64 > mDependentObjectiveValues;

    /**
     * A list of all dependent data objective values;
     */
    CVector< C_FLOAT64 > mDependentRMS;

    /**
     * A list of all dependent data error mean values;
     */
    CVector< C_FLOAT64 > mDependentErrorMean;

    /**
     * A list of all dependent data error mean std. deviations;
     */
    CVector< C_FLOAT64 > mDependentErrorMeanSD;

    /**
     * A list of the number of data points for each dependent object;
     */
    CVector< unsigned C_INT32 > mDependentDataCount;
  };

#endif // COPASI_CExperimentSet
