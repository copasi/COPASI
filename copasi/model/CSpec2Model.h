#ifndef COPASI_Spec2Model
#define COPASI_Spec2Model

#include <string>
#include <vector>
#include <list>
#include "copasi.h"
#include "model.h"
#include "CSpecLine.h"
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
    CSpec2Model(string filename);

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

    /**
     * Prints the input file, used to test that input was correctly read
     */
    void printInput();
 private:
    // Private operations
    
    /**
     * Determine the type of an input line.
     */
    void determineType(string line);

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
     * Parse a line
     */
    C_INT32 parseLine(string line);
 private:
    /**
     * The name of the specification file
     */
    string mSpecFileName;
    /**
     * The contents of the specification file.
     */
    vector<string> mSpecContents;
    /**
     * The contents again, annotated
     */
    vector<CSpecLine> mSpecLines;
    /**
     * The differential equation contents, for further processing
     */
    vector<CBaseEqn> mReactVector;
    /**
     * The moiety equation contents, for further processing
     */
    vector<CBaseEqn> mMoietyVector;
    /**
     * A pointer to the model being constructed.
     */
    CModel *mModel;
};

#endif // COPASI_Spec2Model
