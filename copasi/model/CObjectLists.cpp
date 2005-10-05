/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/model/CObjectLists.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/10/05 14:04:44 $
   End CVS Header */

#include "CObjectLists.h"
 #include "report/CCopasiObject.h"
 #include "model/CModel.h"

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
      break; //not possible at the moment

    case NON_CONST_METAB_PART_RATES:
      for (i = 0; i < imax; ++i)
        if (metabs[i]->getStatus() != CModelEntity::FIXED)
          ret.push_back(const_cast<CCopasiObject*>
                        (metabs[i]->getObject(CCopasiObjectName("Reference=Rate"))));
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

    case GLOBAL_PARAMETERS:
      {
        const CCopasiVectorN< CModelValue > & params = model->getModelValues();
        for (i = 0; i < params.size(); ++i)
          ret.push_back(params[i]);
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

      //case GLOBAL_PARAMETER_INITIAL_VALUES:
      //case GLOBAL_PARAMETER_RATES:

    case COMPARTMENTS:
    case COMPARTMENT_VOLUMES:
      //case COMPARTMENT_INITIAL_VOLUMES:
      //case COMPARTMENT_RATES:

    case ALL_LOCAL_PARAMETER_VALUES:
      break;
    }

  //debug output
  std::vector<CCopasiObject*>::const_iterator it, itEnd = ret.end();
  for (it = ret.begin(); it != itEnd; ++it)
    std::cout << (*it)->getObjectName() << std::endl;

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
