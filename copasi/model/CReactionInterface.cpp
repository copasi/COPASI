// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include "CReactionInterface.h"
#include "CReaction.h"
#include "CModel.h"
#include "CChemEqElement.h"
#include "CopasiDataModel/CDataModel.h"
#include "function/CFunctionDB.h"
#include "report/CKeyFactory.h"
#include "model/CMetabNameInterface.h"
#include "copasi/core/CRootContainer.h"

CReactionInterface::CReactionInterface(CModel * pModel):
  mpModel(pModel),
  emptyString(""),
  mReactionReferenceKey(""),
  mChemEqI(pModel),
  mpFunction(NULL),
  mMassAction(),
  mpParameters(NULL),
  mNameMap(),
  mValues(),
  mIsLocal(),
  mHasNoise(false),
  mNoiseExpression(),
  mKineticLawUnitType(CReaction::Default),
  mScalingCompartment()
{
  assert(mpModel != NULL);
}

CReactionInterface::~CReactionInterface()
{
  pdelete(mpParameters);
  //pdelete(mpChemEq);
}

const std::vector<std::string> & CReactionInterface::getListOfMetabs(CFunctionParameter::Role role) const
{
  return mChemEqI.getListOfDisplayNames(role);
}

std::vector< std::string > CReactionInterface::getListOfPossibleFunctions() const
{
  TriLogic reversible;

  if (isReversible() == false)
    reversible = TriFalse;
  else
    reversible = TriTrue;

  std::vector<CFunction*> functionVector =
    CRootContainer::getFunctionList()->suitableFunctions(
      mChemEqI.getMolecularity(CFunctionParameter::SUBSTRATE),
      mChemEqI.getMolecularity(CFunctionParameter::PRODUCT),
      reversible);

  std::vector<std::string> ret;
  size_t i, imax = functionVector.size();

  for (i = 0; i < imax; ++i)
    ret.push_back(functionVector[i]->getObjectName());

  return ret;
}

size_t CReactionInterface::size() const
{
  if (mpFunction)
    return mpParameters->size();

  return 0;
}

bool CReactionInterface::isVector(size_t index) const
{
  if (mpFunction && index < size())
    return ((*mpParameters)[index]->getType() == CFunctionParameter::VFLOAT64);

  return false;
}

CFunctionParameter::Role CReactionInterface::getUsage(size_t index) const
{
  if (mpFunction && index < size())
    return (*mpParameters)[index]->getUsage();

  return CFunctionParameter::VARIABLE;
}

std::string CReactionInterface::getParameterName(size_t index) const
{
  if (mpFunction && index < size())
    return (*mpParameters)[index]->getObjectName();

  return emptyString;
}

void CReactionInterface::initFromReaction(const std::string & key)
{
  const CReaction *rea = dynamic_cast< CReaction *>(CRootContainer::getKeyFactory()->get(key));

  initFromReaction(rea);
}

void CReactionInterface::initFromReaction(const C_INT32 index)
{
  const CReaction *rea = &mpModel->getReactions()[index];

  initFromReaction(rea);
}

void CReactionInterface::initFromReaction(const CReaction *rea)
{
  if (!rea)
    return;

  mReactionReferenceKey = rea->getKey();

  //chemical equation
  mChemEqI.loadFromChemEq(rea->getChemEq());

  if (rea->getFunction() && (rea->getFunction() != CRootContainer::getUndefinedFunction()))
    {
      //function
      mpFunction = rea->getFunction();
      pdelete(mpParameters)
      mpParameters = new CFunctionParameters(mpFunction->getVariables(), NO_PARENT);

      //mapping
      if (!loadMappingAndValues(*rea))
        {
          setFunctionAndDoMapping(mpFunction->getObjectName());
        }
    }
  else
    {
      setFunctionWithEmptyMapping("");
    }

  mScalingCompartment = "";

  if (rea->getScalingCompartment() != NULL)
    {
      mScalingCompartment = rea->getScalingCompartment()->getObjectName();
    }

  mHasNoise = rea->hasNoise();

  mNoiseExpression = rea->getNoiseExpression();
  mKineticLawUnitType = rea->getKineticLawUnitType();
}

