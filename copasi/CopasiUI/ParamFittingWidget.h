/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ParamFittingWidget.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: chlee $ 
   $Date: 2004/11/04 15:53:28 $
   End CVS Header */

/********************************************************
Author: chlee
Version : 1.xx  <first>
Description: 
Date: 09/19
Comment : ParameterFittingWidget for UI of the param fitting function
 *********************************************************/

#ifndef ParamFittingWidget_H
#define ParamFittingWidget_H

#include <vector>
#include <qvariant.h>
#include "copasiWidget.h"

class QButtonGroup;
class QCheckBox;
class QComboBox;
class QFrame;
class QGridLayout;
class QLabel;
class QLineEdit;
class QListBox;
//class OptimizationItemWidget;
class ParamFittingItemWidget;
class QPushButton;
class QRadioButton;
class ScanScrollView;
class QVBoxLayout;
class QHBoxLayout;
/*
class QTextEdit;
class COptFunction;
class ScanScrollView;
class OptimizationItemWidget;
class QListBoxItem;
class QCheckBox;*/
class SteadyStateWidget;
class TrajectoryWidget;
class CCopasiObject;

class ParamFittingWidget : public CopasiParametersWidget
  {
    Q_OBJECT

  public:
    ParamFittingWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ParamFittingWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    const std::string getKey();

    QLabel* dataFileLabel;
    QLineEdit* dataFileText;
    QPushButton* dataFormatButton;

    QLabel* optimizationMethodLabel;
    QComboBox* methodCombo;
    QPushButton* methodInfoButton;
    QPushButton* adjustParamButton;

    QLabel* sampleLabel1;
    QLabel* sampleLabel2;
    QLabel* sampleLabel3;
    QLabel* sampleLabel4;
    QLineEdit* methodParam1Text;
    QLineEdit* methodParam2Text;
    QLineEdit* methodParam3Text;
    QLineEdit* methodParam4Text;

    QFrame* divisionLine;
    QFrame* divisionLine1;
    QFrame* divisionLine2;
    QFrame* divisionLine3;
    QFrame* divisionLine4;
    QFrame* divisionLine5;

    //QButtonGroup* qbuttongroup;
    //QRadioButton* steadyStateRadio;
    //QRadioButton* timeCourseRadio;

    QCheckBox* steadyStateCheck;
    QPushButton* steadyStateEditButton;
    QCheckBox* timeCheck;
    QPushButton* timeEditButton;

    QLabel* globalCopasiItemsLabel;
    QPushButton* globalAddButton;
    QPushButton* globalDeleteButton;
    QPushButton* globalDownButton;
    QLabel* globalItemsLabel;
    QPushButton* globalUpButton;
    QListBox* globalItemnamesTable;
    ScanScrollView* globalItemsTable;
    std::vector<QWidget*> globalSelectedList;

    QLabel* localCopasiItemsLabel;
    QPushButton* localAddButton;
    QPushButton* localDeleteButton;
    QPushButton* localDownButton;
    QLabel* localItemsLabel;
    QPushButton* localUpButton;
    QListBox* localItemnamesTable;
    ScanScrollView* localItemsTable;
    std::vector<QWidget*> localSelectedList;

    QLabel* resultLabel;
    QLabel* sumOfSqLabel;
    QLabel* iterationsLabel;
    QLineEdit* iterationsText;
    QLineEdit* sumOfSqText;

    QPushButton* cancelButton;
    QPushButton* runButton;
    /*const std::string getKey();
    //manually added
    QLineEdit* expressionText;
    std::vector<QWidget*> selectedList;

    QPushButton* confirmButton;
    QPushButton* cancelButton;
    QFrame* bodyField_2;
    QCheckBox* steadystateCheck;
    QPushButton* steadystateEditButton;
    QCheckBox* timeCheck;
    QPushButton* timeEditButton;
    QFrame* bodyField_2_2;
    QLineEdit* expressionName;
    QComboBox* methodCombo;
    QLabel* optimizationLabel;
    QLabel* expressionEditlabel;
    QLabel* expressionNameLabel;*/

  protected:
    QGridLayout* globalCopasiItemsLayout;
    QGridLayout* localCopasiItemsLayout;
    QGridLayout* ParamFittingWidgetLayout;
    QGridLayout* resultLayout;
    QHBoxLayout* buttonLayout;
    QHBoxLayout* methodParamLabelsLayout;
    QHBoxLayout* methodParamTextboxLayout;
    QHBoxLayout* resultFieldLayout;
    QHBoxLayout* steadyStateOrTimeLayout;
    QVBoxLayout* radioButtonLayout;
    /*QGridLayout* ExpressionWidgetLayout;
    QHBoxLayout* layout14;
    QHBoxLayout* layout7;

    bool loadFromExpression(COptFunction*);
    bool bUpdated;*/

  protected slots:
    /*void addButtonClicked();
    void deleteButtonClicked();
    void upButtonClicked();
    void downButtonClicked();
    virtual void languageChange();
    virtual void slotBtnCancelClicked();
    virtual void slotBtnConfirmClicked();
    virtual void ListBoxClicked (QListBoxItem * item);
    virtual void ListBoxDoubleClicked (QListBoxItem* item);
    virtual void steadystateEditing();
    virtual void timeEditing();
    virtual void steadystateEnable();
    virtual void timeEnable();*/

    /*signals:
      void hide_me();
      void show_me();*/

  private:
    void viewMousePressEvent(QMouseEvent* e);
    /*void mouseSelected(OptimizationItemWidget* pSelected);
    int nSelectedObjects;
    int nTitleHeight;
    int activeObject;
    std::string objKey;*/
    std::string objKey;
    std::string SteadyStateKey;
    std::string TrajectoryKey;
    SteadyStateWidget* pSteadyStateWidget;
    TrajectoryWidget* pTrajectoryWidget;

    //bool addNewOptItem(CCopasiObject* pObject);
  };

#endif // ParameterFittingWidget_H
