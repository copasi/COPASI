/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModel.h,v $
   $Revision: 1.65 $
   $Name:  $
   $Author: gasingh $ 
   $Date: 2003/10/31 22:49:45 $
   End CVS Header */

// cmodel.h : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COPASI_CModel
#define COPASI_CModel

#include <map>
#include <vector>
#include <string>

#include "CReaction.h"
#include "CMoiety.h"
#include "utilities/CVector.h"
#include "utilities/CMatrix.h"
#include "report/CCopasiContainer.h"

class CCompartment;
class CState;
class CStateX;

/** @dia:pos 177.081,30.2423 */
class CModel : public CCopasiContainer
  {
  public:
    /**
     * Enum of valid volume units
     */
    enum VolumeUnit {l = 0, ml, microl, nl, pl, fl};

    /**
     * String representation of valid volume units
     */
    static const char * VolumeUnitName[];

    /**
     *  Enum of valid time units
     */
    enum TimeUnit {s = 0, m, h, d};

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
        /** @dia:route 39,3; h,117.263,65.6961,127.49,65.7298,129.758 */
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
                                        const CLinkMatrixView & A)
        {
          unsigned C_INT32 i, imax = A.numRows();
          unsigned C_INT32 j, jmax = A.numCols();
          os << "Matrix(" << imax << "x" << jmax << ")" << std::endl;

          for (i = 0; i < imax; i++)
            {
              for (j = 0; j < jmax; j++)
                os << "  " << A(i, j);
              os << std::endl;
            }
          return os;
        }
      };

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
    /** @dia:route 2,18; h,158.906,33.503,167.042,36.1423,177.081 */
    CCopasiVectorNS < CCompartment > mCompartments;

    /**
     *  Vector of reference to metabolites
     */
    /** @dia:route 29,44; h,117.263,61.6961,171.362,46.7423,177.081 */
    CCopasiVector< CMetab > mMetabolites;

    /**
     *  Vector of reference to metabolites in reduced model representation
     */
    /** @dia:route 17,44; h,117.263,56.6961,171.362,46.7423,177.081 */
    CCopasiVector< CMetab > mMetabolitesX;

    /**
     *  Vector of reference to independent metabolites
     */
    /** @dia:route 21,44; h,117.263,58.2961,171.362,46.7423,177.081 */
    CCopasiVector< CMetab > mMetabolitesInd;

    /**
     *  Vector of reference to dependent metabolites
     */
    /** @dia:route 25,44; h,117.263,60.0961,171.362,46.7423,177.081 */
    CCopasiVector< CMetab > mMetabolitesDep;

    /**
     *  for array of steps
     */
    /** @dia:route 154,2; h,177.081,90.7423,175.231,75.5337,169.81 */
    CCopasiVectorNS< CReaction > mSteps;

    /**
     *  Vector of reference to reactions in reduced model representation.
     */
    /** @dia:route 154,9; h,177.081,90.7423,175.231,77.4337,169.81 */
    CCopasiVectorN< CReaction > mStepsX;

    /**
     *  Vector of reference to independend reactions.
     */
    /** @dia:route 154,13; h,177.081,90.7423,175.231,79.0337,169.81 */
    CCopasiVectorN< CReaction > mStepsInd;

    /**
     *  Vector of fluxes of the reactions.
     *  Note: The fluxes are the order corresponding to mStepX
     */
    CVector< const C_FLOAT64 * > mFluxes;
    CVector< const C_FLOAT64 * > mFluxesX;
    CVector< const C_FLOAT64 * > mScaledFluxes;
    CVector< const C_FLOAT64 * > mScaledFluxesX;

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
    /** @dia:route 178,7; h,177.081,100.342,174.433,136.262,81.1982 */
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
    /** @dia:route 98,2; h,177.081,68.3423,165.341,65.0298,160.278 */
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
    CStateTemplate mStateTemplate;

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
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 save(CWriteConfig &configBuffer);

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  This is saved in the format required by Gepasi 3.21
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    C_INT32 saveOld(CWriteConfig &configBuffer);

    /**
     *  Saves the contents of the object to a ofstream in SBML format.
     *  @param "std::ofstream &" fout the file stream (already open)
     */
    void saveSBML(std::ofstream &fout);

    /**
     *  This function must be called to initialize the vector of Metabolites
     *  after finishing adding metabolites to compartments.
     */
    void initializeMetabolites();

    /**
     *  Compile the model
     */
    void compile();

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
    void lSODAEval(C_INT32 n, C_FLOAT64 t, C_FLOAT64 * y, C_FLOAT64 * ydot);

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
    unsigned C_INT32 getDimension() const;

    /**
     * Return the comments of this model Wei Sun 
     * @return string
     */
    std::string getComments() const;

    /**
     * Return the key of this model
     * @return string key
     */
    std::string getKey() const;

    /**
     * Return the title of this model
     * @return string
     */
    std::string getTitle() const;

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
    void setInitialState (const CStateX * state);

    /**
     * Calculate the rates of the reaction in the given state.
     * The parameter rates must at least provide space mSteps.size() double
     * &param CState * state (input)
     * &param  C_FLOAT64 * rates (output)
     */
    void getRates(CState * state, C_FLOAT64 * rates);

    /**
     * Calculate the rates of the reaction in the given state in 
     * reduced model representation.
     * The parameter rates must at least provide space mStepsX.size() double
     * &param CStateX * stateX (input)
     * &param  C_FLOAT64 * rates (output)
     */
    void getRates(CStateX * state, C_FLOAT64 * rates);

    /**
     * Calculate the changes of particles numbers of the metabolites 
     * in the given state.
     * The parameter derivatives must at least provide space for
     * state->getVariableNumberSize() double
     * &param CState * state (input)
     * &param CVector< C_FLOAT64 > & derivatives (output)
     */
    void getDerivatives(CState * state, CVector< C_FLOAT64 > & derivatives);

    /**
     * Calculate the changes of particles numbers of the metabolites 
     * in the given state in reduced model representation.
     * The parameter derivatives must at least provide space for
     * state->getVariableNumberSize() double
     * &param CStateX * stateX (input)
     * &param CVector< C_FLOAT64 > & derivatives (output)
     */
    void getDerivatives(CStateX * state, CVector< C_FLOAT64 > & derivatives);

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
     * @param const std::string & compartment (default "")
     * @param const C_FLOAT64 & iconc (default 1.0)
     * @param const CMetab::Status & status (default CMetab::METAB_VARIABL)
     * @return bool success (false if failed)
     * @see CMetab for more information
     */
    bool addMetabolite(const std::string & name,
                       const std::string & compartment = "",
                       const C_FLOAT64 & iconc = 1.0,
                       const CMetab::Status & status = CMetab::METAB_VARIABLE);

    /**
     * Add a compartment to the model
     * @param const std::string &name
     * @param const C_FLOAT64 & volume (default 1.0)
     * @return bool success (false if failed)
     */
    bool addCompartment(const std::string & name,
                        const C_FLOAT64 & volume = 1.0);

    bool removeCompartment(const std::string & name);

    /**
     * Add a new rection to the model
     * @param const std::string &name
     * @return bool success (false if failed)
     */
    bool addReaction(const std::string &name);

    /**
     * Add a new rection to the model
     * @param const CReaction & reaction
     * @return bool success (false if failed)
     */
    bool addReaction(const CReaction & reaction);

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
    void setState(const CStateX * state);

    /**
     * Retreive the state template
     * @return const CModel::CStateTemplate & stateTemplate
     */
    const CModel::CStateTemplate & getStateTemplate() const;

    bool hasReversibleReaction() const;

  private:
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
