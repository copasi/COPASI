/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CReaction.h,v $
   $Revision: 1.73 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/12/20 17:42:39 $
   End CVS Header */

/**
 *  CReaction class.
 *  Derived from Gepasi's cstep.cpp. (C) Pedro Mendes 1995-2000.
 *
 *  Converted for Copasi by Stefan Hoops 2001
 */

#ifndef COPASI_CReaction
#define COPASI_CReaction

#include <string>
#include <vector>

#include "utilities/CCopasiVector.h"
#include "utilities/CCopasiParameterGroup.h"
#include "function/CFunction.h"
#include "function/CCallParameters.h"
#include "function/CFunctionParameters.h"
#include "CMetab.h"
#include "CChemEq.h"
#include "CChemEqElement.h"
#include "CCompartment.h"

//template < class CType > class CVector;
//class CWriteConfig;
class CReadConfig;

/** @dia:pos 129.788,76.3337 */
class CReaction : public CCopasiContainer
  {
    // Attributes
  private:
    /**
     *  The default scaling factor of a reaction which is 1.
     */
    static C_FLOAT64 mDefaultScalingFactor;

    /**
     *  The key of the reaction
     */
    std::string mKey;

    /**
     *  The chemical equation
     */
    /** @dia:route 4,92; h,80.3628,99.0144,105.075,112.034,129.788 */
    CChemEq mChemEq;

    /**
     *  A pointer to the rate function of the reaction
     */
    const CFunction * mpFunction;

    /**
     *  The flux of the reaction
     */
    C_FLOAT64 mFlux;

    /**
     *  The scaled flux of the reaction
     */
    C_FLOAT64 mParticleFlux;

    /**
     *  A Pointer to the scaling factor for the flux to calculate the particle number
     *  changes. For a single compartment reaction this is the volume of
     *  the compartment
     */
    const C_FLOAT64 * mScalingFactor;

    /**
     *  The unit conversion factor 
     */
    const C_FLOAT64 * mUnitScalingFactor;

    /**
     *  Pointer to the compartment in which the kinetic function is defined.
     *  (the kinetic function gives a rate as concentration/time unit. If there is
     *  more than one compartment involved it must be specified to which volume
     *  the concentration change refers)
     */
    /** @dia:route 9,23; h,155.606,36.603,165.837,83.8337,159.088 */
    const CCompartment * mpFunctionCompartment;

    /**
     *  This describes the mapping of the Metabs and Params to the function parameters.
     *  Here are the pointers to the actual objects and values.
     */
    CFunctionParameterMap mMap;

    /**
     *  This describes the mapping of the Metabs to the function parameters. Here the
     *  keys of the metabolites (as in the chemical equation) are stored.
     */
    std::vector< std::vector< std::string > > mMetabKeyMap;

    /**
     *  This is a list of parameter objects.
     */
    CCopasiParameterGroup mParameters;

    // Operations

  public:
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
     *  Delete
     */
    void cleanup();

    /**
     *  Assignment operator
     */ 
    //CReaction & operator=(const CReaction & rhs);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return mFail
     *  @see mFail
     */
    C_INT32 load(CReadConfig & configbuffer);

    /**
     *  Retrieves the key of the reaction
     *  @return std::string key
     */
    virtual const std::string & getKey() const;

    /**
     *  Retrieves the chemical equation of the reaction
     */
    const CChemEq & getChemEq() const;
    CChemEq & getChemEq();

    /**
     *  Retrieves the rate function of the reaction
     *  @return "CBaseFunction &"
     */
    const CFunction & getFunction() const;

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
     *  Sets the name of the reaction
     *  @param "const string &" name
     *  @return bool success
     */
    bool setName(const std::string & name);

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
    bool setFunction(CFunction * pFunction);

    //****************************************************************************************

    /**
     *  Sets a parameter value
     */
    void setParameterValue(const std::string & parameterName, C_FLOAT64 value);

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

    void setParameterMappingVector(const std::string & parameterName,
                                   const std::vector<std::string> & keys);

    /**
     *  Clears a function parameter->metab mapping (only for vector parameters).
     */
    void clearParameterMapping(const std::string & parameterName);
    void clearParameterMapping(C_INT32 index);

    const std::vector< std::vector<std::string> > getParameterMappingName() const;

    const std::vector< std::vector<std::string> > & getParameterMappings() const
      {return mMetabKeyMap;}

    //std::vector<const CMetab *> getParameterMappingMetab(const std::string & parameterName) const;
    std::vector<const CMetab *> getParameterMappingMetab(C_INT32 index) const;

    /**
     *  Gets the list of kinetic parameter objects of the reaction/function
     */
    const CCopasiParameterGroup & getParameters() const;

    /**
     *  Gets the list of kinetic parameter objects of the reaction/function
     */
    CCopasiParameterGroup & getParameters();

    /**
     *  Gets the description of what parameters the function expects.
     */
    const CFunctionParameters & getFunctionParameters() const;

    /**
     *  Sets whether the reaction is reversible
     *  @param bool reversible
     */
    void setReversible(bool reversible);

    /**
     *  Compile the reaction, i.e., links the metabolites and parameters with the
     *  rate function. The connection of the reaction and the function parameter mapping
     *  to the actual metabolites is established (before compile() the chemical equation
     *  and the reaction only hold the names of the metabolites).
     *  @param "CCopasiVectorNS < CCompartment > &" compartments
     */
    void compile(/*const CCopasiVectorNS < CCompartment > & compartments*/);

    /**
     *  Calculate the kinetic function
     *  @return C_FLOAT64 velocity
     */
    C_FLOAT64 calculate();

    /**
     * Calculate partial derivative of the flux 
     * @param C_FLOAT64 & xi
     * @param const C_FLOAT64 & derivationFactor
     * @param const C_FLOAT64 & resolution (unscaled resolution)
     * @return C_FLOAT64 partial 
     */
    C_FLOAT64 calculatePartialDerivative(C_FLOAT64 & xi,
                                         const C_FLOAT64 & derivationFactor,
                                         const C_FLOAT64 & resolution);

    /**
     * Sets the Compartment related to the kinetic function
     */
    void setCompartment(const CCompartment* comp);

    /**
     * Gets the Compartment related to the kinetic function
     */
    const CCompartment* getCompartment() const;

    /**
     *  Retrieves the number of compartments the reaction is acting in.
     *  @return "unsigned C_INT32" the compartment number
     */
    unsigned C_INT32 getCompartmentNumber() const;

    /**
     *  get the largest (smallest) compartment that the reaction touches.
     */
    const CCompartment & getLargestCompartment() const;
    const CCompartment & getSmallestCompartment() const;

    const CFunctionParameterMap & getFunctionParameterMap() const {return mMap;}

    C_INT32 getSubstrateMolecularity() const;
    C_INT32 getProductMolecularity() const;
    C_INT32 getModifierMolecularity() const;

    /**
     * insert operator
     */
    friend std::ostream & operator<<(std::ostream &os, const CReaction & d);

    /**
     * Retrieve the list of CallParameterObjects()
     */ 
    //

    const CCallParameterPointers & getCallParameterObjects() const;
  private:

    /**
     *  used by compile(). It finds the reference to the transient concentration in the
     *  metabolite and tells mMap about it.
     */ 
    //void setParameterMapping(const std::string & parameterName, const CMetab & metab);

    /**
     *  It set the key for a parameter mapping
     *  metabolite and tells mKeyMap about it.
     */ 
    //    void setParameterMappingKey(const std::string & parameterName, const CMetab & metab);

    /**
     *  used by compile(). It finds the reference to the transient concentration in the
     *  metabolite and tells mMap about it.
     */ 
    //void addParameterMapping(const std::string & parameterName, const CMetab & metab);

    /**
     *  It adds a key to a Metabolite to the parameter map.
     */ 
    //    void addParameterMappingKey(const std::string & parameterName, const CMetab & metab);

    /**
     *
     */
    C_INT32 loadOld(CReadConfig & configbuffer);

    /**
     *  Returns the max number of elements for the specified usage
     *  @param "const string" & usage
     *  @return unsigned C_INT32 size
     */
    unsigned C_INT32 usageRangeSize(const std::string & usage) const;

    /**
     * Sets the scaling factor of the for the fluxes
     */
    void setScalingFactor();

    void initObjects();

    /**
     * creates the mParamters List of CParameter objects.
     * mMap needs to be initialized before.
     */
    void initializeParameters();

    /**
     * sets the pointers in mMap to the kinetic parameters. This is needed
     * by initializeParameters() and the copy constructor.
     */
    void compileParameters();

    /**
     * Initializes the mMetabNameMap vectors to the right size.
     */
    void initializeMetaboliteNameMap();
  };

#endif // COPASI_CReaction
