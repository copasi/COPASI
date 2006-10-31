%{

#include "utilities/CCopasiParameterGroup.h"

%}


class CCopasiParameterGroup : public CCopasiParameter
{
  public:
    typedef std::vector< CCopasiParameter * > parameterGroup;
    typedef parameterGroup::iterator index_iterator;
    typedef CCopasiContainer::objectMap::iterator name_iterator;

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
     * This methods must be called to elevate subgroups to
     * derived objects. The default implementation does nothing.
     * @return bool success
     */
    virtual bool elevateChildren();

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
                            const CType & value);

    /**
     * Assert that a parameter with the given name and type is present.
     * If not the parameter is created with the default value.
     * @param const std::string & name
     * @param const CCopasiParameter::Type type
     * @param const CType & Value
     * @return CCopasiParameter * pParameter
     */
    template < class CType >
          CCopasiParameter * assertParameter(const std::string & name,
                                             const CCopasiParameter::Type type,
                                             const CType & defaultValue);

    /**
     * Add a subgroup to the group
     * @param const std::string & name
     * @return bool success
     */
    bool addGroup(const std::string & name);

    /**
     * Assert that a group with the given name is present.
     * If not the group is created as empty group.
     * @param const std::string & name
     * @return CCopasiParameterGroup * pGroup
     */
    CCopasiParameterGroup * assertGroup(const std::string & name);

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
     * @param const std::string & name
     * @return const CCopasiParameter * parameter
     */
    const CCopasiParameter * getParameter(const std::string & name) const;

    /**
     * Retrieve a parameter or subgroup from the group
     * @param const unsigned C_INT32 & index
     * @return CCopasiParameter * parameter
     */
    CCopasiParameter * getParameter(const unsigned C_INT32 & index);

    /**
     * Retrieve a parameter or subgroup from the group
     * @param const unsigned C_INT32 & index
     * @return const CCopasiParameter * parameter
     */
    const CCopasiParameter * getParameter(const unsigned C_INT32 & index) const;

    /**
     * Retrieve a subgroup from the group
     * @param const std::string & name
     * @return CCopasiParameterGroup * group
     */
    CCopasiParameterGroup * getGroup(const std::string & name);

    /**
     * Retrieve a subgroup from the group
     * @param const std::string & name
     * @return const CCopasiParameterGroup * group
     */
    const CCopasiParameterGroup * getGroup(const std::string & name) const;

    /**
     * Retrieve a subgroup from the group
     * @param const unsigned C_INT32 & index
     * @return CCopasiParameterGroup * parameter
     */
    CCopasiParameterGroup * getGroup(const unsigned C_INT32 & index);

    /**
     * Retrieve a subgroup from the group
     * @param const unsigned C_INT32 & index
     * @return const CCopasiParameterGroup * parameter
     */
    const CCopasiParameterGroup * getGroup(const unsigned C_INT32 & index) const;

    /**
     * Retreive a pointer to the value of a parameter or subgroup
     * @param const std::string & name
     * @return const CCopasiParameter::Value & Value
     */
    //const CCopasiParameter::Value & getValue(const std::string & name) const;

    /**
     * Retreive a pointer to the value of a parameter or subgroup
     * @param const unsigned C_INT32 & index
     * @return const CCopasiParameter::Value & Value
     */
    //const CCopasiParameter::Value & getValue(const unsigned C_INT32 & index) const;

    /**
     * Retreive a pointer to the value of a parameter or subgroup
     * @param const std::string & name
     * @return CCopasiParameter::Value & Value
     */
    //CCopasiParameter::Value & getValue(const std::string & name);

    /**
     * Retreive a pointer to the value of a parameter or subgroup
     * @param const unsigned C_INT32 & index
     * @return CCopasiParameter::Value & Value
     */
    //CCopasiParameter::Value & getValue(const unsigned C_INT32 & index);

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
                  const CType & value);

    /**
     * Set the value of a parameter or subgroup.
     * @param const unsigned C_INT32 & index
     * @param const CType & value
     * @return bool success
     */
    template <class CType>
    bool setValue(const unsigned C_INT32 & index,
                  const CType & value);

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

    /**
     * Add a parameter
     * @param CCopasiParameter * pParameter
     */
    void addParameter(CCopasiParameter * pParameter);


};



