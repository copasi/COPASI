// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <locale>

#include "CModelExpansion.h"

#include "CModel.h"
#include "function/CExpression.h"
#include "report/CCopasiObject.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CCopasiRootContainer.h"

void CModelExpansion::SetOfModelElements::addCompartment(const CCompartment* x)
{
  mCompartments.insert(x);
}

void CModelExpansion::SetOfModelElements::addMetab(const CMetab* x)
{
  mMetabs.insert(x);
}

void CModelExpansion::SetOfModelElements::addReaction(const CReaction* x)
{
  mReactions.insert(x);
}

void CModelExpansion::SetOfModelElements::addGlobalQuantity(const CModelValue* x)
{
  mGlobalQuantities.insert(x);
}

void CModelExpansion::SetOfModelElements::addEvent(const CEvent* x)
{
  mEvents.insert(x);
}

bool CModelExpansion::SetOfModelElements::contains(const CCopasiObject* x) const
{
  if (mCompartments.find(static_cast<const CCompartment*>(x)) != mCompartments.end())
    return true;

  if (mMetabs.find(static_cast<const CMetab*>(x)) != mMetabs.end())
    return true;

  if (mReactions.find(static_cast<const CReaction*>(x)) != mReactions.end())
    return true;

  if (mGlobalQuantities.find(static_cast<const CModelValue*>(x)) != mGlobalQuantities.end())
    return true;

  if (mEvents.find(static_cast<const CEvent*>(x)) != mEvents.end())
    return true;

  return false;
}

bool CModelExpansion::SetOfModelElements::contains(const std::string & key) const
{
  const CCopasiObject* tmp = CCopasiRootContainer::getKeyFactory()->get(key);

  if (tmp)
    return contains(tmp);
  else
    return false;
}

void CModelExpansion::SetOfModelElements::fillDependencies(const CModel* pModel)
{
  if (!pModel) return;

  //create a combined set of all elements we know are to be copied
  std::set< const CCopasiObject * > combinedSet;

  std::set<const CCompartment*>::const_iterator itComp;

  for (itComp = mCompartments.begin(); itComp != mCompartments.end(); ++itComp)
    {
      std::set< const CCopasiObject * > tmp = (*itComp)->getDeletedObjects();
      combinedSet.insert(tmp.begin(), tmp.end());
    }

  std::set<const CMetab*>::const_iterator itMetab;

  for (itMetab = mMetabs.begin(); itMetab != mMetabs.end(); ++itMetab)
    {
      std::set< const CCopasiObject * > tmp = (*itMetab)->getDeletedObjects();
      combinedSet.insert(tmp.begin(), tmp.end());
    }

  std::set<const CReaction*>::const_iterator itReac;

  for (itReac = mReactions.begin(); itReac != mReactions.end(); ++itReac)
    {
      std::set< const CCopasiObject * > tmp = (*itReac)->getDeletedObjects();
      combinedSet.insert(tmp.begin(), tmp.end());
    }

  std::set<const CModelValue*>::const_iterator itQuant;

  for (itQuant = mGlobalQuantities.begin(); itQuant != mGlobalQuantities.end(); ++itQuant)
    {
      std::set< const CCopasiObject * > tmp = (*itQuant)->getDeletedObjects();
      combinedSet.insert(tmp.begin(), tmp.end());
    }

  std::set<const CEvent*>::const_iterator itEvent;

  for (itEvent = mEvents.begin(); itEvent != mEvents.end(); ++itEvent)
    {
      std::set< const CCopasiObject * > tmp = (*itQuant)->getDeletedObjects();
      combinedSet.insert(tmp.begin(), tmp.end());
    }

  //ask the model for the dependencies

  std::set< const CCopasiObject * > reacs, metabs, comps, values, events;
  pModel->appendDependentModelObjects(combinedSet, reacs, metabs, comps, values, events);

  //incorporate the results into the local sets
  std::set< const CCopasiObject * >::const_iterator it;

  for (it = reacs.begin(); it != reacs.end(); ++it)
    addReaction(dynamic_cast<const CReaction*>(*it));

  for (it = metabs.begin(); it != metabs.end(); ++it)
    addMetab(dynamic_cast<const CMetab*>(*it));

  for (it = comps.begin(); it != comps.end(); ++it)
    addCompartment(dynamic_cast<const CCompartment*>(*it));

  for (it = values.begin(); it != values.end(); ++it)
    addGlobalQuantity(dynamic_cast<const CModelValue*>(*it));

  for (it = events.begin(); it != events.end(); ++it)
    addEvent(dynamic_cast<const CEvent*>(*it));
}

void CModelExpansion::SetOfModelElements::fillComplete(const CModel* pModel)
{
  if (!pModel)
    return;
  
  size_t i;
  for (i=0; i<pModel->getCompartments().size(); ++i)
    addCompartment(pModel->getCompartments()[i]);
  for (i=0; i<pModel->getMetabolites().size(); ++i)
    addMetab(pModel->getMetabolites()[i]);
  for (i=0; i<pModel->getReactions().size(); ++i)
    addReaction(pModel->getReactions()[i]);
  for (i=0; i<pModel->getModelValues().size(); ++i)
    addGlobalQuantity(pModel->getModelValues()[i]);
  for (i=0; i<pModel->getEvents().size(); ++i)
    addEvent(pModel->getEvents()[i]);
}


