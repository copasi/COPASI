#include "MyCheckListItem.h"

MyCheckListItem::MyCheckListItem(QCheckListItem * parent, const QString & text, Type tt):
QCheckListItem (parent, text, tt) 
{

}

MyCheckListItem::MyCheckListItem(QListViewItem * parent, const QString & text, Type tt):
QCheckListItem (parent, text, tt) 
{

}

MyCheckListItem::MyCheckListItem(QListView * parent, const QString & text, Type tt):
QCheckListItem (parent, text, tt) 
{

}



void MyCheckListItem::stateChange(bool checked) 
{
	QCheckListItem::stateChange(checked); 
	
	QListViewItem* childItem = firstChild ();
	int noOfChildren = childCount();
	
	if(checked)
	{
		setOpen(TRUE);
		for(int i = 0; i < noOfChildren; i++)
		{
			childItem->setSelectable(TRUE);
			childItem = childItem->nextSibling();
			
		}
	}
	else
	{
		setOpen(FALSE);
		for(int i = 0; i < noOfChildren; i++)
		{
			childItem->setSelectable(FALSE);
			childItem = childItem->nextSibling();			
		}
	
	}
}

