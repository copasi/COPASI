
/**
 *  File name: CGA.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the interface (.h file) of the CGA class. 
 *           It is to implement the genetic algorithm for COPASI optimization
 */


#ifndef CGA_H
#define CGA_H


#define TRUE 1
#define FALSE 0


#include <iostream.h>
#include <iomanip.h>
#include <fstream.h>
#include <sys/times.h>
#include <sys/types.h>
#include "stdio.h"
#include "stdlib.h"
#include "stddef.h"
#include "time.h"
#include "ctype.h"
#include "string.h"
#include "math.h"
#include "float.h"
#include "r250.h"
#include <cstdlib>


#include "COptAlgorithm.h"
#include "CRealProblem.h"

//using namespace std;


class CGA : public COptAlgorithm
{
  //private members
private:
  unsigned int mGener;	     // number of generations
  unsigned int mPopSize;     // size of the population
  int mCrossNum;	     // number of crossover points
  double mMin,mMax;
  double mMutVar;	     // variance for mutations
  double mMutProb;	     // probability of mutations
  unsigned int mBest;	     // index of the best individual
  int mParamNum;	     // number of parameters
  double **mIndV;  // for array of individuals w/ candidate values for the parameters
  double *mCandX;	     // array of values of objective function f/ individuals
  unsigned int *mCrp;	     // indexes of the crossover points
  unsigned int *mMidX;	     // indexes for shuffling the population
  unsigned int *mWins;	     // number of wins of each individual in the tournament

  //YOHE: new: add CRealProblem class for testing purpose 
  CRealProblem mRealProblem;

  //implementations
public:

  /**
   * default constructor
   */
  CGA(); 

  /**
   * constructor for initializing population 
   */
  CGA(int psize,int num,int param); 

  /**
   * Copy constructor
   * @param source a CGA object for copy
   */
  CGA(const CGA& source);

  /**
   * Object assignment overloading
   * @param source a CGA object for copy
   * @return an assigned CGA object
   */
  CGA& operator=(const CGA& source);

 
  /**
   * destructor
   */
  ~CGA();

  /**
   * initialize function
   */
  void initialize();

  /**
   * initialize the first generation
   */
  void initFirstGeneration();

  /**
   * clean up 
   */
  void cleanup();

  /**Declare the prototype of member functions ***/

  // define mutation functions

  /**
   * set real problem
   */
  void setRealProblem(CRealProblem & aProb);

  /**
   * set parameter
   */
  void setParamNum (int num);

  /**
   * set population size
   */
  void setPopSize(int num);

  /**
   * set generation number
   */
  void setGeneration(int num);

  /**
   * set mIndV, the private member
   */
  void setIndv(int i,int j,double num);

  /**
   * set mCandX, the private member
   */
  void setCandx(int i, double num);

  /**
   * set the best result
   */	
  void setBest(unsigned int num);

  /**
   * set the mutation variance
   */
  void setMutVar(double num);

  /**
   * set the minimum
   */
  void setMin(double num);

  /**
   * set the max
   */
  void setMax(double num);


  // define access functions 

  /**
   * get the parameter number
   */
  int getParamNum() ;

  /**
   * get the best candidate
   */
  double getBestCandidate();

  /**
   * get generation number
   */
  int getGeneration() ;

  /**
   * get population size
   */
  int getPopSize() ;
 
  /*****define functional functions here**********/

  /**
   * Set the random seed with time
   */
  int initOptRandom();
 
  /**
   *  evaluate the fitness of one individual
   */
  double evaluate( unsigned int i );

 
  /**
   * copy individual o to position d
   */
  void copy( unsigned int o, unsigned int d );


  /**
   * swap individuals o and d
   */
  void swap( unsigned int o, unsigned int d );

  /**
   * process mutation
   */
  void mutate( unsigned int i );

  /**
   * process crossover
   */
  void crossover( unsigned int p1, unsigned int p2, unsigned int c1, unsigned int c2 );

  /**
   * shuffle data
   */
  void shuffle( void );
  
  /**
   * replicate the individuals w/ crossover
   */
  void replicate( void );
  
  /**
   *  select popsize individuals
   */
  void select( int method );
 
  /**
   *  check the best individual at this generation
   */
  unsigned int fittest( void );
  
  /**
   * initialise the population
   */
  void creation( unsigned int l, unsigned int u );

  /**
   * dump data to a file
   */
  void dumpData( unsigned int i );

  /**
   * optimization function
   */
  int optimise();

};



#endif //
