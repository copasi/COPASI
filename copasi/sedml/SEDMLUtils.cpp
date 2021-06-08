// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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
SEDMLUtils::resolveDatagenerator(const CModel *model, const SedDataGenerator* dataReference)
{
  // for now one variable only
  if (dataReference == NULL || dataReference->getNumVariables() < 1) return NULL;

  const SedVariable* var = dataReference->getVariable(0);

  if (var->isSetSymbol() && var->getSymbol() == SEDML_TIME_URN)
    {
      return static_cast<const CDataObject *>(model->getObject(CCommonName("Reference=Time")));
    }

  return resolveXPath(model, var->getTarget());
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

int SEDMLUtils::processArchive(const std::string & archiveFile,
                               std::string &fileName, std::string &fileContent)
{

  int err = 0;
  /*
  const char * cArchive = archiveFile.c_str();

    //Open the ZIP archive
    zip *zip = zip_open(cArchive, 0, &err);

    //Search for file using its given name
    const char *nameOfFile = fileName.c_str();
    struct zip_stat st;
    zip_stat_init(&st);
    zip_stat(zip, nameOfFile, 0, &st);

    //Alloc memory for its uncompressed contents
    char *fileCont = new char[st.size];

    //Read the compressed file
  zip_file *file = zip_fopen(zip, nameOfFile, 0);
  zip_fread(file, fileCont, st.size);

  std::ostringstream fileContentStream;
  size_t i, iMax = st.size;
  for(i = 0; i<iMax; ++i){
    fileContentStream << fileCont[i];
  }
  fileContent = fileContentStream.str();

  //close the file and archive
  zip_fclose(file);
  zip_close(zip);
  */

  return err;
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

/*void SEDMLUtils::resmoveUnwantedChars(std::string & str, char chars[]) {
  for (unsigned int i = 0; i < strlen(chars); ++i) {

    str.erase(std::remove(str.begin(), str.end(), chars[i]), str.end());
  }
}
 */
SEDMLUtils::SEDMLUtils()
{
  // TODO Auto-generated constructor stub
}

SEDMLUtils::~SEDMLUtils()
{
  // TODO Auto-generated destructor stub
}



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
