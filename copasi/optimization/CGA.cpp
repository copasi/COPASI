/**
 *  File name: CGA.cpp
 *
 *  Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the implementation (.cpp file) of the CGA class. 
 *           It is to implement the genetic algorithm for COPASI optimization
 *  Note: Modified from Gepasi and Dingjun Chen's implementation
 */



#include "CGA.h"

/******************The following is implementation of various functions*********/

CGA::CGA()
{

 crp = NULL;
 midx = NULL;
 indv = NULL;
 candx = NULL;
 wins = NULL;
 indv = NULL;
}

CGA::CGA(int psize,int num, int param)
{

 unsigned int i,j;

 popsize=psize;
 gener=num;
 nparam=param;

 candx = new double[2*psize];
 // create array for tournament
 wins = new unsigned int[2*psize];
 // create array for crossover points
 crp = new unsigned int[param];
 // create array for shuffling the population
 midx = new unsigned int[psize];
 // create the population array
 indv = new double*[2*psize];
 // create the individuals
 for( i=0; i<2*psize; i++ )
 {
  indv[i] = new double[param];
 }


 for( i=0; i<nparam; i++ )
  indv[0][i] =1.1+dr250();

 try
 {
  // calculate the fitness
  candx[0] = evaluate(0);
 }
 catch( unsigned int e )
 {
  candx[0] = DBL_MAX;
 }

 // the others are randomly generated
 creation( 1, popsize);
 best=fittest();

}


CGA::~CGA()
{
delete indv;
delete midx;
delete crp;
delete wins;
delete candx;
}


int CGA::OptRandomInit()
{
 struct tms init_time;
 times(&init_time);
 r250_init( init_time.tms_utime);
 return 0;
}

// evaluate the fitness of one individual
double CGA::evaluate( unsigned int i )
{
 int j;
 bool outside_range = FALSE;
 double fitness;
 double fitness0;
 double tmp; 

 // evaluate the fitness
 try
 {
  fitness0=0;
  for(j=0;j<nparam;j++)
   {
     fitness=fitness0+pow(indv[i][j],4.0)-16.0*pow(indv[i][j],2.0)+5.0*indv[i][j];
     fitness0=fitness;
    }
    fitness=fitness0/2.0;
 }
 catch( unsigned int e )
 {
  fitness = DBL_MAX;
 }

 return fitness;
}

// copy individual o to position d
void CGA::copy( unsigned int o, unsigned int d )
{
 int i;
 for( i=0; i<nparam; i++ )
  indv[d][i] = indv[o][i];
 candx[d] = candx[o];
}

// swap individuals o and d
void CGA::swap( unsigned int o, unsigned int d )
{
 int i;
 double tmp;
 for( i=0; i<nparam; i++ )
 {
  tmp = indv[d][i];
  indv[d][i] = indv[o][i];
  indv[o][i] = tmp;
 }
 tmp = candx[d];
 candx[d] = candx[o];
 candx[o] = tmp;
 i = wins[d];
 wins[d] = wins[o];
 wins[o] = i;
}

//mutate one individual
void CGA::mutate( unsigned int i )
{
 int j;
 //double mn, mx, mut;
 double  mut;
 // mutate the parameters

   // calculate the mutatated parameter
   mut = indv[i][j] * ( 1 + mutvar * rnormal01()); 
  
  // force it to be within the bounds
   if( mut <= mn ) mut = mn + DBL_EPSILON;
   else
   {if( mut < mn ) mut = mn;}
 
  if( mut >= mx ) mut = mx - DBL_EPSILON;
   else
   {if( mut > mx ) mut = mx;}
   // store it
   indv[i][j] = mut;

 // evaluate the fitness
 candx[i] = evaluate(i);
}

void CGA::crossover( unsigned int p1, unsigned int p2, unsigned int c1, unsigned int c2 )
{
 int i, j, s, e;
 unsigned int pp1, pp2, tmp, l;
 try
 {
  if( nparam > 1 )
  {
   // get a random number of crossover points, always less than half the number of genes
   ncross = r250n( (unsigned int) nparam / 2 );
  }
  else ncross = 0;
  // if less than 0 just copy parent to child
  if( ncross == 0 )
  {
   for( j=0; j<nparam; j++ )
   {
    indv[c1][j] = indv[p1][j];
    indv[c2][j] = indv[p2][j];
   }
   return;
  }
  // chose first point
  crp[0] = 1 + r250n(nparam-ncross);
  // chose the others
  for( i=1; i<ncross; i++ )
  {
   l = nparam - ncross + i - 1 - crp[i-1];
   crp[i] = 1 + crp[i-1] + ( l==0 ? 0 : r250n( l ) );
  }
  // copy segments
  pp1 = p2; pp2 = p1;
  for( i=0; i<=ncross; i++ )
  {
   // swap the indexes
   tmp = pp1;
   pp1 = pp2;
   pp2 = tmp;
   if( i==0 ) s = 0; else s = crp[i-1];
   if( i==ncross) e = nparam; else e = crp[i];
   for( j=s; j<e; j++ )
   {
    indv[c1][j] = indv[pp1][j];
    indv[c2][j] = indv[pp2][j];
   }
  }
 }
 catch( unsigned int e )
 {
 }
}

void CGA::shuffle( void )
{
 unsigned int i, a, b, tmp;
 for( i=0; i<popsize; i++ ) midx[i] = i;
 for( i=0; i<popsize/2; i++ )
 {
  a = r250n(popsize);
  b = r250n(popsize);
  tmp = midx[a];
  midx[a] = midx[b];
  midx[b] = tmp;
 }
}

// replicate the individuals w/ crossover
void CGA::replicate( void )
{
 unsigned int i;
 
 // generate a random order for the parents
 shuffle();
 // reproduce in consecutive pairs
 for( i=0; i<popsize/2; i++ )
  crossover( midx[i*2], midx[i*2+1], popsize + i*2, popsize + i*2+1 );
 // check if there is one left over and just copy it
 if( popsize % 2 > 0 ) copy( popsize-1, 2*popsize-1 );
 // mutate the offspring
 for( i=0; i<popsize; i++ )
  mutate( popsize+i );
}

// select popsize individuals
void CGA::select( int method )
{
 unsigned int i, j, nopp, opp;
 switch( method )
 {
  case 1:  // parent-offspring competition
	       for( i=popsize; i<2*popsize; i++ )
           {
            // if offspring is fitter keep it
            if( candx[i] < candx[j] ) copy( i, j );
           }
		   break;
  case 2:  // tournament competition
	       // compete with 20% of the population
           nopp = popsize / 5;
		   // but at least one
           if( nopp<1 ) nopp = 1;
		   // parents and offspring are all in competition
           for( i=0; i<2*popsize; i++ )
           {
            wins[i] = 0;
            for( j=0; j<nopp; j++ )
            {
			 // get random opponent
             opp = r250n(popsize*2);
             if( candx[i] <= candx[opp] ) wins[i]++;
            }
           }
           // selection of top popsize winners
           for( i=0; i< popsize; i++ )
            for( j=i+1; j<2*popsize; j++ )
             if( wins[i] < wins[j] ) swap( i, j );
		   break;
 }
}

