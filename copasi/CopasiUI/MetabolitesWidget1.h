/****************************************************************************
 **  $ CopasiUI/MetaboliteWidget.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Metabolite Widget, i.e the second level 
 ** of Metabolites.
 *****************************************************************************/
#ifndef METABOLITESWIDGET1_H
#define METABOLITESWIDGET1_H

#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QButtonGroup;
class QComboBox;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;

class MetabolitesWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    MetabolitesWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~MetabolitesWidget1();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();

  protected:
    bool loadFromMetabolite(const CMetab*);
    bool saveToMetabolite();
    std::string objKey;

    //Widgets
    QGridLayout* MetabolitesWidget1Layout;
    QGridLayout* ButtonGroup2Layout;
    QGridLayout* ButtonGroup3Layout;
    QHBoxLayout* Layout7;
    QLabel* TextLabel4;
    QLabel* TextLabel5;
    QLineEdit* LineEdit1;
    QComboBox* ComboBox1;
    QFrame* Line1;
    QPushButton* commitChanges;
    QPushButton* cancelChanges;
    QFrame* Line1_3;
    QButtonGroup* ButtonGroup2;
    QRadioButton* RadioButton1;
    QRadioButton* RadioButton2;
    QButtonGroup* ButtonGroup3;
    QRadioButton* RadioButton4;
    QRadioButton* RadioButton5;
    QRadioButton* RadioButton3;
    QFrame* Line1_2;
    QLineEdit* LineEdit5;
    QLineEdit* LineEdit8;
    QLineEdit* LineEdit7;
    QLineEdit* LineEdit4;
    QLineEdit* LineEdit9;
    QLabel* TextLabel10;
    QLabel* TextLabel12;
    QLabel* TextLabel8;
    QLabel* TextLabel11;
    QLabel* TextLabel7;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
  };

#endif // METABOLITESWIDGET1_H
