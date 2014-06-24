// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

// CReaction
//
// Derived from Gepasi's cstep.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for COPASI by Stefan Hoops

#include "copasi.h"

#include <algorithm>
#include <stdio.h>

#include "CopasiDataModel/CCopasiDataModel.h"
#include "CReaction.h"
#include "CCompartment.h"
#include "CModel.h"
#include "utilities/CReadConfig.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CCopasiException.h"
#include "utilities/CNodeIterator.h"
#include "utilities/utility.h"
#include "function/CFunctionDB.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "CMetabNameInterface.h"
#include "CChemEqInterface.h" //only for load()
#include "CChemEqElement.h"
#include "function/CExpression.h"
#include "report/CCopasiRootContainer.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Compartment.h"
#include "sbml/SBMLImporter.h"

C_FLOAT64 CReaction::mDefaultScalingFactor = 1.0;

CReaction::CReaction(const std::string & name,
                     const CCopasiContainer * pParent):
  CCopasiContainer(name, pParent, "Reaction"),
  CAnnotation(),
  mChemEq("Chemical Equation", this),
  mpFunction(NULL),
  mFlux(0),
  mpFluxReference(NULL),
  mParticleFlux(0),
  mpParticleFluxReference(NULL),
  mPropensity(0),
  mpPropensityReference(NULL),
  mScalingFactor(&mDefaultScalingFactor),
  mUnitScalingFactor(&mDefaultScalingFactor),
  mMetabKeyMap(),
  mParameters("Parameters", this),
  mFast(false)
{
  mKey = CCopasiRootContainer::getKeyFactory()->add(getObjectType(), this);

  CONSTRUCTOR_TRACE;
  initObjects();
  setFunction(CCopasiRootContainer::getUndefinedFunction());
}

CReaction::CReaction(const CReaction & src,
                     const CCopasiContainer * pParent):
  CCopasiContainer(src, pParent),
  CAnnotation(src),
  mChemEq(src.mChemEq, this),
  mpFunction(src.mpFunction),
  mFlux(src.mFlux),
  mpFluxReference(NULL),
  mParticleFlux(src.mParticleFlux),
  mpParticleFluxReference(NULL),
  mPropensity(src.mPropensity),
  mpPropensityReference(NULL),
  mScalingFactor(src.mScalingFactor),
  mUnitScalingFactor(src.mUnitScalingFactor),
  mMap(src.mMap),
  mMetabKeyMap(src.mMetabKeyMap),
  mParameters(src.mParameters, this),
  mFast(src.mFast)
{
  mKey = CCopasiRootContainer::getKeyFactory()->add(getObjectType(), this);

  CONSTRUCTOR_TRACE;
  initObjects();

  if (mpFunction)
    {
      //compileParameters();
    }

  setMiriamAnnotation(src.getMiriamAnnotation(), mKey, src.mKey);
}

CReaction::~CReaction()
{
  CCopasiRootContainer::getKeyFactory()->remove(mKey);
  cleanup();
  DESTRUCTOR_TRACE;
}

// virtual
std::string CReaction::getChildObjectUnits(const CCopasiObject * pObject) const
{
  const CModel * pModel =
    dynamic_cast< const CModel * >(getObjectAncestor("Model"));

  if (pModel == NULL) return "";

  const std::string & Name = pObject->getObjectName();

  if (Name == "ParticleFlux")
    return pModel->getFrequencyUnitsDisplayString();
  else if (Name == "Flux")
    return pModel->getQuantityRateUnitsDisplayString();
  else if (Name == "Propensity")
    return pModel->getFrequencyUnitsDisplayString();

  return "";
}

void CReaction::cleanup()
{
  // TODO: mMap.cleanup();
  //mParameterDescription.cleanup();
}

bool CReaction::setObjectParent(const CCopasiContainer * pParent)
{
  bool success = CCopasiContainer::setObjectParent(pParent);

  return success;
}

C_INT32 CReaction::load(CReadConfig & configbuffer)
{
  C_INT32 Fail = 0;

  std::string tmp;

  if ((Fail = configbuffer.getVariable("Step", "string", &tmp,
                                       CReadConfig::SEARCH)))
    return Fail;

  setObjectName(tmp);

  std::string ChemEq;

  if ((Fail = configbuffer.getVariable("Equation", "string", &ChemEq)))
    return Fail;

  CModel * pModel
    = dynamic_cast< CModel * >(getObjectAncestor("Model"));
  CChemEqInterface::setChemEqFromString(pModel, *this, ChemEq);

  if ((Fail = configbuffer.getVariable("KineticType", "string", &tmp)))
    return Fail;

  setFunction(tmp);

  if (mpFunction == NULL)
    return Fail = 1;

  bool revers;

  if ((Fail = configbuffer.getVariable("Reversible", "bool", &revers,
                                       CReadConfig::SEARCH)))
    return Fail;

  mChemEq.setReversibility(revers); // TODO: this should be consistent with the ChemEq string

  Fail = loadOld(configbuffer);

  return Fail;
}

const std::string & CReaction::getKey() const {return CAnnotation::getKey();}

const C_FLOAT64 & CReaction::getFlux() const
{return mFlux;}

const CCopasiObject * CReaction::getFluxReference() const
{return this->mpFluxReference;}

CCopasiObject * CReaction::getFluxReference()
{return this->mpFluxReference;}

const C_FLOAT64 & CReaction::getParticleFlux() const
{return mParticleFlux;}

const CCopasiObject * CReaction::getParticleFluxReference() const
{return mpParticleFluxReference;}

CCopasiObject * CReaction::getParticleFluxReference()
{return mpParticleFluxReference;}

CCopasiObject * CReaction::getPropensityReference()
{return mpPropensityReference;}

const CCopasiObject * CReaction::getPropensityReference() const
{return mpPropensityReference;}

const CCallParameters< C_FLOAT64 > & CReaction::getCallParameters() const
{
  return mMap.getPointers();
}

//****************************************

const CChemEq & CReaction::getChemEq() const
{return mChemEq;}

CChemEq & CReaction::getChemEq()
{return mChemEq;}

bool CReaction::isReversible() const
{return mChemEq.getReversibility();}

bool CReaction::addSubstrate(const std::string & metabKey,
                             const C_FLOAT64 & multiplicity)
{return mChemEq.addMetabolite(metabKey, multiplicity, CChemEq::SUBSTRATE);}

