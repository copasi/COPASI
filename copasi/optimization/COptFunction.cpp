/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/optimization/Attic/COptFunction.cpp,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:58 $
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
    mKey(GlobalKeys.add("OptFunction", this))
{
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
    mParaList(src.mParaList),
    mMinList(src.mMinList),
    mMaxList(src.mMaxList),
    mMinOperList(src.mMinOperList),
    mMaxOperList(src.mMaxOperList),
    mMinFunctionList(src.mMinFunctionList),
    mMaxFunctionList(src.mMaxFunctionList),
    mKey(GlobalKeys.add("OptFunction", this))
{}

COptFunction::~COptFunction()
{
  GlobalKeys.remove(mKey);
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
int COptFunction::Index(const std::string & name)
{
  unsigned C_INT32 i;
  for (i = 0; i < mParaList.size(); i++)
    if (mParaList[i]->getCN() == name)
      return i;
  return C_INVALID_INDEX;
}

// add a new item inside
int COptFunction::addItem(CCopasiObject* pObject)
{
  //shall not exist in the list
  if (Index(pObject->getCN()) != C_INVALID_INDEX)
    return C_INVALID_INDEX; //cannot insert in
  mParaList.push_back(pObject);
  mMinList.push_back("-inf");
  mMaxList.push_back("+inf");
  mMinFunctionList.push_back(NULL);
  mMaxFunctionList.push_back(NULL);
  return mParaList.size() - 1;
}

bool COptFunction::removeItem(const std::string & name)
{
  unsigned C_INT32 i;
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
