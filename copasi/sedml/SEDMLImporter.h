// Copyright (C) 2013 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

/**
 * SEDMLImporter.h
 * $Rev:               $:  Revision of last commit
 * $Author:            $:  Author of last commit
 * $Date:              $:  Date of last commit
 * $HeadURL:       $
 * $Id::         $
 */

#ifndef SEDMLIMPORTER_H_
#define SEDMLIMPORTER_H_

#include <string>
#include <map>
#include <set>
#include <utility>

#include "copasi/function/CFunctionDB.h"
//#include "copasi/sbml/StdException.h"
#include "copasi/model/CModel.h"

class SedDocument;
class SedUniformTimeCourse;
class SedSimulation;
class CTrajectoryTask;
class CCompartment;
class CMetab;
class Model;
class SedParameter;
class SedBase;
class CProcessReport;
class CPlotSpecification;

class SEDMLImporter
{

protected:
  static
  C_FLOAT64 round(const C_FLOAT64 & x);

  static
  bool areApproximatelyEqual(const double & x, const double & y, const double & t = 1e-9);

protected:
  std::string mArchiveFileName;
  std::set<unsigned int> mIgnoredSEDMLMessages;
  bool mIncompleteModel;
  unsigned int mLevel;
  unsigned int mOriginalLevel;
  unsigned int mVersion;
  CCopasiDataModel * mpDataModel;
  CModel* mpCopasiModel;
  SedDocument* mpSEDMLDocument;
  CProcessReport* mpImportHandler;
  unsigned C_INT32 mImportStep;
  size_t mhImportStep;
  unsigned C_INT32 mTotalSteps;

  std::set<std::string> mUsedSEDMLIds;
  bool mUsedSEDMLIdsPopulated;

  std::string mImportedModel;

public:
  SEDMLImporter();
  ~SEDMLImporter();

  const std::string getArchiveFileName();

  void readListOfPlotsFromSedMLOutput(
    COutputDefinitionVector *pPlotList, CModel* pModel,
    SedDocument *pSedDocument,
    std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap);

  std::string getDataGeneratorModelItemRefrenceId(SedDocument *pSEDMLDocument, std::string &dataReference, std::string &SBMLType);
  std::string translateTargetXpathInSBMLId(const std::string &xpath, std::string &SBMLType);

  /**
   * Updates COPASI tasks for a given SedML Simulation
   */
  void updateCopasiTaskForSimulation(SedSimulation* sedmlsim,
                                     std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap);

  /**
   * Imports the first viable SBML model
   */
  CModel* importFirstSBMLModel(CProcessReport* pImportHandler,
                               SBMLDocument *& pSBMLDocument,
                               std::map<CCopasiObject*, SBase*>& copasi2sbmlmap,
                               CListOfLayouts *& prLol,
                               CCopasiDataModel* pDataModel);

  /**
   * Import all tasks for the imported SBML model
   */
  void importTasks(std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap);

  CModel* readSEDML(std::string filename, CProcessReport* pImportHandler,
                    SBMLDocument *& pSBMLDocument, SedDocument*& pSedDocument,
                    std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap,
                    std::map<CCopasiObject*, SBase*>& copasi2sbmlmap,
                    CListOfLayouts *& prLol,
                    COutputDefinitionVector * & plotList,
                    CCopasiDataModel* pDataModel);

  CModel* parseSEDML(const std::string& sedmlDocumentText, CProcessReport* pImportHandler,
                     SBMLDocument *& pSBMLDocument, SedDocument *& pSEDMLDocument,
                     std::map<CCopasiObject*, SedBase*>& copasi2sedmlmap,
                     std::map<CCopasiObject*, SBase*>& copasi2sbmlmap,
                     CListOfLayouts *& prLol,
                     COutputDefinitionVector *& plotList,
                     CCopasiDataModel* pDataModel);

  /**
   * This call deletes an existing COPASI model.
   * The method can e.g. be called to clean up if an import fails.
   */
  void deleteCopasiModel();

  void setImportHandler(CProcessReport* pHandler);

  CProcessReport* getImportHandlerAddr();

  void restoreFunctionDB();
};

#endif /* SEDMLIMPORTER_H_ */
