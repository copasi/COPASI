/****************************************************************************
 ** Form interface generated from reading ui file '.\MetabolitesWidget1.ui'
 **
 ** Created: Mon Mar 3 22:02:20 2003
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#ifndef METABOLITESWIDGET1_H
#define METABOLITESWIDGET1_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QComboBox;
class QFrame;
class QGroupBox;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class CModel;

class MetabolitesWidget1 : public QWidget
  {
    Q_OBJECT

  public:
    MetabolitesWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~MetabolitesWidget1();
    CModel *mModel;
    void loadMetabolites(CModel *model);
    void loadName(QString setValue);
    int isName(QString setValue);
    QString *Metabolite1_Name;

    QLabel* TextLabel4;
    QLabel* TextLabel5;
    QLineEdit* LineEdit1;
    QComboBox* ComboBox1;
    QFrame* Line1_3;
    QLineEdit* LineEdit4;
    QLabel* TextLabel10;
    QPushButton* commitChanges;
    QPushButton* cancelChanges;
    QLabel* TextLabel8;
    QLabel* TextLabel11;
    QLineEdit* LineEdit7;
    QLineEdit* LineEdit9;
    QFrame* Line1_2;
    QLineEdit* LineEdit8;
    QFrame* Line1;
    QLabel* TextLabel12;
    QLabel* TextLabel7;
    QLineEdit* LineEdit5;
    QGroupBox* GroupBox3;
    QRadioButton* RadioButton3;
    QRadioButton* RadioButton4;
    QRadioButton* RadioButton5;
    QGroupBox* GroupBox2;
    QRadioButton* RadioButton1;
    QRadioButton* RadioButton2;

  protected:
    QGridLayout* MetabolitesWidget1Layout;
    QHBoxLayout* Layout7;
    QHBoxLayout* Layout12;
    QHBoxLayout* Layout13;

    int myValue;
    QString name;

  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();

  signals:
    void signal_emitted(QString &);

  private:
    void showMessage(QString caption, QString text);
  };

#endif // METABOLITESWIDGET1_H