//***************************************************************************************

bool CModelExpansion::ElementsMap::exists(const CCopasiObject* source) const
{
  std::map<const CCopasiObject*, CCopasiObject*>::const_iterator it;
  it = mMap.find(source);
  return (it != mMap.end() && it->second != NULL);
}

bool CModelExpansion::ElementsMap::exists(const std::string & sourceKey) const
{
  const CCopasiObject* tmp = CCopasiRootContainer::getKeyFactory()->get(sourceKey);
  return exists(tmp);
}

void CModelExpansion::ElementsMap::add(const CCopasiObject* source, CCopasiObject* copy)
{
  mMap[source] = copy;
}

CCopasiObject* CModelExpansion::ElementsMap::getDuplicatePtr(const CCopasiObject* source) const
{
  std::map<const CCopasiObject*, CCopasiObject*>::const_iterator it;
  it = mMap.find(source);

  if (it != mMap.end())
    return it->second;
  else
    return NULL;
}

std::string CModelExpansion::ElementsMap::getDuplicateKey(const std::string & sourceKey) const
{
  const CCopasiObject* tmp = CCopasiRootContainer::getKeyFactory()->get(sourceKey);

  if (tmp)
    {
      const CCopasiObject* retObj = getDuplicatePtr(tmp);

      if (retObj)
        return retObj->getKey();
      else
        return "";
    }
  else
    return "";
}

const std::map<const CCopasiObject*, CCopasiObject*> & CModelExpansion::ElementsMap::getMap() const
{
  return mMap;
}

//***************************************************************************************

CModelExpansion::CModelExpansion(CModel* pModel)
  : mpModel(pModel)
{
}

void CModelExpansion::setModel(CModel* pModel)
{
  mpModel = pModel;
}

void CModelExpansion::simpleCall(const CCompartment * source, std::vector< std::string  > listOfMetabolites,  int  mult, bool diff)
{
  if (!mpModel) return;

  if (!source) return;

  //First we create a SetOfModelElements object. It will contain the list of all things in the model that
  //should be duplicated. (This means that we can duplicate also parts of models, not only complete models)
  SetOfModelElements originalSet;

  //We start by specifying one compartment that we want to duplicate
  originalSet.addCompartment(source);

  //Now we (automatically) include everything that needs to be duplicated with the compartment.
  //(The species in the compartment, the reactions incolving these species)
  originalSet.fillDependencies(mpModel);

  //now we want to create one copy. indexstring contains a postfix that will be added to the names of
  //the duplicated model parts to identify them
  std::string indexstr = "[1]";

  //the ElementsMap object will contain a mapping between original and duplicated objects
  //after the duplicating has been performed. This means we will be able to access the duplicated
  //objects e.g. for creating diffusion reactions.
  ElementsMap map_1;

  //this performes the actual duplication:
  duplicate(originalSet, indexstr, map_1);

  //now a second copy (this can easily be put in a loop)
  indexstr = "[2]";
  ElementsMap map_2;
  duplicate(originalSet, indexstr, map_2);

  //and a third
  indexstr = "[3]";
  ElementsMap map_3;
  duplicate(originalSet, indexstr, map_3);

  if (listOfMetabolites.size() > 0)
    {
      //now create the diffusion reactions:
      //we pick a metab for which we want to create diffusion reactions
      std::string original_metab_key = listOfMetabolites[0];

      //create a global quantity that will be used as the diffusion parameter
      CModelValue* pMV = mpModel->createModelValue("Diff_glu", 7);

      //create first reaction.
      //the maps let us find the duplicates of the original metab.
      createDiffusionReaction("Diff_glu[1-2]",
                              map_1.getDuplicateKey(original_metab_key),
                              map_2.getDuplicateKey(original_metab_key), pMV->getKey());

      //create second reaction (this can easily be put in a loop)
      createDiffusionReaction("Diff_glu[2-3]",
                              map_2.getDuplicateKey(original_metab_key),
                              map_3.getDuplicateKey(original_metab_key), pMV->getKey());
    }

  mpModel->compileIfNecessary(NULL);
}

void CModelExpansion::createLinearArray(const SetOfModelElements & source, size_t n, const std::set< std::string  > & setOfMetabolites)
{
  if (!mpModel) return;

  //create global quantities for the diffusion constants
  std::vector<CModelValue*> diffusionConstants;
  std::set<std::string>::const_iterator itMetab;

  for (itMetab = setOfMetabolites.begin(); itMetab != setOfMetabolites.end(); ++itMetab)
    {
      //try creating the object until we find a name that is not yet used
      CModelValue* newObj;
      const CMetab* pMetab = dynamic_cast<const CMetab*>(CCopasiRootContainer::getKeyFactory()->get(*itMetab));

      if (!pMetab)
        continue;

      std::string name = "diff_" + pMetab->getCompartment()->getObjectName() + "_" + pMetab->getObjectName();

      do
        {
          newObj = mpModel->createModelValue(name, 1.0);
          name += "_";
        }
      while (!newObj);

      diffusionConstants.push_back(newObj);
    }

  //now create the copies
  size_t i;
  std::vector<ElementsMap> maps;
  maps.resize(n);

  for (i = 0; i < n; ++i)
    {
      std::ostringstream indexstr;
      indexstr << "[" << i << "]";
      duplicate(source, indexstr.str(), maps[i]);

      //Diffusion
      if (i)
        {
          std::vector<CModelValue*>::const_iterator itDiff;

          for (itMetab = setOfMetabolites.begin(), itDiff = diffusionConstants.begin();
               itMetab != setOfMetabolites.end();
               ++itMetab, ++itDiff)
            {
              std::ostringstream diffname;
              diffname << (*itDiff)->getObjectName() << "[" << i - 1 << "-" << i << "]";
              createDiffusionReaction(diffname.str(),
                                      maps[i - 1].getDuplicateKey(*itMetab),
                                      maps[i].getDuplicateKey(*itMetab), (*itDiff)->getKey());
            }
        }
    }

  mpModel->compileIfNecessary(NULL);
}

