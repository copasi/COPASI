// cmodel.h : interface of the CModel class
//
/////////////////////////////////////////////////////////////////////////////

#ifndef COPASI_CModel
#define COPASI_CModel

#include <vector>
#include <string>

#include "CReadConfig.h"
#include "CWriteConfig.h"
#include "CMetab.h"
#include "CStep.h"

class CModel
{
public:
    /**
     * 
     */
    CModel();        // constructor

    /**
     * 
     */
    ~CModel();        // destructor (deallocation code here)

    /**
     *  Assignement operator. 
     */
    CModel &operator=(CModel &);    // overloaded assignment operator

    /**
     * 
     */
    void Reset(long nstep, long nmetab,
               long intmet, long nmoiety,
               long ncompart,
               const string &Tit);   // resets the model

    /**
     * 
     */
    void ResetStepMetab(long nstep, long nmetab, long intmet, long nmoiety); //resets all nut compartments and title

    /**
     * 
     */
    long ResetCompartments(long ncompart); // clears the compartments array and resizes it

    /**
     * 
     */
    void ClearStoi(void);    // zeroes all entries in stoichimetry matxs

    /**
     * 
     */
    void Clear(void);     // clears the model (incl resetting to 0)

    /**
     *  Saves the contents of the object to a CWriteConfig object.
     *  (Which usually has a file attached but may also have socket)
     *  @param pconfigbuffer reference to a CWriteConfig object.
     *  @return Fail
     */
    long Save(CWriteConfig &configbuffer);

    /**
     *  Loads an object with data coming from a CReadConfig object.
     *  (CReadConfig object reads an input stream)
     *  @param pconfigbuffer reference to a CReadConfig object.
     *  @return Fail
     */
    long Load(CReadConfig &configbuffer);

    /**
     * 
     */
    void CountMetabolites(void);   // counts the metabolites in each class

    /**
     * 
     */
    void SortMetabolites(void);   // sorts the metabolite for secondary matrices

    /**
     * 
     */
    void Structural(void);    // identifies structural properties

    /**
     * 
     */
    long ElementaryModes(CWriteConfig &configbuffer); // finds the elementary modes

    /**
     * 
     */
    void AddToStoi(long StepNo, 
                   long MetabNo,
                   long Sign, long Value); // adds an entry in Stoi and in the relevant step

    /**
     * 
     */
    void SetupMoiety(void);    // sets the description and concentration of moieties

    /**
     * 
     */
    void UpdateChemEq(void);    // updates the ChemEq equations of all steps

    /**
     * 
     */
    void InitDebug(void);    // For debug output

    /**
     * 
     */
    void PrintSummary(void);    // For debug output

    /**
     * 
     */
    void PrintMatrices(void);   // For debug output

    /**
     * 
     */
    long FindMetab(string &Target);  // returns the index of the metab

    /**
     * 
     */
    long FindStep(string &Target);  // returns the index of the step

    /**
     * 
     */
    long FindMoiety(string &Target);  // returns the index of the moiety

    /**
     * 
     */
    long FindCompartment(string &Target);// returns the index of the compartment

    /**
     * 
     */
    void CalculateMoieties(void);  // calculates the total masses of the moieties

    /**
     * 
     */
    long SubstrateMolecularity(long st); // returns molecularity (substrates)

    /**
     * 
     */
    long ProductMolecularity(long st);  // returns molecularity (products)

    /**
     * 
     */
    void UpdateCompartments(void);  // updates references to compartments

    /**
     * 
     */
    void SaveUDKin(CWriteConfig &configbuffer); // saves the user-defined kinetic types in this model

    /**
     * 
     */
    long AddMetabolite(string &NewName);// adds a new metabolite to the model

    /**
     * 
     */
    void UpdateMoieties(void);

    /**
     * 
     */
    // determine the kernel of the stoichiometry matrix
    long GetKernel(void);

private:

    /**
     * 
     */
    // operations
    // allocate memory and set pointers for a model
    void AllocModel(long nstep, long nmetab, long longmet, long nmoiety, long ncompart);

    /**
     * 
     */
    // deallocate memory and free the pointers
    void DeAlloc(void);

