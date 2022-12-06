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
#include <omex/common/libcombine-version.h>
#include <omex/CaContent.h>
#include <combine/combinearchive.h>
#include <combine/util.h>

#include "copasi/model/CModel.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CDataObject.h"
#include <copasi/commandline/COptions.h>

std::string SEDMLUtils::findIdByNameAndType(
  const std::map< const CDataObject *, SBase * > & map,
  int typeCode,
  const std::string & name)
{
  std::map< const CDataObject *, SBase * >::const_iterator it = map.begin();

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
      SBase * current = it->second;
      const CDataObject * object = it->first;
      std::string displayName = object->getObjectDisplayName();

      if (((current->getTypeCode() & typeCode) != typeCode))
        {
          ++it;
          continue;
        }

      if (current->getName() == name)
        return current->getId();

      if (typeCode == SBML_SPECIES && compartmentStart != std::string::npos)
        {
          if (displayName == name)
            {
              Species * species = static_cast< Species * >(current);

              if (species->getCompartment() == compId)
                return species->getId();
            }
        }

      ++it;
    }

  return "";
}

std::string
SEDMLUtils::getXPathAndName(std::string & sbmlId,
                            const std::string & type,
                            const CModel * pModel,
                            const CDataModel & dataModel)
{
  std::vector< std::string > stringsContainer;
  std::string targetXPathString;
  const std::map< const CDataObject *, SBase * > & copasi2sbmlmap =
    const_cast< CDataModel & >(dataModel).getCopasi2SBMLMap();
  std::string displayName = sbmlId;

  if (copasi2sbmlmap.empty())
    {
      // this should not be happening, as this is used to verify the element.
      return "";
    }

  std::map< CDataObject *, SBase * >::const_iterator pos;

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

      sbmlId = findIdByNameAndType(copasi2sbmlmap, SBML_PARAMETER, displayName);

      if (sbmlId.empty())
        sbmlId = findIdByNameAndType(copasi2sbmlmap, SBML_LOCAL_PARAMETER, displayName);

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

const CDataObject *
SEDMLUtils::resolveDatagenerator(CModel * model, const SedDataGenerator * dataReference)
{
  // for now one variable only
  if (dataReference == NULL || dataReference->getNumVariables() < 1)
    return NULL;

  const SedVariable * var = dataReference->getVariable(0);

  if (var->isSetSymbol() && var->getSymbol() == SEDML_TIME_URN)
    {
      return static_cast< const CDataObject * >(model->getObject(CCommonName("Reference=Time")));
    }

  return resolveVariable(model, var);
}

std::string
SEDMLUtils::translateTargetXpathInSBMLId(const std::string & xpath, std::string & SBMLType)
{
  std::vector< std::string > xpathStrings;
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

const CDataObject *
SEDMLUtils::resolveXPath(const CModel * model, const std::string & xpath, bool initial /* = false*/)
{
  std::string SBMLType;
  std::string id = translateTargetXpathInSBMLId(xpath, SBMLType);
  const CDataObject * result = getObjectForSbmlId(model, id, SBMLType, initial);

  if (result == NULL)
    {
      // old method fails here, possibly a local parameter
      size_t pos = xpath.find("/sbml:kineticLaw/sbml:listOfParameters/");

      if (pos != std::string::npos)
        {
          std::string reactionType;
          std::string reactionId = translateTargetXpathInSBMLId(xpath.substr(0, pos), reactionType);
          const CDataObject * flux = getObjectForSbmlId(model, reactionId, reactionType);

          if (flux != NULL)
            {
              const CDataObject * reactionObj = flux->getObjectParent();
              std::string cn = "ParameterGroup=Parameters,Parameter=" + id + ",Reference=Value";
              return dynamic_cast< const CDataObject * >(reactionObj->getObject(cn));
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

std::string &
SEDMLUtils::removeCharactersFromString(std::string & str, const std::string & characters)
{
  for (unsigned int ii = 0; ii < characters.length(); ++ii)
    {
      str.erase(std::remove(str.begin(), str.end(), characters[ii]), str.end());
    }

  return str;
}

std::string
SEDMLUtils::getXPathForObject(const CDataObject & object)
{
  std::string sbmlId = getSbmlId(object);
  std::string targetXPathString;

  if (!sbmlId.empty())
    {

      targetXPathString = getXPathForSbmlIdAndType(object.getObjectName(), sbmlId);

      if (!targetXPathString.empty())
        return targetXPathString;
    }

  const std::string & type = object.getObjectName();
  const CDataModel * dm = object.getObjectDataModel();
  std::string yAxis = object.getObjectDisplayName();
  targetXPathString = getXPathAndName(yAxis, type,
                                      dm->getModel(), *dm);
  return targetXPathString;
}

std::string SEDMLUtils::getXPathForSbmlIdAndType(const std::string & type, const std::string & sbmlId)
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

std::string SEDMLUtils::getNextId(const std::string & base, int count)
{
  std::stringstream str;
  str << base << count;
  return str.str();
}

std::string SEDMLUtils::getSbmlId(const CDataObject & object)
{
  const CModelEntity * entity = dynamic_cast< const CModelEntity * >(&object);

  if (entity != NULL)
    return entity->getSBMLId();

  entity = dynamic_cast< const CModelEntity * >(object.getObjectParent());

  if (entity != NULL)
    return entity->getSBMLId();

  return std::string();
}

//split: receives a char delimiter and string and a vector of strings that will contain the splited strings
//this is presently a hack to parse the XPath based target attribute in SEDML. A better solution may be
//necessary in the future.

void SEDMLUtils::splitStrings(const std::string & xpath, char delim, std::vector< std::string > & xpathStrings)
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
  int offset = argb[0] == '#' ? 1 : 0;

  if (argb.length() == 7 && offset == 1 && !includeHash)
    return argb.substr(1);

  if (argb.length() < 8)
    {
      if (includeHash && offset == 0)
        return std::string("#") + argb;

      return argb;
    }

  std::string a = argb.substr(offset, 2);

  std::string result = argb.substr(offset + 2) + a;

  if (includeHash)
    return std::string("#") + result;

  return result;
}

std::string SEDMLUtils::rgbaToArgb(const std::string & rgba, bool includeHash)
{
  std::string::size_type len = rgba.length();

  if (len == 7 && rgba[0] == '#' && !includeHash)
    return rgba.substr(1);

  int offset = rgba[0] == '#' ? 1 : 0;

  if (len < 8)
    {
      if (includeHash && offset == 0)
        return std::string("#") + rgba;

      return rgba;
    }

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

void SEDMLUtils::setLibCombineTempDir()
{

#if LIBCOMBINE_VERSION > 218
  std::string tmp;
  COptions::getValue("Tmp", tmp);
  Util::setDefaultTempDir(tmp);
#endif
}

const CDataObject *
SEDMLUtils::getObjectForSbmlId(const CModel * pModel, const std::string & id, const std::string & SBMLType, bool initial /* = false*/)
{
  if (!pModel)
    return NULL;

  if (SBMLType == "Time")
    return static_cast< const CDataObject * >(pModel->getObject(CCommonName("Reference=Time")));

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
  {(int) CPlotItem::SymbolType::Circle, SEDML_MARKERTYPE_CIRCLE},
  {(int) CPlotItem::SymbolType::Diamond, SEDML_MARKERTYPE_DIAMOND},
  {(int) CPlotItem::SymbolType::hDash, SEDML_MARKERTYPE_HDASH},
  {(int) CPlotItem::SymbolType::None, SEDML_MARKERTYPE_NONE},
  {(int) CPlotItem::SymbolType::Plus, SEDML_MARKERTYPE_PLUS},
  {(int) CPlotItem::SymbolType::LargeCross, SEDML_MARKERTYPE_PLUS},
  {(int) CPlotItem::SymbolType::SmallCross, SEDML_MARKERTYPE_PLUS},
  {(int) CPlotItem::SymbolType::Square, SEDML_MARKERTYPE_SQUARE},
  {(int) CPlotItem::SymbolType::Star, SEDML_MARKERTYPE_STAR},
  {(int) CPlotItem::SymbolType::TriangleDown, SEDML_MARKERTYPE_TRIANGLEDOWN},
  {(int) CPlotItem::SymbolType::TriangleLeft, SEDML_MARKERTYPE_TRIANGLELEFT},
  {(int) CPlotItem::SymbolType::TriangleRight, SEDML_MARKERTYPE_TRIANGLERIGHT},
  {(int) CPlotItem::SymbolType::TriangleUp, SEDML_MARKERTYPE_TRIANGLEUP},
  {(int) CPlotItem::SymbolType::vDash, SEDML_MARKERTYPE_VDASH},
  {(int) CPlotItem::SymbolType::xCross, SEDML_MARKERTYPE_XCROSS}
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
  {
    "KISAO:0000488",
    "Random Seed",
  },
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

  mIsValid = (!xpath.empty()) || (!term.empty()) || (!symbol.empty());
}

SedVariable *
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

SedmlInfo::SedmlInfo(SedDocument * pDocument, bool ownDocument)
  : mSupported(false)
  , mComplex(false)
  , mOwnDocument(ownDocument)
  , mpDocument(pDocument)

{
  if (!pDocument)
    return;

  std::map< std::pair< int, int>, int > taskCount;

  for (unsigned int i = 0; i < pDocument->getNumOutputs(); ++i)
    {
      auto * current = pDocument->getOutput(i);
      mOutputMap[current->getId()] = getTasks(current);
      mComplex |= mOutputMap[current->getId()].size() > 1;

      for (auto & taskId : mOutputMap[current->getId()])
        {
          std::stringstream str;

          if (current->isSetName())
            str << current->getName() << " - ";

          str << current->getId();

          if (current->getTypeCode() == SEDML_OUTPUT_REPORT)
            mReports[taskId].push_back(std::make_pair(current->getId(), str.str()));
          else
            mPlots[taskId].push_back(std::make_pair(current->getId(), str.str()));
        }
    }

  for (unsigned int i = 0; i < pDocument->getNumTasks(); ++i)
    {
      auto * current = pDocument->getTask(i);

      if (isRecursiveWithoutOutputs(current))
        continue;

      mTaskMap[current->getId()] = getModelForTask(current);

      int simType = SEDML_SIMULATION;

      if (current->getTypeCode() == SEDML_TASK)
        {
          auto * simulation = pDocument->getSimulation(dynamic_cast< SedTask * >(current)->getSimulationReference());

          if (simulation != NULL)
            simType = simulation->getTypeCode();
        }

      auto currentKey = std::make_pair(current->getTypeCode(), simType);

      taskCount[currentKey] = taskCount[currentKey] + 1;
      std::stringstream str;

      if (current->isSetName())
        str << current->getName() << " - ";

      str << current->getId();

      mTaskNames.push_back(std::make_pair(current->getId(), str.str()));
      mComplex |= taskCount[currentKey] > 1 || mTaskMap[current->getId()].size() > 1;
    }
}

bool SedmlInfo::hasOutputs(const std::string & taskId)
{
  return !(mReports[taskId].empty() && mPlots[taskId].empty());
}

bool SedmlInfo::isRecursiveWithoutOutputs(SedAbstractTask * task)
{
  auto * repeat = dynamic_cast< SedRepeatedTask * >(task);

  if (repeat == NULL)
    return false;

  if (hasOutputs(task->getId()))
    return false;

  return true;
}

SedmlInfo::~SedmlInfo()
{
  if (mOwnDocument)
    pdelete(mpDocument);
}

bool SedmlInfo::isSupported()
{
  return mSupported;
}

bool SedmlInfo::isComplex()
{
  return mComplex;
}

std::set< std::string > SedmlInfo::getModelForTask(SedAbstractTask * current)
{
  std::set< std::string > models;

  if (!current)
    return models;

  if (current->getTypeCode() == SEDML_TASK)
    {
      auto * task = static_cast< SedTask * >(current);
      models.insert(task->getModelReference());
      mTaskMap[task->getId()] = models;
    }
  else if (current->getTypeCode() == SEDML_TASK_REPEATEDTASK)
    {
      auto * task = static_cast< SedRepeatedTask * >(current);

      for (unsigned int j = 0; j < task->getNumSubTasks(); ++j)
        {
          addSets(models, getModelForTask(task->getSubTask(j)->getTask()));
        }
    }

  return models;
}

std::set< std::string > SedmlInfo::getModelForTask(const std::string & taskId)
{
  if (!mpDocument)
    return std::set< std::string >();

  return getModelForTask(mpDocument->getTask(taskId));
}

std::set< std::string > SedmlInfo::getModelForDataGen(SedDataGenerator * dg)
{
  auto result = std::set< std::string >();

  if (!dg)
    return result;

  for (unsigned int i = 0; i < dg->getNumVariables(); ++i)
    {
      auto * var = dg->getVariable(i);

      if (!var)
        continue;

      if (var->isSetModelReference())
        result.insert(var->getModelReference());

      if (var->isSetTaskReference())
        {
          addSets(result, getModelForTask(var->getTaskReference()));
        }
    }

  return result;
}

std::set< std::string > SedmlInfo::getTasks(const std::string & dgId)
{
  if (!mpDocument)
    return std::set< std::string >();

  return getTasks(mpDocument->getDataGenerator(dgId));
}

std::set< std::string > SedmlInfo::getTasks(SedDataGenerator * dg)
{
  auto result = std::set< std::string >();

  if (!dg)
    return result;

  for (unsigned int i = 0; i < dg->getNumVariables(); ++i)
    {
      auto * var = dg->getVariable(i);

      if (!var)
        continue;

      if (var->isSetTaskReference())
        {
          result.insert(var->getTaskReference());
        }
    }

  return result;
}

std::set< std::string > SedmlInfo::getTasks(SedOutput * output)
{
  auto result = std::set< std::string >();

  if (!output)
    return result;

  switch (output->getTypeCode())
    {
      case SEDML_OUTPUT_REPORT:
      {
        auto * current = static_cast< SedReport * >(output);

        for (unsigned int i = 0; i < current->getNumDataSets(); ++i)
          addSets(result, getTasks(current->getDataSet(i)->getDataReference()));
      }
      break;

      case SEDML_OUTPUT_PLOT2D:
      {
        auto * current = static_cast< SedPlot2D * >(output);

        for (unsigned int i = 0; i < current->getNumCurves(); ++i)
          addSets(result, getTasks(current->getCurve(i)));
      }
      break;

      case SEDML_OUTPUT_PLOT3D:
      {
        auto * current = static_cast< SedPlot3D * >(output);

        for (unsigned int i = 0; i < current->getNumSurfaces(); ++i)
          addSets(result, getTasks(current->getSurface(i)));
      }
      break;

      default:
      {
        break;
      }
    }

  return result;
}

std::set< std::string > SedmlInfo::getTasks(SedAbstractCurve * curve)
{
  auto result = std::set< std::string >();

  if (!curve)
    return result;

  switch (curve->getTypeCode())
    {
      case SEDML_OUTPUT_CURVE:
      {
        auto * current = static_cast< SedCurve * >(curve);
        addSets(result, getTasks(current->getXDataReference()));
        addSets(result, getTasks(current->getYDataReference()));
      }
      break;

      case SEDML_SHADEDAREA:
      {
        auto * current = static_cast< SedShadedArea * >(curve);
        addSets(result, getTasks(current->getXDataReference()));
        addSets(result, getTasks(current->getYDataReferenceFrom()));
        addSets(result, getTasks(current->getYDataReferenceTo()));
      }
      break;

      default:
        break;
    }

  return result;
}

std::set< std::string > SedmlInfo::getTasks(SedSurface * surface)
{
  auto result = std::set< std::string >();

  if (!surface)
    return result;

  addSets(result, getTasks(surface->getXDataReference()));
  addSets(result, getTasks(surface->getYDataReference()));
  addSets(result, getTasks(surface->getZDataReference()));

  return result;
}

std::vector< std::pair< std::string, std::string > > SedmlInfo::getTaskNames()
{
  return mTaskNames;
}

std::string SedmlInfo::getFirstModel(const std::string & taskId)
{
  auto it = mTaskMap.find(taskId);

  if (it == mTaskMap.end() || it->second.empty())
    return std::string();

  return *it->second.begin();
}

std::string SedmlInfo::getFirstReport(const std::string & taskId)
{
  auto it = mReports.find(taskId);

  if (it == mReports.end() || it->second.empty())
    return std::string();

  return it->second.begin()->first;
}

std::vector< std::pair< std::string, std::string > > SedmlInfo::getReportsForTask(const std::string & taskId)
{
  return mReports[taskId];
}

std::vector< std::pair< std::string, std::string > > SedmlInfo::getPlotsForTask(const std::string & taskId)
{
  return mPlots[taskId];
}

std::string SedmlInfo::getReportFileName(const std::string & reportId)
{
  return mFileNames[reportId];
}

void SedmlInfo::setReportFileName(const std::string & reportId, const std::string & fileName)
{
  mFileNames[reportId] = fileName;
}

std::string SedmlInfo::getFirstTaskWithOutput()
{
  if (mOutputMap.empty() || mOutputMap.begin()->second.empty())
    return std::string();

  return *mOutputMap.begin()->second.begin();
}

void SedmlInfo::addSets(std::set< std::string > & target, const std::set< std::string > & source)
{
  target.insert(source.begin(), source.end());
}

SedmlInfo SedmlInfo::forArchive(const std::string & fileName)
{
  std::string sedml = SEDMLUtils::getSedMLStringForArchive(fileName);
  SedDocument * doc = readSedMLFromString(sedml.c_str());
  return SedmlInfo(doc, true);
}

SedmlInfo SedmlInfo::forFile(const std::string & fileName)
{
  SedDocument * doc = readSedMLFromFile(fileName.c_str());
  return SedmlInfo(doc, true);
}

SedmlImportOptions::SedmlImportOptions(
  const std::string & taskId,
  const std::string & modelId,
  const std::vector< std::string > & plots,
  const std::string & reportId,
  const std::string & reportFilename)
  : mTaskId(taskId)
  , mModelId(modelId)
  , mPlots(plots)
  , mReportId(reportId)
  , mReportFile(reportFilename)
  , mSkipModelImport(false)
{
}

SedmlImportOptions & SedmlImportOptions::operator=(const SedmlImportOptions & rhs)
{
  if (this != &rhs)
    {
      mTaskId = rhs.mTaskId;
      mModelId = rhs.mModelId;
      mPlots = rhs.mPlots;
      mReportId = rhs.mReportId;
      mReportFile = rhs.mReportFile;
      mSkipModelImport = rhs.mSkipModelImport;
    }

  return *this;
}

void SedmlImportOptions::setSkipModelImport(bool skipModelLoading)
{
  mSkipModelImport = skipModelLoading;
}

bool SedmlImportOptions::skipModelImport() const
{
  return mSkipModelImport;
}

const std::string & SedmlImportOptions::getTaskId() const
{
  return mTaskId;
}

const std::string & SedmlImportOptions::getModelId() const
{
  return mModelId;
}

const std::string & SedmlImportOptions::getReportId() const
{
  return mReportId;
}

const std::string & SedmlImportOptions::getReportFile() const
{
  return mReportFile;
}

const std::vector< std::string > & SedmlImportOptions::getPlots() const
{
  return mPlots;
}

bool SedmlImportOptions::ignoreOutput(const std::string & outputId) const
{
  if (!isValid())
    return false;

  if (outputId == mReportId)
    return false;

  return std::find(mPlots.begin(), mPlots.end(), outputId) == mPlots.end();
}

bool SedmlImportOptions::isValid() const
{
  return !mTaskId.empty() && !mModelId.empty();
}

std::string
SEDMLUtils::getSedMLStringForArchive(const std::string & fileName)
{
  std::string result;

  if (fileName.empty())
    return result;

  setLibCombineTempDir();
  CombineArchive archive;

  if (!archive.initializeFromArchive(fileName))
    {
      CCopasiMessage(CCopasiMessage::ERROR, "Invalid COMBINE archive.");
      return result;
    }

  // read the master file
  const CaContent * content = archive.getMasterFile();
  bool haveCopasi = content != NULL && content->isFormat("copasi");
  std::stringstream messageStream;

  // if we don't have one, or we have one we don't understand look for copasi file
  if (content == NULL || (!content->isFormat("sbml") && !content->isFormat("copasi") && !content->isFormat("sedml")))
    {
      content = archive.getEntryByFormat("copasi");
      haveCopasi = content != NULL;

      if (!haveCopasi)
        {
          for (int i = 0; i < archive.getNumEntries(); ++i)
            {
              const CaContent * entry = archive.getEntry(i);

              if (entry->getFormat().substr(entry->getFormat().length() - 4) == "/xml" && entry->getLocation().find(".cps") != std::string::npos)
                {
                  content = entry;
                  haveCopasi = true;
                }
            }
        }
    }

  // if we have a COPASI file, we will load that in any case
  if (haveCopasi)
    return result;

  // otherwise look for an SedML file
  const CaContent * sedml_content =
    content != NULL && content->isFormat("sedml") ? content : archive.getEntryByFormat("sedml");

  // if we don't have a SedML-file in there, we don't need options
  if (!sedml_content)
    return result;

  // otherwise extract just the SedML
  return archive.extractEntryToString(sedml_content->getLocation());
}