// check the best individual at this generation
unsigned int CGA::fittest( void )
{
 unsigned int i,b;
 double f;
 f = candx[0];
 b = 0;
 for( i=1; i<popsize; i++ )
  if( candx[i] < f )
  {
   b = i;
   f = candx[i];
  }
 return b;
}

// initialise the population
void CGA::creation( unsigned int l, unsigned int u )
{
 unsigned int i;
 int j;

// double mn, mx, la;
 double la;

// BOOL linear;
  bool linear;
 for( i=l; i<u; i++ )
 {
 
 for( j=0; j<nparam; j++ )
  {
   try
   {
    // determine if linear or log scale
    linear = FALSE; la = 1.0;
    if( mn==0.0 ) mn = DBL_EPSILON;
    if( (mx<=0.0) || (mn<=0.0) ) linear = TRUE;
    else
    {
 	 la = log10(mx) - log10(mn); 
	 if( la < 1.8 ) linear = TRUE;
    }
    // set it to a random value within the interval
    if( linear )
     indv[i][j] = mn + dr250() * (mx - mn);
    else
     indv[i][j] = mn *pow( 10, la*dr250() );
   }
   catch( unsigned int e )
   {
    indv[i][j] = (mx - mn)*0.5 + mn;
   }
  }
  try
  {
   // calculate its fitness 
   candx[i] = evaluate(i);
  }
  catch( unsigned int e )
  {
   candx[i] = DBL_MAX;
  }
 }
 // get the index of the fittest
 best = fittest();
}


void CGA::dump_data( unsigned int i )
{
 ofstream finalout("debugopt.dat",ios::app);
 
 if(!finalout)
   	{
   	cout<<"debugopt.dat cannot be opened!"<<endl;
  	exit(1);
	}
 finalout<<"#"<<i<<"\t"<<candx[best]<<endl;
 for(int j=0;j<nparam;j++) 
    {
     finalout<<indv[best][j]<<"\t";
    }
  finalout<<endl;
  finalout<<endl;
  finalout.close();

}


// main.cc changed to optimise function
//main(int argc, char *argv[])
//
void CGA::Optimise(int argc, char *argv[])
{

 unsigned int i, last_update, u100, u300, u500, fr;
 double bx;

 struct tms before,after;
 double dTime=0;
   
 if(argc<4)
  { 
   cout<<endl<<"Usage: ga nparam mini_bound maxi_bond"<<endl; 
  exit(1);
  }
 
 times(&before);
 dTime=time(NULL);

 CGA Ga_10param(4000,4000, atoi(argv[1]));  //define a object

 Ga_10param.Set_mn(atoi(argv[2]));
 Ga_10param.Set_mx(atoi(argv[3]));

//Initialise the random number generator with time
 Ga_10param.OptRandomInit();

 // initialise the variance for mutations
 Ga_10param.Set_mutvar(0.1);

 // initialise the update registers
 last_update = 0;
 u100 = u300 = u500 = 0;


 //Display layout of all MPI processes
 cout<<endl;
 cout<<"Initial populaiton has successfully created!!!!!"<<endl;


 // and store that value
 bx = Ga_10param.Get_best_candidate();
 
 ofstream finalout("debugopt.dat");
 if(!finalout)
   	{
   	cout<<"debugopt.dat cannot be opened!"<<endl;
  	exit(1);
	}
 finalout<<"-----------------------------best result at each generation---------------------"<<endl;
 finalout<<"Generation\t"<<"Best candidate value for object function\t"<<"Display "<<Ga_10param.Get_nparam()<<" parameters"<<endl; 
 finalout<<endl;
 finalout.close();


int psize = Ga_10param.Get_popsize();  

// ITERATE FOR gener GENERATIONS

for( i=0; i<Ga_10param.Get_gener(); i++ )
{
  cout<<endl;
  cout<<"GA is processing at generation "<<i<<endl;
 
  Ga_10param.dump_data( i );
  // replicate the individuals
  Ga_10param.replicate();
  // select the most fit
  Ga_10param.select( 2 );
  // get the index of the fittest
 // best = fittest();
 Ga_10param.Set_best(Ga_10param.fittest());
  if(Ga_10param.Get_best_candidate()!= bx )
  {
   last_update = i;
   bx = Ga_10param.Get_best_candidate();
  }
  if( u100 ) u100--;
  if( u300 ) u300--;
  if( u500 ) u500--;

  // perturb the population if we have stalled for a while
  if( (u500==0) && (i-last_update > 500) )
  {
   Ga_10param.creation( psize/2, psize );
   u500 = 500; u300=300; u100=100;
  }

  else
  {
   if( (u300==0) && (i-last_update > 300) )
   {
	Ga_10param.creation( unsigned(psize*0.7), psize );
	u300=300; u100=100;
   }

   else
    if( (u100==0) && (i-last_update > 100) ) 
   {
	Ga_10param.creation( unsigned(psize*0.9), psize );
	u100=100;
   }
  }

 }

 times(&after);
 ofstream tout("time.dat");
 if(!tout)
	{ cout<<" tout cannot output!"<<endl;
	exit(0);
        }
 tout<<"CPU's Calculation Time:"<<after.tms_utime-before.tms_utime<<endl;
 tout<<" It has taken about "<<time(NULL)-dTime<<" seconds!"<<endl;
 tout.close();
 
 cout<<endl;
 cout<<"GA has successfully done!"<<endl;
 cout<<" It has taken about "<<time(NULL)-dTime<<" seconds!"<<endl;
 cout<<"and it is ready to exit now!"<<endl;

}



#ifdef XX


#include "CGA.h"

//#include "stdafx.h"
#include "stdio.h"
#include "string.h"
#include "math.h"
#include "float.h"
//#include "..\cdatum.h"
//#include "..\optparam.h"

class COptParam;
extern "C" double dr250( void );
extern "C" void r250_init(int seed);
extern "C" unsigned int r250n(unsigned n);
extern "C" double rnormal01( void );


/*
//YOHE: these definitions are not necessary because they are there in CGA.h file.
// exactly the same

// global variables
int debug;			// 1 if output is to be written
unsigned int gener;		// number of generations
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

*/

