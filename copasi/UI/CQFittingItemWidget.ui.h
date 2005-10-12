/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFittingItemWidget.ui.h,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/12 13:26:30 $
   End CVS Header */

#include "CCopasiSelectionDialog.h"
#include "CQValidator.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "parameterFitting/CFitItem.h"
#include "utilities/utility.h"

void CQFittingItemWidget::init()
{
  mpFitItem = new CFitItem;

  mLowerInfChanged = false;
  mUpperInfChanged = false;

  int h, s, v;

  mSavedColor = paletteBackgroundColor();
  mSavedColor.getHsv(&h, &s, &v);

  if (s < 20) s = 20;
  mChangedColor.setHsv(240, s, v);

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
  pdelete(mpFitItem);
}

void CQFittingItemWidget::slotNegativeInfinity()
{
  mpEditLower->setEnabled(!mpLowerInf->isChecked());

  mLowerInfChanged = !mLowerInfChanged;

  if (mLowerInfChanged)
    {
      mpLowerInf->setPaletteBackgroundColor(mChangedColor);
      if (mpEditLower->isEnabled()) mpLowerValidator->revalidate();
    }
  else
    mpLowerInf->setPaletteBackgroundColor(mSavedColor);
}

void CQFittingItemWidget::slotPositiveInfinity()
{
  mpEditUpper->setEnabled(!mpUpperInf->isChecked());

  mUpperInfChanged = !mUpperInfChanged;

  if (mUpperInfChanged)
    {
      mpUpperInf->setPaletteBackgroundColor(mChangedColor);
      if (mpEditUpper->isEnabled()) mpUpperValidator->revalidate();
    }
  else
    mpUpperInf->setPaletteBackgroundColor(mSavedColor);
}

void CQFittingItemWidget::slotLowerEdit()
{
  std::vector<CCopasiObject*> Selection;

  CCopasiSelectionDialog * pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(CCopasiDataModel::Global->getModel());
  pBrowseDialog->setSingleSelection(true);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      mpLowerInf->setChecked(false);
      mpEditLower->setEnabled(true);

      mpFitItem->setLowerBound(Selection[0]->getCN());

      QString Value = FROM_UTF8(Selection[0]->getObjectDisplayName());
      mpLowerValidator->forceAcceptance(Value);
      mpEditLower->setText(Value);
    }
}

void CQFittingItemWidget::slotUpperEdit()
{
  std::vector<CCopasiObject*> Selection;

  CCopasiSelectionDialog * pBrowseDialog = new CCopasiSelectionDialog(this);
  pBrowseDialog->setModel(CCopasiDataModel::Global->getModel());
  pBrowseDialog->setSingleSelection(true);
  pBrowseDialog->setOutputVector(&Selection);

  if (pBrowseDialog->exec () == QDialog::Accepted && Selection.size() != 0)
    {
      mpUpperInf->setChecked(false);
      mpEditUpper->setEnabled(true);

      mpFitItem->setUpperBound(Selection[0]->getCN());

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
      mpFitItem->setObjectCN(Selection[0]->getCN());

      QString Value = FROM_UTF8(Selection[0]->getObjectDisplayName());
      mpObjectValidator->forceAcceptance(Value);
      mpEditObject->setText(Value);
    }
}

void CQFittingItemWidget::slotExperiments()
{}

bool CQFittingItemWidget::loadFitItem(const CFitItem & item)
{
  pdelete(mpFitItem);
  mpFitItem = new CFitItem(item);

  QString Value;

  const CCopasiObject *pObject = RootContainer.getObject(mpFitItem->getObjectCN());

  if (pObject)
    Value = FROM_UTF8(pObject->getObjectDisplayName());
  else
    Value = "Not found: " + FROM_UTF8(mpFitItem->getObjectCN());

  mpEditObject->setText(Value);

  if (mpFitItem->getLowerBound() == "-inf" ||
      isNumber(mpFitItem->getLowerBound()))
    Value = FROM_UTF8(mpFitItem->getLowerBound());
  else if ((pObject = RootContainer.getObject(mpFitItem->getLowerBound())))
    Value = FROM_UTF8(pObject->getObjectDisplayName());
  else
    Value = "Not found: " + FROM_UTF8(mpFitItem->getLowerBound());

  mpEditLower->setText(Value);
  mpLowerInf->setChecked(Value == "-inf");

  if (mpFitItem->getUpperBound() == "inf" ||
      isNumber(mpFitItem->getUpperBound()))
    Value = FROM_UTF8(mpFitItem->getUpperBound());
  else if ((pObject = RootContainer.getObject(mpFitItem->getUpperBound())))
    Value = FROM_UTF8(pObject->getObjectDisplayName());
  else
    Value = "Not found: " + FROM_UTF8(mpFitItem->getUpperBound());

  mpEditUpper->setText(Value);
  mpUpperInf->setChecked(Value == "inf");

  // :TODO: load affected experiments.

  mpLowerInf->setPaletteBackgroundColor(mSavedColor);
  mLowerInfChanged = false;
  mpUpperInf->setPaletteBackgroundColor(mSavedColor);
  mUpperInfChanged = false;
  mpObjectValidator->saved();
  mpLowerValidator->saved();
  mpUpperValidator->saved();

  return true;
}

bool CQFittingItemWidget::saveFitItem(CFitItem & item)
{
  bool changed = false;

  if (mpLowerInf->isChecked())
    mpFitItem->setLowerBound(CCopasiObjectName("-inf"));
  else if (isNumber((const char *) mpEditLower->text().utf8()))
    mpFitItem->setLowerBound(CCopasiObjectName((const char *) mpEditLower->text().utf8()));

  if (mpUpperInf->isChecked())
    mpFitItem->setUpperBound(CCopasiObjectName("inf"));
  else if (isNumber((const char *) mpEditUpper->text().utf8()))
    mpFitItem->setUpperBound(CCopasiObjectName((const char *) mpEditUpper->text().utf8()));

  // :TODO: save affected experiments.

  if (!(item == * mpFitItem))
    {
      changed = true;

      item.setObjectCN(mpFitItem->getObjectCN());
      item.setLowerBound(mpFitItem->getLowerBound());
      item.setUpperBound(mpFitItem->getUpperBound());

      // :TODO: save affected experiments.
    }

  mpLowerInf->setPaletteBackgroundColor(mSavedColor);
  mLowerInfChanged = false;
  mpUpperInf->setPaletteBackgroundColor(mSavedColor);
  mUpperInfChanged = false;
  mpObjectValidator->saved();
  mpLowerValidator->saved();
  mpUpperValidator->saved();

  return changed;
}