bool CReaction::addProduct(const std::string & metabKey,
                           const C_FLOAT64 & multiplicity)
{return mChemEq.addMetabolite(metabKey, multiplicity, CChemEq::PRODUCT);}

bool CReaction::addModifier(const std::string & metabKey,
                            const C_FLOAT64 & multiplicity)
{return mChemEq.addMetabolite(metabKey, multiplicity, CChemEq::MODIFIER);}

//bool CReaction::deleteModifier(const std::string &name)
//{return false;} /* :TODO: this needs to be implemented on CChemEq first. */

void CReaction::setReversible(bool reversible)
{mChemEq.setReversibility(reversible);}

//****************************************

const CFunction * CReaction::getFunction() const
{return mpFunction;}

bool CReaction::setFunction(const std::string & functionName)
{
  CFunction * pFunction =
    dynamic_cast<CFunction *>(CCopasiRootContainer::getFunctionList()->findLoadFunction(functionName));

  if (!pFunction)
    CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 1, functionName.c_str());

  return setFunction(pFunction);
}

bool CReaction::setFunction(CFunction * pFunction)
{
  removeDirectDependency(mpFunction);

  if (!pFunction)
    mpFunction = CCopasiRootContainer::getUndefinedFunction();
  else
    mpFunction = pFunction;

  addDirectDependency(mpFunction);

  mMap.initializeFromFunctionParameters(mpFunction->getVariables());
  initializeMetaboliteKeyMap(); //needs to be called before initializeParamters();
  initializeParameters();

  return true;
}

//****************************************

// TODO: check if function is set and map initialized in the following methods
/**
 * Retrieve the index of the given parameter name in the function call
 * @param const std::string & parameterName
 * @return size_t index;
 */
size_t CReaction::getParameterIndex(const std::string & parameterName, CFunctionParameter::DataType * pType) const
{
  if (pType != NULL)
    {
      return mMap.findParameterByName(parameterName, *pType);
    }

  CFunctionParameter::DataType Type;
  return mMap.findParameterByName(parameterName, Type);
}

void CReaction::setParameterValue(const std::string & parameterName,
                                  const C_FLOAT64 & value,
                                  const bool & updateStatus)
{
  if (!mpFunction) fatalError();

  mParameters.setValue(parameterName, value);

  if (!updateStatus) return;

  //make sure that this local parameter is actually used:

  //first find index
  size_t index = getParameterIndex(parameterName);

  if (index == C_INVALID_INDEX) return;

  if (getFunctionParameters()[index]->getType() != CFunctionParameter::FLOAT64) fatalError(); //wrong data type

  //set the key map
  mMetabKeyMap[index][0] = mParameters.getParameter(parameterName)->getKey();
}

const C_FLOAT64 & CReaction::getParameterValue(const std::string & parameterName) const
{
  if (!mpFunction) fatalError();

  return * mParameters.getValue(parameterName).pDOUBLE;
}

const CCopasiParameterGroup & CReaction::getParameters() const
{return mParameters;}

CCopasiParameterGroup & CReaction::getParameters()
{return mParameters;}

void CReaction::setParameterMapping(const size_t & index, const std::string & key)
{
  if (!mpFunction) fatalError();

  if (getFunctionParameters()[index]->getType() != CFunctionParameter::FLOAT64) fatalError(); //wrong data type

  mMetabKeyMap[index][0] = key;
}

void CReaction::addParameterMapping(const size_t & index, const std::string & key)
{
  if (!mpFunction) fatalError();

  if (getFunctionParameters()[index]->getType() != CFunctionParameter::VFLOAT64) fatalError(); //wrong data type

  mMetabKeyMap[index].push_back(key);
}

bool CReaction::setParameterMapping(const std::string & parameterName, const std::string & key)
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  size_t index = getParameterIndex(parameterName, &type);

  if (C_INVALID_INDEX == index)
    return false;

  if (type != CFunctionParameter::FLOAT64) fatalError();

  mMetabKeyMap[index][0] = key;

  return true;
}

void CReaction::addParameterMapping(const std::string & parameterName, const std::string & key)
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  size_t index;
  index = getParameterIndex(parameterName, &type);

  if (C_INVALID_INDEX == index)
    return;

  if (type != CFunctionParameter::VFLOAT64) fatalError();

  mMetabKeyMap[index].push_back(key);
}

void CReaction::setParameterMappingVector(const std::string & parameterName,
    const std::vector<std::string> & keys)
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  size_t index;
  index = getParameterIndex(parameterName, &type);

  if (C_INVALID_INDEX == index)
    return;

  if ((type == CFunctionParameter::FLOAT64) && (keys.size() != 1)) fatalError();

  mMetabKeyMap[index] = keys;
}

void CReaction::clearParameterMapping(const std::string & parameterName)
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  size_t index;
  index = getParameterIndex(parameterName, &type);

  if (C_INVALID_INDEX == index)
    return;

  if (type != CFunctionParameter::VFLOAT64) fatalError(); //wrong data type

  mMetabKeyMap[index].clear();
}

void CReaction::clearParameterMapping(const size_t & index)
{
  if (!mpFunction) fatalError();

  if (getFunctionParameters()[index]->getType() != CFunctionParameter::VFLOAT64) fatalError();

  mMetabKeyMap[index].clear();
}

const std::vector<std::string> & CReaction::getParameterMapping(const size_t & index) const
{
  if (!mpFunction) fatalError();

  if (C_INVALID_INDEX == index || index >= mMetabKeyMap.size())
    return mMetabKeyMap[0]; //TODO this is kind of ugly!

  return mMetabKeyMap[index];
}

const std::vector<std::string> & CReaction::getParameterMapping(const std::string & parameterName) const
{
  size_t index = getParameterIndex(parameterName);

  return getParameterMapping(index);
}

bool CReaction::isLocalParameter(const size_t & index) const
{
  size_t i, imax = mParameters.size();

  for (i = 0; i < imax; ++i)
    {
      if (mParameters.getParameter(i)->getKey() == mMetabKeyMap[index][0])
        return true;
    }

  return false;
}

bool CReaction::isLocalParameter(const std::string & parameterName) const
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  size_t index = getParameterIndex(parameterName, &type);

  if (C_INVALID_INDEX == index)
    return false;

  if (type != CFunctionParameter::FLOAT64) fatalError();

  return isLocalParameter(index);
}
//***********************************************************************************************

