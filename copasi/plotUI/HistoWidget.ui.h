// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/Attic/HistoWidget.ui.h,v $
//   $Revision: 1.11 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2007/03/13 19:59:11 $
// End CVS Header

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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

#include "copasi.h"

#include "plot/CPlotItem.h"

#include "report/CCopasiContainer.h"
#include "UI/CCopasiSelectionDialog.h"
#include "UI/qtUtilities.h"

void HistoWidget::buttonPressedX()
{
  if (!mpModel) return;
  mpObjectX = CCopasiSelectionDialog::getObjectSingle(this, CCopasiSimpleSelectionTree::NUMERIC, mpObjectX);

  if (mpObjectX)
    {
      lineEditXName->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
      lineEditTitle->setText("Histogram: " + FROM_UTF8(mpObjectX->getObjectDisplayName()));
    }
  else
    {
      lineEditXName->setText("");
      lineEditTitle->setText("Histogram");
    }
}

bool HistoWidget::LoadFromCurveSpec(const CPlotItem * curve)
{
  if (!curve) return false;

  if (curve->getType() != CPlotItem::histoItem1d) return false;
  if (curve->getChannels().size() != 1) return false;

  //title
  lineEditTitle->setText(FROM_UTF8(curve->getTitle()));

  //variable
  mpObjectX = NULL;

  if (curve->getChannels().size() >= 1)
    mpObjectX = CCopasiContainer::ObjectFromName(curve->getChannels()[0]);

  if (mpObjectX)
    lineEditXName->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));

  //other parameters:
  const void* tmp;
  if (!(tmp = curve->getValue("increment").pVOID)) return false;
  lineEditInc->setText(QString::number(*(const C_FLOAT64*)tmp));

  mpCheckBefore->setChecked(curve->getActivity() & COutputInterface::BEFORE);
  mpCheckDuring->setChecked(curve->getActivity() & COutputInterface::DURING);
  mpCheckAfter->setChecked(curve->getActivity() & COutputInterface::AFTER);

  return true; //TODO
}

bool HistoWidget::SaveToCurveSpec(CPlotItem * curve) const
  {
    //title
    curve->setTitle((const char*)lineEditTitle->text().utf8());

    //channels
    curve->getChannels().clear();
    curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectX ? mpObjectX->getCN() : CCopasiObjectName("")));

    //other parameters: TODO
    curve->setValue("increment", lineEditInc->text().toDouble());

    C_INT32 Activity = 0;
    if (mpCheckBefore->isChecked()) Activity += COutputInterface::BEFORE;
    if (mpCheckDuring->isChecked()) Activity += COutputInterface::DURING;
    if (mpCheckAfter->isChecked()) Activity += COutputInterface::AFTER;
    curve->setActivity((COutputInterface::Activity) Activity);

    return true;
  }

void HistoWidget::setModel(const CModel * model)
{
  mpModel = model;
}
