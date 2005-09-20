/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/parameterFitting/CFitItem.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/09/20 13:07:40 $
   End CVS Header */

#ifndef COPASI_CFitItem
 #define COPASI_CFitItem

#include "optimization/COptItem.h"

class CFitItem : public COptItem
  {
    friend class CFitProblem;

    //Operations
  private:
    /**
     * Specific Constructor
     */
    CFitItem(CCopasiParameterGroup & group);

  public:
    /**
     * Copy Constructor
     * @param CFitItem & src
     */
    CFitItem(CFitItem & src);

    /**
     * Destructor
     */
    virtual ~CFitItem();

    /**
     * Initialize the optimization item.
     * @param const CCopasiObjectName & objectCN
     * @return bool success
     */
    virtual bool initialize(const CCopasiObjectName & objectCN);

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
    // Attributes
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
