#ifndef REACTIONS_WIDGET_H
#define REACTIONS_WIDGET_H

#include <qtable.h>
#include <qpushbutton.h> 
#include "MyTable.h"

class CModel;
class ReactionsWidget : public QWidget
{
	Q_OBJECT
protected:
	CModel *mModel;
	MyTable *table;
	QPushButton *btnOK;
	QPushButton *btnCancel;
	

public:
	ReactionsWidget(QWidget *parent, const char * name=0, WFlags f=0);
	void loadReactions(CModel *model);
	void mousePressEvent( QMouseEvent * e );
	void resizeEvent( QResizeEvent * re);

protected slots:
    virtual void slotTableClicked( int row, int col, int button, const QPoint & mousePos );
	virtual void slotTableCurrentChanged( int row, int col );
	virtual void slotTableSelectionChanged();
	virtual void slotBtnOKClicked();
	virtual void slotBtnCancelClicked();
	


};

#endif
