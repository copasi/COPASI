
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

//default constructor
CGA::CGA()
{
 mPopSize=0;
 mGener=0;
 mParamNum=0;

 mCrp = NULL;
 mMidX = NULL;
 mIndV = NULL;
 mCandX = NULL;
 mWins = NULL;
 
 //initialize();

}

// initialize function
void CGA::initialize()
{
  int i;

  mCandX = new double[2*mPopSize];
  // create array for tournament
  mWins = new unsigned int[2*mPopSize];
  // create array for crossover points
  mCrp = new unsigned int[mParamNum];
  // create array for shuffling the population
  mMidX = new unsigned int[mPopSize];
  // create the population array
  mIndV = new double*[2*mPopSize];
  // create the individuals
  for( i=0; i<2*mPopSize; i++ )
    {
      mIndV[i] = new double[mParamNum];
    }

  initFirstGeneration();
}

// initialize the first generation
void CGA::initFirstGeneration()
{
  int i;
 
  for( i=0; i<mParamNum; i++ )
    mIndV[0][i] =1.1+dr250();

  try
    {
      // calculate the fitness
      mCandX[0] = evaluate(0);
    }
  catch( unsigned int e )
    {
      mCandX[0] = DBL_MAX;
    }

  // the others are randomly generated
  creation( 1, mPopSize);
  mBest=fittest();

}

//constructor
CGA::CGA(int psize,int num, int param)
{

 unsigned int i,j;

 mPopSize=psize;
 mGener=num;
 mParamNum=param;

 // initialize();

}




#ifdef XXXX

//constructor
CGA::CGA(int psize,int num, int param)
{

 unsigned int i,j;

 mPopSize=psize;
 mGener=num;
 mParamNum=param;

 mCandX = new double[2*psize];
 // create array for tournament
 mWins = new unsigned int[2*psize];
 // create array for crossover points
 mCrp = new unsigned int[param];
 // create array for shuffling the population
 mMidX = new unsigned int[psize];
 // create the population array
 mIndV = new double*[2*psize];
 // create the individuals
 for( i=0; i<2*psize; i++ )
 {
  mIndV[i] = new double[param];
 }

 for( i=0; i<mParamNum; i++ )
  mIndV[0][i] =1.1+dr250();

 try
 {
  // calculate the fitness
  mCandX[0] = evaluate(0);
 }
 catch( unsigned int e )
 {
  mCandX[0] = DBL_MAX;
 }

 // the others are randomly generated
 creation( 1, mPopSize);
 mBest=fittest();

}
#endif // XXXX


// Copy constructor
CGA::CGA(const CGA& source)
{
  mGener = source.mGener;	   
  mPopSize = source.mPopSize;    
  mCrossNum = source.mCrossNum;	    
  mMin = source.mMin;
  mMax = source.mMax;
  mMutVar = source.mMutVar;	    
  mMutProb = source.mMutProb;	    
  mBest = source.mBest;	    
  mParamNum = source.mParamNum;	    
  mIndV = source.mIndV;    
  mCandX = source.mCandX;     
  mCrp = source.mCrp;	    
  mMidX = source.mMidX;	   
  mWins = source.mWins;

}

// Object assignment overloading
CGA& CGA::operator=(const CGA& source)
{
  cleanup();
    
  if(this != &source)
    {
      mGener = source.mGener;	   
      mPopSize = source.mPopSize;    
      mCrossNum = source.mCrossNum;	    
      mMin = source.mMin;
      mMax = source.mMax;
      mMutVar = source.mMutVar;	    
      mMutProb = source.mMutProb;	    
      mBest = source.mBest;	    
      mParamNum = source.mParamNum;	    
      mIndV = source.mIndV;    
      mCandX = source.mCandX;     
      mCrp = source.mCrp;	    
      mMidX = source.mMidX;	   
      mWins = source.mWins;
    }
    
  return *this;
}


// clean up 
void CGA::cleanup()
{
}


//destructor
CGA::~CGA()
{
delete mIndV;
delete mMidX;
delete mCrp;
delete mWins;
delete mCandX;
}

//implementation of mutation functions

// set real problem
void CGA::setRealProblem(CRealProblem & aProb)
{
  mRealProblem = aProb;
}


