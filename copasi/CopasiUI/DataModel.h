/****************************************************************************
 **  $ CopasiUI/DataModel.h                 Modified on : 28th March, 2002
 **  $ Author  : Ankur Gupta
 *****************************************************************************/
#ifndef DATAMODEL_H

#define DATAMODEL_H

#define ADD 1
#define DELETE 2
#define MODEL 3
#define STEADYSTATETASK 4
#define TRAJECTORYTASK 5

#include <qptrlist.h>
#include <fstream>
#include "Tree.h"
#include "listviews.h"
#include "Subject.h"

class CTrajectoryTask;
class CSteadyStateTask;
class CModel;
class CReadConfig;
class CWriteConfig;
class Folder;

template <class T> class DataModel: public Subject
  {
  private:
    Tree<T> myTree; // create the  object of the tree
    Node<T>* last; // to keep track of the last change done...
    QPtrList<T> folderList;  // to keep track of the number of the object in the tree...
    bool modelUpdate;
    bool steadystatetaskUpdate;
    bool trajectorytaskUpdate;
    CModel* model;

  protected:
    T* searchFolderList(int id);

  public:
    CSteadyStateTask* steadystatetask;
    CTrajectoryTask* trajectorytask;
    //DataModel();
    DataModel(char* fileName = "DataModel.txt");

    void populateData(char* fileName);

    // void setData(int);
    //  void addData(T*);
    void addData(T* parent, T* child);
    void removeData(T*);

    void loadModel(const char* fileName);
    void createModel(const char* fileName);
    void saveModel(const char* fileName);
    inline CModel* getModel(){return model;}
    inline CSteadyStateTask* getSteadyStateTask(){return steadystatetask;}
    inline CTrajectoryTask* getTrajectoryTask() {return trajectorytask;}

    inline void setModelUpdate(bool value){modelUpdate = value;}
    inline bool getModelUpdate(){return modelUpdate;}

    inline void setSteadyStateTaskUpdate(bool value){steadystatetaskUpdate = value;}
    inline bool getSteadyStateTaskUpdate() {return steadystatetaskUpdate;}

    inline void setTrajectoryTaskUpdate(bool value) {trajectorytaskUpdate = value;}
    inline bool getTrajectoryTaskUpdate() {return trajectorytaskUpdate;}

    // inline int getStatus(){return STATUS;}
    inline Node<T>* getRoot(){return myTree.getRoot();}
    inline Node<T>* getData(){return last;}
  };

template <class T>
DataModel<T>::DataModel(char* fileName)
{
  this->populateData(fileName);
  // this->STATUS=0;
  last = NULL;
  model = NULL;
  trajectorytask = NULL;
  steadystatetask = NULL;
  modelUpdate = false;
  steadystatetaskUpdate = false;
  trajectorytaskUpdate = false;
}

template <class T>
T* DataModel<T>::searchFolderList(int id)
{
  for (T* f = folderList.first(); f; f = folderList.next())
    if (f->getID() == id)
      return f;

  return NULL;
}

/*
 
template<class T>
void DataModel<T>::addData(T* i)
{
 
   if(this->searchFolderList(215) == NULL)
      {
    QString str = QString("I am Added--->1");
    T *f021 = new T(i,str);
    f021->setID(215);
    myTree.addSibling(f021,i);
    folderList.append(f021);
   }
 
      if(this->searchFolderList(216) == NULL){
    QString str = QString("I am Added --->2");
    T *f0212 = new T(i,str);
    f0212->setID(216);
    myTree.addSibling(f0212,i);
    folderList.append(f0212);
   }
 
      last=myTree.search(i,myTree.getRoot());
}
 */

template <class T>
void DataModel<T>::addData(T* parent, T* child)
{
  myTree.addSibling(child, parent);
  folderList.append(child);
  last = myTree.search(child, myTree.getRoot());
  notify(ADD);
}

template <class T>
void DataModel<T>::removeData(T* i)
{
  Node<T>* node = myTree.search(i, myTree.getRoot());

  if (node)
    {
      last = node;
      notify(DELETE);

      myTree.deleteNode(i);
      folderList.remove(i);
    }

  last = NULL;
}

/*
template<class T>
void DataModel<T>::setData(int status)
{
// STATUS=status;
// notify(); // call the notify method...to notify the changes...
}*/

template <class T>
void DataModel<T>::createModel(const char* fileName)
{
  pdelete(trajectorytask);
  pdelete(model);
  pdelete(steadystatetask);

  trajectorytask = NULL;
  model = NULL;
  steadystatetask = NULL;

  model = new CModel();
  modelUpdate = true;
  notify(MODEL);

  steadystatetask = new CSteadyStateTask();
  steadystatetask->getProblem()->setModel(model);
  steadystatetaskUpdate = true;
  notify(STEADYSTATETASK);

  trajectorytask = new CTrajectoryTask();
  trajectorytask->getProblem()->setModel(model);
  trajectorytaskUpdate = true;
  notify(TRAJECTORYTASK);

  saveModel(fileName);
}

template <class T>
void DataModel<T>::loadModel(const char* fileName)
{
  pdelete(model);
  CReadConfig inbuf(fileName);
  model = new CModel();
  model->load(inbuf);
  model->compile();
  modelUpdate = true;
  notify(MODEL);

  pdelete(steadystatetask);
  steadystatetask = new CSteadyStateTask();
  steadystatetask->load(inbuf);
  steadystatetaskUpdate = true;
  notify(STEADYSTATETASK);

  pdelete(trajectorytask);
  trajectorytask = new CTrajectoryTask();
  trajectorytask->load(inbuf);
  trajectorytaskUpdate = true;
  notify(TRAJECTORYTASK);

  Copasi->pOutputList->load(inbuf);

  //  steadystatetask->compile();
}

template <class T>
void DataModel<T>::saveModel(const char* fileName)
{
  if (fileName == NULL) return;

  CWriteConfig outbuf(fileName);

  if (model != NULL)
    model->save(outbuf);

  if (steadystatetask != NULL)
    steadystatetask->save(outbuf);

  if (trajectorytask != NULL)
    trajectorytask->save(outbuf);

  Copasi->pOutputList->save(outbuf);
}

/*void DataModel<T>::saveModel(const char* fileName)
{
    pdelete(model);
 CReadConfig inbuf(fileName);
 model=new CModel();
 model->load(inbuf);
 model->compile();
 modelUpdate=true;
 notify(MODEL);
 
}
 */

template <class T>
void DataModel<T>::populateData(char* fileName)
{
  QString str = QString("Folder ");
  Folder *f = new Folder(0, str);
  f->setID(0, true);
  myTree.addRoot(f);
  folderList.append(f);

  const int MAX = 80;
  char str1[MAX];

  std::ifstream in(fileName);

  while (!in.eof())
    {
      in.getline(str1, MAX);
      QString data(str1);

      if (str1 == "")
        break;

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

  in.close();
}

#endif
