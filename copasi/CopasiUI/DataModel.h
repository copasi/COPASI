/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DataModel.h,v $
   $Revision: 1.49 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/05/29 02:37:52 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/DataModel.h                 Modified on : 28th March, 2002
 **  $ Author  : Ankur Gupta
 *****************************************************************************/
#ifndef DATAMODEL_H

#define DATAMODEL_H

#include <qptrlist.h>
#include <qobject.h>
#include <fstream>

#include "copasi.h"

#include "Tree.h" 
//#include "listviews.h"
#include "xml/CCopasiXML.h"
#include "model/CModel.h"
#include "steadystate/CSteadyStateTask.h"
#include "steadystate/CSteadyStateProblem.h"
#include "trajectory/CTrajectoryTask.h"
#include "trajectory/CTrajectoryProblem.h"
#include "report/CReportDefinitionVector.h"
#include "scan/CScanTask.h"
#include "scan/CScanProblem.h"
#include "utilities/CGlobals.h" 
//#include "output/COutputList.h"             //TODO sort out the include dependencies
#include "optimization/COptFunction.h"
#include "plot/CPlotSpecVector.h"

class CReadConfig;
class CWriteConfig;
class CMathModel;

//**********************************************************************

class Folder : public QObject
  {
    Q_OBJECT

  public:
    ~Folder(){}

    Folder(Folder *parent, const QString &name)
        : QObject(parent, name),
        fName(name),
        mDisplayString(name),
        mObjectKey("")
    {}

    int getID(){return id;}

    void setID(int id, bool fixed = false)
    {
      mSortKey = QString::number(id) + "_" + fName;

      if (fixed)
        this->id = id;
      else
        this->id = id * 1000000 + getModifier();
    }

  const QString & getSortKey() const {return mSortKey;}

    const std::string & getObjectKey() const {return mObjectKey;}
    void setObjectKey(const std::string & key) {mObjectKey = key;}

    const QString & getDisplayString() const {return mDisplayString;}
    void setDisplayString(const QString & ds) {mDisplayString = ds;}

    QString folderName() {return fName;}

    const int & getModifier()
    {
      mModifier++;
      mModifier %= 1000000;
      return mModifier;
    }

    int operator==(Folder &folder)
    {
      return this->getID() == folder.getID() ? 1 : 0;
    } // for the comparing the stuff

    // inline friend ostream& operator<< (ostream& s,Folder& f)
    // {
    //  s<<"I am :-"<<f.getID()<<endl;
    //  return s;
    //}

  private:
    QString fName;
    QString mDisplayString;
    std::string mObjectKey; // from KeyFactory
    int id;
    QString mSortKey;

    static int mModifier;
  };

//******************************************************************************

class DataModel
  {
  private:
    Tree<Folder> myTree; // create the  object of the tree
    QPtrList<Folder> folderList;  // to keep track of the number of the object in the tree...

    CModel * model;
    CMathModel * mpMathModel;
    bool mMathModelUpdateScheduled;
    bool mChanged;

    CSteadyStateTask* steadystatetask;
    CTrajectoryTask* trajectorytask;
    CScanTask* scantask;
    CReportDefinitionVector* reportdefinitions;
    CPlotSpecVector* plotspecs;
    COptFunction* pOptFunction;

  public:
    DataModel();

    void populateData();
    Folder* searchFolderList(int id);

    Node<Folder> * addData(Folder* parent, Folder* child);
    void removeData(Folder*);
    void removeAllChildren(Folder* f);

    void loadModel(const char* fileName);
    void createModel();
    void saveModel(const char* fileName);

    CModel* getModel() {return model;}

    CMathModel * getMathModel() {return mpMathModel;}
    bool updateMathModel();
    bool scheduleMathModelUpdate(const bool & update = true);

    bool isChanged() const;
    void changed(const bool & changed = true);

    inline CSteadyStateTask* getSteadyStateTask() {return steadystatetask;}
    inline CTrajectoryTask* getTrajectoryTask() {return trajectorytask;}
    inline CReportDefinitionVector* getReportDefinitionVectorAddr(){return reportdefinitions;}
    inline CPlotSpecVector* getPlotSpecVectorAddr(){return plotspecs;}
    Node<Folder>* getRoot(){return myTree.getRoot();}
    //Node<Folder>* getData(){return last;}
  };

#endif
