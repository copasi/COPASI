/****************************************************************************
 **  $ CopasiUI/listviews.h                Modified on : 8th March, 2002
 **  $ Author  : Ankur Gupta
 *****************************************************************************/
#ifndef LISTVIEWS_H
#define LISTVIEWS_H

#include <qsplitter.h>
#include <qstring.h>
#include <qobject.h>
#include <qptrlist.h>
#include <qlistview.h>
#include <vector>
#include <qvaluelist.h>
#include <qobjectlist.h>
#include <qheader.h>
#include <qmessagebox.h>
#include <qmultilineedit.h>

#include "copasi.h"
#include "DataModel.h"
#include "Observer.h"
#include "Tree.h"

//public QLineEdit:
// #include "model/model.h"

class CSteadyStateTask;
class CTrajectoryTask;
class CompartmentSymbols;
class CompartmentsWidget1;
class CompartmentsWidget;
class ConstantSymbols;
class FixedMetaboliteSymbols;
class FunctionSymbols;
class FunctionWidget1;
class FunctionWidget;
class CMathModel;
class MetaboliteSymbols;
class MetabolitesWidget1;
class MetabolitesWidget;
class ModesWidget;
class MoietyWidget1;
class MoietyWidget;
class ReactionsWidget1;
class ReactionsWidget;
class SteadyStateWidget;
class TrajectoryWidget;

class Folder : public QObject
  {
    Q_OBJECT

  public:
    ~Folder(){}

    inline Folder(Folder *parent, const QString &name)
        : QObject(parent, name), fName(name){}
    // inline void setCaption(const QString &name){fCaption(name);}
    // inline QString getCaption(){return fCaption;}
    inline int getID(){return id;}
    inline void setID(int id, bool fixed = false)
    {
      mKey = QString::number(id) + "_" + fName;

      if (fixed)
        this->id = id;
      else
        this->id = id * 1000000 + getModifier();
    }
  inline const QString & getKey() const {return mKey;}
    inline QString folderName() {return fName;}

    inline const int & getModifier()
    {
      mModifier++;
      mModifier %= 1000000;
      return mModifier;
    }

    inline int operator==(Folder &folder)
    {
      return this->getID() == folder.getID() ? 1 : 0;
    } // for the comparing the stuff

    // inline friend ostream& operator<< (ostream& s,Folder& f)
    // {
    //  s<<"I am :-"<<f.getID()<<endl;
    //  return s;
    //}

  protected:
    // QString fCaption;
    QString fName;
    int id;
    QString mKey;
    static int mModifier;
  };

class FolderListItem : public QListViewItem
  {
  public:
    FolderListItem(QListView *parent, Folder *f);
    FolderListItem(FolderListItem *parent, Folder *f);
    void insertSubFolders(const QObjectList *lst);
    Folder *folder() {return myFolder;}
    QString key(int, bool) const {return myFolder->getKey();}

  protected:
    Folder *myFolder;
  };

class ListViews : public QSplitter, public Observer
  {
    Q_OBJECT

  public:
    ListViews(QWidget *parent = 0, const char *name = 0);
    ~ListViews(){dataModel->detach(this);}

    void setDataModel(DataModel<Folder>* dm);
    void update(Subject*, int status); //overides..the update method...

  public slots:

    virtual void slotFunctionTableChanged(const QString &);
    virtual void slotCompartmentTableChanged(const QString &);
    virtual void slotMetaboliteTableChanged(const QString &);
    virtual void slotMoietyTableChanged(const QString &);
    virtual void slotReactionTableChanged(const QString &);
    virtual void slotNewReaction();
  protected:
    CModel *mModel;  // the re to the model...
    CMathModel *mpMathModel;
    CSteadyStateTask *mSteadyStateTask;
    CTrajectoryTask *mTrajectoryTask;
    void loadModelNodes(CModel *model);
    void loadSteadyStateTaskNodes(CSteadyStateTask*);
    void loadTrajectoryTaskNodes(CTrajectoryTask* p_trajectorytask);
    void ConstructNodeWidgets();

    void clearItem(QListViewItem *);
    void clearParentItem(QListViewItem *); // for the top level items to be cleared..

    void initFolders();

    void setupFolders();

    QListViewItem* searchNode(Folder*);
    QListViewItem* searchNode(int); // search by folder id
    QListViewItem* searchNode(const char*); // searfch by folder name
    int searchNode(QListViewItem* me);

    // the variables used in the code...
    QPtrList<Folder> lstFolders; // to keep the track of the folder items...for creation of the tree...
    QListView *folders;
    QMultiLineEdit *bigWidget;

    SteadyStateWidget *steadystateWidget;
    TrajectoryWidget *trajectoryWidget;
    MetabolitesWidget *metabolitesWidget;
    ReactionsWidget *reactionsWidget;
    CompartmentsWidget *compartmentsWidget;
    CompartmentSymbols *compartmentSymbols;
    MoietyWidget *moietyWidget;
    FunctionWidget *functionWidget;
    FunctionSymbols *functionSymbols;
    ReactionsWidget1 *reactionsWidget1;
    MetabolitesWidget1 *metabolitesWidget1;
    MetaboliteSymbols *metaboliteSymbols;
    FixedMetaboliteSymbols *fixedMetaboliteSymbols;
    CompartmentsWidget1 *compartmentsWidget1;
    ConstantSymbols *constantSymbols;
    MoietyWidget1 *moietyWidget1;
    FunctionWidget1 *functionWidget1;
    ModesWidget *modesWidget;

  protected slots:
    void slotFolderChanged(QListViewItem*);

  private:
    DataModel<Folder>* dataModel; // this the datamodel that has to be used..in the code..
    QListViewItem* lastSelection;
    QWidget* currentWidget;
    QWidget* lastWidget;

    void deleteAllMyChildrens(QListViewItem* me);
    void addItem(QListViewItem* parent, Folder* child);
    void addItem(QListView* parent, Folder* child);
    void loadMetabolites(QListViewItem*);
    void loadReactions(QListViewItem*);
    void loadMoieties(QListViewItem*);
    void loadCompartments(QListViewItem*);
    void loadFunction();
    void loadModes(QListViewItem*);
    void showMessage(QString caption, QString text);
  };

#endif
