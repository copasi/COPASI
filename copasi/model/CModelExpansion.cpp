// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CModelExpansion.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2009/05/07 19:04:18 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CModelExpansion.h"

#include "CModel.h"

CModelExpansion::CModelExpansion(CModel* pModel)
    : mpModel(pModel)
{
}

void CModelExpansion::setModel(CModel* pModel)
{
  mpModel = pModel;
}

void CModelExpansion::simpleCall()
{
  if (!mpModel) return;

  if (!mpModel->getCompartments().size()) return;

  CompartmentInfo ci = copyCompartment(mpModel->getCompartments()[0], "copy");

  mpModel->compileIfNecessary(NULL);
}

CModelExpansion::CompartmentInfo CModelExpansion::copyCompartment(const CCompartment* source, std::string name) const
{
  CompartmentInfo ret;

  if (!mpModel) return ret;

  if (!source) return ret;

  //create new compartment
  CCompartment* newComp = mpModel->createCompartment(name, source->getInitialValue());

  if (!newComp) return ret;

  ret.key = newComp->getKey();

  newComp->setDimensionality(source->getDimensionality());
  //TODO handle non const compartments

  //create copies of the metabs
  unsigned C_INT32 i, imax = source->getMetabolites().size();

  for (i = 0; i < imax; ++i)
    {
      CMetab* pSourceMetab = source->getMetabolites()[i];
      CMetab* pNewMetab = mpModel->createMetabolite(pSourceMetab->getObjectName(), newComp->getObjectName(), pSourceMetab->getInitialConcentration());

      if (!pNewMetab)
        continue; //TODO error handling, should not happen

      if (pSourceMetab->getStatus() == CModelEntity::FIXED) pNewMetab->setStatus(CModelEntity::FIXED);

      //TODO handle metabs with rules

      ret.metabMap[pSourceMetab->getKey()] = pNewMetab->getKey();
    }

  //create copies of the relevant reactions
  imax = mpModel->getReactions().size();

  for (i = 0; i < imax; ++i)
    {
      CReaction * pReac = mpModel->getReactions()[i];

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
                targetKey = sourceElement->getMetaboliteKey();
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
                targetKey = sourceElement->getMetaboliteKey();
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
                targetKey = sourceElement->getMetaboliteKey();
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
                          targetKey = pReac->getParameterMappings()[j][k];
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

  return ret;
}

//static
bool CModelExpansion::reactionInvolvesCompartment(const CReaction * reac, const CCompartment* comp)
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
