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
#include "SEDMLUtils.h"


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
#include "model/CModelValue.h"
#include "commandline/CLocaleString.h"


#include "sbml/Model.h"
#include "sbml/Species.h"
#include "sbml/Parameter.h"
#include "sbml/Reaction.h"

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

	//std::cout<<str<<std::endl; //only for debuging

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

 // CModelValue modelV;
 // CCopasiVector <CModelValue> value = dataModel.getModel()->getModelValues();
 // value.setObjectName("TestMe");

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
	modelRef = "model1";
	SedModel *model = this->mpSEDMLDocument->createModel();
	model->setId(modelRef);
	model->setSource(modelRef+".xml");
	model->setLanguage("urn:sedml:language:sbml");
}

/**
 * Creates the Tasks for SEDML.
 */
void CSEDMLExporter::createTasks(CCopasiDataModel& dataModel, std::string & simRef, std::string & modelRef)
{
	SedTask *task = this->mpSEDMLDocument->createTask();
	//SedSimulation * sim = this->mpSEDMLDocument->createUniformTimeCourse();
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
	const CModel* pModel = dataModel.getModel();
	std::vector<std::string> stringsContainer; //split string container
	SEDMLUtils utils;
	char delim;
	if (pModel == NULL) CCopasiMessage(CCopasiMessage::ERROR, "No model for this SEDML document. An SBML model must exist for every SEDML document.");

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
		CCopasiMessage(CCopasiMessage::ERROR, "No plot definition for this SEDML document.");

	for (i = 0; i < imax; i++) {
		pPSedPlot = this->mpSEDMLDocument->createPlot2D();
		const CPlotSpecification* pPlot = (*dataModel.getPlotDefinitionList())[i];
		std::string plotName = pPlot->getObjectName();

		char chars[] = "[]";
		for (unsigned int ii = 0; ii < strlen(chars); ++ii) {
			plotName.erase(std::remove(plotName.begin(), plotName.end(), chars[ii]), plotName.end());
		}

		std::ostringstream plotIdStream;
		plotIdStream << "plot";
		plotIdStream << i+1;
		pPSedPlot->setId(plotIdStream.str());
		pPSedPlot->setName(plotName);

		size_t j, jmax = pPlot->getItems().size();
		for (j = 0; j < jmax; j++) {
			const CPlotItem* pPlotItem = pPlot->getItems()[j];

			pPDGen = this->mpSEDMLDocument->createDataGenerator();

			CCopasiObject *objectX, *objectY;
			if (pPlotItem->getChannels().size() >= 1)
				objectX = dataModel.getDataObject(pPlotItem->getChannels()[0]);

			if (pPlotItem->getChannels().size() >= 2)
				objectY = dataModel.getDataObject(pPlotItem->getChannels()[1]);

		std::string yAxis = objectY->getObjectDisplayName();
		std::string targetXPathString ="";

		 std::string type = objectY->getObjectName();
			if (type == "Concentration") {
				targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfSpecies/sbml:species[@id=\'";
				//remove unwanted characters from the plot item object name
				char concChars[] = "[]";
				for (unsigned int ii = 0; ii < strlen(concChars); ++ii) {
					yAxis.erase(std::remove(yAxis.begin(), yAxis.end(), concChars[ii]), yAxis.end());
				}
				CCopasiVector<CMetab>::const_iterator it = pModel->getMetabolites().begin(), endit = pModel->getMetabolites().end();
				const std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = const_cast<CCopasiDataModel&>(dataModel).getCopasi2SBMLMap();
				std::map<CCopasiObject*, SBase*>::const_iterator pos;
				const Species* pSBMLSpecies = NULL;
				while (it != endit)
				{
					pos = copasi2sbmlmap.find(*it);

					if (pos != copasi2sbmlmap.end())
					{
						pSBMLSpecies = dynamic_cast<const Species*>(pos->second);
						std::string name = pSBMLSpecies->getName();
						if(name.compare(yAxis) == 0){
							//	  std::cout<<"Name: "<<pSBMLSpecies->getName()<<std::endl;
							yAxis = pSBMLSpecies->getId();
						}
					}
					++it;
				}
			} else if (type == "Flux") {
				targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfReactions/sbml:reaction[@id=\'";
				delim = ')';
				utils.splitStrings(yAxis, delim, stringsContainer);
				yAxis = stringsContainer[0];

				char fluxChars[] = "(";
					for (unsigned int ii = 0; ii < strlen(fluxChars); ++ii) {
						yAxis.erase(std::remove(yAxis.begin(), yAxis.end(), fluxChars[ii]), yAxis.end());
					}

				CCopasiVector<CReaction>::const_iterator it = pModel->getReactions().begin(), endit = pModel->getReactions().end();
				const std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = const_cast<CCopasiDataModel&>(dataModel).getCopasi2SBMLMap();
				std::map<CCopasiObject*, SBase*>::const_iterator pos;
				const Reaction* pSBMLReaction = NULL;

				while (it != endit) {
					pos = copasi2sbmlmap.find(*it);

					if (pos != copasi2sbmlmap.end()) {
						pSBMLReaction = dynamic_cast<const Reaction*>(pos->second);
						std::string name = pSBMLReaction->getName();
						if (name.compare(yAxis) == 0) {
							yAxis = pSBMLReaction->getId();
						}
					}
					++it;
				}



			} else if (type == "Value") {
				targetXPathString = "/sbml:sbml/sbml:model/sbml:listOfParameters/sbml:parameter[@id=\'";
				delim = '[';
				utils.splitStrings(yAxis, delim, stringsContainer);
				yAxis = stringsContainer[1];

				char valueChars[] = "]";
				for (unsigned int ii = 0; ii < strlen(valueChars); ++ii) {
					yAxis.erase(std::remove(yAxis.begin(), yAxis.end(), valueChars[ii]), yAxis.end());
				}

				CCopasiVector<CModelValue>::const_iterator it = pModel->getModelValues().begin(), endit = pModel->getModelValues().end();
				const std::map<CCopasiObject*, SBase*>& copasi2sbmlmap = const_cast<CCopasiDataModel&>(dataModel).getCopasi2SBMLMap();
				std::map<CCopasiObject*, SBase*>::const_iterator pos;
				const Parameter* pSBMLParameter = NULL;

				while (it != endit) {
					pos = copasi2sbmlmap.find(*it);

					if (pos != copasi2sbmlmap.end()) {
						pSBMLParameter =
								dynamic_cast<const Parameter*>(pos->second);
						std::string name = pSBMLParameter->getName();
						if (name.compare(yAxis) == 0) {
							yAxis = pSBMLParameter->getId();
						}
					}
					++it;
				}
			} else {
				return;
			}

			std::ostringstream idStrStream;
			idStrStream << yAxis;
			idStrStream << "_";
			idStrStream << j+1;
			pPDGen->setId(idStrStream.str());

			pPDGen->setName(yAxis);
			pPDGen->setMath(SBML_parseFormula(pPDGen->getName().c_str()));

			SedVariable * pPVar = pPDGen->createVariable();
			std::ostringstream idVarStrStream;
			idVarStrStream << "p";
			idVarStrStream << i+1;
			idVarStrStream<<"_";
			idVarStrStream << pPDGen->getName() ;
			pPVar->setId(idVarStrStream.str());
			pPVar->setTaskReference(taskId);
			pPVar->setName(pPDGen->getName());

			//temporary method to set XPath target
			std::ostringstream targetStrStream;
			targetStrStream<<targetXPathString;
			targetStrStream<<pPVar->getName();
			targetStrStream<<"\']";
			pPVar->setTarget(targetStrStream.str());

			pCurve = pPSedPlot->createCurve();
			std::ostringstream idCurveStrStream;
			idCurveStrStream<<"p";
			idCurveStrStream<<i+1;
			idCurveStrStream<<"_curve_";
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

