/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModel.h,v $
   $Revision: 1.87 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/09 12:27:28 $
   End CVS Header */

// cmodel.h : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COPASI_CModel
#define COPASI_CModel

#include <map>
#include <vector>
#include <set>
#include <string>

#include "CReaction.h"
#include "CMoiety.h"
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"
#include "report/CCopasiContainer.h"

class CCompartment;
class CState;
class CStateX;
class CCallbackHandler;

/** @dia:pos 177.081,30.2423 */
class CModel : public CCopasiContainer
  {
  public:
    /**
     * Enum of valid volume units
     */
    enum VolumeUnit {m3 = 0, l, ml, microl, nl, pl, fl};

    /**
     * String representation of valid volume units
     */
    static const char * VolumeUnitName[];

    /**
     *  Enum of valid time units
     */
    enum TimeUnit {d = 0, h, m, s, ms, micros, ns, ps, fs};

    /**
     * String representation of valid time units
     */
    static const char * TimeUnitName[];

    /**
     *  Enum of valid quantitye units
     */
    enum QuantityUnit {Mol = 0, mMol, microMol, nMol, pMol, fMol, number};

    /**
     * String representation of valid quantity units
     */
    static const char * QuantityUnitName[];

    //Attributes
  public:
    /** @dia:pos 129.758,65.0298 */
    class CLinkMatrixView
      {
      public:
        typedef C_FLOAT64 elementType;

      private:
        const CMatrix< C_FLOAT64 > & mA;
        /** @dia:route 39,3; h,108.729,65.6961,119.243,65.7298,129.758 */
        const CCopasiVector< CMetab > & mIndependent;
        static const elementType mZero;
        static const elementType mUnit;

      public:
        /**
         * Default constructor
         * @param const CMatrix< C_FLOAT64 > & A
         * @param const CCopasiVectorN< CMetab > & independent
         */
        CLinkMatrixView(const CMatrix< C_FLOAT64 > & A,
                        const CCopasiVector< CMetab > & independent);

        /**
         * Destructor.
         */
        ~CLinkMatrixView();

        /**
         * Assignement operator
         * @param const CLinkMatrixView & rhs
         * @return CLinkMatrixView & lhs
         */
        CLinkMatrixView & operator = (const CLinkMatrixView & rhs);

        /**
         * The number of rows of the matrix.
         * @return unsigned C_INT32 rows
         */
        unsigned C_INT32 numRows() const;

        /**
         * The number of columns of the matrix
         * @return unsigned C_INT32 cols
         */
        unsigned C_INT32 numCols() const;

        /**
         * Retrieve a matrix element  using the c-style indexing.
         * @param const unsigned C_INT32 & row
         * @param const unsigned C_INT32 & col
         * @return elementType & element
         */
        inline elementType & operator()(const unsigned C_INT32 & row,
                                        const unsigned C_INT32 & col) const
          {
            if (row >= mIndependent.size())
              return const_cast< elementType & >(mA(row - mIndependent.size(), col));
            else if (row != col)
              return const_cast< elementType & >(mZero);
            else
              return const_cast< elementType & >(mUnit);
          }

        /**
         * Output stream operator
         * @param ostream & os
         * @param const CLinkMatrixView & A
         * @return ostream & os
         */
        friend std::ostream &operator<<(std::ostream &os,
                                        const CLinkMatrixView & A);
      };

    /** @dia:pos 25.9437,20.8602 */
    class CStateTemplate
      {
        // Attributes
      private:
        /**
         * The list of template variables.
         */
        std::vector< std::pair< std::string, std::string > * > mList;

        /**
         * A map to allow finding the object a state variable relates to.
         */
        std::map< std::string, const std::string * > mKeyMap;

        /**
         * A map to allow finding the state variable which represents the 
         * object. 
         */
        std::map< std::string, const std::string * > mObjectMap;

        // Operations
      public:
        /**
         * Constructor
         */
        CStateTemplate();

        /**
         * Destructor
         */
        ~CStateTemplate();

        /**
         * Cleanup
         */
        bool cleanup();

        /**
         * Add a state variable representing an object to the state template.
         * @param const std::string & objectKey
         * @return bool success
         */
        bool add(const std::string & objectKey);

        /**
         * Retrieve the object key the state variable 'key' refers to.
         * @param const std::string & key
         * @return std::string objectKey
         */
        std::string getObjectKey(const std::string & key) const;

        /**
         * Retrieve the state variables key which helds the objects state.
         * @param const std::string & objectKey
         * @return std::string key
         */
        std::string getKey(const std::string & objectKey) const;

        /**
         * Retrieve the size of the state template.
         * @return  unsigned C_INT32 size
         */
        unsigned C_INT32 size() const;

        /**
         * Retreive a state variable descriptions
         * @param const unsigned C_INT32 & index
         * @return std::pair< std::string,std::string >
         */
        std::pair< std::string, std::string >
        operator[](const unsigned C_INT32 & index) const;
      };

  private:
    /**
     *  key of the model
     */
    std::string mKey;

    /**
     *  Comments
     */
    std::string mComments;

    /**
     * The volume unit used in the Model
     */
    std::string mVolumeUnit;

    /**
     * The time unit used in the Model
     */
    std::string mTimeUnit;

    /**
     * The quantity unit used in the Model
     */
    std::string mQuantityUnit;

    /**
     *  for array of compartments
     *  @supplierCardinality 0..*
     *  @associates <{CCompartment}>
     */
    /** @dia:route 2,18; h,155.606,34.703,166.344,36.1423,177.081 */
    CCopasiVectorNS < CCompartment > mCompartments;

    /**
     *  Vector of reference to metabolites
     */
    /** @dia:route 29,44; h,108.729,61.6961,172.66,46.7423,177.081 */
    CCopasiVector< CMetab > mMetabolites;

    /**
     *  Vector of reference to metabolites in reduced model representation
     */
    /** @dia:route 17,44; h,108.729,56.6961,172.66,46.7423,177.081 */
    CCopasiVector< CMetab > mMetabolitesX;

    /**
     *  Vector of reference to independent metabolites
     */
    /** @dia:route 21,44; h,108.729,58.2961,172.66,46.7423,177.081 */
    CCopasiVector< CMetab > mMetabolitesInd;

    /**
     *  Vector of reference to dependent metabolites
     */
    /** @dia:route 25,44; h,108.729,59.8961,172.66,46.7423,177.081 */
    CCopasiVector< CMetab > mMetabolitesDep;

    /**
     *  for array of steps
     */
    /** @dia:route 154,29; h,177.081,90.7423,168.084,86.4337,159.088 */
    CCopasiVectorNS< CReaction > mSteps;

    /**
     *  Vector of reference to reactions in reduced model representation.
     */
    /** @dia:route 154,33; h,177.081,90.7423,168.084,88.0337,159.088 */
    CCopasiVectorN< CReaction > mStepsX;

    /**
     *  Vector of reference to independend reactions.
     */
    /** @dia:route 154,37; h,177.081,90.7423,168.084,89.6337,159.088 */
    CCopasiVectorN< CReaction > mStepsInd;

    /**
     *  Vector of fluxes of the reactions.
     *  Note: The fluxes are the order corresponding to mStepX
     */
    CVector< const C_FLOAT64 * > mFluxes;
    CVector< const C_FLOAT64 * > mFluxesX;
    CVector< const C_FLOAT64 * > mParticleFluxes;
    CVector< const C_FLOAT64 * > mParticleFluxesX;

    /**
     * The initial time for modeling (default = 0)
     */
    C_FLOAT64 mInitialTime;

    /**
     * The actual time for modeling (default = 0)
     */
    C_FLOAT64 mTime;

    /**
     *  Transition time 
     */
    C_FLOAT64 mTransitionTime;

    /**
     *  for array of conserved moieties
     */
    /** @dia:route 178,7; h,177.081,100.342,168.006,136.562,80.2566 */
    CCopasiVectorN< CMoiety > mMoieties;

    /**
     *   Stoichiometry Matrix
     */
    CMatrix< C_FLOAT64 > mStoi;

    /**
     *   Reduced Stoichiometry Matrix
     */
    CMatrix< C_FLOAT64 > mRedStoi;

    /**
     *   The Matrix which stores the LU-Decomposition
     */ 
    // CMatrix< C_FLOAT64 > mLU;

    /**
     * Vector for storing the row interchanges during LU-Decomposition
     */
    CVector< unsigned C_INT32 > mRowLU;

    /**
     * Vector for storing the column interchanges during LU-Decomposition
     */
    CVector< unsigned C_INT32 > mColLU;

    /**
     *   This matrix stores L
     */
    CMatrix < C_FLOAT64 > mL;

    /**
     *   This is used to return a view to L
     */
    /** @dia:route 98,2; h,177.081,68.3423,163.695,65.0298,150.308 */
    CLinkMatrixView mLView;

    /**
     *  Factor to convert from quantity to particle number
     *  taking into account the unit for substance quantities
     */
    C_FLOAT64 mQuantity2NumberFactor;

    /**
     *  Factor to convert from  particle number to quantity
     *  taking into account the unit for substance quantities
     */
    C_FLOAT64 mNumber2QuantityFactor;

    /**
     * The state template for the model
     */
    /** @dia:route 12,2; h,177.081,33.7423,112.487,20.8602,47.8937 */
    CStateTemplate mStateTemplate;

    /**
     * indicates whether a recalculation of the stoichiometry matrix decomposition is 
     * necessary
     */
    bool mCompileIsNecessary;

    CCallbackHandler * mpCompileHandler;

  public:
    /**
     *  Default constructor
     */
    CModel();

    /**
     *  Copy construnctor
     *  @param "const CModel &" src
     */
    CModel(const CModel & src);

    /**
     * Destructor
     */
    ~CModel();        // destructor (deallocation code here)

    /**
     * Cleanup 
     */
    void cleanup();

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    C_INT32 load(CReadConfig &configBuffer);

    /**
     *  This function must be called to initialize the vector of Metabolites
     *  after finishing adding metabolites to compartments.
     */
    void initializeMetabolites();

    /**
     *  This must be called whenever something is changed in the model
     *  that would make it necessary to recalculate the matrix decomposition
     */
    void setCompileFlag(bool flag = true);

    /**
     *  Compile the model if necessary
     */
    bool compileIfNecessary();
    bool forceCompile();

    /**
     *  Build the Stoichiometry Matrix from the chemical equations of the steps
     */
    void buildStoi();

    /**
     *  Build the core of the link matrix L
     *  @param const CMatrix< C_FLOAT64 > & LU
     */
    void buildL(const CMatrix< C_FLOAT64 > & LU);

    /**
     *  LU-Decomposition of the stoichiometry matrix
     *  @param CMatrix< C_FLOAT64 > & LU
     */
    void lUDecomposition(CMatrix< C_FLOAT64 > & LU);

    /**
     *  Set the status of the metabolites
     *  @param const CMatrix< C_FLOAT64 > & LU
     */
    void setMetabolitesStatus(const CMatrix< C_FLOAT64 > & LU);

    /**
     *  Build the Reduced Stoichiometry Matrix from the LU decomposition
     */
    void buildRedStoi();

    /**
     *  Build the Moities based on the LU decomposition
     */
    void buildMoieties();

    /**
     *  This calculate the right hand side (ydot) of the ODE for LSODA
     */ 
    //void lSODAEval(C_INT32 n, C_FLOAT64 t, C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     * Return the metabolites of this model
     * @return CCopasiVectorN< CMetab > & metabolites
     */
    const CCopasiVector< CMetab > & getMetabolites() const;
    CCopasiVector< CMetab > & getMetabolites();

    /**
     * Retrieves the vector of independent metabolites.
     * @return vector < CMetab * > metabolites
     */
    CCopasiVector< CMetab > & getMetabolitesInd();

    /**
     * Retrieves the vector of dependent metabolites.
     * @return vector < CMetab * > metabolites
     */
    CCopasiVector< CMetab > & getMetabolitesDep();

    /**
     * Retrieves the vector of metabolites at it is used in the reduced model.
     * @return const CCopasiVectorN< CMetab > &metabolites
     */
    const CCopasiVector< CMetab > & getMetabolitesX() const;

    /**
     *  Get the number of total metabolites
     *  @return C_INT32 totMetab
     */
    unsigned C_INT32 getTotMetab() const;

    /**
     *  Get the number of total metabolites
     *  @return unsigned C_INT32 totMetab
     */
    unsigned C_INT32 getIntMetab() const;

    /**
     *  Get the number of internal metabolites
     *  @return unsigned C_INT32 dimension
     */
    unsigned C_INT32 getIndMetab() const;

    /**
     *  Get the number of dependent metabolites
     *  @return unsigned C_INT32 dimension
     */
    unsigned C_INT32 getDepMetab() const;

    /**
     *  Set the transition times for all internal metabolites and the
     *  transistion time of the model.
     */
    void setTransitionTimes();

    /**
     * Return the vector of reactions
     * @return CCopasiVectorNS <CReaction> & reactions
     */
    CCopasiVectorNS < CReaction > & getReactions();

    /**
     * Return the vector of reactions
     * @return const CCopasiVectorS <CReaction> & reactions
     */
    const CCopasiVectorNS < CReaction > & getReactions() const;

    /**
     * Retreives the vector of steps in the order used by the reduced model.
     * @return const CCopasiVectorN< CReaction > &
     */
    const CCopasiVectorN< CReaction > & getReactionsX() const;

    // Added by Yongqun He
    /**
     * Get the total steps
     * @return unsigned C_INT32 total steps;
     */
    unsigned C_INT32 getTotSteps() const;

    /**
     *  Get the dimension of the reduced problem
     *  @return unsigned C_INT32 dimension
     */ 
    //unsigned C_INT32 getDimension() const;

    /**
     * Return the comments of this model Wei Sun 
     * @return string
     */
    const std::string & getComments() const;

    /**
     * Return the key of this model
     * @return string key
     */
    const std::string & getKey() const;

    /**
     * Return the title of this model
     * @return string
     */ 
    //std::string getTitle() const;

    /**
     * Set the title of this model
     * @param "const string &" title title for this model
     */
    bool setTitle(const std::string &title);

    /**
     * Set the title of this model
     * @param "const string &" comments comments for this model
     */
    void setComments(const std::string &comments);

    /**
     * Set the start time for modeling
     * @param const C_FLOAT64 & time
     */
    void setInitialTime(const C_FLOAT64 & time);

    /**
     * Retreive the initial time
     * @return const C_FLOAT64 & time
     */
    const C_FLOAT64 & getInitialTime() const;

    /**
     * Set the actual model time
     * @param const C_FLOAT64 & time
     */
    void setTime(const C_FLOAT64 & time);

    /**
     * Retreive the actual model time
     * @return const C_FLOAT64 & time
     */
    const C_FLOAT64 & getTime() const;

    /**
     * Return the compartments of this model
     * @return CCopasiVectorNS < CCompartment > *
     */
    CCopasiVectorNS < CCompartment > & getCompartments();

    /**
     * Return the compartments of this model
     * @return const CCopasiVectorNS < CCompartment > *
     */
    const CCopasiVectorNS < CCompartment > & getCompartments() const;

    /**
     *  Get the Stoichiometry Matrix of this Model
     */
    const CMatrix < C_FLOAT64 > & getStoi() const;

    /**
     *  Get the Reduced Stoichiometry Matrix of this Model
     */
    const CMatrix < C_FLOAT64 >& getRedStoi() const;

    /**
     * Return the mMoieties of this model 
     * @return CCopasiVectorN < CMoiety > & 
     */
    const CCopasiVectorN < CMoiety > & getMoieties() const;

    /**
     * Returns the index of the metab
     */
    C_INT32 findMetabByName(const std::string & Target) const;

    /**
     * Returns the index of the Moiety
     */
    C_INT32 findMoiety(std::string &Target) const;

    /**
     * Returns the mStepsX of this model
     * @return const CCopasiVectorN< CReaction > & 
     */
    const CCopasiVectorN< CReaction > & getStepsX() const;

    /**
     * Get the LU decomposition matrix of this model
     * @return const TNT::Matrix < C_FLOAT64 > & LU
     */ 
    //    const CMatrix < C_FLOAT64 > & getmLU() const;

    /**
     * Get the link matrix L of the relation: Stoi = L * RedStoi
     * @return const CLinkMatrixView L
     */
    const CLinkMatrixView & getL() const;

    /**
     * Get the initial state of the model, i.e., initial concentrations 
     * and volumes.
     * @return CState initialState
     */
    CState getInitialState() const;

    /**
     * Get the initial state of the model, i.e., initial concentrations 
     * and volumes in reduced model representation.
     * @return CStateX initialStateX
     */
    CStateX getInitialStateX() const;

    /**
     * Set the initial state of the model, i.e., initial concentrations 
     * and volumes.
     * @param const CState * initialState
     */
    void setInitialState(const CState * state);

    /**
     * Set the initial state of the model, i.e., initial concentrations 
     * and volumes in reduced model representation.
     * @param const CStateX * initialStateX
     */
    void setInitialStateX (const CStateX * state);

    /**
     * Calculate the rates of the reaction in the given state.
     * The parameter rates must at least provide space mSteps.size() double
     * &param CState * state (input)
     * &param  C_FLOAT64 * rates (output)
     */
    void getRates(const CState * state, C_FLOAT64 * rates);

    /**
     * Calculate the rates of the reaction in the given state in 
     * reduced model representation.
     * The parameter rates must at least provide space mStepsX.size() double
     * &param CStateX * stateX (input)
     * &param  C_FLOAT64 * rates (output)
     */
    void getRatesX(const CStateX * state, C_FLOAT64 * rates);

    /**
     * Calculate the changes of particles numbers of the metabolites 
     * in the given state.
     * The parameter derivatives must at least provide space for
     * state->getVariableNumberSize() double
     * &param CState * state (input)
     * &param CVector< C_FLOAT64 > & derivatives (output)
     */
    void getDerivatives_particles(const CState * state, CVector< C_FLOAT64 > & derivatives);

    /**
     * Calculate the changes of particles numbers of the metabolites 
     * in the given state in reduced model representation.
     * The parameter derivatives must at least provide space for
     * state->getVariableNumberSize() double
     * &param CStateX * stateX (input)
     * &param CVector< C_FLOAT64 > & derivatives (output)
     */
    void getDerivativesX_particles(const CStateX * state, CVector< C_FLOAT64 > & derivatives);

    /**
     * Set the unit for volumes. If copasi recognises 
     * the unit the conversion factors are set accordingly 
     * and true is returned.
     * @param const std::string & name
     * @return bool success
     */
    bool setVolumeUnit(const std::string & name);

    /**
     * Set the unit for volumes. If copasi recognises 
     * the unit the conversion factors are set accordingly 
     * and true is returned.
     * @param const CModel::VolumeUnit & unit
     * @return bool success
     */
    bool setVolumeUnit(const CModel::VolumeUnit & unit);

    /**
     * Get the unit for volumes
     * @return std::string volumeUnit
     */
    std::string getVolumeUnit() const;

    /**
     * Set the unit for time. If copasi recognises 
     * the unit the conversion factors are set accordingly 
     * and true is returned.
     * @param const std::string & name
     * @return bool success
     */
    bool setTimeUnit(const std::string & name);

    /**
     * Set the unit for time. If copasi recognises 
     * the unit the conversion factors are set accordingly 
     * and true is returned.
     * @param const const CModel::TimeUnit & unit
     * @return bool success
     */
    bool setTimeUnit(const CModel::TimeUnit & unit);

    /**
     * Get the unit for time
     * @return std::string timeUnit
     */
    std::string getTimeUnit() const;

    /**
     * Set the unit for quantities. If copasi recognises 
     * the unit the conversion factors are set accordingly 
     * and true is returned.
     * @param const std::string & name
     * @return bool success
     */
    bool setQuantityUnit(const std::string & name);

    /**
     * Set the unit for quantities. If copasi recognises 
     * the unit the conversion factors are set accordingly 
     * and true is returned.
     * @param const CModel::QuantityUnit & unit
     * @return bool success
     */
    bool setQuantityUnit(const CModel::QuantityUnit & unit);

    /**
     * Get the unit for quantities
     * @return std::string quantityUnit
     */
    std::string getQuantityUnit() const;

    /**
     *  Get the conversion factor quantity -> number
     */
    const C_FLOAT64 & getQuantity2NumberFactor() const;

    /**
     *  Get the conversion factor number -> quantity
     */
    const C_FLOAT64 & getNumber2QuantityFactor() const;

    /**
     * Add a metabolite to the model
     * @param const std::string & name
     * @param const std::string & compartment 
     * @param const C_FLOAT64 & iconc (default 1.0)
     * @param const CMetab::Status & status (default CMetab::METAB_VARIABL)
     * @return bool success (false if failed)
     * @see CMetab for more information
     */
    CMetab* createMetabolite(const std::string & name,
                             const std::string & compartment,
                             const C_FLOAT64 & iconc = 1.0,
                             const CMetab::Status & status = CMetab::METAB_VARIABLE);

    /* Remove a metabolite from the model */
    bool removeMetabolite(const std::string & key);

    /* Retreives list of Reactions Keys which are dependent on the Metabolite */
    std::set<std::string> listReactionsDependentOnMetab(const std::string & key);

    /* Retreives list of Reactions Keys which are dependent on the Function */
    std::set<std::string> listReactionsDependentOnFunction(const std::string & key);

    /* Retreives list of Reactions Keys which are dependent on the Compartment*/
    std::set<std::string> listReactionsDependentOnCompartment(const std::string & key);

    /**
     * Add a compartment to the model
     * @param const std::string &name
     * @param const C_FLOAT64 & volume (default 1.0)
     * @return bool success (false if failed)
     */
    CCompartment* createCompartment(const std::string & name,
                                    const C_FLOAT64 & volume = 1.0);

    /* Remove a Compartment from the model */
    bool removeCompartment(const std::string & key);

    /**
     * Add a new rection to the model
     * @param const std::string &name
     * @return bool success (false if failed)
     */
    CReaction* createReaction(const std::string &name);

    /**
     * Add a new rection to the model
     * @param const CReaction & reaction
     * @return bool success (false if failed)
     */
    bool addReaction(const CReaction & reaction);

    /* Remove a reaction from the model*/
    bool removeReaction(const std::string & key);

    /**
     * Retrieve the metabolite permutation vector
     * @return CVector< unsigned C_INT32 > & permutation
     */
    const CVector< unsigned C_INT32 > & getMetabolitePermutation() const;

    /**
     * Retrieve the reaction permutation vector
     * @return const CVector<unsigned C_INT32> & permutation
     */
    const CVector< unsigned C_INT32 > & getReactionPermutation() const;

    /**
     * Calculates the particle numbers of the dependent
     * metabolites for the given reduced model stateX and updates the state
     * @param CStateX & stateX
     */
    void updateDepMetabNumbers (const CStateX & stateX) const;

    /**
     * Set the transient concentrations and volumes according to the
     * given state.
     * @param const CState * state
     */
    void setState(const CState * state);

    /**
     * Set the transient concentrations and volumes according to the
     * given stateX in reduced model representation.
     * @param const CState * stateX
     */
    void setStateX(const CStateX * state);

    /**
     * Retreive the state template
     * @return const CModel::CStateTemplate & stateTemplate
     */
    const CModel::CStateTemplate & getStateTemplate() const;

    bool hasReversibleReaction() const;

    /**
     * set Progress bar handler
     **/
    void setCompileHandler(CCallbackHandler* pHandler);

    /**
     * get address of progress bar handler
     **/
    CCallbackHandler* getCompileHandlerAddr();

  private:

    bool compile();

    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();

    /**
     * Find the unit the string refers to.
     * @param const std::string & name 
     * @param const char ** units (list of valid units)
     * @param const unsigned C_INT32 unique (minimum characters being unique)
     * @return unsigned C_INT32 unit
     */
    static unsigned C_INT32 unitCompare(const std::string & name,
                                        const char ** units,
                                        const unsigned C_INT32 unique);

    /**
     * Build the state template for the model.
     * @return bool success
     */
    bool buildStateTemplate();
  };

#endif // CModel
