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

  /**
   * @return the sbml id of the object (or its parent, in case of a reference) or the empty string if not set
   */
  static std::string getSbmlId(const CDataObject& object);


  /**
   * This function uses the Copasi2SBML map of the datamodel, to resolve the element with the
   * display name provided in the 'sbmlId' parameter. Once the object has been resolved the
   * xpath string will be created for it, and the object sbmlId returned.
   *
   * @param sbmlId input parameter with the displayName of the object sought, will be the output 'sbmlId'
   *        if the element cannot be resolved, sbmlId will be set to the empty string
   * @param type the object type of the element
   * @param pModel the model to search through
   * @param dataModel the datamodel to use
   *
   * @return the xpath expression, if resolving worked, an empty string otherwise
   */
  static std::string getXPathAndName(std::string& sbmlId, const std::string &type,
                                     const CModel *pModel, const CDataModel& dataModel);

  /**
   * @param object the object to generate an xpath expression for
   * @return the xpath for the object or the empty string if it could not be generated
   */
  static std::string getXPathForObject(const CDataObject& object);

  /**
   * Wraps the given sbml id into an xpath expression according to type
   * @param type one of 'Concentration', 'InitialConcentration', 'Volume', 'Value', 'Flux'
   * @param sbmlid the sbmlid of the object
   * @return the sbml xpath expression
   */
  static std::string getXPathForSbmlIdAndType(const std::string& type, const std::string& sbmlId);

  static std::string& removeCharactersFromString(std::string& str, const std::string& characters);

  /**
   * tries to find a species id in the given map. Lookup will be performed by name
   *
   * @return the species id if found or the empty string
   */
  static std::string findIdByNameAndType(const std::map<const CDataObject*, SBase*>& map,
                                         int typeCode,
                                         const std::string& name);

  /**
   *  This is a hack at the moment better solution for processing XPath string may be developed in the future
   */
  static void splitStrings(const std::string &xpath, char delim, std::vector<std::string> &stringsContainer);

  virtual ~SEDMLUtils();

#ifndef SWIG

  static std::map< std::string, std::string > PARAMETER_KISAO_MAP;

#endif

};

#endif /* SEDMLUTILS_H_ */
