/**
 *  File name: COptProblem.cpp
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the source file of the COptProblem class. 
 *           It specifies the optimization problem with its own members and 
 *           functions. It's used by COptAlgorithm class and COptimization class
 */


#include "COptProblem.h"


// double * mParameterValues;        // pointer to parameters
 
   
//  Default constructor
COptProblem::COptProblem()
{
  mParameterValues = NULL;
}

   
// Destructor
COptProblem::~COptProblem()
{ }

 
//clean up memory
int COptProblem::cleanup(void)
{
  mParameterValues = NULL;
}

 
//  Initialization of private variables
int COptProblem::initialize(void)
{

}

 
// calculate function for optimization
void COptProblem::calculate() 
{

}

 


