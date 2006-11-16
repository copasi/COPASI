%{

#include "function/CFunctionParameters.h"

%}

class CFunctionParameters : public CCopasiContainer
{

  public:
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunctionParameters(const std::string & name = "NoName",
                        const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CFunctionParameters &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunctionParameters(const CFunctionParameters & src,
                        const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    ~CFunctionParameters();

    /**
     *  Add a parameter to the parameter list
     *  @param "const CFunctionParameter &" parameter
     */

    void add(const CFunctionParameter & parameter);

    /**
     * Add a parameter to the parameter list
     * @param "const string & name
     * @param "const CFunctionParameter::DataType &" type
     * @param "const string &" usage
     * @return bool success
     */
    bool add(const std::string & name,
             const CFunctionParameter::DataType & type,
             CFunctionParameter::Role usage);

    /**
     *  Remove a parameter from the parameter list
     *  @param "const CFunctionParameter &" parameter
     */
    void remove(const std::string & name);

    /**
     * number of parameters
     */
    unsigned C_INT32 size() const;

    /**
     * tells whether there is a parameter with vector type and the given role
     * (if there is one it is assumed it is the only one with this role)
     */
    bool isVector(CFunctionParameter::Role role) const;

    /**
     *  Retrieves the first parameter with the specified usage after pos
     *  In a normal situation pos is set to 0 for the first call.
     *  It is increment by the method to allow subsequent searches to start
     *  after the last found item. This is usefull if several parameters
     *  with the same usage exist.
     *  @param "const string &" usage
     *  @param "unsigned C_INT32 &" pos (first call should be with 0)
     *  @return "CFunctionParameter &" usageRange
     */
    const CFunctionParameter * getParameterByUsage(CFunctionParameter::Role usage,
        unsigned C_INT32 & pos) const;

    /**
     * gets the number of Parameters with a specific usage
     */
    unsigned C_INT32 getNumberOfParametersByUsage(CFunctionParameter::Role usage) const;

    /**
     * find a parameter by its name and return its index
     */
    unsigned C_INT32 findParameterByName(const std::string & name,
                                         CFunctionParameter::DataType & dataType) const;

};


