#ifndef COPASI_Spec2Model
#define COPASI_Spec2Model

#include <string>
#include <vector>
#include <list>
#include "copasi.h"
#include "CSpecLine.h"
#include "CDeTerm.h" 
/**
 * CSpec2Model
 *
 * This class is responsible for controlling the reading of a text
 * input file and construction of a Copasi model. There are two stages
 * involved. In the first the input is read line by line and passed to
 * a scanner, which extracts tokens and sends these to a parser, which
 * instantiates some of the objects of the model. In the second stage,
 * lines corresponding to differential equations and equations are are
 * again scanned and parsed, during which the reactions in the model
 * are completed.
 *
 * This would be used by a front-end to read a text file from disk or
 * a socket and to produce a model. A GUI front end could also get the
 * input directly from the user.
 *
 * Prototypical use:
 * CModel *model;
 * CSpec2Model specreader(filename);
 * model = sprecreader.createModel();
 */

/** @dia:pos 87.8692,-0.359781 */
class CSpec2Model
  {
  public:
    //Lifecycle methods

    /**
     * The default constructor.
     */
    CSpec2Model();

    /**
     * The named constructor.  This constructs a CSpec2Model which
     * will read the contents of the specified file.  
     * @param filename The name of the spec file to process.
     */
    CSpec2Model(std::string filename);

    /**
     * The destructor
     */
    ~CSpec2Model();

    // Operations

    /**
     * Creates a model, and populates it from the specification file.
     * There are two stages to this: the first pass identifes the
     * variables, assigns them to compartments, and sets initial
     * conditions, while in the second stage the functions and
     * differential equations are constructed and anlysed.
     */
    CModel *createModel();

  private:

    /**
     * Determine the type of an input line.
     */
    void determineType(std::string line);

    /**
     * Extract and instantiate compartments.
     */
    void processCompartments();

    /**
     * For DEs and EQNs, extract the compartment, LHS metabolite
     * andRHS These are then stored in a vector of CBaseEqn.
     */
    void processEQNs();

    /**
     * Assign initial values to metabolites.
     */
    void processInits();

    /**
     * Assign values to constants
     */
    void processConstants();

    /**
     * Initiate reactions and begin rate creation
     */
    void processRates();

    /**
     * This constructs the functions for the function database.
     */
    void processFunctions();

    /**
     * Associate active metabolites with moieties
     */
    void processMoieties();

    /**
     * Extract the terms of the DEs, and process them
     */
    void processDETerms();
  private:
    /**
     * Adds the contents of a file to CSpec2Model
     */
    C_INT32 addFileContents();
    /**
     * Reads individual lines from the spec file and processes them.
     * This essentially identifies the variables and assigns them to
     * compartments. The line is fed through the lexical analyser and
     * then parsed by the parser.
     */
    void readLine();
    /**
     * This processes the lines representing differential equations,
     * analysing these term by term to reconstruct the reactions
     * involved in the model.
     */
    void processDifferentialEquations();

    /**
     * Return the left hand side metabolite in a differential equation
     */
    CMetab *getLHSMetab(CBaseEqn &);
    /**
     * 
     */
    void processDeTerms();
    /**
     * Create a stack of terms, used by processDeTerms().
     * @param The string description of the DE.
     * @return A vector of pointers to CDeTerm describing the stack.
     */
    std::vector< CDeTerm *> createTermStack(std::string str);
    /**
     * Expand any functions found in the rate.
     * @return The expanded rate.
     */
    std::string expandRate(CDeTerm *term);
    /**
     * Adjusts the level of parentheses encountered; used internally by
     * createTermStack to determine term boundaries.
     * @param level The depth of parameters so far
     * @param The symbol type
     * @return The adjusted level
     */
    C_INT32 adjustLevel(C_INT32 level, C_INT32 type);

    /**
     *  Find the metabolite with the given name.
     * @param metab_name The name of the metabolite
     * @return A pointer to the metabolite
     */
    CMetab *findMetabolite(std::string metab_name);

  private:
    /**
     * The name of the specification file
     */
    std::string mSpecFileName;
    /**
     * The contents of the specification file.
     */
    std::vector< std::string> mSpecContents;
    /**
     * The contents again, annotated
     */
    /** @dia:route 22,2; h,87.8692,7.34022,85.8737,11.5496,80.6844 */
    std::vector< CSpecLine> mSpecLines;
    /**
     * The differential equation contents, for further processing
     */
    /** @dia:route 9,0; h,80.6844,1.53787,85.8737,-0.359781,87.8692 */
    std::vector< CBaseEqn> mDeVector;
    /**
     * The moiety equation contents, for further processing
     */
    /** @dia:route 2,0; h,80.6844,-0.362133,85.8737,-0.359781,87.8692 */
    std::vector< CBaseEqn> mMoietyVector;
    /**
     * The constants, which are later plugged into rates or moiety equations
     */
    /** @dia:route 2,40; h,80.6844,25.0669,85.8737,14.5402,87.8692 */
    std::vector< CNameVal> mConstVector;
    /**
     * The rate constants, used later to create reactions and 
     * to parse the differential equations.
     */
    /** @dia:route 9,40; h,80.6844,26.9669,85.8737,14.5402,87.8692 */
    std::vector< CNameVal> mRateVector;
    /**
     * A pointer to the model being constructed.
     */
    /** @dia:route 8,7; h,177.081,32.1423,125.418,23.8402,117.914 */
    CModel *mModel;
  };

#endif // COPASI_Spec2Model
