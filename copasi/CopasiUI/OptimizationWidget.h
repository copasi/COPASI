/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/OptimizationWidget.h,v $
   $Revision: 1.1.1.1 $
   $Name:  $
   $Author: anuragr $ 
   $Date: 2004/10/26 15:17:50 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 09/19
Comment : OptimizationWidget for UI of the optimization function
Contact: Please contact lixu1@vt.edu.
 *********************************************************/

#ifndef OptimizationWidget_H
#define OptimizationWidget_H

#include <vector>
#include <qvariant.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QPushButton;
class QLabel;
class QComboBox;
class QListBox;
class QLineEdit;
class QTextEdit;
class COptFunction;
class ScanScrollView;
class OptimizationItemWidget;
class QListBoxItem;
class QCheckBox;
class SteadyStateWidget;
class TrajectoryWidget;
class CCopasiObject;

class OptimizationWidget : public CopasiParametersWidget
  {
    Q_OBJECT

  public:
    OptimizationWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~OptimizationWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

    const std::string getKey();
    //manually added
    QLineEdit* expressionText;
    ScanScrollView* itemsTable;
    std::vector<QWidget*> selectedList;
    QListBox* itemnamesTable;

    QFrame* bodyField;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
    QPushButton* addButton;
    QPushButton* deleteButton;
    QPushButton* downButton;
    QLabel* itemsLabel;
    QPushButton* upButton;
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
    QLabel* expressionNameLabel;

  protected:
    QGridLayout* ExpressionWidgetLayout;
    QHBoxLayout* layout14;
    QGridLayout* layout8;
    QHBoxLayout* layout7;

    bool loadFromExpression(COptFunction*);
    bool bUpdated;

  protected slots:
    void addButtonClicked();
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
    virtual void timeEnable();

  signals:
    void hide_me();
    void show_me();

  private:
    void mouseSelected(OptimizationItemWidget* pSelected);
    void viewMousePressEvent(QMouseEvent* e);
    int nSelectedObjects;
    int nTitleHeight;
    int activeObject;
    std::string objKey;

    std::string SteadyStateKey;
    std::string TrajectoryKey;
    SteadyStateWidget* pSteadyStateWidget;
    TrajectoryWidget* pTrajectoryWidget;

    bool addNewOptItem(CCopasiObject* pObject);
  };

#endif // OptimizationWidget_H
