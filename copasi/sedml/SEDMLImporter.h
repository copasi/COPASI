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

#include <sedml/common/sedmlfwd.h>

LIBSBML_CPP_NAMESPACE_BEGIN
class Model;
LIBSBML_CPP_NAMESPACE_END

class CTrajectoryTask;
class CCompartment;
class CMetab;
class CProcessReport;
class CPlotSpecification;
class CReportDefinition;
class COutputDefinitionVector;
class CListOfLayouts;

class SEDMLImporter
{

protected:
  static
  C_FLOAT64 round(const C_FLOAT64 & x);

protected:
  std::string mArchiveFileName;
  std::set<unsigned int> mIgnoredSEDMLMessages;
  bool mIncompleteModel;
  unsigned int mLevel;
  unsigned int mOriginalLevel;
  unsigned int mVersion;

  CDataModel * mpDataModel;
  CModel* mpCopasiModel;

  SedDocument* mpSEDMLDocument;

  CProcessReport* mpImportHandler;
  unsigned C_INT32 mImportStep;
  size_t mhImportStep;
  unsigned C_INT32 mTotalSteps;

  std::set<std::string> mUsedSEDMLIds;
  bool mUsedSEDMLIdsPopulated;

  std::string mImportedModel;

  std::map<CReportDefinition*, std::string> mReportMap;

public:
  SEDMLImporter();
  ~SEDMLImporter();

  const std::string getArchiveFileName();

  void readListOfPlotsFromSedMLOutput(
    COutputDefinitionVector *pPlotList, CModel* pModel,
    SedDocument *pSedDocument,
    std::map<CDataObject*, SedBase*>& copasi2sedmlmap);

  /**
   * Updates COPASI tasks for a given SedML Simulation
   */
  void updateCopasiTaskForSimulation(SedSimulation* sedmlsim,
                                     std::map<CDataObject*, SedBase*>& copasi2sedmlmap);

  /**
   * Updates the task / method settings from algorithm
   *
   * @param tTask, the time course task to update
   * @param alg the algorithm including algorithm parameters
   *
   */
  void applyAlgorithm(CTrajectoryTask * tTask, const SedAlgorithm * alg);

  /**
   * Imports the first viable SBML model
   */
  CModel* importFirstSBMLModel(CProcessReport* pImportHandler,
                               SBMLDocument *& pSBMLDocument,
                               std::map<CDataObject*, SBase*>& copasi2sbmlmap,
                               CListOfLayouts *& prLol,
                               CDataModel* pDataModel);

  /**
   * Import all tasks for the imported SBML model
   */
  void importTasks(std::map<CDataObject*, SedBase*>& copasi2sedmlmap);

  CModel* readSEDML(std::string filename, CProcessReport* pImportHandler,
                    SBMLDocument *& pSBMLDocument, SedDocument*& pSedDocument,
                    std::map<CDataObject*, SedBase*>& copasi2sedmlmap,
                    std::map<CDataObject*, SBase*>& copasi2sbmlmap,
                    CListOfLayouts *& prLol,
                    COutputDefinitionVector * & plotList,
                    CDataModel* pDataModel);

  CModel* parseSEDML(const std::string& sedmlDocumentText, CProcessReport* pImportHandler,
                     SBMLDocument *& pSBMLDocument, SedDocument *& pSEDMLDocument,
                     std::map<CDataObject*, SedBase*>& copasi2sedmlmap,
                     std::map<CDataObject*, SBase*>& copasi2sbmlmap,
                     CListOfLayouts *& prLol,
                     COutputDefinitionVector *& plotList,
                     CDataModel* pDataModel);

  /**
   * This call deletes an existing COPASI model.
   * The method can e.g. be called to clean up if an import fails.
   */
  void deleteCopasiModel();

  /**
   * sets a progress handler to inform about updates
   */
  void setImportHandler(CProcessReport* pHandler);

  /**
   * @return the progress handler set
   */
  CProcessReport* getImportHandlerAddr() const;

  /**
   * clears the currently set progress handler
   */
  virtual void clearCallBack();

  void restoreFunctionDB();
};

#endif /* SEDMLIMPORTER_H_ */
