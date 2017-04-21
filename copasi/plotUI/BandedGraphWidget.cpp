// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2011 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "BandedGraphWidget.h"

#include "UI/CCopasiSelectionDialog.h"
#include "UI/qtUtilities.h"
#include "CQPlotEditWidget.h"

#include "copasi.h"

#include "copasi/core/CRootContainer.h"
#include "plot/CPlotItem.h"
#include "resourcesUI/CQIconResource.h"

/**
 * In multiple edit mode, we don't want to edit name & channels
 */
void BandedGraphWidget::setMultipleEditMode(bool mode)
{
  mpEditTitle->setEnabled(!mode);
  mpEditX->setEnabled(!mode);
  mpEditYone->setEnabled(!mode);
  mpEditYtwo->setEnabled(!mode);
  mpBtnX->setEnabled(!mode);
  mpBtnYone->setEnabled(!mode);
  mpBtnYtwo->setEnabled(!mode);
}

/*
 *  Constructs a BandedGraphWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
BandedGraphWidget::BandedGraphWidget(QWidget* parent, const char* /* name */, Qt::WindowFlags fl):
  CQPlotEditWidget(parent, fl),
  mpObjectYone(NULL),
  mpObjectYtwo(NULL),
  mpObjectX(NULL)
{
  setupUi(this);

  mpBtnX->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnYone->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnYtwo->setIcon(CQIconResource::icon(CQIconResource::copasi));
}

/*
 *  Destroys the object and frees any allocated resources
 */
BandedGraphWidget::~BandedGraphWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

bool
BandedGraphWidget::LoadFromCurveSpec(const CPlotItem * pCurve)
{
  if (!pCurve)
    {
      // We need to reset the widget to defaults
      mpEditTitle->setText("");

      mpObjectX = mpObjectYone = mpObjectYtwo = NULL;

      mpEditX->setText("");
      mpEditYone->setText("");
      mpEditYtwo->setText("");

      mpCheckBefore->setChecked(false);
      mpCheckDuring->setChecked(true);
      mpCheckAfter->setChecked(false);

      return true;
    }

  if (pCurve->getType() != CPlotItem::bandedGraph) return false;

  //if (pCurve->getChannels().getSize != 3) return false;

  mpEditTitle->setText(FROM_UTF8(pCurve->getTitle()));

  CDataModel* pDataModel = pCurve->getObjectDataModel();
  assert(pDataModel != NULL);

  mpObjectX = mpObjectYone = mpObjectYtwo = NULL;

  if (pCurve->getChannels().size() >= 1)
    mpObjectX = dynamic_cast<const CDataObject*>(pDataModel->getObject(pCurve->getChannels()[0]));

  if (pCurve->getChannels().size() >= 2)
    mpObjectYone = dynamic_cast<const CDataObject*>(pDataModel->getObject(pCurve->getChannels()[1]));

  if (pCurve->getChannels().size() >= 3)
    {
      mpObjectYtwo = dynamic_cast<const CDataObject*>(pDataModel->getObject(pCurve->getChannels()[2]));

      if ((mpObjectYtwo->getObjectDisplayName() == "(CN)Root") && mpObjectYone)
        mpObjectYtwo = mpObjectYone;  // as long as we haven't a second Y-axis chooser, this has to suffice.
    }

  if (mpObjectX)
    mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
  else
    mpEditX->clear();

  if (mpObjectYone)
    mpEditYone->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()));
  else
    mpEditYone->clear();

  if (mpObjectYtwo)
    mpEditYtwo->setText(FROM_UTF8(mpObjectYtwo->getObjectDisplayName()));
  else
    mpEditYtwo->clear();

  mpCheckBefore->setChecked(pCurve->getActivity() & COutputInterface::BEFORE);
  mpCheckDuring->setChecked(pCurve->getActivity() & COutputInterface::DURING);
  mpCheckAfter->setChecked(pCurve->getActivity() & COutputInterface::AFTER);

  return true;
}

