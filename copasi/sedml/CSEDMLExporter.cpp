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
#include "utilities/CCopasiException.h"
#include "utilities/CVersion.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"
#include "model/CModel.h"


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
}

/**
 * Export the model and Task to SEDML.
 * The SEDML document is written to the file given by SEDMLFilename and reference SBML model is written to SBMLFilename .
 * If the export fails, false is returned.
 */
bool CSEDMLExporter::exportModelAndTasks(CCopasiDataModel& dataModel,
		const std::string& SEDMLFilename,
		const std::string& SBMLFilename,
		unsigned int sedmlLevel,
		unsigned int sedmlVersion,
		bool overwrite)
{

}

void CSEDMLExporter::createSEDMLDocument(CCopasiDataModel& dataModel)
{
  const SedDocument* pOldSEDMLDocument = dataModel.getCurrentSEDMLDocument();
  const CModel* pModel = dataModel.getModel();
  assert(pModel != NULL);

  if (pOldSEDMLDocument == NULL) {
		this->mpSEDMLDocument = new SedDocument(this->mSEDMLLevel, this->mSEDMLVersion);
	} else {
		this->mpSEDMLDocument = dynamic_cast<SedDocument*>(pOldSEDMLDocument->clone());
	}
	if (this->mpSEDMLDocument == NULL) fatalError();

  //  CSBMLExporter exporter;
	// Right now we always import the COPASI MIRIAM annotation if it is there.
	// Later this will be settable by the user in the preferences dialog
	//exporter.setExportCOPASIMIRIAM(true);

    createSimulations(dataModel);
    createModels(dataModel);
    std::string simRef ="simRef", modelRef = "modeRef";
    createTasks(dataModel, simRef, modelRef);
  //  createDataGenerators(dataModel);
   // createReports(dataModel);

}

/**
 * Creates the simulations for SEDML.
 */
void CSEDMLExporter::createSimulations(CCopasiDataModel& dataModel)
{
	SedUniformTimeCourse* tc = this->mpSEDMLDocument->createUniformTimeCourse();
	tc->setId("sim1");
	tc->setInitialTime(0.0);
	tc->setOutputStartTime(0.0);
	tc->setOutputEndTime(10.0);
	tc->setNumberOfPoints(1000);

	// set the correct KISAO Term
	SedAlgorithm* alg = tc->createAlgorithm();
	alg->setKisaoID("KISAO:0000019");

}

/**
 * Creates the models for SEDML.
 */
void CSEDMLExporter::createModels(CCopasiDataModel& dataModel)
{

}

/**
 * Creates the Tasks for SEDML.
 */
void CSEDMLExporter::createTasks(CCopasiDataModel& dataModel, std::string & simRef, std::string & modelRef)
{
	SedTask *task = this->mpSEDMLDocument->createTask();
	SedSimulation * sim = this->mpSEDMLDocument->createUniformTimeCourse();
	SedModel *mod = this->mpSEDMLDocument->createModel();
	std::string taskId = "task1";
	task->setId(taskId);
	task->setSimulationReference(simRef),
	task->setModelReference(modelRef);
	createDataGenerators(dataModel, taskId);




	/*	size_t i, imax = dataModel.getPlotDefinitionList()->size();


	  //std::cerr << "Saving " << imax << " plots." << std::endl;
	  if (!imax) CCopasiMessage(CCopasiMessage::EXCEPTION, "No plot definition for this SEDML document.");

	  //	  SedSimulation * sim = this->mpSEDMLDocument->createUniformTimeCourse();

	  for (i = 0; i < imax; i++)
	    {
	      const CPlotSpecification* pPlot = (*dataModel.getPlotDefinitionList())[i];
	      size_t j, jmax = pPlot->getItems().size();

	      //std::cerr << "Saving " << jmax << "PlotItems." << std::endl;
	      for (j = 0; j < jmax; j++)
	        {
	          const CPlotItem* pPlotItem = pPlot->getItems()[j];

	         //TODO
	          size_t k, kmax = pPlotItem->getNumChannels();

	          //std::cerr << "Saving " << kmax << " Channels." << std::endl;
	          for (k = 0; k < kmax; k++)
	            {
	              const CPlotDataChannelSpec pDataChannelSpec = pPlotItem->getChannels()[k];
	              //TODO

	              if (!pDataChannelSpec.minAutoscale)
	                {
	                  //TODO
	                }

	              if (!pDataChannelSpec.maxAutoscale)
	                {
	                  //TODO
	                }
	            }

	        }
	    }
	  */
}

/**
 * Creates the data generators for SEDML.
 */
void CSEDMLExporter::createDataGenerators(CCopasiDataModel & dataModel, std::string & taskId)
{
	SedPlot2D* pPSedPlot;
	SedCurve* pCurve; // = pPSedPlot->createCurve();
	//SedDataGenerator *pPDGen;

	//create generator for special varibale time
	const CCopasiObject* pTime = static_cast<const CCopasiObject *>(dataModel.getModel()->getObject(CCopasiObjectName("Reference=Time")));
	SedDataGenerator *pTimeDGenp = this->mpSEDMLDocument->createDataGenerator();
	pTimeDGenp->setId("time");
	pTimeDGenp->setName(pTime->getCN());
	SedVariable *pTimeVar = pTimeDGenp->createVariable();
	pTimeVar->setId("var_time");
	pTimeVar->setTaskReference(taskId);
	pTimeVar->setSymbol("usn:sedml:symbol:time");
	pTimeDGenp->setMath(SBML_parseFormula(pTimeVar->getId().c_str()));
//	pPDGen->setId(yDataRefenrence);



	size_t i, imax = dataModel.getPlotDefinitionList()->size();
	SedPlot2D* pPSedlot;
	SedDataGenerator *pPDGen;
	if (!imax)
		CCopasiMessage(CCopasiMessage::EXCEPTION, "No plot definition for this SEDML document.");

	for (i = 0; i < imax; i++) {
		pPSedPlot = this->mpSEDMLDocument->createPlot2D();
		const CPlotSpecification* pPlot = (*dataModel.getPlotDefinitionList())[i];
		pPSedPlot->setId(pPlot->getCN());
		pPSedPlot->setName(pPlot->getCN());

		size_t j, jmax = pPlot->getItems().size();
		for (j = 0; j < jmax; j++) {
			const CPlotItem* pPlotItem = pPlot->getItems()[j];

			pPDGen = this->mpSEDMLDocument->createDataGenerator();
			std::string name = pPlotItem->getCN();
			char cj = j;
			name = name + cj;
		//	pPDGen->setId(name + j);
			pPDGen->setName(pPlotItem->getCN());

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

