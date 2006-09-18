/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CObjectLists.cpp,v $
   $Revision: 1.11 $
   $Name:  $
   $Author: ssahle $
   $Date: 2006/09/18 12:51:03 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "copasi.h"

#include "CObjectLists.h"
#include "report/CCopasiObject.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"

//static
const std::string CObjectLists::ListTypeName[] =
  {
    "Not Set",
    "Single Object",

    "Metabolites",
    "Non-Constant Metabolites",
    "Concentrations of Metabolites",
    "Non-Constant Concentrations of Metabolites",
    "Numbers of Metabolites",
    "Non-Constant Numbers of Metabolites",
    "Non-Constant Concentration Rates",
    "Non-Constant Particle Rates",
    "Initial Concentrations",
    "Initial Numbers",

    "Reactions",
    "Concentration Fluxes of Reactions",
    "Particle Fluxes of Reactions",

    "Global Quantity",
    "Global Quantity Initial Values",
    "Global Quantity Values",
    "Non-Constant Global Quantity Values",
    "Values of Global Quantities with ODE",
    "Values of Global Quantities with Assignment",
    "Global Quantity Rates",

    "Compartments",
    "Compartment Volumes",

    "Local Parameter Values",
    "All Parameter Values",
    "All Parameter and Initial Values",
    ""
  };

//static
std::vector<const CCopasiObject*>
CObjectLists::getListOfConstObjects(ListType t, const CModel* model)
{
  std::vector<CCopasiObject*> tmp = getListOfObjects(t, model);
  return std::vector<const CCopasiObject*>(tmp.begin(), tmp.end());

  //I know this is unnecessary copying. But I want to avoid reinterpret_cast
}

