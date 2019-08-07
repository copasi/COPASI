// Copyright (C) 2019 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include <locale>

#include "CModelExpansion.h"

#include "CModel.h"
#include "copasi/function/CExpression.h"
#include "copasi/core/CDataObject.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/undo/CUndoData.h"

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

void CModelExpansion::SetOfModelElements::setModel(const CModel* x)
{
  mpModel = x;
}

bool CModelExpansion::SetOfModelElements::addObject(const CDataObject* x)
{
  if (dynamic_cast<const CCompartment*>(x))
    {
      addCompartment(dynamic_cast<const CCompartment*>(x));
      return true;
    }

  if (dynamic_cast<const CMetab*>(x))
    {
      addMetab(dynamic_cast<const CMetab*>(x));
      return true;
    }

  if (dynamic_cast<const CReaction*>(x))
    {
      addReaction(dynamic_cast<const CReaction*>(x));
      return true;
    }

  if (dynamic_cast<const CModelValue*>(x))
    {
      addGlobalQuantity(dynamic_cast<const CModelValue*>(x));
      return true;
    }

  if (dynamic_cast<const CEvent*>(x))
    {
      addEvent(dynamic_cast<const CEvent*>(x));
      return true;
    }

  if (dynamic_cast<const CModel*>(x))
    {
      setModel(dynamic_cast<const CModel*>(x));
      return true;
    }

  return false;
}

bool CModelExpansion::SetOfModelElements::contains(const CDataObject* x) const
{
  if (mpModel == x)
    return true;

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
  const CDataObject* tmp = CRootContainer::getKeyFactory()->get(key);

  if (tmp)
    return contains(tmp);
  else
    return false;
}

void CModelExpansion::SetOfModelElements::fillDependencies(const CModel* pModel)
{
  if (!pModel) return;

  //create a combined set of all elements in the SetOfModelElements and their direct descendents.
  //this set is the basis for determining all object that depend on the objects in the SetOfModelElements.
  CDataObject::DataObjectSet Descendants;

  std::set< const CCompartment * >::const_iterator itComp;

  for (itComp = mCompartments.begin(); itComp != mCompartments.end(); ++itComp)
    {
      Descendants.insert(*itComp);
      (*itComp)->getDescendants(Descendants);
    }

  std::set< const CMetab * >::const_iterator itMetab;

  for (itMetab = mMetabs.begin(); itMetab != mMetabs.end(); ++itMetab)
    {
      Descendants.insert(*itMetab);
      (*itMetab)->getDescendants(Descendants);
    }

  std::set< const CReaction * >::const_iterator itReac;

  for (itReac = mReactions.begin(); itReac != mReactions.end(); ++itReac)
    {
      Descendants.insert(*itReac);
      (*itReac)->getDescendants(Descendants);
    }

  std::set< const CModelValue * >::const_iterator itQuant;

  for (itQuant = mGlobalQuantities.begin(); itQuant != mGlobalQuantities.end(); ++itQuant)
    {
      Descendants.insert(*itQuant);
      (*itQuant)->getDescendants(Descendants);
    }

  //for the model
  if (mpModel)
    {
      Descendants.insert(mpModel);
      mpModel->getDescendants(Descendants);
    }

  CDataObject::ObjectSet CombinedSet(Descendants.begin(), Descendants.end());

  //ask the model for the dependencies

  std::set< const CDataObject * > reacs, metabs, comps, values, events, eventAssignments;
  pModel->appendAllDependents(CombinedSet, reacs, metabs, comps, values, events, eventAssignments);

  //incorporate the results into the local sets
  std::set< const CDataObject * >::const_iterator it;

  for (it = reacs.begin(); it != reacs.end(); ++it)
    addReaction(dynamic_cast< const CReaction * >(*it));

  for (it = metabs.begin(); it != metabs.end(); ++it)
    addMetab(dynamic_cast< const CMetab * >(*it));

  for (it = comps.begin(); it != comps.end(); ++it)
    addCompartment(dynamic_cast< const CCompartment * >(*it));

  for (it = values.begin(); it != values.end(); ++it)
    addGlobalQuantity(dynamic_cast<const CModelValue*>(*it));

  for (it = events.begin(); it != events.end(); ++it)
    addEvent(dynamic_cast< const CEvent * >(*it));

  for (it = eventAssignments.begin(); it != eventAssignments.end(); ++it)
    {
      const CEvent * pEvent = dynamic_cast< const CEvent * >((*it)->getObjectAncestor("Event"));

      if (pEvent != NULL)
        {
          addEvent(pEvent);
        }
    }
}

