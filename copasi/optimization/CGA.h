
/**
 *  File name: CGA.h
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the interface (.h file) of the CGA class. 
 *           It is to implement the genetic algorithm for COPASI optimization
 *  Note: Modified from Gepasi and Dingjun Chen's implementation
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


class CGA : public Coptimizer 
{
private:
	unsigned int gener;		// number of generations
	unsigned int popsize;		// size of the population
	int ncross;			// number of crossover points

        double mn,mx;

	double mutvar;			// variance for mutations
	double mutprob;			// probability of mutations
	unsigned int best;		// index of the best individual
 	int nparam;			// number of parameters

	double **indv;	// for array of individuals w/ candidate values for the parameters
 	double *candx;	// array of values of objective function f/ individuals

 	unsigned int *crp;		// indexes of the crossover points
 	unsigned int *midx;		// indexes for shuffling the population
	unsigned int *wins;		// number of wins of each individual in the tournament


public:

	CGA(); //default constructor
	CGA(int psize,int num,int param); //initialize population
	virtual ~CGA();//destructor

/********Declare the prototype of member functions here**************/

	// define mutation functions
	void Set_nparam (int num);
	void Set_popsize(int num);
	void Set_gener(int num);
	void Set_murvar(double num);
	void Set_indv(int i,int j,double num);
	void Set_candx(int i, double num);	
	void Set_best(unsigned int num);
	void Set_mutvar(double num);
	void Set_mn(double num);
	void Set_mx(double num);


	// define access functions 

	int Get_nparam() ;
	double Get_best_candidate();
	int Get_gener() ;
	int Get_popsize() ;

/***********define functional functions here*************************/

        //Set the random seed with time
	virtual int OptRandomInit();

	// evaluate the fitness of one individual
	virtual double evaluate( unsigned int i );


	// copy individual o to position d
	virtual void copy( unsigned int o, unsigned int d );


	// swap individuals o and d
	virtual void swap( unsigned int o, unsigned int d );


	//mutate one individual
	virtual void mutate( unsigned int i );


	virtual void crossover( unsigned int p1, unsigned int p2, unsigned int c1, unsigned int c2 );


	virtual void shuffle( void );

	// replicate the individuals w/ crossover
	virtual void replicate( void );

	// select popsize individuals
	virtual void select( int method );

	// check the best individual at this generation
	virtual unsigned int fittest( void );

	// initialise the population
	virtual void creation( unsigned int l, unsigned int u );

	virtual void dump_data( unsigned int i );

};

//implementation of mutation functions

inline void CGA::Set_nparam (int num)
{
nparam=num;
}

inline void CGA::Set_popsize(int num)
{
popsize=num;
}


inline void CGA::Set_gener(int num)
{
gener=num;
}


inline void CGA::Set_mutvar( double num)
{
mutvar=num;
}
inline void CGA::Set_mn( double num)
{
mn=num;
}
inline void CGA::Set_mx( double num)
{
mx=num;
}

inline void CGA::Set_indv(int i,int j,double num)
{
indv[i][j]=num;
}

inline void CGA::Set_candx(int i, double num)	
{
candx[i]=num;
}

inline void CGA::Set_best(unsigned int num)
{
best=num;
}

//implementation of access functions

inline int CGA::Get_nparam() 
{
return nparam;
}

inline double CGA::Get_best_candidate() 
{
return candx[best];
}

inline int CGA::Get_gener() 
{
return gener;
}

inline int CGA::Get_popsize() 
{
return popsize;
}


#endif //





#ifdef XXXX    // debug purpose


*************
********

#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "float.h"
#include "..\cdatum.h"
#include "..\optparam.h"

class COptParam;
extern "C" double dr250( void );
extern "C" void r250_init(int seed);
extern "C" unsigned int r250n(unsigned n);
extern "C" double rnormal01( void );

