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

#include "optimization.h"

// YOHE: this is an abstract class that contains many virtual functions 
// without definitions
//
class COptAlgorithm
{

  //data member
 private:
  
  COptProblem * mOptProblem;  // pointer to remote problem
  double * mParameters;        // pointer to parameters
  int mParameterNum;           // the number of parameters
  double * mParameterMin;     // the minimum values of parameters
  double * mParameterMax;     // the maximum values of parameters
  vector <COptAlgorithmParameter> mOptAlgmParams;  //vector of COptAlgorithmParameter object

  string mMethodVersion;                  // Method Version string, yes
  string mMethodName;		          // method Name (descriptive)
  bool mBounds;		    // True if method accepts bounds on the parameters

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
    * clean up memory
    */
    int cleanup(void);

   /**
    * Initialization of private variables
    */
   bool initialize(void);

   /**
    * Execute the optimization algorithm calling simulation routine 
    * when needed. It is noted that this procedure can give feedback 
    * of its progress by the callback function set with SetCallback.
    */
   virtual int optimise();
  

   /**
    * get the number of method parameters
    */
   int getMethodParameterNumber(void);

   /**
    * set a method parameter
    */
   void setMethodParameter(int i, double value);

   /**
    * get method parameter that matches a specific index 
    */
   double getMethodParameter(int i);

   /**
    * get method parameter name
    */
   string getMethodParameterName(int i);

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
   //virtual bool isBounded( void );
   bool isBounded( void );
};


#endif  // the end 
