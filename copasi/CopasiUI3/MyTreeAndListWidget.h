
#ifndef MY_TREE_AND_LIST_WIDGET_H
#define MY_TREE_AND_LIST_WIDGET_H

#include <qsplitter.h>
#include <qlistview.h>
#include <qmultilineedit.h>
#include <qheader.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qlineedit.h>

class MyListView;
class MyTreeAndListWidget : public QSplitter
{
	Q_OBJECT

public:
	MyTreeAndListWidget( QWidget *parent = 0, const char *name = 0 );
	//~MyTreeAndListWidget()

protected:
	QListViewItem* initializeTree();
	
	MyListView *ListView1;
	QMultiLineEdit *bigWidget;
	QLineEdit *bigWidget2;

protected slots:
    virtual void slotTreeSelectionChanged(QListViewItem*);


};

class MyListView : public QListView
{
public:
	MyListView(QWidget * parent, const char * name);
	void setOpen(QListViewItem * item, bool open );

};

#endif
