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

#include "copasi/copasi.h"

#include "CObjectLists.h"
#include "copasi/core/CDataObject.h"
#include "copasi/model/CModel.h"
#include "copasi/report/CKeyFactory.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/core/CDataArray.h"

//static
const std::string CObjectLists::ListTypeName[] =
{
  "Not Set", // EMPTY_LIST = 0
  "Single Object", // SINGLE_OBJECT

  "Species", // METABS
  "Initial Concentrations", // METAB_INITIAL_CONCENTRATIONS
  "Initial Numbers", // METAB_INITIAL_NUMBERS
  "Concentrations of Species", // METAB_CONCENTRATIONS
  "Numbers of Species", // METAB_NUMBERS
  "Non-Constant Concentrations of Species", // NON_CONST_METAB_CONCENTRATIONS
  "Non-Constant Numbers of Species", // NON_CONST_METAB_NUMBERS,
  "Constant Concentrations of Species", // CONST_METAB_CONCENTRATIONS,
  "Constant Numbers of Species", // CONST_METAB_NUMBERS,
  "Concentrations of Species with ODE", // ODE_METAB_CONCENTRATIONS,
  "Numbers of Species with ODE", // ODE_METAB_NUMBERS,
  "Concentrations of Species determined by Reactions", // REACTION_METAB_CONCENTRATIONS,
  "Numbers of Species determined by Reactions", // REACTION_METAB_NUMBERS,
  "Concentrations of Species with Assignment", // ASS_METAB_CONCENTRATIONS,
  "Numbers of Species with Assignment", // ASS_METAB_NUMBERS,
  "Concentration Rates", // METAB_CONC_RATES
  "Particle Rates", // METAB_PART_RATES
  "Transition Time", // METAB_TRANSITION_TIME,

  "Reactions", // REACTIONS
  "Concentration Fluxes of Reactions", // REACTION_CONC_FLUXES
  "Particle Fluxes of Reactions", // REACTION_PART_FLUXES,

  "Global Quantity", // GLOBAL_PARAMETERS
  "Global Quantity Initial Values", // GLOBAL_PARAMETER_INITIAL_VALUES
  "Global Quantity Values", // GLOBAL_PARAMETER_VALUES
  "Non-Constant Global Quantity Values", // NON_CONST_GLOBAL_PARAMETER_VALUES
  "Constant Global Quantity Values", // CONST_GLOBAL_PARAMETER_VALUES
  "Values of Global Quantities with ODE", // ODE_GLOBAL_PARAMETER_VALUES
  "Values of Global Quantities with Assignment", // ASS_GLOBAL_PARAMETER_VALUES
  "Global Quantity Rates", // GLOBAL_PARAMETER_RATES

  "Compartments", // COMPARTMENTS
  "Compartment Initial Volumes", // COMPARTMENT_INITIAL_VOLUMES
  "Compartment Volumes", // COMPARTMENT_VOLUMES
  "Non-Constant Compartment Volumes", // NON_CONST_COMPARTMENT_VOLUMES
  "Constant Compartment Volumes", // CONST_COMPARTMENT_VOLUMES
  "Values of Compartment Volumes with ODE", // ODE_COMPARTMENT_VOLUMES
  "Values of Compartment Volumes with Assignment", // ASS_COMPARTMENT_VOLUMES
  "Compartment Volume Rates", // COMPARTMENT_RATES

  "All initial Values", // ALL_INITIAL_VALUES
  "Local Parameter Values", // ALL_LOCAL_PARAMETER_VALUES

  "All Parameter Values", // ALL_PARAMETER_VALUES
  "All Parameter and Initial Values", // ALL_PARAMETER_AND_INITIAL_VALUES

  "All Variables of the model", // ALL_VARIABLES
  "All independent Variables of the model", //  ALL_ODE_VARIABLES

  "Real part of eigenvalues of the reduced jacobian", //REDUCED_JACOBIAN_EV_RE
  "Imaginary part of eigenvalues of the reduced jacobian", //REDUCED_JACOBIAN_EV_IM

  "" // End of the list do not remove!
};

//static
std::vector<CDataObject*>
CObjectLists::getListOfObjects(ListType t, const CModel* model)
{
  std::vector< const CDataObject * > src = getListOfConstObjects(t, model);
  std::vector< CDataObject * > target;
  target.resize(src.size());

  std::vector< const CDataObject * >::iterator itSrc = src.begin();
  std::vector< const CDataObject * >::iterator endSrc = src.end();
  std::vector< CDataObject * >::iterator itTarget = target.begin();

  for (; itSrc != endSrc; ++itSrc, ++itTarget)
    *itTarget = const_cast< CDataObject * >(*itSrc);

  return target;

  //I know this is unnecessary copying. But I want to avoid reinterpret_cast
}

