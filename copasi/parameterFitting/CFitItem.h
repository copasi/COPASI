/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitItem.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/30 15:19:03 $
   End CVS Header */

#ifndef COPASI_CFitItem
 #define COPASI_CFitItem

#include "optimization/COptItem.h"

class CFitItem : public COptItem
  {
    friend class CFitProblem;

    //Operations
  public:
    /**
     * Default constructor
     * @param const std::string & name (default: FitItem)
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitItem(const std::string & name = "FitItem",
             const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param const CFitItem & src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitItem(const CFitItem & src,
             const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor used for reading copasi files
     * @param const CCopasiParameterGroup & group
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFitItem(const CCopasiParameterGroup & group,
             const CCopasiContainer * pParent = NULL);

    /**
     * Destructor
     */
    virtual ~CFitItem();

    /**
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

    /**
     * Retrieve the update method
     * @return UpdateMethod * pUpdateMethod
     */
    virtual UpdateMethod * getUpdateMethod() const;

    /**
     * Check the validity of the optimization item.
     * @return bool isValid
     */
    virtual bool isValid() const;

    /**
     * Check whether the group describes a valid optimization item.
     * @param CCopasiParameterGroup & group
     * @return bool isValid
     */
    static bool isValid(CCopasiParameterGroup & group);

    /**
     * Compile the optimization item. This function must be called 
     * before any of the check functions are called.
     * @param const std::vector< CCopasiContainer * > listOfContainer
     * @return bool success
     */
    virtual bool compile(const std::vector< CCopasiContainer * > listOfContainer =
                           CCopasiContainer::EmptyList);

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CFitItem & A
     * @return ostream & os
     */
    friend std::ostream &operator<<(std::ostream &os, const CFitItem & o);

    /**
     * Set the local value.
     * @param const C_FLOAT64 & value
     * @return bool success
     */
    bool setLocalValue(const C_FLOAT64 & value);

    /**
     * Retreive the local value.
     * @return const C_FLOAT64 & value
     */
    const C_FLOAT64 & getLocalValue() const;

    /**
     * Add an experiment to the list of affected experiments.
     * @param const std::string & key
     * @return bool success
     */
    bool addExperiment(const std::string & key);

    /**
     * Retreive the key of the indexed experiment.
     * @param const unsigned C_INT32 & index
     * @return const std::string & key
     */
    const std::string & getExperiment(const unsigned C_INT32 & index) const;

    /**
     * Remove the indexed experiment from the affected experiments
     * @param const unsigned C_INT32 & index
     * @return bool success
     */
    bool removeExperiment(const unsigned C_INT32 & index);

    /**
     * Retrieve the number of experiments
     * @return unsigned C_INT32 size
     */
    unsigned C_INT32 getExperimentCount() const;

  private:
    /**
     * Allocates all group parameters and assures that they are 
     * properly initialized.
     */
    void initializeParameter();

  private:
    // Attributes
    /**
     * A pointer to the value of the CCopasiParameterGroup holding the 
     * list of AffectedExperiments
     */
    CCopasiParameterGroup * mpGrpAffectedExperiments;

    /**
     * The value for local items, which affect the experiments in the list.
     */
    C_FLOAT64 mLocalValue;

    /**
     * A pointer to the local update method
     */
    UpdateMethod * mpLocalMethod;
  };

#endif // COPASI_CFitItem
