// Copyright (C) 2015 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.


#include <copasi/undoFramework/UndoDependentData.h>

#include <copasi/undoFramework/CCopasiUndoCommand.h>

#include <copasi/undoFramework/UndoCompartmentData.h>
#include <copasi/undoFramework/UndoSpeciesData.h>
#include <copasi/undoFramework/UndoGlobalQuantityData.h>
#include <copasi/undoFramework/UndoReactionData.h>
#include <copasi/undoFramework/UndoEventData.h>

#include <copasi/report/CCopasiObject.h>
#include <copasi/report/CCopasiRootContainer.h>

#include <copasi/model/CModelValue.h>
#include <copasi/model/CModel.h>
#include <copasi/model/CReactionInterface.h>

#include <copasi/function/CFunctionDB.h>


UndoDependentData::UndoDependentData(CModelEntity *pObject)
{
  initializeFrom(pObject->getDeletedObjects());
}


UndoDependentData::UndoDependentData()
{

}


UndoDependentData::~UndoDependentData()
{

}

void
UndoDependentData::initializeFrom(
  const std::set<const CCopasiObject *> &deletedObjects)
{
  mCompartmentData.clear();
  mSpeciesData.clear();
  mParameterData.clear();
  mReactionData.clear();
  mEventData.clear();


  if (deletedObjects.size() == 0)
    return;

  // Determine the affected data model
  const CCopasiDataModel * pDataModel = (*deletedObjects.begin())->getObjectDataModel();

  // Determine the affected function DB
  CFunctionDB * pFunctionDB =
    dynamic_cast< CFunctionDB * >((*deletedObjects.begin())->getObjectAncestor("FunctionDB"));

  if (pDataModel == NULL && pFunctionDB == NULL)
    return;

  if (pFunctionDB != NULL)
    {
      // TODO In case a function is deleted we need to loop through all data models
      pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
    }
  else
    {
      pFunctionDB = CCopasiRootContainer::getFunctionList();
    }

  //TODO presently assume only reaction objects can be deleted when GlobalQuantity is deleted
  std::set< const CCopasiObject * > Functions;
  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;
  std::set< const CCopasiObject * > Events;

  bool Used = false;

  if (pFunctionDB != NULL)
    {
      Used |= pFunctionDB->appendDependentFunctions(deletedObjects, Functions);

      if (Functions.size() > 0)
        {
          std::set< const CCopasiObject * >::const_iterator it = Functions.begin();
          std::set< const CCopasiObject * >::const_iterator end = Functions.end();

          for (; it != end; ++it)
            {
              //TODO store the function data
            }
        }
    }


  if (pDataModel == NULL)
    return;

  const CModel* pModel = pDataModel->getModel();

  if (pModel == NULL)
    return;

  Used |= pModel->appendDependentModelObjects(deletedObjects, Reactions, Metabolites,
          Compartments, Values, Events);

  if (Reactions.size() > 0)
    {
      std::set< const CCopasiObject * >::const_iterator it = Reactions.begin();
      std::set< const CCopasiObject * >::const_iterator end = Reactions.end();

      for (; it != end; ++it)
        {
          //store the Reactions data
          const CReaction * pRea = dynamic_cast<const CReaction*>(*it);

          if (pRea == NULL) continue;

          UndoReactionData *data = new UndoReactionData(pRea);
          mReactionData.append(data);
        }
    }

  if (Metabolites.size() > 0)
    {
      std::set< const CCopasiObject * >::const_iterator it = Metabolites.begin();
      std::set< const CCopasiObject * >::const_iterator end = Metabolites.end();

      for (; it != end; ++it)
        {
          //store the Metabolites data
          const CMetab * pMetab = dynamic_cast<const CMetab*>(*it);

          if (pMetab == NULL) continue;

          UndoSpeciesData *data = new UndoSpeciesData(pMetab);
          mSpeciesData.append(data);
        }
    }

  if (Compartments.size() > 0)
    {
      std::set< const CCopasiObject * >::const_iterator it = Compartments.begin();
      std::set< const CCopasiObject * >::const_iterator end = Compartments.end();

      for (; it != end; ++it)
        {
          const CCompartment * pCompartment = dynamic_cast<const CCompartment*>(*it);

          if (pCompartment == NULL)
            continue;

          //store the Global Quantity data
          UndoCompartmentData *data = new UndoCompartmentData(pCompartment);
          mCompartmentData.append(data);
        }
    }

  if (Values.size() > 0)
    {
      std::set< const CCopasiObject * >::const_iterator it = Values.begin();
      std::set< const CCopasiObject * >::const_iterator end = Values.end();

      for (; it != end; ++it)
        {
          const CModelValue * pModelValue = dynamic_cast<const CModelValue*>(*it);

          if (pModelValue == NULL)
            continue;

          //store the Global Quantity data
          UndoGlobalQuantityData *data = new UndoGlobalQuantityData(pModelValue);
          mParameterData.append(data);
        }
    }

  if (Events.size() > 0)
    {
      std::set< const CCopasiObject * >::const_iterator it = Events.begin();
      std::set< const CCopasiObject * >::const_iterator end = Events.end();

      for (; it != end; ++it)
        {
          //store the Event data
          const CEvent * pEvent = dynamic_cast<const CEvent*>(*it);

          UndoEventData *data = new UndoEventData(pEvent);
          mEventData.append(data);
        }
    }
}
