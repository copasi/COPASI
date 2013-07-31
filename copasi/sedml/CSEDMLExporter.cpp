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
#include "CopasiDataModel/CCopasiDataModel.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "model/CModel.h"
#include "commandline/CLocaleString.h"



const std::string CSEDMLExporter::exportModelAndTasksToString(CCopasiDataModel& dataModel,
		std::string &sbmldocument,
		unsigned int sedmlLevel,
		unsigned int sedmlVersion)
{
	this->mSEDMLLevel = sedmlLevel;
	this->mSEDMLVersion = sedmlVersion;
	mHandledSEDMLObjects.clear();
	this->createSEDMLDocument(dataModel);

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
		const std::string& SBMLFileName,
		unsigned int sedmlLevel,
		unsigned int sedmlVersion,
		bool overwrite)
{
	bool success = true;
	/* create a string that represents the SBMLDocument */
	std::string sbmldocument;
	std::string str = this->exportModelAndTasksToString(dataModel, sbmldocument, sedmlLevel, sedmlVersion);
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

void CSEDMLExporter::createSEDMLDocument(CCopasiDataModel& dataModel)
{
  const SedDocument* pOldSEDMLDocument = NULL; //dataModel.getCurrentSEDMLDocument();
  const CModel* pModel = dataModel.getModel();
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

	std::string simRef, modelRef;
    createSimulations(dataModel, simRef);
    createModels(dataModel, modelRef);
    createTasks(dataModel, simRef, modelRef);
  //  createDataGenerators(dataModel);
   // createReports(dataModel);

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
	modelRef = "model1";
	SedModel *model = this->mpSEDMLDocument->createModel();
	model->setId(modelRef);
	model->setSource("model1.xml");
	model->setLanguage("urn:sedml:sbml");
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
		plotIdStream << plotName;
		plotIdStream << "_";
		plotIdStream << i;
		pPSedPlot->setId(plotIdStream.str());
		pPSedPlot->setName(plotName);


		size_t j, jmax = pPlot->getItems().size();
		for (j = 0; j < jmax; j++) {
			const CPlotItem* pPlotItem = pPlot->getItems()[j];

			pPDGen = this->mpSEDMLDocument->createDataGenerator();

			std::string strName = pPlotItem->getObjectName();

			//remove unwanted characters from the plot item object name
			char chars [] = "[]";
			for (unsigned int i = 0; i < strlen(chars); ++i) {

				strName.erase(std::remove(strName.begin(), strName.end(), chars[i]), strName.end());
			}

			std::ostringstream idStrStream;
			idStrStream << strName;
			idStrStream << "_";
			idStrStream << j;
			pPDGen->setId(idStrStream.str());

			pPDGen->setName(strName);

			pCurve = pPSedPlot->createCurve();
			pCurve->setLogX(pPlot->isLogX());
			pCurve->setLogY(pPlot->isLogY());
			pCurve->setXDataReference(pTimeDGenp->getId());
			pCurve->setYDataReference(pPDGen->getId());

			SedVariable * pPVar = pPDGen->createVariable();
			pPVar->setId(pPDGen->getName());
			pPVar->setTaskReference(taskId);
			pPVar->setName(pPDGen->getName());

			//TODO
			size_t k, kmax = pPlotItem->getNumChannels();
			for (k = 0; k < kmax; k++) {
				const CPlotDataChannelSpec pDataChannelSpec = pPlotItem->getChannels()[k];
		//plot->setId(pDataChannelSpec.getObjectName());

			}

		}

	}
}

/**
 * Creates the Tasks for SEDML.
 */
//void CSEDMLExporter::createPlot2D(CCopasiDataModel &dataModel) //, SedPlot2D * pPSedPlot, std::string &curveId, std::string yDRef, bool logX, bool logY)
//{
	//SedPlot2D* pPSedPlot;
//	pPSedPlot = this->mpSEDMLDocument->createPlot2D();
/*	pPSedPlot->setId("plot1");
	pPSedPlot->setName("S1 Timecourse");
	SedCurve* pCurve = pPSedPlot->createCurve();
	pCurve->setId(curveId);
	//curve->setName(curveId);
	pCurve->setLogX(logX);
	pCurve->setLogY(logY);
	pCurve->setXDataReference("time");
	pCurve->setYDataReference(yDRef);
*/
	/*
	size_t i, imax = dataModel.getPlotDefinitionList()->size();


	//std::cerr << "Saving " << imax << " plots." << std::endl;
	if (!imax)
		CCopasiMessage(CCopasiMessage::EXCEPTION, "No plot definition for this SEDML document.");

	//	  SedSimulation * sim = this->mpSEDMLDocument->createUniformTimeCourse();

	for (i = 0; i < imax; i++) {
		const CPlotSpecification* pPlot = (*dataModel.getPlotDefinitionList())[i];
		size_t j, jmax = pPlot->getItems().size();

		//std::cerr << "Saving " << jmax << "PlotItems." << std::endl;
		for (j = 0; j < jmax; j++) {
			const CPlotItem* pPlotItem = pPlot->getItems()[j];
			pPSedlot = this->mpSEDMLDocument->createPlot2D();
			pPSedlot->setId("curve_"+j);
			pPSedlot->setId(pPlotItem->getCN()+"_" + j);
			pPSedlot->setName(pPlotItem->getCN());

			//TODO
			size_t k, kmax = pPlotItem->getNumChannels();

			//std::cerr << "Saving " << kmax << " Channels." << std::endl;
			for (k = 0; k < kmax; k++) {
				const CPlotDataChannelSpec pDataChannelSpec = pPlotItem->getChannels()[k];
				//TODO
				pModel->getMetabolites()[iMet]->getConcentrationReference();
				plot->setId(pDataChannelSpec.get.get.getObjectName())

				if (!pDataChannelSpec.minAutoscale) {
					//TODO
				}

				if (!pDataChannelSpec.maxAutoscale) {
					//TODO
				}
			}

		}
	}

}*/



CSEDMLExporter::CSEDMLExporter() {
	// TODO Auto-generated constructor stub

}

CSEDMLExporter::~CSEDMLExporter() {
	// TODO Auto-generated destructor stub
}