// virtual
const CObjectInterface * CReaction::getObject(const CCopasiObjectName & cn) const
{
  const CCopasiObject * pObject =
    static_cast< const CCopasiObject * >(CCopasiContainer::getObject(cn));

  if (pObject == NULL ||
      pObject->isStaticString()) return pObject;

  const CCopasiContainer * pParent = pObject->getObjectParent();

  while (pParent != this)
    {
      if (pParent->getObjectParent() == &mParameters)
        {
          if (isLocalParameter(pParent->getObjectName()))
            {
              return pObject;
            }
          else
            {
              return NULL;
            }
        }

      pParent = pParent->getObjectParent();
    }

  return pObject;
}

void CReaction::initializeParameters()
{
  if (!mpFunction) fatalError();

  size_t i;
  size_t imax = mMap.getFunctionParameters().getNumberOfParametersByUsage(CFunctionParameter::PARAMETER);
  size_t pos;
  std::string name;

  /* We have to be more intelligent here because during an XML load we have
     already the correct parameters */

  /* Add missing parameters with default value 1.0. */
  for (i = 0, pos = 0; i < imax; ++i)
    {
      name = mMap.getFunctionParameters().getParameterByUsage(CFunctionParameter::PARAMETER, pos)->getObjectName();

      //      param.setName(name);
      if (!mParameters.getParameter(name))
        {
          mParameters.addParameter(name,
                                   CCopasiParameter::DOUBLE,
                                   (C_FLOAT64) 1.0);
        }

      CCopasiParameter * tmpPar = mParameters.getParameter(name);
      mMetabKeyMap[pos - 1][0] = tmpPar->getKey();
    }

  /* Remove parameters not fitting current function */
  CCopasiParameterGroup::index_iterator it = mParameters.beginIndex();
  CCopasiParameterGroup::index_iterator end = mParameters.endIndex();
  std::vector< std::string > ToBeDeleted;

  for (; it != end; ++it)
    {
      name = (*it)->getObjectName();

      if (getParameterIndex(name) == C_INVALID_INDEX)
        ToBeDeleted.push_back(name);
    }

  std::vector< std::string >::const_iterator itToBeDeleted = ToBeDeleted.begin();
  std::vector< std::string >::const_iterator endToBeDeleted = ToBeDeleted.end();

  for (; itToBeDeleted != endToBeDeleted; ++itToBeDeleted)
    mParameters.removeParameter(*itToBeDeleted);
}

void CReaction::initializeMetaboliteKeyMap()
{
  if (!mpFunction) fatalError();

  size_t i;
  size_t imax = mMap.getFunctionParameters().size();

  mMetabKeyMap.resize(imax);

  for (i = 0; i < imax; ++i)
    {
      if (mMap.getFunctionParameters()[i]->getType() >= CFunctionParameter::VINT32)
        mMetabKeyMap[i].resize(0);
      else
        mMetabKeyMap[i].resize(1);
    }
}

const CFunctionParameters & CReaction::getFunctionParameters() const
{
  if (!mpFunction) fatalError();

  return mMap.getFunctionParameters();
}

void CReaction::compile()
{
  clearDirectDependencies();
  std::set< const CCopasiObject * > Dependencies;

  CCopasiObject * pObject;

  if (mpFunction)
    {
      if (mpFunction != CCopasiRootContainer::getUndefinedFunction())
        {
          addDirectDependency(mpFunction);

          mpFluxReference->setRefresh(this, &CReaction::calculate);
          mpParticleFluxReference->setRefresh(this, &CReaction::calculate);
        }
      else
        {
          mFlux = 0.0;
          mParticleFlux = 0.0;

          mpFluxReference->clearRefresh();
          mpParticleFluxReference->clearRefresh();
        }

      size_t i, j, jmax;
      size_t imax = mMap.getFunctionParameters().size();
      std::string paramName;

      for (i = 0; i < imax; ++i)
        {
          paramName = getFunctionParameters()[i]->getObjectName();

          if (mMap.getFunctionParameters()[i]->getType() >= CFunctionParameter::VINT32)
            {
              mMap.clearCallParameter(paramName);
              jmax = mMetabKeyMap[i].size();

              for (j = 0; j < jmax; ++j)
                if ((pObject = CCopasiRootContainer::getKeyFactory()->get(mMetabKeyMap[i][j])) != NULL)
                  {
                    mMap.addCallParameter(paramName, pObject);
                    Dependencies.insert(pObject->getValueObject());
                  }
                else
                  {
                    mMap.addCallParameter(paramName, CFunctionParameterMap::pUnmappedObject);
                  }
            }
          else if ((pObject = CCopasiRootContainer::getKeyFactory()->get(mMetabKeyMap[i][0])) != NULL)
            {
              mMap.setCallParameter(paramName, pObject);
              Dependencies.insert(pObject->getValueObject());
            }
          else
            {
              mMap.setCallParameter(paramName, CFunctionParameterMap::pUnmappedObject);
            }
        }
    }

  CCopasiVector < CChemEqElement >::const_iterator it = mChemEq.getSubstrates().begin();
  CCopasiVector < CChemEqElement >::const_iterator end = mChemEq.getSubstrates().end();

  for (; it != end; ++it)
    addDirectDependency((*it)->getMetabolite());

  it = mChemEq.getProducts().begin();
  end = mChemEq.getProducts().end();

  for (; it != end; ++it)
    addDirectDependency((*it)->getMetabolite());

  it = mChemEq.getModifiers().begin();
  end = mChemEq.getModifiers().end();

  for (; it != end; ++it)
    addDirectDependency((*it)->getMetabolite());

  mpFluxReference->setDirectDependencies(Dependencies);
  mpParticleFluxReference->setDirectDependencies(Dependencies);

  setScalingFactor();
}