bool CReactionInterface::loadMappingAndValues(const CReaction & rea)
{
  bool success = true;
  std::vector< std::vector<std::string> >::const_iterator it;
  std::vector< std::vector<std::string> >::const_iterator iEnd;
  std::vector<std::string>::const_iterator jt;
  std::vector<std::string>::const_iterator jEnd;
  size_t i;

  std::string metabName;
  const CModelEntity* pObj;

  std::vector<std::string> SubList;
  SubList.resize(1);
  SubList[0] = "unknown";

  mNameMap.resize(size(), std::vector< std::string >(1, "unknown"));
  mValues.resize(size(), 0.1);
  mIsLocal.resize(size(), false);

  it = rea.getParameterMappings().begin();
  iEnd = rea.getParameterMappings().end();

  for (i = 0; it != iEnd; ++it, ++i)
    {

      if (isVector(i))
        {
          assert((getUsage(i) == CFunctionParameter::SUBSTRATE)
                 || (getUsage(i) == CFunctionParameter::PRODUCT)
                 || (getUsage(i) == CFunctionParameter::MODIFIER));

          SubList.clear();

          for (jt = it->begin(), jEnd = it->end(); jt != jEnd; ++jt)
            {
              metabName = CMetabNameInterface::getDisplayName(mpModel, *jt, true);

              if (metabName == "")
                {
                  success = false;
                  continue;
                }

              assert(metabName != "");
              SubList.push_back(metabName);
            }
        }
      else
        {
          assert(it->size() == 1);
          SubList.resize(1); SubList[0] = "unknown";

          switch (getUsage(i))
            {
              case CFunctionParameter::SUBSTRATE:
              case CFunctionParameter::PRODUCT:
              case CFunctionParameter::MODIFIER:
                metabName = CMetabNameInterface::getDisplayName(mpModel, *(it->begin()), true);
                // assert(metabName != "");
                SubList[0] = metabName;
                //TODO: check if the metabolite is in the chemical equation with the correct rule
                break;

              case CFunctionParameter::VOLUME:
                pObj = dynamic_cast<const CCompartment*>(CRootContainer::getKeyFactory()->get(*(it->begin())));

                if (pObj != NULL)
                  SubList[0] = pObj->getObjectName();

                break;

              case CFunctionParameter::TIME:
                pObj = dynamic_cast<const CModel*>(CRootContainer::getKeyFactory()->get(*(it->begin())));
                assert(pObj);
                SubList[0] = pObj->getObjectName();
                break;

              case CFunctionParameter::PARAMETER:
              {
                const CCopasiParameter * pParameter = rea.getParameters().getParameter(getParameterName(i));

                if (pParameter != NULL)
                  {
                    mValues[i] = pParameter->getValue< C_FLOAT64 >();
                  }
                else
                  {
                    mValues[i] = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
                  }

                mIsLocal[i] = rea.isLocalParameter(i);

                if (!mIsLocal[i])
                  {
                    pObj = dynamic_cast<const CModelValue*>(CRootContainer::getKeyFactory()->get(*(it->begin())));

                    if (pObj)
                      {
                        SubList[0] = pObj->getObjectName();
                        mValues[i] = pObj->getInitialValue();
                      }
                  }
              }
              break;

              default:
                break;
            }
        }

      mNameMap[i] = SubList;
    }

  return success;
}

bool CReactionInterface::writeBackToReaction(CReaction * rea, bool compile)
{
  bool success = true;

  //CReaction *rea;
  if (rea == NULL)
    rea = dynamic_cast< CReaction *>(CRootContainer::getKeyFactory()->get(mReactionReferenceKey));

  if (rea == NULL) return false;

  if (!isValid()) compile = false;

  if (mpFunction == NULL) return false;

  if (mpFunction->getObjectName() == "undefined") return false;

  if (mpParameters == NULL) return false;

  if (!(*mpParameters == mpFunction->getVariables())) return false; // do nothing

  // Now we can safely write to the equation as we are sure that only unique metabolites
  // may have the empty string as compartments
  mChemEqI.writeToChemEq(rea->getChemEq());

  // TODO. check if function has changed since it was set in the R.I.
  rea->setFunction(mpFunction->getObjectName());

  size_t j, jmax;
  size_t i, imax = size();
  std::pair< std::string, std::string > Names;

  for (i = 0; i < imax; ++i)
    {
      switch (getUsage(i))
        {
          case CFunctionParameter::PARAMETER:

            if (mIsLocal[i])
              rea->setParameterValue(getParameterName(i), mValues[i]);
            else
              {
                CModelValue & ModelValue = mpModel->getModelValues()[mNameMap[i][0]];

                rea->setParameterValue(getParameterName(i), mValues[i], false);
                rea->setParameterMapping(i, ModelValue.getKey());
              }

            break;

          case CFunctionParameter::VOLUME:
            if (mNameMap[i][0] == "unknown" || mNameMap[i][0] == "") break;

            rea->setParameterMapping(i, mpModel->getCompartments()[mNameMap[i][0]].getKey());
            break;

          case CFunctionParameter::TIME:
            rea->setParameterMapping(i, mpModel->getKey()); //time is the value of the model
            break;

          case CFunctionParameter::SUBSTRATE:
          case CFunctionParameter::PRODUCT:
          case CFunctionParameter::MODIFIER:

            if (isVector(i))
              {
                rea->clearParameterMapping(i);
                jmax = mNameMap[i].size();

                for (j = 0; j < jmax; ++j)
                  {
                    Names = CMetabNameInterface::splitDisplayName(mNameMap[i][j]);
                    rea->addParameterMapping(i, CMetabNameInterface::getMetaboliteKey(mpModel, Names.first, Names.second));
                  }
              }
            else
              {
                Names = CMetabNameInterface::splitDisplayName(mNameMap[i][0]);
                rea->setParameterMapping(i, CMetabNameInterface::getMetaboliteKey(mpModel, Names.first, Names.second));
              }

            break;

          default:
            break;
        }
    }

  rea->setHasNoise(mHasNoise);

  rea->setKineticLawUnitType(mKineticLawUnitType);

  std::string ScalingCompartmentCN;
  size_t Index;

  if (!mScalingCompartment.empty() &&
      (Index = mpModel->getCompartments().getIndex(mScalingCompartment)) != C_INVALID_INDEX)
    {
      ScalingCompartmentCN = mpModel->getCompartments()[Index].getCN();
    }

  rea->setScalingCompartmentCN(ScalingCompartmentCN);

  if (compile)
    {
      rea->setNoiseExpression(mNoiseExpression);
      rea->compile();
      mpModel->setCompileFlag(); //TODO: check if really necessary
    }

  return success;
}

