/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/11 16:26:02 $
   End CVS Header */

#include "SBMLExporter.h"

#include "sbml/Unit.h"
#include "sbml/UnitKind.h"

SBMLExporter::SBMLExporter(): sbmlDocument(NULL)
{}

SBMLExporter::~SBMLExporter()
{
  if (this->sbmlDocument != NULL)
    {
      SBMLDocument_delete(this->sbmlDocument);
    }
}

bool SBMLExporter::exportSBML(const CModel* copasiModel, std::string sbmlFilename) throw (StdException)
{
  this->sbmlDocument = this->createSBMLDocumentFromCModel(copasiModel);
  if (sbmlDocument->getModel() != NULL)
    {
      SBMLWriter_t* writer = SBMLWriter_create();
      int returnValue = SBMLWriter_writeSBML(writer, sbmlDocument, sbmlFilename.c_str());
      SBMLWriter_delete(writer);
      if (returnValue == 0)
        {
          return true;
        }
      else
        {
          return false;
        }
    }
  else
    {
      return false;
    }
}

SBMLDocument_t* SBMLExporter::createSBMLDocumentFromCModel(const CModel* copasiModel, int sbmlVersion, int sbmlLevel)
{
  SBMLDocument_t sbmlDocument = SBMLDocument_createWith(sbmlLevel, sbmlVersion);
  Model_t* sbmlModel = this->createSBMLModelFromCModel(const CModel * copasiModel);
  SBMLDocument_setModel(sbmlDocument, sbmlModel);
  return sbmlDocument;
}

Model_t* SBMLExporter::createSBMLModelFromCModel(const CModel* copasiModel)
{
  Model_t* sbmlModel = Model_create();

  Model_setId(sbmlModel, copasiModel->getKey());
  if (copasModel->getName().size() != 0)
    {
      Model_setName(sbmlModel, copasiModel->getObjectName());
    }
  if (copasiModel->getComments().size() != 0)
    {
      Model_setComments(SBMLExporter::HTML_HEADER + copasiModel->getComments() + SBMLExporter::HTML_FOOTER);
    }
  if (!(copasiModel->getVolumeUnit() == CModel::l))
    {
      UnitDefinition_t* uDef = this->createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(copasiModel->getVolumeUnit());
      if (uDef != NULL)
        {
          Model_addUnitDefinition(sbmlModel, uDef);
        }
      else
        {
          throw StdException("Error. \"volume\" UnitDefinition is NULL.");
        }
    }
  if (!(copasiModel->getTimeUnit() == CModel::s))
    {
      UnitDefinition_t* uDef = this->createSBMLTimeUnitDefinitionFromCopasiVolumeUnit(copasiModel->getTimeUnit());
      if (uDef != NULL)
        {
          Model_addUnitDefinition(sbmlModel, uDef);
        }
      else
        {
          throw StdException("Error. \"time\" UnitDefinition is NULL.");
        }
    }
  if (!(copasiModel->getQuantityUnit() == CModel::Mol))
    {
      UnitDefinition_t* uDef = this->createSBMLSubstanceUnitDefinitionFromCopasiVolumeUnit(copasiModel->getQuantityUnit());
      if (uDef != NULL)
        {
          Model_addUnitDefinition(sbmlModel, uDef);
        }
      else
        {
          throw StdException("Error. \"substance\" UnitDefinition for is NULL.");
        }
    }
  for (unsigned int counter = 0; counter < copasiModel->getCompartments().size(); counter++)
    {
      Compartment_t* sbmlCompartment = this->createSBMLCompartmentFromCCompartment(copasiModel->getCompartments()[counter]);
      if (sbmlCompartment != NULL)
        {
          Model_addCompartment(sbmlModel, sbmlCompartment);
        }
      else
        {
          throw StdException("Error. SBML Compartment is NULL.");
        }
    }
  for (unsigned int counter = 0; counter < copasiModel->getMetabolites().size(); counter++)
    {
      Species_t* sbmlSpecies = this->createSBMLSpeciesFromCMetab(copasiModel->getMetabolites()[counter]);
      if (sbmlSpecies != NULL)
        {
          Model_addSpecies(sbmlModel, sbmlSpecies);
        }
      else
        {
          throw StdException("Error. SBML Species is NULL.");
        }
    }
  for (unsigned int counter = 0; counter < copasiModel->getReactions().size(); counter++)
    {
      Reaction_t* sbmlReaction = this->createSBMLReactionFromCReaction(copasiModel->getReactions()[counter]);
      if (sbmlReaction != NULL)
        {
          Model_addReaction(sbmlModel, sbmlReaction);
        }
      else
        {
          throw StdException("Error. SBML Reaction is NULL.");
        }
    }
  return sbmlModel;
}