bool CReaction::loadOneRole(CReadConfig & configbuffer,
                            CFunctionParameter::Role role, C_INT32 n,
                            const std::string & prefix)
{
  const CModel * pModel
    = dynamic_cast< const CModel * >(getObjectAncestor("Model"));
  const CCopasiVector< CMetab > & Metabolites = pModel->getMetabolites();

  size_t pos;

  C_INT32 i, imax;
  C_INT32 index;
  std::string name, parName, metabName;
  const CFunctionParameter* pParameter;
  CCopasiDataModel* pDataModel = getObjectDataModel();
  assert(pDataModel != NULL);

  if (mMap.getFunctionParameters().isVector(role))
    {
      if (mMap.getFunctionParameters().getNumberOfParametersByUsage(role) != 1)
        {
          // not exactly one variable of this role as vector.
          fatalError();
        }

      pos = 0;
      pParameter = mMap.getFunctionParameters().getParameterByUsage(role, pos);

      if (!pParameter)
        {
          // could not find variable.
          fatalError();
        }

      parName = pParameter->getObjectName();
      clearParameterMapping(parName);

      for (i = 0; i < n; i++)
        {
          name = StringPrint(std::string(prefix + "%d").c_str(), i);
          configbuffer.getVariable(name, "C_INT32", &index);

          metabName = (*pDataModel->pOldMetabolites)[index]->getObjectName();
          addParameterMapping(parName, Metabolites[pModel->findMetabByName(metabName)]->getKey());
        }
    }
  else //no vector
    {
      imax = mMap.getFunctionParameters().getNumberOfParametersByUsage(role);

      if (imax > n)
        {
          // no. of metabs not matching function definition.
          fatalError();
        }

      for (i = 0, pos = 0; i < imax; i++)
        {
          name = StringPrint(std::string(prefix + "%d").c_str(), i);
          configbuffer.getVariable(name, "C_INT32", &index);

          metabName = (*pDataModel->pOldMetabolites)[index]->getObjectName();

          pParameter = mMap.getFunctionParameters().getParameterByUsage(role, pos);

          if (!pParameter)
            {
              // could not find variable.
              fatalError();
            }

          if (pParameter->getType() >= CFunctionParameter::VINT32)
            {
              // unexpected vector variable.
              fatalError();
            }

          parName = pParameter->getObjectName();
          setParameterMapping(parName, Metabolites[pModel->findMetabByName(metabName)]->getKey());

          // in the old files the chemical equation does not contain
          // information about modifiers. This has to be extracted from here.
          if (role == CFunctionParameter::MODIFIER)
            mChemEq.addMetabolite(Metabolites[pModel->findMetabByName(metabName)]->getKey(),
                                  1, CChemEq::MODIFIER);
        }

      //just throw away the rest (the Gepasi files gives all species, not only
      //those that influence the kinetics)
      for (i = imax; i < n; i++)
        {
          name = StringPrint(std::string(prefix + "%d").c_str(), i);
          configbuffer.getVariable(name, "C_INT32", &index);
        }
    }

  return true;
}

C_INT32 CReaction::loadOld(CReadConfig & configbuffer)
{
  C_INT32 SubstrateSize, ProductSize, ModifierSize, ParameterSize;

  configbuffer.getVariable("Substrates", "C_INT32", &SubstrateSize);
  configbuffer.getVariable("Products", "C_INT32", &ProductSize);
  configbuffer.getVariable("Modifiers", "C_INT32", &ModifierSize);
  configbuffer.getVariable("Constants", "C_INT32", &ParameterSize);

  // Construct metabolite mappings
  loadOneRole(configbuffer, CFunctionParameter::SUBSTRATE,
              SubstrateSize, "Subs");

  loadOneRole(configbuffer, CFunctionParameter::PRODUCT,
              ProductSize, "Prod");

  loadOneRole(configbuffer, CFunctionParameter::MODIFIER,
              ModifierSize, "Modf");

  C_INT32 Fail = 0;

  // Construct parameters
  if (mMap.getFunctionParameters().getNumberOfParametersByUsage(CFunctionParameter::PARAMETER)
      != (size_t) ParameterSize)
    {
      // no. of parameters not matching function definition.
      fatalError();
    }

  size_t i, pos;
  std::string name;
  const CFunctionParameter* pParameter;
  C_FLOAT64 value;

  for (i = 0, pos = 0; i < (size_t) ParameterSize; i++)
    {
      name = StringPrint("Param%d", i);
      configbuffer.getVariable(name, "C_FLOAT64", &value);

      pParameter = mMap.getFunctionParameters().getParameterByUsage(CFunctionParameter::PARAMETER, pos);

      if (!pParameter)
        {
          // could not find variable.
          fatalError();
        }

      if (pParameter->getType() != CFunctionParameter::FLOAT64)
        {
          // unexpected parameter type.
          fatalError();
        }

      setParameterValue(pParameter->getObjectName(), value);
    }

  return Fail;
}

const C_FLOAT64 & CReaction::calculateFlux()
{
  calculate();
  return mFlux;
}

const C_FLOAT64 & CReaction::calculateParticleFlux()
{
  if (mpFunction != CCopasiRootContainer::getUndefinedFunction())
    calculate();

  return mParticleFlux;
}

void CReaction::calculate()
{
  mFlux = *mScalingFactor * mpFunction->calcValue(mMap.getPointers());
  mParticleFlux = *mUnitScalingFactor * mFlux;
  return;
}

C_FLOAT64 CReaction::calculatePartialDerivative(C_FLOAT64 * pXi,
    const C_FLOAT64 & derivationFactor,
    const C_FLOAT64 & resolution)
{
  if (mpFunction->dependsOn(pXi, mMap.getPointers()))
    {
      C_FLOAT64 store = *pXi;
      C_FLOAT64 f1, f2;
      C_FLOAT64 tmp =
        (store < resolution) ? resolution * (1.0 + derivationFactor) : store; //TODO: why assymmetric?

      *pXi = tmp * (1.0 + derivationFactor);
      f1 = mpFunction->calcValue(mMap.getPointers());

      *pXi = tmp * (1.0 - derivationFactor);
      f2 = mpFunction->calcValue(mMap.getPointers());

      *pXi = store;

      return *mScalingFactor * (f1 - f2) / (2.0 * tmp * derivationFactor);
      //this is d(flow)/d(concentration)
    }
  else
    return 0.0;
}

size_t CReaction::getCompartmentNumber() const
{return mChemEq.getCompartmentNumber();}

const CCompartment * CReaction::getLargestCompartment() const
{return mChemEq.getLargestCompartment();}

