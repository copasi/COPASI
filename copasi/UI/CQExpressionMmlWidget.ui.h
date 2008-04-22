// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExpressionMmlWidget.ui.h,v $
//   $Revision: 1.2 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2008/04/22 11:06:48 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
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

#include "qtUtilities.h" // for UTF8

void CQExpressionMmlWidget::slotGoExpressionWidget()
{
  std::cout << "CQEMW::slotGoExpressionWidget(): mpExpressionWidget->text() = "
  << mpExpressionWidget->text() << std::endl;
  mpWidgetStackExpressionMml->raiseWidget(mpExpressionPage);
  /*  std::ostringstream mml;
    std::vector<std::vector<std::string> > params;

    if (mpExpressionWidget->text().isEmpty())
      mpWidgetStackExpressionMml->raiseWidget(mpExpressionPage);
    else
    {
  //    ExpressionPage->mp
      mpWidgetStackExpressionMml->raiseWidget(mpMmlPage);
    }
  */
}

void CQExpressionMmlWidget::slotGoMmlWidget()
{
  std::cout << "CQEMW::slotGoMmlWidget()" << std::endl;
  mpWidgetStackExpressionMml->raiseWidget(mpMmlPage);
}

void CQExpressionMmlWidget::updateWidget()
{
#ifdef HAVE_MML

  // Since the mathematical  expression is already validated, then we can go easily further

  std::ostringstream mml;
  std::vector<std::vector<std::string> > params;

  if (mpExpressionWidget->text().isEmpty())
    mpWidgetStackExpressionMml->raiseWidget(mpExpressionPage);
  else
    {
      mpExpressionWidget->mpValidator->getExpression()->writeMathML(mml, false, 0);
      mpWidgetStackExpressionMml->raiseWidget(mpMmlPage);
    }

  /*
    mpMmlScrollView->mpMmlWidget->setContent(FROM_UTF8(mml.str()));
    mpMmlScrollView->resizeContents(mpMmlScrollView->mpMmlWidget->sizeHint().width(), mpMmlScrollView->mpMmlWidget->sizeHint().height());
    mpMmlScrollView->setMinimumHeight(mpMmlScrollView->mpMmlWidget->sizeHint().height() + 30);
  */
  mpMmlScrollView->updateWidget(mml);

#endif /* HAVE_MML */
}