void CReactionInterface::clearFunction()
{
  mpFunction = NULL;
  pdelete(mpParameters);
  //mValid = false;

  mValues.clear();
  mNameMap.clear();
}

void CReactionInterface::clearChemEquation()
{
  mChemEqI.clearAll();
  setFunctionWithEmptyMapping("");
}

void CReactionInterface::setChemEqString(const std::string & eq, const std::string & newFunction)
{
  mChemEqI.setChemEqString(eq);
  findAndSetFunction(newFunction);
}

std::string CReactionInterface::getChemEqString() const
{
  return mChemEqI.getChemEqString(false);
}

const CChemEqInterface &CReactionInterface::getChemEqInterface() const
{
  return mChemEqI;
}

bool CReactionInterface::isReversible() const
{
  return mChemEqI.getReversibility();
}

void CReactionInterface::setReversibility(bool rev, const std::string & newFunction)
{
  mChemEqI.setReversibility(rev);
  findAndSetFunction(newFunction);
}

void CReactionInterface::reverse(bool rev, const std::string & newFunction)
{
  mChemEqI.setReversibility(rev);
  mChemEqI.reverse();
  findAndSetFunction(newFunction);
}

void CReactionInterface::findAndSetFunction(const std::string & newFunction)
{
  std::vector<std::string> fl = getListOfPossibleFunctions();
  size_t i, imax = fl.size();

  //no valid function?
  if (imax == 0)
    {
      setFunctionAndDoMapping("");
      return;
    }

  //first try the function provided as argument
  if (newFunction != "")
    {
      for (i = 0; i < imax; ++i)
        if (fl[i] == newFunction)
          {
            setFunctionAndDoMapping(fl[i]);
            return;
          }
    }

  //next try if the current function works
  std::string currentFunctionName = getFunctionName();

  if ("" != currentFunctionName)
    {
      for (i = 0; i < imax; ++i)
        if (fl[i] == currentFunctionName)
          {
            setFunctionAndDoMapping(fl[i]);
            return;
          }
    }

  // if not found then see if there is a best match in the list (i.e. a corresponding rev/irrev function).
  //if there is a current function try to find a related new function
  std::string s;

  if (currentFunctionName != "")
    {
      s = currentFunctionName.substr(0, currentFunctionName.find('(') - 1);

      //'-1' so as to strip off the white space before '('
      //This is purely heuristics
      for (i = 0; i < imax; i++)
        {
          if (fl[i].find(s) != std::string::npos)    // if find succeeds, the return value is likely to be 0
            //if (fl[i].find(s) >= 0) - for some reason this doesn't work
            {
              setFunctionAndDoMapping(fl[i]);
              return;
            }
        }
    }

  //try mass action next
  s = "Mass action";

  for (i = 0; i < imax; i++)
    {
      if (fl[i].find(s) != std::string::npos)    // if find succeeds, the return value is likely to be 0
        //if (fl[i].find(s) >= 0) - for some reason this doesn't work
        {
          setFunctionAndDoMapping(fl[i]);
          return;
        }
    }

  //try constant flux next
  s = "Constant flux";

  for (i = 0; i < imax; i++)
    {
      if (fl[i].find(s) != std::string::npos)    // if find succeeds, the return value is likely to be 0
        //if (fl[i].find(s) >= 0) - for some reason this doesn't work
        {
          setFunctionAndDoMapping(fl[i]);

          // If we have a reaction of the type X + Y = and the function
          // is Constant flux (reversible) we need to set the parameter v to
          // be negative to avoid negative concentrations during time course simulations.
          // Note, this fix is only done when we are assigning a default rate law.
          if (mChemEqI.getReversibility() == true &&
              mChemEqI.getListOfDisplayNames(CFunctionParameter::PRODUCT).size() == 0)
            {
              C_FLOAT64 v = - fabs(getLocalValue(0));
              setLocalValue(0, v);
            }

          return;
        }
    }

  //if everything else fails just take the first function from the list
  //this should not be reached since constant flux is a valid kinetic function for every reaction
  setFunctionAndDoMapping(fl[0]);
}

