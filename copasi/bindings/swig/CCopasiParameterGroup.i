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
     * Add a parameter to the group
     * @param const std::string & name
     * @param const CCopasiParameter::Type type
     * @return bool success
     */
    bool addParameter(const std::string & name,
                      const CCopasiParameter::Type type);


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

    /**
     * Retrieve a subgroup from the group
     * @param const std::string & name
     * @return CCopasiParameterGroup * group
     */
    CCopasiParameterGroup * getGroup(const std::string & name);

    /**
     * Retrieve a subgroup from the group
     * @param const unsigned C_INT32 & index
     * @return CCopasiParameterGroup * parameter
     */
    CCopasiParameterGroup * getGroup(const unsigned C_INT32 & index);


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


};



