/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/sbml/Attic/SBMLExporter.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/06/14 17:50:31 $
   End CVS Header */

#include "SBMLExporter.h"

#include "sbml/Unit.h"
#include "sbml/UnitKind.h"
#include "sbml/SBMLWriter.h"

#include "sbml/ModifierSpeciesReference.h"

SBMLExporter::SBMLExporter(): sbmlDocument(NULL)
{
  this->HTML_HEADER = "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.01 Transitional//EN\">\n<html><head><meta http-equiv=\"Content-Type\" content=\"text/html; charset=iso-8859-1\">\n<title>Comments</title>\n</head><body>";

  this->HTML_FOOTER = "</body>\n</html>";
}

SBMLExporter::~SBMLExporter()
{
  if (this->sbmlDocument != NULL)
    {
      SBMLDocument_free(this->sbmlDocument);
    }
}

bool SBMLExporter::exportSBML(const CModel* copasiModel, std::string sbmlFilename) throw (StdException)
{
  this->sbmlDocument = this->createSBMLDocumentFromCModel(copasiModel, 2, 1);
  if (SBMLDocument_getModel(sbmlDocument) != NULL)
    {
      SBMLWriter_t* writer = SBMLWriter_create();
      int returnValue = SBMLWriter_writeSBML(writer, sbmlDocument, sbmlFilename.c_str());
      SBMLWriter_free(writer);
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
  SBMLDocument_t* sbmlDocument = SBMLDocument_createWith(sbmlLevel, sbmlVersion);
  Model_t* sbmlModel = this->createSBMLModelFromCModel(copasiModel);
  SBMLDocument_setModel(sbmlDocument, sbmlModel);
  return sbmlDocument;
}

Model_t* SBMLExporter::createSBMLModelFromCModel(const CModel* copasiModel)
{
  Model_t* sbmlModel = Model_create();

  Model_setId(sbmlModel, copasiModel->getKey().c_str());
  if (copasiModel->getObjectName().size() != 0)
    {
      Model_setName(sbmlModel, copasiModel->getObjectName().c_str());
    }
  if (copasiModel->getComments().size() != 0)
    {
      SBase_setNotes((SBase_t*)sbmlModel, (this->HTML_HEADER + copasiModel->getComments() + this->HTML_FOOTER).c_str());
    }
  if (!(copasiModel->getVolumeUnit() == "l"))
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
  if (!(copasiModel->getTimeUnit() == "s"))
    {
      UnitDefinition_t* uDef = this->createSBMLTimeUnitDefinitionFromCopasiTimeUnit(copasiModel->getTimeUnit());
      if (uDef != NULL)
        {
          Model_addUnitDefinition(sbmlModel, uDef);
        }
      else
        {
          throw StdException("Error. \"time\" UnitDefinition is NULL.");
        }
    }
  if (!(copasiModel->getQuantityUnit() == "Mol"))
    {
      UnitDefinition_t* uDef = this->createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(copasiModel->getQuantityUnit());
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

UnitDefinition_t* SBMLExporter::createSBMLTimeUnitDefinitionFromCopasiTimeUnit(const std::string u)
{
  UnitDefinition_t* uDef = UnitDefinition_createWithName("time");
  Unit_t* unit = NULL;

  if (u == "d")
    {
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, 0);
      Unit_setMultiplier(unit, 86400);
    }
  else if (u == "h")
    {
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, 0);
      Unit_setMultiplier(unit, 3600);
    }
  else if (u == "m")
    {
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, 0);
      Unit_setMultiplier(unit, 60);
    }

  else if (u == "ms")
    {
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, -3);
    }
  else if (u == "\xc2\xb5s")
    {
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, -6);
    }
  else if (u == "ns")
    {
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, -9);
    }
  else if (u == "ps")
    {
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, -12);
    }
  else if (u == "fs")
    {
      unit = Unit_createWith(UNIT_KIND_SECOND, 1, -15);
    }
  else
    {
      throw StdException("Error. Unknown copasi time unit.");
    }

  UnitDefinition_addUnit(uDef, unit);
  return uDef;
}

