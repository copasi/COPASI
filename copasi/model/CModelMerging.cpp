// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelMerging.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: nsimus $
//   $Date: 2009/06/29 10:52:20 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CModelMerging.h"

#include "CModel.h"

CModelMerging::CModelMerging(CModel* pModel, CModel* mModel)
    : mpModel(pModel), mmModel(mModel)
{
}

void CModelMerging::setModel(CModel* pModel, CModel* mModel)
{
  mpModel = pModel;
  mmModel = mModel;
}

void CModelMerging::simpleCall()
{
  if (!mpModel) return;

  if (!mmModel) return;

  std::string name = "model_2";

  MergingInfo  mi;

  mi = addCompartments(name);
  mi = addMetabolitesAndReactions(name);

  mpModel->compileIfNecessary(NULL);
}

CModelMerging::MergingInfo CModelMerging::addCompartments(std::string name) const
{
  MergingInfo ret;

  if (!mpModel) return ret;

  if (!mmModel) return ret;

  if (!mmModel->getCompartments().size()) return ret;

  unsigned C_INT32 i, imax = mmModel->getCompartments().size();

  for (i = 0; i < imax; ++i)
    {
      const CCompartment* source = mmModel->getCompartments()[i];

      if (!source) return ret;

      //create new compartment

      std::string compartment = source->getObjectName() + "_" + name;

      CCompartment* newComp = mpModel->createCompartment(compartment, source->getInitialValue());

      if (!newComp) return ret;

      ret.key = newComp->getKey();

      newComp->setDimensionality(source->getDimensionality());
      //TODO handle non const compartments
    }
}

