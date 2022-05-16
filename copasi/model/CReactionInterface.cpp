// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <string>

#include "CReactionInterface.h"
#include "CReaction.h"
#include "CModel.h"
#include "CChemEqElement.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/function/CFunctionDB.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/model/CMetabNameInterface.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/undo/CUndoData.h"

CReactionInterface::CReactionInterface():
  mpReaction(NULL),
  mpModel(NULL),
  mChemEqI(),
  mpFunction(NULL),
  mMassAction(),
  mLocalParameters("LocalParameters"),
  mNameMap(),
  mIndexMap(),
  mValues(),
  mIsLocal(),
  mHasNoise(false),
  mNoiseExpression(),
  mKineticLawUnitType(CReaction::KineticLawUnit::Default),
  mScalingCompartment()
{}

CReactionInterface::~CReactionInterface()
{}

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
      mChemEqI.getMolecularity(CFunctionParameter::Role::SUBSTRATE),
      mChemEqI.getMolecularity(CFunctionParameter::Role::PRODUCT),
      reversible);

  std::vector<std::string> ret;
  size_t i, imax = functionVector.size();

  for (i = 0; i < imax; ++i)
    ret.push_back(functionVector[i]->getObjectName());

  return ret;
}

size_t CReactionInterface::size() const
{
  if (mpFunctionParameters != NULL)
    return mpFunctionParameters->size();

  return 0;
}

bool CReactionInterface::isVector(size_t index) const
{
  if (mpFunctionParameters &&
      index < mpFunctionParameters->size())
    {
      return (mpFunctionParameters->operator [](index)->getType() == CFunctionParameter::DataType::VFLOAT64);
    }

  return false;
}

CFunctionParameter::Role CReactionInterface::getUsage(size_t index) const
{
  if (mpFunctionParameters &&
      index < mpFunctionParameters->size())
    {
      return (*mpFunctionParameters)[index]->getUsage();
    }

  return CFunctionParameter::Role::VARIABLE;
}

std::string CReactionInterface::getParameterName(size_t index) const
{
  if (mpFunctionParameters &&
      index < mpFunctionParameters->size())
    {
      return (*mpFunctionParameters)[index]->getObjectName();
    }

  return "";
}

void CReactionInterface::init(const CReaction & reaction)
{
  mpReaction = &reaction;
  mpModel = dynamic_cast< CModel * >(mpReaction->getObjectAncestor("Model"));

  //chemical equation
  mChemEqI.init(mpReaction->getChemEq());

  mLocalParameters = mpReaction->getParameters();

  mpFunction = mpReaction->getFunction();
  initMapping();

  if (mpFunction != NULL)
    {
      if (!loadMappingAndValues())
        {
          setFunctionAndDoMapping(mpFunction->getObjectName());
        }
    }
  else
    {
      setFunctionWithEmptyMapping("undefined");
    }

  mScalingCompartment = "";

  if (mpReaction->getScalingCompartment() != NULL)
    {
      mScalingCompartment = mpReaction->getScalingCompartment()->getObjectName();
    }

  mHasNoise = mpReaction->hasNoise();

  mNoiseExpression = mpReaction->getNoiseExpression();
  mKineticLawUnitType = mpReaction->getKineticLawUnitType();
}

