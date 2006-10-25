/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CReaction.cpp,v $
   $Revision: 1.163 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/10/25 15:09:38 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// CReaction
//
// Derived from Gepasi's cstep.cpp
// (C) Pedro Mendes 1995-2000
//
// Converted for Copasi by Stefan Hoops

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
#include "utilities/utility.h"
#include "function/CFunctionDB.h"
#include "report/CCopasiObjectReference.h"
#include "report/CKeyFactory.h"
#include "CMetabNameInterface.h"
#include "CChemEqInterface.h" //only for load()
#include "CChemEqElement.h"
#include "function/CExpression.h"

#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Compartment.h"

C_FLOAT64 CReaction::mDefaultScalingFactor = 1.0;

CReaction::CReaction(const std::string & name,
                     const CCopasiContainer * pParent):
    CCopasiContainer(name, pParent, "Reaction"),
    mKey(GlobalKeys.add("Reaction", this)),
    mChemEq("Chemical Equation", this),
    mpFunction(NULL),
    mFlux(0),
    mpFluxReference(NULL),
    mParticleFlux(0),
    mpParticleFluxReference(NULL),
    mScalingFactor(&mDefaultScalingFactor),
    mUnitScalingFactor(&mDefaultScalingFactor),
    mMetabKeyMap(),
    mParameters("Parameters", this)
{
  CONSTRUCTOR_TRACE;
  initObjects();
  setFunction(CCopasiDataModel::Global->mpUndefined);
}

CReaction::CReaction(const CReaction & src,
                     const CCopasiContainer * pParent):
    CCopasiContainer(src, pParent),
    mKey(GlobalKeys.add("Reaction", this)),
    mChemEq(src.mChemEq, this),
    mpFunction(src.mpFunction),
    mFlux(src.mFlux),
    mpFluxReference(NULL),
    mParticleFlux(src.mParticleFlux),
    mpParticleFluxReference(NULL),
    mScalingFactor(src.mScalingFactor),
    mUnitScalingFactor(src.mUnitScalingFactor),
    mMap(src.mMap),
    mMetabKeyMap(src.mMetabKeyMap),
    mParameters(src.mParameters, this)
{
  CONSTRUCTOR_TRACE;
  initObjects();
  if (mpFunction)
    {
      //compileParameters();
    }
}

CReaction::~CReaction()
{
  GlobalKeys.remove(mKey);
  cleanup();
  DESTRUCTOR_TRACE;
}

void CReaction::cleanup()
{
  // TODO: mMap.cleanup();
  //mParameterDescription.cleanup();
}

bool CReaction::setObjectParent(const CCopasiContainer * pParent)
{
  bool success = CCopasiContainer::setObjectParent(pParent);

  CModel * pModel = (CModel *) getObjectAncestor("Model");
  CCopasiObject * pObject;

  pObject =
    const_cast< CCopasiObject * >(getObject(CCopasiObjectName("Reference=Flux")));

  pObject =
    const_cast< CCopasiObject * >(getObject(CCopasiObjectName("Reference=ParticleFlux")));

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

  CModel * pModel = (CModel*) getObjectAncestor("Model");
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

const std::string & CReaction::getKey() const {return mKey;}

const C_FLOAT64 & CReaction::getFlux() const
  {return mFlux;}

const C_FLOAT64 & CReaction::getParticleFlux() const
  {return mParticleFlux;}

CCopasiObject * CReaction::getParticleFluxReference()
{return mpParticleFluxReference;}

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
    dynamic_cast<CFunction *>(CCopasiDataModel::Global->getFunctionList()->findLoadFunction(functionName));
  if (!pFunction)
    CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 1, functionName.c_str());

  return setFunction(pFunction);
}

