// Copyright (C) 2013 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

#include <copasi/model/CModel.h>
#include <copasi/report/CCopasiObject.h>
#include <copasi/CopasiDataModel/CCopasiDataModel.h>

std::string SEDMLUtils::findIdByNameAndType(
  const std::map<CCopasiObject*, SBase*>& map,
  int typeCode,
  const std::string& name)
{
  std::map<CCopasiObject*, SBase*>::const_iterator it = map.begin();

  std::string::size_type compartmentStart = name.find("{");
  std::string nameOnly = name.substr(0, compartmentStart);

  while (it != map.end())
    {
      SBase* current = it->second;

      if (((current->getTypeCode() & typeCode) == typeCode) &&
          current->getName() == name)
        return current->getId();

      if (typeCode == SBML_SPECIES  && compartmentStart != std::string::npos)
        {
          if (((current->getTypeCode() & typeCode) == typeCode) &&
              current->getName() == nameOnly)
            {
              std::string compName = name.substr(compartmentStart + 1, name.size() - compartmentStart  - 2);
              std::string compId = findIdByNameAndType(map, SBML_COMPARTMENT, compName);
              Species* species = (Species*) current;

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
                            const CCopasiDataModel& dataModel)
{
  std::vector<std::string> stringsContainer;
  std::string targetXPathString;

  const std::map<CCopasiObject*, SBase*>& copasi2sbmlmap =
    const_cast<CCopasiDataModel&>(dataModel).getCopasi2SBMLMap();
  std::string displayName = sbmlId;

  if (copasi2sbmlmap.size() == 0)
    {
      // this should not be happening, as this is used to verify the element.
      return "";
    }

  std::map<CCopasiObject*, SBase*>::const_iterator pos;

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
      else
        return "";
    }

  else if (type == "Flux")
    {
      targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id=\'";
      splitStrings(displayName, ')', stringsContainer);
      displayName = stringsContainer[0];

      removeCharactersFromString(displayName, "(");

      sbmlId = findIdByNameAndType(copasi2sbmlmap, SBML_REACTION, displayName);

      if (!sbmlId.empty())
        {
          return targetXPathString + sbmlId + "\']";
        }
      else
        return "";
    }
  else if (type == "Value" || type == "InitialValue")
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
      else
        return "";
    }
  else if (type == "Volume" || type == "InitialVolume")
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
      else
        return "";
    }
  else if (type == "Time" || type == "Initial Time")
    return SEDML_TIME_URN;

  sbmlId = "";
  return targetXPathString;
}

const CCopasiObject*
SEDMLUtils::resolveDatagenerator(const CModel *model, const SedDataGenerator* dataReference)
{
  // for now one variable only
  if (dataReference == NULL || dataReference->getNumVariables() < 1) return NULL;

  const SedVariable* var = dataReference->getVariable(0);

  if (var->isSetSymbol() && var->getSymbol() == SEDML_TIME_URN)
    {
      return static_cast<const CCopasiObject *>(model->getObject(CCopasiObjectName("Reference=Time")));
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

const CCopasiObject*
SEDMLUtils::resolveXPath(const CModel *model,  const std::string& xpath,
                         bool initial /* = false*/)
{
  std::string SBMLType;
  std::string id = translateTargetXpathInSBMLId(xpath, SBMLType);
  const CCopasiObject* result = getObjectForSbmlId(model, id, SBMLType, initial);

  if (result == NULL)
    {
      // old method fails here, possibly a local parameter
      size_t pos = xpath.find("/sbml:kineticLaw/sbml:listOfParameters/");

      if (pos != std::string::npos)
        {
          std::string reactionType;
          std::string reactionId = translateTargetXpathInSBMLId(xpath.substr(0, pos), reactionType);
          const CCopasiObject* flux = getObjectForSbmlId(model, reactionId, reactionType);

          if (flux != NULL)
            {
              const CCopasiObject* reactionObj = flux->getObjectParent();
              std::string cn = "ParameterGroup=Parameters,Parameter=" + id + ",Reference=Value";
              return dynamic_cast<const CCopasiObject*>(reactionObj->getObject(cn));
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
SEDMLUtils::getXPathForObject(const CCopasiObject& object)
{
  const std::string& type = object.getObjectName();
  const CCopasiDataModel* dm = object.getObjectDataModel();
  std::string yAxis = object.getObjectDisplayName();
  std::string targetXPathString = getXPathAndName(yAxis, type,
                                  dm->getModel(), *dm);
  return targetXPathString;
}

std::string SEDMLUtils::getNextId(const std::string& base, int count)
{
  std::stringstream str; str << base << count;
  return str.str();
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
      // check delimeter character
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

const CCopasiObject *
SEDMLUtils::getObjectForSbmlId(const CModel* pModel, const std::string& id, const std::string& SBMLType, bool initial/* = false*/)
{
  if (SBMLType == "Time")
    return static_cast<const CCopasiObject *>(pModel->getObject(CCopasiObjectName("Reference=Time")));

  if (SBMLType == "species")
    {
      size_t iMet, imax = pModel->getMetabolites().size();

      for (iMet = 0; iMet < imax; ++iMet)
        {
          // the importer should not need to change the initial concentration
          // pModel->getMetabolites()[iMet]->setInitialConcentration(0.896901);

          if (pModel->getMetabolites()[iMet]->getSBMLId() == id)
            {
              if (initial)
                return pModel->getMetabolites()[iMet]->getInitialConcentrationReference();

              return pModel->getMetabolites()[iMet]->getConcentrationReference();
            }
        }
    }
  else if (SBMLType == "reaction")
    {
      size_t iMet, imax = pModel->getReactions().size();

      for (iMet = 0; iMet < imax; ++iMet)
        {
          if (pModel->getReactions()[iMet]->getSBMLId() == id)
            {
              if (initial)
                return NULL;

              return pModel->getReactions()[iMet]->getFluxReference();
            }
        }
    }
  else if (SBMLType == "parameter")
    {
      size_t iMet, imax = pModel->getModelValues().size();

      for (iMet = 0; iMet < imax; ++iMet)
        {
          if (pModel->getModelValues()[iMet]->getSBMLId() == id)
            {
              if (initial)
                return pModel->getModelValues()[iMet]->getInitialValueReference();

              return pModel->getModelValues()[iMet]->getValueReference();
            }
        }
    }

  else if (SBMLType == "compartment")
    {
      size_t iComp, imax = pModel->getCompartments().size();

      for (iComp = 0; iComp < imax; ++iComp)
        {
          if (pModel->getCompartments()[iComp]->getSBMLId() == id)
            {
              if (initial)
                return pModel->getCompartments()[iComp]->getInitialValueReference();

              return pModel->getCompartments()[iComp]->getValueReference();
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