// evaluate the fitness of one individual
double evaluate( unsigned int i )
{
 int j;
 BOOL outside_range = FALSE;
 double fitness;
 // set the paramter values
 for( j=0; j<nparam; j++ )
 {
  *(parameter[j]->Parameter.Value) = indv[i][j];
 }
 // evaluate the fitness
 try
 {
  fitness = (*f)();
 }
 catch( unsigned int e )
 {
  fitness = DBL_MAX;
 }
 // verify all constraints
 for( j=0; j<nconstr; j++ )
 {
  if( constraint[j]->MaxIneq )
  { 
   switch( constraint[j]->MaxType )
   {
    case 1: if( *(constraint[j]->Parameter.Value) >= constraint[j]->MaxD ) outside_range = TRUE; break;
    case 2: if( *(constraint[j]->Parameter.Value) >= *(constraint[j]->MaxP.Value) ) outside_range = TRUE; break;
    case 4: if( *(constraint[j]->Parameter.Value) >= constraint[j]->MinD * ( 1.0  + constraint[j]->MaxD) ) outside_range = TRUE; break;
   }
  }
  else
  { 
   switch( constraint[j]->MaxType )
   {
    case 1: if( *(constraint[j]->Parameter.Value) > constraint[j]->MaxD ) outside_range = TRUE; break;
    case 2: if( *(constraint[j]->Parameter.Value) > *(constraint[j]->MaxP.Value) ) outside_range = TRUE; break;
    case 4: if( *(constraint[j]->Parameter.Value) > constraint[j]->MinD * ( 1.0  + constraint[j]->MaxD) ) outside_range = TRUE; break;
   }
  }
  if( constraint[j]->MinIneq )
  { 
   switch( constraint[j]->MinType )
   {
    case 1: if( *(constraint[j]->Parameter.Value) < constraint[j]->MinD ) outside_range = TRUE; break;
    case 2: if( *(constraint[j]->Parameter.Value) < *(constraint[j]->MinP.Value) ) outside_range = TRUE; break;
    case 4: if( *(constraint[j]->Parameter.Value) < constraint[j]->MinD * ( 1.0  - constraint[j]->MaxD) ) outside_range = TRUE; break;
   }
  }
  else
  { 
   switch( constraint[j]->MinType )
   {
    case 1: if( *(constraint[j]->Parameter.Value) <= constraint[j]->MinD ) outside_range = TRUE; break;
    case 2: if( *(constraint[j]->Parameter.Value) <= *(constraint[j]->MinP.Value) ) outside_range = TRUE; break;
    case 4: if( *(constraint[j]->Parameter.Value) <= constraint[j]->MinD * ( 1.0  - constraint[j]->MaxD) ) outside_range = TRUE; break;
   }
  }
 }
 // if outside range make the fitness very large
 if( outside_range ) fitness = DBL_MAX;
 // return the value
 return fitness;
}

// copy individual o to position d
void copy( unsigned int o, unsigned int d )
{
 int i;
 for( i=0; i<nparam; i++ )
  indv[d][i] = indv[o][i];
 candx[d] = candx[o];
}

// swap individuals o and d
void swap( unsigned int o, unsigned int d )
{
 int i;
 double tmp;
 for( i=0; i<nparam; i++ )
 {
  tmp = indv[d][i];
  indv[d][i] = indv[o][i];
  indv[o][i] = tmp;
 }
 tmp = candx[d];
 candx[d] = candx[o];
 candx[o] = tmp;
 i = wins[d];
 wins[d] = wins[o];
 wins[o] = i;
}

//mutate one individual
void mutate( unsigned int i )
{
 int j;
 double mn, mx, mut;
 // mutate the parameters
 for( j=0; j<nparam; j++ )
 {
  // calculate lower and upper bounds
  switch( parameter[j]->MaxType )
  {
   case 1: mx = parameter[j]->MaxD; break;
   case 2: mx = *(parameter[j]->MaxP.Value); break;
   case 3: mx = DBL_MAX; break;
   case 4: mx = parameter[j]->MinD * ( 1.0  + parameter[j]->MaxD); break;
   default: mx = DBL_MAX;
  }
  switch( parameter[j]->MinType )
  {
   case 1: mn = parameter[j]->MinD; break;
   case 2: mn = *(parameter[j]->MinP.Value); break;
   case 3: mn = -DBL_MAX; break;
   case 4: mn = parameter[j]->MinD * ( 1.0  - parameter[j]->MaxD); break;
   default: mn = -DBL_MAX;
  }
  try
  {
   // calculate the mutatated parameter
   mut = indv[i][j] * ( 1 + mutvar * rnormal01()); 
   // force it to be within the bounds
   if( parameter[j]->MinIneq )
   { if( mut <= mn ) mut = mn + DBL_EPSILON;}
   else
   {if( mut < mn ) mut = mn;}
   if( parameter[j]->MaxIneq )
   {if( mut >= mx ) mut = mx - DBL_EPSILON;}
   else
   {if( mut > mx ) mut = mx;}
   // store it
   indv[i][j] = mut;
  }
  catch( unsigned int e )
  {
  }
 }
 // evaluate the fitness
 candx[i] = evaluate(i);
}

void crossover( unsigned int p1, unsigned int p2, unsigned int c1, unsigned int c2 )
{
 int i, j, s, e;
 unsigned int pp1, pp2, tmp, l;
 try
 {
  if( nparam > 1 )
  {
   // get a random number of crossover points, always less than half the number of genes
   ncross = r250n( (unsigned int) nparam / 2 );
  }
  else ncross = 0;
  // if less than 0 just copy parent to child
  if( ncross == 0 )
  {
   for( j=0; j<nparam; j++ )
   {
    indv[c1][j] = indv[p1][j];
    indv[c2][j] = indv[p2][j];
   }
   return;
  }
  // chose first point
  crp[0] = 1 + r250n(nparam-ncross);
  // chose the others
  for( i=1; i<ncross; i++ )
  {
   l = nparam - ncross + i - 1 - crp[i-1];
   crp[i] = 1 + crp[i-1] + ( l==0 ? 0 : r250n( l ) );
  }
  // copy segments
  pp1 = p2; pp2 = p1;
  for( i=0; i<=ncross; i++ )
  {
   // swap the indexes
   tmp = pp1;
   pp1 = pp2;
   pp2 = tmp;
   if( i==0 ) s = 0; else s = crp[i-1];
   if( i==ncross) e = nparam; else e = crp[i];
   for( j=s; j<e; j++ )
   {
    indv[c1][j] = indv[pp1][j];
    indv[c2][j] = indv[pp2][j];
   }
  }
 }
 catch( unsigned int e )
 {
 }
}