bool CReactionInterface::loadMappingAndValues()
{
  bool success = true;
  std::vector< std::vector< const CDataObject * > >::const_iterator it;
  std::vector< std::vector< const CDataObject * > >::const_iterator iEnd;
  std::vector< const CDataObject * >::const_iterator jt;
  std::vector< const CDataObject * >::const_iterator jEnd;
  size_t i;

  std::string metabName;
  const CModelEntity* pObj;

  std::vector<std::string> SubList;
  SubList.resize(1);
  SubList[0] = "unknown";

  mNameMap.clear();
  mValues.resize(size(), 0.1);
  mIsLocal.resize(size(), false);

  it = mpReaction->getParameterObjects().begin();
  iEnd = mpReaction->getParameterObjects().end();

  for (i = 0; it != iEnd; ++it, ++i)
    {

      if (isVector(i))
        {
          assert((getUsage(i) == CFunctionParameter::Role::SUBSTRATE)
                 || (getUsage(i) == CFunctionParameter::Role::PRODUCT)
                 || (getUsage(i) == CFunctionParameter::Role::MODIFIER));

          SubList.clear();

          for (jt = it->begin(), jEnd = it->end(); jt != jEnd; ++jt)
            {
              const CMetab * pMetab = dynamic_cast< const CMetab * >(*jt);

              if (pMetab == NULL)
                {
                  success = false;
                  continue;
                }

              metabName = CMetabNameInterface::getDisplayName(mpModel, *pMetab, true);

              if (metabName.empty())
                {
                  success = false;
                  continue;
                }

              SubList.push_back(metabName);
            }
        }
      else
        {
          assert(it->size() == 1);
          SubList.resize(1); SubList[0] = "unknown";

          switch (getUsage(i))
            {
              case CFunctionParameter::Role::SUBSTRATE:
              case CFunctionParameter::Role::PRODUCT:
              case CFunctionParameter::Role::MODIFIER:
                pObj = dynamic_cast<const CMetab *>(it->at(0));

                if (!pObj)
                  break;

                metabName = CMetabNameInterface::getDisplayName(mpModel, *dynamic_cast<const CMetab *>(pObj), true);
                // assert(metabName != emptyString);
                SubList[0] = metabName;
                //TODO: check if the metabolite is in the chemical equation with the correct rule
                break;

              case CFunctionParameter::Role::VOLUME:
                pObj = dynamic_cast<const CCompartment*>(it->at(0));

                if (!pObj)
                  break;

                SubList[0] = pObj->getObjectName();
                break;

              case CFunctionParameter::Role::TIME:
                pObj = dynamic_cast<const CModel*>(it->at(0));

                if (!pObj)
                  break;

                SubList[0] = pObj->getObjectName();
                break;

              case CFunctionParameter::Role::PARAMETER:
              {
                const CCopasiParameter * pParameter = mpReaction->getParameters().getParameter(getParameterName(i));

                if (pParameter != NULL)
                  {
                    mValues[i] = pParameter->getValue< C_FLOAT64 >();
                  }
                else
                  {
                    mValues[i] = std::numeric_limits< C_FLOAT64 >::quiet_NaN();
                  }

                mIsLocal[i] = mpReaction->isLocalParameter(i);

                if (!mIsLocal[i])
                  {
                    pObj = dynamic_cast<const CModelValue*>(it->at(0));

                    if (pObj)
                      {
                        SubList[0] = pObj->getObjectName();
                        mValues[i] = pObj->getInitialValue();
                      }
                  }
                else
                  {
                    SubList[0] = getParameterName(i);
                  }
              }
              break;

              default:
                break;
            }
        }

      std::vector< std::string > & Sources = mNameMap[getParameterName(i)];
      mIndexMap[i] = &Sources;
      Sources = SubList;
    }

  return success;
}

bool CReactionInterface::writeBackToReaction(CReaction * pReaction, bool compile)
{
  CReaction * pRea = (pReaction != NULL) ? pReaction : const_cast< CReaction * >(mpReaction);

  if (pRea == NULL) return false;

  if (mpModel == NULL)
    {
      mpModel = dynamic_cast< CModel * >(pRea->getObjectAncestor("Model"));

      if (mpModel == NULL) return false;
    }

  if (!isValid()) return false; // do nothing

  if (mpFunction == NULL) return false;

  if (mpFunction->getObjectName() == "undefined") return false;

  if (mpFunctionParameters == NULL) return false;

  if (!(*mpFunctionParameters == mpFunction->getVariables())) return false; // do nothing

  // Now we can safely write to the equation as we are sure that only unique metabolites
  // may have the empty string as compartments
  mChemEqI.writeToChemEq(&pRea->getChemEq());

  // TODO. check if function has changed since it was set in the R.I.
  pRea->setFunction(mpFunction->getObjectName());

  size_t j, jmax;
  size_t i, imax = size();
  std::pair< std::string, std::string > Names;

  for (i = 0; i < imax; ++i)
    {
      std::string ParameterName = getParameterName(i);
      std::vector< const CDataObject * > Objects;

      switch (getUsage(i))
        {
          case CFunctionParameter::Role::PARAMETER:
            pRea->setParameterValue(ParameterName, mValues[i]);

            if (mIsLocal[i])
              {
                Objects.push_back(pRea->getParameters().getParameter(ParameterName));
              }
            else
              {
                Objects.push_back(&mpModel->getModelValues()[mIndexMap[i]->at(0)]);
              }

            break;

          case CFunctionParameter::Role::VOLUME:
            Objects.push_back(&mpModel->getCompartments()[mIndexMap[i]->at(0)]);
            break;

          case CFunctionParameter::Role::TIME:
            Objects.push_back(mpModel); //time is the value of the model
            break;

          case CFunctionParameter::Role::SUBSTRATE:
          case CFunctionParameter::Role::PRODUCT:
          case CFunctionParameter::Role::MODIFIER:
            jmax = mIndexMap[i]->size();

            for (j = 0; j < jmax; ++j)
              {
                Names = CMetabNameInterface::splitDisplayName(mIndexMap[i]->at(j));
                Objects.push_back(CMetabNameInterface::getMetabolite(mpModel, Names.first, Names.second));
              }

            break;

          default:
            break;
        }

      pRea->setParameterObjects(i, Objects);
    }

  pRea->setHasNoise(mHasNoise);

  pRea->setNoiseExpression(mNoiseExpression);
  pRea->setKineticLawUnitType(mKineticLawUnitType);

  std::string ScalingCompartmentCN;
  size_t Index;

  if (!mScalingCompartment.empty() &&
      (Index = mpModel->getCompartments().getIndex(mScalingCompartment)) != C_INVALID_INDEX)
    {
      ScalingCompartmentCN = mpModel->getCompartments()[Index].getCN();
    }

  pRea->setScalingCompartmentCN(ScalingCompartmentCN);

  return true;
}

