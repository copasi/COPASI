/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/DataModelGUI.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/10/08 15:23:45 $
   End CVS Header */

#include "DataModelGUI.h"
#include "DataModel.txt.h"
#include "mathmodel/CMathModel.h"
#include "plot/COutputHandlerPlot.h"
#include "qtUtilities.h"
#include "CProgressBar.h"
#include "model/CModel.h"
#include "steadystate/CSteadyStateTask.h"
#include "trajectory/CTrajectoryTask.h"
#include "scan/CScanTask.h"
#include "report/CReportDefinitionVector.h"
#include "plot/CPlotSpec2Vector.h"
#include "optimization/COptFunction.h"
#include "model/CMetabNameInterface.h"
#include "utilities/CGlobals.h"
#include "function/CFunctionDB.h"

//int Folder::smModifier = 0;

//*****************************************************************************

DataModelGUI::DataModelGUI()
    : DataModel()
{
  this->populateData();
  mpMathModel = NULL;
  mMathModelUpdateScheduled = false;
}

//************************************************************

void DataModelGUI::linkDataModelToGUI()
{
  //TODO: delete old handler
  //progress bar
  CProgressBar* tmpBar = new CProgressBar(this);
  model->setCompileHandler(tmpBar);

  //output handler
  COutputHandlerPlot* tmpHandler = new COutputHandlerPlot();
  tmpHandler->setPlotSpecVectorAddress(plotspecs);
  trajectorytask->setOutputHandler(tmpHandler);

  //math model
  pdelete(mpMathModel);
  mpMathModel = new CMathModel();
  mpMathModel->setModel(model);

  //connect the folder tree with the backend objects
  mTree.findNodeFromId(1).setObjectKey(model->getKey());
  mTree.findNodeFromId(21).setObjectKey(steadystatetask->getKey());
  mTree.findNodeFromId(23).setObjectKey(trajectorytask->getKey());
  //mTree.findNodeFromId(32).setObjectKey(scantask->getKey());
  mTree.findNodeFromId(43).setObjectKey(reportdefinitions->getKey());
  mTree.findNodeFromId(42).setObjectKey(plotspecs->getKey());
  //mTree.findNodeFromId(31).setObjectKey(pOptFunction->getKey());
}

void DataModelGUI::populateData()
{
  std::stringstream in;
  in.str(DataModeltxt);

  std::string str1;
  std::string delimiter("\x0a\x0d");
  char c;

  while (!in.eof())
    {
      str1 = "";
      while (!in.fail())
        {
          in.get(c);
          if (delimiter.find(c) != std::string::npos) break;
          str1 += c;
        }

      if (str1 == "") break;

      QString data(FROM_UTF8(str1));

      int first = data.find(':');
      int second = data.find(':', first + 1);
      int parentId = data.mid(0, first).toInt();
      int myId = data.mid(first + 1, second - first - 1).toInt();
      QString str = data.mid(second + 1, data.length() - second - 1);

      mTree.add(parentId, myId, str, "");
    }
}

void DataModelGUI::updateCompartments()
{
  IndexedNode & parent = mTree.findNodeFromId(111);

  parent.removeChildren();

  if (model == NULL) return;
  const CCopasiVectorN< CCompartment > & objects = model->getCompartments();
  C_INT32 j, jmax = objects.size();
  CCompartment *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent.addChild(-1,
                       FROM_UTF8(obj->getObjectName()),
                       obj->getKey());
    }
}

void DataModelGUI::updateMetabolites()
{
  IndexedNode & parent = mTree.findNodeFromId(112);

  parent.removeChildren();

  if (model == NULL) return;
  const CCopasiVector< CMetab > & objects = model->getMetabolites();
  C_INT32 j, jmax = objects.size();
  CMetab *metab;
  for (j = 0; j < jmax; j++)
    {
      metab = objects[j];
      parent.addChild(-1,
                       FROM_UTF8(CMetabNameInterface::getDisplayName(model, *metab)),
                       metab->getKey());
    }
}

void DataModelGUI::updateReactions()
{
  IndexedNode & parent = mTree.findNodeFromId(114);

  parent.removeChildren();

  if (model == NULL) return;
  const CCopasiVectorN< CReaction > & objects = model->getReactions();
  C_INT32 j, jmax = objects.size();
  CReaction *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent.addChild(-1,
                       FROM_UTF8(obj->getObjectName()),
                       obj->getKey());
    }
}

void DataModelGUI::updateMoieties()
{
  IndexedNode & parent = mTree.findNodeFromId(222);

  parent.removeChildren();

  if (model == NULL) return;
  const CCopasiVectorN< CMoiety > & objects = model->getMoieties();
  C_INT32 j, jmax = objects.size();
  CMoiety *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent.addChild(-1,
                       FROM_UTF8(obj->getObjectName()),
                       obj->getKey());
    }
}

void DataModelGUI::updateFunctions()
{
  IndexedNode & parent = mTree.findNodeFromId(5);

  parent.removeChildren();

  //if (model == NULL) return;
  const CCopasiVectorN< CFunction > & objects = Copasi->pFunctionDB->loadedFunctions();
  C_INT32 j, jmax = objects.size();
  CFunction *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent.addChild(-1,
                       FROM_UTF8(obj->getObjectName()),
                       obj->getKey());
    }
}

void DataModelGUI::updateReportDefinitions()
{
  IndexedNode & parent = mTree.findNodeFromId(43);

  parent.removeChildren();

  //if (model == NULL) return;
  const CCopasiVector< CReportDefinition >* objects = getReportDefinitionVectorAddr();
  C_INT32 j, jmax = objects->size();
  CReportDefinition *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = (*objects)[j];
      parent.addChild(-1,
                       FROM_UTF8(obj->getObjectName()),
                       obj->getKey());
    }
}

void DataModelGUI::updatePlots()
{
  IndexedNode & parent = mTree.findNodeFromId(42);

  parent.removeChildren();

  //if (model == NULL) return;
  const CCopasiVector< CPlotSpecification >* objects = getPlotSpecVectorAddr();
  C_INT32 j, jmax = objects->size();
  CPlotSpecification *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = (*objects)[j];
      parent.addChild(-1,
                       FROM_UTF8(obj->getObjectName()),
                       obj->CCopasiParameter::getKey());
    }
}

//*****************************************************************

const IndexedNode & DataModelGUI::getRootNode() const
  {return mTree.getRoot();}

//*****************************************************************

void DataModelGUI::createModel()
{
  DataModel::createModel();
  linkDataModelToGUI();
}

void DataModelGUI::loadModel(const char* fileName)
{
  DataModel::loadModel(fileName);

  // model->setCompileFlag();
  if (model) linkDataModelToGUI();
}

void DataModelGUI::saveModel(const char* fileName)
{
  DataModel::saveModel(fileName);
}

void DataModelGUI::importSBML(const char* fileName)
{
  DataModel::importSBML(fileName);
  linkDataModelToGUI();
}

void DataModelGUI::exportSBML(const char* fileName)
{
  DataModel::exportSBML(fileName);
}

//************** Math model ***********************************************

bool DataModelGUI::updateMathModel()
{
  if (mMathModelUpdateScheduled) mpMathModel->setModel(model);

  mMathModelUpdateScheduled = false;
  return true;
}

bool DataModelGUI::scheduleMathModelUpdate(const bool & update)
{
  mMathModelUpdateScheduled = update;
  return true;
}

//************** QApplication ***********************************************

void DataModelGUI::setQApp(QApplication* app)
{mpApp = app;}

QApplication* DataModelGUI::getQApp() const
  {return mpApp;}
