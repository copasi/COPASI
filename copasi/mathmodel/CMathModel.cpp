/**
 *  CMathModel class.
 *  The class CMathModel is a mathematical representation of a chemical
 *  model (class CModel
 *
 *  Created for Copasi by Stefan Hoops 2003
 */

#include "copasi.h"
#include "CMathModel.h"
#include "CMathConstant.h"
#include "CMathVariable.h"
#include "model/CModel.h"

CMathModel::CMathModel():
    mpModel(NULL),
    mCompartmentList(),
    mMetabList(),
    mFixedMetabList(),
    mVolumeList(),
    mpTime(NULL),
    mFunctionList(),
    mConstantsList()
{}

CMathModel::CMathModel(const CMathModel & src):
    mpModel(src.mpModel),
    mCompartmentList(src.mCompartmentList),
    mMetabList(src.mMetabList),
    mFixedMetabList(src.mFixedMetabList),
    mVolumeList(src.mVolumeList),
    mpTime(src.mpTime),
    mFunctionList(src.mFunctionList),
    mConstantsList(src.mConstantsList)
{compile();}

CMathModel::~CMathModel()
{
  clearList((std::map< std::string, CMathSymbol * > *) & mCompartmentList);
  clearList((std::map< std::string, CMathSymbol * > *) & mMetabList);
  clearList((std::map< std::string, CMathSymbol * > *) & mFixedMetabList);
  clearList((std::map< std::string, CMathSymbol * > *) & mVolumeList);
  pdelete(mpTime);
  clearList((std::map< std::string, CMathSymbol * > *) & mFunctionList);
  clearList((std::map< std::string, CMathSymbol * > *) & mConstantsList);
}

bool CMathModel::setModel(const CModel * pModel)
{
  mpModel = pModel;
  return compile();
}

const CModel * CMathModel::getModel() const {return mpModel;}

bool CMathModel::compile()
{
  if (!mpModel) return false;

  bool Success = true;

  if (!buildCompartmentList()) Success = false;
  if (!buildMetabList()) Success = false;
  if (!buildFixedMetabList()) Success = false;
  if (!buildVolumeList()) Success = false;
  if (!buildTime()) Success = false;
  if (!buildFunctionList()) Success = false;
  if (!buildConstantsList()) Success = false;

  if (!compileCompartmentList()) Success = false;
  if (!compileMetabList()) Success = false;
  if (!compileFixedMetabList()) Success = false;

  return Success;
}

std::map< std::string, CMathConstantCompartment * > & CMathModel::getCompartmentList()
{return mCompartmentList;}

std::map< std::string, CMathVariableMetab * > & CMathModel::getMetabList()
{return mMetabList;}

std::map< std::string, CMathConstantMetab * > & CMathModel::getFixedMetabList()
{return mFixedMetabList;}

std::map< std::string, CMathVariableVolume * > & CMathModel::getVolumeList()
{return mVolumeList;}

CMathVariableTime * CMathModel::getTime() {return mpTime;}

std::map< std::string, CMathSymbol * > & CMathModel::getFunctionList()
{return mFunctionList;}

std::map< std::string, CMathConstantParameter * > & CMathModel::getConstantsList()
{return mConstantsList;}

bool CMathModel::buildCompartmentList()
{
  bool Success = true;

  clearList((std::map< std::string, CMathSymbol * > *) & mCompartmentList);

  const CCopasiVector< CCompartment > & List = mpModel->getCompartments();
  unsigned C_INT32 i, imax = List.size();

  CMathConstantCompartment * p;

  for (i = 0; i < imax; i++)
    {
      p = new CMathConstantCompartment(*List[i]);
      mCompartmentList[p->getName()] = p;
    }

  return Success;
}

bool CMathModel::buildMetabList()
{
  bool Success = true;

  clearList((std::map< std::string, CMathSymbol * > *) & mMetabList);

  const CCopasiVector< CMetab > & List = mpModel->getMetabolitesX();
  unsigned C_INT32 i, imax = mpModel->getIntMetab();

  CMathVariableMetab * p;

  for (i = 0; i < imax; i++)
    {
      p = new CMathVariableMetab(*List[i]);
      mMetabList[p->getName()] = p;
    }

  return Success;
}