void CModelExpansion::createRectangularArray(const SetOfModelElements & source, size_t nx, size_t ny, const std::set< std::string  > & setOfMetabolites)
{
  if (!mpModel) return;

  //create global quantities for the diffusion constants
  std::vector<CModelValue*> diffusionConstants;
  std::set<std::string>::const_iterator itMetab;

  for (itMetab = setOfMetabolites.begin(); itMetab != setOfMetabolites.end(); ++itMetab)
    {
      //try creating the object until we find a name that is not yet used
      CModelValue* newObj;
      const CMetab* pMetab = dynamic_cast<const CMetab*>(CCopasiRootContainer::getKeyFactory()->get(*itMetab));

      if (!pMetab)
        continue;

      std::string name = "diff_" + pMetab->getCompartment()->getObjectName() + "_" + pMetab->getObjectName();

      do
        {
          newObj = mpModel->createModelValue(name, 1.0);
          name += "_";
        }
      while (!newObj);

      diffusionConstants.push_back(newObj);
    }

  //now create the copies
  size_t i, j;
  std::vector<std::vector<ElementsMap> > maps;
  maps.resize(nx);

  for (i = 0; i < nx; ++i)
    maps[i].resize(ny);

  for (i = 0; i < nx; ++i)
    for (j = 0; j < ny; ++j)
      {
        std::ostringstream indexstr;
        indexstr << "[" << i << "," << j << "]";
        duplicate(source, indexstr.str(), maps[i][j]);

        //Diffusion
        if (i)
          {
            std::vector<CModelValue*>::const_iterator itDiff;

            for (itMetab = setOfMetabolites.begin(), itDiff = diffusionConstants.begin();
                 itMetab != setOfMetabolites.end();
                 ++itMetab, ++itDiff)
              {
                std::ostringstream diffname;
                diffname << (*itDiff)->getObjectName() << "[" << i - 1 << "-" << i << "," << j << "]";
                createDiffusionReaction(diffname.str(),
                                        maps[i - 1][j].getDuplicateKey(*itMetab),
                                        maps[i][j].getDuplicateKey(*itMetab), (*itDiff)->getKey());
              }
          }

        if (j)
          {
            std::vector<CModelValue*>::const_iterator itDiff;

            for (itMetab = setOfMetabolites.begin(), itDiff = diffusionConstants.begin();
                 itMetab != setOfMetabolites.end();
                 ++itMetab, ++itDiff)
              {
                std::ostringstream diffname;
                diffname << (*itDiff)->getObjectName() << "[" << i << "," << j - 1 << "-" << j << "]";
                createDiffusionReaction(diffname.str(),
                                        maps[i][j - 1].getDuplicateKey(*itMetab),
                                        maps[i][j].getDuplicateKey(*itMetab), (*itDiff)->getKey());
              }
          }
      }

  mpModel->compileIfNecessary(NULL);
}

std::set<CCopasiObject*> CModelExpansion::copyCompleteModel(const CModel* pSourceModel)
{
  SetOfModelElements sourceElements;
  sourceElements.fillComplete(pSourceModel);
  ElementsMap map;
  duplicate(sourceElements, "[merge]", map);
  mpModel->compileIfNecessary(NULL);

  std::set<CCopasiObject*> ret;
  std::map<const CCopasiObject*, CCopasiObject*>::const_iterator it;
  for (it=map.getMap().begin(); it != map.getMap().end(); ++it)
    {
    ret.insert(it->second);
    //std::cout << it->second->getObjectDisplayName() << std::endl;
    }
    
  return ret;
}

bool CModelExpansion::duplicate(const SetOfModelElements & source, const std::string & index, ElementsMap & emap)
{
  std::set<const CCompartment*>::const_iterator itComp;

  for (itComp = source.mCompartments.begin(); itComp != source.mCompartments.end(); ++itComp)
    {
      duplicateCompartment(*itComp, index, source, emap);
    }

  std::set<const CMetab*>::const_iterator itMetab;

  for (itMetab = source.mMetabs.begin(); itMetab != source.mMetabs.end(); ++itMetab)
    {
      duplicateMetab(*itMetab, index, source, emap);
    }

  std::set<const CReaction*>::const_iterator itReac;

  for (itReac = source.mReactions.begin(); itReac != source.mReactions.end(); ++itReac)
    {
      duplicateReaction(*itReac, index, source, emap);
    }

  std::set<const CModelValue*>::const_iterator itME;

  for (itME = source.mGlobalQuantities.begin(); itME != source.mGlobalQuantities.end(); ++itME)
    {
      duplicateGlobalQuantity(*itME, index, source, emap);
    }

  std::set<const CEvent*>::const_iterator itEvent;

  for (itEvent = source.mEvents.begin(); itEvent != source.mEvents.end(); ++itEvent)
    {
      duplicateEvent(const_cast<CEvent*>(*itEvent), index, source, emap);
      //the event can be changed. Potentially it is not duplicated in its entirety but only some event assignments are duplicated.
    }

  // compilation failed on Win32, need return value for boolean
  return false;
}