void CReaction::setScalingFactor()
{
  const CCompartment * pCompartment = NULL;

  if (1 == getCompartmentNumber())
    {
      const CMetab *pMetab = NULL;

      if (mChemEq.getSubstrates().size())
        pMetab = mChemEq.getSubstrates()[0]->getMetabolite();
      else if (mChemEq.getProducts().size())
        pMetab = mChemEq.getProducts()[0]->getMetabolite();

      if (pMetab != NULL)
        pCompartment = pMetab->getCompartment();
    }

  if (pCompartment != NULL)
    {
      mScalingFactor = (C_FLOAT64 *) pCompartment->getValuePointer();

      std::set< const CCopasiObject * > Dependencies = mpFluxReference->getDirectDependencies();

      Dependencies.insert(pCompartment->getValueReference());

      mpFluxReference->setDirectDependencies(Dependencies);
      mpParticleFluxReference->setDirectDependencies(Dependencies);
    }
  else
    mScalingFactor = &mDefaultScalingFactor;

#ifdef XXXX

  if (mpFunctionCompartment)
    {
      // should propably check if the compartment appears in the chemical equation
      mScalingFactor = & mpFunctionCompartment->getVolume();
    }
  else
    {
      try
        {mScalingFactor = & mChemEq.CheckAndGetFunctionCompartment()->getVolume();}
      catch (CCopasiException Exc)
        {
          size_t nr = Exc.getMessage().getNumber();

          if ((MCChemEq + 2 == nr) || (MCChemEq + 3 == nr))
            CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 2, getObjectName().c_str());

          if (MCChemEq + 1 == nr)
            CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 3, getObjectName().c_str());

          throw;
        }
    }

#endif // XXXX

  CModel * pModel = (CModel *) getObjectAncestor("Model");

  if (pModel)
    mUnitScalingFactor = & pModel->getQuantity2NumberFactor();
  else
    mUnitScalingFactor = & mDefaultScalingFactor;
}

void CReaction::initObjects()
{
  mpFluxReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Flux", mFlux, CCopasiObject::ValueDbl));
  mpFluxReference->setRefresh(this, &CReaction::calculate);

  mpParticleFluxReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("ParticleFlux", mParticleFlux, CCopasiObject::ValueDbl));
  mpParticleFluxReference->setRefresh(this, &CReaction::calculate);

  mpPropensityReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Propensity", mPropensity, CCopasiObject::ValueDbl));
}

std::set< const CCopasiObject * > CReaction::getDeletedObjects() const
{
  std::set< const CCopasiObject * > Deleted;

  Deleted.insert(this);
  Deleted.insert(mpFluxReference);
  Deleted.insert(mpParticleFluxReference);

  // We need to add all local reaction parameters
  CCopasiParameterGroup::index_iterator it = mParameters.beginIndex();
  CCopasiParameterGroup::index_iterator end = mParameters.endIndex();

  for (; it != end ; ++it)
    {
      if (isLocalParameter((*it)->getObjectName()))
        Deleted.insert((*it)->getValueReference());
    }

  return Deleted;
}

// virtual
bool CReaction::mustBeDeleted(const CCopasiObject::DataObjectSet & deletedObjects) const
{
  bool MustBeDeleted = false;

  DataObjectSet DeletedObjects = deletedObjects;
  // We need to ignore all local reaction parameters
  CCopasiParameterGroup::index_iterator itParameter = mParameters.beginIndex();
  CCopasiParameterGroup::index_iterator endParameter = mParameters.endIndex();

  for (; itParameter != endParameter ; ++itParameter)
    {
      if (isLocalParameter((*itParameter)->getObjectName()))
        {
          DeletedObjects.erase((*itParameter)->getValueReference());
        }
    }

  DataObjectSet ChildObjects;
  ChildObjects.insert(this);
  ChildObjects.insert(mpFluxReference);
  ChildObjects.insert(mpParticleFluxReference);

  DataObjectSet::const_iterator it = ChildObjects.begin();
  DataObjectSet::const_iterator end = ChildObjects.end();

  for (; it != end; ++it)
    {
      if (*it == this)
        {
          if ((*it)->CCopasiObject::mustBeDeleted(DeletedObjects))
            {
              MustBeDeleted = true;
              break;
            }

          continue;
        }

      if ((*it)->mustBeDeleted(DeletedObjects))
        {
          MustBeDeleted = true;
          break;
        }
    }

  return MustBeDeleted;
}

std::ostream & operator<<(std::ostream &os, const CReaction & d)
{
  os << "CReaction:  " << d.getObjectName() << std::endl;
  os << "   SBML id:  " << d.mSBMLId << std::endl;

  os << "   mChemEq " << std::endl;
  os << d.mChemEq;

  if (d.mpFunction)
    os << "   *mpFunction " << d.mpFunction->getObjectName() << std::endl;
  else
    os << "   mpFunction == 0 " << std::endl;

  //os << "   mParameterDescription: " << std::endl << d.mParameterDescription;
  os << "   mFlux: " << d.mFlux << std::endl;

  if (d.mScalingFactor)
    os << "   *mScalingFactor " << *(d.mScalingFactor) << std::endl;
  else
    os << "   mScalingFactor == NULL " << std::endl;

  if (d.mUnitScalingFactor)
    os << "   *mUnitScalingFactor " << *(d.mUnitScalingFactor) << std::endl;
  else
    os << "   mUnitScalingFactor == NULL " << std::endl;

  os << "   parameter group:" << std::endl;
  os << d.mParameters;

  os << "   key map:" << std::endl;
  size_t i, j;

  for (i = 0; i < d.mMetabKeyMap.size(); ++i)
    {
      os << i << ": ";

      for (j = 0; j < d.mMetabKeyMap[i].size(); ++j)
        os << d.mMetabKeyMap[i][j] << ", ";

      os << std::endl;
    }

  os << "----CReaction" << std::endl;

  return os;
}

