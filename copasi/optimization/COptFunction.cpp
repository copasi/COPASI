/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/Attic/COptFunction.cpp,v $
   $Revision: 1.14 $
   $Name:  $
   $Author: lixu1 $ 
   $Date: 2003/10/16 20:00:28 $
   End CVS Header */

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
  mMinFunctionList.push_back(NULL);
  mMaxFunctionList.push_back(NULL);
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
          mMinFunctionList.erase(mMinFunctionList.begin() + i);
          mMaxFunctionList.erase(mMaxFunctionList.begin() + i);
          return true;
        }
    }
  return false;
}

void COptFunction::connect()
{
  int i;
  CKinFunction* pMinFunc, * pMaxFunc;
  for (i = 0; i < mParaList.size(); i++)
    {
      //      pMinFunc = NULL;
      //      pMaxFunc = NULL;
      if (mMinList[i] != "-inf")
        {
          //          pMinFunc = new CKinFunction();
          //          pMinFunc->setDescription(mMinList[i].c_str());
          //          pMinFunc->compile();
          mMinFunctionList[i]->connect();
        }

      if (mMaxList[i] != "+inf")
        {
          //          pMaxFunc = new CKinFunction();
          //          pMaxFunc->setDescription(mMaxList[i].c_str());
          //          pMaxFunc->compile();
          mMaxFunctionList[i]->connect();
        }
      //      mMinFunctionList.push_back(pMinFunc);
      //      mMaxFunctionList.push_back(pMaxFunc);
    }
}
