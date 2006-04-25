/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModel.h,v $
   $Revision: 1.116 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/04/25 13:20:34 $
   End CVS Header */

#ifndef COPASI_CModel
#define COPASI_CModel

#include <map>
#include <vector>
#include <set>
#include <string>

#include "copasi.h"
#include "CState.h"
#include "CReaction.h"
#include "CMoiety.h"
#include "CModelValue.h"

#include "utilities/CVector.h"
#include "utilities/CMatrix.h"
#include "report/CCopasiContainer.h"

class CCompartment;
class CProcessReport;

class CModel : public CModelEntity
  {
  public:
    /**
     * Enum of valid volume units
     */
    enum VolumeUnit {m3 = 0, l, ml, microl, nl, pl, fl};

    /**
     * String representation of valid volume units
     */
    static const char * VolumeUnitNames[];

    /**
     *  Enum of valid time units
     */
    enum TimeUnit {d = 0, h, min, s, ms, micros, ns, ps, fs};

    /**
     * String representation of valid time units
     */
    static const char * TimeUnitNames[];

    /**
     *  Enum of valid quantitye units
     */
    enum QuantityUnit {Mol = 0, mMol, microMol, nMol, pMol, fMol, number};

    /**
     * String representation of valid quantity units
     */
    static const char * QuantityUnitNames[];

    //Attributes
  public:
    class CLinkMatrixView
      {
      public:
        typedef C_FLOAT64 elementType;

      private:
        const CMatrix< C_FLOAT64 > & mA;
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

  private:
    CState mInitialState;

    CState mCurrentState;

    /**
     * The state template for the model
     */
    CStateTemplate mStateTemplate;

    /**
     *  Comments
     */
    std::string mComments;

    /**
     * The volume unit used in the Model
     */
    VolumeUnit mVolumeUnit;

    /**
     * The time unit used in the Model
     */
    TimeUnit mTimeUnit;

    /**
     * The quantity unit used in the Model
     */
    QuantityUnit mQuantityUnit;

    /**
     *  for array of compartments
     *  @supplierCardinality 0..*
     *  @associates <{CCompartment}>
     */
    CCopasiVectorNS < CCompartment > mCompartments;

    /**
     *  Vector of reference to metabolites
     */
    CCopasiVector< CMetab > mMetabolites;

    /**
     *  Vector of reference to metabolites in reduced model representation
     */
    CCopasiVector< CMetab > mMetabolitesX;

    /**
     *  Vector of reference to independent metabolites
     */
    CCopasiVector< CMetab > mMetabolitesInd;

    /**
     *  Vector of reference to dependent metabolites
     */
    CCopasiVector< CMetab > mMetabolitesVar;

    /**
     *  for array of steps
     */
    CCopasiVectorNS< CReaction > mSteps;

    /**
     *  Vectors of fluxes of the reactions.
     */
    CVector< C_FLOAT64 > mParticleFluxes;

    /**
     *  vector of non concentration values in the model
     */
    CCopasiVectorN< CModelValue > mValues;

    /**
     *  Transition time 
     */
    C_FLOAT64 mTransitionTime;

    /**
     *  for array of conserved moieties
     */
    CCopasiVector< CMoiety > mMoieties;

    /**
     *   Stoichiometry Matrix
     */
    CMatrix< C_FLOAT64 > mStoi;

    /**
     *   Stoichiometry Matrix
     */
    CMatrix< C_FLOAT64 > mStoiReordered;

    /**
     *   Reduced Stoichiometry Matrix
     */
    CMatrix< C_FLOAT64 > mRedStoi;

    /**
     * The elasticity matrix d(Flux_i)/dx_j
     */
    CMatrix< C_FLOAT64 > mElasticities;

    /**
     * Vector for storing the row interchanges during LU-Decomposition
     */
    CVector< unsigned C_INT32 > mRowLU;

    /**
     * Vector for storing the column interchanges during LU-Decomposition
     */ 
    //    CVector< unsigned C_INT32 > mColLU;

    /**
     *   This matrix stores L
     */
    CMatrix < C_FLOAT64 > mL;

    /**
     *   This is used to return a view to L
     */
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
     * indicates whether a recalculation of the stoichiometry matrix decomposition is 
     * necessary
     */
    bool mCompileIsNecessary;

    CProcessReport * mpCompileHandler;

    /**
     * The number of fixed metabs in the model
     */
    C_INT32 mNumFixed;

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
     * Converts the set of reactions to a set of reaction where all reactions are irreversible.
    */
    bool convert2NonReversible();

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
     * Compile the model if necessary
     * @return bool success
     */
    bool compileIfNecessary();

    /**
     * Force a compile the model.
     * @return bool success
     */
    bool forceCompile();

    /**
     *  Build the Stoichiometry Matrix from the chemical equations of the steps
     */
    void buildStoi();

    /**
     *  Build the core of the link matrix L
     *  @param const CMatrix< C_FLOAT64 > & LU
     */
    void buildLinkZero();

    /**
     *  Build the core of the link matrix L
     *  @param const CMatrix< C_FLOAT64 > & LU
     */
    void buildL(const CMatrix< C_FLOAT64 > & LU);

#ifdef XXXX
    /**
     *  LU-Decomposition of the stoichiometry matrix
     *  @param CMatrix< C_FLOAT64 > & LU
     */
    void lUDecomposition(CMatrix< C_FLOAT64 > & LU);
#endif // XXXX

    /**
     *  Set the status of the metabolites
     */
    void setMetabolitesStatus();

    /**
     *  Build the Reduced Stoichiometry Matrix from the LU decomposition
     */
    void buildRedStoi();

    /**
     *  Build the Moities based on the LU decomposition
     */
    void buildMoieties();

  private:
    /**
     *  compute the actual initial value of all moieties 
     *  (from the initial values of the metabolites).
     */
    void updateMoietyValues();

  public:
    /**
     *  This calculate the right hand side (ydot) of the ODE for LSODA
     */ 
    //void lSODAEval(C_INT32 n, C_FLOAT64 t, C_FLOAT64 * y, C_FLOAT64 * ydot);

    //********** Metabs *****************************

    /**
     * Return the metabolites of this model
     * @return CCopasiVectorN< CMetab > & metabolites
     */
    const CCopasiVector< CMetab > & getMetabolites() const;
    CCopasiVector< CMetab > & getMetabolites();

    /**
     * Retrieves the vector of metabolites at it is used in the reduced model.
     * @return const CCopasiVectorN< CMetab > &metabolites
     */
    const CCopasiVector< CMetab > & getMetabolitesX() const;
    CCopasiVector< CMetab > & getMetabolitesX();

    /**
     * Retrieves the vector of independent metabolites.
     * @return vector < CMetab * > metabolites
     */
    const CCopasiVector< CMetab > & getMetabolitesInd() const;

    /**
     * Retrieves the vector of variable metabolites.
     * This is a subset of MetabolitesX
     * @return vector < CMetab * > metabolites
     */
    const CCopasiVector< CMetab > & getVariableMetabolites() const;

    /**
     *  Get the number of total metabolites
     *  @return C_INT32 totMetab
     */
    unsigned C_INT32 getNumMetabs() const;

    /**
     *  Get the number of variable metabolites
     *  @return unsigned C_INT32 totMetab
     */
    unsigned C_INT32 getNumVariableMetabs() const;

    /**
     *  Get the number of internal metabolites
     *  @return unsigned C_INT32 dimension
     */
    unsigned C_INT32 getNumIndependentMetabs() const;

    /**
     *  Get the number of dependent metabolites
     *  @return unsigned C_INT32 dimension
     */
    unsigned C_INT32 getNumDependentMetabs() const;

    //********** additional values *****************************

    /**
     * Return the non concentration values of this model
     * @return CCopasiVectorN< CModelValue > & values
     */
    const CCopasiVectorN< CModelValue > & getModelValues() const;
    CCopasiVectorN< CModelValue > & getModelValues();

    /**
     *  Get the number of non concentration values
     *  @return C_INT32 
     */
    unsigned C_INT32 getNumModelValues() const;

    //********** TT *****************************

    /**
     *  Set the transition times for all internal metabolites and the
     *  transistion time of the model.
     */
    void setTransitionTimes();

  public:
    //********** Reactions *****************************

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
     * Get the total steps
     * @return unsigned C_INT32 total steps;
     */
    unsigned C_INT32 getTotSteps() const;

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
     * Return a pointer to the current time
     */ 
    //virtual void * getValuePointer() const;

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

    //************** time *********************

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

    //************** compartments *********************

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
     *  Get the reordered stoichiometry matrix of this model
     */
    const CMatrix < C_FLOAT64 >& getStoiReordered() const;

    /**
     * Return the mMoieties of this model 
     * @return CCopasiVectorN < CMoiety > & 
     */
    const CCopasiVector < CMoiety > & getMoieties() const;

    /**
     * Returns the index of the metab
     */
    C_INT32 findMetabByName(const std::string & Target) const;

    /**
     * Returns the index of the Moiety
     */
    C_INT32 findMoiety(std::string &Target) const;

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
     * Get the relevant portion of the link matrix L.
     * @return const CMatrix< C_FLOAT64 > & L0
     */
    const CMatrix< C_FLOAT64 > & getL0() const;

    /**
     * initialize all values of the model with their initial values
     */
    void applyInitialValues();

    /**
     * Get the current state of the model, i.e., all current model
     * quantities.
     * @return const CState & initialState
     */
    const CState & getInitialState() const;

    /**
     * Get the current state of the model, i.e., all current model
     * quantities.
     * @return const CState & currentState
     */
    const CState & getState() const;

    /**
     * Set all initial model quantities to the one given by the state and
     * updates moieties and metabolite concentrations.
     * @param const CState & state
     */
    void setInitialState(const CState & state);

    /**
     * Set all independent current model quantities to the one given by the
     * state.
     * @param const CState & state
     */
    void setState(const CState & state);

    /**
     * This method refreshes all metabolite concentrations.
     */
    void refreshConcentrations();

    /**
     * This method applies all assignments, which currently includes:
     * i) calculating and assigning the particle numbers for dependent 
     *    metabolites (only if updateDependent is set in current state)
     * ii) updating all concentrations
     * iii) calculating the reaction fluxes
     */
    void applyAssignments(void);

    /**
     * Calculate the changes of all model quantities determined by ODEs
     * for the model in the current state.
     * The parameter derivatives must at least provide space for
     * state->getVariableNumberSize() double
     * &param C_FLOAT64 * derivatives (output)
     */
    void calculateDerivatives(C_FLOAT64 * derivatives);

    /**
     * Calculate the changes of all model quantities determined by ODEs
     * for the reduced model in the current state.
     * The parameter derivatives must at least provide space for
     * state->getDependentNumberSize() double
     * &param C_FLOAT64 * derivatives (output)
     */
    void calculateDerivativesX(C_FLOAT64 * derivativesX);

    /**
     * Calculates and assignes the rates for all model entitities if possible
     */
    void refreshRates();

    /**
     * Calculates the elasticity matrix of the model for the current
     * state and stores it in the provided matrix.
     * @param CMatrix< C_FLOAT64 > & elasticityMatrix
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    void calculateElasticityMatrix(const C_FLOAT64 & factor,
                                   const C_FLOAT64 & resolution);

    /**
     * Calculates the jacobian of the full model for the current state
     * and stores it in the provided matrix.
     * @param CMatrix< C_FLOAT64 > & jacobian
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    void calculateJacobian(CMatrix< C_FLOAT64 > & jacobian) const;

    /**
     * Calculates the jacobian of the reduced model for the current
     * state and stores it in the provided matrix.
     * @param CMatrix< C_FLOAT64 > & jacobianX
     * @param const C_FLOAT64 & factor,
     * @param const C_FLOAT64 & resolution
     */
    void calculateJacobianX(CMatrix< C_FLOAT64 > & jacobianX) const;

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
    std::string getVolumeUnitName() const;

    /**
     * Get the unit for volumes
     * @return CModel::VolumeUnit volumeUnit
     */
    CModel::VolumeUnit getVolumeUnitEnum() const;

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
    std::string getTimeUnitName() const;

    /**
     * Get the unit for time
     * @return CModel::TimeUnit timeUnit
     */
    CModel::TimeUnit getTimeUnitEnum() const;

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
    std::string getQuantityUnitName() const;

    /**
     * Get the unit for quantities
     * @return CModel::QuantityUnit quantityUnit
     */
    CModel::QuantityUnit getQuantityUnitEnum() const;

    /**
     *  Get the conversion factor quantity -> number
     */
    const C_FLOAT64 & getQuantity2NumberFactor() const;

    /**
     *  Get the conversion factor number -> quantity
     */
    const C_FLOAT64 & getNumber2QuantityFactor() const;

    //** convenience methods:
    std::string getConcentrationUnitName() const;
    std::string getConcentrationRateUnitName() const;
    std::string getQuantityRateUnitName() const;

    //************  create/remove model entities *******************

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
                             const CModelEntity::Status & status = CModelEntity::REACTIONS);

    /* Remove a metabolite from the model */
    bool removeMetabolite(const std::string & key);

    /* Retreives list of Reactions Keys which are dependent on the Metabolite */
    std::set<std::string> listReactionsDependentOnMetab(const std::string & key);

    /* Retreives list of Reactions Keys which are dependent on the Function */
    std::set<std::string> listReactionsDependentOnFunction(const std::string & key);

    /* Retreives list of Reactions Keys which are dependent on the Compartment*/
    std::set<std::string> listReactionsDependentOnCompartment(const std::string & key);

    /* Retreives list of Reactions Keys which are dependent on the non concentration value*/
    std::set<std::string> listReactionsDependentOnModelValue(const std::string & key);

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
    //bool addReaction(const CReaction & reaction);

    /* Remove a reaction from the model*/
    bool removeReaction(const std::string & key);

    /**
     * Add a non concentration value to the model
     * @param const std::string &name
     * @param const C_FLOAT64 & value (default 0.0)
     */
    CModelValue* createModelValue(const std::string & name,
                                  const C_FLOAT64 & value = 0.0);

    bool removeModelValue(const std::string & key);

    //*************************

    /**
     * Retrieve the metabolite permutation vector
     * @return CVector< unsigned C_INT32 > & permutation
     */
    const CVector< unsigned C_INT32 > & getMetabolitePermutation() const;

    /**
     * calculate rates, fluxes, and transition times.
     * this can be called after setState() / setStateX()
     */
    void updateRates();

    /**
     * Retreive the state template
     * @return const CModel::CStateTemplate & stateTemplate
     */
    CStateTemplate & getStateTemplate();

    bool hasReversibleReaction() const;

    /**
     * set Progress bar handler
     **/
    void setCompileHandler(CProcessReport* pHandler);

    /**
     * get address of progress bar handler
     **/
    CProcessReport* getCompileHandlerAddr();

    /**
     * check if the model is suitable for stochastic simulation
     **/
    std::string suitableForStochasticSimulation() const;

    /**
     * Check whether the model is autonomous
     * @return bool isAutonomous
     */
    bool isAutonomous() const;

  private:

    bool compile();

    /**
     * Handles unused metbolites and moves them to the end of mMetabolites.
     * Rows of the stoichiometry matrix dealing with unused metabolites are removed.
     * @return bool found
     */
    bool handleUnusedMetabolites();

    /**
     * Calculates all reactions and updates the particle fluxes.
     */
    void calculateReactions();

    /**
     * Initialize the contained CCopasiObjects
     */
    void initObjects();

    /**
     * Build the state template for the model.
     * @return bool success
     */
    bool buildStateTemplate();

#ifdef COPASI_DEBUG
  public:
    void check() const;
#endif
  };

#endif // CModel
