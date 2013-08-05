/*
 * CSEDMLExporter.cpp
 *
 *  Created on: 24 Jul 2013
 *      Author: dada
 */

/**
 * Export the model and Task to SEDML.
 * The SEDML document is returned as a string and SBML model is copied to sbmldocument parameter. In case of an error, an
 * empty string is returned.
 */

#include <sbml/math/FormulaParser.h>

#include <sedml/SedBase.h>
#include <sedml/SedReader.h>
#include <sedml/SedDocument.h>
#include <sedml/SedModel.h>
#include <sedml/SedSimulation.h>
#include <sedml/SedUniformTimeCourse.h>
#include <sedml/SedDataGenerator.h>
#include <sedml/SedPlot2D.h>
#include <sedml/SedAlgorithm.h>
#include <sedml/SedTask.h>
#include <sedml/SedWriter.h>


#include "sbml/CSBMLExporter.h"

#include "CSEDMLExporter.h"

#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "utilities/CCopasiException.h"
#include "utilities/CVersion.h"
#include "utilities/CCopasiMessage.h"
#include "utilities/CDirEntry.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "model/CModel.h"
#include "commandline/CLocaleString.h"



const std::string CSEDMLExporter::exportModelAndTasksToString(CCopasiDataModel& dataModel,
		std::string &sbmlModelSource,
		unsigned int sedmlLevel,
		unsigned int sedmlVersion)
{
	this->mSEDMLLevel = sedmlLevel;
	this->mSEDMLVersion = sedmlVersion;
	mHandledSEDMLObjects.clear();
	this->createSEDMLDocument(dataModel, sbmlModelSource);

	CSBMLExporter exporter;
	SedWriter* writer = new SedWriter();

	writer->setProgramName("COPASI");
	writer->setProgramVersion(CVersion::VERSION.getVersion().c_str());

	char* d = writer->writeToString(this->mpSEDMLDocument);
	std::string returnValue = d;

	if (d) free(d);

	pdelete(writer);

	return returnValue;
}

/**
 * Export the model and Task to SEDML.
 * The SEDML document is written to the file given by SEDMLFilename and reference SBML model is written to SBMLFilename .
 * If the export fails, false is returned.
 */
bool CSEDMLExporter::exportModelAndTasks(CCopasiDataModel& dataModel,
		const std::string& filename,
		const std::string& sbmlDocument,
		unsigned int sedmlLevel,
		unsigned int sedmlVersion,
		bool overwrite)
{
	bool success = true;
	/* create a string that represents the SBMLDocument */
	std::string sedmlModelSource ="model1.xml"; //always name of the SBML model to reference in SEDML document

	std::string sbmlFileName;
	sbmlFileName = CDirEntry::dirName(filename) + CDirEntry::Separator + sedmlModelSource;

	std::ifstream sbmlFile (CLocaleString::fromUtf8(sbmlFileName).c_str(), std::ios::in);

	if (sbmlFile && !overwrite) {
		// create a CCopasiMessage with the appropriate error
		CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 1, sbmlFileName.c_str());
		return false;
	}

	/* write the sbml model document to a file */
	std::ofstream sbmlOutFile(CLocaleString::fromUtf8(sbmlFileName).c_str(), std::ios::out | std::ios::trunc);
	sbmlOutFile << sbmlDocument;
	sbmlOutFile.close();

	std::string str = this->exportModelAndTasksToString(dataModel, sedmlModelSource, sedmlLevel, sedmlVersion);

	std::cout<<str<<std::endl;

	if (!str.empty()) {
		/* check if the file already exists.
		 If yes, write if overwrite is true,
		 else create an appropriate  CCopasiMessage. */
		std::ifstream testInfile(CLocaleString::fromUtf8(filename).c_str(), std::ios::in);

		if (testInfile && !overwrite) {
			// create a CCopasiMessage with the appropriate error
			CCopasiMessage(CCopasiMessage::ERROR, MCDirEntry + 1, filename.c_str());
			return false;
		}

		/* write the document to a file */
		std::ofstream outfile(CLocaleString::fromUtf8(filename).c_str(), std::ios::out | std::ios::trunc);
		outfile << str;
		outfile.close();
	} else {
		/* if no SBMLDocument could be created return false */
		success = false;
	}

	return success;
}