bool
BandedGraphWidget::SaveToCurveSpec(CPlotItem * curve, const CPlotItem *original /*= NULL*/) const
{
  //curve->setType(CPlotItem::bandedGraph);

  std::string title = TO_UTF8(mpEditTitle->text());

  CCommonName xName = mpObjectX ? mpObjectX->getCN() : CCommonName("");
  CCommonName yName1 = mpObjectYone ? mpObjectYone->getCN() : CCommonName("");
  CCommonName yName2 = mpObjectYtwo ? mpObjectYtwo->getCN() : (mpObjectYone ? mpObjectYone->getCN() : CCommonName(""));

  C_INT32 Activity = 0;

  if (mpCheckBefore->isChecked()) Activity += COutputInterface::BEFORE;

  if (mpCheckDuring->isChecked()) Activity += COutputInterface::DURING;

  if (mpCheckAfter->isChecked()) Activity += COutputInterface::AFTER;

  bool thingsChanged = false;

  if (original != NULL)
    {
      // compare whether things changed
      if (original->getTitle() != title)
        thingsChanged = true;

      if (thingsChanged || original->getType() != CPlotItem::bandedGraph)
        thingsChanged = true;

      if (thingsChanged || original->getActivity() != Activity)
        thingsChanged = true;

      if (thingsChanged || original->getChannels().size() != 3)
        thingsChanged = true;

      if (thingsChanged || original->getChannels()[0] != xName)
        thingsChanged = true;

      if (thingsChanged || original->getChannels()[1] != yName1)
        thingsChanged = true;

      if (thingsChanged || original->getChannels()[2] != yName2)
        thingsChanged = true;
    }
  else thingsChanged = true;

  if (!thingsChanged)
    return false;

  //title
  curve->setTitle(title);

  //channels
  curve->getChannels().clear();
  curve->getChannels().push_back(CPlotDataChannelSpec(xName));
  curve->getChannels().push_back(CPlotDataChannelSpec(yName1));
  curve->getChannels().push_back(CPlotDataChannelSpec(yName2));

  curve->setActivity((COutputInterface::Activity) Activity);

  return true;
}

void
BandedGraphWidget::buttonPressedX()
{
  if (!mpModel) return;

  mpObjectX = CCopasiSelectionDialog::getObjectSingle(this,
              CQSimpleSelectionTree::NumericValues,
              mpObjectX);

  if (mpObjectX)
    {
      mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));

      if (mpObjectYone)
        if (mpObjectYtwo && (mpObjectYtwo != mpObjectYone))
          mpEditTitle->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()
                                         + "/"
                                         + mpObjectYtwo->getObjectDisplayName()
                                         + "|"
                                         + mpObjectX->getObjectDisplayName()));
        else
          mpEditTitle->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()
                                         + "|"
                                         + mpObjectX->getObjectDisplayName()));

      //TODO update tab title
    }
  else
    mpEditX->setText("");
}

void
BandedGraphWidget::buttonPressedYone()
{
  if (!mpModel) return;

  mpObjectYone = CCopasiSelectionDialog::getObjectSingle(this,
                 CQSimpleSelectionTree::NumericValues,
                 mpObjectYone);

  if (mpObjectYone)
    {
      mpEditYone->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()));

      if (mpObjectX)
        if (mpObjectYtwo && (mpObjectYtwo != mpObjectYone))
          mpEditTitle->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()
                                         + "/"
                                         + mpObjectYtwo->getObjectDisplayName()
                                         + "|"
                                         + mpObjectX->getObjectDisplayName()));
        else
          mpEditTitle->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()
                                         + "|"
                                         + mpObjectX->getObjectDisplayName()));

      //TODO update tab title
    }
  else
    mpEditYone->setText("");
}

void
BandedGraphWidget::buttonPressedYtwo()
{
  if (!mpModel) return;

  mpObjectYtwo = CCopasiSelectionDialog::getObjectSingle(this,
                 CQSimpleSelectionTree::NumericValues,
                 mpObjectYtwo);

  if (mpObjectYtwo)
    {
      mpEditYtwo->setText(FROM_UTF8(mpObjectYtwo->getObjectDisplayName()));

      if (mpObjectX)
        if (mpObjectYone && (mpObjectYone != mpObjectYtwo))
          mpEditTitle->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()
                                         + "/"
                                         + mpObjectYtwo->getObjectDisplayName()
                                         + "|"
                                         + mpObjectX->getObjectDisplayName()));
        else
          mpEditTitle->setText(FROM_UTF8(mpObjectYtwo->getObjectDisplayName()
                                         + "|"
                                         + mpObjectX->getObjectDisplayName()));

      //TODO update tab title
    }
  else
    mpEditYtwo->setText("");
}
