#ifndef REACTIONS_WIDGET_H
#define REACTIONS_WIDGET_H

#include <qtable.h>
#include <qpushbutton.h> 

class MyTreeAndListWidget;
class ReactionsWidget : public QWidget
{
protected:
	QTable *table;
	QPushButton *btnOK;
	QPushButton *btnCancel;
	

public:
	ReactionsWidget(QWidget *parent, const char * name=0, WFlags f=0);

};

#endif