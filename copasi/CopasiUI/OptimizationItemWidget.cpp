/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/OptimizationItemWidget.cpp,v $
   $Revision: 1.25 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/05/03 20:20:21 $
   End CVS Header */

/********************************************************
Author: Liang Xu
Version : 1.xx  <first>
Description: 
Date: 10/01
Comment : OptimizationItemWidget for embeded widget for limit of the optimization function
Contact: Please contact lixu1@vt.edu.
 *********************************************************/
#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qcombobox.h>
#include <qframe.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qmessagebox.h>

#include "OptimizationWidget.h"
#include "OptimizationItemWidget.h"
#include "ScanItemWidget.h"
#include "FunctionItemWidget.h"
#include "report/CKeyFactory.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CKinFunction.h"
#include "optimization/COptFunction.h"
#include "utilities/CCopasiException.h"
#include "qtUtilities.h"

/*
 *  Constructs a OptimizationItemWidget as a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
OptimizationItemWidget::OptimizationItemWidget(OptimizationWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl),
    mpParent(parent)
{
  if (!name)
    setName("OptimizationItemWidget");
  OptimizationItemWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "OptimizationItemWidgetLayout");

  textLabel2 = new QLabel(this, "textLabel2");

  OptimizationItemWidgetLayout->addWidget(textLabel2, 0, 0);

  layout13 = new QHBoxLayout(0, 0, 6, "layout13");

  lineLower = new ScanLineEdit(this, "lineLower");
  layout13->addWidget(lineLower);

  buttonLowerEdit = new QPushButton(this, "buttonLowerEdit");
  layout13->addWidget(buttonLowerEdit);

  OptimizationItemWidgetLayout->addLayout(layout13, 5, 2);

  comboBoxUpperOp = new QComboBox(FALSE, this, "comboBoxUpperOp");

  OptimizationItemWidgetLayout->addWidget(comboBoxUpperOp, 2, 1);

  textLabel3 = new QLabel(this, "textLabel3");

  OptimizationItemWidgetLayout->addWidget(textLabel3, 2, 0);

  comboBoxLowerOp = new QComboBox(FALSE, this, "comboBoxLowerOp");

  OptimizationItemWidgetLayout->addWidget(comboBoxLowerOp, 5, 1);

  checkLowerInf = new ScanCheckBox(this, "checkLowerInf");

  OptimizationItemWidgetLayout->addWidget(checkLowerInf, 6, 2);

  layout14 = new QHBoxLayout(0, 0, 6, "layout14");

  lineUpper = new ScanLineEdit(this, "lineUpper");
  layout14->addWidget(lineUpper);

  buttonUpperEdit = new QPushButton(this, "buttonUpperEdit");
  layout14->addWidget(buttonUpperEdit);

  OptimizationItemWidgetLayout->addLayout(layout14, 2, 2);

  textLabel4 = new QLabel(this, "textLabel4");

  OptimizationItemWidgetLayout->addWidget(textLabel4, 5, 0);

  line10 = new QFrame(this, "line10");
  line10->setFrameShape(QFrame::HLine);
  line10->setFrameShadow(QFrame::Sunken);
  line10->setFrameShape(QFrame::HLine);

  OptimizationItemWidgetLayout->addMultiCellWidget(line10, 4, 4, 0, 2);

  checkUpperInf = new ScanCheckBox(this, "checkUpperInf");

  OptimizationItemWidgetLayout->addWidget(checkUpperInf, 3, 2);

  line11 = new QFrame(this, "line11");
  line11->setFrameShape(QFrame::HLine);
  line11->setFrameShadow(QFrame::Sunken);
  line11->setFrameShape(QFrame::HLine);

  OptimizationItemWidgetLayout->addMultiCellWidget(line11, 1, 1, 0, 2);

  ObjectName = new ScanLineEdit(this, "ObjectName");
  ObjectName->setEnabled(FALSE);

  OptimizationItemWidgetLayout->addMultiCellWidget(ObjectName, 0, 0, 1, 2);
  languageChange();
  resize(QSize(390, 173).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(checkUpperInf, SIGNAL(clicked()), this, SLOT(slotPosInfClicked()));
  connect(checkLowerInf, SIGNAL(clicked()), this, SLOT(slotNegInfClicked()));
  connect(buttonUpperEdit, SIGNAL(clicked()), this, SLOT(slotUpperEdit()));
  connect(buttonLowerEdit, SIGNAL(clicked()), this, SLOT(slotLowerEdit()));

  // tab order
  setTabOrder(ObjectName, comboBoxUpperOp);
  setTabOrder(comboBoxUpperOp, lineUpper);
  setTabOrder(lineUpper, buttonUpperEdit);
  setTabOrder(buttonUpperEdit, checkUpperInf);
  setTabOrder(checkUpperInf, comboBoxLowerOp);
  setTabOrder(comboBoxLowerOp, lineLower);
  setTabOrder(lineLower, buttonLowerEdit);
  setTabOrder(buttonLowerEdit, checkLowerInf);

  checkUpperInf->setChecked(true);
  checkLowerInf->setChecked(true);

  //  buttonUpperEdit->setEnabled(false);
  //  buttonLowerEdit->setEnabled(false);

  lineUpper->setEnabled(false);
  lineLower->setEnabled(false);
}

/*
 *  Destroys the object and frees any allocated resources
 */
