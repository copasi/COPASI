/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DataModel.cpp,v $
   $Revision: 1.28 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/10 12:58:48 $
   End CVS Header */

#include "DataModel.h"
#include "DataModel.txt.h"
#include "function/CFunctionDB.h"
#include "mathmodel/CMathModel.h"
#include "plot/COutputHandlerPlot.h"
#include "qtUtilities.h"

DataModel::DataModel()
{
  this->populateData();
  model = NULL;
  mpMathModel = NULL;
  mMathModelUpdateScheduled = false;
  trajectorytask = NULL;
  steadystatetask = NULL;
  scantask = NULL;
  reportdefinitions = NULL;
  plotspecs = NULL;
  pOptFunction = NULL;
}

Folder* DataModel::searchFolderList(int id)
{
  for (Folder* f = folderList.first(); f; f = folderList.next())
    if (f->getID() == id)
      return f;

  return NULL;
}

Node<Folder> * DataModel::addData(Folder* parent, Folder* child)
{
  myTree.addSibling(child, parent);
  folderList.append(child);
  return /*last = */ myTree.search(child, myTree.getRoot());    //propably needs to return
}

void DataModel::removeData(Folder* i)
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

void DataModel::removeAllChildren(Folder* f)
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

void DataModel::createModel(const char* fileName)
{
  pdelete(model);
  model = new CModel();
  Copasi->pModel = model;
  searchFolderList(1)->setObjectKey(model->getKey());

  pdelete(mpMathModel);
  mpMathModel = new CMathModel();
  mpMathModel->setModel(model);

  pdelete(steadystatetask);
  steadystatetask = new CSteadyStateTask();
  steadystatetask->getProblem()->setModel(model);
  searchFolderList(21)->setObjectKey(steadystatetask->getKey());

  pdelete(trajectorytask);
  trajectorytask = new CTrajectoryTask();
  trajectorytask->getProblem()->setModel(model);
  COutputHandlerPlot* tmpHandler = new COutputHandlerPlot();
  trajectorytask->setOutputHandler(tmpHandler);
  searchFolderList(23)->setObjectKey(trajectorytask->getKey());  //23=Time course

  pdelete(scantask);
  scantask = new CScanTask();
  scantask->getProblem()->setModel(model);
  searchFolderList(32)->setObjectKey(scantask->getKey());

  pdelete(reportdefinitions);
  reportdefinitions = new CReportDefinitionVector();
  searchFolderList(43)->setObjectKey(reportdefinitions->getKey());

  pdelete(plotspecs);
  plotspecs = new CPlotSpecVector();
  searchFolderList(42)->setObjectKey(plotspecs->getKey());

  tmpHandler->setPlotSpecVectorAddress(plotspecs);

  pdelete(pOptFunction);
  pOptFunction = new COptFunction();
  searchFolderList(31)->setObjectKey(pOptFunction->getKey());

  saveModel(fileName);
}

void DataModel::loadModel(const char* fileName)
{
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
      searchFolderList(1)->setObjectKey(model->getKey());

      pdelete(steadystatetask);
      steadystatetask = new CSteadyStateTask();
      steadystatetask->load(inbuf);
      searchFolderList(21)->setObjectKey(steadystatetask->getKey());

      pdelete(trajectorytask);
      trajectorytask = new CTrajectoryTask();
      trajectorytask->load(inbuf);
      COutputHandlerPlot* tmpHandler = new COutputHandlerPlot();
      trajectorytask->setOutputHandler(tmpHandler);
      searchFolderList(23)->setObjectKey(trajectorytask->getKey()); //23=Time course

      pdelete(scantask);
      scantask = new CScanTask();
      scantask->getProblem()->setModel(model);
      // future work  scantask->load(inbuf);
      searchFolderList(32)->setObjectKey(scantask->getKey());

      pdelete(reportdefinitions);
      reportdefinitions = new CReportDefinitionVector();
      //  reportdefinitions->load(inbuf);
      searchFolderList(43)->setObjectKey(reportdefinitions->getKey());

      pdelete(plotspecs);
      plotspecs = new CPlotSpecVector();
      //  plotspecs->load(inbuf);
      searchFolderList(42)->setObjectKey(plotspecs->getKey());

      tmpHandler->setPlotSpecVectorAddress(plotspecs);

      pdelete(pOptFunction);
      pOptFunction = new COptFunction();
      searchFolderList(31)->setObjectKey(pOptFunction->getKey());

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

      CPlotSpecVector * pNewPlotSpecs = new CPlotSpecVector();
      //TODO XML.setPlotList(*pNewPlotSpecs);

      XML.load(File);

      pdelete(model);
      model = XML.getModel();
      model->compile();
      searchFolderList(1)->setObjectKey(model->getKey());

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
      searchFolderList(21)->setObjectKey(steadystatetask->getKey());

      if (!trajectorytask) trajectorytask = new CTrajectoryTask();
      trajectorytask->getProblem()->setModel(model);
      COutputHandlerPlot* tmpHandler = new COutputHandlerPlot();
      trajectorytask->setOutputHandler(tmpHandler);
      searchFolderList(23)->setObjectKey(trajectorytask->getKey()); //23=Time course

      if (!scantask) scantask = new CScanTask();
      scantask->getProblem()->setModel(model);
      searchFolderList(32)->setObjectKey(scantask->getKey());

      pdelete(reportdefinitions);
      reportdefinitions = pNewReports;
      searchFolderList(43)->setObjectKey(reportdefinitions->getKey());

      pdelete(plotspecs);
      plotspecs = pNewPlotSpecs;
      searchFolderList(42)->setObjectKey(plotspecs->getKey());

      tmpHandler->setPlotSpecVectorAddress(plotspecs);
    }

  pdelete(mpMathModel);
  mpMathModel = new CMathModel();
  mpMathModel->setModel(model);

  //  steadystatetask->compile();
}

void DataModel::saveModel(const char* fileName)
{
  if (fileName == NULL) return;

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

void DataModel::populateData()
{
  QString str = QString("Folder ");
  Folder *f = new Folder(0, str);
  f->setID(0, true);
  myTree.addRoot(f);
  folderList.append(f);

  // const int MAX = 80;
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

bool DataModel::updateMathModel()
{
  if (mMathModelUpdateScheduled) mpMathModel->setModel(model);

  mMathModelUpdateScheduled = false;
  return true;
}

bool DataModel::scheduleMathModelUpdate(const bool & update)
{
  mMathModelUpdateScheduled = update;
  return true;
}
