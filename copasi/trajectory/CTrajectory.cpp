/**
 *  File name: CTrajactory.cpp
 *
 *  Research Programmer: Yongqun He 
 *  Contact email: yohe@vt.edu
 *  Purpose: This is the .cpp file for the class CTrajectory. 
 *           It is to solve the trajectory time course problem of copasi
 */


#include "copasi.h"
#include "utilities/CGlobals.h"
#include "CTrajectory.h"


//default constructor
CTrajectory::CTrajectory()
{
  mPoints = 0;
  mEndTime = 0.0;	
  mN = 0;
  mMethod = 0;

  mY = NULL;
  mModel = NULL;
  mODESolver = NULL;
  mStochSolver = 0;

  mOutInit = NULL;
  mOutPoint = NULL;
  mOutEnd = NULL;

}
	

//Constructor
CTrajectory::CTrajectory(CModel * aModel, C_INT32 aPoints,
                         C_FLOAT64 aEndTime, C_INT32 aMethod)
{
  mPoints = aPoints;
  mEndTime = aEndTime;
  mMethod = aMethod;

  mN = 0;

  mY = NULL;
  mModel = NULL;
  mODESolver = NULL;
  mStochSolver = 0;
    
  initialize(aModel);
}

#ifdef XXXX
CTrajectory::CTrajectory(CModel *model, C_INT32 maxPoints, C_FLOAT64 maxTime, C_INT32 method)
    : mMaxPoints(maxPoints),
      mEndTime(maxTime),
      mMethod(method),
      mODESolver(0),
      mStochSolver(0)
{}
#endif // XXXX

// Object assignment overloading,
CTrajectory & CTrajectory::operator = (const CTrajectory& source)
{
  cleanup();
    
  if(this != &source)
    {
      mMethod = source.mMethod;
      mPoints = source.mPoints;
      mEndTime = source.mEndTime; 	
    }

  mOutInit = NULL;
  mOutPoint = NULL;
  mOutEnd = NULL;

  initialize(source.mModel);
    
  return *this;
}


//destructor
CTrajectory::~CTrajectory()
{
  cout << "~CTrajectory " << endl;
}

void CTrajectory::initialize(CModel * aModel)
{
  cleanup();
    
  // we really need a copy of the model here
  mModel = aModel;
  mN = mModel->getIndMetab();
    
  mY = mModel->getInitialNumbers();
    
  switch (mMethod)
    {
    case 1:
      mODESolver = new CODESolver();
      mODESolver->initialize(* mModel, mY, mN, mMethod);
      break;
    case 2:
        // we're doing a stochastic simulation
        mStochSolver = new CStochSolver(mMethod);
        mStochSolver->initialize(mModel);
    default:
      fatalError();
    }

  mOutInit = new COutputEvent(*this, 0);
  mOutPoint = new COutputEvent(*this, mPoints);
  mOutEnd = new COutputEvent(*this, mEndTime);
  
  return;
}

void CTrajectory::cleanup()
{
  if (mY) delete [] mY;
  mY = NULL;
    
  //if (mModel) delete mModel;
  mModel = NULL;

  if (mODESolver) 
    {
      mODESolver->cleanup();
      delete mODESolver;
    }
  mODESolver = NULL;
  if (mStochSolver)
  {
      mStochSolver->cleanup();
      delete mStochSolver;
  }
  mStochSolver = 0;
  return;
}

C_INT32 CTrajectory::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if((Fail = configbuffer.getVariable("EndTime", "C_FLOAT64",
				      (void *) &mEndTime,
				      CReadConfig::LOOP)))
    return Fail;
  
  if((Fail = configbuffer.getVariable("Points", "C_INT32",
				      (void *) &mPoints)))
    return Fail;

  if ((Fail = configbuffer.getVariable("OutputTimeZero", "C_INT16",
				      (void *) &mOutputTimeZero)))
    return Fail;
  
  return Fail;
}

