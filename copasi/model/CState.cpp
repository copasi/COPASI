// CSate.cpp
//
// (C) Stefan Hoops 2002
//

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CState.h"
#include "CModel.h"
#include "CCompartment.h"

CState::CState(const CModel * model) :
    mModel(model),
    mVolumesSize(0),
    mNumbersSize(0),
    mNumbersUpdated(0),
    mVolumes(NULL),
    mNumbersInt(NULL),
    mNumbersDbl(NULL)
{
  if (mModel)
    {
      mVolumesSize = mModel->getCompartments().size();
      mNumbersSize = mModel->getTotMetab();
      mNumbersUpdated = mModel->getIntMetab();

      mVolumes = new C_FLOAT64[mVolumesSize];
      mNumbersInt = new C_INT32[mNumbersSize];
      mNumbersDbl = new C_FLOAT64[mNumbersSize];
    }
}

CState::CState(const CState & src) :
    mModel(src.mModel),
    mVolumesSize(src.mVolumesSize),
    mNumbersSize(src.mNumbersSize),
    mNumbersUpdated(src.mNumbersUpdated),
    mVolumes(NULL),
    mNumbersInt(NULL),
    mNumbersDbl(NULL)
{
  unsigned C_INT32 i;

  if (mVolumesSize)
    {
      mVolumes = new C_FLOAT64[mVolumesSize];

      for (i = 0; i < mVolumesSize; i++)
        {
          *(mVolumes + i) = *(src.mVolumes + i);
        }
    }

  if (mNumbersSize)
    {
      mNumbersInt = new C_INT32[mNumbersSize];
      mNumbersDbl = new C_FLOAT64[mNumbersSize];

      for (i = 0; i < mNumbersSize; i++)
        {
          *(mNumbersInt + i) = *(src.mNumbersInt + i);
          *(mNumbersDbl + i) = *(src.mNumbersDbl + i);
        }
    }
}

CState::~CState()
{
  pdelete (mVolumes);
  pdelete (mNumbersInt);
  pdelete (mNumbersDbl);
}
const unsigned C_INT32 & CState::getNumbersSize() const { return mNumbersSize; }

const unsigned C_INT32 & CState::getNumbersUpdated() const
  { return mNumbersUpdated; }
const unsigned C_INT32 & CState::getVolumesSize() const { return mVolumesSize; }

CStateX::CStateX(const CModel * model) : CState(model)
{
  if (model)
    mNumbersUpdated = model->getIndMetab();
}
CStateX::CStateX(const CStateX & src) : CState(src) {}
CStateX::~CStateX() {}