OptimizationItemWidget::~OptimizationItemWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void OptimizationItemWidget::languageChange()
{
  setCaption(tr("Optimization Item"));
  textLabel2->setText(tr("Parameter"));
  buttonLowerEdit->setText(tr("edit"));
  comboBoxUpperOp->clear();
  comboBoxUpperOp->insertItem(tr("<"));
  comboBoxUpperOp->insertItem(tr("<="));
  comboBoxUpperOp->insertItem(tr("=="));
  textLabel3->setText(tr("Upper"));
  comboBoxLowerOp->clear();
  comboBoxLowerOp->insertItem(tr(">"));
  comboBoxLowerOp->insertItem(tr(">="));
  comboBoxLowerOp->insertItem(tr("=="));
  checkLowerInf->setText(tr("- Inf"));
  buttonUpperEdit->setText(tr("edit"));
  textLabel4->setText(tr("Lower"));
  checkUpperInf->setText(tr("+ Inf"));
}

void OptimizationItemWidget::slotPosInfClicked()
{
  lineUpper->setEnabled(!checkUpperInf->isChecked());
  //buttonUpperEdit->setEnabled(!checkUpperInf->isChecked());
}

void OptimizationItemWidget::slotLowerEdit()
{
  //qWarning("OptimizationItemWidget::slotLowerEdit(): Not implemented yet");
  checkLowerInf->setChecked(false);
  lineLower->setEnabled(true);
  std::string strFunction;
  FunctionItemWidget* pFuncDlg = new FunctionItemWidget(this);
  strFunction = lineLower->text().utf8();
  pFuncDlg->setStrFunction(&strFunction);

  if (pFuncDlg->exec () == QDialog::Accepted)
    {
      lineLower->setText(FROM_UTF8(strFunction));
      COptFunction* func =
        dynamic_cast< COptFunction * >(GlobalKeys.get(mpParent->getKey()));
      int nIndex; // this nIndex must exist;
      nIndex = func->Index(mpObject->getCN());
      func->mMinList[nIndex] = FROM_UTF8(strFunction);
      if (!(func->mMinFunctionList[nIndex]))
        func->mMinFunctionList[nIndex] = new CKinFunction();
      // dont go through the compile function
      func->mMinFunctionList[nIndex]->CFunction::setDescription(func->mMinList[nIndex]);
      try
        {
          func->mMinFunctionList[nIndex]->compile();
        }
      catch (CCopasiException Exception)
        {
          if (QMessageBox::warning(this, "Invalid Function Input",
                                   "Invalid function expression.\n Please check function again \n Do you still want to keep your input? \n"
                                   "Press <Yes> to keep.",
                                   QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
            {
              func->mMinList[nIndex] = "";
              lineLower->setText("");
            }
        }
    }
}

void OptimizationItemWidget::slotNegInfClicked()
{
  lineLower->setEnabled(!checkLowerInf->isChecked());
  //buttonLowerEdit->setEnabled(!checkLowerInf->isChecked());
}

void OptimizationItemWidget::slotUpperEdit()
{
  //qWarning("OptimizationItemWidget::slotUpperEdit(): Not implemented yet");
  checkUpperInf->setChecked(false);
  lineUpper->setEnabled(true);
  std::string strFunction;
  FunctionItemWidget* pFuncDlg = new FunctionItemWidget(this);
  strFunction = lineUpper->text().utf8();
  pFuncDlg->setStrFunction(&strFunction);
  if (pFuncDlg->exec () == QDialog::Accepted)
    {
      lineUpper->setText(FROM_UTF8(strFunction));
      COptFunction* func =
        dynamic_cast< COptFunction * >(GlobalKeys.get(mpParent->getKey()));
      int nIndex; // this nIndex must exist;
      nIndex = func->Index(mpObject->getCN());
      func->mMaxList[nIndex] = FROM_UTF8(strFunction);
      if (!(func->mMaxFunctionList[nIndex]))
        func->mMaxFunctionList[nIndex] = new CKinFunction();
      // dont go through the compile function
      func->mMaxFunctionList[nIndex]->CFunction::setDescription(func->mMaxList[nIndex]);
      try
        {
          func->mMaxFunctionList[nIndex]->compile();
        }
      catch (CCopasiException Exception)
        {
          if (QMessageBox::warning(this, "Invalid Function Input",
                                   "Invalid function expression.\n Please check function again \n Do you still want to keep your input? \n"
                                   "Press <Yes> to keep.",
                                   QMessageBox::Yes, QMessageBox::No) == QMessageBox::No)
            {
              func->mMaxList[nIndex] = "";
              lineUpper->setText("");
            }
        }
    }
}

std::string OptimizationItemWidget::getItemUpperLimit()
{
  if (checkUpperInf->isChecked())
    return "+inf";
  else
    return lineUpper->text().utf8();
}

std::string OptimizationItemWidget::getItemLowerLimit()
{
  if (checkLowerInf->isChecked())
    return "-inf";
  else
    return lineLower->text().utf8();
}

CCopasiObject* OptimizationItemWidget::getCopasiObject()
{
  return mpObject;
}

void OptimizationItemWidget::setCopasiObjectPtr (CCopasiObject* sourceObject)
{
  if (!sourceObject) // NULL pointer
    return;
  mpObject = sourceObject;
  ObjectName->setText(FROM_UTF8(mpObject->getObjectUniqueName()));
}

void OptimizationItemWidget::setItemUpperLimit(std::string strUpperLimit)
{
  if (strUpperLimit == "+inf")
    {
      checkUpperInf->setChecked(true);
      //buttonUpperEdit->setEnabled(false);
      lineUpper->setEnabled(false);
      lineUpper->setText("");
    }
  else
    {
      checkUpperInf->setChecked(false);
      //buttonUpperEdit->setEnabled(true);
      lineUpper->setEnabled(true);
      lineUpper->setText(FROM_UTF8(strUpperLimit));
    }
}

void OptimizationItemWidget::setItemLowerLimit(std::string strLowerLimit)
{
  if (strLowerLimit == "-inf")
    {
      checkLowerInf->setChecked(true);
      //buttonLowerEdit->setEnabled(false);
      lineLower->setEnabled(false);
      lineLower->setText("");
    }
  else
    {
      checkLowerInf->setChecked(false);
      //buttonLowerEdit->setEnabled(true);
      lineLower->setEnabled(true);
      lineLower->setText(FROM_UTF8(strLowerLimit));
    }
}

std::string OptimizationItemWidget::getItemUpperOper()
{
  return comboBoxUpperOp->currentText().utf8();
}

std::string OptimizationItemWidget::getItemLowerOper()
{
  return comboBoxLowerOp->currentText().utf8();
}

void OptimizationItemWidget::setItemUpperOper(std::string oper)
{
  comboBoxUpperOp->setCurrentText(FROM_UTF8(oper));
}

void OptimizationItemWidget::setItemLowerOper(std::string oper)
{
  comboBoxLowerOp->setCurrentText(FROM_UTF8(oper));
}
