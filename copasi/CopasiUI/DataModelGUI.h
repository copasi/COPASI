/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DataModelGUI.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/17 13:51:43 $
   End CVS Header */

#ifndef DATAMODELGUI_H
#define DATAMODELGUI_H

#include <qptrlist.h>
#include <qobject.h>

#include "DataModel.h"

#include "Tree.h"

class CMathModel;

//**********************************************************************

/*class Folder //: public QObject
  {
//    Q_OBJECT
 
  public:
    ~Folder(){}
 
    Folder(const QString &name, const std::string & key = "")
        : mName(name),
        mObjectKey(key)
    {
      //mSortKey = QString::number(id) + "_" + mName;
 
      if (fixed)
        mId = id;
      else
        mId = id * 1000000 + getModifier();
    }
 
    const QString & folderName() const {return mName;}
    
    //int getID() const {return mId;}
 
    //const QString & getSortKey() const {return mSortKey;}
 
    const std::string & getObjectKey() const {return mObjectKey;}
    void setObjectKey(const std::string & key) {mObjectKey = key;}
 
    //int operator==(Folder &folder)
    //  {return this->getID() == folder.getID() ? 1 : 0;} 
    
    // inline friend ostream& operator<< (ostream& s,Folder& f)
    // {
    //  s<<"I am :-"<<f.getID()<<endl;
    //  return s;
    //}
 
  private:
    QString mName;
    std::string mObjectKey; // from KeyFactory
    //int mId;
    //QString mSortKey;
 
    static int smModifier;
    
    static const int & getModifier()
    {
      smModifier++;
      smModifier %= 1000000;
      return smModifier;
    }
  };
 */ 
//******************************************************************************

class DataModelGUI : public DataModel
  {
  private:
    IndexedTree mTree; // create the  object of the tree

    CMathModel * mpMathModel;
    bool mMathModelUpdateScheduled;

    QApplication *mpApp;

    void linkDataModelToGUI();

  public:
    DataModelGUI();

    void populateData();

    void updateCompartments();
    void updateMetabolites();
    void updateReactions();
    void updateMoieties();
    void updateFunctions();
    void updateReportDefinitions();
    void updatePlots();

    const IndexedNode & getRootNode() const;

    //    Folder* searchFolderList(int id);
    //    Node* addData(Folder* parent, Folder* child);
    //    void removeData(Folder*);
    //    void removeAllChildren(Folder* f);
    //    Node* getRoot(){return mTree.getRoot();}

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
  };

#endif