void CModelExpansion::duplicateCompartment(const CCompartment* source, const std::string & index, const SetOfModelElements & sourceSet, ElementsMap & emap)
{
  //if the source object has already been duplicated: do nothing
  if (emap.exists(source))
    return;

  //try creating the object until we find a name that is not yet used
  CCompartment* newObj;
  std::ostringstream infix;

  do
    {
      std::ostringstream name;
      name << source->getObjectName() << infix.str() << index;
      newObj = mpModel->createCompartment(name.str(), source->getInitialValue());
      infix << "_";
    }
  while (!newObj);

  //now copy the contents of the object
  newObj->setDimensionality(source->getDimensionality());

  //status
  newObj->setStatus(source->getStatus());

  //expression (for assignment or ODE)
  newObj->setExpression(source->getExpression());
  updateExpression(newObj->getExpressionPtr(), index, sourceSet, emap);

  //initial expression
  newObj->setInitialExpression(source->getInitialExpression());
  updateExpression(newObj->getInitialExpressionPtr(), index, sourceSet, emap);

  newObj->setNotes(source->getNotes());
  newObj->setMiriamAnnotation(source->getMiriamAnnotation(), newObj->getKey(), source->getKey());

  //add duplicated object to the map
  emap.add(source, newObj);
}

void CModelExpansion::duplicateMetab(const CMetab* source, const std::string & index, const SetOfModelElements & sourceSet, ElementsMap & emap)
{
  //if the source object has already been duplicated: do nothing
  if (emap.exists(source))
    return;

  //is the containing compartment also duplicated?
  const CCompartment* sourceParent = source->getCompartment();
  const CCompartment * parent = NULL;
  bool nameflag;

  if (!sourceSet.contains(sourceParent))
    {
      parent = sourceParent; //use the original parent compartment
      nameflag = true; //metab needs renaming
    }
  else //use a copy of the parent compartment
    {
      nameflag = false; //no renaming necessary (since the copy is in a different compartment)

      //create copy if it does not exist
      if (!emap.exists(sourceParent))
        {
          duplicateCompartment(sourceParent, index, sourceSet, emap);
        }

      parent = dynamic_cast<CCompartment *>(emap.getDuplicatePtr(sourceParent));
    }

  //try creating the object until we find a name that is not yet used
  CMetab* newObj;
  std::ostringstream infix;

  do
    {
      std::ostringstream name;
      name << source->getObjectName() << infix.str();

      if (nameflag)
        name << index;

      newObj = mpModel->createMetabolite(name.str(), parent->getObjectName(), source->getInitialConcentration(), source->getStatus());

      infix << "_";
    }
  while (!newObj);

  //expression (for assignment or ODE)
  newObj->setExpression(source->getExpression());
  updateExpression(newObj->getExpressionPtr(), index, sourceSet, emap);

  //initial expression
  newObj->setInitialExpression(source->getInitialExpression());
  updateExpression(newObj->getInitialExpressionPtr(), index, sourceSet, emap);

  newObj->setNotes(source->getNotes());
  newObj->setMiriamAnnotation(source->getMiriamAnnotation(), newObj->getKey(), source->getKey());


  //add duplicated object to the map
  emap.add(source, newObj);
}

