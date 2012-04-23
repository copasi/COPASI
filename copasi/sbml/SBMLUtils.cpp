// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/SBMLUtils.cpp,v $
//   $Revision: 1.6 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2012/04/23 15:49:06 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <sbml/Compartment.h>
#include <sbml/Species.h>
#include <sbml/SpeciesReference.h>
#include <sbml/Reaction.h>
#include <sbml/Model.h>
#include <sbml/Parameter.h>
#include <sbml/FunctionDefinition.h>
#include <sbml/Event.h>

#include "SBMLUtils.h"

#include "copasi/utilities/CCopasiMessage.h"

//static
std::string SBMLUtils::getIdFromSBase(const SBase* pS)
{
  if (!pS) return "";

  std::string id;

  int type = pS->getTypeCode();

  switch (type)
    {
      case SBML_COMPARTMENT:
        id = getId(dynamic_cast<const Compartment*>(pS));
        break;
      case SBML_EVENT:
        id = getId(dynamic_cast<const Event*>(pS));
        break;
      case SBML_FUNCTION_DEFINITION:
        id = getId(dynamic_cast<const FunctionDefinition*>(pS));
        break;
      case SBML_MODEL:
        id = getId(dynamic_cast<const Model*>(pS));
        break;
      case SBML_PARAMETER:
        id = getId(dynamic_cast<const Parameter*>(pS));
        break;
      case SBML_REACTION:
        id = getId(dynamic_cast<const Reaction*>(pS));
        break;
      case SBML_SPECIES:
        id = getId(dynamic_cast<const Species*>(pS));
        break;
      case SBML_SPECIES_REFERENCE:
      case SBML_MODIFIER_SPECIES_REFERENCE:
        id = "";
        //id = getId(dynamic_cast<const SimpleSpeciesReference*>(pS));
        //the above should work if layout support is compiled into libsbml
        break;

        //case SBML_COMPARTMENT_TYPE:
        //case SBML_SPECIES_TYPE:
      default:
        id = "";
    }

  return id;
}

//static
template<class CType>
std::string SBMLUtils::getId(const CType * pA, C_INT32 level)
{
  if (!pA) return "";

  if (level == 1)
    return pA->getName();
  else
    return pA->getId();
}

/**
 * This method goes through the given SBML model and collects all ids and
 * meta ids used in the model.
 */
