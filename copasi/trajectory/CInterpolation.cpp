//#include "copasi.h"
//#include "copasi/utilities/CVersion.h"
//#include "copasi/utilities/CMatrix.h"
//#include "copasi/utilities/CCopasiVector.h"

#include "CInterpolation.h"
#include <vector>
#include <set>
#include <new>


/*******************************/
/* Code for class CStateRecord */
/*******************************/

CStateRecord::CStateRecord():
  mpValues(NULL),
  mSize(0)
{}


CStateRecord::CStateRecord(size_t speciesNum):
  mpValues(new C_FLOAT64[speciesNum+2]),
  mSize(speciesNum+2)
{}


CStateRecord::CStateRecord(const CStateRecord & src):
  mpValues(new C_FLOAT64[src.mSize]),
  mSize(src.mSize)
{
  memcpy(mpValues, src.mpValues, sizeof(C_FLOAT64)*mSize);
}


CStateRecord::~CStateRecord() 
{
  pdeletev(mpValues);
}
 

CStateRecord & CStateRecord::operator=(const CStateRecord & rhs)
{
  if (this != &rhs)
  {
    if (mSize != rhs.mSize)
      {
	pdeletev(mpValues);
	mpValues = new C_FLOAT64[rhs.mSize];
	mSize    = rhs.mSize;
      }

    memcpy(mpValues, rhs.mpValues, sizeof(C_FLOAT64)*mSize);
  }

  return *this;
}

C_FLOAT64 * CStateRecord::getArray() const 
{
  return mpValues;
}

const C_FLOAT64 & CStateRecord::getTime() const 
{
  return mpValues[0];
}

const C_FLOAT64 & CStateRecord::getSlowPropensitySum() const 
{
  return mpValues[mSize-1];
}

const size_t & CStateRecord::getArrayLen() const
{
  return mSize;
}

//Friend Function
void printRecord(const CStateRecord& record)
{
  for (int i=0; i<record.mSize; i++)
    {
      cout << record.mpValues[i] << " ";
    }
  cout << endl;
return;
}


/************************************/
/* Code for Class of CInterpolation */
/************************************/
CInterpolation::CInterpolation():
  mpX(NULL),
  mpY(NULL),
  mStateNum(0),
  mBeginRecordIndex(0),
  mHaveRecordNum(0),
  mpState(NULL),
  mpInterpolationState(NULL),
  mShiftBeginIndex(false)
{}

CInterpolation::CInterpolation(size_t stateNum, size_t speciesNum):
  mpX(new C_FLOAT64[stateNum]),
  mpY(new C_FLOAT64[stateNum]),
  mStateNum(stateNum),
  mBeginRecordIndex(0),
  mHaveRecordNum(0),
  mShiftBeginIndex(false)
{
  mpInterpolationState = new CStateRecord(speciesNum);

  mpState = static_cast< CStateRecord* > 
    (operator new[] (sizeof(CStateRecord) * stateNum));

  for (size_t i=0; i<stateNum; i++)
    new (&mpState[i]) CStateRecord(speciesNum);
  
  return;
}


CInterpolation::~CInterpolation()
{
  pdeletev(mpX);
  pdeletev(mpY);

  pdelete(mpInterpolationState);

  for(int i=mStateNum-1; i>=0; i--)
    {
      mpState[i].~CStateRecord();
    }


  if (mpState != NULL)
    operator delete[] (mpState);

}

void CInterpolation::recordState(C_FLOAT64 time,
				 const C_FLOAT64 *y)
{
  mHaveRecordNum++;
  if (mHaveRecordNum>mStateNum)
    {
      mHaveRecordNum = mStateNum;
      if (!mShiftBeginIndex)
	mShiftBeginIndex = true;
    }

  if (mShiftBeginIndex)
    (++mBeginRecordIndex) %= mStateNum;

  size_t newStateIndex = mBeginRecordIndex 
	  + mHaveRecordNum - 1;

  newStateIndex %= mStateNum;
  //cout << "newStateIndex: " << newStateIndex << endl;
    
  C_FLOAT64 *pArray = mpState[newStateIndex].getArray();
  const size_t size = mpState[newStateIndex].getArrayLen();
  
  pArray[0] = time;
  for (size_t i=1; i<size; i++, y++)
    {
      ++pArray;
      *pArray = *y;
    }

  return; 
}

