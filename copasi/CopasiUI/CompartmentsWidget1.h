/****************************************************************************
 **  $ CopasiUI/CompartmentsWidget1.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Compartments Widget1, i.e the second level 
 ** of Compartments.
 *****************************************************************************/
#ifndef COMPARTMENTSWIDGET1_H
#define COMPARTMENTSWIDGET1_H

#include <qvariant.h>
#include <qwidget.h>
class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QLabel;
class QLineEdit;
class QListBox;
class QListBoxItem;
class QPushButton;
class CModel;

class CompartmentsWidget1 : public QWidget
  {
    Q_OBJECT

  public:
    CompartmentsWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~CompartmentsWidget1();
    CModel *mModel;
    void loadCompartments(CModel *model);
    void loadName(QString setValue);
    int isName(QString setValue);
    QString *Compartment1_Name;
    QString name;

    QLineEdit* LineEdit4;
    QLineEdit* LineEdit1;
    QLabel* TextLabel2;
    QLabel* TextLabel2_2;
    QLabel* TextLabel1;
    QFrame* Line4;
    QFrame* Line4_2;
    QListBox* ListBox1;
    QLabel* TextLabel3;
    QLineEdit* LineEdit3;
    QPushButton* commitChanges;
    QPushButton* cancelChanges;
    QFrame* Line4_3;

  public slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();
    virtual void slotListBoxCurrentChanged(const QString &);

  signals:
    void name_changed(const QString &);
    void signal_emitted(const QString &);
    void leaf(CModel*);
    void updated();

  protected:
    QGridLayout* CompartmentsWidget1Layout;
    QHBoxLayout* Layout5;
  };

#endif // COMPARTMENTSWIDGET1_H
