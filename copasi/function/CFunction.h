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

enum TriLogic
{
  TriUnspecified = -1,
  TriFalse = FALSE,
  TriTrue = TRUE
};

class CFunction
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
    string mName;

    /**
     *  The mathematical formula
     */
    string mDescription;

    /**
     *  Whether the function is reversible
     */
    TriLogic mReversible;

    /**
     *  A vector of usages ranges describing the condition under which a 
     *  function may be used.
     * @supplierCardinality 0..**/
    CCopasiVectorNS < CUsageRange > mUsageDescriptions;

    /**
     *  The discription of the parameters of the function
     *  @supplierCardinality 1 
     */
    CFunctionParameters mParameters;

    // Operations
  public:

    /**
     *  Default constructor
     */
    CFunction();

    /**
     *  Copy constructor
     *  @param "const CFunction &" src
     */
    CFunction(const CFunction & src);

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
     *  Retrieves the name of the function
     *  @return "const string &" name
     */
    virtual const string& getName() const;

    /**
     *  Set the name of the function
     *  @param "const string &" name
     */
    virtual void setName(const string& name);

    /**
     *  Retrieves the description of the function
     *  @return "const string &" description
     */
    virtual const string& getDescription() const;

    /**
     *  Set the description of the function
     *  @param "const string &" description
     */
    virtual void setDescription(const string& description);

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
    virtual unsigned C_INT32 getParameterPosition(const string & name);

    /**
     *  Calculates the value of the function
     *  @param "vector < void * >" callParameters
     *  @return "C_FLOAT64" result
     */
    virtual C_FLOAT64 calcValue(const CCallParameters & callParameters) const;

    /**
     *  Adds one usage descriptiont
     *  @param "const string &" usage (SUBSTRATE or PRODUCT)
     *  @param "C_INT32" low lower cardinality
     *  @param "C_INT32" high maximum cardinality
     */
    virtual void addUsage(const string& usage, C_INT32 low, C_INT32 high);

    /**
     *  Adds the description of one parameter 
     *  @param "const string &" name the name of the parameter
    *  @param "CFunctionParameter::DataType &" type type of parameter (usually FLOAT64)
    *  @param "const string &" usage usage for this paramter (SUBSTRATE, PRODUCT, MODIFIER, PARAMETER)
     */
    virtual void addParameter(const string & name, const CFunctionParameter::DataType & type,
                              const string & usage);
  };
#endif // COPASI_CFunction
