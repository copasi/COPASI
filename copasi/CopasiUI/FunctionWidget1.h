/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/FunctionWidget1.h,v $
   $Revision: 1.38 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/12/22 12:31:32 $
   End CVS Header */

/****************************************************************************
 **  $ CopasiUI/FunctionWidget1.h               
 **  $ Author  : Mrinmayee Kulkarni
 **  
 ** This is the header file for Function Widget1, i.e the Second  level 
 ** widget which shows detailed description of an individual function
 *****************************************************************************/
#ifndef FUNCTION_WIDGET1_H
#define FUNCTION_WIDGET1_H

#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QHButtonGroup;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QTable;
class QTextEdit;
class CFunction;
//class MyLineEdit;
class QtMmlWidget;

class CFunction;
class CFunctionParameters;
class CUsageRange;
template <class CType> class CCopasiVectorNS;

class FunctionWidget1 : public CopasiWidget
  {
    Q_OBJECT

  public:
    FunctionWidget1(QWidget *parent, const char * name = 0, WFlags f = 0);
    virtual ~FunctionWidget1();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

  protected slots:
    virtual void slotCancelButtonClicked();
    virtual void slotCommitButtonClicked();
    virtual void slotNewButtonClicked();
    virtual void slotDeleteButtonClicked();
    virtual void slotTableValueChanged(int row, int col);
    virtual void slotAppTableValueChanged(int row, int col);
    virtual void slotFcnDescriptionChanged();

  protected:
    bool loadFromFunction(const CFunction* = NULL);
    bool loadParameterTable(const CFunctionParameters & params);
    bool loadUsageTable(const CCopasiVectorNS<CUsageRange>& usages);
    bool loadReversibility(TriLogic rev);
    void updateParameters();
    void updateApplication();
    bool saveToFunction();
    bool copyFunctionContentsToFunction(const CFunction* src, CFunction* target);

    std::string objKey;
    bool flagRO;
    bool flagChanged;
    bool isValid;

    //Widgets
    QGridLayout* FunctionWidget1Layout;
    QHBoxLayout* Layout1;
    QHBoxLayout* Layout2;
    QLabel* TextLabel1;
    QLabel* TextLabel2;
    QTextEdit* textBrowser;

    QFrame* Line2;
    QPushButton* commitChanges;
    QPushButton* cancelChanges;
    QPushButton* newFcn;
    QPushButton* deleteFcn;
    QHButtonGroup* ButtonGroup1;
    QRadioButton* RadioButton1;
    QRadioButton* RadioButton2;
    QRadioButton* RadioButton3;
    QLabel* TextLabel4;
    QFrame* Line3;
    QLineEdit* LineEdit1;
    QTable* Table2;
    QLabel* TextLabel5;
    QFrame* Line4;
    QTable* Table1;
    QLabel* TextLabel3;
    QFrame* Line1;

    QtMmlWidget* mMmlWidget;
    QScrollView* mScrollView;

    CFunction * pFunction;
  };

#endif // FunctionWidget1
