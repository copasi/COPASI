/****************************************************************************
 ** Form interface generated from reading ui file '.\ExpressionWidget.ui'
 **
 ** Created: Fri Sep 19 15:37:58 2003
 **      by: The User Interface Compiler ($Id: ExpressionWidget.h,v 1.8 2003/09/19 21:02:02 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#ifndef EXPRESSIONWIDGET_H
#define EXPRESSIONWIDGET_H

#include <qvariant.h>
#include "CopasiWidget.h"

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
class CFunction;

class ExpressionWidget : public CopasiWidget
  {
    Q_OBJECT

  public:
    ExpressionWidget(QWidget* parent = 0, const char* name = 0, WFlags fl = 0);
    ~ExpressionWidget();

    virtual bool update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key);
    virtual bool leave();
    virtual bool enter(const std::string & key = "");

    QFrame* bodyField;
    QPushButton* confirmButton;
    QPushButton* cancelButton;
    QLabel* itemsLabel;
    QPushButton* upButton;
    QPushButton* downButton;
    QPushButton* deleteButton;
    QPushButton* addButton;
    //    QTable* itemsTable;
    QListBox* itemsTable;
    QFrame* frame5;
    QLineEdit* expressionName;
    QLabel* expressionNameLabel;
    QTextEdit* textEdit2;
    QLabel* expressionEditlabel;

  protected:
    QGridLayout* ExpressionWidgetLayout;
    QHBoxLayout* layout14;
    QVBoxLayout* layout6;
    QGridLayout* layout5;
    QGridLayout* frame5Layout;
    bool loadFromExpression(CFunction*);
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