// global variables
int debug;		        // 1 if output is to be written
unsigned int gener;	      	// number of generations
unsigned int popsize;		// size of the population
int ncross;			// number of crossover points
double mutvar;			// variance for mutations
double mutprob;			// probability of mutations
unsigned int best;		// index of the best individual
int nparam;			// number of parameters
int nconstr;			// number of constraints
double tau1;			// parameter for updating variances
double tau2;			// parameter for updating variances
COptParam **parameter;		// array of parameters being searched
COptParam **constraint;		// array of constraints
double **indv;			// for array of individuals w/ candidate values for the parameters
double *candx;			// array of values of objective function f/ individuals
unsigned int *crp;		// indexes of the crossover points
unsigned int *midx;		// indexes for shuffling the population
unsigned int *wins;		// number of wins of each individual in the tournament
double (*f) (void);		// pointer to function evaluations
void (*callback) (double);	// pointer to callback function



void OptDLLName( char *name );
int OptDLLInit();
char * OptDLLParameterName( int p, char *name );
int OptDLLParameterNumber( void );
void OptDLLSetMethodParameter( int n, double p );
int OptDLLVersion( void );
int OptDLLIsConstrained( void );
int OptDLLIsBounded( void );
int OptDLLSolveLsq( double (*feval) (double *) );
void OptDLLSetCallback( void (*cb) (double) );
void OptDLLClearMemory( void );
int OptDLLRoutines( void );
int OptDLLCreateArrays( int p, int c, int r );
void OptDLLSetOptParam( int i, COptParam *pr );
void OptDLLSetConstr( int i, COptParam *pr );
double OptDLLGetOptParameter( int i );
double OptDLLGetObjF( void );
int OptDLLOptimise( double (*feval) (void) );

/*   //see above

extern "C" __declspec( dllexport ) void OptDLLName( char *name );
extern "C" __declspec( dllexport ) int OptDLLInit();
extern "C" __declspec( dllexport ) char * OptDLLParameterName( int p, char *name );
extern "C" __declspec( dllexport ) int OptDLLParameterNumber( void );
extern "C" __declspec( dllexport ) void OptDLLSetMethodParameter( int n, double p );
extern "C" __declspec( dllexport ) int OptDLLVersion( void );
extern "C" __declspec( dllexport ) int OptDLLIsConstrained( void );
extern "C" __declspec( dllexport ) int OptDLLIsBounded( void );
extern "C" __declspec( dllexport ) int OptDLLSolveLsq( double (*feval) (double *) );
extern "C" __declspec( dllexport ) void OptDLLSetCallback( void (*cb) (double) );
extern "C" __declspec( dllexport ) void OptDLLClearMemory( void );
extern "C" __declspec( dllexport ) int OptDLLRoutines( void );
extern "C" __declspec( dllexport ) int OptDLLCreateArrays( int p, int c, int r );
extern "C" __declspec( dllexport ) void OptDLLSetOptParam( int i, COptParam *pr );
extern "C" __declspec( dllexport ) void OptDLLSetConstr( int i, COptParam *pr );
extern "C" __declspec( dllexport ) double OptDLLGetOptParameter( int i );
extern "C" __declspec( dllexport ) double OptDLLGetObjF( void );
extern "C" __declspec( dllexport ) int OptDLLOptimise( double (*feval) (void) );

*/


// evaluate the fitness of one individual
double evaluate( unsigned int i );

// copy individual o to position d
void copy( unsigned int o, unsigned int d );

// swap individuals o and d
void swap( unsigned int o, unsigned int d );

//mutate one individual
void mutate( unsigned int i );

void crossover( unsigned int p1, unsigned int p2, unsigned int c1, unsigned int c2 );

void shuffle( void );

// replicate the individuals w/ crossover
void replicate( void );

// select popsize individuals
void select( int method );

// check the best individual at this generation
unsigned int fittest( void );

// initialise the population
void creation( unsigned int l, unsigned int u );

// routines used for debugging
void dump_data_init( void );

void dump_data( unsigned int i );


#endif  // XXXX