void CModelExpansion::duplicateReaction(const CReaction* source, const std::string & index, const SetOfModelElements & sourceSet, ElementsMap & emap)
{
  //if the source object has already been duplicated: do nothing
  if (emap.exists(source))
    return;

  //try creating the object until we find a name that is not yet used
  CReaction* newObj;
  std::ostringstream infix;

  do
    {
      std::ostringstream name;
      name << source->getObjectName() << infix.str() << index;
      newObj = mpModel->createReaction(name.str());
      infix << "_";
    }
  while (!newObj);

  //now copy the chemical equation
  size_t i;

  for (i = 0; i < source->getChemEq().getSubstrates().size(); ++i)
    {
      const CChemEqElement * sourceElement = source->getChemEq().getSubstrates()[i];
      const CMetab* pMetab = NULL;

      if (sourceSet.contains(sourceElement->getMetabolite()))
        {
          if (!emap.exists(sourceElement->getMetabolite()))
            duplicateMetab(sourceElement->getMetabolite(), index, sourceSet, emap);

          pMetab = dynamic_cast<const CMetab*>(emap.getDuplicatePtr(sourceElement->getMetabolite()));
        }
      else //add the original metab
        {
          pMetab = sourceElement->getMetabolite();
        }

      if (pMetab)
        newObj->addSubstrate(pMetab->getKey(), sourceElement->getMultiplicity());
    }

  for (i = 0; i < source->getChemEq().getProducts().size(); ++i)
    {
      const CChemEqElement * sourceElement = source->getChemEq().getProducts()[i];
      const CMetab* pMetab = NULL;

      if (sourceSet.contains(sourceElement->getMetabolite()))
        {
          if (!emap.exists(sourceElement->getMetabolite()))
            duplicateMetab(sourceElement->getMetabolite(), index, sourceSet, emap);

          pMetab = dynamic_cast<const CMetab*>(emap.getDuplicatePtr(sourceElement->getMetabolite()));
        }
      else //add the original metab
        {
          pMetab = sourceElement->getMetabolite();
        }

      if (pMetab)
        newObj->addProduct(pMetab->getKey(), sourceElement->getMultiplicity());
    }

  for (i = 0; i < source->getChemEq().getModifiers().size(); ++i)
    {
      const CChemEqElement * sourceElement = source->getChemEq().getModifiers()[i];
      const CMetab* pMetab = NULL;

      if (sourceSet.contains(sourceElement->getMetabolite()))
        {
          if (!emap.exists(sourceElement->getMetabolite()))
            duplicateMetab(sourceElement->getMetabolite(), index, sourceSet, emap);

          pMetab = dynamic_cast<const CMetab*>(emap.getDuplicatePtr(sourceElement->getMetabolite()));
        }
      else //add the original metab
        {
          pMetab = sourceElement->getMetabolite();
        }

      if (pMetab)
        newObj->addModifier(pMetab->getKey());
    }

  newObj->setReversible(source->isReversible());

  //set the kinetic function
  newObj->setFunction(const_cast<CFunction*>(source->getFunction()));

  //mapping and local parameters
  for (i = 0; i < newObj->getFunctionParameters().size(); ++i)
    {
      switch (newObj->getFunctionParameters()[i]->getUsage())
        {
          case CFunctionParameter::SUBSTRATE:
          case CFunctionParameter::PRODUCT:
          case CFunctionParameter::MODIFIER:
          {
            bool isVector = (newObj->getFunctionParameters()[i]->getType() == CFunctionParameter::VFLOAT64);

            if (isVector)
              newObj->clearParameterMapping(i);

            size_t k;

            for (k = 0; k < source->getParameterMappings()[i].size(); ++k)
              {
                //we assume that by now the metab was copied if necessary.
                //therefore we only need to check the map.
                std::string targetKey;

                if (emap.exists(source->getParameterMappings()[i][k]))
                  targetKey = emap.getDuplicateKey(source->getParameterMappings()[i][k]);
                else
                  targetKey = source->getParameterMappings()[i][k];

                if (isVector)
                  newObj->addParameterMapping(i, targetKey);
                else
                  newObj->setParameterMapping(i, targetKey);
              }
          }
          break;

          case CFunctionParameter::TIME:
            newObj->setParameterMapping(i, source->getParameterMappings()[i][0]);
            break;

          case CFunctionParameter::VOLUME:
            if (sourceSet.contains(source->getParameterMappings()[i][0]))
              {
                if (!emap.exists(source->getParameterMappings()[i][0]))
                  {
                    const CCompartment* pSource = dynamic_cast<const CCompartment*>(
                                                    (CCopasiRootContainer::getKeyFactory()->get(source->getParameterMappings()[i][0])));
                    duplicateCompartment(pSource, index, sourceSet, emap);
                  }

                newObj->setParameterMapping(i, emap.getDuplicateKey(source->getParameterMappings()[i][0]));
              }
            else //add the original metab
              {
                newObj->setParameterMapping(i, source->getParameterMappings()[i][0]);
              }

            break;

          case CFunctionParameter::PARAMETER:
            if (newObj->isLocalParameter(i))
              {
                //just copy the value
                newObj->setParameterValue(newObj->getFunctionParameters()[i]->getObjectName(),
                                          source->getParameterValue(newObj->getFunctionParameters()[i]->getObjectName()));
              }
            else
              {
                if (sourceSet.contains(source->getParameterMappings()[i][0]))
                  {
                    if (!emap.exists(source->getParameterMappings()[i][0]))
                      {
                        const CModelValue* pSource = dynamic_cast<const CModelValue*>(
                                                        (CCopasiRootContainer::getKeyFactory()->get(source->getParameterMappings()[i][0])));
                        duplicateGlobalQuantity(pSource, index, sourceSet, emap);
                      }

                    newObj->setParameterMapping(i, emap.getDuplicateKey(source->getParameterMappings()[i][0]));
                  }
                else //add the original global quantity
                  {
                    newObj->setParameterMapping(i, source->getParameterMappings()[i][0]);
                  }
              }

            break;

          default:
            break;
        }
    }

  newObj->setNotes(source->getNotes());
  newObj->setMiriamAnnotation(source->getMiriamAnnotation(), newObj->getKey(), source->getKey());

  //add duplicated object to the map
  emap.add(source, newObj);
}

