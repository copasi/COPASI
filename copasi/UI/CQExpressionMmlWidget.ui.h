// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExpressionMmlWidget.ui.h,v $
//   $Revision: 1.6.2.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/13 20:32:38 $
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

#include "CQMessageBox.h"

#include "qtUtilities.h" // for UTF8

#include "CopasiFileDialog.h"

#ifdef HAVE_MML
# include "mml/qtmmlwidget.h"
#endif // HAVE_MML

#include "tex/CMathMLToTeX.h"

void CQExpressionMmlWidget::slotGoExpressionWidget()
{
  // std::cout << "CQEMW::slotGoExpressionWidget(): mpExpressionWidget->text() = " << mpExpressionWidget->text() << std::endl;
  mpWidgetStackExpressionMml->raiseWidget(mpExpressionPage);
}

void CQExpressionMmlWidget::slotGoMmlWidget()
{
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

  MMLStr = FROM_UTF8(mml.str());

#endif /* HAVE_MML */
}

void CQExpressionMmlWidget::init()
{
  //  mpBtnViewExpression->setEnabled(FALSE);
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
        CopasiFileDialog::getSaveFileNameAndFilter(filter,
            this,
            "Save File Dialog",
            QString::null,
            "MathML (*.mml);;XML (*.xml);;TeX (*.tex);;",
            "Save Expression to Disk");

      if (!outfilename) return;

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
  ofile.open(utf8ToLocale((const char *)outfilename.utf8()).c_str(), std::ios::trunc);

  ofile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
  ofile << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN\" \"HTMLFiles/xhtml-math11-f.dtd\">" << std::endl;
  ofile << "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">" << std::endl;

  //  ofile << mml.str();
  mpExpressionWidget->mpValidator->getExpression()->writeMathML(ofile, false, 0);

  ofile << "</math>" << std::endl;

  ofile.close();
}

void CQExpressionMmlWidget::saveTeX(const QString outfilename)
{
  std::ostringstream mml;
  mpExpressionWidget->mpValidator->getExpression()->writeMathML(mml, false, 0);

  QString latexStr(FROM_UTF8(mml.str()));

  CMathMLToTeX::convert(latexStr);

  std::ofstream ofile;
  ofile.open(utf8ToLocale((const char *)outfilename.utf8()).c_str(), std::ios::trunc);

  ofile << (const char *) latexStr.utf8();

  ofile.close();
}