void shuffle( void )
{
 unsigned int i, a, b, tmp;
 for( i=0; i<popsize; i++ ) midx[i] = i;
 for( i=0; i<popsize/2; i++ )
 {
  a = r250n(popsize);
  b = r250n(popsize);
  tmp = midx[a];
  midx[a] = midx[b];
  midx[b] = tmp;
 }
}

// replicate the individuals w/ crossover
void replicate( void )
{
 unsigned int i;
 
 // generate a random order for the parents
 shuffle();
 // reproduce in consecutive pairs
 for( i=0; i<popsize/2; i++ )
  crossover( midx[i*2], midx[i*2+1], popsize + i*2, popsize + i*2+1 );
 // check if there is one left over and just copy it
 if( popsize % 2 > 0 ) copy( popsize-1, 2*popsize-1 );
 // mutate the offspring
 for( i=0; i<popsize; i++ )
  mutate( popsize+i );
}

// select popsize individuals
void select( int method )
{
 unsigned int i, j, nopp, opp;
 switch( method )
 {
  case 1:  // parent-offspring competition
	       for( i=popsize; i<2*popsize; i++ )
           {
            // if offspring is fitter keep it
            if( candx[i] < candx[j] ) copy( i, j );
           }
		   break;
  case 2:  // tournament competition
	       // compete with 20% of the population
           nopp = popsize / 5;
		   // but at least one
           if( nopp<1 ) nopp = 1;
		   // parents and offspring are all in competition
           for( i=0; i<2*popsize; i++ )
           {
            wins[i] = 0;
            for( j=0; j<nopp; j++ )
            {
			 // get random opponent
             opp = r250n(popsize*2);
             if( candx[i] <= candx[opp] ) wins[i]++;
            }
           }
           // selection of top popsize winners
           for( i=0; i< popsize; i++ )
            for( j=i+1; j<2*popsize; j++ )
             if( wins[i] < wins[j] ) swap( i, j );
		   break;
 }
}

// check the best individual at this generation
unsigned int fittest( void )
{
 unsigned int i,b;
 double f;
 f = candx[0];
 b = 0;
 for( i=1; i<popsize; i++ )
  if( candx[i] < f )
  {
   b = i;
   f = candx[i];
  }
 return b;
}


// initialise the population
void creation( unsigned int l, unsigned int u )
{
 unsigned int i;
 int j;
 double mn, mx, la;
 BOOL linear;
 for( i=l; i<u; i++ )
 {
  for( j=0; j<nparam; j++ )
  {
   // calculate lower and upper bounds
   switch( parameter[j]->MaxType )
   {
    case 1: mx = parameter[j]->MaxD; break;
	case 2: mx = *(parameter[j]->MaxP.Value); break;
	case 3: mx = DBL_MAX; break;
    case 4: mx = parameter[j]->MinD * ( 1.0  + parameter[j]->MaxD); break;
	default: mx = DBL_MAX;
   }
   switch( parameter[j]->MinType )
   {
    case 1: mn = parameter[j]->MinD; break;
	case 2: mn = *(parameter[j]->MinP.Value); break;
	case 3: mn = -DBL_MAX; break;
    case 4: mn = parameter[j]->MinD * ( 1.0  - parameter[j]->MaxD); break;
	default: mn = -DBL_MAX;
   }
   try
   {
    // determine if linear or log scale
    linear = FALSE; la = 1.0;
    if( mn==0.0 ) mn = DBL_EPSILON;
    if( (mx<=0.0) || (mn<=0.0) ) linear = TRUE;
    else
    {
 	 la = log10(mx) - log10(mn); 
	 if( la < 1.8 ) linear = TRUE;
    }
    // set it to a random value within the interval
    if( linear )
     indv[i][j] = mn + dr250() * (mx - mn);
    else
     indv[i][j] = mn *pow( 10, la*dr250() );
   }
   catch( unsigned int e )
   {
    indv[i][j] = (mx - mn)*0.5 + mn;
   }
  }
  try
  {
   // calculate its fitness 
   candx[i] = evaluate(i);
  }
  catch( unsigned int e )
  {
   candx[i] = DBL_MAX;
  }
 }
 // get the index of the fittest
 best = fittest();
}

// routines used for debugging
void dump_data_init( void )
{
 FILE *f;
 // check if debugopt.dat exists
 f = fopen( "debugopt.dat", "r" );
 if( f==NULL )
 {
  // no ouptut!
  debug = 0;
  return;
 }
 // we'll do some output
 debug = 1;
 fclose( f );
 // clear all the files
 f = fopen( "debugopt.dat", "w" );
 fclose( f );
}

void dump_data( unsigned int i )
{
 FILE *f;
 int j;
 // write the best individual
 f = fopen( "debugopt.dat", "a" );
 if( f == NULL ) return;
 fprintf( f, "%u %lg ", i, candx[best] );
 for( j=0; j<nparam; j++ ) fprintf( f, "%lg ", indv[best][j] );
 fprintf( f, "\n");
 fclose( f );
}

//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ begin dll stuff

//extern "C" __declspec( dllexport ) void OptDLLName( char *name )
void OptDLLName( char *name )
{
 strcpy( name, "Genetic algorithm" );
}

extern "C" __declspec( dllexport ) int OptDLLInit()
{
 SYSTEMTIME curtime;
 debug = 1;
 nparam = 0;
 nconstr = 0;
 parameter = NULL;
 constraint = NULL;
 crp = NULL;
 midx = NULL;
 indv = NULL;
 candx = NULL;
 wins = NULL;
 indv = NULL;
 callback = NULL;
 // initialise the random number generator with the time (milliseconds)
 GetSystemTime( &curtime);
 r250_init( (int) curtime.wMilliseconds );
 return 0;
}

//extern "C" __declspec( dllexport ) char * OptDLLParameterName( int p, char *name )
char * OptDLLParameterName( int p, char *name )
{
 switch( p )
 {
  case 0:  strcpy( name, "Generations" ); break;
  case 1:  strcpy( name, "Population" ); break;
  default: strcpy( name, "not used" );
 }
 return name;
}

//extern "C" __declspec( dllexport ) int OptDLLParameterNumber( void )
int OptDLLParameterNumber( void )
{
 return 2;
}

//extern "C" __declspec( dllexport ) void OptDLLSetMethodParameter( int n, double p )
void OptDLLSetMethodParameter( int n, double p )
{
 if( n>2 ) return;
 switch( n )
 {
  case 0: if( p>0.0 ) gener = (unsigned int) p; else gener = 0; break;
  case 1: if( p>2.0 ) popsize = (unsigned int) p; else popsize = 2; break;
  case 2: if( p>0.0 ) mutprob = p; else mutprob = 0.0; break;
 }
}

