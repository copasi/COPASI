// Copyright (C) 2013 - 2014 by Pedro Mendes, Virginia Tech Intellectual
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

class CTrajectoryTask;
class CCompartment;
class CMetab;
class CProcessReport;
class CPlotSpecification;

class CModelValue;
class CReaction;
class Event;
class CModelEntity;
class KineticLaw;
class Model;
class Parameter;
class Rule;
class SBase;
class SBMLDocument;
class SBMLIncompatibility;
class XMLNode;

class CSEDMLExporter
{

protected:
  SedDocument* mpSEDMLDocument;
  unsigned int mSEDMLLevel;
  unsigned int mSEDMLVersion;
  SedUniformTimeCourse *mpTimecourse;
  SedTask *mpTimecourseTask;

public:
  CSEDMLExporter();
  ~CSEDMLExporter();

  SedDocument* getSEDMLDocument() {return this->mpSEDMLDocument;};

  /**
   * Export the model and Task to SEDML.
   * The SEDML document is returned as a string and SBML model is copied to sbmldocument parameter. In case of an error, an
   * empty string is returned.
   */
  const std::string exportModelAndTasksToString(CCopasiDataModel& dataModel, std::string &sbmldocument, unsigned int sedmlLevel, unsigned int sedmlVersion);

  /**
   * Export the model and Task to SEDML.
   * The SEDML document is written to the file given by SEDMLFilename and reference SBML model is written to SBMLFilename .
   * If the export fails, false is returned.
   */
  bool exportModelAndTasks(CCopasiDataModel& dataModel, const std::string& SEDMLFilename, const std::string& SBMLFilename, unsigned int sedmlLevel = 1, unsigned int sedmlVersion = 1, bool overwrite = false);

  /**
   * Creates an SEDMLDocument and SBMLDocument from the given CCopasiDataModelObject.
   * It checks if an SEDMLDocument and SBMLDocument already exists from an import and if
   * this is the case, the old document is copied.
   * If none exists a new one is created.
   * Copying the old one makes sure that if something goes wrong during
   * export, the original model is still consistent.
   */
  void createSEDMLDocument(CCopasiDataModel& dataModel, std::string modelRef);

  /**
   * Creates the timecourse task for the given model id and returns its id.
   */
  std::string createTimeCourseTask(CCopasiDataModel& dataModel, const  std::string & modelId);

  /**
   * Creates the steady state task for the given model id and returns its id.
   */
  std::string createSteadyStateTask(CCopasiDataModel& dataModel, const  std::string & modelId);

  /**
   * Creates a scan task for the given model id if the dataModel contains a number of scan items
   * and returns its id.
   *
   * @return the id of the task, if craeted, otherwise an empty string.
   */
  std::string createScanTask(CCopasiDataModel& dataModel, const  std::string & modelId);

  /**
   * Creates the models for SEDML.
   */
  void createModels(CCopasiDataModel& dataModel, std::string &modelRef);

  /**
   * Creates the Tasks for SEDML.
   */
  void createTasks(CCopasiDataModel& dataModel, std::string & modelRef);

  /**
   * Creates the data generators for SEDML.
   */
  void createDataGenerators(CCopasiDataModel & dataModel,
                            std::string & taskId,
                            CCopasiTask* task = NULL);

  /**
   * Creates the Tasks for SEDML.
   */
  //void createReports(CCopasiDataModel &dataModel);
};

#endif /* CSEDMLEXPORTER_H_ */