UnitDefinition_t* SBMLExporter::createSBMLTimeUnitDefinitionFromCopasiTimeUnit(CModel::TimeUnit u)
{
  UnitDefinition_t* uDef = UnitDefinition_createWithName("time");
  Unit_t* unit = NULL;
  switch (u)
    {
    case CModel::d:
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, 0);
      Unit_setMultiplier(unit, 86400);
      break;
    case CModel::h:
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, 0);
      Unit_setMultiplier(unit, 3600);
      break;
    case CModel::m:
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, 0);
      Unit_setMultiplier(unit, 60);
      break;
    case CModel::ms:
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, -3);
      break;
    case CModel::micros:
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, -6);
      break;
    case CModel::ns:
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, -9);
      break;
    case CModel::ps:
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, -12);
      break;
    case CModel::fs:
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, -15);
      break;
    default:
      throw StdException("Error. Unknown copasi time unit.");
    }
  UnitDefinition_addUnit(uDef, unit);
  return uDef;
}

UnitDefinition_t* SBMLExporter::createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(CModel::QuantityUnit u)
{
  UnitDefinition_t* uDef = UnitDefinition_createWithName("substance");
  Unit_t* unit = NULL;
  switch (u)
    {
    case CModel::mMol:
      unit = Unit_createWith(UNIT_KIND_MOLE, 1, -3);
      break;
    case CModel::microMol:
      unit = Unit_createWith(UNIT_KIND_MOLE, 1, -6);
      break;
    case CModel::nMol:
      unit = Unit_createWith(UNIT_KIND_MOLE, 1, -9);
      break;
    case CModel::pMol:
      unit = Unit_createWith(UNIT_KIND_MOLE, 1, -12);
      break;
    case CModel::fMol:
      unit = Unit_createWith(UNIT_KIND_MOLE, 1, -15);
      break;
    case CModel::number:
      unit = Unit_createWith(UNIT_KIND_ITEM, 1, 1);
      break;
    default:
      throw StdException("Error. Unknown copasi quantity unit.");
    }
  UnitDefinition_addUnit(uDef, unit);
  return uDef;
}

UnitDefinition_t* SBMLExporter::createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(CModel::VolumeUnit u)
{
  UnitDefinition_t* uDef = UnitDefinition_createWithName("volume");
  Unit_t* unit = NULL;
  switch (u)
    {
    case CModel::ml:
      unit = Unit_createWith(UNIT_KIND_LITER, 1, -3);
      break;
    case CModel::microl:
      unit = Unit_createWith(UNIT_KIND_LITER, 1, -6);
      break;
    case CModel::nl:
      unit = Unit_createWith(UNIT_KIND_LITER, 1, -9);
      break;
    case CModel::pl:
      unit = Unit_createWith(UNIT_KIND_LITER, 1, -12);
      break;
    case CModel::fl:
      unit = Unit_createWith(UNIT_KIND_LITER, 1, -15);
      break;
    default:
      throw StdException("Error. Unknown copasi volume unit.");
    }
  UnitDefinition_addUnit(uDef, unit);
  return uDef;
}

Compartment_t* SBMLExporter::createSBMLCompartmentFromCCompartment(const CCompartment* copasiCompartment)
{
  return NULL;
}

Species_t* SBMLExporter::createSBMLSpeciesFromCMetab(const CMetab* copasiMetabolite)
{
  return NULL;
}

Reaction_t* SBMLExporter::createSBMLReactionFromCReaction(const CReaction* reaction)
{
  return NULL;
}

KineticLaw_t* SBMLExporter::createSBMLKineticLawFromCKinFunction(const CKinFunction* cKinFunction)
{
  return NULL;
}
