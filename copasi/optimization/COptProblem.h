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
#include <math>
#include <copasi.h>
#include <vector>

//
class COptProblem
{

  //data member
 private:
  
  double * mParameterValues;        // pointer to parameters
 
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
    * clear up memory
    */
    int clearup(void);

   /**
    * Initialization of private variables
    */
   int initialize(void);

   /**
    * calculate function for optimization
    */
   void calculate(); 

 
};


#endif  // the end 