bool CReaction::setFunction(CFunction * pFunction)
{
  mDependencies.erase(mpFunction);

  if (!pFunction)
    mpFunction = CCopasiDataModel::Global->mpUndefined;
  else
    mpFunction = pFunction;

  mDependencies.insert(mpFunction);

  mMap.initializeFromFunctionParameters(mpFunction->getVariables());
  initializeMetaboliteKeyMap(); //needs to be called before initializeParamters();
  initializeParameters();

  return true;
}

//****************************************

// TODO: check if function is set and map initialized in the following methods

void CReaction::setParameterValue(const std::string & parameterName, C_FLOAT64 value, bool updateStatus)
{
  if (!mpFunction) fatalError();
  mParameters.setValue(parameterName, value);

  if (!updateStatus) return;

  //make shure that this local parameter is actually used:

  //first find index
  CFunctionParameter::DataType Type;
  unsigned C_INT32 index = mMap.findParameterByName(parameterName, Type);
  //std::cout << "reaction::setParameterValue  " << parameterName << " index " << index << std::endl;

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

void CReaction::setParameterMapping(C_INT32 index, const std::string & key)
{
  //std::cout << "CReaction::setParameterMapping, index = " << index << ", key = " << key << std::endl;
  if (!mpFunction) fatalError();
  if (getFunctionParameters()[index]->getType() != CFunctionParameter::FLOAT64) fatalError(); //wrong data type

  mMetabKeyMap[index][0] = key;
}

void CReaction::addParameterMapping(C_INT32 index, const std::string & key)
{
  if (!mpFunction) fatalError();
  if (getFunctionParameters()[index]->getType() != CFunctionParameter::VFLOAT64) fatalError(); //wrong data type

  mMetabKeyMap[index].push_back(key);
}

void CReaction::setParameterMapping(const std::string & parameterName, const std::string & key)
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if (type != CFunctionParameter::FLOAT64) fatalError();

  mMetabKeyMap[index][0] = key;
}

void CReaction::addParameterMapping(const std::string & parameterName, const std::string & key)
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if (type != CFunctionParameter::VFLOAT64) fatalError();

  mMetabKeyMap[index].push_back(key);
}

void CReaction::setParameterMappingVector(const std::string & parameterName,
    const std::vector<std::string> & keys)
{
  if (!mpFunction) fatalError();

  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if ((type == CFunctionParameter::FLOAT64) && (keys.size() != 1)) fatalError();

  mMetabKeyMap[index] = keys;
}

void CReaction::clearParameterMapping(const std::string & parameterName)
{
  if (!mpFunction) fatalError();
  CFunctionParameter::DataType type;
  unsigned C_INT32 index;
  index = mMap.findParameterByName(parameterName, type);
  if (type != CFunctionParameter::VFLOAT64) fatalError(); //wrong data type
  mMetabKeyMap[index].clear();
}

void CReaction::clearParameterMapping(C_INT32 index)
{
  if (!mpFunction) fatalError();
  if (getFunctionParameters()[index]->getType() != CFunctionParameter::VFLOAT64) fatalError();
  mMetabKeyMap[index].clear();
}

const std::vector<std::string> & CReaction::getParameterMapping(const std::string & parameterName) const
  {
    if (!mpFunction) fatalError();
    CFunctionParameter::DataType type;
    unsigned C_INT32 index;
    index = mMap.findParameterByName(parameterName, type);
    //if (type != CFunctionParameter::FLOAT64) fatalError();

    return mMetabKeyMap[index];
  }

bool CReaction::isLocalParameter(C_INT32 index) const
  {
    unsigned C_INT32 i, imax = mParameters.size();
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
    unsigned C_INT32 index;
    index = mMap.findParameterByName(parameterName, type);
    if (type != CFunctionParameter::FLOAT64) fatalError();

    return isLocalParameter(index);
  }
//***********************************************************************************************

