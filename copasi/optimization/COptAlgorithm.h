/**
 *  File name: COptAlgorithm.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the interface (.h file) of the COptAlgorithm class. 
 *           It contains the designed abstract interaction between a simulation
 *           subsystem and optimization algorithms. This base class defines
 *           methods by which the simulation subsystem accesses several 
 *           optimization algorithms.
 *  Note: This is an abstract class
 */

#ifndef COPTALGORITHM_H
#define COPTALGORITHM_H

#include <string>
#include <copasi.h>
#include <vector>
#include "utilities/CMethodParameter.h"
#include "utilities/CMethodParameterList.h"

using std::vector;

class COptProblem;

// YOHE: this is an abstract class that contains many virtual functions
// without definitions
//
class COptAlgorithm
  {
    //data member
  private:

    //These parameters are optimization parameters, not method (algm) parameters
    //they are for the model or calculation function.
    //Their memories are stored in COptProblem. Here are only pointers.
    C_FLOAT64 * mParameters;          // pointer to parameters
    unsigned C_INT32 mParameterNum;   // the number of parameters
    C_FLOAT64 * mParameterMin;        // the minimum values of parameters
    C_FLOAT64 * mParameterMax;        // the maximum values of parameters

    // is this ever used ? -- 10/14
    //vector <COptAlgorithmParameter> mOptAlgmParams;  //vector of COptAlgorithmParameter object

    string mMethodVersion;            // Method Version string, yes
    string mMethodName;               // method Name (descriptive)
    bool mBounds;                     // True if method accepts bounds on the parameters

    //rohan: modified 7/26
  protected:
    COptProblem * mOptProblem;        // pointer to remote problem
    CMethodParameterList * mOptAlgmParams; // pointer to parameter list
    // Implementation
  public:

    /**
     * Default constructor
     */
    COptAlgorithm();

    /**
     * Destructor
     */
    virtual ~COptAlgorithm();

    /**
     * Copy constructor
     * @param source a COptAlgorithm object for copy
     */
    COptAlgorithm(const COptAlgorithm & source);

    /**
     * Object assignment overloading
     * @param source a COptAlgorithm object for copy
     * @return an assigned COptAlgorithm object
     */
    COptAlgorithm& operator=(const COptAlgorithm & source);

    /**
     * clean up memory
     */
    virtual void cleanup(void);

    /**
     * Initialization of private variables
     */
    virtual bool initialize(void);

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     */
    virtual C_INT32 optimise();

    /**
     * set the number of method parameters
     */
    void setMethodParameterNumber(C_INT32 aNum);

    /**
     * get the number of method parameters
     */
    unsigned C_INT32 getMethodParameterNumber(void);

    /**
     * get method parameter that matches a specific index 
     */ 
    //vector <COptAlgorithmParameter> & getMethodParameters();

    /**
     * set a method parameter
     */ 
    //void setMethodParameterValue(C_INT32 i, C_FLOAT64 value);

    /**
     * get method parameter that matches a specific index
     * @param "C_INT32" i
     */ 
    //C_FLOAT64 getMethodParameterValue(C_INT32 i);

    /**
     * get method parameter name
     * @param "C_INT32" i
     */ 
    //string getMethodParameterName(C_INT32 i);

    /**
     * get method name
     */
    string getMethodName(void);

    /**
     * get method version
     */
    string getMethodVersion(void);

    /**
     * Returns True if this method is capable of handling adjustable parameter 
     * boundary constraints, False otherwise
     */ 
    //virtual bool isBounded(void);
    bool isBounded(void);

    /**
     * Set the problem to be optmised
     * @param "COptProblem *" problem
     */
    void setProblem(COptProblem * problem);
  };

#endif  // the end