void
CReactionInterface::connectFromScratch(CFunctionParameter::Role role)
{
  size_t i, imax = mpParameters->getNumberOfParametersByUsage(role);

  if (!imax) return;

  // get the list of chem eq elements
  std::vector<std::string> el = getExpandedMetabList(role);

  // get the first parameter with the respective role
  CFunctionParameter::DataType Type;
  size_t pos = 0;
  Type = mpParameters->getParameterByUsage(role, pos)->getType();

  if (Type == CFunctionParameter::VFLOAT64)
    {
      mNameMap[pos - 1] = el;
    }
  else if (Type == CFunctionParameter::FLOAT64)
    {
      if (el.size() > 0)
        mNameMap[pos - 1][0] = el[0];
      else
        {mNameMap[pos - 1][0] = "unknown"; /*mValid = false;*/}

      for (i = 1; i < imax; ++i)
        {
          Type = mpParameters->getParameterByUsage(role, pos)->getType();

          if (Type != CFunctionParameter::FLOAT64) fatalError();

          if (el.size() > i)
            mNameMap[pos - 1][0] = el[i];
          else
            {mNameMap[pos - 1][0] = "unknown"; /*mValid = false;*/}
        }
    }
  else fatalError();
}

bool
CReactionInterface::isLocked(size_t index) const
{
  return isLocked(getUsage(index));
}

bool
CReactionInterface::isLocked(CFunctionParameter::Role usage) const
{
  switch (usage)
    {
      case CFunctionParameter::MODIFIER:
        return false;
        break;

      case CFunctionParameter::TIME:
        return true;
        break;

      case CFunctionParameter::SUBSTRATE:
      case CFunctionParameter::PRODUCT:
      {
        // get number of parameters
        size_t paramSize = mpParameters->getNumberOfParametersByUsage(usage);

        if (paramSize == 0)
          return true;

        // get index of first parameter
        size_t pos = 0;
        mpParameters->getParameterByUsage(usage, pos); --pos;

        if (isVector(pos))
          {
            assert(paramSize == 1);
            return true;
          }
        else
          {
            return (mChemEqI.getListOfDisplayNames(usage).size() == 1);
          }
      }
      break;

      case CFunctionParameter::PARAMETER:
        return mpModel->getModelValues().size() <= 1;
        break;

      case CFunctionParameter::VOLUME:
        return mpModel->getCompartments().size() <= 1;
        break;

      default:
        break;
    }

  return false;
}

std::set< const CDataObject * >
CReactionInterface::getDeletedParameters() const
{
  std::set< const CDataObject * > ToBeDeleted;

  // We need to compare the current visible local parameter with the one stored
  // in the reaction.
  const CReaction * pReaction
    = dynamic_cast< CReaction *>(CRootContainer::getKeyFactory()->get(mReactionReferenceKey));

  if (pReaction == NULL)
    return ToBeDeleted;

  if (pReaction->getFunction() == NULL)
    return ToBeDeleted;

  const CFunctionParameters & OriginalParameters
    = pReaction->getFunction()->getVariables();

  size_t j, jmax = size();
  size_t i, imax = OriginalParameters.size();
  const CFunctionParameter * pParameter;

  for (i = 0; i < imax; ++i)
    {
      pParameter = OriginalParameters[i];

      if (pParameter->getUsage() == CFunctionParameter::PARAMETER &&
          pReaction->isLocalParameter(i))
        {
          const std::string & Name = pParameter->getObjectName();

          //find parameter with same name in current parameters
          for (j = 0; j < jmax; ++j)
            if (Name == getParameterName(j)) break;

          if (j < jmax && mIsLocal[j])
            continue;

          // The old parameter is either not found or is no longer local, i.e., it needs to
          // be added to values to be deleted.
          ToBeDeleted.insert(pReaction->getParameters().getParameter(Name));
        }
    }

  return ToBeDeleted;
}

void
CReactionInterface::initMapping()
{
  mpParameters = new CFunctionParameters(mpFunction->getVariables(), NO_PARENT);
  //make sure mpParameters is deleted! (e.g. in copyMapping())
  mNameMap.resize(size());
  mValues.resize(size());
  mIsLocal.resize(size());

  size_t i, imax = size();

  for (i = 0; i < imax; ++i)
    {
      if (isVector(i))
        mNameMap[i].resize(0);
      else
        {
          mNameMap[i].resize(1);
          mNameMap[i][0] = "unknown";
        }

      if (getUsage(i) == CFunctionParameter::PARAMETER)
        mIsLocal[i] = true;
      else
        mIsLocal[i] = false;

      mValues[i] = 0.1;
    }
}

