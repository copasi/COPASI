%{

#include "model/CReaction.h"

%}

#ifndef COPASI_DEBUG

%nodefaultctor
%nodefaultdtor

#endif /* !COPASI_DEBUG */


class CReaction : public CCopasiContainer
{
  public:
#ifdef COPASI_DEBUG
    /**
     * Default constructor
     * @param const std::string & name (default: "NoName")
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReaction(const std::string & name = "NoName",
              const CCopasiContainer * pParent = NULL);

    /**
     * Copy constructor
     * @param "const CReaction &" src
     * @param const CCopasiContainer * pParent (default: NULL)
     */
    CReaction(const CReaction & src,
              const CCopasiContainer * pParent = NULL);


    /**
     *  Destructor
     */
    ~CReaction();

    /**
     * Sets the parent of the metabolite;
     * @param const CCopasiContainer * pParent
     * @return bool success
     */
    virtual bool setObjectParent(const CCopasiContainer * pParent);
#endif /* COPASI_DEBUG */

    /**
     *  Retrieves the key of the reaction
     *  @return std::string key
     */
    virtual const std::string & getKey() const;

    /**
     *  Retrieves the chemical equation of the reaction
     */
    //CChemEq & getChemEq();

    /**
     *  Retrieves the rate function of the reaction
     *  @return "CBaseFunction &"
     */
    const CFunction * getFunction() const;

    /**
     *  Retrieves the flux of the reaction
     *  @return const C_FLOAT64 & flux
     */
    const C_FLOAT64 & getFlux() const;

    /**
     *  Retrieves the scaled flux of the reaction
     *  @return const C_FLOAT64 & scaledFlux
     */
    const C_FLOAT64 & getParticleFlux() const;

    /**
     *  Retrieves whether the reaction is reversible
     *  @return bool
     */
    bool isReversible() const;

    /**
     * Add a substrate to the reaction
     * @param std::string & metabKey
     * @param const C_FLOAT64 & multiplicity (Default 1.0)
     * @return bool success
     */
    bool addSubstrate(const std::string & metabKey,
                      const C_FLOAT64 & multiplicity = 1.0);

    /**
     * Add a product to the reaction
     * @param std::string & metabKey
     * @param const C_FLOAT64 & multiplicity (Default 1.0)
     * @return bool success
     */
    bool addProduct(const std::string & metabKey,
                    const C_FLOAT64 & multiplicity = 1.0);

    /**
     * Add a modifier to the reaction
     * @param std::string & metabKey
     * @param const C_FLOAT64 & multiplicity (Default 1.0)
     * @return bool success
     */
    bool addModifier(const std::string & metabKey,
                     const C_FLOAT64 & multiplicity = 1.0);

    /**
     * Sets the rate function of the reaction
     * @param const string & functionName
     * @return bool success
     */
    bool setFunction(const std::string & functionName);

    /**
     * Sets the rate function of the reaction
     * @param CFunction * pFunction
     * @return bool success
     */
    //bool setFunction(CFunction * pFunction);

    /****************************************************************************************/

    /**
     *  Sets a parameter value
     *  if updateStatus==true the status is also updated to make shure
     *  the value is actually used (instead of a global value that may
     *  have been used before).
     *  if updateStatus==false only the value of the local parameter is
     *  set, even if it is not used
     */
    void setParameterValue(const std::string & parameterName, C_FLOAT64 value,
                           bool updateStatus = true);

    /**
     *  Gets a parameter value
     */
    const C_FLOAT64 & getParameterValue(const std::string & parameterName) const;

    /**
     *  sets a function parameter->metab mapping.
     */
    void setParameterMapping(C_INT32 index, const std::string & key);
    void addParameterMapping(C_INT32 index, const std::string & key);
    void setParameterMapping(const std::string & parameterName, const std::string & key);
    void addParameterMapping(const std::string & parameterName, const std::string & key);

    /**
     *  Clears a function parameter->metab mapping (only for vector parameters).
     */
    void clearParameterMapping(const std::string & parameterName);
    void clearParameterMapping(C_INT32 index);

    const std::vector<std::string> & getParameterMapping(const std::string & parameterName) const;

    /**
     *  Gets the list of kinetic parameter objects of the reaction/function
     */
    CCopasiParameterGroup & getParameters();

    bool isLocalParameter(C_INT32 index) const;
    bool isLocalParameter(const std::string & parameterName) const;

    /***********************/

    /**
     *  Gets the description of what parameters the function expects.
     */
    //const CFunctionParameters & getFunctionParameters() const;

    /**
     *  Sets whether the reaction is reversible
     *  @param bool reversible
     */
    void setReversible(bool reversible);

    /**
     * Calculate the kinetic function and returns the flux
     * @return const C_FLOAT64 & Flux
     */
    const C_FLOAT64 & calculateFlux();

    /**
     * Calculates the kinetic function and returns the particle flux
     * @return const C_FLOAT64 & ParticleFlux
     */
    const C_FLOAT64 & calculateParticleFlux();

    /**
     * Calculate partial derivative of the flux
     * @param C_FLOAT64 * pXi
     * @param const C_FLOAT64 & derivationFactor
     * @param const C_FLOAT64 & resolution (unscaled resolution)
     * @return C_FLOAT64 partial
     */
    C_FLOAT64 calculatePartialDerivative(C_FLOAT64 * pXi,
                                         const C_FLOAT64 & derivationFactor,
                                         const C_FLOAT64 & resolution);

    /**
     *  Retrieves the number of compartments the reaction is acting in.
     *  @return "unsigned C_INT32" the compartment number
     */
    unsigned C_INT32 getCompartmentNumber() const;

    /**
     *  get the largest (smallest) compartment that the reaction touches.
     */
    const CCompartment & getLargestCompartment() const;
    //const CCompartment & getSmallestCompartment() const;

    /**
     * Converts an expression tree into a CFunction object
     * and sets the mapping for the reaction.
     */
    //bool setFunctionFromExpressionTree(CEvaluationTree* tree, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, CFunctionDB* pFunctionDB);

    /**
     * Converts the function tree into the corresponding expression tree.
     * All variable nodes are replaced by object nodes.
     */
    //CEvaluationNode* getExpressionTree();

    /**
     * Sets the SBMLId.
     */
    void setSBMLId(const std::string& id);

    /**
     * Returns a reference to the SBML Id.
     */
    const std::string& getSBMLId() const;


};

#ifndef COPASI_DEBUG

%clearnodefaultctor
%clearnodefaultdtor

#endif /* !COPASI_DEBUG */