//extern "C" __declspec( dllexport ) int OptDLLVersion( void )
int OptDLLVersion( void )
{
 return 100301;
}

//extern "C" __declspec( dllexport ) int OptDLLIsConstrained( void )
int OptDLLIsConstrained( void )
{
 return 1;
}

//extern "C" __declspec( dllexport ) int OptDLLIsBounded( void )
int OptDLLIsBounded( void )
{
 return 1;
}

//extern "C" __declspec( dllexport ) int OptDLLSolveLsq( double (*feval) (double *) )
int OptDLLSolveLsq( double (*feval) (double *) )
{
 return -1;
}

//extern "C" __declspec( dllexport ) void OptDLLSetCallback( void (*cb) (double) )
void OptDLLSetCallback( void (*cb) (double) )
{
 callback = cb;
}

//extern "C" __declspec( dllexport ) void OptDLLClearMemory( void )
void OptDLLClearMemory( void )
{
 unsigned int i;
 if( indv != NULL )
 {
  for(i=0;i<2*popsize;i++) 
   if( indv[i] != NULL ) 
   {
	delete [] indv[i];
	indv[i] = NULL;
   }
  delete [] indv;
  indv = NULL;
 }
 if( midx != NULL )
 {
  delete [] midx;
  midx = NULL;
 }
 if( crp != NULL )
 {
  delete [] crp;
  crp = NULL;
 }
 if( wins != NULL )
 {
  delete [] wins;
  wins = NULL;
 }
 if( candx != NULL )
 {
  delete [] candx;
  candx = NULL;
 }
 if( parameter != NULL )
 {
  delete [] parameter;
  parameter = NULL;
 }
 if( constraint != NULL )
 {
  delete [] constraint;
  constraint = NULL;
 }
}

//extern "C" __declspec( dllexport ) int OptDLLRoutines( void )
int OptDLLRoutines( void )
{
 // 1 - only DLLOptimise
 // 2 - only DLLSolveLsq
 // 3 - both
 return 1;
}

//extern "C" __declspec( dllexport ) int OptDLLCreateArrays( int p, int c, int r )
int OptDLLCreateArrays( int p, int c, int r )
{
 unsigned int i,j;
 parameter = new COptParam *[p];
 if( parameter == NULL ) return 1;
 constraint = new COptParam *[c];
 if( constraint == NULL )
 {
  OptDLLClearMemory();
  return 2;
 }
 // create the array for fitnesses
 candx = new double[2*popsize];
 if( candx == NULL )
 {
  OptDLLClearMemory();
  return 3;
 }
 // create array for tournament
 wins = new unsigned int[2*popsize];
 if( wins == NULL )
 {
  OptDLLClearMemory();
  return 4;
 }
 // create array for crossover points
 crp = new unsigned int[p];
 if( crp == NULL )
 {
  OptDLLClearMemory();
  return 5;
 }
 // create array for shuffling the population
 midx = new unsigned int[popsize];
 if( midx == NULL )
 {
  OptDLLClearMemory();
  return 6;
 }
 // create the population array
 indv = new double*[2*popsize];
 if( indv == NULL )
 {
  OptDLLClearMemory();
  return 7;
 }
 // create the individuals
 for( i=0; i<2*popsize; i++ )
 {
  indv[i] = new double[p];
  if( indv[i] == NULL )
  {
   for(j=0;j<i;j++) delete [] indv[j];
   delete [] indv;
   indv = NULL;
   OptDLLClearMemory();
   return 8;
  }
 }
 nparam = p;
 nconstr = c;
 // successful memory allocation
 return 0;
}

//extern "C" __declspec( dllexport ) void OptDLLSetOptParam( int i, COptParam *pr )
 void OptDLLSetOptParam( int i, COptParam *pr )
{
 if( (parameter==NULL) || (i>nparam) ) return;
 parameter[i] = pr;
}

//extern "C" __declspec( dllexport ) void OptDLLSetConstr( int i, COptParam *pr )
void OptDLLSetConstr( int i, COptParam *pr )
{
 if( (parameter==NULL) || (i>nconstr) ) return;
 constraint[i] = pr;
}

//extern "C" __declspec( dllexport ) double OptDLLGetOptParameter( int i )
double OptDLLGetOptParameter( int i )
{
 return indv[best][i];
}

//extern "C" __declspec( dllexport ) double OptDLLGetObjF( void )
double OptDLLGetObjF( void )
{
 return candx[best];
}


//extern "C" __declspec( dllexport ) int OptDLLOptimise( double (*feval) (void) )
int OptDLLOptimise( double (*feval) (void) )
{
 unsigned int i, last_update, u10, u30, u50, fr;
 double bx;

 dump_data_init();
 if( debug )
 {
//  int fr = gener / 100;
//  if( fr==0 ) fr=1;
  fr=1;
 }
 // store the pointer to the function calls
 f = feval;
 // initialise the variance for mutations
 mutvar = 0.1;
 // initialise the update registers
 last_update = 0;
 u10 = u30 = u50 = 0;
 // initialise the population
 // first individual is the initial guess
 for( i=0; i<nparam; i++ )
  indv[0][i] = *(parameter[i]->Parameter.Value);
 try
 {
  // calculate the fitness
  candx[0] = evaluate(0);
 }
 catch( unsigned int e )
 {
  candx[0] = DBL_MAX;
 }
 // the others are random
 creation( 1, popsize );
 // initialise the update register
 last_update = 0;
 // get the index of the fittest
 best = fittest();
 // and store that value
 bx = candx[best];
 // ITERATE FOR gener GENERATIONS
 for( i=0; i<gener; i++ )
 {
  if( debug )  if( i%fr == 0 ) dump_data( i );
  // replicate the individuals
  replicate();
  // select the most fit
  select( 2 );
  // get the index of the fittest
  best = fittest();
  if( candx[best] != bx )
  {
   last_update = i;
   bx = candx[best];
  }
  if( u10 ) u10--;
  if( u30 ) u30--;
  if( u50 ) u50--;
  // perturb the population if we have stalled for a while
  if( (u50==0) && (i-last_update > 50) )
  {
   creation( popsize/2, popsize );
   u50 = 50; u30=30; u10=10;
  }
  else
  {
   if( (u30==0) && (i-last_update > 30) )
   {
	creation( unsigned(popsize*0.7), popsize );
	u30=30; u10=10;
   }
   else
    if( (u10==0) && (i-last_update > 10) ) 
   {
	creation( unsigned(popsize*0.9), popsize );
	u10=10;
   }
  }
  // signal another generation
  if( callback != NULL ) callback( candx[best] );
 }
 return 0;
}


//$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$$ end dll stuff


#endif // XX


#ifdef XXXX