UnitDefinition_t* SBMLExporter::createSBMLSubstanceUnitDefinitionFromCopasiQuantityUnit(const std::string u)
{
  UnitDefinition_t* uDef = UnitDefinition_createWithName("substance");
  Unit_t* unit = NULL;
  if (u == "mMol")
    {
      unit = Unit_createWith(UNIT_KIND_MOLE, 1, -3);
    }
  else if (u == "\xc2\xb5Mol")
    {
      unit = Unit_createWith(UNIT_KIND_MOLE, 1, -6);
    }
  else if (u == "nMol")
    {
      unit = Unit_createWith(UNIT_KIND_MOLE, 1, -9);
    }
  else if (u == "pMol")
    {
      unit = Unit_createWith(UNIT_KIND_MOLE, 1, -12);
    }
  else if (u == "fMol")
    {
      unit = Unit_createWith(UNIT_KIND_MOLE, 1, -15);
    }
  else if (u == "#")
    {
      unit = Unit_createWith(UNIT_KIND_ITEM, 1, 1);
    }
  else
    {
      throw StdException("Error. Unknown copasi quantity unit.");
    }
  UnitDefinition_addUnit(uDef, unit);
  return uDef;
}

UnitDefinition_t* SBMLExporter::createSBMLVolumeUnitDefinitionFromCopasiVolumeUnit(const std::string u)
{
  UnitDefinition_t* uDef = UnitDefinition_createWithName("volume");
  Unit_t* unit = NULL;
  if (u == "ml")
    {
      unit = Unit_createWith(UNIT_KIND_LITER, 1, -3);
    }
  else if (u == "\xc2\xb5l")
    {
      unit = Unit_createWith(UNIT_KIND_LITER, 1, -6);
    }
  else if (u == "nl")
    {
      unit = Unit_createWith(UNIT_KIND_LITER, 1, -9);
    }
  else if (u == "pl")
    {
      unit = Unit_createWith(UNIT_KIND_LITER, 1, -12);
    }
  else if (u == "fl")
    {
      unit = Unit_createWith(UNIT_KIND_LITER, 1, -15);
    }
  else if (u == "m3")
    {
      unit = Unit_createWith(UNIT_KIND_METER, 3, 1);
    }
  else
    {
      throw StdException("Error. Unknown copasi volume unit.");
    }
  UnitDefinition_addUnit(uDef, unit);
  return uDef;
}

Compartment_t* SBMLExporter::createSBMLCompartmentFromCCompartment(const CCompartment* copasiCompartment)
{
  Compartment_t* sbmlCompartment = Compartment_create();
  Compartment_setId(sbmlCompartment, copasiCompartment->getKey().c_str());
  Compartment_setName(sbmlCompartment, copasiCompartment->getObjectName().c_str());
  Compartment_setSpatialDimensions(sbmlCompartment, 3);
  Compartment_setConstant(sbmlCompartment, 1);
  Compartment_setVolume(sbmlCompartment, copasiCompartment->getInitialVolume());
  return sbmlCompartment;
}

Species_t* SBMLExporter::createSBMLSpeciesFromCMetab(const CMetab* copasiMetabolite)
{
  Species_t* sbmlSpecies = Species_create();
  Species_setId(sbmlSpecies, copasiMetabolite->getKey().c_str());
  Species_setName(sbmlSpecies, copasiMetabolite->getObjectName().c_str());
  Species_setBoundaryCondition(sbmlSpecies, false);
  Species_setCharge(sbmlSpecies, 0);
  Species_setConstant(sbmlSpecies, copasiMetabolite->getStatus() == CMetab::METAB_FIXED);
  Species_setCompartment(sbmlSpecies, copasiMetabolite->getCompartment()->getKey().c_str());
  Species_setInitialAmount(sbmlSpecies, copasiMetabolite->getInitialNumber());
  return sbmlSpecies;
}

