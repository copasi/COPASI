/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/DataModel.cpp,v $
   $Revision: 1.40 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/08/05 12:55:51 $
   End CVS Header */

#include "DataModel.h" 
//#include "DataModel.txt.h"
#include "function/CFunctionDB.h"
#include "sbml/SBMLImporter.h"
#include "sbml/SBMLExporter.h"

#include "utilities/CGlobals.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "scan/CScanTask.h"
#include "report/CReportDefinitionVector.h"
#include "plot/CPlotSpecVector.h"
#include "plot/CPlotSpec2Vector.h"
#include "optimization/COptFunction.h"
#include "xml/CCopasiXML.h"

DataModel::DataModel()
{
  //this->populateData();
  model = NULL;
  //mpMathModel = NULL;
  //mMathModelUpdateScheduled = false;
  mChanged = false;
  trajectorytask = NULL;
  steadystatetask = NULL;
  scantask = NULL;
  reportdefinitions = NULL;
  plotspecs = NULL;
  pOptFunction = NULL;
}

void DataModel::createModel()
{
  mChanged = false;

  pdelete(model);
  model = new CModel();
  Copasi->pModel = model;
  //  CProgressBar* tmpBar = new CProgressBar(this);
  //  model->setCompileHandler(tmpBar);
  //  searchFolderList(1)->setObjectKey(model->getKey());

  //  pdelete(mpMathModel);
  //  mpMathModel = new CMathModel();
  //  mpMathModel->setModel(model);

  pdelete(steadystatetask);
  steadystatetask = new CSteadyStateTask();
  steadystatetask->getProblem()->setModel(model);
  //  searchFolderList(21)->setObjectKey(steadystatetask->getKey());

  pdelete(trajectorytask);
  trajectorytask = new CTrajectoryTask();
  trajectorytask->getProblem()->setModel(model);
  //  COutputHandlerPlot* tmpHandler = new COutputHandlerPlot();
  //  trajectorytask->setOutputHandler(tmpHandler);
  //  searchFolderList(23)->setObjectKey(trajectorytask->getKey());  //23=Time course

  pdelete(scantask);
  scantask = new CScanTask();
  scantask->getProblem()->setModel(model);
  //  searchFolderList(32)->setObjectKey(scantask->getKey());

  pdelete(reportdefinitions);
  reportdefinitions = new CReportDefinitionVector();
  //  searchFolderList(43)->setObjectKey(reportdefinitions->getKey());

  pdelete(plotspecs);
  plotspecs = new CPlotSpec2Vector();
  //  searchFolderList(42)->setObjectKey(plotspecs->getKey());

  //  tmpHandler->setPlotSpecVectorAddress(plotspecs);

  pdelete(pOptFunction);
  pOptFunction = new COptFunction();
  //searchFolderList(31)->setObjectKey(pOptFunction->getKey());
}

void DataModel::loadModel(const char* fileName)
{
  mChanged = false;

  std::ifstream File(fileName);
  std::string Line;
  File >> Line;

  if (!Line.compare(0, 8, "Version="))
    {
      File.close();
      pdelete(model);
      CReadConfig inbuf(fileName);
      model = new CModel();
      //      CProgressBar* tmpBar = new CProgressBar(this);
      //      model->setCompileHandler(tmpBar);
      model->load(inbuf);
      //searchFolderList(1)->setObjectKey(model->getKey());

      pdelete(steadystatetask);
      steadystatetask = new CSteadyStateTask();
      steadystatetask->load(inbuf);
      //searchFolderList(21)->setObjectKey(steadystatetask->getKey());

      pdelete(trajectorytask);
      trajectorytask = new CTrajectoryTask();
      trajectorytask->load(inbuf);
      //COutputHandlerPlot* tmpHandler = new COutputHandlerPlot();
      //trajectorytask->setOutputHandler(tmpHandler);
      //searchFolderList(23)->setObjectKey(trajectorytask->getKey()); //23=Time course

      pdelete(scantask);
      scantask = new CScanTask();
      scantask->getProblem()->setModel(model);
      // future work  scantask->load(inbuf);
      //searchFolderList(32)->setObjectKey(scantask->getKey());

      pdelete(reportdefinitions);
      reportdefinitions = new CReportDefinitionVector();
      //  reportdefinitions->load(inbuf);
      //searchFolderList(43)->setObjectKey(reportdefinitions->getKey());

      pdelete(plotspecs);
      plotspecs = new CPlotSpec2Vector();
      //  plotspecs->load(inbuf);
      //searchFolderList(42)->setObjectKey(plotspecs->getKey());

      //tmpHandler->setPlotSpecVectorAddress(plotspecs);

      pdelete(pOptFunction);
      pOptFunction = new COptFunction();
      //searchFolderList(31)->setObjectKey(pOptFunction->getKey());

      //Copasi->pOutputList->load(inbuf);
    }
  else if (!Line.compare(0, 5, "<?xml"))
    {
      std::cout << "XML Format" << std::endl;
      File.seekg(0, std::ios_base::beg);

      CCopasiXML XML;

      XML.setFunctionList(Copasi->pFunctionDB->loadedFunctions());

      CReportDefinitionVector * pNewReports = new CReportDefinitionVector();
      XML.setReportList(*pNewReports);

      CCopasiVectorN< CCopasiTask > TaskList;
      XML.setTaskList(TaskList);

      CPlotSpec2Vector * pNewPlotSpecs = new CPlotSpec2Vector();
      //TODO XML.setPlotList(*pNewPlotSpecs);

      XML.load(File);

      pdelete(model);
      model = XML.getModel();
      //      CProgressBar* tmpBar = new CProgressBar(this);
      //      model->setCompileHandler(tmpBar);
      //searchFolderList(1)->setObjectKey(model->getKey());

      pdelete(steadystatetask);
      pdelete(trajectorytask);
      pdelete(scantask);

      unsigned C_INT32 i, imax = TaskList.size();
      for (i = 0; i < imax; i++)
        {
          switch (TaskList[i]->getType())
            {
            case CCopasiTask::steadyState:
              steadystatetask = dynamic_cast< CSteadyStateTask * >(TaskList[i]);
              break;

            case CCopasiTask::timeCourse:
              trajectorytask = dynamic_cast< CTrajectoryTask * >(TaskList[i]);
              break;

            case CCopasiTask::scan:
              scantask = dynamic_cast< CScanTask * >(TaskList[i]);
              break;
            }
        }

      if (!steadystatetask) steadystatetask = new CSteadyStateTask();
      steadystatetask->getProblem()->setModel(model);
      //searchFolderList(21)->setObjectKey(steadystatetask->getKey());

      if (!trajectorytask) trajectorytask = new CTrajectoryTask();
      trajectorytask->getProblem()->setModel(model);
      //COutputHandlerPlot* tmpHandler = new COutputHandlerPlot();
      //trajectorytask->setOutputHandler(tmpHandler);
      //searchFolderList(23)->setObjectKey(trajectorytask->getKey()); //23=Time course

      if (!scantask) scantask = new CScanTask();
      scantask->getProblem()->setModel(model);
      //searchFolderList(32)->setObjectKey(scantask->getKey());

      pdelete(reportdefinitions);
      reportdefinitions = pNewReports;
      //searchFolderList(43)->setObjectKey(reportdefinitions->getKey());

      pdelete(plotspecs);
      plotspecs = pNewPlotSpecs;
      //searchFolderList(42)->setObjectKey(plotspecs->getKey());

      //tmpHandler->setPlotSpecVectorAddress(plotspecs);
    }

  model->setCompileFlag();

  //  pdelete(mpMathModel);
  //  mpMathModel = new CMathModel();
  //  mpMathModel->setModel(model);

  //  steadystatetask->compile();
}