void
CReactionInterface::copyMapping()
{
  if (!mpParameters) //nothing to copy
    {
      initMapping();
      return;
    }

  // save the old information
  CFunctionParameters *oldParameters = mpParameters;
  std::vector<std::vector<std::string> > oldMap = mNameMap;
  std::vector<C_FLOAT64> oldValues = mValues;
  std::vector<bool> oldIsLocal = mIsLocal;

  //create new mapping
  initMapping();

  //try to preserve as much information from the old mapping as possible
  size_t j, jmax = oldParameters->size();
  size_t i, imax = size();

  for (i = 0; i < imax; ++i)
    {
      //find parameter with same name in old parameters
      for (j = 0; j < jmax; ++j)
        if ((*oldParameters)[j]->getObjectName() == getParameterName(i)) break;

      if (j == jmax) continue;

      //see if usage matches
      if (getUsage(i) != (*oldParameters)[j]->getUsage()) continue;

      //see if vector property matches
      if (isVector(i) != ((*oldParameters)[j]->getType() == CFunctionParameter::VFLOAT64))
        continue;

      mIsLocal[i] = oldIsLocal[j];
      mValues[i] = oldValues[j];

      switch (getUsage(i))
        {
          case CFunctionParameter::SUBSTRATE:
          case CFunctionParameter::PRODUCT:
            //TODO: check with chemeq
            mNameMap[i] = oldMap[j];
            break;

          case CFunctionParameter::MODIFIER:
            //TODO: check existence?
            mNameMap[i] = oldMap[j];
            //TODO: add to chemeq
            break;

          case CFunctionParameter::PARAMETER:
          case CFunctionParameter::VOLUME:
          case CFunctionParameter::TIME:
            //TODO: check existence?
            mNameMap[i] = oldMap[j];
            break;

          default:
            break;
        }
    }

  pdelete(oldParameters);
}

void
CReactionInterface::connectNonMetabolites()
{
  size_t i, imax = size();

  for (i = 0; i < imax; ++i)
    {
      //only do something if the current mapping is "unknown"
      if (mNameMap[i].size())
        if (mNameMap[i][0] != "unknown")
          continue;

      if (isLocalValue(i))
        continue;

      switch (getUsage(i))
        {
          case CFunctionParameter::SUBSTRATE:
          case CFunctionParameter::PRODUCT:
          case CFunctionParameter::MODIFIER:
            break;

          case CFunctionParameter::PARAMETER:

            if (mpModel->getModelValues().size() == 1)
              mNameMap[i][0] = mpModel->getModelValues()[0].getObjectName();

            break;

          case CFunctionParameter::VOLUME:
            //if (mpModel->getCompartments().size()==1)
            //  mNameMap[i][0] = mpModel->getCompartments()[0]->getObjectName();
          {
            const CCompartment* comp = mChemEqI.getCompartment();

            if (comp)
              mNameMap[i][0] = comp->getObjectName();
          }
          break;

          case CFunctionParameter::TIME:
            mNameMap[i][0] = mpModel->getObjectName();
            break;

          default:
            break;
        }
    }
}

void
CReactionInterface::setFunctionWithEmptyMapping(const std::string & fn)
{
  if ((fn == "") || (fn == "undefined"))
    {clearFunction(); return;}

  //get the function
  mpFunction = dynamic_cast<CFunction *>
               (CRootContainer::getFunctionList()->findLoadFunction(fn));

  if (!mpFunction) fatalError();

  pdelete(mpParameters);
  initMapping(); //empty mapping
}

void
CReactionInterface::setFunctionAndDoMapping(const std::string & fn)
{
  if ((fn == "") || (fn == "undefined"))
    {clearFunction(); return;}

  //get the function
  mpFunction = dynamic_cast<CFunction *>
               (CRootContainer::getFunctionList()->findLoadFunction(fn));

  if (!mpFunction)
    {
      mpFunction = CRootContainer::getUndefinedFunction();
    }

  copyMapping();
  connectNonMetabolites();

  //guess initial connections between metabs and function parameters
  connectFromScratch(CFunctionParameter::SUBSTRATE);
  connectFromScratch(CFunctionParameter::PRODUCT);
  connectFromScratch(CFunctionParameter::MODIFIER); // we can not be pedantic about modifiers
  // because modifiers are not taken into acount
  // when looking for suitable functions
}

const std::string &
CReactionInterface::getFunctionName() const
{
  if (mpFunction)
    return mpFunction->getObjectName();

  return emptyString;
}

const std::string &
CReactionInterface::getFunctionDescription() const
{
  if (mpFunction)
    return mpFunction->getInfix();

  return emptyString;
}