CModelMerging::MergingInfo CModelMerging::addMetabolitesAndReactions(std::string name) const
{
  MergingInfo ret;

  if (!mpModel) return ret;

  if (!mmModel) return ret;

  //create copies of the metabs
  unsigned C_INT32 i, imax = mmModel->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      CMetab* pSourceMetab = mmModel->getMetabolites()[i];
      const CCompartment* pSourceComp =  pSourceMetab->getCompartment();

      std::string compartment = pSourceComp->getObjectName() + "_" + name;

      unsigned C_INT32 Index;

      if ((Index = mpModel->getCompartments().getIndex(compartment)) == C_INVALID_INDEX)
        return ret;

      CCompartment* newComp = mpModel->getCompartments()[Index];

      if (!newComp) return ret;

      CMetab* pNewMetab = mpModel->createMetabolite(pSourceMetab->getObjectName(), compartment, pSourceMetab->getInitialConcentration());

      if (!pNewMetab)
        {
          continue; //TODO error handling, should not happen
        }

      if (pSourceMetab->getStatus() == CModelEntity::FIXED) pNewMetab->setStatus(CModelEntity::FIXED);

      //TODO handle metabs with rules

      ret.metabMap[pSourceMetab->getKey()] = pNewMetab->getKey();
    }

  //create copies of the relevant reactions

  imax = mmModel->getReactions().size();

  if (!mmModel->getCompartments().size()) return ret;

  unsigned C_INT32 ic, icmax = mmModel->getCompartments().size();

  for (ic = 0; ic < icmax; ++ic)
    {
      const CCompartment* source = mmModel->getCompartments()[ic];

      if (!source) return ret;

      std::string compartment = source->getObjectName() + "_" + name;

      unsigned C_INT32 Index;

      if ((Index = mpModel->getCompartments().getIndex(compartment)) == C_INVALID_INDEX)
        return ret;

      CCompartment* newComp = mpModel->getCompartments()[Index];

      if (!newComp) return ret;

      for (i = 0; i < imax; ++i)
        {
          CReaction * pReac = mmModel->getReactions()[i];

          if (reactionInvolvesCompartment(pReac, source))
            {
              CReaction* pNewReac = mpModel->createReaction(pReac->getObjectName() + "_" + name);

              if (!pNewReac)
                continue; //should not happen TODO: error handling

              //copy the chemical equation. If the involved metabs are among those that
              //were copied with the compartment, replace them. Otherwise keep the original metab
              pNewReac->setReversible(pReac->isReversible());
              std::map<std::string, std::string>::const_iterator mapIt;
              std::string targetKey;
              unsigned C_INT32 j, jmax = pReac->getChemEq().getSubstrates().size();

              for (j = 0; j < jmax; ++j)
                {
                  const CChemEqElement * sourceElement = pReac->getChemEq().getSubstrates()[j];
                  //check if the metab is in the map. If yes, translate it, otherwise not.
                  mapIt = ret.metabMap.find(sourceElement->getMetaboliteKey());

                  if (mapIt == ret.metabMap.end())
                    {
                      targetKey = sourceElement->getMetaboliteKey();
                    }
                  else
                    targetKey = mapIt->second;

                  pNewReac->addSubstrate(targetKey, sourceElement->getMultiplicity());
                }

              jmax = pReac->getChemEq().getProducts().size();

              for (j = 0; j < jmax; ++j)
                {
                  const CChemEqElement * sourceElement = pReac->getChemEq().getProducts()[j];
                  //check if the metab is in the map. If yes, translate it, otherwise not.
                  mapIt = ret.metabMap.find(sourceElement->getMetaboliteKey());

                  if (mapIt == ret.metabMap.end())
                    {
                      targetKey = sourceElement->getMetaboliteKey();
                    }
                  else
                    targetKey = mapIt->second;

                  pNewReac->addProduct(targetKey, sourceElement->getMultiplicity());
                }

              jmax = pReac->getChemEq().getModifiers().size();

              for (j = 0; j < jmax; ++j)
                {
                  const CChemEqElement * sourceElement = pReac->getChemEq().getModifiers()[j];
                  //check if the metab is in the map. If yes, translate it, otherwise not.
                  mapIt = ret.metabMap.find(sourceElement->getMetaboliteKey());

                  if (mapIt == ret.metabMap.end())
                    {
                      targetKey = sourceElement->getMetaboliteKey();
                    }
                  else
                    targetKey = mapIt->second;

                  pNewReac->addModifier(targetKey);
                }

              //set the kinetic function
              pNewReac->setFunction(const_cast<CFunction*>(pReac->getFunction()));

              //mapping and local parameters
              for (j = 0; j < pNewReac->getFunctionParameters().size(); ++j)
                {
                  switch (pNewReac->getFunctionParameters()[j]->getUsage())
                    {
                      case CFunctionParameter::SUBSTRATE:
                      case CFunctionParameter::PRODUCT:
                      case CFunctionParameter::MODIFIER:
                        //translate the metab keys
                      {
                        bool isVector = (pNewReac->getFunctionParameters()[j]->getType() == CFunctionParameter::VFLOAT64);

                        //we assume that only SUBSTRATE, PRODUCT, MODIFIER can be vectors
                        if (isVector)
                          pNewReac->clearParameterMapping(j);

                        unsigned C_INT32 k;

                        for (k = 0; k < pReac->getParameterMappings()[j].size(); ++k)
                          {
                            mapIt = ret.metabMap.find(pReac->getParameterMappings()[j][k]);

                            if (mapIt == ret.metabMap.end())
                              {
                                targetKey = pReac->getParameterMappings()[j][k];
                              }
                            else
                              targetKey = mapIt->second;

                            if (isVector)
                              pNewReac->addParameterMapping(j, targetKey);
                            else
                              pNewReac->setParameterMapping(j, targetKey);
                          }
                      }
                      break;

                      case CFunctionParameter::TIME:
                        //just copy the key
                        pNewReac->setParameterMapping(j, pReac->getParameterMappings()[j][0]);
                        break;

                      case CFunctionParameter::VOLUME:

                        //translate the compartment key if necessary
                        if (pReac->getParameterMappings()[j][0] == source->getKey())
                          pNewReac->setParameterMapping(j, newComp->getKey());
                        else
                          pNewReac->setParameterMapping(j, pReac->getParameterMappings()[j][0]);

                        //TODO: this needs to be adapted when sets of compartments will be copied
                        break;

                      case CFunctionParameter::PARAMETER:

                        if (pReac->isLocalParameter(j))
                          pNewReac->setParameterValue(pNewReac->getFunctionParameters()[j]->getObjectName(),
                                                      pReac->getParameterValue(pNewReac->getFunctionParameters()[j]->getObjectName()));
                        else
                          pNewReac->setParameterMapping(j, pReac->getParameterMappings()[j][0]);

                        break;

                      default:
                        //TODO: error handling
                        break;
                    }
                }
            }
        }
    }

  return ret;
}

//static
bool CModelMerging::reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp)
{
  if (!reac) return false;

  if (!comp) return false;

  unsigned C_INT32 i, imax = reac->getChemEq().getSubstrates().size();

  for (i = 0; i < imax; ++i)
    if (reac->getChemEq().getSubstrates()[i]->getMetabolite()->getCompartment() == comp)
      return true;

  imax = reac->getChemEq().getProducts().size();

  for (i = 0; i < imax; ++i)
    if (reac->getChemEq().getProducts()[i]->getMetabolite()->getCompartment() == comp)
      return true;

  imax = reac->getChemEq().getModifiers().size();

  for (i = 0; i < imax; ++i)
    if (reac->getChemEq().getModifiers()[i]->getMetabolite()->getCompartment() == comp)
      return true;

  return false;
}