void CReaction::initializeParameters()
{
  if (!mpFunction) fatalError();
  unsigned C_INT32 i;
  unsigned C_INT32 imax = mMap.getFunctionParameters().getNumberOfParametersByUsage(CFunctionParameter::PARAMETER);
  unsigned C_INT32 pos;
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
  CCopasiParameterGroup::index_iterator begin = mParameters.beginIndex();
  CCopasiParameterGroup::index_iterator it = mParameters.endIndex();
  CFunctionParameter::DataType Type;

  while (it != begin)
    {
      --it;

      name = (*it)->getObjectName();
      if (mMap.findParameterByName(name, Type) == C_INVALID_INDEX)
        mParameters.removeParameter(name);
    }
}

void CReaction::initializeMetaboliteKeyMap()
{
  if (!mpFunction) fatalError();
  unsigned C_INT32 i;
  unsigned C_INT32 imax = mMap.getFunctionParameters().size();

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
  mDependencies.clear();
  std::set< const CCopasiObject * > Dependencies;

  CCopasiObject * pObject;

  if (mpFunction)
    {
      mDependencies.insert(mpFunction);

      unsigned C_INT32 i, j, jmax;
      unsigned C_INT32 imax = mMap.getFunctionParameters().size();
      std::string paramName;

      for (i = 0; i < imax; ++i)
        {
          paramName = getFunctionParameters()[i]->getObjectName();
          if (mMap.getFunctionParameters()[i]->getType() >= CFunctionParameter::VINT32)
            {
              mMap.clearCallParameter(paramName);
              jmax = mMetabKeyMap[i].size();
              for (j = 0; j < jmax; ++j)
                {
                  pObject = GlobalKeys.get(mMetabKeyMap[i][j]);
                  mMap.addCallParameter(paramName, pObject);
                  Dependencies.insert(pObject->getValueObject());
                }
            }
          else
            {
              pObject = GlobalKeys.get(mMetabKeyMap[i][0]);
              mMap.setCallParameter(paramName, pObject);
              Dependencies.insert(pObject->getValueObject());
            }
        }
    }

  CCopasiVector < CChemEqElement >::const_iterator it = mChemEq.getSubstrates().begin();
  CCopasiVector < CChemEqElement >::const_iterator end = mChemEq.getSubstrates().end();

  for (; it != end; ++it)
    mDependencies.insert((*it)->getMetabolite());

  it = mChemEq.getProducts().begin();
  end = mChemEq.getProducts().end();

  for (; it != end; ++it)
    mDependencies.insert((*it)->getMetabolite());

  mpFluxReference->setDirectDependencies(Dependencies);
  mpParticleFluxReference->setDirectDependencies(Dependencies);

  setScalingFactor();
}