// ga.cpp : Genetic algorithm optimisation.
//

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
int debug;					// 1 if output is to be written
unsigned int gener;			// number of generations
unsigned int popsize;		// size of the population
int ncross;					// number of crossover points
double mutvar;				// variance for mutations
double mutprob;				// probability of mutations
unsigned int best;			// index of the best individual
int nparam;					// number of parameters
int nconstr;				// number of constraints
double tau1;				// parameter for updating variances
double tau2;				// parameter for updating variances
COptParam **parameter;		// array of parameters being searched
COptParam **constraint;		// array of constraints
double **indv;				// for array of individuals w/ candidate values for the parameters
double *candx;				// array of values of objective function f/ individuals
unsigned int *crp;			// indexes of the crossover points
unsigned int *midx;			// indexes for shuffling the population
unsigned int *wins;			// number of wins of each individual in the tournament
double (*f) (void);			// pointer to function evaluations
void (*callback) (double);	// pointer to callback function

extern "C" __declspec( dllexport ) void OptDLLName( char *name )
{
 strcpy( name, "Genetic algorithm" );
}

extern "C" __declspec( dllexport ) int OptDLLInit()
{
 SYSTEMTIME curtime;
 debug = 1;
 nparam = 0;
 nconstr = 0;
 parameter = NULL;
 constraint = NULL;
 crp = NULL;
 midx = NULL;
 indv = NULL;
 candx = NULL;
 wins = NULL;
 indv = NULL;
 callback = NULL;
 // initialise the random number generator with the time (milliseconds)
 GetSystemTime( &curtime);
 r250_init( (int) curtime.wMilliseconds );
 return 0;
}

extern "C" __declspec( dllexport ) char * OptDLLParameterName( int p, char *name )
{
 switch( p )
 {
  case 0:  strcpy( name, "Generations" ); break;
  case 1:  strcpy( name, "Population" ); break;
  default: strcpy( name, "not used" );
 }
 return name;
}

extern "C" __declspec( dllexport ) int OptDLLParameterNumber( void )
{
 return 2;
}

extern "C" __declspec( dllexport ) void OptDLLSetMethodParameter( int n, double p )
{
 if( n>2 ) return;
 switch( n )
 {
  case 0: if( p>0.0 ) gener = (unsigned int) p; else gener = 0; break;
  case 1: if( p>2.0 ) popsize = (unsigned int) p; else popsize = 2; break;
  case 2: if( p>0.0 ) mutprob = p; else mutprob = 0.0; break;
 }
}

extern "C" __declspec( dllexport ) int OptDLLVersion( void )
{
 return 100301;
}

extern "C" __declspec( dllexport ) int OptDLLIsConstrained( void )
{
 return 1;
}

extern "C" __declspec( dllexport ) int OptDLLIsBounded( void )
{
 return 1;
}

extern "C" __declspec( dllexport ) int OptDLLSolveLsq( double (*feval) (double *) )
{
 return -1;
}

extern "C" __declspec( dllexport ) void OptDLLSetCallback( void (*cb) (double) )
{
 callback = cb;
}

extern "C" __declspec( dllexport ) void OptDLLClearMemory( void )
{
 unsigned int i;
 if( indv != NULL )
 {
  for(i=0;i<2*popsize;i++) 
   if( indv[i] != NULL ) 
   {
	delete [] indv[i];
	indv[i] = NULL;
   }
  delete [] indv;
  indv = NULL;
 }
 if( midx != NULL )
 {
  delete [] midx;
  midx = NULL;
 }
 if( crp != NULL )
 {
  delete [] crp;
  crp = NULL;
 }
 if( wins != NULL )
 {
  delete [] wins;
  wins = NULL;
 }
 if( candx != NULL )
 {
  delete [] candx;
  candx = NULL;
 }
 if( parameter != NULL )
 {
  delete [] parameter;
  parameter = NULL;
 }
 if( constraint != NULL )
 {
  delete [] constraint;
  constraint = NULL;
 }
}

extern "C" __declspec( dllexport ) int OptDLLRoutines( void )
{
 // 1 - only DLLOptimise
 // 2 - only DLLSolveLsq
 // 3 - both
 return 1;
}

extern "C" __declspec( dllexport ) int OptDLLCreateArrays( int p, int c, int r )
{
 unsigned int i,j;
 parameter = new COptParam *[p];
 if( parameter == NULL ) return 1;
 constraint = new COptParam *[c];
 if( constraint == NULL )
 {
  OptDLLClearMemory();
  return 2;
 }
 // create the array for fitnesses
 candx = new double[2*popsize];
 if( candx == NULL )
 {
  OptDLLClearMemory();
  return 3;
 }
 // create array for tournament
 wins = new unsigned int[2*popsize];
 if( wins == NULL )
 {
  OptDLLClearMemory();
  return 4;
 }
 // create array for crossover points
 crp = new unsigned int[p];
 if( crp == NULL )
 {
  OptDLLClearMemory();
  return 5;
 }
 // create array for shuffling the population
 midx = new unsigned int[popsize];
 if( midx == NULL )
 {
  OptDLLClearMemory();
  return 6;
 }
 // create the population array
 indv = new double*[2*popsize];
 if( indv == NULL )
 {
  OptDLLClearMemory();
  return 7;
 }
 // create the individuals
 for( i=0; i<2*popsize; i++ )
 {
  indv[i] = new double[p];
  if( indv[i] == NULL )
  {
   for(j=0;j<i;j++) delete [] indv[j];
   delete [] indv;
   indv = NULL;
   OptDLLClearMemory();
   return 8;
  }
 }
 nparam = p;
 nconstr = c;
 // successful memory allocation
 return 0;
}

extern "C" __declspec( dllexport ) void OptDLLSetOptParam( int i, COptParam *pr )
{
 if( (parameter==NULL) || (i>nparam) ) return;
 parameter[i] = pr;
}

extern "C" __declspec( dllexport ) void OptDLLSetConstr( int i, COptParam *pr )
{
 if( (parameter==NULL) || (i>nconstr) ) return;
 constraint[i] = pr;
}

extern "C" __declspec( dllexport ) double OptDLLGetOptParameter( int i )
{
 return indv[best][i];
}

extern "C" __declspec( dllexport ) double OptDLLGetObjF( void )
{
 return candx[best];
}