CEvaluationNodeVariable* CReaction::object2variable(const CEvaluationNodeObject* objectNode, std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> >& replacementMap, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  CEvaluationNodeVariable* pVariableNode = NULL;
  std::string objectCN = objectNode->getData();
  CModel * pModel
    = dynamic_cast< CModel * >(getObjectAncestor("Model"));
  std::vector<CCopasiContainer*> containers = std::vector<CCopasiContainer*>();
  containers.push_back(pModel);
  CCopasiObject* object = getObjectDataModel()->ObjectFromName(containers, CCopasiObjectName(objectCN.substr(1, objectCN.size() - 2)));
  std::string id;

  // if the object if of type reference
  if (object)
    {
      if (dynamic_cast<CCopasiObjectReference<C_FLOAT64>*>(object))
        {
          object = object->getObjectParent();

          if (object)
            {
              std::map<CCopasiObject*, SBase*>::iterator pos = copasi2sbmlmap.find(object);

              //assert(pos!=copasi2sbmlmap.end());
              // check if it is a CMetab, a CModelValue or a CCompartment
              if (dynamic_cast<CMetab*>(object))
                {
                  Species* pSpecies = dynamic_cast<Species*>(pos->second);
                  id = pSpecies->getId();

                  // We need to check that we have no reserved name.
                  const char *Reserved[] =
                  {
                    "pi", "exponentiale", "true", "false", "infinity", "nan",
                    "PI", "EXPONENTIALE", "TRUE", "FALSE", "INFINITY", "NAN"
                  };

                  size_t j, jmax = 12;

                  for (j = 0; j < jmax; j++)
                    if (id == Reserved[j]) break;

                  if (j != jmax)
                    id = "\"" + id + "\"";

                  pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, id);

                  if (replacementMap.find(id) == replacementMap.end())
                    {
                      // check whether it is a substrate, a product or a modifier
                      bool found = false;
                      const CCopasiVector<CChemEqElement>* v = &this->getChemEq().getSubstrates();
                      unsigned int i;
                      //std::string usage;
                      CFunctionParameter::Role usage;

                      for (i = 0; i < v->size(); ++i)
                        {
                          if (((*v)[i]->getMetabolite()) == static_cast<CMetab *>(object))
                            {
                              found = true;
                              usage = CFunctionParameter::SUBSTRATE;
                              break;
                            }
                        }

                      if (!found)
                        {
                          v = &this->getChemEq().getProducts();

                          for (i = 0; i < v->size(); ++i)
                            {
                              if (((*v)[i]->getMetabolite()) == static_cast<CMetab *>(object))
                                {
                                  found = true;
                                  usage = CFunctionParameter::PRODUCT;
                                  break;
                                }
                            }

                          if (!found)
                            {
                              v = &this->getChemEq().getModifiers();

                              for (i = 0; i < v->size(); ++i)
                                {
                                  if (((*v)[i]->getMetabolite()) == static_cast<CMetab *>(object))
                                    {
                                      found = true;
                                      usage = CFunctionParameter::MODIFIER;
                                      break;
                                    }
                                }

                              if (!found)
                                {
                                  // if we are reading an SBML Level 1 file
                                  // we can assume that this is a modifier since
                                  // Level 1 did not define these in the reaction
                                  if (pSpecies->getLevel() == 1)
                                    {
                                      found = true;
                                      usage = CFunctionParameter::MODIFIER;
                                    }
                                  else
                                    {
                                      delete pVariableNode;
                                      pVariableNode = NULL;
                                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCReaction + 7, id.c_str(), this->getSBMLId().c_str());
                                    }
                                }
                            }
                        }

                      if (found)
                        {
                          CFunctionParameter* pFunParam = new CFunctionParameter(id, CFunctionParameter::FLOAT64, usage);
                          replacementMap[id] = std::make_pair(object, pFunParam);
                        }
                    }
                }
              else if (dynamic_cast<CModelValue*>(object))
                {
                  // usage = "PARAMETER"
                  id = dynamic_cast<Parameter*>(pos->second)->getId();
                  pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, id);

                  if (replacementMap.find(id) == replacementMap.end())
                    {
                      CFunctionParameter* pFunParam = new CFunctionParameter(id, CFunctionParameter::FLOAT64,
                          CFunctionParameter::PARAMETER);
                      replacementMap[id] = std::make_pair(object, pFunParam);
                    }
                }
              else if (dynamic_cast<CCompartment*>(object))
                {
                  // usage = "VOLUME"
                  id = dynamic_cast<Compartment*>(pos->second)->getId();
                  pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, id);

                  if (replacementMap.find(id) == replacementMap.end())
                    {
                      CFunctionParameter* pFunParam = new CFunctionParameter(id, CFunctionParameter::FLOAT64,
                          CFunctionParameter::VOLUME);
                      replacementMap[id] = std::make_pair(object, pFunParam);
                    }
                }
              else if (dynamic_cast<CModel*>(object))
                {
                  id = object->getObjectName();
                  id = this->escapeId(id);
                  pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, id);

                  if (replacementMap.find(id) == replacementMap.end())
                    {
                      CFunctionParameter* pFunParam = new CFunctionParameter(id, CFunctionParameter::FLOAT64,
                          CFunctionParameter::TIME);
                      replacementMap[id] = std::make_pair(object, pFunParam);
                    }
                }
              else if (dynamic_cast<CReaction*>(object))
                {
                  const CReaction* pReaction = static_cast<const CReaction*>(object);
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 88, pReaction->getSBMLId().c_str(), this->getSBMLId().c_str());
                }
              else
                {
                  // error
                  CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 4);
                }
            }
        }
      else if (dynamic_cast<CCopasiParameter*>(object))
        {
          id = object->getObjectName();
          id = this->escapeId(id);
          pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, id);

          if (replacementMap.find(id) == replacementMap.end())
            {
              CFunctionParameter* pFunParam = new CFunctionParameter(id, CFunctionParameter::FLOAT64,
                  CFunctionParameter::PARAMETER);
              replacementMap[id] = std::make_pair(object, pFunParam);
            }
        }
      /*
      else if (dynamic_cast<CModel*>(object))
        {
          // usage = "TIME"
          id = object->getObjectName();
          id = this->escapeId(id);
          pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, id);
          if (replacementMap.find(id) == replacementMap.end())
            {
              CFunctionParameter* pFunParam = new CFunctionParameter(id, CFunctionParameter::FLOAT64,
                                              CFunctionParameter::TIME);
              replacementMap[id] = std::make_pair(object, pFunParam);
            }
        }
        */
      else
        {
          // error
          CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 4);
        }
    }

  return pVariableNode;
}

