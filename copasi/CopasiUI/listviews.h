/****************************************************************************
**  $ CopasiUI/listviews.h                Modified on : 8th March, 2002
**  $ Author  : Ankur Gupta
**  
** 
**   
**
*****************************************************************************/
#ifndef LISTVIEWS_H
#define LISTVIEWS_H

#include <qsplitter.h>
#include <qstring.h>
#include <qobject.h>
#include <qptrlist.h>
#include <qlistview.h>
//#include <iostream.h>
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
#include "MetabolitesWidget.h"
//#include "ReactionsWidget.h"



#include "./icons/folderclosed.xpm"
#include "./icons/folderopen.xpm"
#include "./icons/folderlocked.xpm"
// -----------------------------------------------------------------
class Folder : public QObject
{
    Q_OBJECT

public:
    
    ~Folder(){}
  	inline Folder( Folder *parent, const QString &name )
                 : QObject( parent, name ), fName( name ){}

//	inline void setCaption(const QString &name){ fCaption(name);}
//	inline QString getCaption(){return fCaption;}

	inline int getID(){return id;}
	inline void setID(int id){this->id=id;}
	inline QString folderName() { return fName; }
	inline int operator==(Folder &folder){
			return this->getID()==folder.getID()?1:0;}// for the comparing the stuff
//	inline friend ostream& operator<< (ostream& s,Folder& f)
//	{
//	 s<<"I am :-"<<f.getID()<<endl;
//	 return s;
//	}

	
protected:
//	QString fCaption;
    QString fName;
	int id;

};

// -----------------------------------------------------------------

class FolderListItem : public QListViewItem
{
public:
    FolderListItem( QListView *parent, Folder *f );
    FolderListItem( FolderListItem *parent, Folder *f );
    void insertSubFolders( const QObjectList *lst );
    Folder *folder() { return myFolder; }
	

protected:
    Folder *myFolder;

};


// -----------------------------------------------------------------

class ListViews : public QSplitter,public Observer
{
    Q_OBJECT

public:
    ListViews( QWidget *parent = 0, const char *name = 0 );
    ~ListViews(){dataModel->detach(this);}
    void setDataModel(DataModel<Folder>* dm);
	void update(Subject*,int status);//overides..the update method...
	// for loading models...


protected:
	CModel *mModel;  // the re to the model...

	void loadNodes(CModel *model);
	void ConstructNodeWidgets();

    void clearItem(QListViewItem *);
//	void clearMyChildrenItem(QListViewItem * i);
	void clearParentItem(QListViewItem *);// for the top level items to be cleared..

    void initFolders();
//	void initFolders(Node<Folder>*);// default parameter....

    void setupFolders();
//	void setupFolders(QListView*);
//	void setupFolders(QListViewItem*);
	
	QListViewItem* searchNode(Folder*);
	QListViewItem* searchNode(int);// search by folder id
    QListViewItem* searchNode(char*);// searfch by folder name
	int searchNode(QListViewItem* me);
	
	// the variables used in the code...
	QPtrList<Folder> lstFolders;// to keep the track of the folder items...for creation of the tree...
    QListView *folders;
	QMultiLineEdit *bigWidget;
    // all the objects to be displayed...
	// all the new object widgets information goes here..
	// create the pointer to the new one here and use it in the code
    MetabolitesWidget *metabolitesWidget;


protected slots:
    void slotFolderChanged( QListViewItem*);

private:
	DataModel<Folder>* dataModel; // this the datamodel that has to be used..in the code..
	QListViewItem* lastSelection;
	QWidget* currentWidget;
	QWidget* lastWidget;

	void deleteAllMyChildrens(QListViewItem* me);
	void addItem(QListViewItem* parent,Folder* child);
	void addItem(QListView* parent,Folder* child);
	void loadMetabolites(QListViewItem*);
	void showMessage(QString caption,QString text);

	



};

#endif
