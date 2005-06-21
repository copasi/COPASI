/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/utilities/CCopasiParameterGroup.h,v $
   $Revision: 1.12 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/06/21 13:15:28 $
   End CVS Header */

#ifndef COPASI_CCopasiParameterGroup
#define COPASI_CCopasiParameterGroup

#include <string>
#include <vector>

#include "CCopasiParameter.h"

/**
 *  CCopasiParameterGroup class.
 *  This class is used to describe parameters. This class is intended
 *  to be used with integration or optimization methods or reactions.
 *  
 *  Created for Copasi by Stefan Hoops 2002
 */
class CCopasiParameterGroup: public CCopasiParameter
  {
  public:
    typedef std::vector< CCopasiParameter * > parameterGroup;
    typedef parameterGroup::iterator index_iterator;
    typedef CCopasiContainer::objectMap::iterator name_iterator;

    // Operations
  protected:
    /**
     * Default constructor
     */
    CCopasiParameterGroup();

  public:
    /**
     * Copy constructor
     * @param "const CCopasiParameterGroup &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CCopasiParameterGroup(const CCopasiParameterGroup & src,
                          const CCopasiContainer * pParent = NULL);

    /**
     * Specific constructor
     * @param const string & name
     * @param const CCopasiContainer * pParent (default: NULL)
     * @param const std::string & objectType (default: "ParameterGroup")
     */
    CCopasiParameterGroup(const std::string & name,
                          const CCopasiContainer * pParent = NULL,
                          const std::string & objectType = "ParameterGroup");

    /**
     * Destructor
     */
    virtual ~CCopasiParameterGroup();

    /**
     * Assignement operator
     * @param const CCopasiParameterGroup & rhs
     * @return CCopasiParameterGroup & lhs
     */
    CCopasiParameterGroup & operator = (const CCopasiParameterGroup & rhs);

    /**
     * Retrieve the begin of an alphabetically sorted iterator
     * @return name_iterator begin
     */
    name_iterator beginName() const;

    /**
     * Retrieve the end of an alphabetically sorted iterator
     * @return name_iterator end
     */
    name_iterator nameEnd() const;

    /**
     * Retrieve the begin of unsorted iterator
     * Note: the swap function may be used to change the order
     * @return name_iterator begin
     */
    index_iterator beginIndex() const;

    /**
     * Retrieve the end of unsorted iterator
     * Note: the swap function may be used to change the order
     * @return name_iterator end
     */
    index_iterator endIndex() const;

    /**
     * Add a parameter
     * @param const CCopasiParameter & parameter
     * @return bool success
     */
    bool addParameter(const CCopasiParameter & parameter);

    /**
     * Add a parameter to the group
     * @param const std::string & name
     * @param const CCopasiParameter::Type type
     * @return bool success
     */
    bool addParameter(const std::string & name,
                      const CCopasiParameter::Type type);

    /**
     * Add a parameter to the group
     * @param const std::string & name
     * @param const CCopasiParameter::Type type
     * @param const CType & value
     * @return bool success
     */
    template < class CType >
          bool addParameter(const std::string & name,
                            const CCopasiParameter::Type type,
                            const CType & value)
      {
        CCopasiParameter * pParameter;

        if (type == GROUP)
          {
            CCopasiParameterGroup *tmp = new CCopasiParameterGroup(name);
            if (!tmp->isValidValue(value))
              {
                delete tmp;
                return false;
              }

            tmp->mValue.pVOID = const_cast<void *>((const void *) & value);
            pParameter = new CCopasiParameterGroup(*tmp);
          }
        else
          {
            pParameter = new CCopasiParameter(name, type);
            if (!pParameter->isValidValue(value))
              {
                delete pParameter;
                return false;
              }

            pParameter->setValue(value);
          }

        addParameter(pParameter);

        return true;
      }

    /**
     * Add a subgroup to the group
     * @param const std::string & name
     * @return bool success
     */
    bool addGroup(const std::string & name);

    /**
     * Remove a parameter or subgroup from the group
     * @param const std::string & name
     * @return bool success
     */
    bool removeParameter(const std::string & name);

    /**
     * Remove a parameter or subgroup from the group
     * @param const unsigned C_INT32 & index
     * @return bool success
     */
    bool removeParameter(const unsigned C_INT32 & index);

    /**
     * Retrieve a parameter or subgroup from the group
     * @param const std::string & name
     * @return CCopasiParameter * parameter
     */
    CCopasiParameter * getParameter(const std::string & name);

    /**
     * Retrieve a parameter or subgroup from the group
     * @param const unsigned C_INT32 & index
     * @return CCopasiParameter * parameter
     */
    CCopasiParameter * getParameter(const unsigned C_INT32 & index);
    const CCopasiParameter * getParameter(const unsigned C_INT32 & index) const;

    /**
     * Retreive a pointer to the value of a parameter or subgroup
     * @param const std::string & name
     * @return const void * pValue
     */
    const void * getValue(const std::string & name) const;

    /**
     * Retreive a pointer to the value of a parameter or subgroup
     * @param const unsigned C_INT32 & index
     * @return const void * pValue
     */
    const void * getValue(const unsigned C_INT32 & index) const;

    /**
     * Retreive a pointer to the value of a parameter or subgroup
     * @param const std::string & name
     * @return void * pValue
     */
    void * getValue(const std::string & name);

    /**
     * Retreive a pointer to the value of a parameter or subgroup
     * @param const unsigned C_INT32 & index
     * @return void * pValue
     */
    void * getValue(const unsigned C_INT32 & index);

    /**
     * Retreive the type of a parameter or subgroup
     * @param const std::string & name
     * @return CCopasiParameter::Type
     */
    CCopasiParameter::Type getType(const std::string & name) const;

    /**
     * Retreive the type of a parameter or subgroup
     * @param const unsigned C_INT32 & index
     * @return CCopasiParameter::Type
     */
    CCopasiParameter::Type getType(const unsigned C_INT32 & index) const;

    /**
     * Retreive the key of a parameter or subgroup
     * @param const std::string & name
     * @return std::string key
     */
    std::string getKey(const std::string & name) const;

    /**
     * Retreive the key of a parameter or subgroup
     * @param const unsigned C_INT32 & index
     * @return std::string key
     */
    std::string getKey(const unsigned C_INT32 & index) const;

    /**
     * Retreive the name of a parameter or subgroup
     * @param const unsigned C_INT32 & index
     * @return std::string name
     * 
     */
    const std::string & getName(const unsigned C_INT32 & index) const;

    /**
     * Set the value of a parameter or subgroup.
     * @param const std::string & name
     * @param const CType & value
     * @return bool success
     */
    template <class CType>
    bool setValue(const std::string & name,
                  const CType & value)
    {
      CCopasiParameter * pParameter =
        const_cast< CCopasiParameterGroup * >(this)->getParameter(name);

      if (pParameter) return pParameter->setValue(value);

      return false;
    }

    /**
     * Set the value of a parameter or subgroup.
     * @param const unsigned C_INT32 & index
     * @param const CType & value
     * @return bool success
     */
    template <class CType>
    bool setValue(const unsigned C_INT32 & index,
                  const CType & value)
    {
      CCopasiParameter * pParameter =
        const_cast< CCopasiParameterGroup * >(this)->getParameter(index);

      if (pParameter) return pParameter->setValue(value);

      return false;
    }

    /**
     * Swap two parameters
     * Note: This has effect on the index_iterator and index access methods.
     * @param const unsigned C_INT32 & iFrom
     * @param const unsigned C_INT32 & iTo
     * @return bool success 
     */
    bool swap(const unsigned C_INT32 & iFrom,
              const unsigned C_INT32 & iTo);

    /**
     * Swap two parameters
     * Note: This has effect on the iterator and index access methods.
     * @param index_iterator & from
     * @param index_iterator & to
     * @return bool success 
     */
    bool swap(index_iterator & from,
              index_iterator & to);

    /**
     * The size of the parameter group
     * @ return unsigned C_INT32 size
     */
    unsigned C_INT32 size() const;

    /**
     * Clear all parameters and subgroups
     */
    void clear();

    /**
     * Retrieve the index of a parameter or subgroup with a given name
     * @param const std::string & name
     * @return unsigned C_INT32 index
     */
    unsigned C_INT32 getIndex(const std::string & name) const;

  private:
    /**
     * Create or copy the parameterGroup 
     * @param const parameterGroup * pGroup (default: NULL)
     */
    void createGroup(const parameterGroup * pGroup = NULL);

    /**
     * Delete the parameterGroup
     */
    void deleteGroup();

    /**
     * Add a parameter
     * @param CCopasiParameter * pParameter
     */
    void addParameter(CCopasiParameter * pParameter);

    /**
     * Output stream operator
     * @param ostream & os
     * @param const CCopasiParameterGroup & A
     * @return ostream & os
     */
    friend std::ostream & operator << (std::ostream & os,
                                       const CCopasiParameterGroup & A)
    {
      os << (CCopasiParameter) A;

      parameterGroup::const_iterator it =
        A.mValue.pGROUP->begin();
      parameterGroup::const_iterator end =
        A.mValue.pGROUP->end();

      for (; it != end; ++it) os << **it;

      return os;
    }
  };

#endif // COPASI_CCopasiParameterGroup
