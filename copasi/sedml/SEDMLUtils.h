// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include "copasi/CopasiDataModel/CDataModel.h"
#include "copasi/core/CDataObject.h"

#define SEDML_TIME_URN "urn:sedml:symbol:time"
#define SEDML_KISAO_STOCHASTIC "KISAO:0000241"

class CModel;

LIBSEDML_CPP_NAMESPACE_BEGIN
class SedDataGenerator;
LIBSEDML_CPP_NAMESPACE_END

class SEDMLUtils
{
public:
  int processArchive(const std::string & archiveFile, std::string &fileName, std::string &fileContent);

  //  void resmoveUnwantedChars(std::string & str, char chars[]);

  SEDMLUtils();

  static const CDataObject* resolveXPath(const CModel *model,
                                         const std::string& xpath, bool initial = false);

  static const CDataObject* resolveDatagenerator(const CModel *model, const SedDataGenerator* dataReference);

  static const CDataObject *getObjectForSbmlId(const CModel* pModel, const std::string& id, const std::string& SBMLType, bool initial = false);

  static std::string translateTargetXpathInSBMLId(const std::string &xpath, std::string& SBMLType);

  static std::string getNextId(const std::string& base, int count);

  static std::string getXPathAndName(std::string& sbmlId, const std::string &type,
                                     const CModel *pModel, const CDataModel& dataModel);

  static std::string getXPathForObject(const CDataObject& object);

  static std::string& removeCharactersFromString(std::string& str, const std::string& characters);

  static std::string findIdByNameAndType(const std::map<const CDataObject*, SBase*>& map,
                                         int typeCode,
                                         const std::string& name);

  /**
   *  This is a hack at the moment better solution for processing XPath string may be developed in the future
   */
  static void splitStrings(const std::string &xpath, char delim, std::vector<std::string> &stringsContainer);

  virtual ~SEDMLUtils();
};

#endif /* SEDMLUTILS_H_ */