void DataModel::saveModel(const char* fileName)
{
  if (fileName == NULL) return;

  model->compileIfNecessary();

  CCopasiXML XML;
  std::ofstream os(fileName);

  XML.setModel(*model);
  XML.setReportList(*reportdefinitions);

  CCopasiVectorN< CCopasiTask > TaskList;
  if (steadystatetask) TaskList.add(steadystatetask);
  if (trajectorytask) TaskList.add(trajectorytask);
  //  if (scantask) TaskList.add(scantask);
  XML.setTaskList(TaskList);

  //TODO XML.setPlotList(*plotspecs);
  XML.save(os);
}

bool DataModel::isChanged() const {return mChanged;}

void DataModel::changed(const bool & changed) {mChanged = changed;}

void DataModel::importSBML(const char* fileName)
{
  mChanged = false;

  pdelete(pOptFunction);
  pOptFunction = new COptFunction();
  //searchFolderList(31)->setObjectKey(pOptFunction->getKey());

  pdelete(model);
  SBMLImporter* importer = new SBMLImporter();
  try
    {
      model = importer->readSBML(fileName, Copasi->pFunctionDB);
    }
  catch (StdException ex)
  {}
  if (model == NULL)
    {
      model = new CModel();
    }

  //  CProgressBar* tmpBar = new CProgressBar(this);
  //  model->setCompileHandler(tmpBar);
  Copasi->pModel = model;
  //searchFolderList(1)->setObjectKey(model->getKey());

  pdelete(steadystatetask);
  steadystatetask = new CSteadyStateTask();
  steadystatetask->getProblem()->setModel(model);
  //searchFolderList(21)->setObjectKey(steadystatetask->getKey());

  pdelete(trajectorytask);
  trajectorytask = new CTrajectoryTask();
  trajectorytask->getProblem()->setModel(model);
  //COutputHandlerPlot* tmpHandler = new COutputHandlerPlot();
  //trajectorytask->setOutputHandler(tmpHandler);
  //searchFolderList(23)->setObjectKey(trajectorytask->getKey());  //23=Time course

  pdelete(scantask);
  scantask = new CScanTask();
  scantask->getProblem()->setModel(model);
  //searchFolderList(32)->setObjectKey(scantask->getKey());

  pdelete(reportdefinitions);
  reportdefinitions = new CReportDefinitionVector();
  //searchFolderList(43)->setObjectKey(reportdefinitions->getKey());

  pdelete(plotspecs);
  plotspecs = new CPlotSpec2Vector();
  //searchFolderList(42)->setObjectKey(plotspecs->getKey());

  //tmpHandler->setPlotSpecVectorAddress(plotspecs);

  //  pdelete(mpMathModel);
  //  mpMathModel = new CMathModel();
  //  mpMathModel->setModel(model);
}

void DataModel::exportSBML(const char* fileName)
{
  if (fileName == NULL) return;

  SBMLExporter exporter;

  exporter.exportSBML(model, fileName);
}
