// CSate.cpp
//
// (C) Stefan Hoops 2002
//

#include <typeinfo>

#define  COPASI_TRACE_CONSTRUCTION

#include "copasi.h"
#include "CState.h"
#include "CModel.h"
#include "CCompartment.h"
#include "utilities/CGlobals.h"

CState::CState(const CModel * model) :
    mModel(model),
    mVolumesSize(0),
    mVolumes(NULL),
    mNumbersSize(0),
    mNumbersUpdated(0),
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
    mVolumes(NULL),
    mNumbersSize(src.mNumbersSize),
    mNumbersUpdated(src.mNumbersUpdated),
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

void CState::setModel(const CModel * model)
{
  pdelete (mVolumes);
  pdelete (mNumbersInt);
  pdelete (mNumbersDbl);

  mModel = model;

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
const unsigned C_INT32 & CState::getNumbersSize() const { return mNumbersSize; }

const unsigned C_INT32 & CState::getNumbersUpdated() const
  { return mNumbersUpdated; }
const unsigned C_INT32 & CState::getVolumesSize() const { return mVolumesSize; }

CState * CState::load(CReadConfig & configBuffer)
{
  CState * pState = NULL;
  string Tmp;
  C_INT32 Size;
  unsigned C_INT32 i;

  configBuffer.getVariable("StateType", "string", &Tmp);

  if (Tmp == "Full Model")
    pState = new CState();
  else if (Tmp == "Reduced Model")
    pState = new CStateX();
  else
    fatalError();

  configBuffer.getVariable("StateModel", "string", &Tmp);

  if (Tmp == Copasi->Model->getTitle())
    pState->mModel = Copasi->Model;
  else
    fatalError();

  configBuffer.getVariable("StateTime", "C_FLOAT64", &pState->mTime);

  configBuffer.getVariable("StateVolumesSize", "C_INT32", &Size);

  pState->mVolumesSize = Size;

  for (i = 0; i < pState->mVolumesSize; i++)
    {
      Tmp = StringPrint("StateVolumes[%d]", i);
      configBuffer.getVariable("Tmp", "C_FLOAT64", & pState->mVolumes[i]);
    }

  configBuffer.getVariable("StateNumberdSize", "C_INT32", &Size);
  pState->mNumbersSize = Size;

  configBuffer.getVariable("StateNumberdUpdated", "C_INT32", &Size);
  pState->mNumbersUpdated = Size;

  for (i = 0; i < pState->mNumbersSize; i++)
    {
      Tmp = StringPrint("StateNumbersInt[%d]", i);
      configBuffer.getVariable("Tmp", "C_INT32", & pState->mNumbersInt[i]);
    }

  for (i = 0; i < pState->mNumbersSize; i++)
    {
      Tmp = StringPrint("StateNumbersDbl[%d]", i);
      configBuffer.getVariable("Tmp", "C_FLOAT64", & pState->mNumbersDbl[i]);
    }

  return pState;
}

void CState::save(CWriteConfig & configBuffer, const CState * pState)
{
  string Tmp;
  C_INT32 Size;
  unsigned C_INT32 i;

  if (typeid(*pState) == typeid(CState))
    Tmp == "Full Model";
  else if (typeid(*pState) == typeid(CStateX))
    Tmp == "Reduced Model";
  else
    fatalError();

  Tmp = pState->mModel->getTitle();

  configBuffer.setVariable("StateModel", "string", &Tmp);

  configBuffer.setVariable("StateType", "string", &Tmp);

  configBuffer.setVariable("StateTime", "C_FLOAT64", &pState->mTime);

  Size = pState->mVolumesSize;

  configBuffer.setVariable("StateVolumesSize", "C_INT32", &Size);

  for (i = 0; i < pState->mVolumesSize; i++)
    {
      Tmp = StringPrint("StateVolumes[%d]", i);
      configBuffer.setVariable("Tmp", "C_FLOAT64", & pState->mVolumes[i]);
    }

  Size = pState->mNumbersSize;
  configBuffer.setVariable("StateNumberdSize", "C_INT32", &Size);

  Size = pState->mNumbersUpdated;
  configBuffer.setVariable("StateNumberdUpdated", "C_INT32", &Size);

  for (i = 0; i < pState->mNumbersSize; i++)
    {
      Tmp = StringPrint("StateNumbersInt[%d]", i);
      configBuffer.setVariable("Tmp", "C_INT32", & pState->mNumbersInt[i]);
    }

  for (i = 0; i < pState->mNumbersSize; i++)
    {
      Tmp = StringPrint("StateNumbersDbl[%d]", i);
      configBuffer.setVariable("Tmp", "C_FLOAT64", & pState->mNumbersDbl[i]);
    }

  return ;
}

CStateX::CStateX(const CModel * model) : CState(model)
{
  if (model)
    mNumbersUpdated = model->getIndMetab();
}
CStateX::CStateX(const CStateX & src) : CState(src) {}
CStateX::~CStateX() {}

void CStateX::setModel(const CModel * model)
{
  CState::setModel(model);

  mModel = model;
  mNumbersUpdated = model->getIndMetab();
}