//set parameter
void CGA::setParamNum (int num)
{
mParamNum=num;
}

//set population size
void CGA::setPopSize(int num)
{
  mPopSize=num;
}

//set generation
void CGA::setGeneration(int num)
{
  mGener=num;
}


//set the mutation variance
void CGA::setMutVar( double num)
{
  mMutVar=num;
}

//set the minimum
void CGA::setMin( double num)
{
  mMin=num;
}


//set maximum
void CGA::setMax( double num)
{
  mMax=num;
}

//set array of individuals w/ candidate values for the parameters
void CGA::setIndv(int i,int j,double num)
{
  mIndV[i][j]=num;
}

//set array of values of objective function for individuals
void CGA::setCandx(int i, double num)
{
  mCandX[i]=num;
}

//set the best result
void CGA::setBest(unsigned int num)
{
  mBest=num;
}

//implementation of access functions

//get parameter number
int CGA::getParamNum()
{
  return mParamNum;
}

//get the best candidate
double CGA::getBestCandidate()
{
  return mCandX[mBest];
}

// get generation
int CGA::getGeneration()
{
  return mGener;
}

// get population size
int CGA::getPopSize()
{
  return mPopSize;
}

// init  optimization random numbers
int CGA::initOptRandom()
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
  double tmp;

  for(j=0;j<mParamNum;j++)
  {
    tmp = mIndV[i][j];
    mRealProblem.setParameter(j, tmp);
  }
  
  //for debugging purpose
  //cout << "Debug: mRealProblem.getParameterNum() is:"<<mRealProblem.getParameterNum()<<endl;

  mRealProblem.calculate();

  return mRealProblem.getBestValue();

}


#ifdef XXXX