void CInterpolation::recordReset()
{
  mBeginRecordIndex = 0;
  mHaveRecordNum    = 0;
  mShiftBeginIndex  = false;
}

C_FLOAT64 CInterpolation::interpolation(C_FLOAT64 x)
{
  //Before use this function, data have been stored in 
  //arraies mpX, mpY. Lengths of array is given by 
  //mHaveRecordNum
  
  if ((x>mpX[mHaveRecordNum-1])
      || (x<mpX[0])) //If x is within the range
    //Show Error !!!
    cout << "x " << x << " is out of range" << endl;

  if (mHaveRecordNum == 1)
    return mpY[0]; //only one point recorded

  int i, j;
  for (i=0; i<mHaveRecordNum; i++) //x is in *mpX
    {
      if(x==mpX[i])
	return mpY[i];
    }

  //Calculate interpolation value
  C_FLOAT64 numer, tmpNumer = 1;
  C_FLOAT64 denom;
  for (i=0; i<mHaveRecordNum; i++)
    tmpNumer *= x - mpX[i];

  C_FLOAT64 y = 0;
  for (i=0; i<mHaveRecordNum; i++)
    {
      numer = tmpNumer / (x-mpX[i]);
      denom = 1;
      for (j=0; j<mHaveRecordNum; j++)
	{
	  if (i!=j)
	    denom *= mpX[i] - mpX[j];
	}

      y += mpY[i] * numer / denom;
    }

  return y;
}


void CInterpolation::calculateFiringTime()
{
  size_t i = mBeginRecordIndex;

  //(1)Load time into mpY
  //(2)Load sum of slow reaction propensities
  //   into mpX

  for (size_t j=0; j<mHaveRecordNum; j++)
    {
      mpY[j] = mpState[i].getTime();
      mpX[j] = mpState[i].getSlowPropensitySum();
      
      if (++i > (mStateNum-1))
	i -= mStateNum;
    }

  //(3)do interpolation at propensity=0
  C_FLOAT64 *pArray = mpInterpolationState->getArray();
  pArray[0] = interpolation(0.0);
} 

void CInterpolation::calculateState()
{
  C_FLOAT64 *pInterArray = mpInterpolationState->getArray();
  C_FLOAT64 **ppArray = new C_FLOAT64*[mHaveRecordNum];
  C_FLOAT64 time = mpInterpolationState->getTime();

  //(1)Load time into array mpX
  //(2)Load pointers of objects CStateRecord into ppArray
  size_t i = mBeginRecordIndex;
  for (size_t j=0; j<mHaveRecordNum; j++)
    {
      ppArray[j] = mpState[i].getArray();
      mpX[j] = mpState[i].getTime();

      if(++i > mStateNum-1)
	i -= mStateNum;
    }

  //(3)Load propensities into mpY
  //(4)Do interpolation 
  size_t speciesNum = (mpInterpolationState->getArrayLen()) - 2;
  for (size_t species=1; species<=speciesNum; species++)
    {
      for (size_t j=0; j<mHaveRecordNum; j++)
	mpY[j] = ppArray[j][species];
	
      pInterArray[species] = interpolation(time);
    }

}

CStateRecord * CInterpolation::getInterpolationState()
{
  calculateFiringTime();
  calculateState();
  return mpInterpolationState;
}


//Friend Function
void printInterpolation(const CInterpolation& interp)
{
  cout << "State Num: " << interp.mStateNum << endl;
  cout << "Record Num: " << interp.mHaveRecordNum << endl;
  cout << "Begin Record Index: " << interp.mBeginRecordIndex << endl;
  cout << "Shift or not: ";
  if (interp.mShiftBeginIndex)
    cout << "Yes" << endl;
  else
    cout << "No" << endl;

  int site;
  for (int i=0; i<interp.mHaveRecordNum; i++)
    {
      cout << "Record #:" << i << endl;
      site = (interp.mBeginRecordIndex+i) % interp.mStateNum;
      printRecord(interp.mpState[site]);
    }

  cout << "Finish, aha" << endl;
  return;
}