bool CReaction::loadOneRole(CReadConfig & configbuffer,
                            CFunctionParameter::Role role, unsigned C_INT32 n,
                            const std::string & prefix)
{
  CModel * pModel = (CModel*) getObjectAncestor("Model");
  const CCopasiVector< CMetab > & Metabolites = pModel->getMetabolites();

  unsigned C_INT32 i, imax, pos;
  C_INT32 index;
  std::string name, parName, metabName;
  const CFunctionParameter* pParameter;

  if (mMap.getFunctionParameters().isVector(role))
    {
      if (mMap.getFunctionParameters().getNumberOfParametersByUsage(role) != 1)
        {
          //std::cout << "not exactly one variable of this role as vector" << std::endl;
          fatalError();
        }

      pos = 0;
      pParameter = mMap.getFunctionParameters().getParameterByUsage(role, pos);
      if (!pParameter)
        {
          //std::cout << "could not find variable" << std::endl;
          fatalError();
        }

      parName = pParameter->getObjectName();
      clearParameterMapping(parName);

      for (i = 0; i < n; i++)
        {
          name = StringPrint(std::string(prefix + "%d").c_str(), i);
          configbuffer.getVariable(name, "C_INT32", &index);

          metabName = (*CCopasiDataModel::Global->pOldMetabolites)[index]->getObjectName();
          addParameterMapping(parName, Metabolites[pModel->findMetabByName(metabName)]->getKey());
        }
    }
  else //no vector
    {
      imax = mMap.getFunctionParameters().getNumberOfParametersByUsage(role);
      if (imax > n)
        {
          //std::cout << "no. of metabs not matching function definition" << std::endl;
          fatalError();
        }

      for (i = 0, pos = 0; i < imax; i++)
        {
          name = StringPrint(std::string(prefix + "%d").c_str(), i);
          configbuffer.getVariable(name, "C_INT32", &index);

          metabName = (*CCopasiDataModel::Global->pOldMetabolites)[index]->getObjectName();

          pParameter = mMap.getFunctionParameters().getParameterByUsage(role, pos);
          if (!pParameter)
            {
              //std::cout << "could not find variable" << std::endl;
              fatalError();
            }
          if (pParameter->getType() >= CFunctionParameter::VINT32)
            {
              //std::cout << "unexpected vector variable" << std::endl;
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

      //just throw away the rest (the gepasi files gives all metabs, not only
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
  unsigned C_INT32 SubstrateSize, ProductSize, ModifierSize, ParameterSize;

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
      != ParameterSize)
    {
      //std::cout << "no. of parameters not matching function definition" << std::endl;
      fatalError();
    }

  unsigned C_INT32 i, pos;
  std::string name;
  const CFunctionParameter* pParameter;
  C_FLOAT64 value;
  for (i = 0, pos = 0; i < ParameterSize; i++)
    {
      name = StringPrint("Param%d", i);
      configbuffer.getVariable(name, "C_FLOAT64", &value);

      pParameter = mMap.getFunctionParameters().getParameterByUsage(CFunctionParameter::PARAMETER, pos);
      if (!pParameter)
        {
          //std::cout << "could not find variable" << std::endl;
          fatalError();
        }
      if (pParameter->getType() != CFunctionParameter::FLOAT64)
        {
          //std::cout << "unexpected parameter type" << std::endl;
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

unsigned C_INT32 CReaction::getCompartmentNumber() const
{return mChemEq.getCompartmentNumber();}

const CCompartment & CReaction::getLargestCompartment() const
  {return mChemEq.getLargestCompartment();}

/*const CCompartment & CReaction::getSmallestCompartment() const
{return mChemEq.getSmallestCompartment();}*/

void CReaction::setScalingFactor()
{
  const CCompartment * pCompartment = NULL;

  if (1 == getCompartmentNumber())
    {
      if (mChemEq.getSubstrates().size())
        pCompartment = mChemEq.getSubstrates()[0]->getMetabolite()->getCompartment();
      else if (mChemEq.getProducts().size())
        pCompartment = mChemEq.getProducts()[0]->getMetabolite()->getCompartment();
    }

  if (pCompartment != NULL)
    {
      mScalingFactor = (C_FLOAT64 *) pCompartment->getValuePointer();

      std::set< const CCopasiObject * > Dependencies = mpFluxReference->getDirectDependencies();

      Dependencies.insert(pCompartment->getObject(CCopasiObjectName("Reference=Volume")));

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
          unsigned C_INT32 nr = Exc.getMessage().getNumber();
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
  CModel * pModel = (CModel *) getObjectAncestor("Model");

  mpFluxReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("Flux", mFlux, CCopasiObject::ValueDbl));
  mpFluxReference->setRefresh(this, &CReaction::calculate);

  mpParticleFluxReference =
    static_cast<CCopasiObjectReference<C_FLOAT64> *>(addObjectReference("ParticleFlux", mParticleFlux, CCopasiObject::ValueDbl));
  mpParticleFluxReference->setRefresh(this, &CReaction::calculate);
}

std::set< const CCopasiObject * > CReaction::getDeletedObjects() const
  {
    std::set< const CCopasiObject * > Deleted;

    Deleted.insert(this);
    Deleted.insert(mpFluxReference);
    Deleted.insert(mpParticleFluxReference);

    return Deleted;
  }

std::ostream & operator<<(std::ostream &os, const CReaction & d)
{
  os << "CReaction:  " << d.getObjectName() << std::endl;
  os << "   sbml id:  " << d.mSBMLId << std::endl;

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
  unsigned C_INT32 i, j;
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

CEvaluationNodeVariable* CReaction::object2variable(CEvaluationNodeObject* objectNode, std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> >& replacementMap, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  CEvaluationNodeVariable* pVariableNode = NULL;
  std::string objectCN = objectNode->getData();
  CModel * pModel = (CModel*) getObjectAncestor("Model");
  std::vector<CCopasiContainer*> containers = std::vector<CCopasiContainer*>();
  containers.push_back(pModel);
  CCopasiObject* object = CCopasiContainer::ObjectFromName(containers, CCopasiObjectName(objectCN.substr(1, objectCN.size() - 2)));
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
                  id = dynamic_cast<Species*>(pos->second)->getId();

                  // We need to check that we have no reserved name.
                  const char *Reserved[] =
                    {"pi", "exponentiale", "true", "false", "infinity", "nan",
                     "PI", "EXPONENTIALE", "TRUE", "FALSE", "INFINITY", "NAN"
                    };

                  unsigned C_INT32 j, jmax = 12;
                  for (j = 0; j < jmax; j++)
                    if (id == Reserved[j]) break;

                  if (j != jmax)
                    id = "\"" + id + "\"";

                  pVariableNode = new CEvaluationNodeVariable(CEvaluationNodeVariable::ANY, id);
                  if (replacementMap.find(id) == replacementMap.end())
                    {
                      // check wether it is a substrate, a product or a modifier
                      bool found = false;
                      const CCopasiVector<CChemEqElement>* v = &this->getChemEq().getSubstrates();
                      unsigned int i;
                      //std::string usage;
                      CFunctionParameter::Role usage;
                      for (i = 0; i < v->size();++i)
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
                          for (i = 0; i < v->size();++i)
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
                              for (i = 0; i < v->size();++i)
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
                                  //found = true;
                                  //usage = CFunctionParameter::MODIFIER;
                                  //CCopasiMessage::CCopasiMessage(CCopasiMessage::WARNING, MCReaction + 7, id.c_str(), this->getSBMLId().c_str());
                                  delete pVariableNode;
                                  pVariableNode = NULL;
                                  CCopasiMessage::CCopasiMessage(CCopasiMessage::EXCEPTION, MCReaction + 7, id.c_str(), this->getSBMLId().c_str());
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
    }
  return pVariableNode;
}

CEvaluationNode* CReaction::objects2variables(CEvaluationNode* expression, std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> >& replacementMap, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap)
{
  CEvaluationNode* pTmpNode = NULL;
  CEvaluationNode* pChildNode = NULL;
  CEvaluationNode* pOldChildNode = NULL;

  switch (CEvaluationNode::type(expression->getType()))
    {
    case CEvaluationNode::NUMBER:
      pTmpNode = new CEvaluationNodeNumber(static_cast<CEvaluationNodeNumber::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      break;
    case CEvaluationNode::CONSTANT:
      pTmpNode = new CEvaluationNodeConstant(static_cast<CEvaluationNodeConstant::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      break;
    case CEvaluationNode::OPERATOR:
      pTmpNode = new CEvaluationNodeOperator(static_cast<CEvaluationNodeOperator::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      // convert the two children as well
      pChildNode = this->objects2variables(static_cast<CEvaluationNode*>(expression->getChild()), replacementMap, copasi2sbmlmap);
      if (pChildNode)
        {
          pTmpNode->addChild(pChildNode);
          pChildNode = this->objects2variables(static_cast<CEvaluationNode*>(expression->getChild()->getSibling()), replacementMap, copasi2sbmlmap);
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
      // convert to a variable node
      pTmpNode = this->object2variable(static_cast<CEvaluationNodeObject*>(expression), replacementMap, copasi2sbmlmap);
      break;
    case CEvaluationNode::FUNCTION:
      pTmpNode = new CEvaluationNodeFunction(static_cast<CEvaluationNodeFunction::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      // convert the only child as well
      pChildNode = this->objects2variables(static_cast<CEvaluationNode*>(expression->getChild()), replacementMap, copasi2sbmlmap);
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
      pTmpNode = new CEvaluationNodeCall(static_cast<CEvaluationNodeCall::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      // convert all children
      pOldChildNode = static_cast<CEvaluationNode*>(expression->getChild());
      while (pOldChildNode)
        {
          pChildNode = this->objects2variables(pOldChildNode, replacementMap, copasi2sbmlmap);
          if (pChildNode)
            {
              pTmpNode->addChild(pChildNode);
            }
          pOldChildNode = static_cast<CEvaluationNode*>(pOldChildNode->getSibling());
        }
      break;
    case CEvaluationNode::STRUCTURE:
      // this should not occur here
      fatalError();
      break;
    case CEvaluationNode::CHOICE:
      pTmpNode = new CEvaluationNodeChoice(static_cast<CEvaluationNodeChoice::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      // convert the two children as well
      pChildNode = this->objects2variables(static_cast<CEvaluationNode*>(expression->getChild()), replacementMap, copasi2sbmlmap);
      if (pChildNode)
        {
          pTmpNode->addChild(pChildNode);
          pChildNode = this->objects2variables(static_cast<CEvaluationNode*>(expression->getChild()->getSibling()), replacementMap, copasi2sbmlmap);
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
      // error variables may not be in an expression
      CCopasiMessage(CCopasiMessage::ERROR, MCReaction + 6);
      break;
    case CEvaluationNode::WHITESPACE:
      pTmpNode = new CEvaluationNodeWhiteSpace(static_cast<CEvaluationNodeWhiteSpace::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      break;
    case CEvaluationNode::LOGICAL:
      pTmpNode = new CEvaluationNodeLogical(static_cast<CEvaluationNodeLogical::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      // convert the two children as well
      pChildNode = this->objects2variables(static_cast<CEvaluationNode*>(expression->getChild()), replacementMap, copasi2sbmlmap);
      if (pChildNode)
        {
          pTmpNode->addChild(pChildNode);
          pChildNode = this->objects2variables(static_cast<CEvaluationNode*>(expression->getChild()->getSibling()), replacementMap, copasi2sbmlmap);
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

bool CReaction::setFunctionFromExpressionTree(CEvaluationTree* tree, std::map<CCopasiObject*, SBase*>& copasi2sbmlmap, CFunctionDB* pFunctionDB)
{
  // walk the tree and replace all object nodes with variable nodes.
  CFunction* pFun = NULL;
  if (dynamic_cast<CExpression*>(tree))
    {
      CEvaluationNode* pOrigNode = tree->getRoot();

      std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> > replacementMap = std::map<std::string , std::pair<CCopasiObject*, CFunctionParameter*> >();

      CEvaluationNode* pFunctionTree = this->objects2variables(pOrigNode, replacementMap, copasi2sbmlmap);
      if (pFunctionTree)
        {
          // create the function object

          // later I might have to find out if I have to create a generic
          // function or a kinetic function
          // this can be distinguished by looking if the replacement map
          // constains CFunctionParameters that don't have the usage PARAMETER

          // create a unique name first
          std::string functionName = "function_4_" + this->getObjectName();

          std::string appendix = "";
          unsigned int counter = 0;
          std::ostringstream numberStream;
          while (pFunctionDB->findFunction(functionName + appendix) != NULL)
            {
              counter++;
              numberStream.str("");
              numberStream << "_" << counter;
              appendix = numberStream.str();
            }

          pFun = new CKinFunction(functionName + appendix);
          pFun->setType(CFunction::UserDefined);
          pFun->setRoot(pFunctionTree);
          pFun->setReversible(this->isReversible() ? TriTrue : TriFalse);

          pFunctionDB->add(pFun, true);
          // add the variables
          // and do the mapping
          std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> >::iterator it = replacementMap.begin();
          std::map<std::string, std::pair<CCopasiObject*, CFunctionParameter*> >::iterator endIt = replacementMap.end();
          while (it != endIt)
            {
              CFunctionParameter* pFunPar = it->second.second;
              pFun->addVariable(pFunPar->getObjectName(), pFunPar->getUsage(), pFunPar->getType());
              ++it;
            }
          pFun->compile();

          this->setFunction(pFun);
          it = replacementMap.begin();
          while (it != endIt)
            {
              CFunctionParameter* pFunPar = it->second.second;
              CCopasiObject* pObject = it->second.first;
              std::string id = it->first;
              this->setParameterMapping(pFunPar->getObjectName(), it->second.first->getKey());
              delete pFunPar;
              ++it;
            }
        }
    }
  return pFun != NULL;
}

CEvaluationNode* CReaction::variables2objects(CEvaluationNode* expression)
{
  CEvaluationNode* pTmpNode = NULL;
  CEvaluationNode* pChildNode = NULL;
  CEvaluationNode* pChildNode2 = NULL;
  switch (CEvaluationNode::type(expression->getType()))
    {
    case CEvaluationNode::NUMBER:
      pTmpNode = new CEvaluationNodeNumber(static_cast<CEvaluationNodeNumber::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      break;
    case CEvaluationNode::CONSTANT:
      pTmpNode = new CEvaluationNodeConstant(static_cast<CEvaluationNodeConstant::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      break;
    case CEvaluationNode::OPERATOR:
      pTmpNode = new CEvaluationNodeOperator(static_cast<CEvaluationNodeOperator::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
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
      pTmpNode = new CEvaluationNodeObject(static_cast<CEvaluationNodeObject::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      break;
    case CEvaluationNode::FUNCTION:
      pTmpNode = new CEvaluationNodeFunction(static_cast<CEvaluationNodeFunction::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
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
      pTmpNode = new CEvaluationNodeCall(static_cast<CEvaluationNodeCall::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
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
      pTmpNode = new CEvaluationNodeStructure(static_cast<CEvaluationNodeStructure::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      break;
    case CEvaluationNode::CHOICE:
      pTmpNode = new CEvaluationNodeChoice(static_cast<CEvaluationNodeChoice::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
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
      pTmpNode = new CEvaluationNodeWhiteSpace(static_cast<CEvaluationNodeWhiteSpace::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
      break;
    case CEvaluationNode::LOGICAL:
      pTmpNode = new CEvaluationNodeLogical(static_cast<CEvaluationNodeLogical::SubType>(CEvaluationNode::subType(expression->getType())), expression->getData());
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
  unsigned C_INT32 index = this->getFunction()->getVariables().findParameterByName(paraName, type);

  if (index == C_INVALID_INDEX)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCReaction + 8, (static_cast<std::string>(pVariableNode->getData())).c_str());
    }
  if (type == CFunctionParameter::VFLOAT64 || type == CFunctionParameter::VINT32)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCReaction + 10, (static_cast<std::string>(pVariableNode->getData())).c_str());
    }
  const std::string& key = this->getParameterMappings()[index][0];
  CCopasiObject* pObject = GlobalKeys.get(key);
  if (!pObject)
    {
      CCopasiMessage(CCopasiMessage::EXCEPTION, MCReaction + 9 , key.c_str());
    }
  pObjectNode = new CEvaluationNodeObject(CEvaluationNodeObject::ANY, "<" + pObject->getCN() + ">");
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

void CReaction::printDebug() const
  {std::cout << *this;}