// evaluate the fitness of one individual
double CGA::evaluate( unsigned int i )
{
 int j;
 //bool outside_range = FALSE;
 double fitness;
 double fitness0;
 //double tmp;

 //YOHE: this is the mathematics function used only for testing purpose
 // evaluate the fitness
 try
 {
  fitness0=0;
  for(j=0;j<mParamNum;j++)
   {
     fitness=fitness0+pow(mIndV[i][j],4.0)-16.0*pow(mIndV[i][j],2.0)+5.0*mIndV[i][j];
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

#endif // XXXX

// copy individual o to position d
void CGA::copy( unsigned int o, unsigned int d )
{
 int i;
 for( i=0; i<mParamNum; i++ )
  mIndV[d][i] = mIndV[o][i];
 mCandX[d] = mCandX[o];
}

// swap individuals o and d
void CGA::swap( unsigned int o, unsigned int d )
{
 int i;
 double tmp;
 for( i=0; i<mParamNum; i++ )
 {
  tmp = mIndV[d][i];
  mIndV[d][i] = mIndV[o][i];
  mIndV[o][i] = tmp;
 }
 tmp = mCandX[d];
 mCandX[d] = mCandX[o];
 mCandX[o] = tmp;
 i = mWins[d];
 mWins[d] = mWins[o];
 mWins[o] = i;
}

//mutate one individual
void CGA::mutate( unsigned int i )
{
 int j;
 //double mMin, mMax, mut;
 double  mut;
 // mutate the parameters

 for (j = 0; j < mParamNum; j++) {
 //YOHE: test
 //  double indtmp = mIndV[i][j];
 //  double rnorm = rnormal01();
 //  mut = indtmp * (1 + mMutVar * rnorm);

  // calculate the mutatated parameter
   mut = mIndV[i][j] * ( 1 + mMutVar * rnormal01());

  // force it to be within the bounds
   if( mut <= mMin ) mut = mMin + DBL_EPSILON;
   else
   {if( mut < mMin ) mut = mMin;}

  if( mut >= mMax ) mut = mMax - DBL_EPSILON;
   else
   {if( mut > mMax ) mut = mMax;}
   // store it
   mIndV[i][j] = mut;
 }
 // evaluate the fitness
 mCandX[i] = evaluate(i);

}

// process crossover
void CGA::crossover( unsigned int p1, unsigned int p2, unsigned int c1, unsigned int c2 )
{
 int i, j, s, e;
 unsigned int pp1, pp2, tmp, l;
 try
 {
  if( mParamNum > 1 )
  {
   // get a random number of crossover points, always less than half the number of genes
   mCrossNum = r250n( (unsigned int) mParamNum / 2 );
  }
  else mCrossNum = 0;
  // if less than 0 just copy parent to child
  if( mCrossNum == 0 )
  {
   for( j=0; j<mParamNum; j++ )
   {
    mIndV[c1][j] = mIndV[p1][j];
    mIndV[c2][j] = mIndV[p2][j];
   }
   return;
  }
  // chose first point
  mCrp[0] = 1 + r250n(mParamNum-mCrossNum);
  // chose the others
  for( i=1; i<mCrossNum; i++ )
  {
   l = mParamNum - mCrossNum + i - 1 - mCrp[i-1];
   mCrp[i] = 1 + mCrp[i-1] + ( l==0 ? 0 : r250n( l ) );
  }
  // copy segments
  pp1 = p2; pp2 = p1;
  for( i=0; i<=mCrossNum; i++ )
  {
   // swap the indexes
   tmp = pp1;
   pp1 = pp2;
   pp2 = tmp;
   if( i==0 ) s = 0; else s = mCrp[i-1];
   if( i==mCrossNum) e = mParamNum; else e = mCrp[i];
   for( j=s; j<e; j++ )
   {
    mIndV[c1][j] = mIndV[pp1][j];
    mIndV[c2][j] = mIndV[pp2][j];
   }
  }
 }
 catch( unsigned int e )
 {
 }
}

// shuffle data
void CGA::shuffle( void )
{
 unsigned int i, a, b, tmp;
 for( i=0; i<mPopSize; i++ ) mMidX[i] = i;
 for( i=0; i<mPopSize/2; i++ )
 {
  a = r250n(mPopSize);
  b = r250n(mPopSize);
  tmp = mMidX[a];
  mMidX[a] = mMidX[b];
  mMidX[b] = tmp;
 }
}

// replicate the individuals w/ crossover
void CGA::replicate( void )
{
 unsigned int i;

 // generate a random order for the parents
 shuffle();
 // reproduce in consecutive pairs
 for( i=0; i<mPopSize/2; i++ )
  crossover( mMidX[i*2], mMidX[i*2+1], mPopSize + i*2, mPopSize + i*2+1 );
 // check if there is one left over and just copy it
 if( mPopSize % 2 > 0 ) copy( mPopSize-1, 2*mPopSize-1 );
 // mutate the offspring
 for( i=0; i<mPopSize; i++ )
  mutate( mPopSize+i );
}

// select mPopSize individuals
void CGA::select( int method )
{
 unsigned int i, j, nopp, opp;
 switch( method )
 {
  case 1:  // parent-offspring competition
	       for( i=mPopSize; i<2*mPopSize; i++ )
           {
            // if offspring is fitter keep it
            if( mCandX[i] < mCandX[j] ) copy( i, j );
           }
		   break;
  case 2:  // tournament competition
	       // compete with 20% of the population
           nopp = mPopSize / 5;
		   // but at least one
           if( nopp<1 ) nopp = 1;
		   // parents and offspring are all in competition
           for( i=0; i<2*mPopSize; i++ )
           {
            mWins[i] = 0;
            for( j=0; j<nopp; j++ )
            {
			 // get random opponent
             opp = r250n(mPopSize*2);
             if( mCandX[i] <= mCandX[opp] ) mWins[i]++;
            }
           }
           // selection of top mPopSize winners
           for( i=0; i< mPopSize; i++ )
            for( j=i+1; j<2*mPopSize; j++ )
             if( mWins[i] < mWins[j] ) swap( i, j );
		   break;
 }
}

// check the best individual at this generation
unsigned int CGA::fittest( void )
{
 unsigned int i,b;
 double f;
 f = mCandX[0];
 b = 0;
 for( i=1; i<mPopSize; i++ )
  if( mCandX[i] < f )
  {
   b = i;
   f = mCandX[i];
  }
 return b;
}

// initialise the population
void CGA::creation( unsigned int l, unsigned int u )
{
 unsigned int i;
 int j;

// double mMin, mMax, la;
 double la;

// BOOL linear;
  bool linear;
 for( i=l; i<u; i++ )
 {

 for( j=0; j<mParamNum; j++ )
  {
   try
   {
    // determine if linear or log scale
    linear = FALSE; la = 1.0;
    if( mMin==0.0 ) mMin = DBL_EPSILON;
    if( (mMax<=0.0) || (mMin<=0.0) ) linear = TRUE;
    else
    {
 	 la = log10(mMax) - log10(mMin);
	 if( la < 1.8 ) linear = TRUE;
    }
    // set it to a random value within the interval
    if( linear )
     mIndV[i][j] = mMin + dr250() * (mMax - mMin);
    else
     mIndV[i][j] = mMin *pow( 10, la*dr250() );
   }
   catch( unsigned int e )
   {
    mIndV[i][j] = (mMax - mMin)*0.5 + mMin;
   }
  }
  try
  {
   // calculate its fitness
   mCandX[i] = evaluate(i);
  }
  catch( unsigned int e )
  {
   mCandX[i] = DBL_MAX;
  }
 }
 // get the index of the fittest
 mBest = fittest();
}


// dump data 
void CGA::dumpData( unsigned int i )
{
  //YOHE: use cout instead
  //ofstream finalout("debugopt.dat",ios::app);

  //if(!finalout)
  // 	{
  // 	cout<<"debugopt.dat cannot be opened!"<<endl;
  //	exit(1);
  //	}
  //finalout<<"#"<<i<<"\t"<<mCandX[mBest]<<endl;
 cout<<"#"<<i<<"\t"<<mCandX[mBest]<<endl;
 for(int j=0;j<mParamNum;j++)
    {
      //finalout<<mIndV[mBest][j]<<"\t";
      cout<<mIndV[mBest][j]<<"\t";
    }
 //finalout<<endl;
 // finalout<<endl;
 //finalout.close();

}



// optimise function, the real function for optimization
int CGA::optimise()
{

 unsigned int i, last_update, u100, u300, u500, fr;
 double bx;

 struct tms before,after;
 double dTime=0;

 times(&before);
 dTime=time(NULL);

 mMin = *(mRealProblem.getParameterMin());
 mMax = *(mRealProblem.getParameterMax());

 cout << "mMin = "<<mMin<<", mMax= "<<mMax<<", mParamNum = "<<mParamNum<<endl;
 cout << "mRealProblem.getParameterNum() = " << mRealProblem.getParameterNum()<<endl;

 initOptRandom();

 // initialise the variance for mutations
 setMutVar(0.1);

 // initialise the update registers
 last_update = 0;
 u100 = u300 = u500 = 0;

 //Display layout of all MPI processes
 cout<<endl;
 cout<<"Initial populaiton has successfully created!!!!!"<<endl;

 // and store that value
 bx = getBestCandidate();

 cout<<"-----------------------------best result at each generation---------------------"<<endl;
 cout<<"Generation\t"<<"Best candidate value for object function\t"<<"Display "<<mParamNum<<" parameters"<<endl;
 cout<<endl;

 int psize = getPopSize();

// ITERATE FOR gener GENERATIONS

for( i=0; i<getGeneration(); i++ )
{
  cout<<endl;
  cout<<"GA is processing at generation "<<i<<endl;

  dumpData( i );
  // replicate the individuals
  replicate();
  // select the most fit
  select( 2 );
  // get the index of the fittest
  // mBest = fittest();
  setBest(fittest());
  if(getBestCandidate()!= bx )
  {
   last_update = i;
   bx =getBestCandidate();
  }
  if( u100 ) u100--;
  if( u300 ) u300--;
  if( u500 ) u500--;

  // perturb the population if we have stalled for a while
  if( (u500==0) && (i-last_update > 500) )
  {
   creation( psize/2, psize );
   u500 = 500; u300=300; u100=100;
  }

  else
  {
   if( (u300==0) && (i-last_update > 300) )
   {
         creation( unsigned(psize*0.7), psize );

	u300=300; u100=100;
   }

   else
    if( (u100==0) && (i-last_update > 100) )
   {
         creation( unsigned(psize*0.9), psize );
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

