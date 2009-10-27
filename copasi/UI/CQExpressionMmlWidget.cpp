// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQExpressionMmlWidget.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/10/27 14:04:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQExpressionMmlWidget.h"

//#include <qvariant.h>
//#include "CQExpressionWidget.h"
#include "utilities/CCopasiException.h"
//#include "CQMmlScrollView.h"
//#include "CQExpressionMmlWidget.ui.h"

#include "CQMessageBox.h"
#include "qtUtilities.h" // for UTF8
#include "CopasiFileDialog.h"
#include "tex/CMathMLToTeX.h"

#include <QtDebug>

/*
 *  Constructs a CQExpressionMmlWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQExpressionMmlWidget::CQExpressionMmlWidget(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, name, fl)
{
  setupUi(this);

  const QIcon icon = qt_get_icon(image0_ID);
  mpBtnExpressionObject->setIcon(icon);

  const QIcon icon1 = qt_get_icon(image1_ID);
  mpBtnViewExpression->setIcon(icon1);

  const QIcon icon2 = qt_get_icon(image2_ID);
  mpBtnEditExpression->setIcon(icon2);

  const QIcon icon3 = qt_get_icon(image3_ID);
  mpBtnSaveExpression->setIcon(icon3);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQExpressionMmlWidget::~CQExpressionMmlWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQExpressionMmlWidget::languageChange()
{
  retranslateUi(this);
}

void CQExpressionMmlWidget::slotGoExpressionWidget()
{
  mpWidgetStackExpressionMml->setCurrentWidget(mpExpressionPage);
}

void CQExpressionMmlWidget::slotGoMmlWidget()
{
  mpWidgetStackExpressionMml->setCurrentWidget(mpMmlPage);
}

void CQExpressionMmlWidget::updateWidget()
{
#ifdef HAVE_MML
  std::ostringstream mml;
  std::vector<std::vector<std::string> > params;

  if (mpExpressionWidget->text().isEmpty() ||
      !mpExpressionWidget->isValid())
    mpWidgetStackExpressionMml->setCurrentWidget(mpExpressionPage);
  else
    {
      mpExpressionWidget->mpValidator->getExpression()->writeMathML(mml, false, 0);

      mpWidgetStackExpressionMml->setCurrentWidget(mpMmlPage);
      mpMmlScrollView->updateWidget(mml);
      MMLStr = FROM_UTF8(mml.str());
    }

#endif /* HAVE_MML */
}

void CQExpressionMmlWidget::init()
{
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
  ofile.open(utf8ToLocale(TO_UTF8(outfilename)).c_str(), std::ios::trunc);

  ofile << TO_UTF8(latexStr);

  ofile.close();
}
