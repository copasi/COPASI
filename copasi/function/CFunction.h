/**
 * CFunction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunction
#define COPASI_CFunction

#include <string>

#include "copasi.h"
#include "CFunctionParameters.h"
#include "CCallParameters.h"
#include "report/CCopasiContainer.h"

enum TriLogic
{
  TriUnspecified = -1,
  TriFalse = 0,
  TriTrue = 1
};

/** @dia:pos 58.2,12.15 */
class CFunction : public CCopasiContainer
  {
  public:
    /**
     *  The valid types of a function
     */
    enum Type
    {
      Base = 0,
      MassAction,
      PreDefined,
      UserDefined,
      Output
    };

    // Attributes
  private:

    /**
     *  The type of the function
     */
    CFunction::Type mType;

    /**
     *  The name of the function
     */
    std::string & mName;

    /**
     *  The mathematical formula
     */
    std::string mDescription;

    /**
     *  Whether the function is reversible
     */
    TriLogic mReversible;

    /**
     *  A vector of usages ranges describing the condition under which a 
     *  function may be used.
     */
    CCopasiVectorNS < CUsageRange > mUsageDescriptions;

    /**
     *  The discription of the parameters of the function
     */
    /** @dia:route 3,2; h,58.2,12.85,56.537,6.51973,52.9592 */
    CFunctionParameters mParameters;

    // Operations
  public:

    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunction(const std::string & name = "NoName",
              const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CFunction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CFunction(const CFunction & src,
              const CCopasiContainer * pParent = NULL);

    /**
     *  Destructor
     */
    virtual ~CFunction();

    /**
     *  Cleanup
     */
    virtual void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param "CReadConfig &" configBuffer
     *  @param "CReadConfig::Mode" mode (default: CReadConfig::SEARCH)
     *  @return Fail
     */
    virtual void load(CReadConfig & configBuffer,
                      CReadConfig::Mode mode = CReadConfig::SEARCH);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param "CWriteConfig &" configBuffer.
     *  @return Fail
     */
    virtual void save(CWriteConfig & configBuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  Output is in Gepasi 3.21 file format.
     *  @param "CWriteConfig &" configBuffer.
     *  @return Fail
     */
    virtual void saveOld(CWriteConfig & configBuffer);

    /**
     *  Returns a string containing the explicit function in SBML format
     *  @param "vector < void * >" callParameters
    *  @param "const string &" r a suffix for parameter names (usually reaction number)
     */
    virtual std::string getSBMLString(const CCallParameters & callParameterNames, const std::string &r);

    /**
     *  Retrieves the name of the function
     *  @return "const string &" name
     */
    virtual const std::string& getName() const;

    /**
     *  Set the name of the function
     *  @param "const string &" name
     */
    virtual void setName(const std::string& name);

    /**
     *  Retrieves the description of the function
     *  @return "const string &" description
     */
    virtual const std::string& getDescription() const;

    /**
     *  Set the description of the function
     *  @param "const string &" description
     */
    virtual void setDescription(const std::string& description);

    /**
     *  Retrieves the type of the function
     *  @return "const CFunction::Type &" type
     */
    virtual const CFunction::Type & getType() const;

    /**
     *  Set the type of the function
     *  @param "const CFunction::Type &" type
     */
    virtual void setType(const CFunction::Type & type);

    /**
     *  Set whether the function is reversible.
     */
    virtual void setReversible(const TriLogic & reversible);

    /**
     *  Retrieves whether the function is reversible.
     */
    virtual const TriLogic & isReversible() const;

    /**
     *  Retrives the definition of the parameters
     */
    virtual CFunctionParameters & getParameters();

    /**
     *  Retrives the of the usage description of 
     */
    virtual CCopasiVectorNS < CUsageRange > & getUsageDescriptions();

    /**
     *  Retrieves the position of a parameter in the function call
     *  @param "const string &" name
     *  @return "const unsigned C_INT32" index
     */
    virtual unsigned C_INT32 getParameterPosition(const std::string & name);

    /**
     *  Calculates the value of the function
     *  @param const CCallParameters & callParameters
     *  @return "C_FLOAT64" result
     */
    virtual C_FLOAT64 calcValue(const CCallParameters & callParameters) const;

    /**
     * Returns whether the function depends on the given parameter
     * &param const void * parameter
     * &param const CCallParameters & callParameters
     * &param bool dependsOn
     */
    virtual bool dependsOn(const void * C_UNUSED(parameter),
                           const CCallParameters & C_UNUSED(callParameters)) const;

    /**
     *  Adds one usage descriptiont
     *  @param "const string &" usage (SUBSTRATE or PRODUCT)
     *  @param "C_INT32" low lower cardinality
     *  @param "C_INT32" high maximum cardinality
     */
    virtual void addUsage(const std::string& usage, C_INT32 low, C_INT32 high);

    /**
     *  Adds the description of one parameter 
     *  @param "const string &" name the name of the parameter
    *  @param "CFunctionParameter::DataType &" type type of parameter (usually FLOAT64)
    *  @param "const string &" usage usage for this paramter (SUBSTRATE, PRODUCT, MODIFIER, PARAMETER)
     */
    virtual void addParameter(const std::string & name,
                              const CFunctionParameter::DataType & type,
                              const std::string & usage);
  };
#endif // COPASI_CFunction
