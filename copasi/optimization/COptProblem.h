/**
 *  File name: COptProblem.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the header file of the COptProblem class. 
 *           It specifies the optimization problem with its own members and 
 *           functions. It's used by COptAlgorithm class and COptimization class
 */


#ifndef COPTPROBLEM_H
#define COPTPROBLEM_H

#include <string>
#include <copasi.h>
#include <vector>

//
class COptProblem
{

  //data member
 private:
  
  double * mParameterValues;        // pointer to parameters
  int mParameterNum;          // the number of parameters
  double * mParameterMin;     // the minimum values of parameters
  double * mParameterMax;     // the maximum values of parameters


  // Implementation
 public:

   /**
    * Default constructor
    */
   COptProblem();

   /**
    * Destructor
    */
   virtual ~COptProblem();


  /**
   * Copy constructor
   * @param source a COptProblem object for copy
   */
  COptProblem(const COptProblem& source);

  /**
   * Object assignment overloading
   * @param source a COptProblem object for copy
   * @return an assigned COptProblem object
   */
  COptProblem& operator=(const COptProblem& source);


   /**
    * clean up memory
    */
    int cleanup(void);

   /**
    * Initialization of private variables
    */
   int initialize(void);

   /**
    * calculate function for optimization
    */
   virtual void calculate(); 

 
   /**
    * get parameters
    */
   void getParameters(); 
};


#endif  // the end 

