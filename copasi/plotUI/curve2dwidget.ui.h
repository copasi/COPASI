// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plotUI/Attic/curve2dwidget.ui.h,v $
//   $Revision: 1.21 $
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
 ** If you wish to add, delete or rename functions or slots use
 ** Qt Designer which will update this file, preserving your code. Create an
 ** init() function in place of a constructor, and a destroy() function in
 ** place of a destructor.
 *****************************************************************************/
#include "copasi.h"

#include "plot/CPlotItem.h"

#include "report/CCopasiContainer.h"
#include "UI/CCopasiSelectionDialog.h"
#include "UI/qtUtilities.h"

// mpBoxType lines|points|symbols

bool Curve2DWidget::LoadFromCurveSpec(const CPlotItem * curve)
{
  if (!curve) return false;

  if (curve->getType() != CPlotItem::curve2d) return false;
  //if (curve->getChannels().getSize != 2) return false;

  mpEditTitle->setText(FROM_UTF8(curve->getTitle()));

  //TODO: check if objects exist....

  mpObjectX = mpObjectY = NULL;
  if (curve->getChannels().size() >= 1)
    mpObjectX = CCopasiContainer::ObjectFromName(curve->getChannels()[0]);
  if (curve->getChannels().size() >= 2)
    mpObjectY = CCopasiContainer::ObjectFromName(curve->getChannels()[1]);

  if (mpObjectX)
    mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));
  if (mpObjectY)
    mpEditY->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()));

  const void* tmp;

  if (!(tmp = curve->getValue("Line type").pVOID)) return false;
  mpBoxType->setCurrentItem(*(unsigned C_INT32*)tmp);

  mpCheckBefore->setChecked(curve->getActivity() & COutputInterface::BEFORE);
  mpCheckDuring->setChecked(curve->getActivity() & COutputInterface::DURING);
  mpCheckAfter->setChecked(curve->getActivity() & COutputInterface::AFTER);

  //for debugging:
  //  std::cout << "Curve2DWidget::LoadFromCurveSpec:" << std::endl;
  //  std::cout << "  title: " << curve->title << std::endl;
  //  std::cout << "  " << curve->mChannels.size() << "  " << curve->mChannels[0].object << "  " << curve->mChannels[1].object << std::endl;

  //  std::string sss = CCopasiContainer::ObjectFromName(ListOfContainer, curve->mChannels[0].object)->getObjectUniqueName().c_str();
  //  std::cout << "uni : " << sss << " *** " << std::endl;

  return true; //TODO
}

bool Curve2DWidget::SaveToCurveSpec(CPlotItem * curve) const
  {
    //if (!(mpObjectX && mpObjectY)) return false;

    //title
    curve->setTitle((const char*)mpEditTitle->text().utf8());

    //channels
    curve->getChannels().clear();
    curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectX ? mpObjectX->getCN() : CCopasiObjectName("")));
    curve->getChannels().push_back(CPlotDataChannelSpec(mpObjectY ? mpObjectY->getCN() : CCopasiObjectName("")));

    curve->setValue("Line type", (unsigned C_INT32)mpBoxType->currentItem());

    C_INT32 Activity = 0;
    if (mpCheckBefore->isChecked()) Activity += COutputInterface::BEFORE;
    if (mpCheckDuring->isChecked()) Activity += COutputInterface::DURING;
    if (mpCheckAfter->isChecked()) Activity += COutputInterface::AFTER;
    curve->setActivity((COutputInterface::Activity) Activity);

    return true;
  }

void Curve2DWidget::buttonPressedX()
{
  if (!mpModel) return;

  mpObjectX = CCopasiSelectionDialog::getObjectSingle(this, CCopasiSimpleSelectionTree::NUMERIC, mpObjectX);

  if (mpObjectX)
    {
      mpEditX->setText(FROM_UTF8(mpObjectX->getObjectDisplayName()));

      if (mpObjectY)
        mpEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                       + "|"
                                       + mpObjectX->getObjectDisplayName()));
      //TODO update tab title
    }
  else
    mpEditX->setText("");
}

void Curve2DWidget::buttonPressedY()
{
  if (!mpModel) return;

  mpObjectY = CCopasiSelectionDialog::getObjectSingle(this, CCopasiSimpleSelectionTree::NUMERIC, mpObjectY);

  if (mpObjectY)
    {
      mpEditY->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()));

      if (mpObjectX)
        mpEditTitle->setText(FROM_UTF8(mpObjectY->getObjectDisplayName()
                                       + "|"
                                       + mpObjectX->getObjectDisplayName()));
      //TODO update tab title
    }
  else
    mpEditY->setText("");
}

void Curve2DWidget::setModel(const CModel * model)
{
  mpModel = model;
}
