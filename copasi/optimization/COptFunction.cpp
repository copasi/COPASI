
#include <sstream>
#include "copasi.h"
#include "FlexLexer.h"
#include "function/CFunction.h"
#include "COptFunction.h"
#include "COptMethod.h"
#include "COptProblem.h"
#include "report/CKeyFactory.h"

COptFunction::COptFunction(const std::string & name, const CCopasiContainer * pParent)
    : CCopasiContainer(name, pParent, "OptFunction"),
    mKey(CKeyFactory::add("OptFunction", this)),
    mpMethod(new COptMethod),
    mpProblem(new COptProblem)
{
  mpMethod->setProblem(mpProblem);
  mParaList.clear();
  mMinFunctionList.clear();
  mMaxFunctionList.clear();
  mMinList.clear();
  mMaxList.clear();
  mMinOperList.clear();
  mMaxOperList.clear();
}

COptFunction::COptFunction(const COptFunction & src, CReadConfig * configBuffer, const CCopasiContainer * pParent)
    : CCopasiContainer(src, pParent),
    mKey(CKeyFactory::add("OptFunction", this)),
    mpMethod(src.mpMethod),
    mpProblem(src.mpProblem),
    mParaList(src.mParaList),
    mMinFunctionList(src.mMinFunctionList),
    mMaxFunctionList(src.mMaxFunctionList),
    mMinList(src.mMinList),
    mMaxList(src.mMaxList),
    mMinOperList(src.mMinOperList),
    mMaxOperList(src.mMaxOperList)
{
  mpMethod->setProblem(mpProblem);
}

COptFunction::~COptFunction()
{
  CKeyFactory::remove(mKey);
  cleanup();
}

void COptFunction::cleanup()
{
  //static members will be deleted during the deconstruction of COptFunction
  mParaList.clear();
  mMinFunctionList.clear();
  mMaxFunctionList.clear();
  mMinList.clear();
  mMaxList.clear();
  mMinOperList.clear();
  mMaxOperList.clear();
}

// check if a parameter already existing inside the mParaList
bool COptFunction::bExisted(const std::string & name)
{
  int i;
  for (i = 0; i < mParaList.size(); i++)
    if (mParaList[i]->getCN() == name)
      return true;
  return false;
}

// add a new item inside
int COptFunction::addItem(CCopasiObject* pObject)
{
  if (bExisted(pObject->getCN()))
    return - 1; //
  mParaList.push_back(pObject);
  mMinList.push_back("-inf");
  mMaxList.push_back("+inf");
  return mParaList.size() - 1;
}

bool COptFunction::removeItem(const std::string & name)
{
  int i;
  for (i = 0; i < mParaList.size(); i++)
    {
      if (mParaList[i]->getCN() == name)
        {
          mParaList.erase(mParaList.begin() + i);
          mMinList.erase(mMinList.begin() + i);
          mMaxList.erase(mMaxList.begin() + i);
          return true;
        }
    }
  return false;
}