void CSEDMLExporter::createSEDMLDocument(CCopasiDataModel& dataModel, std::string modelRef)
{
  const SedDocument* pOldSEDMLDocument = NULL; //dataModel.getCurrentSEDMLDocument();
  const CModel* pModel = dataModel.getModel();
  COutputDefinitionVector *plotDef = dataModel.getPlotDefinitionList();
  assert(plotDef != NULL); //need to emit a message
  assert(pModel != NULL);


  if (pOldSEDMLDocument == NULL) {
		this->mpSEDMLDocument = new SedDocument();
		this->mpSEDMLDocument->setLevel(this->mSEDMLLevel);
		this->mpSEDMLDocument->setVersion(this->mSEDMLVersion);
	} else {
		this->mpSEDMLDocument = dynamic_cast<SedDocument*>(pOldSEDMLDocument->clone());
	}
	if (this->mpSEDMLDocument == NULL) fatalError();

  //  CSBMLExporter exporter;
	// Right now we always import the COPASI MIRIAM annotation if it is there.
	// Later this will be settable by the user in the preferences dialog
	//exporter.setExportCOPASIMIRIAM(true);

	std::string simRef;
    createSimulations(dataModel, simRef);
    createModels(dataModel, modelRef);
    createTasks(dataModel, simRef, modelRef);
}

/**
 * Creates the simulations for SEDML.
 */
void CSEDMLExporter::createSimulations(CCopasiDataModel& dataModel, std::string & simRef)
{
	SedUniformTimeCourse* tc = this->mpSEDMLDocument->createUniformTimeCourse();
	simRef = "sim1";
	tc->setId(simRef);
	//presently SEDML only supports time course
	CCopasiTask* pTask = (*dataModel.getTaskList())[CCopasiTask::timeCourse];
	CTrajectoryProblem* tProblem = static_cast<CTrajectoryProblem*>(pTask->getProblem());
	tc->setInitialTime(0.0);
	tc->setOutputStartTime(tProblem->getOutputStartTime());
	tc->setOutputEndTime(tProblem->getStepNumber()*tProblem->getStepSize());
	tc->setNumberOfPoints(tProblem->getStepNumber());

	// set the correct KISAO Term
	SedAlgorithm* alg = tc->createAlgorithm();
	alg->setKisaoID("KISAO:0000019");

}

/**
 * Creates the models for SEDML.
 */
void CSEDMLExporter::createModels(CCopasiDataModel& dataModel, std::string & modelRef) {
	std::string modelId = "model1"; // onlu one model
	SedModel *model = this->mpSEDMLDocument->createModel();
	model->setId(modelId);
	model->setSource(modelRef);
	model->setLanguage("urn:sedml:language:sbml");
}

/**
 * Creates the Tasks for SEDML.
 */
void CSEDMLExporter::createTasks(CCopasiDataModel& dataModel, std::string & simRef, std::string & modelRef)
{
	SedTask *task = this->mpSEDMLDocument->createTask();
	SedSimulation * sim = this->mpSEDMLDocument->createUniformTimeCourse();
	std::string taskId = "task1";
	task->setId(taskId);
	task->setSimulationReference(simRef),
	task->setModelReference(modelRef);
	createDataGenerators(dataModel, taskId);
}

/**
 * Creates the data generators for SEDML.
 */
