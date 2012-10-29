// Copyright (C) 2010 - 2012 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/**
 * CFunctionDB
 *
 * Created for Copasi by Stefan Hoops
 * (C) Stefan Hoops 2001
 */

#include <algorithm>

#include "copasi.h"

#include "CFunctionDB.h"
#include "CFunction.h"
#include "FunctionDB.xml.h"

#include "utilities/CCopasiException.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "xml/CCopasiXML.h"
#include "model/CModel.h"

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
  XML.setFunctionList(&mLoadedFunctions);

  std::stringstream DB;
  DB.str(FunctionDBxml);

  if (DB.fail())
    return false;

  if (!XML.load(DB, ""))
    return false;

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
            break;
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

bool CFunctionDB::add(CFunction * pFunction,
                      const bool & adopt)
{return mLoadedFunctions.add(pFunction, adopt);}

CFunction * CFunctionDB::addAndAdaptName(CFunction * pFunction)
{
  if (!pFunction) return NULL;

  std::string basename = pFunction->getObjectName();
  std::string name = basename;
  //CFunction* pFunc;
  //CCopasiVectorN<CEvaluationTree>& FunctionList
  //= this->loadedFunctions();
  int i = 0;

  size_t Index = C_INVALID_INDEX;

  while ((Index = mLoadedFunctions.getIndex(name)) != C_INVALID_INDEX)
    {
      // Check whether the new functions and the old are the same.
      if (*mLoadedFunctions[Index] == *pFunction)
        {
          pdelete(pFunction);
          return mLoadedFunctions[Index];
        }

      i++;
      std::ostringstream ss; ss << "[" << i << "]";
      name = basename + ss.str();
    }

  pFunction->setObjectName(name);
  this->add(pFunction, true);

  return pFunction;
}

bool CFunctionDB::removeFunction(size_t index)
{
  if (index == C_INVALID_INDEX) return false;

  // We need to delete all dependent objects in all data models.
  CCopasiVector< CCopasiDataModel >::iterator it = CCopasiRootContainer::getDatamodelList()->begin();
  CCopasiVector< CCopasiDataModel >::iterator end = CCopasiRootContainer::getDatamodelList()->end();

  std::set< const CCopasiObject * > DeletedObjects = mLoadedFunctions[index]->getDeletedObjects();

  for (; it != end; ++it)
    {
      (*it)->getModel()->removeDependentModelObjects(DeletedObjects);
    }

  mLoadedFunctions.CCopasiVector<CFunction>::remove(index);

  return true;
}

bool CFunctionDB::removeFunction(const std::string &key)
{
  CEvaluationTree* func = dynamic_cast< CEvaluationTree * >(CCopasiRootContainer::getKeyFactory()->get(key));

  if (!func) return false;

  size_t index =
    mLoadedFunctions.CCopasiVector<CFunction>::getIndex(func);

  if (index == C_INVALID_INDEX) return false;

  return removeFunction(index);
}

CFunction * CFunctionDB::findFunction(const std::string & functionName)
{
  size_t index = mLoadedFunctions.getIndex(functionName);

  if (index != C_INVALID_INDEX)
    return mLoadedFunctions[index];
  else
    return NULL;
}

CFunction * CFunctionDB::findLoadFunction(const std::string & functionName)
{
  size_t i;

  for (i = 0; i < mLoadedFunctions.size(); i++)
    if (functionName == mLoadedFunctions[i]->getObjectName())
      return mLoadedFunctions[i];

  return NULL;
}

CCopasiVectorN < CFunction > & CFunctionDB::loadedFunctions()
{return mLoadedFunctions;}

std::vector<CFunction*>
CFunctionDB::suitableFunctions(const size_t noSubstrates,
                               const size_t noProducts,
                               const TriLogic reversibility)
{
  std::vector<CFunction*> ret;
  CFunction *pFunction;

  size_t i, imax = mLoadedFunctions.size();

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

bool CFunctionDB::appendDependentFunctions(std::set< const CCopasiObject * > candidates,
    std::set< const CCopasiObject * > & dependentFunctions) const
{
  size_t Size = dependentFunctions.size();
  CCallParameters< C_FLOAT64 > CallParmeters;

  CCopasiVectorN< CFunction >::const_iterator it = mLoadedFunctions.begin();
  CCopasiVectorN< CFunction >::const_iterator end = mLoadedFunctions.end();

  for (; it != end; ++it)
    if (candidates.find(*it) == candidates.end() &&
        (*it)->CEvaluationTree::dependsOn(candidates))
      dependentFunctions.insert((*it));

  return Size < dependentFunctions.size();
}

std::set<std::string>
CFunctionDB::listDependentTrees(const std::string & name) const
{
  std::set<std::string> List;

  CCopasiVectorN < CFunction >::const_iterator it = mLoadedFunctions.begin();
  CCopasiVectorN < CFunction >::const_iterator end = mLoadedFunctions.end();

  for (; it != end; ++it)
    if ((*it)->dependsOnTree(name))
      List.insert((*it)->getObjectName());

  return List;
}

std::vector< CFunction * > CFunctionDB::getUsedFunctions(const CModel* pModel) const
{
  std::vector< CFunction * > UsedFunctions;
  CCopasiVectorN < CFunction >::const_iterator it = mLoadedFunctions.begin();
  CCopasiVectorN < CFunction >::const_iterator end = mLoadedFunctions.end();

  for (; it != end; ++it)
    {
      std::set< const CCopasiObject * > Function;
      Function.insert(*it);

      std::set< const CCopasiObject * > Reactions;
      std::set< const CCopasiObject * > Metabolites;
      std::set< const CCopasiObject * > Values;
      std::set< const CCopasiObject * > Compartments;
      std::set< const CCopasiObject * > Events;

      pModel->appendDependentModelObjects(Function,
                                          Reactions, Metabolites, Compartments, Values, Events);

      if (Reactions.size() != 0)
        {
          UsedFunctions.push_back(*it);
          continue;
        }

      if (Metabolites.size() != 0)
        {
          UsedFunctions.push_back(*it);
          continue;
        }

      if (Values.size() != 0)
        {
          UsedFunctions.push_back(*it);
          continue;
        }

      if (Compartments.size() != 0)
        {
          UsedFunctions.push_back(*it);
          continue;
        }

      if (Events.size() != 0)
        {
          UsedFunctions.push_back(*it);
          continue;
        }
    }

  CFunction::completeFunctionList(UsedFunctions);

  return UsedFunctions;
}
