#ifndef MY_TREE_AND_LIST_WIDGET_H
#define MY_TREE_AND_LIST_WIDGET_H

#include <qsplitter.h>
#include <qlistview.h>
#include <qmultilineedit.h>
#include <qheader.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qlineedit.h>

#include "copasi.h"
#include "model/model.h"

#include "MetabolitesWidget.h"
#include "ReactionsWidget.h"


class MyTreeAndListWidget : public QSplitter
{
	Q_OBJECT

public:
	MyTreeAndListWidget( QWidget *parent = 0, const char *name = 0 );
	//~MyTreeAndListWidget()
	CModel* getModel()
	{
		return mModel;
	}
	void loadNodes(CModel *model);
protected:
	CModel *mModel;
	QListView *ListView1;
	QMultiLineEdit *bigWidget;
	MetabolitesWidget *metabolitesWidget;
	ReactionsWidget *reactionsWidget;

	void ConstructNodeWidgets();
	QListViewItem* initializeTree();
	void changingFromReactions();

protected slots:
    virtual void slotTreeSelectionChanged(QListViewItem*);


};
#endif

