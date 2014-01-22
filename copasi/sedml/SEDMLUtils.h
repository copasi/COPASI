// Copyright (C) 2013 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/*
 * SEDMLUtils.h
 *
 *  Created on: 15 Jul 2013
 *      Author: dada
 */

#ifndef SEDMLUTILS_H_
#define SEDMLUTILS_H_

#include <string>

#include <copasi/CopasiDataModel/CCopasiDataModel.h>
#include <copasi/report/CCopasiObject.h>

#define SEDML_TIME_URN "urn:sedml:symbol:time"

class CModel;
class SedDataGenerator;

class SEDMLUtils
{
public:
  int processArchive(const std::string & archiveFile, std::string &fileName, std::string &fileContent);

  //  void resmoveUnwantedChars(std::string & str, char chars[]);

  SEDMLUtils();

  static const CCopasiObject* resolveXPath(const CModel *model,
      const std::string& xpath, bool initial = false);

  static const CCopasiObject* resolveDatagenerator(const CModel *model, const SedDataGenerator* dataReference);

  static const CCopasiObject *getObjectForSbmlId(const CModel* pModel, const std::string& id, const std::string& SBMLType, bool initial = false);

  static std::string translateTargetXpathInSBMLId(const std::string &xpath, std::string& SBMLType);

  static std::string getNextId(const std::string& base, int count);

  static std::string getXPathAndName(std::string& sbmlId, const std::string &type,
                                     const CModel *pModel, const CCopasiDataModel& dataModel);

  static std::string getXPathForObject(const CCopasiObject& object);

  static std::string& removeCharactersFromString(std::string& str, const std::string& characters);

  static std::string findIdByNameAndType(const std::map<CCopasiObject*, SBase*>& map,
                                         int typeCode,
                                         const std::string& name);

  /**
   *  This is a hack at the moment better solution for processing XPath string may be developed in the future
   */
  static void splitStrings(const std::string &xpath, char delim, std::vector<std::string> &stringsContainer);

  virtual ~SEDMLUtils();
};

#endif /* SEDMLUTILS_H_ */
