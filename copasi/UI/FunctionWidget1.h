/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/FunctionWidget1.h,v $
   $Revision: 1.36 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/09/20 07:33:56 $
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
class QButtonGroup;
class QFrame;
class QLabel;
class QLineEdit;
class QPushButton;
class QRadioButton;
class QTable;
class QTextEdit;
class CFunction;
//class MyLineEdit;

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
    QButtonGroup* ButtonGroup1;
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

    //void loadName(QString setValue);
    //int isName(QString setValue);

    //QString mName;

    //QString *Function_Name;
    //QString *new_Name;
    //QString *new_Description;
    //QString param_Type;
    //QString param_Name;
    //QString param_Usage;
    //QString app_Desc;
    //QString app_Low;
    //QString app_High;
    //int int_Low;
    //int int_High;

    CFunction * pFunction;
  };

#endif // FunctionWidget1
