/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/COptMethodEP2.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/11/23 12:31:29 $
   End CVS Header */

/**
 * COptMethodEP2 class
 */

#ifndef COPASI_COptMethodEP2
#define COPASI_COptMethodEP2

#define TRUE 1
#define FALSE 0

#include <iostream>
#include <iomanip>
#include <fstream> 
// #include <sys/times.h>
// #include <sys/types.h>
#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "time.h"
#include "ctype.h"
#include "string.h"
#include "math.h"
#include "float.h" 
//#include "r250.h"

class CRandom;

//  this is an abstract class that contains many virtual functions
// without definitions

class COptMethodEP2 : public COptMethod
  {
    friend COptMethod * COptMethod::createMethod(CCopasiMethod::SubType subType);

    // Operations
  private:

    int NumGeneration;  // number of generations
    int PopulationSize;  // size of the population
    int NumCrossPoint;  // number of crossover points

    double Minimum, Maximum;    //parameter boundary

    int BestFoundSoFar;  // index of the BestFoundSoFar individual
    int NumParameter;   // number of parameters

    double **individual; // for array of individuals w/ candidate values for the parameters
    double *CandidateValue; // array of values of objective function f/ individuals
    double *CandidateValueRate; // array of map values of objective function f/ individuals

    int *CrossPoint;  // indexes of the crossover points
    int *WinScore;  // number of WinScore of each individual in the tournament

    /**
     * Default Constructor
     */
    COptMethodEP2();

  public:
    /**
     * Copy Constructor
     * @param const COptMethodEP2 & src
     */
    COptMethodEP2(const COptMethodEP2 & src);

    /**
     * Destructor
     */
    virtual ~COptMethodEP2();

    /**
     * Execute the optimization algorithm calling simulation routine 
     * when needed. It is noted that this procedure can give feedback 
     * of its progress by the callback function set with SetCallback.
     */

    /********Declare the prototype of member functions here**************/

    // define mutation functions
    void Set_NumParameter (int num);
    void Set_PopulationSize(int num);
    void Set_NumGeneration(int num);
    void Set_murvar(double num);
    void Set_individual(int i, int j, double num);
    void Set_CandidateValue(int i, double num);
    void Set_BestFoundSoFar(int num);
    // void Set_mutvar(double num);
    void Set_Minimum(double num);
    void Set_Maximum(double num);

    // define access functions

    int Get_NumParameter();
    double Get_BestFoundSoFar_candidate();
    int Get_NumGeneration();
    int Get_PopulationSize();

    /***********define functional functions here*************************/

    // evaluate the fitness of one individual
    //virtual double evaluate(int i);

    // copy individual o to position d
    virtual void copy(int o, int d);

    // swap individuals o and d
    virtual void swap(int o, int d);

    // exchange individuals o and d
    virtual void exchange(int o, int d);

    //mutate one individual
    //virtual void mutate(int i);

    //virtual void shuffle(void);

    // select PopulationSize individuals
    virtual void select(int method);

    // check the BestFoundSoFar individual at this NumGenerationation
    virtual int fittest(void);

    // initialise the population
    //virtual void creation(int l,  int u);

    virtual void TrackDataFile(int i);

    virtual C_INT32 optimise();
  };

//implementation of mutation functions

inline void COptMethodEP2::Set_NumParameter (int num)
{
  NumParameter = num;
}

inline void COptMethodEP2::Set_PopulationSize(int num)
{
  PopulationSize = num;
}

inline void COptMethodEP2::Set_NumGeneration(int num)
{
  NumGeneration = num;
}

/*
inline void COptMethodEP2::Set_mutvar(double num)
{
mutvar=num;
}
 */

inline void COptMethodEP2::Set_Minimum(double num)
{
  Minimum = num;
}
inline void COptMethodEP2::Set_Maximum(double num)
{
  Maximum = num;
}

inline void COptMethodEP2::Set_individual(int i, int j, double num)
{
  individual[i][j] = num;
}

inline void COptMethodEP2::Set_CandidateValue(int i, double num)
{
  CandidateValue[i] = num;
}

inline void COptMethodEP2::Set_BestFoundSoFar(int num)
{
  BestFoundSoFar = num;
}

//implementation of access functions

inline int COptMethodEP2::Get_NumParameter()
{
  return NumParameter;
}

inline double COptMethodEP2::Get_BestFoundSoFar_candidate()
{
  return CandidateValue[BestFoundSoFar];
}

inline int COptMethodEP2::Get_NumGeneration()
{
  return NumGeneration;
}

inline int COptMethodEP2::Get_PopulationSize()
{
  return PopulationSize;
}

#endif  // COPASI_COptMethodEP2