CEvaluationNode* CReaction::objects2variables(const CEvaluationNode* pNode, std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> >& replacementMap, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  CNodeContextIterator< const CEvaluationNode, std::vector< CEvaluationNode * > > itNode(pNode);

  CEvaluationNode* pResult = NULL;

  while (itNode.next() != itNode.end())
    {
      if (*itNode == NULL)
        {
          continue;
        }

      switch (CEvaluationNode::type(itNode->getType()))
        {
          case CEvaluationNode::OBJECT:
            // convert to a variable node
            pResult = object2variable(static_cast<const CEvaluationNodeObject * >(*itNode), replacementMap, copasi2sbmlmap);
            break;

          case CEvaluationNode::STRUCTURE:
            // this should not occur here
            fatalError();
            break;

          case CEvaluationNode::VARIABLE:
            // error variables may not be in an expression
            CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 6);
            pResult = NULL;
            break;

          case CEvaluationNode::MV_FUNCTION:
            // create an error message until there is a class for it
            CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 5, "MV_FUNCTION");
            pResult = NULL;
            break;

          case CEvaluationNode::INVALID:
            CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 5, "INVALID");
            // create an error message
            pResult = NULL;
            break;

          default:
            pResult = itNode->copyNode(itNode.context());
            break;
        }

      if (pResult != NULL &&
          itNode.parentContextPtr() != NULL)
        {
          itNode.parentContextPtr()->push_back(pResult);
        }
    }

  return pResult;
}

CFunction * CReaction::setFunctionFromExpressionTree(const CExpression & expression, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, CFunctionDB* pFunctionDB)
{
  // walk the tree and replace all object nodes with variable nodes.
  CFunction* pTmpFunction = NULL;

  const CEvaluationNode * pOrigNode = expression.getRoot();

  std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> > replacementMap = std::map<std::string , std::pair<CCopasiObject*, CFunctionParameter*> >();

  CEvaluationNode* pFunctionTree = objects2variables(pOrigNode->copyBranch(), replacementMap, copasi2sbmlmap);

  if (pFunctionTree)
    {
      // create the function object

      // later I might have to find out if I have to create a generic
      // function or a kinetic function
      // this can be distinguished by looking if the replacement map
      // contains CFunctionParameters that don't have the usage PARAMETER

      // create a unique name first
      pTmpFunction = new CKinFunction("\t"); // tab is an invalid name

      pTmpFunction->setRoot(pFunctionTree);
      pTmpFunction->setReversible(this->isReversible() ? TriTrue : TriFalse);

      pFunctionDB->add(pTmpFunction, true);
      // add the variables
      // and do the mapping
      std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> >::iterator it = replacementMap.begin();
      std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> >::iterator endIt = replacementMap.end();

      while (it != endIt)
        {
          CFunctionParameter* pFunPar = it->second.second;
          pTmpFunction->addVariable(pFunPar->getObjectName(), pFunPar->getUsage(), pFunPar->getType());
          ++it;
        }

      pTmpFunction->compile();

      setFunction(pTmpFunction);
      it = replacementMap.begin();

      while (it != endIt)
        {
          CFunctionParameter* pFunPar = it->second.second;
          std::string id = it->first;
          setParameterMapping(pFunPar->getObjectName(), it->second.first->getKey());
          delete pFunPar;
          ++it;
        }

      std::string functionName = "Function for " + this->getObjectName();

      if (expression.getObjectName() != "Expression")
        {
          functionName = expression.getObjectName();
        }

      std::string appendix = "";
      unsigned int counter = 0;
      std::ostringstream numberStream;
      CFunction * pExistingFunction = NULL;

      while ((pExistingFunction = pFunctionDB->findFunction(functionName + appendix)) != NULL)
        {
          if (SBMLImporter::areEqualFunctions(pExistingFunction, pTmpFunction))
            {
              removeDirectDependency(mpFunction);
              mpFunction = pExistingFunction;
              addDirectDependency(mpFunction);

              // The functions and their signature are equal however the role of the variables
              // might not be defined for the existing function if this is the first time it is used
              mpFunction->setReversible(pTmpFunction->isReversible());
              mpFunction->getVariables() = pTmpFunction->getVariables();

              pdelete(pTmpFunction);

              return NULL;
            }

          counter++;
          numberStream.str("");
          numberStream << "_" << counter;
          appendix = numberStream.str();
        }

      pTmpFunction->setObjectName(functionName + appendix);
    }

  return pTmpFunction;
}

