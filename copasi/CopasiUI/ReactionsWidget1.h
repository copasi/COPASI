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
#include <qsplitter.h>
#include <qvariant.h>
#include <qlayout.h>
#include "qtable.h"
#include "MyTable.h"
#include "MyLineEdit.h"
#include "copasiWidget.h"
#include "CReactionInterface.h" 
//#include "parametertable.h"

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

class CModel;
class CReaction;

class ReactionsWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    ReactionsWidget1(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ReactionsWidget1();
    CModel *mpModel;
    CReactionInterface mRi;

    void loadName(QString setValue);
    int isName(QString setValue);
    void loadReactions(CModel *model);
    QString name;

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
    //CReaction *reactn1;

    //int num_substrates;
    //int num_products;
    //int numrows;
  protected slots:
    virtual void slotBtnCancelClicked();
    virtual void slotBtnOKClicked();
    virtual void slotBtnNewClicked();
    virtual void slotCheckBoxClicked();
    virtual void slotComboBoxSelectionChanged(const QString &);
    virtual void slotLineEditChanged();

  public slots:
    virtual void slotTableChanged(int index, int sub, QString newValue);

    void FillWidgetFromRI();

  signals:
    void signal_emitted(const QString &);
    void new_reaction();
    void leaf(CModel*);
    void updated();

  protected:
    QGridLayout* ReactionsWidget1Layout;
    QHBoxLayout* Layout1;
  };

#endif // REACTIONSWIDGET1_H
