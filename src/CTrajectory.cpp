/**
 * CTrajectory.cpp
 * copyright            : (C) 2001 by
 */

#include "CTrajectory.h"


//default constructor
CTrajectory::CTrajectory()
{
	mPoints = 0;
	mEndTime = 0.0;	
	mN = 0;
	mMethod = 0;
	mY = new C_FLOAT64[mN];
	mCModel = NULL;
	mCODESolver = NULL;
}
	

//Constructor
CTrajectory::CTrajectory(CModel * aModel, C_INT32 aPoints, C_INT32 aN,
															 C_FLOAT64 aEndTime, C_INT32 aMethod)
{
	mN = aN;
	mY = new C_FLOAT64[mN];
	mModel = aModel;
	mPoints = aPoints;
	mEndTime = aEndTime;
	mMethod = aMethod;
}


// Copy constructor
CTrajectory::	CTrajectory(CTrajectory& source)
{
	mY = source.mY;
	mCModel = source.mCModell;
	mCODESolver = source.mCODESolver;
	mPoints = source.mPoints;
	mEndTime = source.mEndTime; 	
	mN = source.mN;
}

// Object assignment overloading,
CTrajectory::CTrajectory& operator=(CTrajectory& source)
{
	if(this != &source)
	{
		mY = source.mY;
		mCModel = source.mCModell;
		mCODESolver = source.mCODESolver;
		mPoints = source.mPoints;
		mEndTime = source.mEndTime; 	
		mN = source.mN;
	}

	return *this;
}


//destructor
CTrajectory::~CTrajectory()
{
	cout << "~CTrajectory " << endl;
}


void CTrajectory::SetModel(CModel * aModel)
{
 	mCModel = aModel;
}


CModel * CTrajectory::GetModel()
{
 	return mCModel;
}


void CTrajectory::SetODESolver(CODESolver * aSolver)
{
 	mCODESolver = aSolver;
}


CODESolver * CTrajectory::GetSolver()
{
 	return mCODESolver;
}


void CTrajectory::SetPoints(C_INT32 anInt)
{
	mPoints = anInt;	
}

C_INT32 CTrajectory::GetPoints()
{
	return mPoints;
}


void CTrajectory::SetArrSize(C_INT32 anInt)
{
 	mN = anInt;
}


C_INT32 CTrajectory::GetArrSize()
{
 	return mN;
}

	
void CTrajectory::SetEndTime(C_FLOAT64e aDouble)
{
	mEndTime = aDounble;
}

C_FLOAT64 CTrajectory::GetEndTime()
{
	return mEndTime;
}

	
void CTrajectory::SetMethod(C_INT32 anInt)
{
	mTypeOfSolver = anInt;
}

C_INT32 CTrajectory::GetMethod()
{
	return mTypeOfSolver;
}


void CTrajectory::SetMY(C_FLOAT64 * arrDouble)
{
	mY = arrDouble;
}

C_FLOAT64 * CTrajectory::GetMY()
{
	return mY;
}


void CTrajectory::Process()
{

	// COutputEvent *OutInit = NULL, *OutPoint = NULL, *OutEnd = NULL;

	// OutInit = COutputEvent(TIME_INIT, this);
	// OutPoint = COutputEvent(TIME_POINT, this);		
 	// OutEnd = COutputEvent(TIME_END, this);


	//calculates number of iterations and time intervals
	C_FLOAT64 length = mEndTIme/mPoints;

	// print for the initial time point	
	// if (OutInit) OutInit.Print();
  // if (OutPoint) OutPoint.Print();
	
	for(C_FLOAT64 t = 0.0, C_INT32 i = 0; i < mPoints; i++, t += length)
	{
		//update the CODESolver from current time to end time
		mCODESolver->Step(t, t+length);

		//update CModel
		mCModel->SetConcentrations(mY);

		//print for current time point in the outputEvent
		// if (OutPoint) OutPoint.Print();
	}
	
	// if (OutEnd) OutEnd.Print();

	// delete OutInit;
	// delete OutPoint;
	// delete OutEnd;
	
}