void CModelExpansion::duplicateGlobalQuantity(const CModelValue* source, const std::string & index, const SetOfModelElements & sourceSet, ElementsMap & emap)
{
  //if the source object has already been duplicated: do nothing
  if (emap.exists(source))
    return;

  //try creating the object until we find a name that is not yet used
  CModelEntity* newObj;
  std::ostringstream infix;

  do
    {
      std::ostringstream name;
      name << source->getObjectName() << infix.str() << index;
      newObj = mpModel->createModelValue(name.str(), source->getInitialValue());
      infix << "_";
    }
  while (!newObj);

  //status
  newObj->setStatus(source->getStatus());

  //expression (for assignment or ODE)
  newObj->setExpression(source->getExpression());
  updateExpression(newObj->getExpressionPtr(), index, sourceSet, emap);

  //initial expression
  newObj->setInitialExpression(source->getInitialExpression());
  updateExpression(newObj->getInitialExpressionPtr(), index, sourceSet, emap);

  newObj->setNotes(source->getNotes());
  newObj->setMiriamAnnotation(source->getMiriamAnnotation(), newObj->getKey(), source->getKey());

  //add duplicated object to the map
  emap.add(source, newObj);
}

void CModelExpansion::duplicateEvent(CEvent* source, const std::string & index, const SetOfModelElements & sourceSet, ElementsMap & emap)
{
  //if the source object has already been duplicated: do nothing
  if (emap.exists(source))
    return;

  CEvent* newObj = NULL;

  if (expressionContainsObject(source->getTriggerExpressionPtr(), sourceSet)
      || expressionContainsObject(source->getDelayExpressionPtr(), sourceSet))
    {
      //we need to duplicate the event itself (because the trigger refers to a duplicated object)

      //try creating the object until we find a name that is not yet used
      std::ostringstream infix;

      do
        {
          std::ostringstream name;
          name << source->getObjectName() << infix.str() << index;
          newObj = mpModel->createEvent(name.str());
          infix << "_";
        }
      while (!newObj);

      //now do the trigger
      newObj->setTriggerExpression(source->getTriggerExpression());
      newObj->getTriggerExpressionPtr()->compile(); //I don't know why this is necessary
      updateExpression(newObj->getTriggerExpressionPtr(), index, sourceSet, emap);

      //delay
      newObj->setDelayExpression(source->getDelayExpression());
      newObj->getDelayExpressionPtr()->compile(); //I don't know why this is necessary
      updateExpression(newObj->getDelayExpressionPtr(), index, sourceSet, emap);

      newObj->setDelayAssignment(source->getDelayAssignment());
    }
  else
    newObj = source; //no copying necessary

  //now the event assignments...
  size_t i;

  for (i = 0; i < source->getAssignments().size(); ++i)
    {
      const CEventAssignment* pSourceAssignment = source->getAssignments()[i];

      //const CModelEntity * pSourceTarget = dynamic_cast<const CModelEntity * >(CCopasiRootContainer::getKeyFactory()->get(pSourceAssignment->getTargetKey()));
      if (sourceSet.contains(pSourceAssignment->getTargetKey()))
        {
          //we assume that the duplicate of the target object already exists.
          //this should be true since events are duplicated last.
          if (!emap.exists(pSourceAssignment->getTargetKey()))
            continue;

          //create duplicate of assignment (this can be either in the original event or in the
          //duplicate of an event)
          CEventAssignment * pNewAssignment = new CEventAssignment(emap.getDuplicateKey(pSourceAssignment->getTargetKey()));
          newObj->getAssignments().add(pNewAssignment, true);

          //we do an assumption:
          //It should not happen that the assignment expression contains a reference to an object that is duplicated,
          //but the assignment target is not duplicated.

          //now copy the expression
          pNewAssignment->setExpression(pSourceAssignment->getExpression());
          pNewAssignment->getExpressionPtr()->compile();
          updateExpression(pNewAssignment->getExpressionPtr(), index, sourceSet, emap);
        }
    }

  newObj->setNotes(source->getNotes());
  newObj->setMiriamAnnotation(source->getMiriamAnnotation(), newObj->getKey(), source->getKey());

  //add duplicated object to the map
  emap.add(source, newObj);
}

void CModelExpansion::updateExpression(CExpression* exp, const std::string & index, const SetOfModelElements & sourceSet, ElementsMap & emap)
{
  if (!exp)
    return;

  //we loop through the complete expression
  std::vector< CEvaluationNode * >::const_iterator it = exp->getNodeList().begin();
  std::vector< CEvaluationNode * >::const_iterator end = exp->getNodeList().end();

  for (; it != end; ++it)
    {
      CEvaluationNodeObject * node = dynamic_cast<CEvaluationNodeObject*>(*it);

      if (!node)
        continue;

      //std::cout << node->getData() << std::endl;
      const CCopasiObject * pObj = dynamic_cast<const CCopasiObject*>(node->getObjectInterfacePtr());
      std::string refname = "";
      std::string reftype = "";

      if (pObj)
        {
          refname = pObj->getObjectName();
          reftype = pObj->getObjectType();
          pObj = pObj->getObjectParent();
        }

      //is the object one that is/should be copied?
      if (sourceSet.contains(pObj))
        {
          if (!emap.exists(pObj))
            {
              //we have to create the duplicate
              std::cout << "!!!" << std::endl;

              if (dynamic_cast<const CCompartment*>(pObj))
                duplicateCompartment(dynamic_cast<const CCompartment*>(pObj), index, sourceSet, emap);

              if (dynamic_cast<const CMetab*>(pObj))
                duplicateMetab(dynamic_cast<const CMetab*>(pObj), index, sourceSet, emap);

              if (dynamic_cast<const CModelValue*>(pObj))
                duplicateGlobalQuantity(dynamic_cast<const CModelValue*>(pObj), index, sourceSet, emap);

              if (dynamic_cast<const CReaction*>(pObj))
                duplicateReaction(dynamic_cast<const CReaction*>(pObj), index, sourceSet, emap);
            }

          //find the duplicate
          const CCopasiObject* duplicate = emap.getDuplicatePtr(pObj);

          if (duplicate)
            {
              //get the reference object
              const CCopasiObject* pRef = dynamic_cast<const CCopasiObject*>(duplicate->getObject(reftype + "=" + refname));

              //update the node
              if (pRef)
                node->setData("<" + pRef->getCN() + ">");

              //std::cout << node->getData() << std::endl;
            }
        }
    }
}

