/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/function/CFunctionDB.cpp,v $
   $Revision: 1.72.2.2 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/09/26 15:43:10 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionDB
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#include "copasi.h"

#include "CFunctionDB.h"
#include "CFunction.h"

#include "utilities/CCopasiException.h"
#include "report/CCopasiObjectReference.h"
#include "xml/CCopasiXML.h"
#include "report/CKeyFactory.h"
#include "FunctionDB.xml.h"

CFunctionDB::CFunctionDB(const std::string & name,
                         const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "FunctionDB"),
    mFilename(),
    mLoadedFunctions("Functions", this)
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CFunctionDB::~CFunctionDB()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CFunctionDB::cleanup() {mLoadedFunctions.cleanup();}

void CFunctionDB::initObjects()
{
  addObjectReference("File", mFilename);
}

bool CFunctionDB::load()
{
  CCopasiXML XML;
  std::stringstream DB;
  DB.str(FunctionDBxml);
  //  std::ifstream DB(mFilename.c_str());
  if (DB.fail()) return false;
  if (!XML.load(DB, "")) return false;

  CCopasiVectorN< CEvaluationTree > * pFunctionList = XML.getFunctionList();

  unsigned C_INT32 i, imax = pFunctionList->size();

  for (i = 0; i < imax; i++)
    mLoadedFunctions.add((*pFunctionList)[i], true);

  XML.freeFunctionList();

  return true;
}

C_INT32 CFunctionDB::load(CReadConfig &configbuffer)
{
  CFunction Function;
  CFunction * pFunction = NULL;

  C_INT32 Size = 0;
  C_INT32 Fail = 0;

  configbuffer.getVariable("TotalUDKinetics", "C_INT32", &Size,
                           CReadConfig::LOOP);

  for (C_INT32 i = 0; i < Size; i++)
    {
      Function.load(configbuffer);

      switch (Function.getType())
        {
        case CEvaluationTree::Function:
          pFunction = new CFunction(Function);
          break;

        case CEvaluationTree::MassAction:
          pFunction = new CMassAction(Function);
          break;

        case CEvaluationTree::PreDefined:
        case CEvaluationTree::UserDefined:
          pFunction = new CKinFunction(Function,
                                       &configbuffer);
          break;

        default:
          fatalError();
        }

      pFunction->compile();

      if (!mLoadedFunctions.add(pFunction, true))
        {
          pdelete(pFunction);
          // We ignore:
          // CCopasiVector (2): Object '%s' allready exists.
          if ((MCCopasiVector + 2) != CCopasiMessage::peekLastMessage().getNumber())
            return Fail = 1;

          // Remove the ignored meesage.
          CCopasiMessage::getLastMessage();
        }
    }

  return Fail;
}

void CFunctionDB::setFilename(const std::string & filename)
{mFilename = filename;}

std::string CFunctionDB::getFilename() const
  {return mFilename;}

#ifdef FFFF
CFunction * CFunctionDB::dBLoad(const std::string & functionName)
{
  CFunction Function("NoName", &mLoadedFunctions);
  CFunction * pFunction = NULL;

  if (mFilename == "") return NULL;
  CReadConfig inbuf(mFilename);

  while (functionName != Function.getObjectName())
    {
      Function.cleanup();
      Function.load(inbuf);
    }

  switch (Function.getType())
    {
    case CFunction::Base:
      pFunction = new CFunction(Function);
      break;

    case CFunction::MassAction:
      pFunction = new CMassAction(Function.isReversible());
      break;

    case CFunction::PreDefined:

    case CFunction::UserDefined:
      pFunction = new CKinFunction(Function, &inbuf);
      break;

    case CFunction::Expression:
      fatalError(); //disabled
      //pFunction = new CUDFunction(Function);
      break;

    default:
      fatalError();
    }

  if (!mLoadedFunctions.add(pFunction))
    {
      pdelete(pFunction);
      // We ignore:
      // CCopasiVector (2): Object '%s' allready exists.
      if ((MCCopasiVector + 2) != CCopasiMessage::getLastMessage().getNumber())

        pFunction = mLoadedFunctions[Function.getObjectName()];
    }

  return pFunction;
}
#endif // FFFF

