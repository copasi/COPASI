// Copyright (C) 2019 - 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SEDMLUtils.cpp
 *
 *  Created on: 15 Jul 2013
 *      Author: dada
 */

//#include <zip.h>
#include <sstream>
#include <iostream>
#include <vector>
#include "SEDMLUtils.h"

#include <sedml/SedTypes.h>
#include <sbml/SBMLTypes.h>

#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CDataObject.h"

std::string SEDMLUtils::findIdByNameAndType(
  const std::map<const CDataObject*, SBase*>& map,
  int typeCode,
  const std::string& name)
{
  std::map<const CDataObject*, SBase*>::const_iterator it = map.begin();

  std::string::size_type compartmentStart = name.find("{");

  std::string compId;

  if (compartmentStart != std::string::npos)
    {
      std::string compName = name.substr(compartmentStart + 1, name.size() - compartmentStart - 2);
      SEDMLUtils::removeCharactersFromString(compName, "\"");

      compId = findIdByNameAndType(map, SBML_COMPARTMENT, compName);
    }

  while (it != map.end())
    {
      SBase* current = it->second;
      const CDataObject* object = it->first;
      std::string displayName = object->getObjectDisplayName();

      if (((current->getTypeCode() & typeCode) != typeCode))
        {
          ++it;
          continue;
        }

      if (current->getName() == name)
        return current->getId();

      if (typeCode == SBML_SPECIES  && compartmentStart != std::string::npos)
        {
          if (displayName == name)
            {
              Species* species = static_cast<Species*>(current);

              if (species->getCompartment() == compId)
                return species->getId();
            }
        }

      ++it;
    }

  return "";
}

