/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DataModelGUI.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/02 13:47:31 $
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
#include "plot/CPlotSpecVector.h"
#include "optimization/COptFunction.h"

int Folder::mModifier = 0;

DataModelGUI::DataModelGUI()
    : DataModel()
{
  this->populateData();
  mpMathModel = NULL;
  mMathModelUpdateScheduled = false;
}

Folder* DataModelGUI::searchFolderList(int id)
{
  for (Folder* f = folderList.first(); f; f = folderList.next())
    if (f->getID() == id)
      return f;

  return NULL;
}

Node<Folder> * DataModelGUI::addData(Folder* parent, Folder* child)
{
  myTree.addSibling(child, parent);
  folderList.append(child);
  return /*last = */ myTree.search(child, myTree.getRoot());    //propably needs to return
}

void DataModelGUI::removeData(Folder* i)
{
  Node<Folder>* node = myTree.search(i, myTree.getRoot());

  if (node)
    {
      //last = node;
      //notify(DELETE);

      myTree.deleteNode(i);
      folderList.remove(i);
    }

  //last = NULL;
}

void DataModelGUI::removeAllChildren(Folder* f)
{
  Node<Folder>* node = myTree.search(f, myTree.getRoot());
  Folder* fff;

  if (!node->child) return;

  while (node->child)
    {
      fff = node->child->info;
      removeData(node->child->info);
      delete fff;
    }
}

//************************************************************

void DataModelGUI::linkDataModelToGUI()
{
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
  searchFolderList(1)->setObjectKey(model->getKey());
  searchFolderList(21)->setObjectKey(steadystatetask->getKey());
  searchFolderList(23)->setObjectKey(trajectorytask->getKey());
  searchFolderList(32)->setObjectKey(scantask->getKey());
  searchFolderList(43)->setObjectKey(reportdefinitions->getKey());
  searchFolderList(42)->setObjectKey(plotspecs->getKey());
  searchFolderList(31)->setObjectKey(pOptFunction->getKey());
}

void DataModelGUI::createModel()
{
  DataModel::createModel();
  linkDataModelToGUI();
}

void DataModelGUI::loadModel(const char* fileName)
{
  DataModel::loadModel(fileName);

  model->setCompileFlag();
  linkDataModelToGUI();
}

void DataModelGUI::saveModel(const char* fileName)
{
  DataModel::saveModel(fileName);
}

void DataModelGUI::importSBML(const char* fileName)
{
  DataModel::importSBML(fileName);
}

void DataModelGUI::exportSBML(const char* fileName)
{
  DataModelGUI::exportSBML(fileName);
  linkDataModelToGUI();
}

void DataModelGUI::populateData()
{
  QString str = QString("Folder ");
  Folder *f = new Folder(0, str);
  f->setID(0, true);
  myTree.addRoot(f);
  folderList.append(f);

  std::string str1;

  std::stringstream in;
  in.str(DataModeltxt);

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
      QString myStr = data.mid(second + 1, data.length() - second - 1);
      str = QString(myStr);

      Folder* parent = this->searchFolderList(parentId);

      Folder* f1;
      f1 = (parentId == 0) ? new Folder(0, str) : new Folder(parent, str);
      f1->setID(myId, true);

      myTree.addSibling(f1, parent);

      folderList.append(f1);
    }
}

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

void DataModelGUI::setQApp(QApplication* app)
{mpApp = app;}

QApplication* DataModelGUI::getQApp() const
  {return mpApp;}
