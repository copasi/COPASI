/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingItemWidget.ui.h,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/10 18:53:10 $
   End CVS Header */

#include "CCopasiSelectionDialog.h"
#include "CQValidator.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "parameterFitting/CFitItem.h"

void CQFittingItemWidget::init()
{
  mpObject = NULL;
  mpFitItem = NULL;

  mpObjectValidator = new CQValidatorNotEmpty(mpEditObject);
  mpEditObject->setValidator(mpObjectValidator);
  mpObjectValidator->revalidate();

  mpLowerValidator = new CQValidatorBound(mpEditLower);
  mpEditLower->setValidator(mpLowerValidator);
  mpLowerValidator->revalidate();

  mpUpperValidator = new CQValidatorBound(mpEditUpper);
  mpEditUpper->setValidator(mpUpperValidator);
  mpUpperValidator->revalidate();
}

void CQFittingItemWidget::destroy()
{
  pdelete(mpObject);
  pdelete(mpFitItem);
}

void CQFittingItemWidget::setItemUpperLimit(std::string strUpperLimit)
{}

void CQFittingItemWidget::setItemLowerLimit(std::string strLowerLimit)
{}

std::string CQFittingItemWidget::getItemUpperLimit() const
  {
    return "";
  }

std::string CQFittingItemWidget::getItemLowerLimit() const
  {
    return "";
  }

CCopasiObject * CQFittingItemWidget::getCopasiObject()
{
  return mpObject;
}

void CQFittingItemWidget::setCopasiObjectPtr(CCopasiObject * sourceObject)
{}

void CQFittingItemWidget::slotNegativeInfinity()
{
  mpEditLower->setEnabled(!mpLowerInf->isChecked());
  if (mpEditLower->isEnabled()) mpLowerValidator->revalidate();
}

void CQFittingItemWidget::slotPositiveInfinity()
{
  mpEditUpper->setEnabled(!mpUpperInf->isChecked());
  if (mpEditUpper->isEnabled()) mpUpperValidator->revalidate();
}

void CQFittingItemWidget::slotLowerEdit()
{
  mpLowerInf->setChecked(false);
  mpEditLower->setEnabled(true);

  std::vector<CCopasiObject*> Selection;

  CCopasiSelectionDialog * pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(CCopasiDataModel::Global->getModel());
  pBrowseDialog->setSingleSelection(true);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      mpFitItem->setLowerBound(Selection[0]->getObjectName());

      QString Value = FROM_UTF8(Selection[0]->getObjectDisplayName());
      mpLowerValidator->forceAcceptance(Value);
      mpEditLower->setText(Value);
    }
}

void CQFittingItemWidget::slotUpperEdit()
{
  mpUpperInf->setChecked(false);
  mpEditUpper->setEnabled(true);

  std::vector<CCopasiObject*> Selection;

  CCopasiSelectionDialog * pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(CCopasiDataModel::Global->getModel());
  pBrowseDialog->setSingleSelection(true);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      mpFitItem->setUpperBound(Selection[0]->getObjectName());

      QString Value = FROM_UTF8(Selection[0]->getObjectDisplayName());
      mpUpperValidator->forceAcceptance(Value);
      mpEditUpper->setText(Value);
    }
}

void CQFittingItemWidget::slotParamEdit()
{
  std::vector<CCopasiObject*> Selection;

  CCopasiSelectionDialog * pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(CCopasiDataModel::Global->getModel());
  pBrowseDialog->setSingleSelection(true);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      mpFitItem->setObjectCN(Selection[0]->getObjectName());

      QString Value = FROM_UTF8(Selection[0]->getObjectDisplayName());
      mpObjectValidator->forceAcceptance(Value);
      mpEditObject->setText(Value);
    }
}

void CQFittingItemWidget::slotExperiments()
{}

bool CQFittingItemWidget::loadFitItem(const CFitItem * pItem)
{
  pdelete(mpFitItem);
  mpFitItem = new CFitItem(*pItem);

  return true;
}

CFitItem * CQFittingItemWidget::saveFitItem(CFitItem * pItem)
{
  return mpFitItem;
}
