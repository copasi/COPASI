/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DataModelGUI.cpp,v $
   $Revision: 1.22 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/03/02 20:50:25 $
   End CVS Header */

#include "copasi.h"

#include "DataModelGUI.h"
#include "DataModel.txt.h"
#include "qtUtilities.h"
#include "CProgressBar.h"
#include "listviews.h"

#include "function/CFunctionDB.h"
#include "mathmodel/CMathModel.h"
#include "model/CModel.h"
#include "model/CMetabNameInterface.h"
#include "optimization/COptFunction.h"
#include "plot/COutputHandlerPlot.h"
#include "plot/CPlotSpec2Vector.h"
#include "report/CReportDefinitionVector.h"
#include "scan/CScanTask.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CMCATask.h"
#include "trajectory/CTrajectoryTask.h"
#include "CopasiDataModel/CCopasiDataModel.h"

//int Folder::smModifier = 0;

//*****************************************************************************

DataModelGUI::DataModelGUI():
    mPlotDefinitionList()
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
  CCopasiDataModel::Global->getModel()->setCompileHandler(tmpBar);

  //output handler
  COutputHandlerPlot* tmpHandler = new COutputHandlerPlot();
  tmpHandler->setPlotSpecVectorAddress(& mPlotDefinitionList);
  (*CCopasiDataModel::Global->getTaskList())["Time-Course"]->setOutputHandler(tmpHandler);
  (*CCopasiDataModel::Global->getTaskList())["Scan"]->setOutputHandler(tmpHandler);

  //math model
  pdelete(mpMathModel);
  mpMathModel = new CMathModel();
  mpMathModel->setModel(CCopasiDataModel::Global->getModel());

  //connect the folder tree with the backend objects
  mTree.findNodeFromId(1)->setObjectKey(CCopasiDataModel::Global->getModel()->getKey());
  mTree.findNodeFromId(21)->setObjectKey((*CCopasiDataModel::Global->getTaskList())["Steady-State"]->getKey());
  mTree.findNodeFromId(23)->setObjectKey((*CCopasiDataModel::Global->getTaskList())["Time-Course"]->getKey());
  mTree.findNodeFromId(24)->setObjectKey((*CCopasiDataModel::Global->getTaskList())["Metabolic Control Analysis"]->getKey());

#ifdef COPASI_DEBUG
  mTree.findNodeFromId(31)->setObjectKey((*CCopasiDataModel::Global->getTaskList())["Scan"]->getKey());
  //  mTree.findNodeFromId(32).setObjectKey(pOptFunction->getKey());
  mTree.findNodeFromId(115)->setObjectKey(CCopasiDataModel::Global->getModel()->getKey());
#endif // COPASI_DEBUG

  mTree.findNodeFromId(43)->setObjectKey(CCopasiDataModel::Global->getReportDefinitionList()->getKey());
  mTree.findNodeFromId(42)->setObjectKey(mPlotDefinitionList.getKey());

  ListViews::setDataModel(this);
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
  IndexedNode * parent = mTree.findNodeFromId(111);

  parent->removeChildren();

  if (CCopasiDataModel::Global->getModel() == NULL) return;
  const CCopasiVectorN< CCompartment > & objects = CCopasiDataModel::Global->getModel()->getCompartments();
  C_INT32 j, jmax = objects.size();
  CCompartment *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->getKey());
    }
}

void DataModelGUI::updateMetabolites()
{
  IndexedNode * parent = mTree.findNodeFromId(112);

  parent->removeChildren();

  const CCopasiVector< CMetab > & objects = CCopasiDataModel::Global->getModel()->getMetabolites();
  C_INT32 j, jmax = objects.size();
  CMetab *metab;
  for (j = 0; j < jmax; j++)
    {
      metab = objects[j];
      parent->addChild(-1,
                        FROM_UTF8(CMetabNameInterface::getDisplayName(CCopasiDataModel::Global->getModel(), *metab)),
                        metab->getKey());
    }
}

void DataModelGUI::updateReactions()
{
  IndexedNode * parent = mTree.findNodeFromId(114);

  parent->removeChildren();

  const CCopasiVectorN< CReaction > & objects = CCopasiDataModel::Global->getModel()->getReactions();
  C_INT32 j, jmax = objects.size();
  CReaction *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->getKey());
    }
}