#ifdef FFFF
CEvaluationTree * CFunctionDB::createFunction(const std::string & name, const CEvaluationTree::Type & type)
{
  if (mLoadedFunctions.getIndex(name) != C_INVALID_INDEX)
    return NULL;

  //CFunction * pFunction = new CFunction(name);

  CEvaluationTree * pFunction = NULL;
  switch (type)
    {
    case CEvaluationTree::Base:
      pFunction = new CFunction(name);
      break;

    case CEvaluationTree::MassAction:
      pFunction = new CMassAction(name);
      break;

    case CEvaluationTree::PreDefinedKineticLaw:
    case CEvaluationTree::UserDefinedKineticLaw:
      pFunction = new CKinFunction(name);
      break;

    default:
      fatalError();
    }

  if (!mLoadedFunctions.add(pFunction, true))
    {
      delete pFunction;
      return NULL;
    }
  return pFunction;
}
#endif // FFFF

bool CFunctionDB::add(CEvaluationTree * pFunction,
                      const bool & adopt)
{return mLoadedFunctions.add(pFunction, adopt);}

bool CFunctionDB::removeFunction(const std::string &key)
{
  CEvaluationTree* func = dynamic_cast< CEvaluationTree * >(GlobalKeys.get(key));
  if (!func) return false;

  unsigned C_INT32 index =
    mLoadedFunctions.CCopasiVector<CEvaluationTree>::getIndex(func);
  if (index == C_INVALID_INDEX) return false;

  mLoadedFunctions.CCopasiVector<CEvaluationTree>::remove(index);

  return true;
}

CEvaluationTree * CFunctionDB::findFunction(const std::string & functionName)
{
  unsigned C_INT32 index = mLoadedFunctions.getIndex(functionName);

  if (index != C_INVALID_INDEX)
    return mLoadedFunctions[index];
  else
    return NULL;
}

CEvaluationTree * CFunctionDB::findLoadFunction(const std::string & functionName)
{
  unsigned C_INT32 i;

  for (i = 0; i < mLoadedFunctions.size(); i++)
    if (functionName == mLoadedFunctions[i]->getObjectName())
      return mLoadedFunctions[i];

  return NULL;
}

CCopasiVectorN < CEvaluationTree > & CFunctionDB::loadedFunctions()
{return mLoadedFunctions;}

std::vector<CFunction*>
CFunctionDB::suitableFunctions(const unsigned C_INT32 noSubstrates,
                               const unsigned C_INT32 noProducts,
                               const TriLogic reversibility)
{
  std::vector<CFunction*> ret;
  CFunction *pFunction;

  unsigned C_INT32 i, imax = mLoadedFunctions.size();
  for (i = 0; i < imax; i++)
    {
      pFunction = dynamic_cast<CFunction *>(mLoadedFunctions[i]);
      if (!pFunction) continue;

      if (pFunction->isSuitable(noSubstrates, noProducts, reversibility))
        ret.push_back(pFunction);
    }

  //always add constant flux it is is missing
  if (reversibility == TriTrue)
    {
      if ((noSubstrates > 0) || (noProducts > 0)) //constant flux was not yet added
        {
          pFunction = dynamic_cast<CFunction*>(findFunction("Constant flux (reversible)"));
          if (!pFunction) fatalError();
          ret.push_back(pFunction);
        }
    }
  else //irreversible
    {
      if (noSubstrates > 0) //constant flux was not yet added
        {
          pFunction = dynamic_cast<CFunction*>(findFunction("Constant flux (irreversible)"));
          if (!pFunction) fatalError();
          ret.push_back(pFunction);
        }
    }

  return ret;
}

void CFunctionDB::appendDependentFunctions(std::set< const CCopasiObject * > candidates,
    std::set< const CCopasiObject * > & dependentFunctions) const
  {
    CCopasiVectorN< CEvaluationTree >::const_iterator it = mLoadedFunctions.begin();
    CCopasiVectorN< CEvaluationTree >::const_iterator end = mLoadedFunctions.end();

    for (; it != end; ++it)
      if (candidates.find(*it) == candidates.end() &&
          (*it)->hasCircularDependencies(candidates))
        dependentFunctions.insert((*it));

    return;
  }

std::set<std::string>
CFunctionDB::listDependentTrees(const std::string & name) const
  {
    std::set<std::string> List;

    CCopasiVectorN < CEvaluationTree >::const_iterator it = mLoadedFunctions.begin();
    CCopasiVectorN < CEvaluationTree >::const_iterator end = mLoadedFunctions.end();

    for (; it != end; ++it)
      if ((*it)->dependsOnTree(name))
        List.insert((*it)->getObjectName());

    return List;
  }