Reaction_t* SBMLExporter::createSBMLReactionFromCReaction(const CReaction* copasiReaction)
{
  Reaction_t* sbmlReaction = Reaction_create();
  Reaction_setId(sbmlReaction, copasiReaction->getKey().c_str());
  Reaction_setName(sbmlReaction, copasiReaction->getObjectName().c_str());
  Reaction_setReversible(sbmlReaction, copasiReaction->isReversible());
  const CChemEq chemicalEquation = copasiReaction->getChemEq();
  for (unsigned int counter = 0; counter < chemicalEquation.getSubstrates().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getSubstrates()[counter];
      SpeciesReference_t* sRef = SpeciesReference_create();
      SpeciesReference_setSpecies(sRef, element->getMetaboliteKey().c_str());
      SpeciesReference_setStoichiometry(sRef, element->getMultiplicity());
      SpeciesReference_setDenominator(sRef, 1);
      Reaction_addReactant(sbmlReaction, sRef);
    }
  for (unsigned int counter = 0; counter < chemicalEquation.getProducts().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getProducts()[counter];
      SpeciesReference_t* sRef = SpeciesReference_create();
      SpeciesReference_setSpecies(sRef, element->getMetaboliteKey().c_str());
      SpeciesReference_setStoichiometry(sRef, element->getMultiplicity());
      SpeciesReference_setDenominator(sRef, 1);
      Reaction_addProduct(sbmlReaction, sRef);
    }
  for (unsigned int counter = 0; counter < chemicalEquation.getModifiers().size(); counter++)
    {
      CChemEqElement* element = chemicalEquation.getModifiers()[counter];
      ModifierSpeciesReference_t* sRef = ModifierSpeciesReference_create();
      ModifierSpeciesReference_setSpecies(sRef, element->getMetaboliteKey().c_str());
      Reaction_addModifier(sbmlReaction, sRef);
    }
  KineticLaw_t* kLaw = this->createSBMLKineticLawFromCReaction(copasiReaction);
  Reaction_setKineticLaw(sbmlReaction, kLaw);
  return sbmlReaction;
}

KineticLaw_t* SBMLExporter::createSBMLKineticLawFromCReaction(const CReaction* copasiReaction)
{
  KineticLaw_t* kLaw = KineticLaw_create();
  if (copasiReaction->getFunction().getType() == CFunction::MassAction)
    {
      const CMassAction cMassAction = static_cast<const CMassAction>(copasiReaction->getFunction());
      ASTNode_t* forwardNode = ASTNode_createWithType(AST_TIMES);

      ASTNode_t* parameterNode1 = ASTNode_createWithType(AST_NAME);
      std::string parameterName1 = cMassAction.getParameters()[0]->getObjectName();
      ASTNode_setName(parameterNode1, parameterName1.c_str());
      Parameter_t* parameter1 = Parameter_create();
      Parameter_setName(parameter1, parameterName1.c_str());
      Parameter_setId(parameter1, parameterName1.c_str());
      Parameter_setValue(parameter1, copasiReaction->getParameterValue(parameterName1));
      KineticLaw_addParameter(kLaw, parameter1);

      ASTNode_addChild(forwardNode, parameterNode1);
      ASTNode_addChild(forwardNode, this->createTimesTree(copasiReaction->getChemEq().getSubstrates()));
      if (cMassAction.isReversible() == TriTrue)
        {
          ASTNode_t* backwardNode = ASTNode_createWithType(AST_TIMES);

          ASTNode_t* parameterNode2 = ASTNode_createWithType(AST_NAME);
          std::string parameterName2 = cMassAction.getParameters()[2]->getObjectName();
          ASTNode_setName(parameterNode2, parameterName2.c_str());
          Parameter_t* parameter2 = Parameter_create();
          Parameter_setName(parameter2, parameterName2.c_str());
          Parameter_setId(parameter2, parameterName2.c_str());
          Parameter_setValue(parameter2, copasiReaction->getParameterValue(parameterName2));
          KineticLaw_addParameter(kLaw, parameter2);
          ASTNode_addChild(backwardNode, parameterNode2);

          ASTNode_addChild(backwardNode, this->createTimesTree(copasiReaction->getChemEq().getProducts()));
          ASTNode_t* tempNode = ASTNode_createWithType(AST_MINUS);
          ASTNode_addChild(tempNode, forwardNode);
          ASTNode_addChild(tempNode, backwardNode);
          forwardNode = tempNode;
        }
      KineticLaw_setMath(kLaw, forwardNode);
    }
  else
    {
      CKinFunction cKinFunction = static_cast<CKinFunction>(copasiReaction->getFunction());
      ASTNode_t* node = this->createASTNodeFromCNodeK(cKinFunction.getNodes()[0]->getLeft(), cKinFunction, copasiReaction->getParameterMappings());
      KineticLaw_setMath(kLaw, node);
      /* add the parameters */
      for (unsigned int counter = 0; counter < copasiReaction->getFunctionParameters().size(); counter++)
        {
          const CFunctionParameter* para = copasiReaction->getFunctionParameters()[counter];
          if (para->getUsage() == "PARAMETER")
            {
              Parameter_t* sbmlPara = Parameter_create();

              CFunctionParameter::DataType dataType;
              unsigned C_INT32 index = cKinFunction.getParameters().findParameterByName(para->getObjectName(), dataType);
              std::string parameterName = copasiReaction->getParameterMappings()[index][0];

              Parameter_setName(sbmlPara, parameterName.c_str());
              Parameter_setValue(sbmlPara, copasiReaction->getParameterValue(parameterName));
            }
        }
    }
  return kLaw;
}

