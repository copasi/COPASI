
#ifndef MY_CHECK_LIST_ITEM_H
#define MY_CHECK_LIST_ITEM_H

#include <qlistview.h>

class MyCheckListItem:public QCheckListItem
{

public:
	MyCheckListItem ( QCheckListItem * parent, const QString & text, Type tt = Controller ); 
	MyCheckListItem ( QListViewItem * parent, const QString & text, Type tt = Controller ); 
	MyCheckListItem ( QListView * parent, const QString & text, Type tt = Controller ); 

	void stateChange(bool checked);
};

#endif
