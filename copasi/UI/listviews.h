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
#include "DataModel.h"
#include "Observer.h"
#include "Tree.h"
#include "copasi.h"

//public QLineEdit:
// #include "model/model.h"
class CSteadyStateTask;

class SteadyStateWidget;

class MetabolitesWidget;

class ReactionsWidget;

class CompartmentsWidget;

class MoietyWidget;

class FunctionWidget;

class ReactionsWidget1;

class MetabolitesWidget1;

class CompartmentsWidget1;

class MoietyWidget1;

class FunctionWidget1;
class ModesWidget;

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
    inline void setID(int id)
    {
      this->id = id;
      mKey = QString::number(this->id) + fName;
    }
    inline const QString & getKey() const {return mKey;}
    inline QString folderName() {return fName;}

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

    virtual void slotFunctionTableChanged(QString &);
    virtual void slotCompartmentTableChanged(QString &);
    virtual void slotMetaboliteTableChanged(QString &);
    virtual void slotMoietyTableChanged(QString &);
    virtual void slotReactionTableChanged(QString &);
    virtual void slotNewReaction();
  protected:
    CModel *mModel;  // the re to the model...
    CSteadyStateTask *mSteadyStateTask;
    void loadNodes(CModel *model);
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
    MetabolitesWidget *metabolitesWidget;
    ReactionsWidget *reactionsWidget;
    CompartmentsWidget *compartmentsWidget;
    MoietyWidget *moietyWidget;
    FunctionWidget *functionWidget;
    ReactionsWidget1 *reactionsWidget1;
    MetabolitesWidget1 *metabolitesWidget1;
    CompartmentsWidget1 *compartmentsWidget1;
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
    void loadFunction(QListViewItem*);
    void loadModes(QListViewItem*);
    void showMessage(QString caption, QString text);
  };

#endif
