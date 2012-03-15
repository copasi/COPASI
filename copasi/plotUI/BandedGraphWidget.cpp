// Begin CVS Header
//   $Source: /fs/turing/cvs/copasi_dev/copasi/plotUI/BandedGraphWidget.cpp,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: tjohann $
//   $Date: 2011/09/05 11:53:01 $
// End CVS Header

// Copyright (C) 2012 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#include "BandedGraphWidget.h"

#include "UI/CCopasiSelectionDialog.h"
#include "UI/qtUtilities.h"

#include "copasi.h"

#include "report/CCopasiRootContainer.h"
#include "plot/CPlotItem.h"
#include "resourcesUI/CQIconResource.h"

/*
 *  Constructs a BandedGraphWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
BandedGraphWidget::BandedGraphWidget(QWidget* parent, const char* /* name */, Qt::WindowFlags fl)
    : QWidget(parent, fl)
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
BandedGraphWidget::LoadFromCurveSpec(const CPlotItem * curve)
{
  if (!curve) return false;

  if (curve->getType() != CPlotItem::bandedGraph) return false;

  //if (curve->getChannels().getSize != 3) return false;

  mpEditTitle->setText(FROM_UTF8(curve->getTitle()));

  //TODO: check if objects exist....
  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CCopasiDataModel* pDataModel = (*CCopasiRootContainer::getDatamodelList())[0];
  assert(pDataModel != NULL);
  mpObjectX = mpObjectYone = mpObjectYtwo = NULL;

  if (curve->getChannels().size() >= 1)
    mpObjectX = pDataModel->getDataObject(curve->getChannels()[0]);

  if (curve->getChannels().size() >= 2)
    mpObjectYone = pDataModel->getDataObject(curve->getChannels()[1]);

  if (curve->getChannels().size() >= 3)
    {
      mpObjectYtwo = pDataModel->getDataObject(curve->getChannels()[2]);

      if ((mpObjectYtwo->getObjectDisplayName() == "(CN)Root") && mpObjectYone)
        mpObjectYtwo = mpObjectYone;  // as long as we haven't a second Y-axis chooser, this has to suffice.
    }

  if (mpObjectX)
    mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));

  if (mpObjectYone)
    mpEditYone->setText(FROM_UTF8(mpObjectYone->getObjectDisplayName()));

  if (mpObjectYtwo)
    mpEditYtwo->setText(FROM_UTF8(mpObjectYtwo->getObjectDisplayName()));


  const void* tmp;

  if (!(tmp = curve->getValue("Line type").pVOID)) return false;

  mpCheckBefore->setChecked(curve->getActivity() & COutputInterface::BEFORE);
  mpCheckDuring->setChecked(curve->getActivity() & COutputInterface::DURING);
  mpCheckAfter->setChecked(curve->getActivity() & COutputInterface::AFTER);

  return true;
}

bool
BandedGraphWidget::SaveToCurveSpec(CPlotItem * curve) const
{
  //title
  curve->setTitle(TO_UTF8(mpEditTitle->text()));

  //channels
  curve->getChannels().clear();
  curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectX ? mpObjectX->getCN() : CCopasiObjectName("")));
  curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectYone ? mpObjectYone->getCN() : CCopasiObjectName("")));
  curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectYtwo ? mpObjectYtwo->getCN() : (mpObjectYone ? mpObjectYone->getCN() : CCopasiObjectName(""))));

  C_INT32 Activity = 0;

  if (mpCheckBefore->isChecked()) Activity += COutputInterface::BEFORE;

  if (mpCheckDuring->isChecked()) Activity += COutputInterface::DURING;

  if (mpCheckAfter->isChecked()) Activity += COutputInterface::AFTER;

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

void
BandedGraphWidget::setModel(const CModel * model)
{
  mpModel = model;
}

