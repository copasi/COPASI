/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DataModelGUI.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/02 13:47:31 $
   End CVS Header */

#ifndef DATAMODELGUI_H
#define DATAMODELGUI_H

#include <qptrlist.h>
#include <qobject.h>

#include "DataModel.h"

#include "Tree.h"

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

class DataModelGUI : public DataModel
  {
  private:
    Tree<Folder> myTree; // create the  object of the tree
    QPtrList<Folder> folderList;  // to keep track of the number of the object in the tree...

    CMathModel * mpMathModel;
    bool mMathModelUpdateScheduled;

    QApplication *mpApp;

    void linkDataModelToGUI();

  public:
    DataModelGUI();

    void populateData();
    Folder* searchFolderList(int id);

    Node<Folder> * addData(Folder* parent, Folder* child);
    void removeData(Folder*);
    void removeAllChildren(Folder* f);

    void loadModel(const char* fileName);
    void createModel();
    void saveModel(const char* fileName);

    void importSBML(const char* fileName);
    void exportSBML(const char* fileName);

    CMathModel * getMathModel() {return mpMathModel;}
    bool updateMathModel();
    bool scheduleMathModelUpdate(const bool & update = true);

    void setQApp(QApplication* app);
    QApplication* getQApp() const;

    Node<Folder>* getRoot(){return myTree.getRoot();}
  };

#endif