const CFunction &
CReactionInterface::getFunction() const
{
  if (mpFunction == NULL)
    {
      return *CRootContainer::getUndefinedFunction();
    }

  if (mpFunction->getType() != CEvaluationTree::Type::MassAction)
    {
      return *mpFunction;
    }

  mMassAction.setObjectName(mpFunction->getObjectName());

  std::stringstream Infix;
  Infix << "k1";

  for (size_t i = 0; i < mChemEqI.getMolecularity(CFunctionParameter::SUBSTRATE); ++i)
    {
      Infix << "*S" << i;
    }

  if (mpFunction->isReversible() == TriTrue)
    {
      Infix << "-k2";

      for (size_t i = 0; i < mChemEqI.getMolecularity(CFunctionParameter::PRODUCT); ++i)
        {
          Infix << "*P" << i;
        }
    }

  mMassAction.setInfix(Infix.str());

  return mMassAction;
}

void
CReactionInterface::updateModifiersInChemEq()
{
  mChemEqI.clearModifiers();
  size_t j, jmax = size();

  for (j = 0; j < jmax; ++j)
    if (getUsage(j) == CFunctionParameter::MODIFIER) //all the modifiers in the table
      if (getMapping(j) != "unknown")
        mChemEqI.addModifier(getMapping(j));
}

void
CReactionInterface::setMapping(size_t index, std::string mn)
{
  if (mIsLocal.size() <= index) return;

  mIsLocal[index] = false;

  switch (getUsage(index))
    {
      case CFunctionParameter::VOLUME:
      case CFunctionParameter::PARAMETER:
      case CFunctionParameter::TIME:
        assert(!isVector(index));
        mNameMap[index][0] = mn;
        break;

      case CFunctionParameter::SUBSTRATE:
      case CFunctionParameter::PRODUCT:

        if (isVector(index))
          mNameMap[index].push_back(mn);
        else
          {
            mNameMap[index][0] = mn;

            //TODO: check the following
            // if we have two parameters of this usage change the other one.
            size_t listSize = mChemEqI.getListOfDisplayNames(getUsage(index)).size();

            if ((listSize == 2) && (mpParameters->getNumberOfParametersByUsage(getUsage(index)) == 2))
              {
                // get index of other parameter
                size_t pos = 0;
                mpParameters->getParameterByUsage(getUsage(index), pos);

                if ((pos - 1) == index) mpParameters->getParameterByUsage(getUsage(index), pos);

                --pos;

                // get name if other metab
                std::vector<std::string> ml = getListOfMetabs(getUsage(index));
                std::string otherMetab;

                if (ml[0] == mn) otherMetab = ml[1]; else otherMetab = ml[0];

                // set other parameter
                mNameMap[pos][0] = otherMetab;
              }
          }

        break;

      case CFunctionParameter::MODIFIER:
        assert(!isVector(index));
        mNameMap[index][0] = mn;
        updateModifiersInChemEq();
        break;

      default:
        break;
    }
}

const std::vector<std::string> &
CReactionInterface::getMappings(size_t index) const
{
  return mNameMap[index];
}

const std::string &
CReactionInterface::getMapping(size_t index) const
{
  return mNameMap[index][0];
}

std::vector< std::string > CReactionInterface::getUnitVector(size_t index) const
{
  std::vector< std::string > Units;

  switch (getUsage(index))
    {
      case CFunctionParameter::SUBSTRATE:
      case CFunctionParameter::PRODUCT:
      case CFunctionParameter::MODIFIER:
      {
        std::vector< std::string >::const_iterator it = mNameMap[index].begin();
        std::vector< std::string >::const_iterator end = mNameMap[index].end();

        for (; it != end; ++it)
          {

            const CMetab* mpMetab = dynamic_cast<const CMetab*>(mpModel->getObjectDataModel()->findObjectByDisplayName(*it));

            if (mpMetab != NULL)
              {
                Units.push_back(CUnit::prettyPrint(mpMetab->getConcentrationReference()->getUnits()));
              }
            else
              {

                std::pair< std::string, std::string > Names = CMetabNameInterface::splitDisplayName(*it);
                size_t Index = mpModel->getCompartments().getIndex(Names.second);

                if (Index != C_INVALID_INDEX)
                  {
                    Units.push_back(mpModel->getQuantityUnit() + "/(" + mpModel->getCompartments()[Index].getUnits() + ")");
                  }
                else
                  {
                    Units.push_back(mpModel->getQuantityUnit() + "/(" + mpModel->getVolumeUnit() + ")");
                  }
              }
          }
      }
      break;

      case CFunctionParameter::PARAMETER:
      case CFunctionParameter::VARIABLE:
      case CFunctionParameter::TEMPORARY:
      case CFunctionParameter::VOLUME:
      case CFunctionParameter::TIME:
        break;
    }

  return Units;
}

