/**
 *  File name: CRealProblem.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the header file of the CRealProblem class. 
 *           It specifies the optimization problem with its own members and 
 *           functions. It's used by COptAlgorithm class and COptimization class
 *           It's a subclass of COptProblem
 *     
 *  The specific purpose here is to use it to demonstrate that the system works
 *  fine. It is for my independent study project.  -- Yongqun He
 *  
 *  The function I use here is a N-Dimensional Test Function:
 *            f(x) = (1/2)Sum(j=1, n)(Xj^4 - 16Xj^2 + 5Xj)
 *        where, x = [X1, X2, ... , Xj, ..., Xn]
 *        Number of global minima = 1;
 *    Global minimum found by TRUST is:
 *        [-2.90354, -2.90354, ..., -2.90354].
 * 
 */


#ifndef CREALPROBLEM_H
#define CREALPROBLEM_H

#include <string>
#include <copasi.h>
#include <vector>
#include "math.h"
#include "float.h"


#include "COptProblem.h"

//
class CRealProblem : public COptProblem
{

  //data member
  //no real variables defined here, but the base class has many members
 private:
  
  
  // Implementation
 public:

   /**
    * Default constructor
    */
   CRealProblem();

   /**
    * Destructor
    */
   ~CRealProblem();



   /**
    * calculate function for optimization
    */
   void calculate(); 

 
};


#endif  // the end 