bool CModelExpansion::expressionContainsObject(const CExpression* exp, const SetOfModelElements & sourceSet)
{
  if (!exp)
    return false;

  //we loop through the complete expression
  std::vector< CEvaluationNode * >::const_iterator it = exp->getNodeList().begin();
  std::vector< CEvaluationNode * >::const_iterator end = exp->getNodeList().end();

  for (; it != end; ++it)
    {
      CEvaluationNodeObject * node = dynamic_cast<CEvaluationNodeObject*>(*it);

      if (!node)
        continue;

      //std::cout << node->getData() << std::endl;
      const CCopasiObject * pObj = dynamic_cast<const CCopasiObject*>(node->getObjectInterfacePtr());

      if (pObj)
        {
          pObj = pObj->getObjectParent();
        }

      //is the object one that should be copied?
      if (sourceSet.contains(pObj))
        return true;
    }

  return false;
}

void CModelExpansion::createDiffusionReaction(const std::string & name,
    const std::string & metabkey1, const std::string & metabkey2,
    const std::string & parameterkey)
{
  //try creating the object until we find a name that is not yet used
  CReaction* newObj;
  std::ostringstream name_;
  name_ << name;

  do
    {
      newObj = mpModel->createReaction(name_.str());
      name_ << "_";
    }
  while (!newObj);

  newObj->setReversible(true);
  newObj->addSubstrate(metabkey1, 1);
  newObj->addProduct(metabkey2, 1);
  newObj->setFunction("Mass action (reversible)");
  newObj->addParameterMapping("substrate", metabkey1);
  newObj->addParameterMapping("product", metabkey2);
  newObj->setParameterMapping(0, parameterkey);
  newObj->setParameterMapping(2, parameterkey);
}

void CModelExpansion::replaceInModel(const ElementsMap & emap, bool remove)
{
  if (!mpModel)
    return;
  
  size_t i;
  for (i=0; i<mpModel->getCompartments().size(); ++i)
    replaceInCompartment(mpModel->getCompartments()[i], emap);
  std::vector<CMetab*> metvec;
  for (i=0; i<mpModel->getMetabolites().size(); ++i)
    metvec.push_back(mpModel->getMetabolites()[i]);
  for (i=0; i<metvec.size(); ++i)
    replaceInMetab(metvec[i], emap);
  for (i=0; i<mpModel->getReactions().size(); ++i)
    replaceInReaction(mpModel->getReactions()[i], emap);
  for (i=0; i<mpModel->getModelValues().size(); ++i)
    replaceInModelEntity(mpModel->getModelValues()[i], emap);
  for (i=0; i<mpModel->getEvents().size(); ++i)
    replaceInEvent(mpModel->getEvents()[i], emap);
  
  mpModel->forceCompile(NULL);
  
  if (remove)
    {
    std::map<const CCopasiObject*, CCopasiObject*>::const_iterator it;
    for (it = emap.getMap().begin(); it !=emap.getMap().end(); ++it)
      {
      if (dynamic_cast<const CCompartment*>(it->first))
        {
        mpModel->removeCompartment(const_cast<CCompartment*>(dynamic_cast<const CCompartment*>(it->first)), true);
        break;
        }
      if (dynamic_cast<const CMetab*>(it->first))
        {
        mpModel->removeMetabolite(const_cast<CMetab*>(dynamic_cast<const CMetab*>(it->first)), true);
        break;
        }
      if (dynamic_cast<const CReaction*>(it->first))
        {
        mpModel->removeReaction(const_cast<CReaction*>(dynamic_cast<const CReaction*>(it->first)), true);
        break;
        }
      if (dynamic_cast<const CModelValue*>(it->first))
        {
        mpModel->removeModelValue(const_cast<CModelValue*>(dynamic_cast<const CModelValue*>(it->first)), true);
        break;
        }
      if (dynamic_cast<const CEvent*>(it->first))
        {
        mpModel->removeEvent(const_cast<CEvent*>(dynamic_cast<const CEvent*>(it->first)), true);
        break;
        }
      }
    }
  
}

void CModelExpansion::replaceInCompartment(CCompartment* pX, const ElementsMap & emap)
{
  replaceInModelEntity(pX, emap);
}