// evaluate the fitness of one individual
double evaluate( unsigned int i )
{
 int j;
 BOOL outside_range = FALSE;
 double fitness;
 // set the paramter values
 for( j=0; j<nparam; j++ )
 {
  *(parameter[j]->Parameter.Value) = indv[i][j];
 }
 // evaluate the fitness
 try
 {
  fitness = (*f)();
 }
 catch( unsigned int e )
 {
  fitness = DBL_MAX;
 }
 // verify all constraints
 for( j=0; j<nconstr; j++ )
 {
  if( constraint[j]->MaxIneq )
  { 
   switch( constraint[j]->MaxType )
   {
    case 1: if( *(constraint[j]->Parameter.Value) >= constraint[j]->MaxD ) outside_range = TRUE; break;
    case 2: if( *(constraint[j]->Parameter.Value) >= *(constraint[j]->MaxP.Value) ) outside_range = TRUE; break;
    case 4: if( *(constraint[j]->Parameter.Value) >= constraint[j]->MinD * ( 1.0  + constraint[j]->MaxD) ) outside_range = TRUE; break;
   }
  }
  else
  { 
   switch( constraint[j]->MaxType )
   {
    case 1: if( *(constraint[j]->Parameter.Value) > constraint[j]->MaxD ) outside_range = TRUE; break;
    case 2: if( *(constraint[j]->Parameter.Value) > *(constraint[j]->MaxP.Value) ) outside_range = TRUE; break;
    case 4: if( *(constraint[j]->Parameter.Value) > constraint[j]->MinD * ( 1.0  + constraint[j]->MaxD) ) outside_range = TRUE; break;
   }
  }
  if( constraint[j]->MinIneq )
  { 
   switch( constraint[j]->MinType )
   {
    case 1: if( *(constraint[j]->Parameter.Value) < constraint[j]->MinD ) outside_range = TRUE; break;
    case 2: if( *(constraint[j]->Parameter.Value) < *(constraint[j]->MinP.Value) ) outside_range = TRUE; break;
    case 4: if( *(constraint[j]->Parameter.Value) < constraint[j]->MinD * ( 1.0  - constraint[j]->MaxD) ) outside_range = TRUE; break;
   }
  }
  else
  { 
   switch( constraint[j]->MinType )
   {
    case 1: if( *(constraint[j]->Parameter.Value) <= constraint[j]->MinD ) outside_range = TRUE; break;
    case 2: if( *(constraint[j]->Parameter.Value) <= *(constraint[j]->MinP.Value) ) outside_range = TRUE; break;
    case 4: if( *(constraint[j]->Parameter.Value) <= constraint[j]->MinD * ( 1.0  - constraint[j]->MaxD) ) outside_range = TRUE; break;
   }
  }
 }
 // if outside range make the fitness very large
 if( outside_range ) fitness = DBL_MAX;
 // return the value
 return fitness;
}

// copy individual o to position d
void copy( unsigned int o, unsigned int d )
{
 int i;
 for( i=0; i<nparam; i++ )
  indv[d][i] = indv[o][i];
 candx[d] = candx[o];
}

// swap individuals o and d
void swap( unsigned int o, unsigned int d )
{
 int i;
 double tmp;
 for( i=0; i<nparam; i++ )
 {
  tmp = indv[d][i];
  indv[d][i] = indv[o][i];
  indv[o][i] = tmp;
 }
 tmp = candx[d];
 candx[d] = candx[o];
 candx[o] = tmp;
 i = wins[d];
 wins[d] = wins[o];
 wins[o] = i;
}

//mutate one individual
void mutate( unsigned int i )
{
 int j;
 double mn, mx, mut;
 // mutate the parameters
 for( j=0; j<nparam; j++ )
 {
  // calculate lower and upper bounds
  switch( parameter[j]->MaxType )
  {
   case 1: mx = parameter[j]->MaxD; break;
   case 2: mx = *(parameter[j]->MaxP.Value); break;
   case 3: mx = DBL_MAX; break;
   case 4: mx = parameter[j]->MinD * ( 1.0  + parameter[j]->MaxD); break;
   default: mx = DBL_MAX;
  }
  switch( parameter[j]->MinType )
  {
   case 1: mn = parameter[j]->MinD; break;
   case 2: mn = *(parameter[j]->MinP.Value); break;
   case 3: mn = -DBL_MAX; break;
   case 4: mn = parameter[j]->MinD * ( 1.0  - parameter[j]->MaxD); break;
   default: mn = -DBL_MAX;
  }
  try
  {
   // calculate the mutatated parameter
   mut = indv[i][j] * ( 1 + mutvar * rnormal01()); 
   // force it to be within the bounds
   if( parameter[j]->MinIneq )
   { if( mut <= mn ) mut = mn + DBL_EPSILON;}
   else
   {if( mut < mn ) mut = mn;}
   if( parameter[j]->MaxIneq )
   {if( mut >= mx ) mut = mx - DBL_EPSILON;}
   else
   {if( mut > mx ) mut = mx;}
   // store it
   indv[i][j] = mut;
  }
  catch( unsigned int e )
  {
  }
 }
 // evaluate the fitness
 candx[i] = evaluate(i);
}

void crossover( unsigned int p1, unsigned int p2, unsigned int c1, unsigned int c2 )
{
 int i, j, s, e;
 unsigned int pp1, pp2, tmp, l;
 try
 {
  if( nparam > 1 )
  {
   // get a random number of crossover points, always less than half the number of genes
   ncross = r250n( (unsigned int) nparam / 2 );
  }
  else ncross = 0;
  // if less than 0 just copy parent to child
  if( ncross == 0 )
  {
   for( j=0; j<nparam; j++ )
   {
    indv[c1][j] = indv[p1][j];
    indv[c2][j] = indv[p2][j];
   }
   return;
  }
  // chose first point
  crp[0] = 1 + r250n(nparam-ncross);
  // chose the others
  for( i=1; i<ncross; i++ )
  {
   l = nparam - ncross + i - 1 - crp[i-1];
   crp[i] = 1 + crp[i-1] + ( l==0 ? 0 : r250n( l ) );
  }
  // copy segments
  pp1 = p2; pp2 = p1;
  for( i=0; i<=ncross; i++ )
  {
   // swap the indexes
   tmp = pp1;
   pp1 = pp2;
   pp2 = tmp;
   if( i==0 ) s = 0; else s = crp[i-1];
   if( i==ncross) e = nparam; else e = crp[i];
   for( j=s; j<e; j++ )
   {
    indv[c1][j] = indv[pp1][j];
    indv[c2][j] = indv[pp2][j];
   }
  }
 }
 catch( unsigned int e )
 {
 }
}

void shuffle( void )
{
 unsigned int i, a, b, tmp;
 for( i=0; i<popsize; i++ ) midx[i] = i;
 for( i=0; i<popsize/2; i++ )
 {
  a = r250n(popsize);
  b = r250n(popsize);
  tmp = midx[a];
  midx[a] = midx[b];
  midx[b] = tmp;
 }
}