//static
std::vector<const CDataObject*>
CObjectLists::getListOfConstObjects(ListType t, const CModel* pModel)
{
  ObjectList ret;

  CDataVector< CMetab >::const_iterator itMetab = pModel->getMetabolites().begin();
  CDataVector< CMetab >::const_iterator endMetab = pModel->getMetabolites().end();

  CDataVector< CModelValue >::const_iterator itValue = pModel->getModelValues().begin();
  CDataVector< CModelValue >::const_iterator endValue = pModel->getModelValues().end();

  CDataVector< CCompartment >::const_iterator itComp = pModel->getCompartments().begin();
  CDataVector< CCompartment >::const_iterator endComp = pModel->getCompartments().end();

  CDataVector< CReaction >::const_iterator itReaction = pModel->getReactions().begin();
  CDataVector< CReaction >::const_iterator endReaction = pModel->getReactions().end();

  std::set< const CModelEntity * > EventTargets = getEventTargets(pModel);

  switch (t)
    {
      case EMPTY_LIST:
      case SINGLE_OBJECT:
        break;

      // Metabolites
      case METABS:

        for (; itMetab != endMetab; ++itMetab)
          ret.push_back(itMetab);

        break;

      case METAB_INITIAL_CONCENTRATIONS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() != CModelEntity::Status::ASSIGNMENT)
            ret.push_back(itMetab->getInitialConcentrationReference());

        break;

      case METAB_INITIAL_NUMBERS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() != CModelEntity::Status::ASSIGNMENT)
            ret.push_back(itMetab->getInitialValueReference());

        break;

      case METAB_CONCENTRATIONS:

        for (; itMetab != endMetab; ++itMetab)
          ret.push_back(itMetab->getConcentrationReference());

        break;

      case METAB_NUMBERS:

        for (; itMetab != endMetab; ++itMetab)
          ret.push_back(itMetab->getValueReference());

        break;

      case NON_CONST_METAB_CONCENTRATIONS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() != CModelEntity::Status::FIXED ||
              EventTargets.count(itMetab) > 0)
            ret.push_back(itMetab->getConcentrationReference());

        break;

      case NON_CONST_METAB_NUMBERS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() != CModelEntity::Status::FIXED ||
              EventTargets.count(itMetab) > 0)
            ret.push_back(itMetab->getValueReference());

        break;

      case CONST_METAB_CONCENTRATIONS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::FIXED)
            ret.push_back(itMetab->getConcentrationReference());

        break;

      case CONST_METAB_NUMBERS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::FIXED)
            ret.push_back(itMetab->getValueReference());

        break;

      case ODE_METAB_CONCENTRATIONS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::ODE)
            ret.push_back(itMetab->getConcentrationReference());

        break;

      case ODE_METAB_NUMBERS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::ODE)
            ret.push_back(itMetab->getValueReference());

        break;

      case REACTION_METAB_CONCENTRATIONS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::REACTIONS)
            ret.push_back(itMetab->getConcentrationReference());

        break;

      case REACTION_METAB_NUMBERS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::REACTIONS)
            ret.push_back(itMetab->getValueReference());

        break;

      case ASS_METAB_CONCENTRATIONS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::ASSIGNMENT)
            ret.push_back(itMetab->getConcentrationReference());

        break;

      case ASS_METAB_NUMBERS:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::ASSIGNMENT)
            ret.push_back(itMetab->getValueReference());

        break;

      case METAB_CONC_RATES:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::ODE ||
              itMetab->getStatus() == CModelEntity::Status::REACTIONS)
            ret.push_back(itMetab->getConcentrationRateReference());

        break; //not possible at the moment

      case METAB_PART_RATES:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::ODE ||
              itMetab->getStatus() == CModelEntity::Status::REACTIONS)
            ret.push_back(itMetab->getRateReference());

        break;

      case METAB_TRANSITION_TIME:

        for (; itMetab != endMetab; ++itMetab)
          if (itMetab->getStatus() == CModelEntity::Status::ODE ||
              itMetab->getStatus() == CModelEntity::Status::REACTIONS)
            ret.push_back(static_cast< const CDataObject * >(itMetab->getObject(CCommonName("Reference=TransitionTime"))));

        break;

      // reactions
      case REACTIONS:

        for (; itReaction != endReaction; ++itReaction)
          ret.push_back(itReaction);

        break;

      case REACTION_CONC_FLUXES:

        for (; itReaction != endReaction; ++itReaction)
          ret.push_back(static_cast< const CDataObject * >(itReaction->getObject(CCommonName("Reference=Flux"))));

        break;

      case REACTION_PART_FLUXES:

        for (; itReaction != endReaction; ++itReaction)
          ret.push_back(static_cast< const CDataObject * >(itReaction->getObject(CCommonName("Reference=ParticleFlux"))));

        break;

      // global quantities
      case GLOBAL_PARAMETERS:

        for (; itValue != endValue; ++itValue)
          ret.push_back(itValue);

        break;

      case GLOBAL_PARAMETER_INITIAL_VALUES:

        for (; itValue != endValue; ++itValue)
          if (itValue->getStatus() != CModelEntity::Status::ASSIGNMENT)
            ret.push_back(itValue->getInitialValueReference());

        break;

      case GLOBAL_PARAMETER_VALUES:

        for (; itValue != endValue; ++itValue)
          ret.push_back(itValue->getValueReference());

        break;

      case NON_CONST_GLOBAL_PARAMETER_VALUES:

        for (; itValue != endValue; ++itValue)
          if (itValue->getStatus() != CModelEntity::Status::FIXED ||
              EventTargets.count(itValue) > 0)
            ret.push_back(itValue->getValueReference());

        break;

      case CONST_GLOBAL_PARAMETER_INITIAL_VALUES:

        for (; itValue != endValue; ++itValue)
          if (itValue->getStatus() == CModelEntity::Status::FIXED)
            ret.push_back(itValue->getInitialValueReference());

        break;

      case ODE_GLOBAL_PARAMETER_VALUES:

        for (; itValue != endValue; ++itValue)
          if (itValue->getStatus() == CModelEntity::Status::ODE)
            ret.push_back(itValue->getValueReference());

        break;

      case ASS_GLOBAL_PARAMETER_VALUES:

        for (; itValue != endValue; ++itValue)
          if (itValue->getStatus() == CModelEntity::Status::ASSIGNMENT)
            ret.push_back(itValue->getValueReference());

        break;

      case GLOBAL_PARAMETER_RATES:

        for (; itValue != endValue; ++itValue)
          if (itValue->getStatus() == CModelEntity::Status::ODE)
            ret.push_back(itValue->getRateReference());

        break;

      // compartments
      case COMPARTMENTS:

        for (; itComp != endComp; ++itComp)
          ret.push_back(itComp);

        break;

      case COMPARTMENT_INITIAL_VOLUMES:

        for (; itComp != endComp; ++itComp)
          if (itComp->getStatus() != CModelEntity::Status::ASSIGNMENT)
            ret.push_back(itComp->getInitialValueReference());

        break;

      case COMPARTMENT_VOLUMES:

        for (; itComp != endComp; ++itComp)
          ret.push_back(itComp->getValueReference());

        break;

      case NON_CONST_COMPARTMENT_VOLUMES:

        for (; itComp != endComp; ++itComp)
          if (itComp->getStatus() != CModelEntity::Status::FIXED ||
              EventTargets.count(itComp) > 0)
            ret.push_back(itComp->getValueReference());

        break;

      case CONST_COMPARTMENT_VOLUMES:

        for (; itComp != endComp; ++itComp)
          if (itComp->getStatus() == CModelEntity::Status::FIXED)
            ret.push_back(itComp->getValueReference());

        break;

      case ODE_COMPARTMENT_VOLUMES:

        for (; itComp != endComp; ++itComp)
          if (itComp->getStatus() == CModelEntity::Status::ODE)
            ret.push_back(itComp->getValueReference());

        break;

      case ASS_COMPARTMENT_VOLUMES:

        for (; itComp != endComp; ++itComp)
          if (itComp->getStatus() == CModelEntity::Status::ASSIGNMENT)
            ret.push_back(itComp->getValueReference());

        break;

      case COMPARTMENT_RATES:

        for (; itComp != endComp; ++itComp)
          if (itComp->getStatus() == CModelEntity::Status::ODE)
            ret.push_back(itComp->getRateReference());

        break;

      case ALL_INITIAL_VALUES:
      {
        ret = getListOfConstObjects(METAB_INITIAL_CONCENTRATIONS, pModel);

        ObjectList tmp = getListOfConstObjects(GLOBAL_PARAMETER_INITIAL_VALUES, pModel);
        ret.insert(ret.end(), tmp.begin(), tmp.end());

        tmp = getListOfConstObjects(COMPARTMENT_INITIAL_VOLUMES, pModel);
        ret.insert(ret.end(), tmp.begin(), tmp.end());
      }
      break;

      case ALL_LOCAL_PARAMETER_VALUES:
      {
        for (; itReaction != endReaction; ++itReaction)
          {
            const CFunctionParameters & params = itReaction->getFunctionParameters();
            size_t j, jmax = params.size();

            for (j = 0; j < jmax; ++j)
              if (params[j]->getUsage() == CFunctionParameter::Role::PARAMETER)
                if (itReaction->isLocalParameter(j))
                  {
                    const CCopasiParameter * par =
                      dynamic_cast< const CCopasiParameter * >(itReaction->getParameterObjects(j)[0]);

                    if (par)
                      ret.push_back(par->getValueReference());
                  }
          }
      }
      break;

      case ALL_PARAMETER_VALUES:
      {
        ret = getListOfConstObjects(CONST_GLOBAL_PARAMETER_INITIAL_VALUES, pModel);

        ObjectList tmp = getListOfConstObjects(ALL_LOCAL_PARAMETER_VALUES, pModel);
        ret.insert(ret.end(), tmp.begin(), tmp.end());
      }
      break;

      case ALL_PARAMETER_AND_INITIAL_VALUES:
      {
        ret = getListOfConstObjects(ALL_PARAMETER_VALUES, pModel);

        ObjectList tmp = getListOfConstObjects(ALL_INITIAL_VALUES, pModel);
        ret.insert(ret.end(), tmp.begin(), tmp.end());
      }
      break;

      case ALL_VARIABLES:
      {
        ret = getListOfConstObjects(NON_CONST_METAB_CONCENTRATIONS, pModel);

        ObjectList tmp = getListOfConstObjects(NON_CONST_GLOBAL_PARAMETER_VALUES, pModel);
        ret.insert(ret.end(), tmp.begin(), tmp.end());

        tmp = getListOfConstObjects(NON_CONST_COMPARTMENT_VOLUMES, pModel);
        ret.insert(ret.end(), tmp.begin(), tmp.end());
      }
      break;

      case REDUCED_JACOBIAN_EV_RE:
      {
        CDataContainer * pParent = dynamic_cast<CDataContainer*>(pModel->getObjectParent());

        if (!pParent)
          break;

        const CDataArray * pEV = dynamic_cast<const CDataArray*>(pParent->getObject(CCommonName("Vector=TaskList[Steady-State],Array=Eigenvalues of reduced system Jacobian")));

        if (pEV->dimensionality() != 2) //2d matrix
          break;

        if (pEV->size()[1] != 2) //must be two columns for Re and Im part
          break;

        size_t imax = pEV->size()[0];
        size_t i;

        for (i = 0; i < imax; ++i)
          ret.push_back(static_cast< const CDataObject * >(pEV->addElementReference(i, 0)));
      }
      break;

      case REDUCED_JACOBIAN_EV_IM:
      {
        CDataContainer * pParent = dynamic_cast<CDataContainer*>(pModel->getObjectParent());

        if (!pParent)
          break;

        const CDataArray * pEV = dynamic_cast<const CDataArray*>(pParent->getObject(CCommonName("Vector=TaskList[Steady-State],Array=Eigenvalues of reduced system Jacobian")));

        if (pEV->dimensionality() != 2) //2d matrix
          break;

        if (pEV->size()[1] != 2) //must be two columns for Re and Im part
          break;

        size_t imax = pEV->size()[0];
        size_t i;

        for (i = 0; i < imax; ++i)
          ret.push_back(static_cast< const CDataObject * >(pEV->addElementReference(i, 1)));
      }
      break;

      default:
        break;
    }

  return ret;
}