void CModelExpansion::replaceInMetab(CMetab* pX, const ElementsMap & emap)
{
  replaceInModelEntity(pX, emap);

  //is the metab in a compartment that needs to be replaced?
  if (emap.exists( pX->getCompartment()))
    {
    //move the metab to the new compartment
    CCompartment* oldComp = const_cast<CCompartment*>( pX->getCompartment());
    CCompartment* newComp = dynamic_cast<CCompartment*>( emap.getDuplicatePtr(pX->getCompartment()));
    bool success=false;
    do
      {
      success = newComp->addMetabolite(pX);

      if (success)
        {
        oldComp->getMetabolites().remove(pX->getObjectName());
        mpModel->setCompileFlag();
        mpModel->initializeMetabolites();
        }
      else
        {
        //rename the metab so that it can be added to the new compartment
        pX->setObjectName(pX->getObjectName()+"_");
        //TODO: check if the renaming actually worked
        }
      
      }
    while (!success);
    
    }
}

void CModelExpansion::replaceInReaction(CReaction* pX, const ElementsMap & emap)
{
  //replace in the chemical equation
  size_t i;
  for(i=0; i<pX->getChemEq().getSubstrates().size(); ++i)
    {
    CChemEqElement * sourceElement = pX->getChemEq().getSubstrates()[i];
    const CMetab* pMetab = dynamic_cast<const CMetab*>(emap.getDuplicatePtr(sourceElement->getMetabolite()));
    if (pMetab)
      {
      sourceElement->setMetabolite(pMetab->getKey());
      }
    }
  for(i=0; i<pX->getChemEq().getProducts().size(); ++i)
    {
    CChemEqElement * sourceElement = pX->getChemEq().getProducts()[i];
    const CMetab* pMetab = dynamic_cast<const CMetab*>(emap.getDuplicatePtr(sourceElement->getMetabolite()));
    if (pMetab)
      {
      sourceElement->setMetabolite(pMetab->getKey());
      }
    }
  for(i=0; i<pX->getChemEq().getModifiers().size(); ++i)
    {
    CChemEqElement * sourceElement = pX->getChemEq().getModifiers()[i];
    const CMetab* pMetab = dynamic_cast<const CMetab*>(emap.getDuplicatePtr(sourceElement->getMetabolite()));
    if (pMetab)
      {
      sourceElement->setMetabolite(pMetab->getKey());
      }
    }
  
  //mapping and local parameters
  for (i = 0; i < pX->getFunctionParameters().size(); ++i)
    {
    switch (pX->getFunctionParameters()[i]->getUsage())
      {
        case CFunctionParameter::SUBSTRATE:
        case CFunctionParameter::PRODUCT:
        case CFunctionParameter::MODIFIER:
        case CFunctionParameter::VOLUME:
        case CFunctionParameter::PARAMETER:
        {
        size_t k;
        for (k = 0; k < pX->getParameterMappings()[i].size(); ++k)
          {
          std::string targetKey = emap.getDuplicateKey(pX->getParameterMappings()[i][k]);
          if (targetKey != "")
            pX->getParameterMappings()[i][k]=targetKey;
          }
        }
        break;
        
        case CFunctionParameter::TIME:
        default:
        break;
      }
    
    }
  
}

void CModelExpansion::replaceInModelEntity(CModelEntity* pX, const ElementsMap & emap)
{
  //expression (for assignment or ODE)
  replaceInExpression(pX->getExpressionPtr(), emap);
  
  //initial expression
  replaceInExpression(pX->getInitialExpressionPtr(), emap);
}

void CModelExpansion::replaceInEvent(CEvent* pX, const ElementsMap & emap)
{
  replaceInExpression(pX->getTriggerExpressionPtr(), emap);
  replaceInExpression(pX->getDelayExpressionPtr(), emap);
  
  //now the event assignments...
  size_t i;
  for (i=0; i < pX->getAssignments().size(); ++i)
    {
    CEventAssignment* pAssignment = pX->getAssignments()[i];
    replaceInExpression(pAssignment->getExpressionPtr(), emap);
    
    std::string replacekey = emap.getDuplicateKey(pAssignment->getTargetKey());
    if (replacekey != "")
      pAssignment->setTargetKey(replacekey);
    }
}


void CModelExpansion::replaceInExpression(CExpression* exp, const ElementsMap & emap)
{
  if (!exp)
    return;
  
  //we loop through the complete expression
  std::vector< CEvaluationNode * >::const_iterator it = exp->getNodeList().begin();
  std::vector< CEvaluationNode * >::const_iterator end = exp->getNodeList().end();
  for (; it != end; ++it)
    {
    CEvaluationNodeObject * node = dynamic_cast<CEvaluationNodeObject*>(*it);
    if (!node)
      continue;
    
    //std::cout << node->getData() << std::endl;
    const CCopasiObject * pObj = dynamic_cast<const CCopasiObject*>(node->getObjectInterfacePtr());
    std::string refname = "";
    std::string reftype = "";
    if (pObj)
      {
      refname = pObj->getObjectName();
      reftype = pObj->getObjectType();
      pObj = pObj->getObjectParent();
      }
    
    const CCopasiObject* duplicate = emap.getDuplicatePtr(pObj);
    if (duplicate)
        {
        //get the reference object
        const CCopasiObject* pRef = dynamic_cast<const CCopasiObject*>(duplicate->getObject(reftype + "=" + refname));
        //update the node
        if (pRef)
          node->setData("<" + pRef->getCN() + ">");
        //std::cout << node->getData() << std::endl;
        }
    }
}