C_INT32 CTrajectory::save(CWriteConfig & configbuffer)
{
  C_INT32 Fail = 0;

  if((Fail = configbuffer.setVariable("EndTime", "C_FLOAT64",
				      (void *) &mEndTime)))
    return Fail;
  
  if((Fail = configbuffer.setVariable("Points", "C_FLOAT64",
				      (void *) &mPoints)))
    return Fail;

  if((Fail = configbuffer.setVariable("OutputTimeZero", "C_INT16",
				      (void *) &mOutputTimeZero)))
    return Fail;

  return Fail;
}

void CTrajectory::setModel(CModel * aModel)
{
  mModel = aModel;
}


CModel * CTrajectory::getModel() const
{
  return mModel;
}


void CTrajectory::setODESolver(CODESolver * aSolver)
{
  mODESolver = aSolver;
}


CODESolver * CTrajectory::getODESolver() const
{
  return mODESolver;
}

void CTrajectory::setPoints(const C_INT32 anInt)
{
  mPoints = anInt;	
}

C_INT32 CTrajectory::getPoints() const
{
  return mPoints;
}


void CTrajectory::setArrSize(const C_INT32 anInt)
{
  mN = anInt;
}


C_INT32 CTrajectory::getArrSize() const
{
  return mN;
}


//calculate the time length
C_FLOAT64 CTrajectory::calcTimeLength()
{
  return mEndTime/mPoints;
}

	
void CTrajectory::setEndTime(const C_FLOAT64 aDouble)
{
  mEndTime = aDouble;
}

const C_FLOAT64 & CTrajectory::getEndTime() const
{
  return mEndTime;
}

const C_FLOAT64 & CTrajectory::getTime() const
{
  return mTime;
}

	
void CTrajectory::setMethod(const C_INT32 anInt)
{
  mMethod = anInt;
}

C_INT32 CTrajectory::getMethod() const
{
  return mMethod;
}

C_FLOAT64 * CTrajectory::getMY() const
{
  return mY;
}

void CTrajectory::process(ofstream &fout)
{
  // mODESolver->initialize(* mModel, mY, mN, mMethod);
    
  // COutputEvent *OutInit = NULL, *OutPoint = NULL, *OutEnd = NULL;

  // mOutInit = COutputEvent(TIME_INIT, this);
  // mOutPoint = COutputEvent(TIME_POINT, this);		
  // mOutEnd = COutputEvent(TIME_END, this);

	//print for the initial time point	
	if (mOutInit) mOutInit->print(*this, Copasi->OutputList, fout);

    // The trajectory can be calculated using the ODE solver, 
    // one of the stochastic solver, or a hybrid method (as yet unimplemented)
    if (mMethod == CONTINUOUS_ODE)
    {
        //calculates number of iterations and time intervals
        C_FLOAT64 length = mEndTime/mPoints;
        mTime = 0.0;

        // print for the initial time point	
        // if (mOutInit) mOutInit->Print();
        // if (mOutPoint) mOutPoint->Print();
        
        for(C_INT32 i = 0; i < mPoints; i++)
        {
            //update the CODESolver from current time to end time
            cout << mTime << "  ";
      
			//print for current time point in the outputEvent
			if (!mOutputTimeZero)
			{
				if (mTime != 0)
					if (mOutPoint) mOutPoint->print(*this, Copasi->OutputList, fout);      
			}
			else if (mOutPoint) mOutPoint->print(*this, Copasi->OutputList, fout);      

            mODESolver->step(mTime, mTime+length);

            //update CModel
            mModel->setConcentrations(mY);

            //print for current time point in the outputEvent
            // if (OutPoint) OutPoint.Print();

            mTime += length;
        }
    }
#ifdef XXXX
    else if (mMethod == STOCH_DIRECT || mMethod == STOCH_NEXTREACTION)
    {
        C_FLOAT64 time = 0;
        C_INT32 step = 0;
         while (step < mMaxSteps && time < mEndTime && time >= 0)
         {
             time = mStochSolver->GetMethod()->DoStep(time);
             step++;
         }
    }
#endif // XXXX

  // if (OutEnd) OutEnd.Print();

  // delete OutInit; -> to cleanup
  // delete OutPoint;
  // delete OutEnd;
    
  // mODESolver->cleanup();
}