CUndoData CReactionInterface::createUndoData(const CCore::Framework & framework) const
{
  if (mpReaction == NULL ||
      mpFunction == NULL)
    {
      return CUndoData();
    }

  CUndoData UndoData(CUndoData::Type::CHANGE, mpReaction->CDataContainer::toData());
  CData OldData(mpReaction->toData());

  // We iterate over all non existing species and add their compartment if missing
  std::set< std::pair< std::string, std::string > > NonExisting = mChemEqI.listOfNonExistingMetabNames();
  std::set< std::pair< std::string, std::string > >::const_iterator itSpecies = NonExisting.begin();
  std::set< std::pair< std::string, std::string > >::const_iterator endSpecies = NonExisting.end();

  std::map< std::string, CCommonName > SpeciesParentCNs;

  for (; itSpecies != endSpecies; ++itSpecies)
    {
      std::map< std::string, CCommonName >::iterator itSpeciesParentCN = SpeciesParentCNs.find(itSpecies->second);

      if (itSpeciesParentCN == SpeciesParentCNs.end())
        {
          if (mpModel->getCompartments().getIndex(itSpecies->second) == C_INVALID_INDEX)
            {
              CCompartment Compartment(itSpecies->second);
              CUndoData CompartmentData(CUndoData::Type::INSERT, &Compartment);
              CompartmentData.addProperty(CData::OBJECT_PARENT_CN, mpModel->getCompartments().getCN());
              UndoData.addPreProcessData(CompartmentData);

              itSpeciesParentCN = SpeciesParentCNs.insert(std::make_pair(itSpecies->second, mpModel->getCompartments().getCN() + "[" + CCommonName::escape(itSpecies->second) + "],Vector=Metabolites")).first;
            }
          else
            {
              itSpeciesParentCN = SpeciesParentCNs.insert(std::make_pair(itSpecies->second, mpModel->getCompartments()[itSpecies->second].getMetabolites().getCN())).first;
            }
        }

      CMetab Species(itSpecies->first);

      size_t compIndex = mpModel->getCompartments().getIndex(itSpecies->second);
      C_FLOAT64 volume = compIndex == C_INVALID_INDEX ? 1.0 : mpModel->getCompartments()[compIndex].getInitialValue();

      if (volume != volume)
        volume = 1.0;

      switch (framework)
        {
          case CCore::Framework::Concentration:
            Species.setInitialConcentration(1.0);
            Species.setInitialValue(mpModel->getQuantity2NumberFactor() * volume); // model compile will use this value to compute initial concentration
            break;

          case CCore::Framework::ParticleNumbers:
            Species.setInitialValue(100.0);
            Species.setInitialConcentration(100.0 * mpModel->getNumber2QuantityFactor()); // value is ignored
            break;
        }

      CUndoData SpeciesData(CUndoData::Type::INSERT, &Species);
      SpeciesData.addProperty(CData::OBJECT_PARENT_CN, itSpeciesParentCN->second);

      // We need to add references to the vectors referencing the species;
      CData ReferenceData;
      std::vector< CData > References;

      ReferenceData.addProperty(CData::OBJECT_REFERENCE_CN, mpModel->getMetabolites().getCN());
      ReferenceData.addProperty(CData::OBJECT_REFERENCE_INDEX, mpModel->getMetabolites().getIndex(&Species));
      References.push_back(ReferenceData);

      ReferenceData.addProperty(CData::OBJECT_REFERENCE_CN, mpModel->getMetabolitesX().getCN());
      ReferenceData.addProperty(CData::OBJECT_REFERENCE_INDEX, mpModel->getMetabolitesX().getIndex(&Species));
      References.push_back(ReferenceData);

      SpeciesData.addProperty(CData::OBJECT_REFERENCES, References);

      UndoData.addPreProcessData(SpeciesData);
    }

  UndoData.addProperty(CData::CHEMICAL_EQUATION, OldData.getProperty(CData::CHEMICAL_EQUATION), mChemEqI.toDataValue());
  UndoData.addProperty(CData::KINETIC_LAW, OldData.getProperty(CData::KINETIC_LAW), mpFunction->getObjectName());

  size_t j, jmax;
  size_t i, imax = size();
  std::pair< std::string, std::string > Names;
  const std::vector< CData > & OldVariableMapping = OldData.getProperty(CData::KINETIC_LAW_VARIABLE_MAPPING).toDataVector();
  std::vector< CData >::const_iterator itOldVariable = OldVariableMapping.begin();
  std::vector< CData >::const_iterator endOldVariable = OldVariableMapping.end();
  std::vector< CData > OldParameterMapping;
  std::vector< CData > NewParameterMapping;
  std::map< std::string, CData > NewParameterSet;
  CCopasiParameterGroup NewParameters("Parameters", mpReaction);

  for (i = 0; i < imax && itOldVariable != endOldVariable; ++i, ++itOldVariable)
    {
      std::string ParameterName = getParameterName(i);
      CData NewMap;
      NewMap.addProperty(CData::OBJECT_NAME, ParameterName);
      std::vector< CDataValue > ParameterSource;

      const CDataObject * pObject = NULL;

      switch (getUsage(i))
        {
          case CFunctionParameter::Role::PARAMETER:

            if (mIsLocal[i])
              {
                NewParameters.addParameter(ParameterName, CCopasiParameter::Type::DOUBLE, mValues[i]);
                NewParameterSet.insert(std::make_pair(ParameterName, NewParameters.getParameter(ParameterName)->toData()));
                ParameterSource.push_back(mpReaction->getParameters().getCN() + ",Parameter=" + CCommonName::escape(ParameterName));
              }
            else
              {
                // We need to use the create the CN as the object may not yet exist;
                ParameterSource.push_back(mpModel->getModelValues().getCN() + "[" + CCommonName::escape(mIndexMap[i]->at(0)) + "]");
              }

            break;

          case CFunctionParameter::Role::VOLUME:
            ParameterSource.push_back(mpModel->getCompartments().getCN() + "[" + CCommonName::escape(mIndexMap[i]->at(0)) + "]");
            break;

          case CFunctionParameter::Role::TIME:
            ParameterSource.push_back(mpModel->getCN());
            break;

          case CFunctionParameter::Role::SUBSTRATE:
          case CFunctionParameter::Role::PRODUCT:
          case CFunctionParameter::Role::MODIFIER:

            for (j = 0, jmax = mIndexMap[i]->size(); j < jmax; ++j)
              {
                Names = mChemEqI.displayNameToNamePair(getUsage(i), mIndexMap[i]->at(j));
                ParameterSource.push_back(mpModel->getCompartments().getCN() + "[" + CCommonName::escape(Names.second) + "]" + ",Vector=Metabolites[" + CCommonName::escape(Names.first) + "]");
              }

            break;

          default:
            break;
        }

      NewMap.addProperty(CData::PARAMETER_VALUE, ParameterSource);

      if (NewMap != *itOldVariable)
        {
          OldParameterMapping.push_back(*itOldVariable);
          NewParameterMapping.push_back(NewMap);
        }
    }

  for (; i < imax; ++i)
    {
      std::string ParameterName = getParameterName(i);
      CData NewMap;
      NewMap.addProperty(CData::OBJECT_NAME, ParameterName);
      std::vector< CDataValue > ParameterSource;

      const CDataObject * pObject = NULL;

      switch (getUsage(i))
        {
          case CFunctionParameter::Role::PARAMETER:

            if (mIsLocal[i])
              {
                NewParameters.addParameter(ParameterName, CCopasiParameter::Type::DOUBLE, mValues[i]);
                NewParameterSet.insert(std::make_pair(ParameterName, NewParameters.getParameter(ParameterName)->toData()));
                ParameterSource.push_back(mpReaction->getParameters().getCN() + ",Parameter=" + CCommonName::escape(ParameterName));
              }
            else
              {
                // We need to use the create the CN as the object may not yet exist;
                ParameterSource.push_back(mpModel->getModelValues().getCN() + "[" + CCommonName::escape(mIndexMap[i]->at(0)) + "]");
              }

            break;

          case CFunctionParameter::Role::VOLUME:
            ParameterSource.push_back(mpModel->getCompartments().getCN() + "[" + CCommonName::escape(mIndexMap[i]->at(0)) + "]");
            break;

          case CFunctionParameter::Role::TIME:
            ParameterSource.push_back(mpModel->getCN());
            break;

          case CFunctionParameter::Role::SUBSTRATE:
          case CFunctionParameter::Role::PRODUCT:
          case CFunctionParameter::Role::MODIFIER:

            for (j = 0, jmax = mIndexMap[i]->size(); j < jmax; ++j)
              {
                Names = mChemEqI.displayNameToNamePair(getUsage(i), mIndexMap[i]->at(j));
                ParameterSource.push_back(mpModel->getCompartments().getCN() + "[" + CCommonName::escape(Names.second) + "]" + ",Vector=Metabolites[" + CCommonName::escape(Names.first) + "]");
              }

            break;

          default:
            break;
        }

      NewMap.addProperty(CData::PARAMETER_VALUE, ParameterSource);
      NewParameterMapping.push_back(NewMap);
    }

  for (; itOldVariable != endOldVariable; ++itOldVariable)
    {
      OldParameterMapping.push_back(*itOldVariable);
    }

  // This assumes that the function is correctly set, i.e., all local parameters have been created.
  std::map< std::string, CData >::const_iterator itNewParameter = NewParameterSet.begin();
  std::map< std::string, CData >::const_iterator endNewParameter = NewParameterSet.end();
  std::vector< CData >::const_iterator itOldParameter = OldData.getProperty(CData::LOCAL_REACTION_PARAMETERS).toDataVector().begin();
  std::vector< CData >::const_iterator endOldParameter = OldData.getProperty(CData::LOCAL_REACTION_PARAMETERS).toDataVector().end();
  std::vector< CData > OldReactionParameters;
  std::vector< CData > NewReactionParameters;

  while (itNewParameter != endNewParameter && itOldParameter != endOldParameter)
    {
      const std::string & OldName = itOldParameter->getProperty(CData::OBJECT_NAME).toString();

      if (itNewParameter->first == OldName)
        {
          if (itNewParameter->second.getProperty(CData::PARAMETER_VALUE) != itOldParameter->getProperty(CData::PARAMETER_VALUE))
            {
              NewReactionParameters.push_back(itNewParameter->second);
              OldReactionParameters.push_back(*itOldParameter);
            }

          ++itNewParameter;
          ++itOldParameter;
        }
      else if (itNewParameter->first < OldName)
        {
          NewReactionParameters.push_back(itNewParameter->second);
          ++itNewParameter;
        }
      else
        {
          OldReactionParameters.push_back(*itOldParameter);
          ++itOldParameter;
        }
    }

  for (; itNewParameter != endNewParameter; ++itNewParameter)
    {
      NewReactionParameters.push_back(itNewParameter->second);
    }

  for (; itOldParameter != endOldParameter; ++itOldParameter)
    {
      OldReactionParameters.push_back(*itOldParameter);
    }

  // Old and new parameter data is sorted by object name
  UndoData.addProperty(CData::LOCAL_REACTION_PARAMETERS, OldReactionParameters, NewReactionParameters);

  UndoData.addProperty(CData::KINETIC_LAW_VARIABLE_MAPPING, OldParameterMapping, NewParameterMapping);
  UndoData.addProperty(CData::KINETIC_LAW_UNIT_TYPE, OldData.getProperty(CData::KINETIC_LAW_UNIT_TYPE), CReaction::KineticLawUnitTypeName[mKineticLawUnitType]);
  std::string ScalingCompartmentCN;
  size_t Index;

  if (!mScalingCompartment.empty() &&
      (Index = mpModel->getCompartments().getIndex(mScalingCompartment)) != C_INVALID_INDEX)
    {
      ScalingCompartmentCN = mpModel->getCompartments()[Index].getCN();
    }

  UndoData.addProperty(CData::SCALING_COMPARTMENT, OldData.getProperty(CData::SCALING_COMPARTMENT), ScalingCompartmentCN);
  UndoData.addProperty(CData::ADD_NOISE, OldData.getProperty(CData::ADD_NOISE), mHasNoise);
  UndoData.addProperty(CData::NOISE_EXPRESSION, OldData.getProperty(CData::NOISE_EXPRESSION), mNoiseExpression);

  return UndoData;
}