void CSEDMLExporter::createDataGenerators(CCopasiDataModel & dataModel, std::string & taskId)
{
	SedPlot2D* pPSedPlot;
	SedCurve* pCurve; // = pPSedPlot->createCurve();

	//create generator for special varibale time
	const CCopasiObject* pTime = static_cast<const CCopasiObject *>(dataModel.getModel()->getObject(CCopasiObjectName("Reference=Time")));
	SedDataGenerator *pTimeDGenp = this->mpSEDMLDocument->createDataGenerator();
	pTimeDGenp->setId("time");
	pTimeDGenp->setName(pTime->getObjectName());
	SedVariable *pTimeVar = pTimeDGenp->createVariable();
	pTimeVar->setId("var_time");
	pTimeVar->setTaskReference(taskId);
	pTimeVar->setSymbol("usn:sedml:symbol:time");
	pTimeDGenp->setMath(SBML_parseFormula(pTimeVar->getId().c_str()));

	size_t i, imax = dataModel.getPlotDefinitionList()->size();
	SedPlot2D* pPSedlot;
	SedDataGenerator *pPDGen;
	if (!imax)
		CCopasiMessage(CCopasiMessage::EXCEPTION, "No plot definition for this SEDML document.");

	for (i = 0; i < imax; i++) {
		pPSedPlot = this->mpSEDMLDocument->createPlot2D();
		const CPlotSpecification* pPlot = (*dataModel.getPlotDefinitionList())[i];
		std::string plotName = pPlot->getObjectName();
		char chars[] = "[]";
		for (unsigned int ii = 0; ii < strlen(chars); ++ii) {
			plotName.erase(std::remove(plotName.begin(), plotName.end(), chars[i]), plotName.end());
		}

		std::ostringstream plotIdStream;
		plotIdStream << "plot";
	//	plotIdStream << "_";
		plotIdStream << i+1;
		pPSedPlot->setId(plotIdStream.str());
		pPSedPlot->setName(plotName);

		size_t j, jmax = pPlot->getItems().size();
		for (j = 0; j < jmax; j++) {
			const CPlotItem* pPlotItem = pPlot->getItems()[j];

			pPDGen = this->mpSEDMLDocument->createDataGenerator();

		/*	std::string strName = pPlotItem->getObjectName();

			//remove unwanted characters from the plot item object name
			char chars [] = "[]";
			for (unsigned int i = 0; i < strlen(chars); ++i) {
				strName.erase(std::remove(strName.begin(), strName.end(), chars[i]), strName.end());
			} */

			CCopasiObject *objectX, *objectY;

			if (pPlotItem->getChannels().size() >= 1)
				objectX = dataModel.getDataObject(pPlotItem->getChannels()[0]);

			if (pPlotItem->getChannels().size() >= 2)
				objectY = dataModel.getDataObject(pPlotItem->getChannels()[1]);

			std::string yAxis = objectY->getObjectDisplayName();

			//remove unwanted characters from the plot item object name
			char chars[] = "[]";
			for (unsigned int i = 0; i < strlen(chars); ++i) {
				yAxis.erase(std::remove(yAxis.begin(), yAxis.end(), chars[i]), yAxis.end());
			}

			std::ostringstream idStrStream;
			idStrStream << yAxis;
			idStrStream << "_";
			idStrStream << j+1;
			pPDGen->setId(idStrStream.str());

			pPDGen->setName(yAxis);
			pPDGen->setMath(SBML_parseFormula(pPDGen->getName().c_str()));

			SedVariable * pPVar = pPDGen->createVariable();
			pPVar->setId(pPDGen->getName());
			pPVar->setTaskReference(taskId);
			pPVar->setName(pPDGen->getName());

			//temporary method to set XPath target
			std::ostringstream targetStrStream;
			targetStrStream<<"/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id=\'";
			targetStrStream<<pPVar->getName();
			targetStrStream<<"\']";
			pPVar->setTarget(targetStrStream.str());

			pCurve = pPSedPlot->createCurve();
			std::ostringstream idCurveStrStream;
			idCurveStrStream<<"curve_";
			idCurveStrStream<<j+1;
			pCurve->setId(idCurveStrStream.str());
			pCurve->setLogX(pPlot->isLogX());
			pCurve->setLogY(pPlot->isLogY());
			pCurve->setXDataReference(pTimeDGenp->getId());
			pCurve->setYDataReference(pPDGen->getId());
		}

	}
}

CSEDMLExporter::CSEDMLExporter() {
	// TODO Auto-generated constructor stub

}

CSEDMLExporter::~CSEDMLExporter() {
	// TODO Auto-generated destructor stub
}