//static
bool CObjectLists::existsFixedMetab(const CModel* pModel)
{
  bool fixedMetab = false;
  const CDataVector< CMetab > & metabs = pModel->getMetabolites();
  size_t i, imax = metabs.size();

  for (i = 0; i < imax; ++i)
    if (metabs[i].getStatus() == CModelEntity::Status::FIXED)
      {fixedMetab = true; break;}

  return fixedMetab;
}

// static
std::set< const CModelEntity * > CObjectLists::getEventTargets(const CModel* pModel)
{
  std::set< const CModelEntity * > EventTargets;
  CObjectInterface::ContainerList List;
  List.push_back(pModel);

  CDataVectorN< CEvent >::const_iterator itEvent = pModel->getEvents().begin();
  CDataVectorN< CEvent >::const_iterator endEvent = pModel->getEvents().end();

  for (; itEvent != endEvent; ++itEvent)
    {
      CDataVectorN< CEventAssignment >::const_iterator itAssignment =
        itEvent->getAssignments().begin();
      CDataVectorN< CEventAssignment >::const_iterator endAssignment =
        itEvent->getAssignments().end();

      for (; itAssignment != endAssignment; ++itAssignment)
        {
          const CModelEntity * pModelEntity =
            dynamic_cast< const CModelEntity * >(CDataObject::GetObjectFromCN(List, itAssignment->getTargetCN()));

          if (pModelEntity != NULL)
            {
              EventTargets.insert(pModelEntity);
            }
        }
    }

  return EventTargets;
}