CEvaluationNode* CReaction::variables2objects(CEvaluationNode* expression)
{
  CEvaluationNode* pTmpNode = NULL;
  CEvaluationNode* pChildNode = NULL;
  CEvaluationNode* pChildNode2 = NULL;

  switch (CEvaluationNode::type(expression->getType()))
    {
      case CEvaluationNode::NUMBER:
        pTmpNode = new CEvaluationNodeNumber(static_cast<CEvaluationNodeNumber::SubType>((int) CEvaluationNode::subType(expression->getType())), expression->getData());
        break;

      case CEvaluationNode::CONSTANT:
        pTmpNode = new CEvaluationNodeConstant(static_cast<CEvaluationNodeConstant::SubType>((int) CEvaluationNode::subType(expression->getType())), expression->getData());
        break;

      case CEvaluationNode::OPERATOR:
        pTmpNode = new CEvaluationNodeOperator(static_cast<CEvaluationNodeOperator::SubType>((int) CEvaluationNode::subType(expression->getType())), expression->getData());
        // convert the two children as well
        pChildNode = this->variables2objects(static_cast<CEvaluationNode*>(expression->getChild()));

        if (pChildNode)
          {
            pTmpNode->addChild(pChildNode);
            pChildNode = this->variables2objects(static_cast<CEvaluationNode*>(expression->getChild()->getSibling()));

            if (pChildNode)
              {
                pTmpNode->addChild(pChildNode);
              }
            else
              {
                delete pTmpNode;
                pTmpNode = NULL;
              }
          }
        else
          {
            delete pTmpNode;
            pTmpNode = NULL;
          }

        break;

      case CEvaluationNode::OBJECT:
        pTmpNode = new CEvaluationNodeObject(static_cast<CEvaluationNodeObject::SubType>((int) CEvaluationNode::subType(expression->getType())), expression->getData());
        break;

      case CEvaluationNode::FUNCTION:
        pTmpNode = new CEvaluationNodeFunction(static_cast<CEvaluationNodeFunction::SubType>((int) CEvaluationNode::subType(expression->getType())), expression->getData());
        // convert the only child as well
        pChildNode = this->variables2objects(static_cast<CEvaluationNode*>(expression->getChild()));

        if (pChildNode)
          {
            pTmpNode->addChild(pChildNode);
          }
        else
          {
            delete pTmpNode;
            pTmpNode = NULL;
          }

        break;

      case CEvaluationNode::CALL:
        pTmpNode = new CEvaluationNodeCall(static_cast<CEvaluationNodeCall::SubType>((int) CEvaluationNode::subType(expression->getType())), expression->getData());
        // convert all children
        pChildNode2 = static_cast<CEvaluationNode*>(expression->getChild());

        while (pChildNode2)
          {
            pChildNode = this->variables2objects(static_cast<CEvaluationNode*>(pChildNode2));

            if (pChildNode)
              {
                pTmpNode->addChild(pChildNode);
              }
            else
              {
                delete pTmpNode;
                pTmpNode = NULL;
              }

            pChildNode2 = static_cast<CEvaluationNode*>(pChildNode2->getSibling());
          }

        break;

      case CEvaluationNode::STRUCTURE:
        pTmpNode = new CEvaluationNodeStructure(static_cast<CEvaluationNodeStructure::SubType>((int) CEvaluationNode::subType(expression->getType())), expression->getData());
        break;

      case CEvaluationNode::CHOICE:
        pTmpNode = new CEvaluationNodeChoice(static_cast<CEvaluationNodeChoice::SubType>((int) CEvaluationNode::subType(expression->getType())), expression->getData());
        // convert the two children as well
        pChildNode = this->variables2objects(static_cast<CEvaluationNode*>(expression->getChild()));

        if (pChildNode)
          {
            pTmpNode->addChild(pChildNode);
            pChildNode = this->variables2objects(static_cast<CEvaluationNode*>(expression->getChild()->getSibling()));

            if (pChildNode)
              {
                pTmpNode->addChild(pChildNode);
              }
            else
              {
                delete pTmpNode;
                pTmpNode = NULL;
              }
          }
        else
          {
            delete pTmpNode;
            pTmpNode = NULL;
          }

        break;

      case CEvaluationNode::VARIABLE:
        pTmpNode = this->variable2object(static_cast<CEvaluationNodeVariable*>(expression));
        break;

      case CEvaluationNode::WHITESPACE:
        pTmpNode = new CEvaluationNodeWhiteSpace(static_cast<CEvaluationNodeWhiteSpace::SubType>((int) CEvaluationNode::subType(expression->getType())), expression->getData());
        break;

      case CEvaluationNode::LOGICAL:
        pTmpNode = new CEvaluationNodeLogical(static_cast<CEvaluationNodeLogical::SubType>((int) CEvaluationNode::subType(expression->getType())), expression->getData());
        // convert the two children as well
        pChildNode = this->variables2objects(static_cast<CEvaluationNode*>(expression->getChild()));

        if (pChildNode)
          {
            pTmpNode->addChild(pChildNode);
            pChildNode = this->variables2objects(static_cast<CEvaluationNode*>(expression->getChild()->getSibling()));

            if (pChildNode)
              {
                pTmpNode->addChild(pChildNode);
              }
            else
              {
                delete pTmpNode;
                pTmpNode = NULL;
              }
          }
        else
          {
            delete pTmpNode;
            pTmpNode = NULL;
          }

        break;

      case CEvaluationNode::MV_FUNCTION:
        // create an error message until there is a class for it
        CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 5, "MV_FUNCTION");
        break;

      case CEvaluationNode::INVALID:
        CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 5, "INVALID");
        // create an error message
        break;

      default:
        break;
    }

  return pTmpNode;
}

CEvaluationNodeObject* CReaction::variable2object(CEvaluationNodeVariable* pVariableNode)
{
  CEvaluationNodeObject* pObjectNode = NULL;
  const std::string paraName = static_cast<const std::string>(pVariableNode->getData());
  CFunctionParameter::DataType type;
  size_t index = this->getFunction()->getVariables().findParameterByName(paraName, type);

  if (index == C_INVALID_INDEX)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCReaction + 8, (static_cast<std::string>(pVariableNode->getData())).c_str());
    }

  if (type == CFunctionParameter::VFLOAT64 || type == CFunctionParameter::VINT32)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCReaction + 10, (static_cast<std::string>(pVariableNode->getData())).c_str());
    }

  const std::string& key = this->getParameterMappings()[index][0];

  CCopasiObject* pObject = CCopasiRootContainer::getKeyFactory()->get(key);

  if (!pObject)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCReaction + 9 , key.c_str());
    }

  pObjectNode = new CEvaluationNodeObject(CEvaluationNodeObject::CN, "<" + pObject->getCN() + ">");
  return pObjectNode;
}

CEvaluationNode* CReaction::getExpressionTree()
{
  return this->variables2objects(const_cast<CFunction*>(this->getFunction())->getRoot());
}

void CReaction::setSBMLId(const std::string& id)
{
  this->mSBMLId = id;
}

const std::string& CReaction::getSBMLId() const
{
  return this->mSBMLId;
}

std::string CReaction::escapeId(const std::string& id)
{
  std::string s = id;
  std::string::size_type idx = s.find('\\');

  while (idx != std::string::npos)
    {
      s.insert(idx, "\\");
      ++idx;
      idx = s.find('\\', ++idx);
    }

  idx = s.find('"');

  while (idx != std::string::npos)
    {
      s.insert(idx, "\\");
      ++idx;
      idx = s.find('"', ++idx);
    }

  if (s.find(' ') != std::string::npos || s.find('\t') != std::string::npos)
    {
      s = std::string("\"") + s + std::string("\"");
    }

  return s;
}

std::string CReaction::getObjectDisplayName(bool regular, bool richtext) const
{
  CModel* tmp = dynamic_cast<CModel*>(this->getObjectAncestor("Model"));

  if (tmp)
    {
      return "(" + getObjectName() + ")";
    }

  return CCopasiObject::getObjectDisplayName(regular, richtext);
}

void CReaction::printDebug() const
{}

void CReaction::setFast(const bool & fast)
{
  mFast = fast;
}

/**
 * Check whether the reaction needs to be treated as fast
 * @ return const bool & fast
 */
const bool & CReaction::isFast() const
{
  return mFast;
}
