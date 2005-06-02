/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunction.h,v $
   $Revision: 1.33 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/06/02 19:58:13 $
   End CVS Header */

/**
 * CFunction
 * 
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#ifndef COPASI_CFunction
#define COPASI_CFunction

#include <string>

#include "CFunctionParameters.h"
#include "CCallParameters.h"
#include "report/CCopasiContainer.h"

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
      Expression
    };

    /**
     *  The string representation of valid types of a function
     */
    static const std::string TypeName[];

    /**
     *  The string representation of valid types of a function
     */
    static const char * XMLType[];

    // Attributes
  private:

    /**
     * The type of the function
     */
    CFunction::Type mType;

    /**
     * The key of the function
     */
    std::string mKey;

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
     *  Specifically it describes what number of substrates and products a
     *  reaction may have to be able to use this function as its rate function.
     *  Consequently the vector has at most two entries (SUBSTRATE and PRODUCT).
     */
    CCopasiVectorNS < CUsageRange > mUsageDescriptions;

    /**
     *  The discription of the parameters of the function.
     *  It describes which parameters need to be passed to the function
     *  for evaluation.
     */
    /** @dia:route 3,2; h,58.2,12.85,56.537,6.51973,52.9592 */
    CFunctionParameters mParameters;

    // Operations
  public:

    /**
     * Create a function of the specified type.
     * Note: the returned object has to be released after use with delete.
     */
    static CFunction *
    createFunction(CFunction::Type type = CFunction::Base);

    /**
     * Create a function of the specified type.
     * Note: the returned object has to be released after use with delete.
     */
    static CFunction *
    createFunction(const CFunction * pFunction);

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
     *  Retrieves the key of the function
     *  @return std::string name
     */
    virtual const std::string & getKey() const;

    /**
     *  Set the name of the function
     *  @param "const string &" name
     */
    virtual bool setName(const std::string& name);

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
    virtual const CFunctionParameters & getParameters() const;

    /**
     *  Retrives the of the usage description of 
     */
    virtual CCopasiVectorNS < CUsageRange > & getUsageDescriptions();
    virtual const CCopasiVectorNS < CUsageRange > & getUsageDescriptions() const;

    /**
     *  Retrieves the position of a parameter in the function call
     *  @param "const string &" name
     *  @return "const unsigned C_INT32" index
     */ 
    //virtual unsigned C_INT32 getParameterPosition(const std::string & name) const;

    /**
     *  Calculates the value of the function
     *  @param const CCallParameters & callParameters
     *  @return "C_FLOAT64" result
     */
    virtual C_FLOAT64 calcValue(const CCallParameterPointers & callParameters) const;

    /**
     * Returns whether the function depends on the given parameter
     * &param const void * parameter
     * &param const CCallParameters & callParameters
     * &param bool dependsOn
     */
    virtual bool dependsOn(const void * C_UNUSED(parameter),
                           const CCallParameterPointers & C_UNUSED(callParameters)) const;

    /**
     *  Adds one usage descriptiont
     *  @param "const string &" usage (SUBSTRATE or PRODUCT)
     *  @param "C_INT32" low lower cardinality
     *  @param "C_INT32" high maximum cardinality
     */
    virtual void addUsage(const std::string& usage, C_INT32 low, C_INT32 high);

    /**
     * Adds the description of one parameter 
     * @param "const string &" name the name of the parameter
     * @param "CFunctionParameter::DataType &" type type of parameter (usually FLOAT64)
     * @param "const string &" usage usage for this paramter (SUBSTRATE, PRODUCT, MODIFIER, PARAMETER)
     * @return bool success
     */
    virtual bool addParameter(const std::string & name,
                              const CFunctionParameter::DataType & type,
                              const std::string & usage);

    virtual void writeMathML(std::ostream & out) const;

  protected:

    /**
     * this adds a Usage range for modifiers that is derived from the parameter list.
     * It is only used for heuristics and will be obsolete once a modifier usage range
     * is saved in the database file.
     */
    void guessModifierUsageRange();
  };

#include "CMassAction.h"
#include "CKinFunction.h"

#endif // COPASI_CFunction