std::string CReactionInterface::getUnit(size_t index) const
{
  assert(!isVector(index));

  switch (getUsage(index))
    {
      case CFunctionParameter::SUBSTRATE:
      case CFunctionParameter::PRODUCT:
      case CFunctionParameter::MODIFIER:
      {
        // first try to find the species and return its concentration units
        const CMetab* mpMetab = dynamic_cast<const CMetab*>(mpModel->getObjectDataModel()->findObjectByDisplayName(mNameMap[index][0]));

        if (mpMetab != NULL)
          return CUnit::prettyPrint(mpMetab->getConcentrationReference()->getUnits());

        // if not found use the old code
        std::pair< std::string, std::string > Names = CMetabNameInterface::splitDisplayName(mNameMap[index][0]);
        size_t Index = mpModel->getCompartments().getIndex(Names.second); // will fail for empty string

        if (Index != C_INVALID_INDEX)
          {
            return mpModel->getQuantityUnit() + "/(" + mpModel->getCompartments()[Index].getUnits() + ")";
          }
        else
          {
            return mpModel->getQuantityUnit() + "/(" + mpModel->getVolumeUnit() + ")";
          }
      }
      break;

      case CFunctionParameter::PARAMETER:

        if (isLocalValue(index))
          {
            return "?";
          }
        else
          {
            size_t Index = mpModel->getModelValues().getIndex(mNameMap[index][0]);

            if (Index != C_INVALID_INDEX)
              {
                return mpModel->getModelValues()[Index].getUnits();
              }
            else
              {
                return "?";
              }
          }

        break;

      case CFunctionParameter::VARIABLE:
      case CFunctionParameter::TEMPORARY:
        return "?";

      case CFunctionParameter::VOLUME:
      {
        size_t Index = mpModel->getCompartments().getIndex(mNameMap[index][0]);

        if (Index != C_INVALID_INDEX)
          {
            return mpModel->getCompartments()[Index].getUnits();
          }
        else
          {
            return mpModel->getVolumeUnit();
          }
      }
      break;

      case CFunctionParameter::TIME:
        return mpModel->getUnits();
        break;
    }

  return "?";
}

void
CReactionInterface::setLocalValue(size_t index, C_FLOAT64 value)
{
  if (index >= mValues.size() || index >= mIsLocal.size())
    return;

  mValues[index] = value;
  mIsLocal[index] = true;
}

void
CReactionInterface::setLocal(size_t index)
{
  if (index >= mIsLocal.size())
    return;

  mIsLocal[index] = true;
}

const double &
CReactionInterface::getLocalValue(size_t index) const
{
  if (index >= mValues.size())
    {
      static double invalidValue = std::numeric_limits<double>::quiet_NaN();
      return invalidValue;
    }

  return mValues[index];
}

bool
CReactionInterface::isLocalValue(size_t index) const
{
  if (index >= mIsLocal.size())
    return false;

  return mIsLocal[index];
}

std::vector<std::string>
CReactionInterface::getExpandedMetabList(CFunctionParameter::Role role) const
{
  const std::vector<std::string> & names = mChemEqI.getListOfDisplayNames(role);
  const std::vector<C_FLOAT64> & mults = mChemEqI.getListOfMultiplicities(role);

  size_t j, jmax;
  size_t i, imax = names.size();

  std::vector<std::string> ret;

  for (i = 0; i < imax; ++i)
    {
      if (role == CFunctionParameter::MODIFIER)
        {
          jmax = 1;
        }
      else
        {
          C_FLOAT64 Multiplicity = mults[i];

          if (Multiplicity == floor(Multiplicity + 0.5))
            {
              jmax = (size_t) Multiplicity;
            }
          else
            {
              jmax = 1;
            }
        }

      for (j = 0; j < jmax; ++j)
        {
          ret.push_back(names[i]);
        }
    }

  return ret;
}

bool
CReactionInterface::createMetabolites()
{
  std::vector<std::string> createdMetabolites;
  return createMetabolites(createdMetabolites);
}

bool
CReactionInterface::createMetabolites(
  std::vector<std::string> &createdMetabolites)
{
  bool created = mChemEqI.createNonExistingMetabs(createdMetabolites);

  // Update the parameter mapping to assure that the new names match.
  if (created)
    setFunctionAndDoMapping(getFunctionName());

  return created;
}

bool
CReactionInterface::createOtherObjects() const
{
  std::vector<std::string> keys;
  return createOtherObjects(keys);
}

bool
CReactionInterface::createOtherObjects(std::vector<std::string> &createdKeys) const
{
  bool ret = false;

  size_t i, imax = size();

  for (i = 0; i < imax; ++i)
    {
      switch (getUsage(i))
        {
          case CFunctionParameter::VOLUME:
          {
            if (mNameMap[i][0] == "unknown" || mNameMap[i][0] == "") break;

            CCompartment *comp = mpModel->createCompartment(mNameMap[i][0], 1.0);

            if (comp != NULL)
              {
                createdKeys.insert(createdKeys.begin(), comp->getKey());
                ret = true;
              }

            break;
          }

          case CFunctionParameter::PARAMETER:

            if (mNameMap[i][0] == "unknown" || mNameMap[i][0] == "") break;

            if (!isLocalValue(i))
              {
                CModelValue* param = mpModel->createModelValue(mNameMap[i][0], 1.0);

                if (param != NULL)
                  {
                    createdKeys.insert(createdKeys.begin(), param->getKey());
                    ret = true;
                  }
              }

            break;

          default:
            break;
        }
    }

  return ret;
}