//static
std::vector<CCopasiObject*>
CObjectLists::getListOfObjects(ListType t, const CModel* model)
{
  ObjectList ret;

  const CCopasiVector< CMetab > & metabs = model->getMetabolites();
  unsigned C_INT32 i, imax = metabs.size();

  const CCopasiVectorN<CReaction> & reacs = model->getReactions();
  unsigned C_INT32 reacMax = reacs.size();

  switch (t)
    {
    case EMPTY_LIST:
    case SINGLE_OBJECT:
      break;

    case ALL_METABS:
      for (i = 0; i < imax; ++i)
        ret.push_back(metabs[i]);
      break;

    case NON_CONST_METABS:
      for (i = 0; i < imax; ++i)
        if (metabs[i]->getStatus() != CModelEntity::FIXED)
          ret.push_back(metabs[i]);
      break;

    case ALL_METAB_CONCENTRATIONS:
      for (i = 0; i < imax; ++i)
        ret.push_back(const_cast<CCopasiObject*>
                      (metabs[i]->getObject(CCopasiObjectName("Reference=Concentration"))));
      break;

    case NON_CONST_METAB_CONCENTRATIONS:
      for (i = 0; i < imax; ++i)
        if (metabs[i]->getStatus() != CModelEntity::FIXED)
          ret.push_back(const_cast<CCopasiObject*>
                        (metabs[i]->getObject(CCopasiObjectName("Reference=Concentration"))));
      break;

    case ALL_METAB_NUMBERS:
      for (i = 0; i < imax; ++i)
        ret.push_back(const_cast<CCopasiObject*>
                      (metabs[i]->getObject(CCopasiObjectName("Reference=ParticleNumber"))));
      break;

    case NON_CONST_METAB_NUMBERS:
      for (i = 0; i < imax; ++i)
        if (metabs[i]->getStatus() != CModelEntity::FIXED)
          ret.push_back(const_cast<CCopasiObject*>
                        (metabs[i]->getObject(CCopasiObjectName("Reference=ParticleNumber"))));
      break;

    case NON_CONST_METAB_CONC_RATES:
      for (i = 0; i < imax; ++i)
        if (metabs[i]->getStatus() != CModelEntity::FIXED)
          ret.push_back(const_cast<CCopasiObject*>
                        (metabs[i]->getObject(CCopasiObjectName("Reference=Rate"))));
      break; //not possible at the moment

    case NON_CONST_METAB_PART_RATES:
      for (i = 0; i < imax; ++i)
        if (metabs[i]->getStatus() != CModelEntity::FIXED)
          ret.push_back(const_cast<CCopasiObject*>
                        (metabs[i]->getObject(CCopasiObjectName("Reference=ParticleNumberRate"))));
      break;

    case ALL_METAB_INITIAL_CONCENTRATIONS:
      for (i = 0; i < imax; ++i)
        ret.push_back(const_cast<CCopasiObject*>
                      (metabs[i]->getObject(CCopasiObjectName("Reference=InitialConcentration"))));
      break;

    case ALL_METAB_INITIAL_NUMBERS:
      for (i = 0; i < imax; ++i)
        ret.push_back(const_cast<CCopasiObject*>
                      (metabs[i]->getObject(CCopasiObjectName("Reference=InitialParticleNumber"))));
      break;

      // reactions

    case REACTIONS:
      for (i = 0; i < reacMax; ++i)
        ret.push_back(reacs[i]);
      break;

    case REACTION_CONC_FLUXES:
      for (i = 0; i < reacMax; ++i)
        ret.push_back(const_cast<CCopasiObject*>
                      (reacs[i]->getObject(CCopasiObjectName("Reference=Flux"))));
      break;

    case REACTION_PART_FLUXES:
      for (i = 0; i < reacMax; ++i)
        ret.push_back(const_cast<CCopasiObject*>
                      (reacs[i]->getObject(CCopasiObjectName("Reference=ParticleFlux"))));
      break;

      // global parameters

    case GLOBAL_PARAMETERS:
      {
        const CCopasiVectorN< CModelValue > & params = model->getModelValues();
        for (i = 0; i < params.size(); ++i)
          ret.push_back(params[i]);
      }
      break;

    case GLOBAL_PARAMETER_INITIAL_VALUES:
      {
        const CCopasiVectorN< CModelValue > & params = model->getModelValues();
        for (i = 0; i < params.size(); ++i)
          if (params[i]->getStatus() != CModelEntity::ASSIGNMENT)
            ret.push_back(const_cast<CCopasiObject*>
                          (params[i]->getObject(CCopasiObjectName("Reference=InitialValue"))));
      }
      break;

    case GLOBAL_PARAMETER_VALUES:
      {
        const CCopasiVectorN< CModelValue > & params = model->getModelValues();
        for (i = 0; i < params.size(); ++i)
          ret.push_back(const_cast<CCopasiObject*>
                        (params[i]->getObject(CCopasiObjectName("Reference=Value"))));
      }
      break;

    case NON_CONST_GLOBAL_PARAMETER_VALUES:
      {
        const CCopasiVectorN< CModelValue > & params = model->getModelValues();
        for (i = 0; i < params.size(); ++i)
          if (params[i]->getStatus() != CModelEntity::FIXED)
            ret.push_back(const_cast<CCopasiObject*>
                          (params[i]->getObject(CCopasiObjectName("Reference=Value"))));
      }
      break;

    case ODE_GLOBAL_PARAMETER_VALUES:
      {
        const CCopasiVectorN< CModelValue > & params = model->getModelValues();
        for (i = 0; i < params.size(); ++i)
          if (params[i]->getStatus() == CModelEntity::ODE)
            ret.push_back(const_cast<CCopasiObject*>
                          (params[i]->getObject(CCopasiObjectName("Reference=Value"))));
      }
      break;

    case ASS_GLOBAL_PARAMETER_VALUES:
      {
        const CCopasiVectorN< CModelValue > & params = model->getModelValues();
        for (i = 0; i < params.size(); ++i)
          if (params[i]->getStatus() == CModelEntity::ASSIGNMENT)
            ret.push_back(const_cast<CCopasiObject*>
                          (params[i]->getObject(CCopasiObjectName("Reference=Value"))));
      }
      break;

    case GLOBAL_PARAMETER_RATES:
      {
        const CCopasiVectorN< CModelValue > & params = model->getModelValues();
        for (i = 0; i < params.size(); ++i)
          if (params[i]->getStatus() == CModelEntity::ODE)
            ret.push_back(const_cast<CCopasiObject*>
                          (params[i]->getObject(CCopasiObjectName("Reference=Rate"))));
      }
      break;

      // compartments

    case COMPARTMENTS:
    case COMPARTMENT_VOLUMES:
      //case COMPARTMENT_INITIAL_VOLUMES:
      //case COMPARTMENT_RATES:
      break;

    case ALL_LOCAL_PARAMETER_VALUES:
      {
        for (i = 0; i < reacMax; ++i)
          {
            const CFunctionParameters & params = reacs[i]->getFunctionParameters();
            unsigned C_INT32 j, jmax = params.size();
            for (j = 0; j < jmax; ++j)
              if (params[j]->getUsage() == CFunctionParameter::PARAMETER)
                if (reacs[i]->isLocalParameter(j))
                  {
                    CCopasiParameter * par =
                      dynamic_cast<CCopasiParameter*>
                      (GlobalKeys.get(reacs[i]->getParameterMappings()[j][0]));
                    if (par)
                      ret.push_back(const_cast<CCopasiObject*>
                                    (par->getObject(CCopasiObjectName("Reference=Value"))));
                  }
          }

        //ret.push_back(reacs[i]);
      }
      break;

    case ALL_PARAMETER_VALUES:
    case ALL_PARAMETER_AND_INITIAL_VALUES:
      break;
    }

  //debug output

#ifdef COPASI_DEBUG
  std::vector<CCopasiObject*>::const_iterator it, itEnd = ret.end();
  for (it = ret.begin(); it != itEnd; ++it)
    std::cout << (*it)->getObjectDisplayName() << std::endl;
#endif // COPASI_DEBUG

  return ret;
}

//static
bool CObjectLists::existsFixedMetab(const CModel* model)
{
  bool fixedMetab = false;
  const CCopasiVector< CMetab > & metabs = model->getMetabolites();
  C_INT32 i, imax = metabs.size();
  for (i = 0; i < imax; ++i)
    if (metabs[i]->getStatus() == CModelEntity::FIXED)
    {fixedMetab = true; break;}
  return fixedMetab;
}