    /**
     * 
     */
    // initilizes the indeces to RedStoi
    void InitIndex(void);  

    /**
     * 
     */
    // copies Stoi longo RedStoi
    void InitRedStoi(void);

    /**
     * 
     */
    // finds metabolites that must be external
    void SpotExternal(void);

    /**
     * 
     */
    // checks if a row in RedStoi is empty
    long EmptyRow(long r);

    /**
     * 
     */
    // switches two rows in the secondary matrices
    void RedStoiRowSwitch(long r1, long r2);

    /**
     * 
     */
    // switches two cols in the secondary matrices
    void RedStoiColSwitch(long c1, long c2);

    /**
     * 
     */
    // allocates space for the ml and lm matrices
    long CreateLM(void);

    /**
     * 
     */
    // deletes the space used by ml and lm matrices
    void DestroyLM(void);

    /**
     * 
     */
    // reduces RedStoi
    long Gauss(void);

    /**
     * 
     */
    // identifies the conseravation relations
    void SpotDependent(void);

    /**
     * 
     */
    // Creates the mapping for secondary matrices
    void MapSecondary(void);

    /**
     * 
     */
    // mark the status of longernal metabolites
    void MarkStatus(void);

    /**
     * 
     */
    // rebuild the stoichiometry matrix
    void RebuildStoi(long flag);


    /**
     * 
     */
    // title of the model
    string mTitle;


    /**
     * 
     */
    // Comments
    string mComments;

    // metabolites

    /**
     * 
     */
    // number of internal metabolites
    long mIntMetab;

    /**
     * 
     */
    // number of independent metabolites
    long mIndMetab;

    /**
     * 
     */
    // number of dependent metabolites
    long mDepMetab;

    /**
     * 
     */
    // number of external metabolites
    long mExtMetab;

    /**
     * 
     */
    // for array of metabolites
    vector < CMetab > mMetabolite;

    /**
     * 
     */
    // for array of conserved moieties
    vector < CMetab > mMoiety;


    /**
     * 
     */
    // the overall transition time of the pathway
    double mTransTime;


    /**
     * 
     */
    // for array of steps
    vector < CStep > mStep;

    /**
     * 
     */
    // for array of compartments`
    vector < CCompartment > mCompartment;

    // reaction network

    /**
     * 
     */
    // for the stoichiometry matrix (ptrs for the rows)
    vector < vector < float > > mStoichiometry;

    /**
     * 
     */
    // for the reduced stoichiometry matrix (ptrs for the rows)
    vector < vector < float > > mRedStoi;

    /**
     * 
     */
    // to index rows from primary to secondary matrix notation - Stoi notation to RedStoi
    vector < long > mRow;

    /**
     * 
     */
    // to index cols from primary to secondary matrix notation
    vector < long > mCol;

    /**
     * 
     */
    // to index rows from secondary to primary matrix notation - RedStoi notation to Stoi
    vector < long > mIRow;

    /**
     * 
     */
    // to index cols from secondary to primary matrix notation
    vector < long > mICol;

    /**
     * 
     */
    // for the reaction structure description vectors
    vector < vector < long > > mReactStruct;

    /**
     * 
     */
    // for the array of conservation relations (ptrs to the rows)
    vector < vector < float > > mConsRel;

    /**
     * 
     */
    // multipliers of gauss reduction (IntMet x IntMet)
    vector < vector < float > > mML;

    /**
     * 
     */
    // for the kernel of the stoichiometry matrix (ptrs for the rows)
    vector < vector < float > > mKernel;

    /**
     * 
     */
    // permutation matrix (index of Kernel's rows
    vector < long > mKernelP;

    /**
     * 
     */
    // dimensions of the Kernel matrix
    long mKernelI, mKernelJ;

    /**
     * 
     */
    // rank of the stoichiometry matrix
    long mRank;

    /**
     * 
     */
    // number of reactions in equil at steady state
    long mDetBalance;

    /**
     * 
     */
    // inverse of ml (IntMet x IntMet)
    vector < vector < float > > mLM;

    /**
     * 
     */
    // temporary file for debugging
    string   mDebugFile;   // temporary file for debugging
};

#endif // CModel
