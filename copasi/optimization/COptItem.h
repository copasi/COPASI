/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptItem.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/01/20 20:41:42 $
   End CVS Header */

#ifndef COPASI_COptItem
#define COPASI_COptItem

#include "report/CCopasiObject.h"

class CCopasiParameterGroup;
class CCopasiObjectName;
class COptProblem;

class COptItem
  {
    friend class COptProblem;

    //Operations
  private:
    /**
     * Specific Constructor
     */
    COptItem(CCopasiParameterGroup & group);

  public:
    /**
     * Copy Constructor
     * @param COptItem & src
     */
    COptItem(COptItem & src);

    /**
     * Destructor
     */
    ~COptItem();

    /**
     * Set the object of the optimization item.
     * @param const CCopasiObjectName & objectCN
     * @return bool success
     */
    bool setObjectCN(const CCopasiObjectName & objectCN);

    /**
     * Retrieve the object of the optimization item.
     * @return const CCopasiObjectName objectCN
     */
    const CCopasiObjectName getObjectCN() const;

    /**
     * Set the lower bound.
     * @param const std::string & lowerBound
     * @return bool success
     */
    bool setLowerBound(const std::string & lowerBound);

    /**
     * Retrieve the lower bound.
     * @return const std::string lowerBound
     */
    const std::string getLowerBound() const;

    /**
     * Set the lower relationship.
     * @param const std::string & lowerRel (< or <=)
     * @return bool success
     */
    bool setLowerRelation(const std::string & lowerRel);

    /**
     * Retrieve the lower relationship.
     * @return const std::string lowerRel
     */
    const std::string getLowerRelation() const;

    /**
     * Set the upper bound.
     * @param const std::string & upperBound
     * @return bool success
     */
    bool setUpperBound(const std::string & upperBound);

    /**
     * Retrieve the upper bound.
     * @return const std::string upperBound
     */
    const std::string getUpperBound() const;

    /**
     * Set the upper relationship.
     * @param const std::string & upperRel (< or <=)
     * @return bool success
     */
    bool setUpperRelation(const std::string & upperRel);

    /**
     * Retrieve the upper relationship.
     * @return const std::string upperRel
     */
    const std::string getUpperRelation() const;

    /**
     * Check the validity of the optimization item.
     * @return bool isValid
     */
    bool isValid() const;

    /**
     * Check whether the group describes a valit optimization item.
     * @param CCopasiParameterGroup & group
     * @return bool isValid
     */
    static bool isValid(CCopasiParameterGroup & group);

    bool compile();

    C_INT32 checkConstraint(const C_FLOAT64 & value);

    bool checkLowerBound(const C_FLOAT64 & value);

    bool checkUpperBound(const C_FLOAT64 & value);

    static bool less(const C_FLOAT64 & val1, const C_FLOAT64 & val2);

    static bool lessOrEqual(const C_FLOAT64 & val1, const C_FLOAT64 & val2);

    C_FLOAT64 * getObjectValue();

    C_FLOAT64 * getLowerBoundValue();

    C_FLOAT64 * getUpperBoundValue();

    //Attributes:
  private:
    /**
     * A pointer to the parameter group which stores the information.
     */
    CCopasiParameterGroup * mpGroup;

    /**
     *
     */
    C_FLOAT64 * mpObjectValue;

    /**
     *
     */
    C_FLOAT64 * mpLowerBound;

    /**
     *
     */
    C_FLOAT64 mLowerBound;

    /**
     *
     */
    bool (*mpLowerRel)(const C_FLOAT64 & val1, const C_FLOAT64 & val2);

    /**
     *
     */
    C_FLOAT64 * mpUpperBound;

    /**
     *
     */
    C_FLOAT64 mUpperBound;

    /**
     *
     */
    bool (*mpUpperRel)(const C_FLOAT64 & val1, const C_FLOAT64 & val2);
  };

#endif // COPASI_COptItem
