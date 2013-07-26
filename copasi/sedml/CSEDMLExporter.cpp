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


#include <sedml/SedReader.h>
#include <sedml/SedDocument.h>
#include <sedml/SedModel.h>
#include <sedml/SedSimulation.h>
#include <sedml/SedUniformTimeCourse.h>
#include <sedml/SedDataGenerator.h>
#include <sedml/SedPlot2D.h>
#include <sedml/SedAlgorithm.h>


#include "sbml/CSBMLExporter.h"

#include "CSEDMLExporter.h"
#include "utilities/CCopasiException.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "plot/COutputDefinitionVector.h"
#include "plot/CPlotSpecification.h"

const std::string exportModelAndTasksToString(CCopasiDataModel& dataModel,
		std::string &sbmldocument,
		unsigned int sedmlLevel,
		unsigned int sedmlVersion)
{
	CSBMLExporter exporter;
	return NULL;
}

/**
 * Export the model and Task to SEDML.
 * The SEDML document is written to the file given by SEDMLFilename and reference SBML model is written to SBMLFilename .
 * If the export fails, false is returned.
 */
bool exportModelAndTasks(CCopasiDataModel& dataModel,
		const std::string& SEDMLFilename,
		const std::string& SBMLFilename,
		unsigned int sedmlLevel = 1,
		unsigned int sedmlVersion = 1,
		bool overwrite = false) {

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
    createTasks(dataModel);
    createDataGenerators(dataModel);
    createReports(dataModel);

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
void CSEDMLExporter::createTasks(CCopasiDataModel& dataModel)
{
	size_t i, imax = dataModel.getPlotDefinitionList()->size();

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
}

/**
 * Creates the data generators for SEDML.
 */
void CSEDMLExporter::createDataGenerators(CCopasiDataModel & dataModel)
{

}

/**
 * Creates the Tasks for SEDML.
 */
void CSEDMLExporter::createReports(CCopasiDataModel &dataModel)
{

}



CSEDMLExporter::CSEDMLExporter() {
	// TODO Auto-generated constructor stub

}

CSEDMLExporter::~CSEDMLExporter() {
	// TODO Auto-generated destructor stub
}

