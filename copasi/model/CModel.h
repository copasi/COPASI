// cmodel.h : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COPASI_CModel
#define COPASI_CModel

#include <vector>
#include <string>

#include "CReaction.h"
#include "CMoiety.h"
#include "tnt/tnt.h"
#include "tnt/cmat.h"
#include "tnt/triang.h"
#include "tnt/transv.h"

class CCompartment;

class CState;

class CStateX;

class CModel
  {
    //Attributes

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
     *  for array of metabolites
     */
    vector < CMetab * > mMetabolites;
    vector < CMetab * > mMetabolitesX;
    vector < CMetab * > mMetabolitesInd;
    vector < CMetab * > mMetabolitesDep;

    /**
     *  for array of steps
     *  @supplierCardinality 0..*
     *  @associates <{CReaction}>
     */
    CCopasiVectorNS < CReaction > mSteps;
    vector < CReaction * > mStepsX;
    vector < CReaction * > mStepsInd;

    /**
     *  Vector of fluxes of the reactions.
     *  Note: The fluxes are the order corresponding to mStepX
     */
    vector <const C_FLOAT64 *> mFluxes;
    vector <const C_FLOAT64 *> mFluxesX;

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
    TNT::Matrix < C_FLOAT64 > mStoi;

    /**
     *   Reduced Stoichiometry Matrix
     */
    TNT::Matrix < C_FLOAT64 > mRedStoi;

    /**
     *   The Matrix which stores the L U Decompasition
     */
    TNT::Matrix < C_FLOAT64 > mLU;

    /**
     *   This matrix stores L and the inverse of L
     */
    TNT::Matrix < C_FLOAT64 > mL;

    /**
     *   This is used to return a view to L
     */
    TNT::UnitLowerTriangularView < TNT::Matrix < C_FLOAT64 > > *mpLView;

    /**
     *   This is used to return a view to the inverse of L
     */
    TNT::Transpose_View< TNT::UpperTriangularView< TNT::Matrix< C_FLOAT64 > > >
    *mpInverseLView;

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
     * 
     */
    void initialize();

    /**
     * 
     */
    ~CModel();        // destructor (deallocation code here)

    /**
     * 
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

    vector < CMetab * > & getMetabolitesInd();
    vector < CMetab * > & getMetabolitesDep();
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

    /**
     *  This functions returns a pointer to a vector of the initial particle
     *  numbers of the independent metabolites. 
     *  Note: After ussage the memory has to be released with delete [] y.
     *  @return C_FLOAT64 * y
     */
    C_FLOAT64 * getInitialNumbers();

    /**
     *  This functions returns a pointer to a vector of the current particle
     *  numbers of the independent metabolites. 
     *  Note: After ussage the memory has to be released with delete [] y.
     *  @return C_FLOAT64 * y
     */
    C_FLOAT64 * getNumbers();

    /**
     *  Set the concentration of all metabolites as a result of the particle
     *  number of the independent metabolites
     *  param C_FLOAT64 & y
     */
    void setConcentrations(const C_FLOAT64 *y);

    /**
     *  Set the rate for all internal metabolites and the
     *  transistion time of the model.
     *  param C_FLOAT64 & y
     */
    void setRates(const C_FLOAT64 *y);

    /**
     *  Set the transition times for all internal metabolites and the
     *  transistion time of the model.
     */
    void setTransitionTimes();

    // Added by CvG
    /**
     * Return the vector of reactions
     * @return "CCopasiVectorS <CReaction> &"
     */
    CCopasiVectorNS < CReaction > & getReactions();
    const CCopasiVectorNS < CReaction > & getReactions() const;
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
    const TNT::Matrix < C_FLOAT64 > & getStoi() const;

    /**
     *  Get the Reduced Stoichiometry Matrix of this Model
     */
    const TNT::Matrix < C_FLOAT64 >& getRedStoi() const;

    /**
     * Return the mMoieties of this model 
     * @return CCopasiVectorN < CMoiety > & 
     */
    CCopasiVectorN < CMoiety > & getMoieties();

    /**
     * Returns the index of the metab
     */
    C_INT32 findMetab(string &Target);

    /**
     * Returns the index of the step
     */
    C_INT32 findStep(string &Target);

    /**
     * Returns the index of the compartment
     */
    C_INT32 findCompartment(string &Target);

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
     *  Get the mLU matrix of this model
     */
    const TNT::Matrix < C_FLOAT64 > & getmLU() const;

    const TNT::UnitLowerTriangularView<TNT::Matrix<C_FLOAT64 > > & getL() const;

    const
    TNT::Transpose_View<TNT::UpperTriangularView<TNT::Matrix<C_FLOAT64 > > >
    & getInverseL() const;

    /**
     *  Get the reverse Matrix of this Model
     */
    const TNT::Matrix < C_FLOAT64 >& getML() const;

    TNT::Matrix < C_FLOAT64 >& getML();

    CState * getInitialState() const;
    CStateX * getInitialStateX() const;
    void setInitialState(const CState * state);
    void setInitialState (const CStateX * state);
    void getRates(CState * state, C_FLOAT64 * rates);
    void getRates(CStateX * state, C_FLOAT64 * rates);
    void getDerivatives(CState * state, C_FLOAT64 * derivatives);
    void getDerivatives(CStateX * state, C_FLOAT64 * derivatives);
    CStateX * convertState(CState * state);
    CState * convertState(CStateX * state);

  private:
    void setState(const CState * state);
    void setState(const CStateX * state);
    CState * getState() const;
    CStateX * getStateX() const;
  };

#endif // CModel
