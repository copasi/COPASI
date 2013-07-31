/*
 * CSEDMLExporter.h
 *
 *  Created on: 24 Jul 2013
 *      Author: dada
 */

#ifndef CSEDMLEXPORTER_H_
#define CSEDMLEXPORTER_H_

class SedDocument;
class SedUniformTimeCourse;
class SedSimulation;
class CTrajectoryTask;
class CCompartment;
class CMetab;
class SedModel;
class SedParameter;
class SedBase;
class CProcessReport;
class CPlotSpecification;

class CSEDMLExporter {

protected:
  SedDocument* mpSEDMLDocument;
  unsigned int mSEDMLLevel;
  unsigned int mSEDMLVersion;
  std::vector<CModelEntity*> mAssignmentVector;
  std::vector<CModelEntity*> mODEVector;
  std::vector<CModelEntity*> mInitialAssignmentVector;
  std::map<const CCopasiObject*, SedBase*> mCOPASI2SEDMLMap;
  std::set<SedBase*> mHandledSEDMLObjects;
  std::set<CFunction*> mUsedFunctions;
  std::map<std::string, const SedBase*> mSedIdMap;
  bool mIncompleteExport;
  std::map<std::string, const SedBase*> mSedMetaIdMap;
  std::map<std::string, const CEvaluationTree*> mFunctionIdMap;
  bool mDocumentDisowned;
  bool mExportCOPASIMIRIAM;

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
	void createSEDMLDocument(CCopasiDataModel& dataModel);

	/**
	 * Creates the simulations for SEDML.
	 */
	void createSimulations(CCopasiDataModel& dataModel, std::string & simRef);

	/**
	 * Creates the models for SEDML.
	 */
	void createModels(CCopasiDataModel& dataModel, std::string &modelRef);

	/**
	 * Creates the Tasks for SEDML.
	 */
	void createTasks(CCopasiDataModel& dataModel, std::string & simRef, std::string & modelRef);

	/**
	 * Creates the data generators for SEDML.
	 */
	void createDataGenerators(CCopasiDataModel & dataModel, std::string & taskId);

	/**
	 * Creates the Tasks for SEDML.
	 */
	//void createReports(CCopasiDataModel &dataModel);


};

#endif /* CSEDMLEXPORTER_H_ */