bool
CReactionInterface::isMulticompartment() const
{
  return mChemEqI.isMulticompartment();
}

bool
CReactionInterface::isValid() const
{
  //A reaction is invalid if it has a metab, a global parameter, or a compartment "unknown"
  size_t j, jmax = size();

  for (j = 0; j < jmax; ++j)
    if ((mNameMap[j].size() == 0 ||  mNameMap[j][0] == "unknown" ||  mNameMap[j][0] == "") && (!mIsLocal[j]))
      return false;

  return true;
}

void CReactionInterface::setHasNoise(const bool & hasNoise)
{
  mHasNoise = hasNoise;

  if (!mHasNoise || !mNoiseExpression.empty()) return;

  const CReaction * pReaction = dynamic_cast< CReaction *>(CRootContainer::getKeyFactory()->get(mReactionReferenceKey));

  if (pReaction == NULL) return;

  mNoiseExpression = pReaction->getDefaultNoiseExpression();
}

const bool & CReactionInterface::hasNoise() const
{
  return mHasNoise;
}

bool CReactionInterface::setNoiseExpression(const std::string & expression)
{
  mNoiseExpression = expression;
  return true;
}

const std::string & CReactionInterface::getNoiseExpression() const
{
  return mNoiseExpression;
}

void CReactionInterface::setKineticLawUnitType(const CReaction::KineticLawUnit & kineticLawUnitType)
{
  mKineticLawUnitType = kineticLawUnitType;
}

const CReaction::KineticLawUnit & CReactionInterface::getKineticLawUnitType() const
{
  return mKineticLawUnitType;
}

CReaction::KineticLawUnit CReactionInterface::getEffectiveKineticLawUnitType() const
{
  CReaction::KineticLawUnit EffectiveUnit = mKineticLawUnitType;

  if (EffectiveUnit == CReaction::Default)
    {
      if (isMulticompartment())
        {
          EffectiveUnit = CReaction::AmountPerTime;
        }
      else
        {
          EffectiveUnit = CReaction::ConcentrationPerTime;
        }
    }

  return EffectiveUnit;
}

std::string CReactionInterface::getConcentrationRateUnit() const
{
  size_t Index = mpModel->getCompartments().getIndex(getDefaultScalingCompartment());

  if (Index == C_INVALID_INDEX)
    {
      return mpModel->getQuantityUnit() + "/(" + mpModel->getVolumeUnit() + "*" + mpModel->getTimeUnit() + ")";
    }

  CCompartment & Compartment = mpModel->getCompartments()[Index];

  return mpModel->getQuantityUnit() + "/(" + Compartment.getUnits() + "*" + mpModel->getTimeUnit() + ")";
}

std::string CReactionInterface::getAmountRateUnit() const
{
  return mpModel->getQuantityUnit() + "/(" + mpModel->getTimeUnit() + ")";
}

std::string CReactionInterface::getEffectiveKineticLawUnit() const
{
  switch (getEffectiveKineticLawUnitType())
    {
      case CReaction::AmountPerTime:
        return getAmountRateUnit();
        break;

      case CReaction::ConcentrationPerTime:
        return getConcentrationRateUnit();
        break;
    }

  return "";
}

void CReactionInterface::setScalingCompartment(const std::string & scalingCompartment)
{
  mScalingCompartment = scalingCompartment;
}

const std::string & CReactionInterface::getScalingCompartment() const
{
  return mScalingCompartment;
}

std::string CReactionInterface::getDefaultScalingCompartment() const
{
  if (!mScalingCompartment.empty() &&
      mKineticLawUnitType != CReaction::Default) return mScalingCompartment;

  return mChemEqI.getDefaultCompartment();
}

#ifdef COPASI_DEBUG
void
CReactionInterface::printDebug() const
{
  std::cout << "Reaction interface   " << std::endl;
  std::cout << "  Function: " << getFunctionName() << std::endl;
  std::cout << "  ChemEq:   " << getChemEqString() << std::endl;

  size_t i, imax = size();

  for (i = 0; i < imax; ++i)
    {
      std::cout << "    ---  " << i << ": " << getParameterName(i)
                << ", vector: " << isVector(i) << " local: " << isLocalValue(i)
                << ", value: " << mValues[i] << std::endl;

      size_t j, jmax = mNameMap[i].size();

      for (j = 0; j < jmax; ++j)
        std::cout << "            " << mNameMap[i][j] << std::endl;
    }

  std::cout << std::endl;
}
#endif // COPASI_DEBUG
