/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DataModel.cpp,v $
   $Revision: 1.50 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/12/06 20:06:59 $
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
#include "steadystate/CMCATask.h"
#include "report/CReportDefinitionVector.h"
#include "plot/CPlotSpec2Vector.h"
#include "optimization/COptFunction.h"
#include "xml/CCopasiXML.h"
#include "steadystate/CMCAMethod.h"

DataModel::DataModel()
{
  //this->populateData();
  model = NULL;
  mChanged = false;
  trajectorytask = NULL;
  steadystatetask = NULL;
  scantask = NULL;
  reportdefinitions = NULL;
  plotspecs = NULL;
  pOptFunction = NULL;
  mpCMCATask = NULL;
}

bool DataModel::createModel()
{
  mChanged = false;

  pdelete(model);
  model = new CModel();
  Copasi->pModel = model;

  pdelete(steadystatetask);
  steadystatetask = new CSteadyStateTask();
  steadystatetask->getProblem()->setModel(model);

  pdelete(trajectorytask);
  trajectorytask = new CTrajectoryTask();
  trajectorytask->getProblem()->setModel(model);

  pdelete(scantask);
  scantask = new CScanTask();
  scantask->getProblem()->setModel(model);

  pdelete(mpCMCATask);
  mpCMCATask = new CMCATask();
  mpCMCATask->getProblem()->setModel(model);
  dynamic_cast<CMCAMethod*>(mpCMCATask->getMethod())->setModel(model);

  pdelete(reportdefinitions);
  reportdefinitions = new CReportDefinitionVector();

  pdelete(plotspecs);
  plotspecs = new CPlotSpec2Vector();

  pdelete(pOptFunction);
  pOptFunction = new COptFunction();

  return true;
}

bool DataModel::loadModel(const char* fileName)
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
      model->load(inbuf);

      pdelete(steadystatetask);
      steadystatetask = new CSteadyStateTask();
      steadystatetask->load(inbuf);

      pdelete(trajectorytask);
      trajectorytask = new CTrajectoryTask();
      trajectorytask->load(inbuf);

      pdelete(scantask);
      scantask = new CScanTask();
      scantask->getProblem()->setModel(model);

      pdelete(mpCMCATask);
      mpCMCATask = new CMCATask();
      mpCMCATask->getProblem()->setModel(model);
      dynamic_cast<CMCAMethod*>(mpCMCATask->getMethod())->setModel(model);

      pdelete(reportdefinitions);
      reportdefinitions = new CReportDefinitionVector();

      pdelete(plotspecs);
      plotspecs = new CPlotSpec2Vector();

      pdelete(pOptFunction);
      pOptFunction = new COptFunction();
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
      XML.setPlotList(*pNewPlotSpecs);

      if (!XML.load(File)) return false;

      pdelete(model);
      model = XML.getModel();

      pdelete(steadystatetask);
      pdelete(trajectorytask);
      pdelete(scantask);
      pdelete(mpCMCATask);

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

            case CCopasiTask::mca:
              mpCMCATask = dynamic_cast< CMCATask * >(TaskList[i]);
              break;
            }
        }

      if (!steadystatetask) steadystatetask = new CSteadyStateTask();
      steadystatetask->getProblem()->setModel(model);

      if (!trajectorytask) trajectorytask = new CTrajectoryTask();
      trajectorytask->getProblem()->setModel(model);

      if (!scantask) scantask = new CScanTask();
      scantask->getProblem()->setModel(model);

      if (!mpCMCATask) mpCMCATask = new CMCATask();
      mpCMCATask->getProblem()->setModel(model);
      dynamic_cast<CMCAMethod*>(mpCMCATask->getMethod())->setModel(model);

      pdelete(reportdefinitions);
      reportdefinitions = pNewReports;

      pdelete(plotspecs);
      plotspecs = pNewPlotSpecs;

      pdelete(pOptFunction);
      pOptFunction = new COptFunction();
    }

  if (model) model->setCompileFlag();

  return true;
}

bool DataModel::saveModel(const char* fileName)
{
  if (fileName == NULL) return false;

  model->compileIfNecessary();

  CCopasiXML XML;
  std::ofstream os(fileName);

  XML.setModel(*model);
  XML.setReportList(*reportdefinitions);

  CCopasiVectorN< CCopasiTask > TaskList;
  if (steadystatetask) TaskList.add(steadystatetask);
  if (trajectorytask) TaskList.add(trajectorytask);
  //  if (scantask) TaskList.add(scantask);
  if (mpCMCATask) TaskList.add(mpCMCATask);
  XML.setTaskList(TaskList);

  XML.setPlotList(*plotspecs);
  XML.save(os);

  return true;
}

bool DataModel::isChanged() const {return mChanged;}

void DataModel::changed(const bool & changed) {mChanged = changed;}

bool DataModel::importSBML(const char* fileName)
{
  mChanged = false;

  pdelete(pOptFunction);
  pOptFunction = new COptFunction();

  SBMLImporter importer;
  CModel * pModel = importer.readSBML(fileName, Copasi->pFunctionDB);

  if (pModel == NULL) return false;

  pdelete(model);
  model = pModel;

  Copasi->pModel = model;

  pdelete(steadystatetask);
  steadystatetask = new CSteadyStateTask();
  steadystatetask->getProblem()->setModel(model);

  pdelete(trajectorytask);
  trajectorytask = new CTrajectoryTask();
  trajectorytask->getProblem()->setModel(model);

  pdelete(scantask);
  scantask = new CScanTask();
  scantask->getProblem()->setModel(model);

  pdelete(mpCMCATask);
  mpCMCATask = new CMCATask();
  mpCMCATask->getProblem()->setModel(model);
  dynamic_cast<CMCAMethod*>(mpCMCATask->getMethod())->setModel(model);

  pdelete(reportdefinitions);
  reportdefinitions = new CReportDefinitionVector();

  pdelete(plotspecs);
  plotspecs = new CPlotSpec2Vector();

  return true;
}

bool DataModel::exportSBML(const char* fileName)
{
  if (fileName == NULL) return false;

  SBMLExporter exporter;

  exporter.exportSBML(model, fileName);

  return true;
}
