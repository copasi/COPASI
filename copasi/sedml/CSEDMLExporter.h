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
 * CSEDMLExporter.h
 *
 *  Created on: 24 Jul 2013
 *      Author: dada
 */

#ifndef CSEDMLEXPORTER_H_
#define CSEDMLEXPORTER_H_

#include <sedml/common/sedmlfwd.h>

#include <string>
#include <unordered_set>
#include <map>

class CTrajectoryTask;
class CScanProblem;
class CCopasiTask;
class CCopasiMethod;

class CSEDMLExporter
{

protected:
  SedDocument* mpSEDMLDocument;
  unsigned int mSEDMLLevel;
  unsigned int mSEDMLVersion;
  SedUniformTimeCourse *mpTimecourse;
  SedTask *mpTimecourseTask;

  std::unordered_set< std::string > mGeneratedIds;

  bool mExportExecutableTasksOnly;
  bool mExportActivePlotsOnly;
  bool mExportSpecificPlots;

  std::string mModelId;

public:

  /**
   * constructs a new exporter element
   */
  CSEDMLExporter();

  /**
   * destructor
   */
  ~CSEDMLExporter();

  /**
   * @return the currently constructed SED-ML document
   */
  LIBSEDML_CPP_NAMESPACE::SedDocument * getSEDMLDocument();

  /**
   * @return the current SED-ML document as string
   */
  std::string writeSedMLToString() const;

  /**
   * writes the current SED-ML document to the given filename
   *
   * @param filename the file name to write to
   *
   * @return boolean indicating success / failure
   */
  bool writeSedMLToFile(const std::string& filename) const;

  /**
   * Export the model and Task to SEDML.
   * The SEDML document is returned as a string the model is not exported, instead the
   * provided modelLocation will be referenced.
   *
   * @param dataModel the copasi model to export
   * @param modelLocation the location where the SBML file was exported to
   * @param sedmlLevel the SED-ML Level
   * @param sedmlVersion the SED-ML version
   *
   * @return the SED-ML document as string
   */
  std::string exportModelAndTasksToString(CDataModel& dataModel,
                                          const std::string &modelLocation,
                                          unsigned int sedmlLevel, unsigned int sedmlVersion);

  /**
   * Sets the SED-ML Level and Version used to export
   */
  void setLevelAndVersion(unsigned int sedmlLevel, unsigned int sedmlVersion);

  /**
   * Export the model and Task to SEDML. This legacy version requires
   * that the SBML document is passed as string and is kept only for
   * compatibility reasons.
   *
   * @param dataModel the copasi model to export
   * @param sedmlFilename the filename to write the SED-ML document to
   * @param sbmlDocument the sbml document as string
   * @param sedmlLevel the the SED-ML level (defaults to 1)
   * @param sedmlVersion the SED-ML version (defaults to 2)
   * @param overwrite boolean indicating whether the file should be overwritten
   *                  (defaults to false)
   *
   * @return success / failure. If the export fails, false is returned.
   */
  bool exportModelAndTasks(CDataModel& dataModel,
                           const std::string& sedmlFilename,
                           const std::string& sbmlDocument,
                           unsigned int sedmlLevel = 1,
                           unsigned int sedmlVersion = 1,
                           bool overwrite = false);

  /**
   * Creates an SED-ML document from the given data model. It assumes that
   * the SBML model has been exported to the given model location
   *
   * @param dataModel the data model to export
   * @param modelRef the location of the SBML model
   *
   * @return the created SED-ML document
   */
  LIBSEDML_CPP_NAMESPACE::SedDocument* createSEDMLDocument
  (CDataModel & dataModel, std::string modelRef);

  /**
   * resets the internal map of created elements
   * (will be called automatically by createSEDMLDocument() )
   */
  void clearMaps();

  /**
   * Creates the time course task and returns its id.
   */
  std::string createTimeCourseTask(CDataModel& dataModel);

  /**
   * specifies the most specific KISAO terms for the given method
   */
  void exportAlgorithm(SedAlgorithm * alg, const CCopasiMethod * pMethod);

  /**
   * Creates the steady state task and returns its id.
   */
  std::string createSteadyStateTask(CDataModel& dataModel);

  /**
   * Creates a scan task if the dataModel contains a number of scan items
   * and returns its id.
   *
   * @return the id of the task, if created, otherwise an empty string.
   */
  std::string createScanTask(CDataModel& dataModel);

  /**
   * Creates a SED-ML model for the given model reference. This function
   * is supposed to be executed before exporting tasks, as it will
   * generate the model id that will be used for further exports.
   *
   * @return the model id created
   */
  std::string createModel(CDataModel & dataModel, const std::string & modelRef);

  /**
   * Creates the SED-ML Tasks for the data model, assuming the
   * model has already been created.
   *
   * Before executing this method the model should have been created using
   * createModel, or the model id should have been set with setModelId.
   *
   */
  void createTasks(CDataModel& dataModel);

  /**
   * Creates the data generators for SEDML.
   */
  void createDataGenerators(CDataModel & dataModel,
                            std::string & taskId,
                            CCopasiTask* task = NULL);

  /**
   * exports the nth scan item, to the given task.
   * @return boolean indicating success or failure
   */
  bool exportNthScanItem(CScanProblem * pProblem,
                         size_t n,
                         SedRepeatedTask * task,
                         CDataModel & dataModel);


  /**
   * @return whether only executable tasks should be exported
   */
  bool getExportExecutableTasksOnly() const;

  /**
   * Specify whether only executable tasks should be exported
   */
  void setExportExecutableTasksOnly(bool val);

  /**
   * @return whether only active plots should be exported
   */
  bool getExportActivePlotsOnly() const;

  /**
   * Specify whether only active plots should be exported
   */
  void setExportActivePlotsOnly(bool val);

  /**
   * @return whether only plots should be exported that apply to the
   *         specific task
   */
  bool getExportSpecificPlots() const;

  /**
   * Specify whether plots should be exported only if they apply to the
   * specific task
   */
  void setExportSpecificPlots(bool val);

  /**
   * @returns the SBML model id used
   */
  const std::string& getModelId() const;

  /**
   * specifies the SBML model id to be used by the task export.
   */
  void setModelId(const std::string& val);

  /**
   * frees the SED-ML document, and resets maps
   */
  void freeSedMLDocument();

protected:

  /**
   * Helper function for creating data generators. They will just reference
   * the element with given SBML id, and target xpath expression.
   */
  SedDataGenerator * createDataGenerator(
    const std::string & sbmlId,
    const std::string & targetXPathString,
    const std::string & taskId,
    size_t i,
    size_t j);

  /**
   * A utility function returning the value of the copasi parameter
   * as a std::string.
   */
  static std::string getParameterValueAsString(const CCopasiParameter * pParameter);

};

#endif /* CSEDMLEXPORTER_H_ */
