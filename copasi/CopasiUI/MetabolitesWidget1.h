#ifndef METABOLITES_WIDGET1_H
#define METABOLITES_WIDGET1_H

#include <qsplitter.h>
#include <qvariant.h>
class QVBoxLayout; 
class QHBoxLayout; 
class QGridLayout; 
class QAction;
class QActionGroup;
class QToolBar;
class QPopupMenu;
class QGroupBox;
class QLabel;
class QLineEdit;
class QComboBox;
class QListBoxItem;
class QPushButton;
class QRadioButton;
class QFrame;
class CModel;
class MetabolitesWidget1 : public QWidget
{ 
    Q_OBJECT

protected:
	QPushButton* cancelChanges;
    QPushButton* commitChanges;
	CModel *mModel;
public:
    MetabolitesWidget1( QWidget *parent, const char * name=0, WFlags f=0 );
	void loadMetabolites(CModel *model);

    QGroupBox* GroupBox1;
    QGroupBox* GroupBox2;

	QRadioButton* RadioButton1;
    QRadioButton* RadioButton2;
	QRadioButton* RadioButton3;
    QRadioButton* RadioButton4;
	QRadioButton* RadioButton5;
   
    QLineEdit* LineEdit1;
    QLineEdit* LineEdit4;
    QLineEdit* LineEdit5;
	QLineEdit* LineEdit7;
    QLineEdit* LineEdit8;
    QLineEdit* LineEdit9;

    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QLabel* TextLabel4;
	QLabel* TextLabel5;
    QLabel* TextLabel7;
    QLabel* TextLabel8;
	QLabel* TextLabel9;
    
	QComboBox* ComboBox1;
	
	QFrame* Frame1;
	QFrame* Frame2;
	QFrame* Frame3;
	QFrame* Frame4a;
	QFrame* Frame4b;
	QFrame* Frame4c;
	QFrame* Frame4d;
	QFrame* Frame4e;
	QFrame* Frame4f;
	QFrame* Frame4g;
	QFrame* Frame4h;
	QFrame* Frame4i;
};

#endif // MetabolitesWidget
