/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/ReactionsWidget1.h,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: chlee $ 
   $Date: 2004/05/25 19:39:04 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/ReactionsWidget1.h               
 **  $ Author  : Mudita Singhal
 **  
 ** This is the header file for the Reactions Widget, i.e the second level 
 ** of Reactions.
 **
 *****************************************************************************/

#ifndef REACTIONS_WIDGET1_H
#define REACTIONS_WIDGET1_H

#include "copasiWidget.h"
#include "CReactionInterface.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QCheckBox;
class QComboBox;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class ParameterTable;
class MyLineEdit;

class ReactionsWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    ReactionsWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ReactionsWidget1();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();
    virtual void slotBtnNewClicked();
    virtual void slotBtnDeleteClicked();
    virtual void slotCheckBoxClicked();
    virtual void slotComboBoxSelectionChanged(const QString &);
    virtual void slotLineEditChanged();

    //  public slots:
    virtual void slotTableChanged(int index, int sub, QString newValue);

  protected:
    bool loadFromReaction(const CReaction* reaction);
    bool saveToReaction();
    void FillWidgetFromRI();

    std::string objKey;
    CReactionInterface mRi;

    QGridLayout* ReactionsWidget1Layout;
    QHBoxLayout* Layout1;
    QLabel* TextLabel4;
    QLabel* TextLabel7;
    QPushButton* commitChanges;
    QPushButton* cancelChanges;
    QPushButton* newReaction;
    QPushButton* deleteReaction;
    QLabel* TextLabel8;
    QFrame* Line2;
    QFrame* Line1;
    QFrame* Line3;
    QLabel* TextLabel6;
    QLineEdit* LineEdit1;
    MyLineEdit* LineEdit2;
    QComboBox* ComboBox1;
    QFrame* Line4;
    ParameterTable* table;
    QLineEdit* LineEdit3;
    QLabel* TextLabel5;
    QPushButton* newKinetics;
    QCheckBox* CheckBox;

    //QString name;
  };

#endif // REACTIONSWIDGET1_H
