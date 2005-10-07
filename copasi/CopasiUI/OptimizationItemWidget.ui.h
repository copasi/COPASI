/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/OptimizationItemWidget.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/07 16:40:23 $
   End CVS Header */

/****************************************************************************
 ** ui.h extension file, included from the uic-generated form implementation.
 **
 ** If you want to add, delete, or rename functions or slots, use
 ** Qt Designer to update this file, preserving your code.
 **
 ** You should not define a constructor or destructor in this file.
 ** Instead, write your code in functions called init() and destroy().
 ** These will automatically be called by the form's constructor and
 ** destructor.
 *****************************************************************************/

#include "CopasiDataModel/CCopasiDataModel.h"
 #include "CCopasiSelectionDialog.h"
 #include "qtUtilities.h"
 #include "optimization/COptItem.h"
 #include "optimization/COptProblem.h"

//this is called by the constructor
void OptimizationItemWidget::init()
{
  paramObjectCN = NULL;
  mpLowerObject = NULL;
  mpUpperObject = NULL;
  mpObject = NULL;

  lineLower->setEnabled(!checkLowerInf->isChecked());
  lineUpper->setEnabled(!checkUpperInf->isChecked());
}

void OptimizationItemWidget::slotNegativeInfinity()
{
  lineLower->setEnabled(!checkLowerInf->isChecked());
}

void OptimizationItemWidget::slotPositiveInfinity()
{
  lineUpper->setEnabled(!checkUpperInf->isChecked());
}

void OptimizationItemWidget::slotLowerEdit()
{
  checkLowerInf->setChecked(false);
  lineLower->setEnabled(true);
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);
  browseDialog->setModel(CCopasiDataModel::Global->getModel());
  browseDialog->setSingleSelection(true);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec () == QDialog::Accepted && selection->size() != 0)
    {
      mpLowerObject = selection->at(0);
      lineLower->setText(FROM_UTF8(mpLowerObject->getObjectDisplayName()));
    }
}

void OptimizationItemWidget::slotUpperEdit()
{
  checkUpperInf->setChecked(false);
  lineUpper->setEnabled(true);
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);
  browseDialog->setModel(CCopasiDataModel::Global->getModel());
  browseDialog->setSingleSelection(true);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec () == QDialog::Accepted && selection->size() != 0)
    {
      mpUpperObject = selection->at(0);
      lineUpper->setText(FROM_UTF8(mpUpperObject->getObjectDisplayName()));
    }
}

void OptimizationItemWidget::slotParamEdit()
{
  lineObjectName->setEnabled(true);
  CCopasiSelectionDialog* browseDialog = new CCopasiSelectionDialog(this);
  browseDialog->setModel(CCopasiDataModel::Global->getModel());
  browseDialog->setSingleSelection(true);
  std::vector<CCopasiObject*>* selection = new std::vector<CCopasiObject*>();
  browseDialog->setOutputVector(selection);

  if (browseDialog->exec () == QDialog::Accepted && selection->size() != 0)
    {
      paramObjectCN = new CCopasiObjectName();
      *paramObjectCN = (selection->at(0))->getCN();
      lineObjectName->setText(FROM_UTF8((selection->at(0))->getObjectDisplayName()));
    }
}

bool OptimizationItemWidget::initFromOptItem(const COptItem & item)
{
  if (paramObjectCN == NULL) paramObjectCN = new CCopasiObjectName();

  *paramObjectCN = item.getObjectCN();
  lineObjectName->setText(FROM_UTF8(RootContainer.getObject(*paramObjectCN)->getObjectDisplayName()));

  setItemUpperLimit(item.getUpperBound());
  setItemLowerLimit(item.getLowerBound());

  //setItemUpperOper(item.getUpperRelation());
  //setItemLowerOper(item.getLowerRelation());

  return true;
}

bool OptimizationItemWidget::saveToOptItem(COptProblem * pg) const
  {
    if (paramObjectCN != NULL)
      {
        COptItem & pTmp = (pg->addOptItem(*paramObjectCN));
        pTmp.setLowerBound(getItemLowerLimit());
        pTmp.setUpperBound(getItemUpperLimit());
        return true;
      }

    else
      return false;
  }

void OptimizationItemWidget::setItemUpperLimit(std::string strUpperLimit)
{
  if (strUpperLimit == "inf")
    {
      checkUpperInf->setChecked(true);
      //buttonUpperEdit->setEnabled(false);
      lineUpper->setEnabled(false);
      lineUpper->setText("");
    }
  else if (isNumber(strUpperLimit))
    {
      checkUpperInf->setChecked(false);
      //buttonUpperEdit->setEnabled(true);
      lineUpper->setEnabled(true);
      lineUpper->setText(FROM_UTF8(strUpperLimit));
    }
  else
    {
      checkUpperInf->setChecked(false);
      //buttonUpperEdit->setEnabled(true);
      lineUpper->setEnabled(true);

      mpUpperObject = RootContainer.getObject(strUpperLimit);
      if (mpUpperObject)
        lineUpper->setText(FROM_UTF8(mpUpperObject->getObjectDisplayName()));
      else
        lineUpper->setText("");
    }
}

void OptimizationItemWidget::setItemLowerLimit(std::string strLowerLimit)
{
  mpLowerObject = NULL;
  if (strLowerLimit == "-inf")
    {
      checkLowerInf->setChecked(true);
      //buttonLowerEdit->setEnabled(false);
      lineLower->setEnabled(false);
      lineLower->setText("");
    }
  else if (isNumber(strLowerLimit))
    {
      checkLowerInf->setChecked(false);
      //buttonLowerEdit->setEnabled(true);
      lineLower->setEnabled(true);
      lineLower->setText(FROM_UTF8(strLowerLimit));
    }
  else
    {
      checkLowerInf->setChecked(false);
      lineLower->setEnabled(true);

      mpLowerObject = RootContainer.getObject(strLowerLimit);
      if (mpLowerObject)
        lineLower->setText(FROM_UTF8(mpLowerObject->getObjectDisplayName()));
      else
        lineLower->setText("");
    }
}

std::string OptimizationItemWidget::getItemUpperLimit() const
  {
    if (checkUpperInf->isChecked())
      return "inf";
    else if (isNumber((const char*) lineUpper->text().utf8()))
      return (const char*) lineUpper->text().utf8();
    else if (mpUpperObject)
      return mpUpperObject->getCN();
    else
      return "";
  }

std::string OptimizationItemWidget::getItemLowerLimit() const
  {
    if (checkLowerInf->isChecked())
      return "-inf";
    else if (isNumber((const char*) lineLower->text().utf8()))
      return (const char*) lineLower->text().utf8();
    else if (mpLowerObject)
      return mpLowerObject->getCN();
    else
      return "";
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
  lineObjectName->setText(FROM_UTF8(mpObject->getObjectUniqueName()));
}