void CModelExpansion::SetOfModelElements::fillComplete(const CModel* pModel)
{
  if (!pModel)
    return;

  size_t i;
  setModel(pModel);

  for (i = 0; i < pModel->getCompartments().size(); ++i)
    addCompartment(&pModel->getCompartments()[i]);

  for (i = 0; i < pModel->getMetabolites().size(); ++i)
    addMetab(&pModel->getMetabolites()[i]);

  for (i = 0; i < pModel->getReactions().size(); ++i)
    addReaction(&pModel->getReactions()[i]);

  for (i = 0; i < pModel->getModelValues().size(); ++i)
    addGlobalQuantity(&pModel->getModelValues()[i]);

  for (i = 0; i < pModel->getEvents().size(); ++i)
    addEvent(&pModel->getEvents()[i]);
}

//***************************************************************************************

bool CModelExpansion::ElementsMap::exists(const CDataObject* source) const
{
  std::map< const CDataObject *, const CDataObject * >::const_iterator it;
  it = mMap.find(source);
  return (it != mMap.end() && it->second != NULL);
}

bool CModelExpansion::ElementsMap::exists(const std::string & sourceKey) const
{
  const CDataObject* tmp = CRootContainer::getKeyFactory()->get(sourceKey);
  return exists(tmp);
}

void CModelExpansion::ElementsMap::add(const CDataObject* source, const CDataObject* copy)
{
  mMap[source] = copy;
}

const CDataObject* CModelExpansion::ElementsMap::getDuplicateFromObject(const CDataObject* source) const
{
  std::map<const CDataObject*, const CDataObject * >::const_iterator it;
  it = mMap.find(source);

  if (it != mMap.end())
    return it->second;
  else
    return NULL;
}

CCommonName CModelExpansion::ElementsMap::getDuplicateFromCN(const CCommonName & cn) const
{
  const CDataObject* tmp = CObjectInterface::DataObject(CRootContainer::getRoot()->getObject(cn));

  if (tmp != NULL)
    {
      const CDataObject* retObj = getDuplicateFromObject(tmp);

      if (retObj != NULL)
        return retObj->getCN();
    }

  return CCommonName("");
}

const std::map<const CDataObject*, const CDataObject*> & CModelExpansion::ElementsMap::getMap() const
{
  return mMap;
}

//***************************************************************************************

CModelExpansion::CModelExpansion(CModel* pModel)
  : mpModel(pModel),
    mpSourceModel(NULL)
{
}

void CModelExpansion::setModel(CModel* pModel)
{
  mpModel = pModel;
}

void CModelExpansion::simpleCall(const CCompartment * source, std::vector< const CDataObject *  > listOfMetabolites,  int /* mult */, bool /* diff */)
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
      const CDataObject * pMetab =  listOfMetabolites[0];

      //create a global quantity that will be used as the diffusion parameter
      CModelValue* pMV = mpModel->createModelValue("Diff_glu", 7);

      //create first reaction.
      //the maps let us find the duplicates of the original metab.
      createDiffusionReaction("Diff_glu[1-2]",
                              map_1.getDuplicateFromObject(pMetab),
                              map_2.getDuplicateFromObject(pMetab), pMV);

      //create second reaction (this can easily be put in a loop)
      createDiffusionReaction("Diff_glu[2-3]",
                              map_2.getDuplicateFromObject(pMetab),
                              map_3.getDuplicateFromObject(pMetab), pMV);
    }

  mpModel->compileIfNecessary(NULL);
}

void CModelExpansion::createLinearArray(const SetOfModelElements & source, size_t n, const std::set< const CDataObject * > & setOfMetabolites)
{
  if (!mpModel) return;

  //create global quantities for the diffusion constants
  std::vector<CModelValue*> diffusionConstants;
  std::set< const CDataObject * >::const_iterator itMetab;

  for (itMetab = setOfMetabolites.begin(); itMetab != setOfMetabolites.end(); ++itMetab)
    {
      //try creating the object until we find a name that is not yet used
      CModelValue* newObj;
      const CMetab * pMetab = dynamic_cast< const CMetab * >(*itMetab);

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
                                      maps[i - 1].getDuplicateFromObject(*itMetab),
                                      maps[i].getDuplicateFromObject(*itMetab), *itDiff);
            }
        }
    }

  mpModel->compileIfNecessary(NULL);
}

void CModelExpansion::createRectangularArray(const SetOfModelElements & source, size_t nx, size_t ny, const std::set< const CDataObject * > & setOfMetabolites)
{
  if (!mpModel) return;

  //create global quantities for the diffusion constants
  std::vector<CModelValue*> diffusionConstants;
  std::set< const CDataObject * >::const_iterator itMetab;

  for (itMetab = setOfMetabolites.begin(); itMetab != setOfMetabolites.end(); ++itMetab)
    {
      //try creating the object until we find a name that is not yet used
      CModelValue * newObj;
      const CMetab * pMetab = dynamic_cast< const CMetab * >(*itMetab);

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
                                        maps[i - 1][j].getDuplicateFromObject(*itMetab),
                                        maps[i][j].getDuplicateFromObject(*itMetab), *itDiff);
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
                                        maps[i][j - 1].getDuplicateFromObject(*itMetab),
                                        maps[i][j].getDuplicateFromObject(*itMetab), *itDiff);
              }
          }
      }

  mpModel->compileIfNecessary(NULL);
}

