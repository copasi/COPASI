/****************************************************************************
 ** Form interface generated from reading ui file '.\ExpressionWidget.ui'
 **
 ** Created: Fri Sep 19 15:37:58 2003
 **      by: The User Interface Compiler ($Id: ExpressionWidget.h,v 1.12 2003/09/23 20:24:21 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef EXPRESSIONWIDGET_H
#define EXPRESSIONWIDGET_H

#include <qvariant.h>
#include "copasiWidget.h"

class QVBoxLayout;
class QHBoxLayout;
class QGridLayout;
class QFrame;
class QPushButton;
class QLabel;
//class QTable;
class QListBox;
class QLineEdit;
class QTextEdit;
class CExpression;

class ExpressionWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    ExpressionWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ExpressionWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");
    //manually added
    QLineEdit* expressionText;
    QListBox* itemsTable;

    QLineEdit* expressionName;
    QLabel* expressionEditlabel;
    QLabel* expressionNameLabel;
    QFrame* bodyField_2;
    QLabel* itemsLabel;
    QPushButton* downButton;
    QPushButton* deleteButton;
    QPushButton* addButton;
    QPushButton* upButton;
    QListBox* listBoxItems;
    QFrame* bodyField;
    QPushButton* confirmButton;
    QPushButton* cancelButton;

  protected:
    QGridLayout* ExpressionWidgetLayout;
    QVBoxLayout* layout18;
    QGridLayout* layout17;
    QHBoxLayout* layout16;
    QVBoxLayout* layout15;
    QGridLayout* layout14;
    QHBoxLayout* layout14_2;

    bool loadFromExpression(CExpression*);
    std::string objKey;
    bool bUpdated;

  protected slots:
    void addButtonClicked();
    void deleteButtonClicked();
    void upButtonClicked();
    void downButtonClicked();
    virtual void languageChange();
    virtual void slotBtnCancelClicked();
    virtual void slotBtnConfirmClicked();
  };

#endif // EXPRESSIONWIDGET_H