ASTNode_t* SBMLExporter::createASTNodeFromCNodeK(const CNodeK& cNodeK, const CKinFunction& kinFunction, const std::vector< std::vector < std::string > >& vect)
{
  ASTNode_t* node = ASTNode_create();
  char mType = cNodeK.getType();
  char mSubtype = cNodeK.getSubtype();
  ASTNode_t* childNode = NULL;
  switch (mType)
    {
    case N_NUMBER:
      ASTNode_setType(node, AST_REAL);
      ASTNode_setReal(node, cNodeK.getConstant());
      break;
    case N_IDENTIFIER:
      ASTNode_setType(node, AST_NAME);
      CFunctionParameter::DataType dataType;
      ASTNode_setName(node, vect[kinFunction.getParameters().findParameterByName(cNodeK.getName(), dataType)][0].c_str());
      break;
    case N_OPERATOR:
      switch (mSubtype)
        {
        case '+':
          ASTNode_setType(node, AST_PLUS);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        case '-':
          ASTNode_setType(node, AST_MINUS);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        case '*':
          ASTNode_setType(node, AST_TIMES);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        case '/':
          ASTNode_setType(node, AST_DIVIDE);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        case '^':
          ASTNode_setType(node, AST_POWER);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        default:
          break;
        }
      break;
    case N_FUNCTION:
      switch (mSubtype)
        {
        case '+':
          node = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          break;
        case '-':
          ASTNode_setType(node, AST_MINUS);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        case N_EXP:
          ASTNode_setType(node, AST_FUNCTION_EXP);
          ASTNode_setName(node, "exp");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          childNode = this->createASTNodeFromCNodeK(cNodeK.getRight(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        case N_LOG:
          ASTNode_setType(node, AST_FUNCTION_LN);
          ASTNode_setName(node, "ln");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        case N_LOG10:
          ASTNode_setType(node, AST_FUNCTION_LOG);
          ASTNode_setName(node, "log");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        case N_SIN:
          ASTNode_setType(node, AST_FUNCTION_SIN);
          ASTNode_setName(node, "sin");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        case N_COS:
          ASTNode_setType(node, AST_FUNCTION_COS);
          ASTNode_setName(node, "cos");
          childNode = this->createASTNodeFromCNodeK(cNodeK.getLeft(), kinFunction, vect);
          ASTNode_addChild(node, childNode);
          break;
        default:
          break;
        }
      break;
    default:
      break;
    }
  return node;
}

ASTNode_t* SBMLExporter::createTimesTree(const CCopasiVector<CChemEqElement >& vect, unsigned int pos)
{
  ASTNode_t* node = NULL;
  if (pos == vect.size() - 1)
    {
      node = ASTNode_createWithType(AST_NAME);
      ASTNode_setName(node, vect[pos]->getMetaboliteKey().c_str());
    }
  else
    {
      node = ASTNode_createWithType(AST_TIMES);
      ASTNode_t* child = ASTNode_createWithType(AST_NAME);
      ASTNode_setName(child, vect[pos]->getMetaboliteKey().c_str());
      ASTNode_addChild(node, child);
      ASTNode_addChild(node, this->createTimesTree(vect, pos + 1));
    }
  return node;
}