std::set< const CDataObject * > CModelExpansion::copyCompleteModel(const CModel* pSourceModel)
{
  mpSourceModel = pSourceModel;

  SetOfModelElements sourceElements;
  sourceElements.fillComplete(pSourceModel);
  ElementsMap map;
  map.add(pSourceModel, mpModel);
  duplicate(sourceElements, "[merge]", map);
  mpModel->compileIfNecessary(NULL);

  std::set< const CDataObject * > ret;
  std::map< const CDataObject *, const CDataObject * >::const_iterator it;

  for (it = map.getMap().begin(); it != map.getMap().end(); ++it)
    {
      ret.insert(it->second);
      //std::cout << it->second->getObjectDisplayName() << std::endl;
    }

  return ret;
}

CUndoData CModelExpansion::duplicate(const SetOfModelElements & source, const std::string & index, ElementsMap & emap)
{
  CUndoData UndoData;

  std::set<const CCompartment*>::const_iterator itComp;

  for (itComp = source.mCompartments.begin(); itComp != source.mCompartments.end(); ++itComp)
    {
      duplicateCompartment(*itComp, index, source, emap, UndoData);
    }

  std::set<const CMetab*>::const_iterator itMetab;

  for (itMetab = source.mMetabs.begin(); itMetab != source.mMetabs.end(); ++itMetab)
    {
      duplicateMetab(*itMetab, index, source, emap, UndoData);
    }

  std::set<const CReaction*>::const_iterator itReac;

  for (itReac = source.mReactions.begin(); itReac != source.mReactions.end(); ++itReac)
    {
      duplicateReaction(*itReac, index, source, emap, UndoData);
    }

  std::set<const CModelValue*>::const_iterator itME;

  for (itME = source.mGlobalQuantities.begin(); itME != source.mGlobalQuantities.end(); ++itME)
    {
      duplicateGlobalQuantity(*itME, index, source, emap, UndoData);
    }

  std::set<const CEvent*>::const_iterator itEvent;

  for (itEvent = source.mEvents.begin(); itEvent != source.mEvents.end(); ++itEvent)
    {
      duplicateEvent(const_cast<CEvent*>(*itEvent), index, source, emap, UndoData);
      //the event can be changed. Potentially it is not duplicated in its entirety but only some event assignments are duplicated.
    }

  // compilation failed on Win32, need return value for boolean
  return UndoData;
}

void CModelExpansion::duplicateCompartment(const CCompartment* source,
    const std::string & index,
    const SetOfModelElements & sourceSet,
    ElementsMap & emap,
    CUndoData & undoData)
{
  // if there is no source, nothing to do
  if (source == NULL)
    return;

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

  //add duplicated object to the map
  emap.add(source, newObj);

  //now copy the contents of the object
  newObj->setDimensionality(source->getDimensionality());

  //status
  newObj->setStatus(source->getStatus());

  //expression (for assignment or ODE)
  newObj->setExpression(source->getExpression());
  updateExpression(newObj->getExpressionPtr(), index, sourceSet, emap, undoData);

  //initial expression
  newObj->setInitialExpression(source->getInitialExpression());
  updateExpression(newObj->getInitialExpressionPtr(), index, sourceSet, emap, undoData);

  //noise expression
  newObj->setHasNoise(source->hasNoise());
  newObj->setNoiseExpression(source->getNoiseExpression());
  updateExpression(newObj->getNoiseExpressionPtr(), index, sourceSet, emap, undoData);

  newObj->setNotes(source->getNotes());
  newObj->setMiriamAnnotation(source->getMiriamAnnotation(), newObj->getKey(), source->getKey());

  if (undoData.empty())
    {
      undoData = CUndoData(CUndoData::Type::INSERT, newObj);
    }
  else
    {
      undoData.addPostProcessData(CUndoData(CUndoData::Type::INSERT, newObj));
    }
}

