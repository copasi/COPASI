#ifndef METABOLITES_WIDGET_H
#define METABOLITES_WIDGET_H

#include <qtable.h>

class MyTreeAndListWidget;
class MetabolitesWidget : public QWidget
{
protected:
	MyTreeAndListWidget *myParent;
	QTable *table;
	

public:
	MetabolitesWidget(QWidget *parent, const char * name=0, WFlags f=0);

};

#endif