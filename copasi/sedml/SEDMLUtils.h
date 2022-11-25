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
#include "copasi/plot/CPlotItem.h"
#include <sedml/common/SedmlEnumerations.h>
#include "SedmlImportOptions.h"

#define SEDML_TIME_URN                 "urn:sedml:symbol:time"
#define SEDML_KISAO_TIME               "KISAO:0000832"
#define SEDML_KISAO_STOCHASTIC         "KISAO:0000241"
#define SEDML_KISAO_CONCENTRATION      "KISAO:0000838"
#define SEDML_KISAO_AMOUNT             "KISAO:0000836"
#define SEDML_KISAO_PARTICLENUMBER     "KISAO:0000837"
#define SEDML_KISAO_RATEOFCHANGE       "KISAO:0000647"
#define SEDML_KISAO_PARTICLE_RATE      "KISAO:0000653"
#define SEDML_KISAO_CONCENTRATION_RATE "KISAO:0000652"
#define SEDML_KISAO_RATE               "KISAO:0000655"
#define SEDML_KISAO_FLUX               "KISAO:0000639"

class CModel;
class CMetab;
class CModelValue;
class CDataObject;

LIBSEDML_CPP_NAMESPACE_BEGIN
class SedDataGenerator;
class SedVariable;
class SedDocument;
class SedAbstractTask;
class SedDataGenerator;
class SedOutput;
class SedAbstractCurve;
class SedSurface;
LIBSEDML_CPP_NAMESPACE_END

/**
 * Utility class for writing SedVariables for objects
 */
class VariableInfo
{
  std::string name;
  std::string term;
  std::string symbol;
  std::string xpath;
  std::string sbmlId;
  bool mIsValid;

  const CDataObject * mpObject;

public:
  VariableInfo(const CDataObject* pObject);
  SedVariable * addToDataGenerator(SedDataGenerator * pGenerator) const;

  const std::string & getName() const;
  void setName(const std::string & name);
  const std::string & getSymbol() const;
  void setSymbol(const std::string & symbol);
  const std::string & getXpath() const;
  void setXpath(const std::string & xpath);
  const std::string & getSbmlId() const;
  const std::string & getTerm() const;
  void setTerm(const std::string & term);

  bool isValid() const;

  bool operator< (const VariableInfo & other) const;
};

/**
 * Utility class describing the SEDML document
 */
class SedmlInfo
{
  std::map< std::string, std::set< std::string > > mOutputMap;
  std::map< std::string, std::set< std::string > > mTaskMap;
  std::vector< std::string > mMessages;
  std::vector< std::pair< std::string, std::string > > mTaskNames;
  std::map< std::string, std::vector< std::pair< std::string, std::string > > > mReports;
  std::map< std::string, std::vector< std::pair< std::string, std::string > > > mPlots;
  std::map< std::string, std::string > mFileNames;
  bool mSupported;
  bool mComplex;
  bool mOwnDocument;
  SedDocument * mpDocument;

public:
  SedmlInfo(SedDocument * pDocument, bool ownDocument = false);
  ~SedmlInfo();

  bool isSupported();

  /**
   * @return true, if the document is complex (> 1 model, multiple
             tasks of the same type ) requiring the user to choose
             which one to import.
   */
  bool isComplex();

  std::set< std::string > getModelForTask(SedAbstractTask * task);
  std::set< std::string > getModelForTask(const std::string& taskId);
  std::set< std::string > getModelForDataGen(SedDataGenerator * dg);
  std::set< std::string > getTasks(const std::string & dgId);
  std::set< std::string > getTasks(SedDataGenerator * dg);
  std::set< std::string > getTasks(SedOutput * output);
  std::set< std::string > getTasks(SedAbstractCurve * curve);
  std::set< std::string > getTasks(SedSurface * surface);
  std::vector< std::pair< std::string, std::string > > getTaskNames();
  std::string getFirstModel(const std::string & taskId = "");
  std::string getFirstReport(const std::string & taskId);
  std::vector< std::pair< std::string, std::string > > getReportsForTask(const std::string & taskId);
  std::vector< std::pair< std::string, std::string > > getPlotsForTask(const std::string & taskId);

  bool hasOutputs(const std::string & taskId);
  bool isRecursiveWithoutOutputs(SedAbstractTask * task);

  std::string getReportFileName(const std::string & reportId);
  void setReportFileName(const std::string & reportId, const std::string & fileName);

  std::string getFirstTaskWithOutput();
  static void addSets(std::set< std::string > & target, const std::set< std::string > & source);

  static SedmlInfo forArchive(const std::string & fileName);
  static SedmlInfo forFile(const std::string & fileName);
};

/**
 * Utility methods for SED-ML Import / Export
 */
class SEDMLUtils
{
public:

  static std::string getSedMLStringForArchive(const std::string & fileName);

  static const CDataObject* resolveXPath(const CModel *model,
                                         const std::string& xpath, bool initial = false);

  static const CDataObject * resolveVariable(CModel * model, const SedVariable * variable);

  static CModelValue * createAmountMV(CModel * pModel, const CMetab * pMetab);

  static const CDataObject* resolveDatagenerator(CModel *model, const SedDataGenerator* dataReference);

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

  static std::string getXPathForObjectAndType(const CDataObject & object, const std::string & sbmlId);

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

  static int lineTypeToSed(int linetype);
  static int lineTypeFromSed(int linetype);

  static int symbolToSed(int symbol);
  static int symbolFromSed(int symbol);

  static std::string argbToRgba(const std::string & argb, bool includeHash = true);
  static std::string rgbaToArgb(const std::string & rgba, bool includeHash = true);

  static int getAlphaFromArgb(const std::string & argb);
  static int getAlphaFromRgba(const std::string & rgba);

  /**
   * updates the libcombine temp directory to the COPASI temp path
   */
  static void setLibCombineTempDir();

#ifndef SWIG

  static std::map< std::string, std::string > PARAMETER_KISAO_MAP;
  static std::map< int, int > COPASI_SYMBOL_MAP;
  static std::map< int, int > COPASI_LINE_STYLE_MAP;

#endif
};

#endif /* SEDMLUTILS_H_ */
