// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/copasi.h"

#include "copasi/function/CFunctionDB.h"
#include "copasi/function/CFunction.h"
#include "copasi/function/FunctionDB.xml.h"

#include "copasi/utilities/CCopasiException.h"
#include "copasi/utilities/CDirEntry.h"
#include "copasi/core/CDataObjectReference.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/xml/CCopasiXML.h"
#include "copasi/model/CModel.h"
#include "copasi/core/CRootContainer.h"

CFunctionDB::CFunctionDB(const std::string & name,
                         const CDataContainer * pParent):
  CDataContainer(name, pParent, "FunctionDB"),
  mFilename(),
  mLoadedFunctions("Functions", this),
  mDependencies()
{
  initObjects();
  CONSTRUCTOR_TRACE;
}

CFunctionDB::~CFunctionDB()
{
  cleanup();
  DESTRUCTOR_TRACE;
}

void CFunctionDB::cleanup()
{
  mLoadedFunctions.cleanup();
  mDependencies.clear();
}

void CFunctionDB::initObjects()
{
  addObjectReference("File", mFilename);
  addObjectReference("Avogadro Constant", CUnit::Avogadro);
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

bool CFunctionDB::load(const std::string& fileName)
{
  CCopasiXML XML;
  XML.setFunctionList(&mLoadedFunctions);
  std::fstream str(fileName.c_str());

  if (str.fail())
    return false;

  if (!XML.load(str, ""))
    return false;

  return true;
}

bool CFunctionDB::save(const std::string& fileName)
{
  CCopasiXML XML;
  XML.setFunctionList(&mLoadedFunctions);
  return XML.CCopasiXMLInterface::save(fileName, CDirEntry::dirName(fileName));
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
            pFunction = new CFunction(Function, NO_PARENT);
            break;

          case CEvaluationTree::MassAction:
            pFunction = new CMassAction(Function, NO_PARENT);
            break;

          case CEvaluationTree::PreDefined:
          case CEvaluationTree::UserDefined:
            pFunction = new CKinFunction(Function, NO_PARENT, &configbuffer);
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
          // CDataVector (2): Object '%s' allready exists.
          if ((MCDataVector + 2) != CCopasiMessage::peekLastMessage().getNumber())
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
      // CDataVector (2): Object '%s' allready exists.
      if ((MCDataVector + 2) != CCopasiMessage::getLastMessage().getNumber())

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
  //CDataVectorN<CEvaluationTree>& FunctionList
  //= this->loadedFunctions();
  int i = 0;

  size_t Index = C_INVALID_INDEX;

  while ((Index = mLoadedFunctions.getIndex(name)) != C_INVALID_INDEX)
    {
      // Check whether the new functions and the old are the same.
      if (mLoadedFunctions[Index] == *pFunction)
        {
          pdelete(pFunction);
          return &mLoadedFunctions[Index];
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

  CFunction * pFunction = &mLoadedFunctions[index];

  // We need to remove all dependent functions.
  CDataObject::ObjectSet DeletedObjects;
  DeletedObjects.insert(pFunction);
  CDataObject::DataObjectSet Functions;

  appendDependentFunctions(DeletedObjects, Functions);

  std::set< const CDataObject * >::const_iterator itFunction = Functions.begin();
  std::set< const CDataObject * >::const_iterator endFunction = Functions.end();

  for (; itFunction != endFunction; ++itFunction)
    {
      removeFunction(mLoadedFunctions.CDataVector<CFunction>::getIndex(*itFunction));
    }

  // We need to delete all dependent objects in all data models.
  CDataVector< CDataModel >::iterator it = CRootContainer::getDatamodelList()->begin();
  CDataVector< CDataModel >::iterator end = CRootContainer::getDatamodelList()->end();

  for (; it != end; ++it)
    {
      it->getModel()->removeFunction(pFunction);
    }

  mLoadedFunctions.CDataVector<CFunction>::remove(index);

  return true;
}

bool CFunctionDB::removeFunction(const std::string &key)
{
  CEvaluationTree* func = dynamic_cast< CEvaluationTree * >(CRootContainer::getKeyFactory()->get(key));

  if (!func) return false;

  size_t index =
    mLoadedFunctions.CDataVector<CFunction>::getIndex(func);

  if (index == C_INVALID_INDEX) return false;

  return removeFunction(index);
}

CFunction * CFunctionDB::findFunction(const std::string & functionName)
{
  size_t index = mLoadedFunctions.getIndex(functionName);

  if (index != C_INVALID_INDEX)
    return &mLoadedFunctions[index];
  else
    return NULL;
}

CFunction * CFunctionDB::findLoadFunction(const std::string & functionName)
{
  size_t Index = mLoadedFunctions.getIndex(functionName);

  if (Index < mLoadedFunctions.size())
    {
      return &mLoadedFunctions[Index];
    }

  return NULL;
}

CDataVectorN < CFunction > & CFunctionDB::loadedFunctions()
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
      pFunction = dynamic_cast<CFunction *>(&mLoadedFunctions[i]);

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

bool CFunctionDB::appendDependentFunctions(const CDataObject::ObjectSet & candidates,
    CDataObject::DataObjectSet & dependentFunctions) const
{
  dependentFunctions.erase(NULL);
  size_t Size = dependentFunctions.size();

  CObjectInterface::ObjectSet DependentObjects;

  if (mDependencies.appendAllDependents(candidates, DependentObjects))
    {
      CObjectInterface::ObjectSet::const_iterator it = DependentObjects.begin();
      CObjectInterface::ObjectSet::const_iterator end = DependentObjects.end();

      for (; it != end; ++it)
        {
          dependentFunctions.insert((*it)->getDataObject());
        }

      dependentFunctions.erase(NULL);
    }

  return Size < dependentFunctions.size();
}

std::vector< const CFunction * > CFunctionDB::getUsedFunctions(const CModel* pModel) const
{
  std::vector< const CFunction * > UsedFunctions;

  if (pModel != nullptr)
    {
      CDataVectorN< CFunction >::const_iterator it = mLoadedFunctions.begin();
      CDataVectorN< CFunction >::const_iterator end = mLoadedFunctions.end();

      for (; it != end; ++it)
        {
          CDataObject::ObjectSet Function;
          Function.insert(it);

          CDataObject::DataObjectSet Reactions;
          CDataObject::DataObjectSet Metabolites;
          CDataObject::DataObjectSet Values;
          CDataObject::DataObjectSet Compartments;
          CDataObject::DataObjectSet Events;
          CDataObject::DataObjectSet EventAssignments;

          if (pModel->appendAllDependents(Function, Reactions, Metabolites, Compartments, Values, Events, EventAssignments))
            UsedFunctions.push_back(it);
        }

      CFunction::completeFunctionList(UsedFunctions);
    }

  return UsedFunctions;
}

void CFunctionDB::purgeUnusedUserDefinedFunctions()
{
  std::set< const CFunction * > UserDefinedFunctions;
  std::set< const CFunction * > UsedFunctions;

  for (const CFunction & Function : mLoadedFunctions)
    if (Function.getType() == CFunction::Type::UserDefined)
      UserDefinedFunctions.insert(&Function);

  for (const CDataModel & DataModel : *CRootContainer::getDatamodelList())
    {
      std::vector< const CFunction * > Functions = getUsedFunctions(DataModel.getModel());
      UsedFunctions.insert(Functions.begin(), Functions.end());
    }

  for (const CFunction * pFunction : UserDefinedFunctions)
    if (UsedFunctions.find(pFunction) == UsedFunctions.end())
      delete pFunction;
}