void CModelExpansion::duplicateMetab(const CMetab* source,
                                     const std::string & index,
                                     const SetOfModelElements & sourceSet,
                                     ElementsMap & emap,
                                     CUndoData & undoData)
{

  // if there is no source, nothing to do
  if (source == NULL)
    return;

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
      //this should never happen when copying across models.
      nameflag = true; //metab needs renaming
    }
  else //use a copy of the parent compartment
    {
      nameflag = false; //no renaming necessary (since the copy is in a different compartment)

      //create copy if it does not exist
      if (!emap.exists(sourceParent))
        {
          duplicateCompartment(sourceParent, index, sourceSet, emap, undoData);
        }

      parent = dynamic_cast< const CCompartment * >(emap.getDuplicateFromObject(sourceParent));
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

  //add duplicated object to the map
  emap.add(source, newObj);

  //expression (for assignment or ODE)
  newObj->setExpression(source->getExpression());
  updateExpression(newObj->getExpressionPtr(), index, sourceSet, emap, undoData);

  //initial expression
  newObj->setInitialExpression(source->getInitialExpression());
  updateExpression(newObj->getInitialExpressionPtr(), index, sourceSet, emap, undoData);

  //noise expression
  newObj->setHasNoise(source->hasNoise());
  newObj->setNoiseExpression(source->getNoiseExpression());
  updateExpression(newObj->getNoiseExpressionPtr(), index, sourceSet, emap, undoData);

  newObj->setNotes(source->getNotes());
  newObj->setMiriamAnnotation(source->getMiriamAnnotation(), newObj->getKey(), source->getKey());

  if (undoData.empty())
    {
      undoData = CUndoData(CUndoData::Type::INSERT, newObj);
    }
  else
    {
      undoData.addPostProcessData(CUndoData(CUndoData::Type::INSERT, newObj));
    }
}

