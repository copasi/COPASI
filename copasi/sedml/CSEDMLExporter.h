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

class CTrajectoryTask;
class CCompartment;
class CMetab;
class CProcessReport;
class CPlotSpecification;
class CScanProblem;

class CModelValue;
class CReaction;
class CModelEntity;
class SBMLIncompatibility;
class CCopasiTask;

LIBSBML_CPP_NAMESPACE_BEGIN
class Event;
class KineticLaw;
class Model;
class Parameter;
class Rule;
class SBase;
class SBMLDocument;
class XMLNode;
LIBSBML_CPP_NAMESPACE_END

class CSEDMLExporter
{

protected:
  SedDocument* mpSEDMLDocument;
  unsigned int mSEDMLLevel;
  unsigned int mSEDMLVersion;
  SedUniformTimeCourse *mpTimecourse;
  SedTask *mpTimecourseTask;

  std::unordered_set< std::string > mGeneratedIds;

public:
  CSEDMLExporter();
  ~CSEDMLExporter();

  SedDocument* getSEDMLDocument() {return this->mpSEDMLDocument;};

  /**
   * Export the model and Task to SEDML.
   * The SEDML document is returned as a string the model is not exported, instead the
   * provided modelLocation will be referenced.
   */
  const std::string exportModelAndTasksToString(CDataModel& dataModel,
      const std::string &modelLocation,
      unsigned int sedmlLevel, unsigned int sedmlVersion);

  /**
   * Export the model and Task to SEDML.
   * The SEDML document is written to the file given by SEDMLFilename and reference SBML model is written to SBMLFilename .
   * If the export fails, false is returned.
   */
  bool exportModelAndTasks(CDataModel& dataModel, const std::string& SEDMLFilename, const std::string& SBMLFilename, unsigned int sedmlLevel = 1, unsigned int sedmlVersion = 1, bool overwrite = false);

  /**
   * Creates an SEDMLDocument and SBMLDocument from the given CDataModelObject.
   * It checks if an SEDMLDocument and SBMLDocument already exists from an import and if
   * this is the case, the old document is copied.
   * If none exists a new one is created.
   * Copying the old one makes sure that if something goes wrong during
   * export, the original model is still consistent.
   */
  void createSEDMLDocument(CDataModel& dataModel, std::string modelRef);

  /**
   * Creates the timecourse task for the given model id and returns its id.
   */
  std::string createTimeCourseTask(CDataModel& dataModel, const  std::string & modelId);

  /**
   * Creates the steady state task for the given model id and returns its id.
   */
  std::string createSteadyStateTask(CDataModel& dataModel, const  std::string & modelId);

  /**
   * Creates a scan task for the given model id if the dataModel contains a number of scan items
   * and returns its id.
   *
   * @return the id of the task, if craeted, otherwise an empty string.
   */
  std::string createScanTask(CDataModel& dataModel, const  std::string & modelId);

  /**
   * Creates the models for SEDML.
   */
  void createModels(CDataModel& dataModel, std::string &modelRef);

  /**
   * Creates the Tasks for SEDML.
   */
  void createTasks(CDataModel& dataModel, std::string & modelRef);

  /**
   * Creates the data generators for SEDML.
   */
  void createDataGenerators(CDataModel & dataModel,
                            std::string & taskId,
                            CCopasiTask* task = NULL);

  SedDataGenerator * createDataGenerator(
    SedDocument * mpSEDMLDocument,
    const std::string & sbmlId,
    const std::string & targetXPathString,
    const std::string & taskId,
    size_t i,
    size_t j);


  bool exportNthScanItem(CScanProblem * pProblem,
                         size_t n,
                         SedRepeatedTask * task,
                         CDataModel & dataModel,
                         const std::string & modelId);

  /**
   * Creates the Tasks for SEDML.
   */
  //void createReports(CDataModel &dataModel);
};

#endif /* CSEDMLEXPORTER_H_ */
