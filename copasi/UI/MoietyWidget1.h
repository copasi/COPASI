#ifndef MOIETY_WIDGET1_H
#define MOIETY_WIDGET1_H

#include <qsplitter.h>
#include <qvariant.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QLabel;
class QLineEdit;
class QListBoxItem;
class QPushButton;
class QFrame;
class CModel;
class MoietyWidget1 : public QWidget
{ 
    Q_OBJECT

protected:
	QPushButton* cancelChanges;
    QPushButton* commitChanges;
	CModel *mModel;
public:
    MoietyWidget1( QWidget *parent, const char * name=0, WFlags f=0 );
	void loadMoieties(CModel *model);
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel3;
    QLineEdit* LineEdit1;
    QLineEdit* LineEdit2;
    QLineEdit* LineEdit3;
 	QFrame* Frame1;
	QFrame* Frame2;
	QFrame* Frame3;
	QFrame* Frame4a;
	QFrame* Frame4b;
	QFrame* Frame4c;
	QFrame* Frame4d;

};

#endif 