void CModelExpansion::duplicateReaction(const CReaction* source,
                                        const std::string & index,
                                        const SetOfModelElements & sourceSet,
                                        ElementsMap & emap,
                                        CUndoData & undoData)
{
  // if there is no source, nothing to do
  if (source == NULL)
    return;

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

  //add duplicated object to the map
  emap.add(source, newObj);

  //now copy the chemical equation
  size_t i;

  for (i = 0; i < source->getChemEq().getSubstrates().size(); ++i)
    {
      const CChemEqElement * sourceElement = &source->getChemEq().getSubstrates()[i];
      const CMetab* pMetab = NULL;

      if (sourceSet.contains(sourceElement->getMetabolite()))
        {
          if (!emap.exists(sourceElement->getMetabolite()))
            duplicateMetab(sourceElement->getMetabolite(), index, sourceSet, emap, undoData);

          pMetab = dynamic_cast<const CMetab*>(emap.getDuplicateFromObject(sourceElement->getMetabolite()));
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
      const CChemEqElement * sourceElement = &source->getChemEq().getProducts()[i];
      const CMetab* pMetab = NULL;

      if (sourceSet.contains(sourceElement->getMetabolite()))
        {
          if (!emap.exists(sourceElement->getMetabolite()))
            duplicateMetab(sourceElement->getMetabolite(), index, sourceSet, emap, undoData);

          pMetab = dynamic_cast<const CMetab*>(emap.getDuplicateFromObject(sourceElement->getMetabolite()));
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
      const CChemEqElement * sourceElement = &source->getChemEq().getModifiers()[i];
      const CMetab* pMetab = NULL;

      if (sourceSet.contains(sourceElement->getMetabolite()))
        {
          if (!emap.exists(sourceElement->getMetabolite()))
            duplicateMetab(sourceElement->getMetabolite(), index, sourceSet, emap, undoData);

          pMetab = dynamic_cast<const CMetab*>(emap.getDuplicateFromObject(sourceElement->getMetabolite()));
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
      std::vector< const CDataObject * > Objects;

      switch (newObj->getFunctionParameters()[i]->getUsage())
        {
          case CFunctionParameter::Role::SUBSTRATE:
          case CFunctionParameter::Role::PRODUCT:
          case CFunctionParameter::Role::MODIFIER:
          {
            size_t k;

            for (k = 0; k < source->getParameterObjects(i).size(); ++k)
              {
                //we assume that by now the metab was copied if necessary.
                //therefore we only need to check the map.
                const CDataObject * pObject = emap.getDuplicateFromObject(source->getParameterObjects(i)[k]);

                if (pObject == NULL)
                  {
                    pObject = source->getParameterObjects(i)[k];
                  }

                if (pObject != NULL)
                  {
                    Objects.push_back(pObject);
                  }
              }
          }
          break;

          case CFunctionParameter::Role::TIME:
            Objects.push_back(mpModel);
            break;

          case CFunctionParameter::Role::VOLUME:
            if (sourceSet.contains(source->getParameterObjects(i)[0]))
              {
                if (!emap.exists(source->getParameterObjects(i)[0]))
                  {
                    const CCompartment* pSource = dynamic_cast<const CCompartment*>(source->getParameterObjects(i)[0]);
                    duplicateCompartment(pSource, index, sourceSet, emap, undoData);
                  }

                Objects.push_back(emap.getDuplicateFromObject(source->getParameterObjects(i)[0]));
              }
            else //add the original metab
              {
                Objects.push_back(source->getParameterObjects(i)[0]);
              }

            break;

          case CFunctionParameter::Role::PARAMETER:
            if (source->isLocalParameter(i))
              {
                //just copy the value
                newObj->setParameterValue(newObj->getFunctionParameters()[i]->getObjectName(),
                                          source->getParameterValue(newObj->getFunctionParameters()[i]->getObjectName()));

                CCopasiParameter * pParameter = newObj->getParameters().getParameter(newObj->getFunctionParameters()[i]->getObjectName());
                assert(pParameter != NULL);

                Objects.push_back(pParameter);
              }
            else
              {
                if (sourceSet.contains(source->getParameterObjects(i)[0]))
                  {
                    if (!emap.exists(source->getParameterObjects(i)[0]))
                      {
                        const CModelValue* pSource = dynamic_cast<const CModelValue*>(source->getParameterObjects(i)[0]);
                        duplicateGlobalQuantity(pSource, index, sourceSet, emap, undoData);
                      }

                    Objects.push_back(emap.getDuplicateFromObject(source->getParameterObjects(i)[0]));
                  }
                else //add the original global quantity
                  {
                    Objects.push_back(source->getParameterObjects(i)[0]);
                  }
              }

            break;

          default:
            break;
        }

      newObj->setParameterObjects(i, Objects);
    }

  //noise expression
  newObj->setHasNoise(source->hasNoise());
  newObj->setNoiseExpression(source->getNoiseExpression());
  updateExpression(newObj->getNoiseExpressionPtr(), index, sourceSet, emap, undoData);

  newObj->setFast(source->isFast());

  newObj->setKineticLawUnitType(source->getKineticLawUnitType());

  //Scaling Compartment
  if (sourceSet.contains(source->getScalingCompartment()))
    {
      //create copy if it doesn't exist yet
      if (!emap.exists(source->getScalingCompartment()))
        {
          duplicateCompartment(source->getScalingCompartment(), index, sourceSet, emap, undoData);
        }

      //use copy
      newObj->setScalingCompartment(dynamic_cast<const CCompartment*>(emap.getDuplicateFromObject(source->getScalingCompartment())));
    }
  else //use original
    {
      newObj->setScalingCompartment(source->getScalingCompartment());
    }

  newObj->setNotes(source->getNotes());
  newObj->setMiriamAnnotation(source->getMiriamAnnotation(), newObj->getKey(), source->getKey());

  if (undoData.empty())
    {
      undoData = CUndoData(CUndoData::Type::INSERT, newObj);
    }
  else
    {
      undoData.addPostProcessData(CUndoData(CUndoData::Type::INSERT, newObj));
    }
}

void CModelExpansion::duplicateGlobalQuantity(const CModelValue* source,
    const std::string & index,
    const SetOfModelElements & sourceSet,
    ElementsMap & emap,
    CUndoData & undoData)
{

  // if there is no source, nothing to do
  if (source == NULL)
    return;

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

  //add duplicated object to the map
  emap.add(source, newObj);

  //status
  newObj->setStatus(source->getStatus());

  //expression (for assignment or ODE)
  newObj->setExpression(source->getExpression());
  updateExpression(newObj->getExpressionPtr(), index, sourceSet, emap, undoData);

  //initial expression
  newObj->setInitialExpression(source->getInitialExpression());
  updateExpression(newObj->getInitialExpressionPtr(), index, sourceSet, emap, undoData);

  //noise expression
  newObj->setHasNoise(source->hasNoise());
  newObj->setNoiseExpression(source->getNoiseExpression());
  updateExpression(newObj->getNoiseExpressionPtr(), index, sourceSet, emap, undoData);

  newObj->setNotes(source->getNotes());
  newObj->setMiriamAnnotation(source->getMiriamAnnotation(), newObj->getKey(), source->getKey());

  if (undoData.empty())
    {
      undoData = CUndoData(CUndoData::Type::INSERT, newObj);
    }
  else
    {
      undoData.addPostProcessData(CUndoData(CUndoData::Type::INSERT, newObj));
    }
}

void CModelExpansion::duplicateEvent(CEvent* source,
                                     const std::string & index,
                                     const SetOfModelElements & sourceSet,
                                     ElementsMap & emap,
                                     CUndoData & undoData)
{

  // if there is no source, nothing to do
  if (source == NULL)
    return;

  //if the source object has already been duplicated: do nothing
  if (emap.exists(source))
    return;

  CEvent* newObj = NULL;
  CData OldData;

  if (expressionContainsObject(source->getTriggerExpressionPtr(), sourceSet)
      || expressionContainsObject(source->getDelayExpressionPtr(), sourceSet)
      || expressionContainsObject(source->getPriorityExpressionPtr(), sourceSet)
      || mpModel != source->getObjectAncestor("Model"))
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

      //add duplicated object to the map
      emap.add(source, newObj);

      //now do the trigger
      newObj->setTriggerExpression(source->getTriggerExpression());
      newObj->getTriggerExpressionPtr()->compile(); //I don't know why this is necessary
      updateExpression(newObj->getTriggerExpressionPtr(), index, sourceSet, emap, undoData);

      //delay
      newObj->setDelayExpression(source->getDelayExpression());
      newObj->getDelayExpressionPtr()->compile(); //I don't know why this is necessary
      updateExpression(newObj->getDelayExpressionPtr(), index, sourceSet, emap, undoData);

      newObj->setDelayAssignment(source->getDelayAssignment());
      newObj->setFireAtInitialTime(source->getFireAtInitialTime());
      newObj->setPersistentTrigger(source->getPersistentTrigger());

      //priority
      newObj->setPriorityExpression(source->getPriorityExpression());
      updateExpression(newObj->getPriorityExpressionPtr(), index, sourceSet, emap, undoData);
    }
  else
    {
      OldData = source->toData();
      newObj = source; //no copying necessary

      //add duplicated object to the map
      emap.add(source, newObj);
    }

  //now the event assignments...
  size_t i;

  for (i = 0; i < source->getAssignments().size(); ++i)
    {
      const CEventAssignment* pSourceAssignment = &source->getAssignments()[i];

      const CModelEntity * pSourceTarget = dynamic_cast<const CModelEntity *>(CObjectInterface::DataObject(source->getObjectDataModel() ->getObject(pSourceAssignment->getTargetCN())));

      if (sourceSet.contains(pSourceTarget->getKey()))
        {
          //we assume that the duplicate of the target object already exists.
          //this should be true since events are duplicated last.
          if (!emap.exists(pSourceTarget->getKey()))
            continue;

          //create duplicate of assignment (this can be either in the original event or in the
          //duplicate of an event)
          CEventAssignment * pNewAssignment = new CEventAssignment(emap.getDuplicateFromObject(pSourceTarget)->getKey());
          newObj->getAssignments().add(pNewAssignment, true);

          //we do an assumption:
          //It should not happen that the assignment expression contains a reference to an object that is duplicated,
          //but the assignment target is not duplicated.

          //now copy the expression
          pNewAssignment->setExpression(pSourceAssignment->getExpression());
          pNewAssignment->getExpressionPtr()->compile();
          updateExpression(pNewAssignment->getExpressionPtr(), index, sourceSet, emap, undoData);
        }
      else
        {
          //the assignment target is not duplicated. That means that if the event was duplicated
          //we need to copy the assignment, but not duplicate it.
          //If the event was not duplicated, we do nothing
          if (source != newObj)
            {
              //create duplicate of assignment
              CEventAssignment * pNewAssignment = new CEventAssignment(pSourceTarget->getCN());
              newObj->getAssignments().add(pNewAssignment, true);
              //now copy the expression
              pNewAssignment->setExpression(pSourceAssignment->getExpression());
              pNewAssignment->getExpressionPtr()->compile();
              updateExpression(pNewAssignment->getExpressionPtr(), index, sourceSet, emap, undoData);
            }
        }
    }

  for (i = 0; i < newObj->getAssignments().size(); ++i)
    {
      updateExpression(newObj->getAssignments()[i].getExpressionPtr(), index, sourceSet, emap, undoData);
    }

  newObj->setNotes(source->getNotes());
  newObj->setMiriamAnnotation(source->getMiriamAnnotation(), newObj->getKey(), source->getKey());

  if (newObj != source)
    {
      if (undoData.empty())
        {
          undoData = CUndoData(CUndoData::Type::INSERT, newObj);
        }
      else
        {
          undoData.addPostProcessData(CUndoData(CUndoData::Type::INSERT, newObj));
        }
    }
  else
    {
      CUndoData Change;
      source->createUndoData(Change, CUndoData::Type::CHANGE, OldData);

      if (!Change.empty())
        {
          if (undoData.empty())
            {
              undoData = Change;
            }
          else
            {
              undoData.addPostProcessData(Change);
            }
        }
    }
}

void CModelExpansion::updateExpression(CExpression* exp,
                                       const std::string & index,
                                       const SetOfModelElements & sourceSet,
                                       ElementsMap & emap,
                                       CUndoData & undoData)
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
      const CDataObject * pObj = dynamic_cast<const CDataObject*>(node->getObjectInterfacePtr());
      std::string refname = "";
      std::string reftype = "";

      //when copying between models, pObj=NULL. This is because the expression could not be compiled
      //if it points to an object in a different model.
      //We try to fix this now:
      if (!pObj && mpSourceModel)
        {
          CCommonName cn = node->getObjectCN();

          while (cn.getPrimary().getObjectType() != "Model" && !cn.empty())
            {
              cn = cn.getRemainder();
            }

          pObj = dynamic_cast<const CDataObject*>(mpSourceModel->getObject(cn));
        }

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
              // std::cout << "!!!" << std::endl;

              if (dynamic_cast<const CCompartment*>(pObj))
                duplicateCompartment(dynamic_cast<const CCompartment*>(pObj), index, sourceSet, emap, undoData);

              if (dynamic_cast<const CMetab*>(pObj))
                duplicateMetab(dynamic_cast<const CMetab*>(pObj), index, sourceSet, emap, undoData);

              if (dynamic_cast<const CModelValue*>(pObj))
                duplicateGlobalQuantity(dynamic_cast<const CModelValue*>(pObj), index, sourceSet, emap, undoData);

              if (dynamic_cast<const CReaction*>(pObj))
                duplicateReaction(dynamic_cast<const CReaction*>(pObj), index, sourceSet, emap, undoData);
            }

          //find the duplicate
          const CDataObject* duplicate = emap.getDuplicateFromObject(pObj);

          if (duplicate)
            {
              //get the reference object
              const CDataObject* pRef = dynamic_cast<const CDataObject*>(duplicate->getObject(reftype + "=" + refname));

              //update the node
              if (pRef)
                node->setData("<" + pRef->getCN() + ">");

              // std::cout << node->getData() << std::endl;
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
      const CDataObject * pObj = dynamic_cast<const CDataObject*>(node->getObjectInterfacePtr());

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
    const CDataObject * pSubstrate, const CDataObject * pProduct,
    const CDataObject * pParameter)
{
  if (!mpModel || !pSubstrate || !pProduct)
    return;

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
  newObj->addSubstrate(pSubstrate->getKey(), 1);
  newObj->addProduct(pProduct->getKey(), 1);
  newObj->setFunction("Mass action (reversible)");

  std::vector< const CDataObject * > Objects(1, pSubstrate);
  newObj->setParameterObjects("substrate", Objects);

  Objects[0] = pProduct;
  newObj->setParameterObjects("product", Objects);

  Objects[0] = pParameter;
  newObj->setParameterObjects(0, Objects);
  newObj->setParameterObjects(2, Objects);
}

void CModelExpansion::replaceInModel(const ElementsMap & emap, bool remove)
{
  if (!mpModel)
    return;

  size_t i;

  for (i = 0; i < mpModel->getCompartments().size(); ++i)
    replaceInCompartment(&mpModel->getCompartments()[i], emap);

  std::vector<CMetab*> metvec;

  for (i = 0; i < mpModel->getMetabolites().size(); ++i)
    metvec.push_back(&mpModel->getMetabolites()[i]);

  for (i = 0; i < metvec.size(); ++i)
    replaceInMetab(metvec[i], emap);

  for (i = 0; i < mpModel->getReactions().size(); ++i)
    replaceInReaction(&mpModel->getReactions()[i], emap);

  for (i = 0; i < mpModel->getModelValues().size(); ++i)
    replaceInModelEntity(&mpModel->getModelValues()[i], emap);

  for (i = 0; i < mpModel->getEvents().size(); ++i)
    replaceInEvent(&mpModel->getEvents()[i], emap);

  mpModel->forceCompile(NULL);

  if (remove)
    {
      std::map< const CDataObject *, const CDataObject * >::const_iterator it;

      for (it = emap.getMap().begin(); it != emap.getMap().end(); ++it)
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
  if (!pX)
    return;

  replaceInModelEntity(pX, emap);

  //is the metab in a compartment that needs to be replaced?
  if (emap.exists(pX->getCompartment()))
    {
      //move the metab to the new compartment
      CCompartment* oldComp = const_cast<CCompartment*>(pX->getCompartment());
      CCompartment* newComp = const_cast<CCompartment*>(dynamic_cast<const CCompartment*>(emap.getDuplicateFromObject(pX->getCompartment())));
      bool success = false;
      bool wasEnabled = CRegisteredCommonName::isEnabled();
      CRegisteredCommonName::setEnabled(true);
      auto oldCN = pX->getCN();

      do
        {
          success = newComp->addMetabolite(pX);

          if (success)
            {
              oldComp->getMetabolites().remove(pX->getObjectName());
              auto newCN = pX->getCN();
              CRegisteredCommonName::handle(oldCN, newCN);
              mpModel->setCompileFlag();
              mpModel->initializeMetabolites();
            }
          else
            {
              //rename the metab so that it can be added to the new compartment
              pX->setObjectName(pX->getObjectName() + "_");
              //TODO: check if the renaming actually worked
            }
        }
      while (!success);

      CRegisteredCommonName::setEnabled(wasEnabled);
    }
}

void CModelExpansion::replaceInReaction(CReaction* pX, const ElementsMap & emap)
{
  if (!pX)
    return;

  //replace in the chemical equation
  size_t i;

  for (i = 0; i < pX->getChemEq().getSubstrates().size(); ++i)
    {
      CChemEqElement * sourceElement = const_cast< CChemEqElement * >(&pX->getChemEq().getSubstrates()[i]);
      const CMetab* pMetab = dynamic_cast<const CMetab*>(emap.getDuplicateFromObject(sourceElement->getMetabolite()));

      if (pMetab)
        {
          sourceElement->setMetabolite(pMetab->getKey());
        }
    }

  for (i = 0; i < pX->getChemEq().getBalances().size(); ++i)
    {
      CChemEqElement * sourceElement = const_cast< CChemEqElement * >(&pX->getChemEq().getBalances()[i]);
      const CMetab* pMetab = dynamic_cast<const CMetab*>(emap.getDuplicateFromObject(sourceElement->getMetabolite()));

      if (pMetab)
        {
          sourceElement->setMetabolite(pMetab->getKey());
        }
    }

  for (i = 0; i < pX->getChemEq().getProducts().size(); ++i)
    {
      CChemEqElement * sourceElement = const_cast< CChemEqElement * >(&pX->getChemEq().getProducts()[i]);
      const CMetab* pMetab = dynamic_cast<const CMetab*>(emap.getDuplicateFromObject(sourceElement->getMetabolite()));

      if (pMetab)
        {
          sourceElement->setMetabolite(pMetab->getKey());
        }
    }

  for (i = 0; i < pX->getChemEq().getModifiers().size(); ++i)
    {
      CChemEqElement * sourceElement = const_cast< CChemEqElement * >(&pX->getChemEq().getModifiers()[i]);
      const CMetab* pMetab = dynamic_cast<const CMetab*>(emap.getDuplicateFromObject(sourceElement->getMetabolite()));

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
          case CFunctionParameter::Role::SUBSTRATE:
          case CFunctionParameter::Role::PRODUCT:
          case CFunctionParameter::Role::MODIFIER:
          case CFunctionParameter::Role::VOLUME:
          case CFunctionParameter::Role::PARAMETER:
          {
            size_t k;

            std::vector< const CDataObject * > Objects;

            for (k = 0; k < pX->getParameterObjects(i).size(); ++k)
              {
                const CDataObject * pObject = emap.getDuplicateFromObject(pX->getParameterObjects(i)[k]);

                if (pObject != NULL)
                  {
                    Objects.push_back(pObject);
                  }
                else
                  {
                    Objects.push_back(pX->getParameterObjects(i)[k]);
                  }
              }

            pX->setParameterObjects(i, Objects);
          }
          break;

          case CFunctionParameter::Role::TIME:
          default:
            break;
        }
    }

  pX->compile();
}

void CModelExpansion::replaceInModelEntity(CModelEntity* pX, const ElementsMap & emap)
{
  if (!pX)
    return;

  //expression (for assignment or ODE)
  replaceInExpression(pX->getExpressionPtr(), emap);

  //initial expression
  replaceInExpression(pX->getInitialExpressionPtr(), emap);

  //noise expression
  replaceInExpression(pX->getNoiseExpressionPtr(), emap);
}

void CModelExpansion::replaceInEvent(CEvent* pX, const ElementsMap & emap)
{
  if (!pX)
    return;

  replaceInExpression(pX->getTriggerExpressionPtr(), emap);
  replaceInExpression(pX->getDelayExpressionPtr(), emap);

  //now the event assignments...
  size_t i;

  for (i = 0; i < pX->getAssignments().size(); ++i)
    {
      CEventAssignment* pAssignment = &pX->getAssignments()[i];
      replaceInExpression(pAssignment->getExpressionPtr(), emap);

      const CDataObject * pObject = emap.getDuplicateFromObject(pAssignment->getTargetObject());

      if (pObject != NULL)
        pAssignment->setTargetCN(pObject->getCN());
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
      const CDataObject * pObj = dynamic_cast<const CDataObject*>(node->getObjectInterfacePtr());
      std::string refname = "";
      std::string reftype = "";

      if (pObj)
        {
          refname = pObj->getObjectName();
          reftype = pObj->getObjectType();
          pObj = pObj->getObjectParent();
        }

      const CDataObject* duplicate = emap.getDuplicateFromObject(pObj);

      if (duplicate)
        {
          //get the reference object
          const CDataObject* pRef = dynamic_cast<const CDataObject*>(duplicate->getObject(reftype + "=" + refname));

          //update the node
          if (pRef)
            node->setData("<" + pRef->getCN() + ">");

          //std::cout << node->getData() << std::endl;
        }
    }
}

bool CModelExpansion::existDependentEntities(const CDataObject* pObj)
{
  SetOfModelElements sme;

  if (!sme.addObject(pObj))
    return false;

  /*std::cout << sme.mCompartments.size() << " "
  << sme.mMetabs.size() << " "
  << sme.mReactions.size() << " "
  << sme.mGlobalQuantities.size() << " "
  << sme.mEvents.size() << " " << std::endl;*/

  size_t s1 = sme.mCompartments.size();
  size_t s2 = sme.mMetabs.size();
  size_t s3 = sme.mReactions.size();
  size_t s4 = sme.mGlobalQuantities.size();
  size_t s5 = sme.mEvents.size();

  sme.fillDependencies(mpModel);

  if (s1 < sme.mCompartments.size())
    return true;

  if (s2 < sme.mMetabs.size())
    return true;

  if (s3 < sme.mReactions.size())
    return true;

  if (s4 < sme.mGlobalQuantities.size())
    return true;

  if (s5 < sme.mEvents.size())
    return true;

  return false;
}
