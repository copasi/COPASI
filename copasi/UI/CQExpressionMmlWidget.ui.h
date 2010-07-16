// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExpressionMmlWidget.ui.h,v $
//   $Revision: 1.14 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2010/07/16 19:05:17 $
// End CVS Header

// Copyright (C) 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

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

#include "CQMessageBox.h"

// #ifdef HAVE_MML
// # include "mml/qtmmlwidget.h"
// #endif // HAVE_MML

#include "qtUtilities.h" // for UTF8

#include "CopasiFileDialog.h"

#include "tex/CMathMLToTeX.h"

void CQExpressionMmlWidget::slotGoExpressionWidget()
{
  mpWidgetStackExpressionMml->raiseWidget(mpExpressionPage);
}

void CQExpressionMmlWidget::slotGoMmlWidget()
{
  mpWidgetStackExpressionMml->raiseWidget(mpMmlPage);
}

void CQExpressionMmlWidget::updateWidget()
{
#ifdef HAVE_MML

  std::ostringstream mml;
  std::vector<std::vector<std::string> > params;

  if (mpExpressionWidget->text().isEmpty() ||
      !mpExpressionWidget->isValid())
    mpWidgetStackExpressionMml->raiseWidget(mpExpressionPage);
  else
    {
      mpExpressionWidget->mpValidatorExpression->getExpression()->writeMathML(mml, false, 0);
      mpWidgetStackExpressionMml->raiseWidget(mpMmlPage);
    }

  /*
    mpMmlScrollView->mpMmlWidget->setContent(FROM_UTF8(mml.str()));
    mpMmlScrollView->resizeContents(mpMmlScrollView->mpMmlWidget->sizeHint().width(), mpMmlScrollView->mpMmlWidget->sizeHint().height());
    mpMmlScrollView->setMinimumHeight(mpMmlScrollView->mpMmlWidget->sizeHint().height() + 30);
  */
  mpMmlScrollView->updateWidget(mml);

  MMLStr = FROM_UTF8(mml.str());

#endif /* HAVE_MML */
}

void CQExpressionMmlWidget::init()
{
  //  mpBtnViewExpression->setEnabled(FALSE);
#ifndef HAVE_MML
  mpBtnViewExpression->hide();
#endif // not HAVE_MML
}

// add 22.07.08
void CQExpressionMmlWidget::slotSaveExpression()
{
  QString filter;
  QString outfilename;

  C_INT32 Answer = QMessageBox::No;

  while (Answer == QMessageBox::No)
    {
      outfilename =
        CopasiFileDialog::getSaveFileName(this,
                                          "Save File Dialog",
                                          "untitled.mml",
                                          "MathML (*.mml);;TeX (*.tex)",
                                          "Save Expression to Disk", new QString);

      if (outfilename.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(outfilename);

      if (Answer == QMessageBox::Cancel)
        return;
    }

  if (filter.contains("tex"))
    saveTeX(outfilename);
  else
    saveMML(outfilename);
}

void CQExpressionMmlWidget::saveMML(const QString outfilename)
{
  std::ofstream ofile;
  ofile.open(utf8ToLocale(TO_UTF8(outfilename)).c_str(), std::ios::trunc);

  ofile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
  ofile << "<!DOCTYPE math PUBLIC \"-//W3C//DTD MathML 2.0//EN\" \"http://www.w3.org/Math/DTD/mathml2/mathml2.dtd\">" << std::endl;
  ofile << "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">" << std::endl;

  //  ofile << mml.str();
  mpExpressionWidget->mpValidatorExpression->getExpression()->writeMathML(ofile, false, 0);

  ofile << "</math>" << std::endl;

  ofile.close();
}

void CQExpressionMmlWidget::saveTeX(const QString outfilename)
{
  std::ostringstream mml;
  mpExpressionWidget->mpValidatorExpression->getExpression()->writeMathML(mml, false, 0);

  QString latexStr(FROM_UTF8(mml.str()));

  CMathMLToTeX::convert(latexStr);

  std::ofstream ofile;
  ofile.open(utf8ToLocale(TO_UTF8(outfilename)).c_str(), std::ios::trunc);

  ofile << TO_UTF8(latexStr);

  ofile.close();
}