//static
void SBMLUtils::collectIds(Model* pModel, std::map<std::string, const SBase*>& ids, std::map<std::string, const SBase*>& metaIds)
{
  if (pModel != NULL)
    {
      // the model itself
      SBase* pSBase = NULL;
      std::string id;

      if (pModel->isSetId())
        {
          id = pModel->getId();

          if (ids.find(id) == ids.end())
            {
              ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
            }
          else
            {
              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
            }
        }

      if (pModel->isSetMetaId())
        {
          id = pModel->getMetaId();

          if (metaIds.find(id) == metaIds.end())
            {
              metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
            }
          else
            {
              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
            }
        }

      // ListOfFunctionDefinitions
      pSBase = pModel->getListOfFunctionDefinitions();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // all FunctionDefinitions
          unsigned int i, iMax = pModel->getListOfFunctionDefinitions()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pModel->getListOfFunctionDefinitions()->get(i);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }

              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }

      // ListOfUnitDefinition
      pSBase = pModel->getListOfUnitDefinitions();

      if (pSBase != NULL)
        {
          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // all UnitDefinitions
          // for each UnitDefinition: ListOfUnits, each Unit in ListOfUnits
          unsigned int i, iMax = pModel->getListOfUnitDefinitions()->size();

          for (i = 0; i < iMax; ++i)
            {
              /* UnitDefinitions have their ids in a different namespace
                 so we only consider meta ids.
                 */
              UnitDefinition* pUDef = pModel->getUnitDefinition(i);
              assert(pUDef != NULL);

              if (pUDef->isSetMetaId())
                {
                  id = pUDef->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pUDef));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }

              ListOf* pList = pUDef->getListOfUnits();

              if (pList != NULL)
                {
                  if (pList->isSetMetaId())
                    {
                      id = pList->getMetaId();

                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::pair<const std::string, const SBase*>(id, pList));
                        }
                      else
                        {
                          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }

                  unsigned j, jMax = pList->size();

                  for (j = 0; j < jMax; ++j)
                    {
                      pSBase = pList->get(j);
                      assert(pSBase != NULL);

                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();

                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                    }
                }
            }
        }

      // ListOfCompartmentTypes
      pSBase = pModel->getListOfCompartmentTypes();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // each compartment type
          unsigned int i, iMax = pModel->getListOfCompartmentTypes()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pModel->getCompartmentType(i);
              assert(pSBase != NULL);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }

              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }

      // ListOfSpeciesTypes
      pSBase = pModel->getListOfSpeciesTypes();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // each species type
          unsigned int i, iMax = pModel->getListOfSpeciesTypes()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pModel->getSpeciesType(i);
              assert(pSBase != NULL);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }

              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }

      // ListOfCompartments
      pSBase = pModel->getListOfCompartments();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // all compartments
          unsigned int i, iMax = pModel->getListOfCompartments()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pModel->getCompartment(i);
              assert(pSBase != NULL);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }

              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }

      // ListOfSpecies
      pSBase = pModel->getListOfSpecies();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // all species
          unsigned int i, iMax = pModel->getListOfSpecies()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pModel->getSpecies(i);
              assert(pSBase != NULL);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }

              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }

      // ListOfParameters
      pSBase = pModel->getListOfParameters();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // each parameter
          unsigned int i, iMax = pModel->getListOfParameters()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pModel->getParameter(i);
              assert(pSBase != NULL);

              if (pSBase->isSetId())
                {
                  id = pSBase->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }

              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }

      // ListOfInitialAssignments
      pSBase = pModel->getListOfInitialAssignments();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // each initial assignment
          unsigned int i, iMax = pModel->getListOfInitialAssignments()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pModel->getInitialAssignment(i);
              assert(pSBase != NULL);

              // initial assignments have no ids
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }

      // ListOfRules
      pSBase = pModel->getListOfRules();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // each rule
          unsigned int i, iMax = pModel->getListOfRules()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pModel->getRule(i);
              assert(pSBase != NULL);

              // rules don't have ids
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }

      // ListOfConstraints
      pSBase = pModel->getListOfConstraints();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // each constraint
          unsigned int i, iMax = pModel->getListOfConstraints()->size();

          for (i = 0; i < iMax; ++i)
            {
              pSBase = pModel->getConstraint(i);
              assert(pSBase != NULL);

              // constraints don't have ids
              if (pSBase->isSetMetaId())
                {
                  id = pSBase->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }
            }
        }

      // ListOfReactions
      pSBase = pModel->getListOfReactions();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // all reactions
          unsigned int i, iMax = pModel->getListOfReactions()->size();

          for (i = 0; i < iMax; ++i)
            {
              Reaction* pReaction = pModel->getReaction(i);
              assert(pReaction != NULL);

              if (pReaction->isSetId())
                {
                  id = pReaction->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::pair<const std::string, const SBase*>(id, pReaction));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }

              if (pReaction->isSetMetaId())
                {
                  id = pReaction->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pReaction));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }

              // for each reaction: ListOfSubstrates, each substrate, ListOfProducts, each
              // Product, ListOfModifieres, each modifier, KineticLaw, ListOfparameters,
              // each parameter
              if (pReaction->getListOfReactants() != NULL)
                {
                  pSBase = pReaction->getListOfReactants();

                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();

                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }

                  unsigned int j, jMax = pReaction->getListOfReactants()->size();

                  for (j = 0; j < jMax; ++j)
                    {
                      pSBase = pReaction->getReactant(j);
                      assert(pSBase != NULL);

                      // since L2V2 species references can have ids
                      if (pSBase->isSetId())
                        {
                          id = pSBase->getId();

                          if (ids.find(id) == ids.end())
                            {
                              ids.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                            }
                        }

                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();

                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                    }
                }

              if (pReaction->getListOfProducts() != NULL)
                {
                  pSBase = pReaction->getListOfProducts();

                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();

                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }

                  unsigned int j, jMax = pReaction->getListOfProducts()->size();

                  for (j = 0; j < jMax; ++j)
                    {
                      pSBase = pReaction->getProduct(j);
                      assert(pSBase != NULL);

                      // since L2V2 species references can have ids
                      if (pSBase->isSetId())
                        {
                          id = pSBase->getId();

                          if (ids.find(id) == ids.end())
                            {
                              ids.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                            }
                        }

                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();

                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                    }
                }

              if (pReaction->getListOfModifiers() != NULL)
                {
                  pSBase = pReaction->getListOfModifiers();

                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();

                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }

                  unsigned int j, jMax = pReaction->getListOfModifiers()->size();

                  for (j = 0; j < jMax; ++j)
                    {
                      pSBase = pReaction->getModifier(j);
                      assert(pSBase != NULL);

                      // since L2V2 species references can have ids
                      if (pSBase->isSetId())
                        {
                          id = pSBase->getId();

                          if (ids.find(id) == ids.end())
                            {
                              ids.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                            }
                        }

                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();

                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                    }
                }

              KineticLaw* pKLaw = pReaction->getKineticLaw();

              if (pKLaw != NULL)
                {
                  if (pKLaw->isSetMetaId())
                    {
                      id = pKLaw->getMetaId();

                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::pair<const std::string, const SBase*>(id, pKLaw));
                        }
                      else
                        {
                          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }

                  pSBase = pKLaw->getListOfParameters();

                  if (pSBase != NULL)
                    {
                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();

                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }

                      unsigned int j, jMax = pKLaw->getListOfParameters()->size();

                      for (j = 0; j < jMax; ++j)
                        {
                          pSBase = pKLaw->getParameter(j);
                          assert(pSBase != NULL);

                          // local parameters have their ids in a
                          // different namespace
                          if (pSBase->isSetMetaId())
                            {
                              id = pSBase->getMetaId();

                              if (metaIds.find(id) == metaIds.end())
                                {
                                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                                }
                              else
                                {
                                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                                }
                            }
                        }
                    }
                }
            }
        }

      // ListOfEvents
      pSBase = pModel->getListOfEvents();

      if (pSBase != NULL)
        {
          if (pSBase->isSetId())
            {
              id = pSBase->getId();

              if (ids.find(id) == ids.end())
                {
                  ids.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                }
            }

          if (pSBase->isSetMetaId())
            {
              id = pSBase->getMetaId();

              if (metaIds.find(id) == metaIds.end())
                {
                  metaIds.insert(std::pair<const std::string, const SBase*>(id, pModel));
                }
              else
                {
                  CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                }
            }

          // each event
          unsigned int i, iMax = pModel->getListOfEvents()->size();

          for (i = 0; i < iMax; ++i)
            {
              Event* pEvent = pModel->getEvent(i);
              assert(pEvent != NULL);

              if (pEvent->isSetId())
                {
                  id = pEvent->getId();

                  if (ids.find(id) == ids.end())
                    {
                      ids.insert(std::pair<const std::string, const SBase*>(id, pEvent));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::EXCEPTION, MCSBML + 68, id.c_str());
                    }
                }

              if (pEvent->isSetMetaId())
                {
                  id = pEvent->getMetaId();

                  if (metaIds.find(id) == metaIds.end())
                    {
                      metaIds.insert(std::pair<const std::string, const SBase*>(id, pEvent));
                    }
                  else
                    {
                      CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                    }
                }

              // in each event Trigger,Delay,ListOfEventAssignments, each event assignment
              if (pEvent->isSetTrigger())
                {
                  pSBase = pEvent->getTrigger();
                  assert(pSBase != NULL);

                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();

                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }
                }

              if (pEvent->isSetDelay())
                {
                  pSBase = pEvent->getDelay();
                  assert(pSBase != NULL);

                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();

                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }
                }

              if (pEvent->getListOfEventAssignments() != NULL)
                {
                  pSBase = pEvent->getListOfEventAssignments();

                  if (pSBase->isSetMetaId())
                    {
                      id = pSBase->getMetaId();

                      if (metaIds.find(id) == metaIds.end())
                        {
                          metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                        }
                      else
                        {
                          CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                        }
                    }

                  unsigned int j, jMax = pEvent->getListOfEventAssignments()->size();

                  for (j = 0; j < jMax; ++j)
                    {
                      pSBase = pEvent->getEventAssignment(j);
                      assert(pSBase != NULL);

                      if (pSBase->isSetMetaId())
                        {
                          id = pSBase->getMetaId();

                          if (metaIds.find(id) == metaIds.end())
                            {
                              metaIds.insert(std::pair<const std::string, const SBase*>(id, pSBase));
                            }
                          else
                            {
                              CCopasiMessage(CCopasiMessage::WARNING, MCSBML + 67, id.c_str());
                            }
                        }
                    }
                }
            }
        }
    }
}