void CReactionInterface::clearChemEquation()
{
  mChemEqI.clearAll();
  setFunctionWithEmptyMapping("undefined");
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
      setFunctionAndDoMapping("undefined");
      return;
    }

  //first try the function provided as argument
  if (!newFunction.empty())
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

  if (currentFunctionName != "undefined")
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

  if (currentFunctionName != "undefined")
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
              mChemEqI.getListOfDisplayNames(CFunctionParameter::Role::PRODUCT).size() == 0)
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
  size_t i, imax = mpFunctionParameters->getNumberOfParametersByUsage(role);

  if (!imax) return;

  // get the list of chem eq elements
  std::vector<std::string> el;

  if (dynamic_cast< const CMassAction * >(mpFunction) != NULL)
    el = getExpandedMetabList(role);
  else
    el = mChemEqI.getListOfDisplayNames(role);

  // get the first parameter with the respective role
  CFunctionParameter::DataType Type;
  size_t pos = 0;
  const CFunctionParameter * pFunctionParameter = mpFunctionParameters->getParameterByUsage(role, pos);
  Type = pFunctionParameter->getType();

  if (Type == CFunctionParameter::DataType::VFLOAT64)
    {
      mNameMap[pFunctionParameter->getObjectName()] = el;
    }
  else if (Type == CFunctionParameter::DataType::FLOAT64)
    {
      if (el.size() > 0)
        mNameMap[pFunctionParameter->getObjectName()][0] = el[0];
      else
        mNameMap[pFunctionParameter->getObjectName()][0] = "unknown";

      for (i = 1; i < imax; ++i)
        {
          pFunctionParameter = mpFunctionParameters->getParameterByUsage(role, pos);

          if (pFunctionParameter == NULL) fatalError();

          Type = pFunctionParameter->getType();

          if (Type != CFunctionParameter::DataType::FLOAT64) fatalError();

          if (el.size() > i)
            mNameMap[pFunctionParameter->getObjectName()][0] = el[i];
          else
            {mNameMap[pFunctionParameter->getObjectName()][0] = "unknown"; /*mValid = false;*/}
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
      case CFunctionParameter::Role::MODIFIER:
        return false;
        break;

      case CFunctionParameter::Role::TIME:
        return true;
        break;

      case CFunctionParameter::Role::SUBSTRATE:
      case CFunctionParameter::Role::PRODUCT:
      {
        // get number of parameters
        size_t paramSize = mpFunctionParameters->getNumberOfParametersByUsage(usage);

        if (paramSize == 0)
          return true;

        // get index of first parameter
        size_t pos = 0;
        mpFunctionParameters->getParameterByUsage(usage, pos); --pos;

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

      case CFunctionParameter::Role::PARAMETER:
        return mpModel->getModelValues().size() <= 1;
        break;

      case CFunctionParameter::Role::VOLUME:
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

  if (mpReaction == NULL)
    return ToBeDeleted;

  if (mpReaction->getFunction() == NULL)
    return ToBeDeleted;

  const CFunctionParameters & OriginalParameters
    = mpReaction->getFunction()->getVariables();

  size_t j, jmax = size();
  size_t i, imax = OriginalParameters.size();
  const CFunctionParameter * pParameter;

  for (i = 0; i < imax; ++i)
    {
      pParameter = OriginalParameters[i];

      if (pParameter->getUsage() == CFunctionParameter::Role::PARAMETER &&
          mpReaction->isLocalParameter(i))
        {
          const std::string & Name = pParameter->getObjectName();

          //find parameter with same name in current parameters
          for (j = 0; j < jmax; ++j)
            if (Name == getParameterName(j)) break;

          if (j < jmax && mIsLocal[j])
            continue;

          // The old parameter is either not found or is no longer local, i.e., it needs to
          // be added to values to be deleted.
          ToBeDeleted.insert(mpReaction->getParameters().getParameter(Name));
        }
    }

  return ToBeDeleted;
}

void
CReactionInterface::initMapping()
{
  mpFunctionParameters = & mpFunction->getVariables();
  mNameMap.clear();
  mIndexMap.resize(size());
  mValues.resize(size());
  mIsLocal.resize(size());

  size_t i, imax = size();

  for (i = 0; i < imax; ++i)
    {
      std::vector< std::string > & Sources = mNameMap[getParameterName(i)];
      mIndexMap[i] = &Sources;

      if (isVector(i))
        Sources.resize(0);
      else
        {
          Sources.resize(1);
          Sources[0] = "unknown";
        }

      if (getUsage(i) == CFunctionParameter::Role::PARAMETER)
        mIsLocal[i] = true;
      else
        mIsLocal[i] = false;

      mValues[i] = 0.1;
    }
}

void
CReactionInterface::copyMapping()
{
  if (!mpFunctionParameters) //nothing to copy
    {
      initMapping();
      return;
    }

  // save the old information
  const CFunctionParameters * pOldFunctionParameters = mpFunctionParameters;
  std::map< std::string, std::vector< std::string > > oldMap = mNameMap;
  std::vector<C_FLOAT64> oldValues = mValues;
  std::vector<bool> oldIsLocal = mIsLocal;

  // create new mapping
  initMapping();

  //try to preserve as much information from the old mapping as possible
  size_t i, imax = size();

  for (i = 0; i < imax; ++i)
    {
      std::map< std::string, std::vector< std::string > >::const_iterator found = oldMap.find(getParameterName(i));

      if (found == oldMap.end()) continue;

      // see if usage matches
      if (getUsage(i) != pOldFunctionParameters->operator[](getParameterName(i))->getUsage()) continue;

      // see if vector property matches
      if (isVector(i) != (pOldFunctionParameters->operator[](getParameterName(i))->getType() == CFunctionParameter::DataType::VFLOAT64))
        continue;

      size_t Index = pOldFunctionParameters->findParameterByName(getParameterName(i));
      mIsLocal[i] = oldIsLocal[Index];
      mValues[i] = oldValues[Index];

      mNameMap[getParameterName(i)] = found->second;
    }
}

void
CReactionInterface::connectNonMetabolites()
{
  size_t i, imax = size();

  for (i = 0; i < imax; ++i)
    {
      std::vector< std::string > & Sources = *mIndexMap[i];

      //only do something if the current mapping is "unknown"
      if (Sources.size())
        if (Sources[0] != "unknown")
          continue;

      if (isLocalValue(i))
        {
          // The source is the local parameter with the same name.
          Sources[0] = getParameterName(i);
          continue;
        }

      switch (getUsage(i))
        {
          case CFunctionParameter::Role::SUBSTRATE:
          case CFunctionParameter::Role::PRODUCT:
          case CFunctionParameter::Role::MODIFIER:
            break;

          case CFunctionParameter::Role::PARAMETER:

            if (mpModel->getModelValues().size() == 1)
              Sources[0] = mpModel->getModelValues()[0].getObjectName();

            break;

          case CFunctionParameter::Role::VOLUME:
            //if (mpModel->getCompartments().size()==1)
            //  mNameMap[i][0] = mpModel->getCompartments()[0]->getObjectName();
          {
            const CCompartment* comp = mChemEqI.getCompartment();

            if (comp)
              Sources[0] = comp->getObjectName();
          }
          break;

          case CFunctionParameter::Role::TIME:
            Sources[0] = mpModel->getObjectName();
            break;

          default:
            break;
        }
    }
}

void
CReactionInterface::setFunctionWithEmptyMapping(const std::string & fn)
{
  //get the function
  mpFunction = dynamic_cast<CFunction *>
               (CRootContainer::getFunctionList()->findLoadFunction(fn));

  if (mpFunction == NULL)
    {
      mpFunction = CRootContainer::getUndefinedFunction();
    }

  mpFunctionParameters = NULL;
  initMapping(); //empty mapping
}

void
CReactionInterface::setFunctionAndDoMapping(const std::string & fn)
{
  //get the function
  mpFunction = dynamic_cast<CFunction *>
               (CRootContainer::getFunctionList()->findLoadFunction(fn));

  if (mpFunction == NULL)
    {
      mpFunction = CRootContainer::getUndefinedFunction();
    }

  copyMapping();
  connectNonMetabolites();

  //guess initial connections between metabs and function parameters
  connectFromScratch(CFunctionParameter::Role::SUBSTRATE);
  connectFromScratch(CFunctionParameter::Role::PRODUCT);
  connectFromScratch(CFunctionParameter::Role::MODIFIER); // we can not be pedantic about modifiers
  // because modifiers are not taken into acount
  // when looking for suitable functions
}

std::string CReactionInterface::getFunctionName() const
{
  if (mpFunction)
    return mpFunction->getObjectName();

  return "undefined";
}

std::string CReactionInterface::getFunctionDescription() const
{
  if (mpFunction)
    return mpFunction->getInfix();

  return "";
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

  for (size_t i = 0; i < mChemEqI.getMolecularity(CFunctionParameter::Role::SUBSTRATE); ++i)
    {
      Infix << "*S" << i;
    }

  if (mpFunction->isReversible() == TriTrue)
    {
      Infix << "-k2";

      for (size_t i = 0; i < mChemEqI.getMolecularity(CFunctionParameter::Role::PRODUCT); ++i)
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
    if (getUsage(j) == CFunctionParameter::Role::MODIFIER) //all the modifiers in the table
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
      case CFunctionParameter::Role::VOLUME:
      case CFunctionParameter::Role::PARAMETER:
      case CFunctionParameter::Role::TIME:
        assert(!isVector(index));
        mNameMap[getParameterName(index)][0] = mn;
        break;

      case CFunctionParameter::Role::SUBSTRATE:
      case CFunctionParameter::Role::PRODUCT:

        if (isVector(index))
          mNameMap[getParameterName(index)].push_back(mn);
        else
          {
            mNameMap[getParameterName(index)][0] = mn;

            //TODO: check the following
            // if we have two parameters of this usage change the other one.
            size_t listSize = mChemEqI.getListOfDisplayNames(getUsage(index)).size();

            if ((listSize == 2) && (mpFunctionParameters->getNumberOfParametersByUsage(getUsage(index)) == 2))
              {
                // get index of other parameter
                size_t pos = 0;
                mpFunctionParameters->getParameterByUsage(getUsage(index), pos);

                if ((pos - 1) == index) mpFunctionParameters->getParameterByUsage(getUsage(index), pos);

                --pos;

                // get name if other metab
                std::vector<std::string> ml = getListOfMetabs(getUsage(index));
                std::string otherMetab;

                if (ml[0] == mn) otherMetab = ml[1]; else otherMetab = ml[0];

                // set other parameter
                mNameMap[getParameterName(pos)][0] = otherMetab;
              }
          }

        break;

      case CFunctionParameter::Role::MODIFIER:
        assert(!isVector(index));
        mNameMap[getParameterName(index)][0] = mn;
        updateModifiersInChemEq();
        break;

      default:
        break;
    }
}

const std::vector<std::string> &
CReactionInterface::getMappings(size_t index) const
{
  return *mIndexMap[index];
}

const std::string &
CReactionInterface::getMapping(size_t index) const
{
  return mIndexMap[index]->operator [](0);
}

std::vector< std::string > CReactionInterface::getUnitVector(size_t index) const
{
  std::vector< std::string > Units;

  switch (getUsage(index))
    {
      case CFunctionParameter::Role::SUBSTRATE:
      case CFunctionParameter::Role::PRODUCT:
      case CFunctionParameter::Role::MODIFIER:
      {
        std::vector< std::string >::const_iterator it = mIndexMap[index]->begin();
        std::vector< std::string >::const_iterator end = mIndexMap[index]->end();

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

      case CFunctionParameter::Role::PARAMETER:
      case CFunctionParameter::Role::VARIABLE:
      case CFunctionParameter::Role::TEMPORARY:
      case CFunctionParameter::Role::VOLUME:
      case CFunctionParameter::Role::TIME:
        break;
    }

  return Units;
}

std::string CReactionInterface::getUnit(size_t index) const
{
  assert(!isVector(index));

  switch (getUsage(index))
    {
      case CFunctionParameter::Role::SUBSTRATE:
      case CFunctionParameter::Role::PRODUCT:
      case CFunctionParameter::Role::MODIFIER:
      {
        // first try to find the species and return its concentration units
        const CMetab* mpMetab = dynamic_cast<const CMetab*>(mpModel->getObjectDataModel()->findObjectByDisplayName(mIndexMap[index]->operator[](0)));

        if (mpMetab != NULL)
          return CUnit::prettyPrint(mpMetab->getConcentrationReference()->getUnits());

        // if not found use the old code
        std::pair< std::string, std::string > Names = CMetabNameInterface::splitDisplayName(mIndexMap[index]->operator[](0));
        size_t Index = mpModel->getCompartments().getIndex(Names.second);

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

      case CFunctionParameter::Role::PARAMETER:

        if (isLocalValue(index))
          {
            return "?";
          }
        else
          {
            size_t Index = mpModel->getModelValues().getIndex(mIndexMap[index]->operator[](0));

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

      case CFunctionParameter::Role::VARIABLE:
      case CFunctionParameter::Role::TEMPORARY:
        return "?";

      case CFunctionParameter::Role::VOLUME:
      {
        size_t Index = mpModel->getCompartments().getIndex(mIndexMap[index]->operator[](0));

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

      case CFunctionParameter::Role::TIME:
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
      if (role == CFunctionParameter::Role::MODIFIER)
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
  CModel * pModel = const_cast< CModel * >(mpModel);

  bool ret = false;

  size_t i, imax = size();

  for (i = 0; i < imax; ++i)
    {
      const std::vector< std::string > & Sources = *mIndexMap[i];

      switch (getUsage(i))
        {
          case CFunctionParameter::Role::VOLUME:
          {
            if (Sources[0] == "unknown" || Sources[0].empty()) break;

            CCompartment *comp = pModel->createCompartment(Sources[0], 1.0);

            if (comp != NULL)
              {
                createdKeys.insert(createdKeys.begin(), comp->getKey());
                ret = true;
              }

            break;
          }

          case CFunctionParameter::Role::PARAMETER:

            if (Sources[0] == "unknown" || Sources[0].empty()) break;

            if (!isLocalValue(i))
              {
                CModelValue* param = pModel->createModelValue(Sources[0], 1.0);

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
    if ((mIndexMap[j]->size() == 0 ||
         mIndexMap[j]->operator [](0) == "unknown") &&
        (!mIsLocal[j]))
      return false;

  return true;
}

void CReactionInterface::setHasNoise(const bool & hasNoise)
{
  mHasNoise = hasNoise;

  if (!mHasNoise || !mNoiseExpression.empty()) return;

  if (mpReaction == NULL) return;

  mNoiseExpression = mpReaction->getDefaultNoiseExpression();
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

  if (EffectiveUnit == CReaction::KineticLawUnit::Default)
    {
      if (isMulticompartment())
        {
          EffectiveUnit = CReaction::KineticLawUnit::AmountPerTime;
        }
      else
        {
          EffectiveUnit = CReaction::KineticLawUnit::ConcentrationPerTime;
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

  const CCompartment & Compartment = mpModel->getCompartments()[Index];

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
      case CReaction::KineticLawUnit::AmountPerTime:
        return getAmountRateUnit();
        break;

      case CReaction::KineticLawUnit::ConcentrationPerTime:
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
      mKineticLawUnitType != CReaction::KineticLawUnit::Default) return mScalingCompartment;

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

      const std::vector< std::string > & Sources = * mIndexMap[i];
      size_t j, jmax = Sources.size();

      for (j = 0; j < jmax; ++j)
        std::cout << "            " << Sources[j] << std::endl;
    }

  std::cout << std::endl;
}
#endif // COPASI_DEBUG
