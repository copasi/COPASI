// cmodel.h : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COPASI_CModel
#define COPASI_CModel

#include <vector>
#include <string>

#include "CReaction.h"
#include "CMoiety.h"
#include "utilities/CMatrix.h"

class CCompartment;
class CState;
class CStateX;
template <class CType> class CVector;

class CModel
  {
    //Attributes
    class CLinkMatrixView
      {
      public:
        typedef C_FLOAT64 elementType;

      private:
        const CMatrix< C_FLOAT64 > & mA;
        const vector < CMetab * > & mIndependent;
        static const elementType mZero;
        static const elementType mUnit;

      public:
        /**
         * Default constructor
         * @param const CMatrix< C_FLOAT64 > & A
         * @param const vector< CMetab * > & independent
         */
        CLinkMatrixView(const CMatrix< C_FLOAT64 > & A,
                        const vector< CMetab * > & independent);

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
         * @return elementType element
         */
        inline elementType operator()(const unsigned C_INT32 & row,
                                      const unsigned C_INT32 & col) const
        {
          if (row >= mIndependent.size())
          return mA(row - mIndependent.size(), col);
          else if (row != col)
            return mZero;
            else
              return mUnit;
            }

            /**
             * Output stream operator
             * @param ostream & os
             * @param const CLinkMatrixView & A
             * @return ostream & os
             */
            friend ostream &operator<<(ostream &os,
                                       const CLinkMatrixView & A)
              {
                unsigned C_INT32 i, imax = A.numRows();
                unsigned C_INT32 j, jmax = A.numCols();
                os << "Matrix(" << imax << "x" << jmax << ")" << endl;

                for (i = 0; i < imax; i++)
                  {
                    for (j = 0; j < jmax; j++)
                      cout << "  " << A(i, j);
                    cout << endl;
                  }
                return os;
              }
      };

  private:
    /**
     *  title of the model
     */
    string mTitle;

    /**
     *  Comments
     */
    string mComments;

    // metabolites

    /**
     *  for array of compartments
     *  @supplierCardinality 0..*
     *  @associates <{CCompartment}>
     */
    CCopasiVectorNS < CCompartment > mCompartments;

    /**
     *  Vector of reference to metabolites
     */
    vector < CMetab * > mMetabolites;

    /**
     *  Vector of reference to metabolites in reduced model representation
     */
    vector < CMetab * > mMetabolitesX;

    /**
     *  Vector of reference to independent metabolites
     */
    vector < CMetab * > mMetabolitesInd;

    /**
     *  Vector of reference to dependent metabolites
     */
    vector < CMetab * > mMetabolitesDep;

    /**
     *  for array of steps
     *  @supplierCardinality 0..*
     *  @associates <{CReaction}>
     */
    CCopasiVectorNS < CReaction > mSteps;

    /**
     *  Vector of reference to reactions in reduced model representation.
     */
    vector < CReaction * > mStepsX;

    /**
     *  Vector of reference to independend reactions.
     */
    vector < CReaction * > mStepsInd;

    /**
     *  Vector of fluxes of the reactions.
     *  Note: The fluxes are the order corresponding to mStepX
     */
    vector <const C_FLOAT64 *> mFluxes;
    vector <const C_FLOAT64 *> mFluxesX;
    vector <const C_FLOAT64 *> mScaledFluxes;
    vector <const C_FLOAT64 *> mScaledFluxesX;

    /**
     *  Transition time 
     */
    C_FLOAT64 mTransitionTime;

    /**
     *  for array of conserved moieties
     *  @supplierCardinality 0..*
     *  @associates <{CMoiety}>
     */
    CCopasiVectorN < CMoiety > mMoieties;

    /**
     *   Stoichiometry Matrix
     */
    CMatrix < C_FLOAT64 > mStoi;

    /**
     *   Reduced Stoichiometry Matrix
     */
    CMatrix < C_FLOAT64 > mRedStoi;

    /**
     *   The Matrix which stores the LU-Decomposition
     */
    CMatrix < C_FLOAT64 > mLU;

    /**
     * Vector for storing the row interchanges during LU-Decomposition
     */
    vector < unsigned C_INT32 > mRowLU;

    /**
     * Vector for storing the column interchanges during LU-Decomposition
     */
    vector < unsigned C_INT32 > mColLU;

    /**
     *   This matrix stores L
     */
    CMatrix < C_FLOAT64 > mL;

    /**
     *   This is used to return a view to L
     */
    CLinkMatrixView mLView;

    /**
     *  Unit for substance quantities
     */
    string mQuantityUnitName;

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
     *  Build L and InverseL
     */
    void buildL();

    /**
     *  LU-Decomposition of the stoichiometry matrix
     */
    void lUDecomposition();

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

    /**
     *  This calculate the right hand side (ydot) of the ODE for LSODA
     */
    void lSODAEval(C_INT32 n, C_FLOAT64 t, C_FLOAT64 * y, C_FLOAT64 * ydot);

    /**
     * Retrieves the vector of independent metabolites.
     * @return vector < CMetab * > metabolites
     */
    vector < CMetab * > & getMetabolitesInd();

    /**
     * Retrieves the vector of dependent metabolites.
     * @return vector < CMetab * > metabolites
     */
    vector < CMetab * > & getMetabolitesDep();

    /**
     * Retrieves the vector of metabolites at it is used in the reduced model.
     * @return vector < CMetab * > metabolites
     */
    vector < CMetab * > & getMetabolitesX();

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

#ifndef COPASI_DEPRECATED
    /**
     *  This functions returns a pointer to a vector of the initial particle
     *  numbers of the independent metabolites. 
     *  Note: After ussage the memory has to be released with delete [] y.
     *  @return C_FLOAT64 * y
     */
    C_FLOAT64 * getInitialNumbersDbl() const;
#endif // COPASI_DEPRECATED

#ifndef COPASI_DEPRECATED
    /**
     *  This functions returns a pointer to a vector of the current particle
     *  numbers of the independent metabolites. 
     *  Note: After ussage the memory has to be released with delete [] y.
     *  @return C_FLOAT64 * y
     */
    C_FLOAT64 * getNumbersDbl() const;
#endif // COPASI_DEPRECATED

#ifndef COPASI_DEPRECATED
    /**
     *  Set the concentration of all metabolites as a result of the particle
     *  number of the independent metabolites
     *  param C_FLOAT64 & y
     */
    void setNumbersDblAndUpdateConcentrations(const C_FLOAT64 *y);
#endif // COPASI_DEPRECATED

#ifndef COPASI_DEPRECATED
    /**
     *  Set the rate for all internal metabolites and the
     *  transistion time of the model.
     *  param C_FLOAT64 & y
     */
    void setRates(const C_FLOAT64 *y);
#endif // COPASI_DEPRECATED

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
     * @return vector < CReaction * > & reactions
     */
    vector < CReaction * > & getReactionsX();

    // Added by Yongqun He
    /**
     * Get the total steps
     * @return unsigned C_INT32 total steps;
     */
    unsigned C_INT32 getTotSteps();

    /**
     *  Get the dimension of the reduced problem
     *  @return unsigned C_INT32 dimension
     */
    unsigned C_INT32 getDimension() const;

    /**
     * Return the comments of this model Wei Sun 
     * @return string
     */
    string getComments() const;

    /**
     * Return the title of this model
     * @return string
     */
    string getTitle() const;

    /**
     * Set the title of this model
     * @param "const string &" title title for this model
     */
    void setTitle(const string &title);

    /**
     * Set the title of this model
     * @param "const string &" comments comments for this model
     */
    void setComments(const string &comments);

    /**
     * Return the compartments of this model
     * @return CCopasiVectorNS < CCompartment > *
     */
    CCopasiVectorNS < CCompartment > & getCompartments() const;

    /**
     * Return the metabolites of this model
     * @return vector < CMetab * > 
     */
    vector < CMetab * > & getMetabolites();

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
    CCopasiVectorN < CMoiety > & getMoieties();

    /**
     * Returns the index of the metab
     */
    C_INT32 findMetab(const string & Target);

    /**
     * Returns the index of the step
     */
    C_INT32 findStep(const string & Target);

    /**
     * Returns the index of the compartment
     */
    C_INT32 findCompartment(const string & Target);

    /**
     * Returns the index of the Moiety
     */
    C_INT32 findMoiety(string &Target);

    /**
     * Returns the mStepsX of this model
     * @return vector < CStep * > 
     */
    vector < CReaction * > & getStepsX();

    /**
     * Get the LU decomposition matrix of this model
     * @return const TNT::Matrix < C_FLOAT64 > & LU
     */
    const CMatrix < C_FLOAT64 > & getmLU() const;

    /**
     * Get the link matrix L of the relation: Stoi = L * RedStoi
     * @return const CLinkMatrixView L
     */
    const CLinkMatrixView & getL() const;

    /**
     * Get the initial state of the model, i.e., initial concentrations 
     * and volumes.
     * @return CState * initialState
     */
    CState * getInitialState() const;

    /**
     * Get the initial state of the model, i.e., initial concentrations 
     * and volumes in reduced model representation.
     * @return CStateX * initialStateX
     */
    CStateX * getInitialStateX() const;

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
     * set the unit for substance quantities. If copasi recognises 
     * the unit the conversion factors are set accordingly. 
     * Otherwise they are set to 1.
     */
    void setQuantityUnit(const string & name);

    /**
     *  Get the Name of the unit for substance quantities
     */
    string getQuantityUnit() const;

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
     * @param comp name of compartment to own this metabolite
     * @param name name of metabolite
     * @param iconc initial concentration of metabolite
     * @param status metabolite status (see CMetab for valid values)
     */
    C_INT32 addMetabolite(const string & comp,
                          const string & name,
                          C_FLOAT64 iconc,
                          C_INT16 status);

    /**
     * Add a compartment to the model
     * @param name name of the new compartment
     * @param vol volume of the new compartment
     * @return C_INT32 number of compartments in the model 
     *   (after insertion) or -1 if failed
     */
    C_INT32 addCompartment(string &name, C_FLOAT64 vol);

    /**
     * Add a new rection to the model
     * @param r a pointer to the new reaction
     * @return C_INT32 number of reactions in the model (after insertion)
     */
    C_INT32 addReaction(CReaction *r);

    /**
     * Retrieve the metabolite permutation vector
     * @return const vector <unsigned C_INT32> & permutation
     */
    const vector <unsigned C_INT32> & getMetabolitePermutation() const;

    /**
     * Retrieve the reaction permutation vector
     * @return const vector <unsigned C_INT32> & permutation
     */
    const vector <unsigned C_INT32> & getReactionPermutation() const;

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

  private:
    /**
     * Set the transient concentrations and volumes according to the
     * given stateX in reduced model representation.
     * @param const CState * stateX
     */
    void setState(const CStateX * state);
  };

#endif // CModel