bool CMathModel::buildFixedMetabList()
{
  bool Success = true;

  clearList((std::map< std::string, CMathSymbol * > *) & mFixedMetabList);

  const CCopasiVector< CMetab > & List = mpModel->getMetabolitesX();
  unsigned C_INT32 i, imax = List.size();

  CMathConstantMetab * p;

  for (i = mpModel->getIntMetab(); i < imax; i++)
    {
      p = new CMathConstantMetab(*List[i]);
      mFixedMetabList[p->getName()] = p;
    }

  return Success;
}

bool CMathModel::buildVolumeList()
{
  bool Success = true;

#ifdef  XXXX
  /* :TODO: This needs to be activated/modified when we implement variable
     volumes. */
  clearList((std::map< std::string, CMathSymbol * > *) & mCompartmentList);

  const CCopasiVector< CCompartment > & List = mpModel->getCompartments();
  unsigned C_INT32 i, imax = List.size();

  CMathVariableVolume * p;

  for (i = 0; i < imax; i++)
    {
      p = new CMathVariableVolume(*List[i]);
      mVolumeList[p->getName()] = p;
    }
#endif // XXXX
  return Success;
}

bool CMathModel::buildTime()
{
  bool Success = true;

  pdelete(mpTime);

  mpTime = new CMathVariableTime(*mpModel);

  return Success;
}

bool CMathModel::buildFunctionList()
{
  bool Success = true;

  clearList(& mFunctionList);

  const CCopasiVector< CReaction > & List = mpModel->getReactions();
  unsigned C_INT32 i, imax = List.size();

  CMathSymbol * p;
  const CFunction * pFunction;

  for (i = 0; i < imax; i++)
    {
      pFunction = &List[i]->getFunction();
      if (!CMathSymbol::find(pFunction))
        {
          p = new CMathSymbol(pFunction);
          mFunctionList[p->getName()] = p;
        }
    }

  return Success;
}

bool CMathModel::buildConstantsList()
{
  bool Success = true;

  clearList((std::map< std::string, CMathSymbol * > *) & mConstantsList);

  const CCopasiVector< CReaction > & List = mpModel->getReactions();
  unsigned C_INT32 i, imax = List.size();
  unsigned C_INT32 j, jmax;

  CMathConstantParameter * p;
  CCopasiVector< CReaction::CId2Param > * ParamList;
  for (i = 0; i < imax; i++)
    {
      ParamList = &List[i]->getId2Parameters();
      jmax = ParamList->size();

      for (j = 0; j < jmax; j++)
        {
          p = new CMathConstantParameter(*(*ParamList)[j]);
          mConstantsList[p->getName()] = p;
        }
    }

  return Success;
}

bool CMathModel::clearList(std::map< std::string, CMathSymbol * > * list)
{
  std::map< std::string, CMathSymbol * >::iterator it = list->begin();
  std::map< std::string, CMathSymbol * >::iterator end = list->end();

  for (; it != end; it++)
    pdelete(it->second);

  list->clear();

  return true;
}

bool CMathModel::compileCompartmentList()
{
  bool Success = true;

  std::map< std::string, CMathConstantCompartment * >::iterator it =
    mCompartmentList.begin();
  std::map< std::string, CMathConstantCompartment * >::iterator end =
    mCompartmentList.end();

  for (; it != end; it++)
    if (!it->second->compile()) Success = false;

  return Success;
}

bool CMathModel::compileMetabList()
{
  bool Success = true;

  std::map< std::string, CMathVariableMetab * >::iterator it =
    mMetabList.begin();
  std::map< std::string, CMathVariableMetab * >::iterator end =
    mMetabList.end();

  for (; it != end; it++)
    if (!it->second->compile()) Success = false;

  return Success;
}

bool CMathModel::compileFixedMetabList()
{
  bool Success = true;

  std::map< std::string, CMathConstantMetab * >::iterator it =
    mFixedMetabList.begin();
  std::map< std::string, CMathConstantMetab * >::iterator end =
    mFixedMetabList.end();

  for (; it != end; it++)
    if (!it->second->compile()) Success = false;

  return Success;
}
