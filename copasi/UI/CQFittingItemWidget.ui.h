/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQFittingItemWidget.ui.h,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/28 15:38:20 $
   End CVS Header */

#include <qapplication.h>

#include "CCopasiSelectionDialog.h"
#include "CQValidator.h"
#include "qtUtilities.h"

#include "CopasiDataModel/CCopasiDataModel.h"
#include "report/CKeyFactory.h"
#include "parameterFitting/CFitItem.h"
#include "utilities/utility.h"

void CQFittingItemWidget::init()
{
  mpItem = NULL;
  enableFitItem(false);

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
{pdelete(mpItem);}

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

      mpItem->setLowerBound(Selection[0]->getCN());

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

      mpItem->setUpperBound(Selection[0]->getCN());

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
      mpItem->setObjectCN(Selection[0]->getCN());

      QString Value = FROM_UTF8(Selection[0]->getObjectDisplayName());
      mpObjectValidator->forceAcceptance(Value);
      mpEditObject->setText(Value);
    }
}

void CQFittingItemWidget::slotExperiments()
{}

CQFittingItemWidget * CQFittingItemWidget::copy()
{
  CQFittingItemWidget * pWidget =
    new CQFittingItemWidget(static_cast<QWidget *>(parent()));
  pWidget->enableFitItem(mIsFitItem);

  pWidget->mpEditObject->setText(mpEditObject->text());
  pWidget->mpItem->setObjectCN(mpItem->getObjectCN());
  pWidget->mpObjectValidator->forceAcceptance(mpEditObject->text());
  pWidget->mpObjectValidator->revalidate();

  pWidget->mpLowerInf->setChecked(mpLowerInf->isChecked());
  pWidget->mLowerInfChanged = mLowerInfChanged;
  pWidget->mpEditLower->setText(mpEditLower->text());
  pWidget->mpItem->setLowerBound(mpItem->getLowerBound());

  const CCopasiObject *pObject;

  if (isNumber((const char *)mpEditLower->text().utf8()))
    pWidget->mpLowerValidator->forceAcceptance(mpEditLower->text());
  if ((pObject = RootContainer.getObject(mpItem->getLowerBound())))
    pWidget->mpLowerValidator->forceAcceptance(FROM_UTF8(pObject->getObjectDisplayName()));
  pWidget->mpLowerValidator->revalidate();

  pWidget->mpUpperInf->setChecked(mpUpperInf->isChecked());
  pWidget->mUpperInfChanged = mUpperInfChanged;
  pWidget->mpEditUpper->setText(mpEditUpper->text());
  pWidget->mpItem->setUpperBound(mpItem->getUpperBound());

  if (isNumber((const char *)mpEditUpper->text().utf8()))
    pWidget->mpUpperValidator->forceAcceptance(mpEditUpper->text());
  if ((pObject = RootContainer.getObject(mpItem->getUpperBound())))
    pWidget->mpUpperValidator->forceAcceptance(FROM_UTF8(pObject->getObjectDisplayName()));
  pWidget->mpUpperValidator->revalidate();

  // :TODO: Copy affected experiments.

  return pWidget;
}

bool CQFittingItemWidget::load(const CFitItem & item)
{
  if (!mIsFitItem) return false;

  pdelete(mpItem);
  mpItem = new CFitItem(item);

  return loadCommon(item);
}

bool CQFittingItemWidget::load(const COptItem & item)
{
  if (mIsFitItem) return false;

  pdelete(mpItem);
  mpItem = new COptItem(item);

  return loadCommon(item);
}

bool CQFittingItemWidget::loadCommon(const COptItem & item)
{
  QString Value;

  const CCopasiObject *pObject = RootContainer.getObject(mpItem->getObjectCN());

  if (pObject)
    Value = FROM_UTF8(pObject->getObjectDisplayName());
  else
    Value = "Not found: " + FROM_UTF8(mpItem->getObjectCN());

  mpEditObject->setText(Value);

  if (mpItem->getLowerBound() == "-inf" ||
      isNumber(mpItem->getLowerBound()))
    Value = FROM_UTF8(mpItem->getLowerBound());
  else if ((pObject = RootContainer.getObject(mpItem->getLowerBound())))
    Value = FROM_UTF8(pObject->getObjectDisplayName());
  else
    Value = "Not found: " + FROM_UTF8(mpItem->getLowerBound());

  mpEditLower->setText(Value);
  mpLowerInf->setChecked(Value == "-inf");

  if (mpItem->getUpperBound() == "inf" ||
      isNumber(mpItem->getUpperBound()))
    Value = FROM_UTF8(mpItem->getUpperBound());
  else if ((pObject = RootContainer.getObject(mpItem->getUpperBound())))
    Value = FROM_UTF8(pObject->getObjectDisplayName());
  else
    Value = "Not found: " + FROM_UTF8(mpItem->getUpperBound());

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

bool CQFittingItemWidget::save(CFitItem & item)
{
  bool changed = saveCommon(item);

  // :TODO: load affected experiments.

  return changed;
}

bool CQFittingItemWidget::save(COptItem & item)
{return saveCommon(item);}

bool CQFittingItemWidget::saveCommon(COptItem & item)
{
  bool changed = false;

  if (mpLowerInf->isChecked())
    mpItem->setLowerBound(CCopasiObjectName("-inf"));
  else if (isNumber((const char *) mpEditLower->text().utf8()))
    mpItem->setLowerBound(CCopasiObjectName((const char *) mpEditLower->text().utf8()));

  if (mpUpperInf->isChecked())
    mpItem->setUpperBound(CCopasiObjectName("inf"));
  else if (isNumber((const char *) mpEditUpper->text().utf8()))
    mpItem->setUpperBound(CCopasiObjectName((const char *) mpEditUpper->text().utf8()));

  if (!(item == * mpItem))
    {
      changed = true;

      item.setObjectCN(mpItem->getObjectCN());
      item.setLowerBound(mpItem->getLowerBound());
      item.setUpperBound(mpItem->getUpperBound());
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

void CQFittingItemWidget::enableFitItem(const bool & enable)
{
  mIsFitItem = enable;
  pdelete(mpItem);

  if (mIsFitItem)
    {
      mpItem = new CFitItem;

      mpLblExperiments->show();
      mpBoxExperiments->show();
      mpBtnExperiments->show();
    }
  else
    {
      mpItem = new COptItem;

      mpLblExperiments->hide();
      mpBoxExperiments->hide();
      mpBtnExperiments->hide();
    }

  qApp->processEvents();
}

bool CQFittingItemWidget::update(const std::map<std::string, std::string> & keymap)
{
  if (!mIsFitItem) return false;

  bool success = true;

  CCopasiParameterGroup *pGroup = mpItem->getGroup("Affected Experiments");

  std::map<std::string, std::string>::const_iterator it = keymap.begin();
  std::map<std::string, std::string>::const_iterator end = keymap.end();

  unsigned C_INT32 i;

  mpBoxExperiments->clear();
  for (i = pGroup->size() - 1; i != C_INVALID_INDEX; i--)
    {
      it = keymap.find(*pGroup->getValue(i).pKEY);

      if (it != end)
        {
          pGroup->setValue(i, it->second);
          mpBoxExperiments->insertItem(FROM_UTF8(GlobalKeys.get(it->second)->getObjectName()), 0);
        }
      else
        {
          pGroup->removeParameter(i);
          success = false;
        }
    }

  if (!mpBoxExperiments->count()) mpBoxExperiments->insertItem("All");

  return success;
}