// replicate the individuals w/ crossover
void replicate( void )
{
 unsigned int i;
 
 // generate a random order for the parents
 shuffle();
 // reproduce in consecutive pairs
 for( i=0; i<popsize/2; i++ )
  crossover( midx[i*2], midx[i*2+1], popsize + i*2, popsize + i*2+1 );
 // check if there is one left over and just copy it
 if( popsize % 2 > 0 ) copy( popsize-1, 2*popsize-1 );
 // mutate the offspring
 for( i=0; i<popsize; i++ )
  mutate( popsize+i );
}

// select popsize individuals
void select( int method )
{
 unsigned int i, j, nopp, opp;
 switch( method )
 {
  case 1:  // parent-offspring competition
	       for( i=popsize; i<2*popsize; i++ )
           {
            // if offspring is fitter keep it
            if( candx[i] < candx[j] ) copy( i, j );
           }
		   break;
  case 2:  // tournament competition
	       // compete with 20% of the population
           nopp = popsize / 5;
		   // but at least one
           if( nopp<1 ) nopp = 1;
		   // parents and offspring are all in competition
           for( i=0; i<2*popsize; i++ )
           {
            wins[i] = 0;
            for( j=0; j<nopp; j++ )
            {
			 // get random opponent
             opp = r250n(popsize*2);
             if( candx[i] <= candx[opp] ) wins[i]++;
            }
           }
           // selection of top popsize winners
           for( i=0; i< popsize; i++ )
            for( j=i+1; j<2*popsize; j++ )
             if( wins[i] < wins[j] ) swap( i, j );
		   break;
 }
}

// check the best individual at this generation
unsigned int fittest( void )
{
 unsigned int i,b;
 double f;
 f = candx[0];
 b = 0;
 for( i=1; i<popsize; i++ )
  if( candx[i] < f )
  {
   b = i;
   f = candx[i];
  }
 return b;
}

// initialise the population
void creation( unsigned int l, unsigned int u )
{
 unsigned int i;
 int j;
 double mn, mx, la;
 BOOL linear;
 for( i=l; i<u; i++ )
 {
  for( j=0; j<nparam; j++ )
  {
   // calculate lower and upper bounds
   switch( parameter[j]->MaxType )
   {
    case 1: mx = parameter[j]->MaxD; break;
	case 2: mx = *(parameter[j]->MaxP.Value); break;
	case 3: mx = DBL_MAX; break;
    case 4: mx = parameter[j]->MinD * ( 1.0  + parameter[j]->MaxD); break;
	default: mx = DBL_MAX;
   }
   switch( parameter[j]->MinType )
   {
    case 1: mn = parameter[j]->MinD; break;
	case 2: mn = *(parameter[j]->MinP.Value); break;
	case 3: mn = -DBL_MAX; break;
    case 4: mn = parameter[j]->MinD * ( 1.0  - parameter[j]->MaxD); break;
	default: mn = -DBL_MAX;
   }
   try
   {
    // determine if linear or log scale
    linear = FALSE; la = 1.0;
    if( mn==0.0 ) mn = DBL_EPSILON;
    if( (mx<=0.0) || (mn<=0.0) ) linear = TRUE;
    else
    {
 	 la = log10(mx) - log10(mn); 
	 if( la < 1.8 ) linear = TRUE;
    }
    // set it to a random value within the interval
    if( linear )
     indv[i][j] = mn + dr250() * (mx - mn);
    else
     indv[i][j] = mn *pow( 10, la*dr250() );
   }
   catch( unsigned int e )
   {
    indv[i][j] = (mx - mn)*0.5 + mn;
   }
  }
  try
  {
   // calculate its fitness 
   candx[i] = evaluate(i);
  }
  catch( unsigned int e )
  {
   candx[i] = DBL_MAX;
  }
 }
 // get the index of the fittest
 best = fittest();
}

// routines used for debugging
void dump_data_init( void )
{
 FILE *f;
 // check if debugopt.dat exists
 f = fopen( "debugopt.dat", "r" );
 if( f==NULL )
 {
  // no ouptut!
  debug = 0;
  return;
 }
 // we'll do some output
 debug = 1;
 fclose( f );
 // clear all the files
 f = fopen( "debugopt.dat", "w" );
 fclose( f );
}

void dump_data( unsigned int i )
{
 FILE *f;
 int j;
 // write the best individual
 f = fopen( "debugopt.dat", "a" );
 if( f == NULL ) return;
 fprintf( f, "%u %lg ", i, candx[best] );
 for( j=0; j<nparam; j++ ) fprintf( f, "%lg ", indv[best][j] );
 fprintf( f, "\n");
 fclose( f );
}

extern "C" __declspec( dllexport ) int OptDLLOptimise( double (*feval) (void) )
{
 unsigned int i, last_update, u10, u30, u50, fr;
 double bx;

 dump_data_init();
 if( debug )
 {
//  int fr = gener / 100;
//  if( fr==0 ) fr=1;
  fr=1;
 }
 // store the pointer to the function calls
 f = feval;
 // initialise the variance for mutations
 mutvar = 0.1;
 // initialise the update registers
 last_update = 0;
 u10 = u30 = u50 = 0;
 // initialise the population
 // first individual is the initial guess
 for( i=0; i<nparam; i++ )
  indv[0][i] = *(parameter[i]->Parameter.Value);
 try
 {
  // calculate the fitness
  candx[0] = evaluate(0);
 }
 catch( unsigned int e )
 {
  candx[0] = DBL_MAX;
 }
 // the others are random
 creation( 1, popsize );
 // initialise the update register
 last_update = 0;
 // get the index of the fittest
 best = fittest();
 // and store that value
 bx = candx[best];
 // ITERATE FOR gener GENERATIONS
 for( i=0; i<gener; i++ )
 {
  if( debug )  if( i%fr == 0 ) dump_data( i );
  // replicate the individuals
  replicate();
  // select the most fit
  select( 2 );
  // get the index of the fittest
  best = fittest();
  if( candx[best] != bx )
  {
   last_update = i;
   bx = candx[best];
  }
  if( u10 ) u10--;
  if( u30 ) u30--;
  if( u50 ) u50--;
  // perturb the population if we have stalled for a while
  if( (u50==0) && (i-last_update > 50) )
  {
   creation( popsize/2, popsize );
   u50 = 50; u30=30; u10=10;
  }
  else
  {
   if( (u30==0) && (i-last_update > 30) )
   {
	creation( unsigned(popsize*0.7), popsize );
	u30=30; u10=10;
   }
   else
    if( (u10==0) && (i-last_update > 10) ) 
   {
	creation( unsigned(popsize*0.9), popsize );
	u10=10;
   }
  }
  // signal another generation
  if( callback != NULL ) callback( candx[best] );
 }
 return 0;
}


#endif  // XXXX