void DataModelGUI::updateMoieties()
{
  IndexedNode * parent = mTree.findNodeFromId(222);

  parent->removeChildren();

  const CCopasiVectorN< CMoiety > & objects = CCopasiDataModel::Global->getModel()->getMoieties();

  C_INT32 j, jmax = objects.size();
  CMoiety *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->getKey());
    }
}

void DataModelGUI::updateFunctions()
{
  IndexedNode * parent = mTree.findNodeFromId(5);

  parent->removeChildren();

  const CCopasiVectorN< CFunction > & objects = CCopasiDataModel::Global->getFunctionList()->loadedFunctions();
  C_INT32 j, jmax = objects.size();
  CFunction *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = objects[j];
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->getKey());
    }
}

void DataModelGUI::updateReportDefinitions()
{
  IndexedNode * parent = mTree.findNodeFromId(43);

  parent->removeChildren();

  const CCopasiVector< CReportDefinition >* objects = CCopasiDataModel::Global->getReportDefinitionList();
  C_INT32 j, jmax = objects->size();
  CReportDefinition *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = (*objects)[j];
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->getKey());
    }
}

void DataModelGUI::updatePlots()
{
  IndexedNode * parent = mTree.findNodeFromId(42);

  //if (parent.children().size())
  // {std::cout << " updatePlots() " << parent.children()[0]->getSortKey() << std::endl;
  //  std::cout << " updatePlots() " << parent.children()[0]->getName() << std::endl;}
  parent->removeChildren();

  //  const CCopasiVector< CPlotSpecification >* objects = mPlotDefinitionList;
  C_INT32 j, jmax = CCopasiDataModel::Global->getPlotDefinitionList()->size();
  CPlotSpecification *obj;
  for (j = 0; j < jmax; j++)
    {
      obj = (*CCopasiDataModel::Global->getPlotDefinitionList())[j];
      parent->addChild(-1,
                        FROM_UTF8(obj->getObjectName()),
                        obj->CCopasiParameter::getKey());
    }
}

//*****************************************************************

const IndexedNode * DataModelGUI::getRootNode() const
  {return mTree.getRoot();}

const IndexedNode * DataModelGUI::getNode(const int & id) const
  {return mTree.findNodeFromId(id);}
//  {return const_cast<IndexedTree *>(&mTree)->findNodeFromId(id);}

//*****************************************************************

bool DataModelGUI::createModel()
{
  if (!CCopasiDataModel::Global->newModel()) return false;

  mPlotDefinitionList.setPlotDefinitionList(CCopasiDataModel::Global->getPlotDefinitionList());

  linkDataModelToGUI();
  return true;
}

bool DataModelGUI::loadModel(const char* fileName)
{
  if (!CCopasiDataModel::Global->loadModel(fileName)) return false;

  // getModel()->setCompileFlag();
  mPlotDefinitionList.setPlotDefinitionList(CCopasiDataModel::Global->getPlotDefinitionList());

  linkDataModelToGUI();
  return true;
}

bool DataModelGUI::saveModel(const char* fileName)
{
  assert(mPlotDefinitionList.getPlotDefintionList() ==
         CCopasiDataModel::Global->getPlotDefinitionList());

  return CCopasiDataModel::Global->saveModel(fileName);
}

bool DataModelGUI::importSBML(const char* fileName)
{
  if (!CCopasiDataModel::Global->importSBML(fileName)) return false;

  mPlotDefinitionList.setPlotDefinitionList(CCopasiDataModel::Global->getPlotDefinitionList());

  linkDataModelToGUI();
  return true;
}

bool DataModelGUI::exportSBML(const char* fileName)
{
  assert(mPlotDefinitionList.getPlotDefintionList() ==
         CCopasiDataModel::Global->getPlotDefinitionList());

  return CCopasiDataModel::Global->exportSBML(fileName);
}

CPlotSpec2Vector & DataModelGUI::getPlotDefinitionList()
{return mPlotDefinitionList;}

//************** Math model ***********************************************

bool DataModelGUI::updateMathModel()
{
  if (mMathModelUpdateScheduled) mpMathModel->setModel(CCopasiDataModel::Global->getModel());

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
