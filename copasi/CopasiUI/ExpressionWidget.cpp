/****************************************************************************
 ** Form implementation generated from reading ui file '.\ExpressionWidget.ui'
 **
 ** Created: Fri Sep 19 15:37:59 2003
 **      by: The User Interface Compiler ($Id: ExpressionWidget.cpp,v 1.2 2003/09/19 19:48:34 lixu1 Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "ExpressionWidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qframe.h>
#include <qlabel.h>
#include <qtable.h>
#include <qlineedit.h>
#include <qtextedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>

/*
 *  Constructs a ExpressionWidget as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ExpressionWidget::ExpressionWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl)
{
  if (!name)
    setName("ExpressionWidget");
  ExpressionWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "ExpressionWidgetLayout");

  bodyField = new QFrame(this, "bodyField");
  bodyField->setFrameShape(QFrame::HLine);
  bodyField->setFrameShadow(QFrame::Sunken);
  bodyField->setFrameShape(QFrame::HLine);

  ExpressionWidgetLayout->addMultiCellWidget(bodyField, 2, 2, 0, 1);

  layout14 = new QHBoxLayout(0, 0, 6, "layout14");

  confirmButton = new QPushButton(this, "confirmButton");
  layout14->addWidget(confirmButton);

  cancelButton = new QPushButton(this, "cancelButton");
  layout14->addWidget(cancelButton);

  ExpressionWidgetLayout->addMultiCellLayout(layout14, 3, 3, 0, 1);

  layout6 = new QVBoxLayout(0, 0, 6, "layout6");

  itemsLabel = new QLabel(this, "itemsLabel");
  layout6->addWidget(itemsLabel);

  layout5 = new QGridLayout(0, 1, 1, 0, 6, "layout5");

  upButton = new QPushButton(this, "upButton");

  layout5->addWidget(upButton, 1, 0);

  downButton = new QPushButton(this, "downButton");

  layout5->addWidget(downButton, 1, 1);

  deleteButton = new QPushButton(this, "deleteButton");

  layout5->addWidget(deleteButton, 0, 1);

  addButton = new QPushButton(this, "addButton");

  layout5->addWidget(addButton, 0, 0);
  layout6->addLayout(layout5);
  QSpacerItem* spacer = new QSpacerItem(90, 262, QSizePolicy::Minimum, QSizePolicy::Expanding);
  layout6->addItem(spacer);

  ExpressionWidgetLayout->addLayout(layout6, 1, 0);

  itemsTable = new QTable(this, "itemsTable");
  itemsTable->setNumRows(0);
  itemsTable->setNumCols(0);

  ExpressionWidgetLayout->addWidget(itemsTable, 1, 1);

  frame5 = new QFrame(this, "frame5");
  frame5->setFrameShape(QFrame::Box);
  frame5->setFrameShadow(QFrame::Sunken);
  frame5Layout = new QGridLayout(frame5, 1, 1, 11, 6, "frame5Layout");

  expressionName = new QLineEdit(frame5, "expressionName");
  expressionName->setFrameShape(QLineEdit::LineEditPanel);
  expressionName->setFrameShadow(QLineEdit::Sunken);

  frame5Layout->addWidget(expressionName, 0, 1);

  expressionNameLabel = new QLabel(frame5, "expressionNameLabel");

  frame5Layout->addWidget(expressionNameLabel, 0, 0);

  textEdit2 = new QTextEdit(frame5, "textEdit2");

  frame5Layout->addMultiCellWidget(textEdit2, 1, 2, 1, 1);

  expressionEditlabel = new QLabel(frame5, "expressionEditlabel");

  frame5Layout->addWidget(expressionEditlabel, 1, 0);
  QSpacerItem* spacer_2 = new QSpacerItem(60, 31, QSizePolicy::Minimum, QSizePolicy::Expanding);
  frame5Layout->addItem(spacer_2, 2, 0);

  ExpressionWidgetLayout->addMultiCellWidget(frame5, 0, 0, 0, 1);
  languageChange();
  resize(QSize(519, 468).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
}

/*
 *  Destroys the object and frees any allocated resources
 */
ExpressionWidget::~ExpressionWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void ExpressionWidget::languageChange()
{
  setCaption(tr("Expression"));
  confirmButton->setText(tr("confirm"));
  cancelButton->setText(tr("cancel"));
  itemsLabel->setText(tr("Items"));
  upButton->setText(QString::null);
  downButton->setText(QString::null);
  deleteButton->setText(QString::null);
  addButton->setText(QString::null);
  expressionNameLabel->setText(tr("Expresion Name"));
  expressionEditlabel->setText(tr("Expression"));
}