std::string
SEDMLUtils::getXPathAndName(std::string& sbmlId,
                            const std::string &type,
                            const CModel *pModel,
                            const CDataModel& dataModel)
{
  std::vector<std::string> stringsContainer;
  std::string targetXPathString;
  const std::map<const CDataObject*, SBase*>& copasi2sbmlmap =
    const_cast<CDataModel&>(dataModel).getCopasi2SBMLMap();
  std::string displayName = sbmlId;

  if (copasi2sbmlmap.empty())
    {
      // this should not be happening, as this is used to verify the element.
      return "";
    }

  std::map<CDataObject*, SBase*>::const_iterator pos;

  if (type == "Concentration" || type == "InitialConcentration")
    {
      targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id=\'";
      //remove unwanted characters from the plot item object name
      removeCharactersFromString(displayName, "[]");

      if (type == "InitialConcentration")
        {
          displayName = displayName.substr(0, displayName.length() - 2);
        }

      sbmlId = findIdByNameAndType(copasi2sbmlmap, SBML_SPECIES, displayName);

      if (!sbmlId.empty())
        {
          return targetXPathString + sbmlId + "\']";
        }

      return "";
    }

  if (type == "Flux")
    {
      targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id=\'";

      std::string::size_type pos = displayName.rfind(".Flux");
      displayName = displayName.substr(1, pos - 2);

      sbmlId = findIdByNameAndType(copasi2sbmlmap, SBML_REACTION, displayName);

      if (!sbmlId.empty())
        {
          return targetXPathString + sbmlId + "\']";
        }

      return "";
    }

  if (type == "Value" || type == "InitialValue")
    {
      if (type == "InitialValue")
        {
          displayName = displayName.substr(0, displayName.find(".InitialValue"));
        }

      targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfParameters/sbml:parameter[@id=\'";
      splitStrings(displayName, '[', stringsContainer);

      if (stringsContainer.size() == 1)
        {
          // not found ... might be a local parameter
          size_t parameterPos = displayName.rfind(".");

          if (parameterPos != std::string::npos)
            {
              std::string parameterId = displayName.substr(parameterPos + 1);
              std::string reactionName = displayName.substr(1, parameterPos - 2);
              sbmlId = findIdByNameAndType(copasi2sbmlmap, SBML_REACTION, reactionName);

              std::stringstream xpath;
              xpath << "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id=\'";
              xpath << sbmlId;
              xpath << "\']/sbml:kineticLaw/sbml:listOfParameters/sbml:parameter[@id=\'";
              xpath << parameterId;
              xpath << "\']";

              sbmlId += "_" + parameterId;

              return xpath.str();
            }

          removeCharactersFromString(displayName, "()");
          splitStrings(displayName, '.', stringsContainer);

          if (stringsContainer.size() == 2)
            {
              sbmlId = stringsContainer[0] + "_" + stringsContainer[1];
              std::stringstream xpath;
              xpath << "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id=\'";
              xpath << stringsContainer[0];
              xpath << "\']/sbml:kineticLaw/sbml:listOfParameters/sbml:parameter[@id=\'";
              xpath << stringsContainer[1];
              xpath << "\']";
              return xpath.str();
            }
        }

      displayName = stringsContainer[1];

      removeCharactersFromString(displayName, "]");

      sbmlId = findIdByNameAndType(copasi2sbmlmap, SBML_PARAMETER , displayName);

      if (sbmlId.empty())
        sbmlId = findIdByNameAndType(copasi2sbmlmap, SBML_LOCAL_PARAMETER , displayName);

      if (!sbmlId.empty())
        {
          return targetXPathString + sbmlId + "\']";
        }

      return "";
    }

  if (type == "Volume" || type == "InitialVolume")
    {
      targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfCompartments/sbml:compartment[@id=\'";
      splitStrings(displayName, '[', stringsContainer);
      displayName = stringsContainer[1];

      if (type == "InitialVolume")
        {
          displayName = displayName.substr(0, displayName.find(".InitialVolume"));
        }

      if (type == "Volume")
        {
          displayName = displayName.substr(0, displayName.find(".Volume"));
        }

      removeCharactersFromString(displayName, "]");

      sbmlId = findIdByNameAndType(copasi2sbmlmap, SBML_COMPARTMENT, displayName);

      if (!sbmlId.empty())
        {
          return targetXPathString + sbmlId + "\']";
        }

      return "";
    }

  if (type == "Time" || type == "Initial Time")
    return SEDML_TIME_URN;

  sbmlId = "";
  return targetXPathString;
}

const CDataObject*
SEDMLUtils::resolveDatagenerator(CModel *model, const SedDataGenerator* dataReference)
{
  // for now one variable only
  if (dataReference == NULL || dataReference->getNumVariables() < 1) return NULL;

  const SedVariable* var = dataReference->getVariable(0);

  if (var->isSetSymbol() && var->getSymbol() == SEDML_TIME_URN)
    {
      return static_cast<const CDataObject *>(model->getObject(CCommonName("Reference=Time")));
    }

  return resolveVariable(model, var);
}

std::string
SEDMLUtils::translateTargetXpathInSBMLId(const std::string &xpath, std::string& SBMLType)
{
  std::vector<std::string> xpathStrings;
  std::string id, nextString;

  splitStrings(xpath, ':', xpathStrings);
  nextString = xpathStrings[xpathStrings.size() - 1];

  splitStrings(nextString, '[', xpathStrings);
  SBMLType = xpathStrings[0];
  nextString = xpathStrings[xpathStrings.size() - 1];

  splitStrings(nextString, '=', xpathStrings);
  nextString = xpathStrings[xpathStrings.size() - 1];
  splitStrings(nextString, ']', xpathStrings);
  id = xpathStrings[0];

  //remove the remaining unwanted characters
  removeCharactersFromString(id, "\"']");
  return id;
}

const CDataObject*
SEDMLUtils::resolveXPath(const CModel *model,  const std::string& xpath,
                         bool initial /* = false*/)
{
  std::string SBMLType;
  std::string id = translateTargetXpathInSBMLId(xpath, SBMLType);
  const CDataObject* result = getObjectForSbmlId(model, id, SBMLType, initial);

  if (result == NULL)
    {
      // old method fails here, possibly a local parameter
      size_t pos = xpath.find("/sbml:kineticLaw/sbml:listOfParameters/");

      if (pos != std::string::npos)
        {
          std::string reactionType;
          std::string reactionId = translateTargetXpathInSBMLId(xpath.substr(0, pos), reactionType);
          const CDataObject* flux = getObjectForSbmlId(model, reactionId, reactionType);

          if (flux != NULL)
            {
              const CDataObject* reactionObj = flux->getObjectParent();
              std::string cn = "ParameterGroup=Parameters,Parameter=" + id + ",Reference=Value";
              return dynamic_cast<const CDataObject*>(reactionObj->getObject(cn));
            }
        }
    }

  return result;
}

const CDataObject *
SEDMLUtils::resolveVariable(CModel * model, const SedVariable * variable)
{
  if (!variable)
    return NULL;

  const CDataObject * obj = resolveXPath(model, variable->getTarget());

  std::string term = variable->isSetTerm() ? variable->getTerm() : variable->getSymbol();


  if (!term.empty())
    {
      if (obj->getObjectType() == "Reference")
        obj = obj->getObjectParent();

      const CMetab * pMetab = dynamic_cast< const CMetab * >(obj);
      const CReaction * pReaction = dynamic_cast< const CReaction * >(obj);
      const CModelEntity * pME = dynamic_cast< const CModelEntity * >(obj);

      if (term == SEDML_KISAO_PARTICLENUMBER && pMetab)
        return pMetab->getValueReference();

      if (term == SEDML_KISAO_PARTICLE_RATE && pMetab)
        return pMetab->getRateReference();

      if (term == SEDML_KISAO_CONCENTRATION && pMetab)
        return pMetab->getConcentrationReference();

      if ((term == SEDML_KISAO_CONCENTRATION_RATE || term == SEDML_KISAO_RATEOFCHANGE) && pMetab)
        return pMetab->getConcentrationRateReference();

      if (term == SEDML_KISAO_RATE && pME)
        return pME->getRateReference();

      if (term == SEDML_KISAO_AMOUNT && pMetab)
        {
          CModelValue * pMV = createAmountMV(model, pMetab);

          if (pMV != NULL)
            return pMV->getValueReference();
        }

      CCopasiMessage(CCopasiMessage::WARNING,
                     "Encountered unsupported KISAO term '%s' while resolving Variable.", term.c_str());
    }

  return obj;
}

CModelValue * SEDMLUtils::createAmountMV(CModel * pModel, const CMetab * pMetab)
{
  std::string name = pMetab->getObjectName() + " (amount)";
  CModelValue * pMV = NULL;

  if (pModel->getModelValues().getIndex(name) == C_INVALID_INDEX)
    {
      pMV = pModel->createModelValue(name);
    }
  else
    {
      pMV = &pModel->getModelValues()[name];
    }

  pMV->setStatus(CModelEntity::Status::ASSIGNMENT);
  std::stringstream expr;
  expr << "<" << pMetab->getConcentrationReference()->getCN() << "> * "
       << "<" << pMetab->getCompartment()->getValueReference()->getCN() << ">";
  pMV->setExpression(expr.str());

  return pMV;
}

std::string&
SEDMLUtils::removeCharactersFromString(std::string& str, const std::string& characters)
{
  for (unsigned int ii = 0; ii < characters.length(); ++ii)
    {
      str.erase(std::remove(str.begin(), str.end(), characters[ii]), str.end());
    }

  return str;
}

std::string
SEDMLUtils::getXPathForObject(const CDataObject& object)
{
  std::string sbmlId = getSbmlId(object);
  std::string targetXPathString;

  if (!sbmlId.empty())
    {

      targetXPathString = getXPathForSbmlIdAndType(object.getObjectName(), sbmlId);

      if (!targetXPathString.empty())
        return targetXPathString;
    }

  const std::string& type = object.getObjectName();
  const CDataModel* dm = object.getObjectDataModel();
  std::string yAxis = object.getObjectDisplayName();
  targetXPathString = getXPathAndName(yAxis, type,
                                      dm->getModel(), *dm);
  return targetXPathString;
}

std::string SEDMLUtils::getXPathForSbmlIdAndType(const std::string& type, const std::string& sbmlId)
{
  if (type == "Concentration" || type == "InitialConcentration")
    return "/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id=\'" + sbmlId + "\']";

  if (type == "Flux")
    return "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id=\'" + sbmlId + "\']";

  if (type == "Volume" || type == "InitialVolume")
    return "/sbml:sbml/sbml:model/sbml:listOfCompartments/sbml:compartment[@id=\'" + sbmlId + "\']";

  if (type == "Value" || type == "InitialValue")
    return "/sbml:sbml/sbml:model/sbml:listOfParameters/sbml:parameter[@id=\'" + sbmlId + "\']";

  return std::string();
}

std::string SEDMLUtils::getXPathForObjectAndType(const CDataObject & object, const std::string & sbmlId)
{
  const CDataObject * pObject = object.getObjectType() == "Reference" ? object.getObjectParent() : &object;

  if (pObject)
    {
      const CMetab * pMetab = dynamic_cast< const CMetab * >(pObject);

      if (pMetab)
        {
          return "/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id=\'" + sbmlId + "\']";
        }

      const CModelValue * pMV = dynamic_cast< const CModelValue * >(pObject);

      if (pMV)
        {
          return "/sbml:sbml/sbml:model/sbml:listOfParameters/sbml:parameter[@id=\'" + sbmlId + "\']";
        }

      const CCompartment * pComp = dynamic_cast< const CCompartment * >(pObject);

      if (pComp)
        {
          return "/sbml:sbml/sbml:model/sbml:listOfCompartments/sbml:compartment[@id=\'" + sbmlId + "\']";
        }

      const CReaction * pRea = dynamic_cast< const CReaction * >(pObject);

      if (pRea)
        {
          return "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id=\'" + sbmlId + "\']";
        }

      const CReaction * pParentReaction = dynamic_cast< const CReaction * >(pObject->getObjectAncestor("Reaction"));

      if (pParentReaction)
        {
          std::stringstream xpath;
          xpath << "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id=\'";
          xpath << pParentReaction->getSBMLId();
          xpath << "\']/sbml:kineticLaw/sbml:listOfParameters/sbml:parameter[@id=\'";
          xpath << pObject->getObjectName();
          xpath << "\']";
          return xpath.str();
        }
    }


  return std::string();
}

std::string SEDMLUtils::getNextId(const std::string& base, int count)
{
  std::stringstream str; str << base << count;
  return str.str();
}

std::string SEDMLUtils::getSbmlId(const CDataObject& object)
{
  const CModelEntity* entity = dynamic_cast<const CModelEntity*>(&object);

  if (entity != NULL)
    return entity->getSBMLId();

  entity = dynamic_cast<const CModelEntity*>(object.getObjectParent());

  if (entity != NULL)
    return entity->getSBMLId();

  return std::string();
}

//split: receives a char delimiter and string and a vector of strings that will contain the splited strings
//this is presently a hack to parse the XPath based target attribute in SEDML. A better solution may be
//necessary in the future.

void
SEDMLUtils::splitStrings(const std::string &xpath, char delim,
                         std::vector<std::string> &xpathStrings)
{
  std::string myPath = xpath;
  xpathStrings.clear();
  std::string next;

  // For each character in the string
  for (std::string::const_iterator it = xpath.begin(); it != xpath.end(); it++)
    {
      // check delimiter character
      if (*it == delim)
        {
          if (!next.empty())
            {
              // Add them to the xpathStrings vector
              xpathStrings.push_back(next);
              next.clear();
            }
        }
      else
        {
          next += *it;
        }
    }

  if (!next.empty())
    xpathStrings.push_back(next);
}

int SEDMLUtils::lineTypeToSed(int linetype)
{
for (auto item : COPASI_LINE_STYLE_MAP)
    {
      if (item.first == linetype)
        return item.second;
    }

  return 0;
}

int SEDMLUtils::lineTypeFromSed(int linetype)
{
for (auto item : COPASI_LINE_STYLE_MAP)
    {
      if (item.second == linetype)
        return item.first;
    }

  return 0;
}

int SEDMLUtils::symbolToSed(int symbol)
{
for (auto item : COPASI_SYMBOL_MAP)
    {
      if (item.first == symbol)
        return item.second;
    }

  return 0;
}

int SEDMLUtils::symbolFromSed(int symbol)
{
for (auto item : COPASI_SYMBOL_MAP)
    {
      if (item.second == symbol)
        return item.first;
    }

  return 0;
}

std::string SEDMLUtils::argbToRgba(const std::string & argb, bool includeHash)
{
  if (argb.length() < 8)
    return argb;

  int offset = argb[0] == '#' ? 1 : 0;

  std::string a = argb.substr(offset, 2);

  std::string result = argb.substr(offset + 2) + a;

  if (includeHash)
    return std::string("#") + result;

  return result;
}

std::string SEDMLUtils::rgbaToArgb(const std::string & rgba, bool includeHash)
{
  std::string::size_type len = rgba.length();

  if (len < 8)
    return rgba;

  int offset = rgba[0] == '#' ? 1 : 0;

  std::string a = rgba.substr(len - 2);

  std::string result = a + rgba.substr(offset, len - 2 - offset);

  if (includeHash)
    return std::string("#") + result;

  return result;
}

int SEDMLUtils::getAlphaFromArgb(const std::string & argb)
{
  if (argb.length() < 8)
    return 255;

  int offset = argb[0] == '#' ? 1 : 0;

  int result = std::stoi(argb.substr(offset, 2));

  return result;
}

int SEDMLUtils::getAlphaFromRgba(const std::string & rgba)
{
  std::string::size_type len = rgba.length();

  if (len < 8)
    return 255;

  int offset = rgba[0] == '#' ? 1 : 0;

  int result = std::stoi(rgba.substr(len - 2));
  return result;
}

const CDataObject *
SEDMLUtils::getObjectForSbmlId(const CModel* pModel, const std::string& id, const std::string& SBMLType, bool initial/* = false*/)
{
  if (SBMLType == "Time")
    return static_cast<const CDataObject *>(pModel->getObject(CCommonName("Reference=Time")));

  if (SBMLType == "species")
    {
      size_t iMet, imax = pModel->getMetabolites().size();

      for (iMet = 0; iMet < imax; ++iMet)
        {
          // the importer should not need to change the initial concentration
          // pModel->getMetabolites()[iMet].setInitialConcentration(0.896901);

          if (pModel->getMetabolites()[iMet].getSBMLId() == id)
            {
              if (initial)
                return pModel->getMetabolites()[iMet].getInitialConcentrationReference();

              return pModel->getMetabolites()[iMet].getConcentrationReference();
            }
        }
    }
  else if (SBMLType == "reaction")
    {
      size_t iMet, imax = pModel->getReactions().size();

      for (iMet = 0; iMet < imax; ++iMet)
        {
          if (pModel->getReactions()[iMet].getSBMLId() == id)
            {
              if (initial)
                return NULL;

              return pModel->getReactions()[iMet].getFluxReference();
            }
        }
    }
  else if (SBMLType == "parameter")
    {
      size_t iMet, imax = pModel->getModelValues().size();

      for (iMet = 0; iMet < imax; ++iMet)
        {
          if (pModel->getModelValues()[iMet].getSBMLId() == id)
            {
              if (initial)
                return pModel->getModelValues()[iMet].getInitialValueReference();

              return pModel->getModelValues()[iMet].getValueReference();
            }
        }
    }

  else if (SBMLType == "compartment")
    {
      size_t iComp, imax = pModel->getCompartments().size();

      for (iComp = 0; iComp < imax; ++iComp)
        {
          if (pModel->getCompartments()[iComp].getSBMLId() == id)
            {
              if (initial)
                return pModel->getCompartments()[iComp].getInitialValueReference();

              return pModel->getCompartments()[iComp].getValueReference();
            }
        }
    }

  return NULL;
}

std::map< int, int > SEDMLUtils::COPASI_SYMBOL_MAP =
{
  {(int)CPlotItem::SymbolType::Circle, SEDML_MARKERTYPE_CIRCLE},
  {(int)CPlotItem::SymbolType::Diamond, SEDML_MARKERTYPE_DIAMOND},
  {(int)CPlotItem::SymbolType::hDash, SEDML_MARKERTYPE_HDASH},
  {(int)CPlotItem::SymbolType::None, SEDML_MARKERTYPE_NONE},
  {(int) CPlotItem::SymbolType::Plus, SEDML_MARKERTYPE_PLUS},
  {(int) CPlotItem::SymbolType::LargeCross, SEDML_MARKERTYPE_PLUS},
  {(int) CPlotItem::SymbolType::SmallCross, SEDML_MARKERTYPE_PLUS},
  {(int) CPlotItem::SymbolType::Square, SEDML_MARKERTYPE_SQUARE},
  {(int)CPlotItem::SymbolType::Star, SEDML_MARKERTYPE_STAR},
  {(int)CPlotItem::SymbolType::TriangleDown, SEDML_MARKERTYPE_TRIANGLEDOWN},
  {(int)CPlotItem::SymbolType::TriangleLeft, SEDML_MARKERTYPE_TRIANGLELEFT},
  {(int)CPlotItem::SymbolType::TriangleRight, SEDML_MARKERTYPE_TRIANGLERIGHT},
  {(int)CPlotItem::SymbolType::TriangleUp, SEDML_MARKERTYPE_TRIANGLEUP},
  {(int)CPlotItem::SymbolType::vDash, SEDML_MARKERTYPE_VDASH},
  {(int)CPlotItem::SymbolType::xCross, SEDML_MARKERTYPE_XCROSS}
};

std::map< int, int > SEDMLUtils::COPASI_LINE_STYLE_MAP =
{
  {(int) CPlotItem::LineStyle::Dashed, SEDML_LINETYPE_DASH},
  {(int) CPlotItem::LineStyle::DotDash, SEDML_LINETYPE_DASHDOT},
  {(int) CPlotItem::LineStyle::DotDotDash, SEDML_LINETYPE_DASHDOTDOT},
  {(int) CPlotItem::LineStyle::Dotted, SEDML_LINETYPE_DOT},
  {(int) CPlotItem::LineStyle::None, SEDML_LINETYPE_NONE},
  {(int) CPlotItem::LineStyle::Solid, SEDML_LINETYPE_SOLID},
};


std::map< std::string, std::string > SEDMLUtils::PARAMETER_KISAO_MAP =
{
  {"KISAO:0000209", "Relative Tolerance"},
  {"KISAO:0000211", "Absolute Tolerance"},
  {"KISAO:0000216", "Integrate Reduced Model"},
  {"KISAO:0000415", "Max Internal Steps"},
  {"KISAO:0000467", "Max Internal Step Size"},
  {"KISAO:0000488", "Random Seed", },
  {"KISAO:0000228", "Epsilon"},
  {"KISAO:0000203", "Lower Limit"},
  {"KISAO:0000205", "Partitioning Interval"},
  {"KISAO:0000559", "Initial Step Size"},
  {"KISAO:0000483", "Runge Kutta Stepsize"},
  {"KISAO:0000483", "Internal Steps Size"},
  {"KISAO:0000565", "Tolerance for Root Finder"},
  {"KISAO:0000567", "Force Physical Correctness"},
};

VariableInfo::VariableInfo(const CDataObject * pObject)
  : mpObject(pObject)
  , mIsValid(false)
{
  if (!pObject)
    return;

  bool isReference = pObject->getObjectType() == "Reference";
  const CDataObject * pObj = isReference ? pObject->getObjectParent() : pObject;
  const CDataObject * pRef = pObject;

  if (!pObj)
    return;

  const CModelEntity * pME = dynamic_cast< const CModelEntity * >(pObj);
  const CMetab * pMetab = dynamic_cast< const CMetab * >(pObj);
  const CReaction * pReaction = dynamic_cast< const CReaction * >(pObj);

  if (pME)
    sbmlId = pME->getSBMLId();

  if (pReaction)
    sbmlId = pReaction->getSBMLId();

  if (!isReference)
    {
      if (pMetab)
        pRef = pMetab->getConcentrationReference();
      else if (pME)
        pRef = pME->getValueReference();
    }

  if (!pRef)
    return;

  name = pRef->getObjectDisplayName();
  xpath = SEDMLUtils::getXPathForObjectAndType(*pRef, sbmlId);

  std::string ref = pRef->getObjectName();

  if (ref == "Time")
    {
      symbol = SEDML_TIME_URN;
      term = SEDML_KISAO_TIME;
    }
  else if (ref == "Concentration" || ref == "InitialConcentration")
    {
      term = SEDML_KISAO_CONCENTRATION;
    }
  else if (ref == "ParticleNumber" || ref == "InitialParticleNumber")
    {
      term = SEDML_KISAO_PARTICLENUMBER;
    }
  else if (ref == "Flux")
    {
      term = SEDML_KISAO_FLUX;
    }
  else if (ref == "ParticleNumberRate")
    {
      term = SEDML_KISAO_PARTICLE_RATE;
    }
  else if (ref == "Rate")
    {
      if (pMetab)
        term = SEDML_KISAO_CONCENTRATION_RATE;
      else
        term = SEDML_KISAO_RATE;
    }

  mIsValid = true;
}

SedVariable*
VariableInfo::addToDataGenerator(SedDataGenerator * pGenerator) const
{
  SedVariable * pVar = pGenerator->createVariable();
  pVar->setName(name);

  if (pVar->getVersion() > 3)
    pVar->setTerm(term);

  pVar->setTarget(xpath);
  pVar->setSymbol(symbol);
  return pVar;
}

const std::string & VariableInfo::getName() const
{
  return name;
}

void VariableInfo::setName(const std::string & name_)
{
  name = name_;
}

const std::string & VariableInfo::getSymbol() const
{
  return symbol;
}

void VariableInfo::setSymbol(const std::string & symbol_)
{
  symbol = symbol_;
}

const std::string & VariableInfo::getXpath() const
{
  return xpath;
}

void VariableInfo::setXpath(const std::string & xpath_)
{
  xpath = xpath_;
}

const std::string & VariableInfo::getSbmlId() const
{
  return sbmlId;
}

const std::string & VariableInfo::getTerm() const
{
  return term;
}

void VariableInfo::setTerm(const std::string & term_)
{
  term = term_;
}

bool VariableInfo::isValid() const
{
  return mIsValid;
}

bool VariableInfo::operator<(const VariableInfo & other) const
{
  if (xpath != other.xpath)
    return xpath < other.xpath;

  if (term != other.term)
    return term < other.term;

  return symbol < other.symbol;
}
