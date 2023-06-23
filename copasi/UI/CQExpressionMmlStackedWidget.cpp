// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQExpressionMmlStackedWidget.h"

#include <QtCore/QString>
#include <QPainter>
#include <QPrinter>

#include "copasi/utilities/CCopasiException.h"

#include "CQMessageBox.h"
#include "qtUtilities.h" // for UTF8
#include "CopasiFileDialog.h"
#include "copasi/tex/CMathMLToTeX.h"
#include "copasi/commandline/CLocaleString.h"
#include "copasi/resourcesUI/CQIconResource.h"

#include <fstream>

#include <copasi/utilities/CCopasiMessage.h>
// turns out that the fatalError definition in copasi message is incompatible
// with the mml widget
#undef fatalError

#ifdef HAVE_MML
# include <qtmmlwidget.h>
#endif // HAVE_MML

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

/*
 *  Constructs a CQExpressionMmlStackedWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CQExpressionMmlStackedWidget::CQExpressionMmlStackedWidget(QWidget* parent)
  : QStackedWidget(parent)
{
  setupUi(this);

  mpBtnExpressionObject->setIcon(CQIconResource::icon(CQIconResource::copasi));
  mpBtnViewExpression->setIcon(CQIconResource::icon(CQIconResource::renderMathML));
  mpBtnEditExpression->setIcon(CQIconResource::icon(CQIconResource::edit));
  mpBtnSaveExpression->setIcon(CQIconResource::icon(CQIconResource::fileExport));

#ifdef WIN32
  // on windows there ought to be a border around the MML widget
  // otherwise it is difficult to distinguish the formula from the rest of the
  // dialog
  mpMmlScrollView->setFrameShape(QFrame::Panel);
  mpMmlScrollView->setFrameStyle(QFrame::Panel | QFrame::Plain);
#endif

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQExpressionMmlStackedWidget::~CQExpressionMmlStackedWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQExpressionMmlStackedWidget::slotGoExpressionWidget()
{
#ifdef DEBUG_UI
  qDebug() << "- here on CQExpressionMmlStackedWidget::slotGoExpressionWidget() -";
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->getExpression() = " << mpExpressionWidget->getExpression().c_str();
#endif

  setCurrentWidget(mpExpressionPage);

#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->getExpression() = " << mpExpressionWidget->getExpression().c_str();;
  qDebug() << "L" << __LINE__ << " on CQEMSW: activeWidget NEW = " << currentIndex();
#endif
}

void CQExpressionMmlStackedWidget::slotGoMmlWidget()
{
#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->getExpression() = " << mpExpressionWidget->getExpression().c_str();;
#endif

  setCurrentWidget(mpMmlPage);

#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->getExpression() = " << mpExpressionWidget->getExpression().c_str();;
  qDebug() << "L" << __LINE__ << " on CQEMSW: activeWidget NEW = " << currentIndex();
#endif
}

void CQExpressionMmlStackedWidget::updateWidget()
{
#ifdef DEBUG_UI
  qDebug() << "- here on CQExpressionMmlStackedWidget::updateWidget() -";
#endif

#ifdef HAVE_MML

  std::ostringstream mml;
  std::vector<std::vector<std::string> > params;

#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->getExpression() = " << mpExpressionWidget->getExpression().c_str();;
  qDebug() << "L" << __LINE__ << " on CQEMSW: activeWidget NEW = " << currentIndex();
#endif

  if (mpExpressionWidget->toPlainText().isEmpty() || !mpExpressionWidget->isValid())
    setCurrentWidget(mpExpressionPage);
  else
    {
      mpExpressionWidget->writeMathML(mml);

#ifdef DEBUG_UI
      qDebug() << "mml.str() = " << FROM_UTF8(mml.str());
#endif

      setCurrentWidget(mpMmlPage);
      mpMmlScrollView->updateWidget(mml);
    }

#endif /* HAVE_MML */

#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEMSW: activeWidget = " << currentIndex();
#endif
}

void CQExpressionMmlStackedWidget::setReadOnly(const bool & readOnly)
{
  if (readOnly)
    mpBtnEditExpression->hide();
  else
    mpBtnEditExpression->show();
}

QString CQExpressionMmlStackedWidget::getText()
{
  return mpExpressionWidget->toPlainText();
}

void CQExpressionMmlStackedWidget::reset()
{
  mpExpressionWidget->setExpression("");

  updateWidget();

}

void CQExpressionMmlStackedWidget::init()
{
#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->getExpression() = " << mpExpressionWidget->getExpression().c_str();;
  qDebug() << "L" << __LINE__ << " on CQEMSW: activeWidget = " << currentIndex();
#endif

#ifndef HAVE_MML
  mpBtnViewExpression->hide();
#endif // not HAVE_MML
}

void CQExpressionMmlStackedWidget::slotSaveExpression()
{
  QString filter;
  QString outfilename;

  C_INT32 Answer = QMessageBox::No;

  while (Answer == QMessageBox::No)
    {
      outfilename =
        CopasiFileDialog::getSaveFileName(this,
                                          "Save File Dialog",
                                          CopasiFileDialog::getDefaultFileName(".mml"),
                                          "MathML (*.mml);;TeX (*.tex);;PDF files (*.pdf);;PNG (*.png)",
//                                          "Save Expression to Disk", new QString);
                                          "Save Expression to Disk", &filter);

      if (outfilename.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, outfilename);

      if (Answer == QMessageBox::Cancel)
        return;
    }

#ifdef DEBUG_UI
  qDebug() << "\non CQEMSW::slotSaveExpression -> filter = " << filter << "\n";
#endif

  if (filter.contains(".tex"))
    saveTeX(outfilename);
  else if (filter.contains(".png"))
    savePNG(outfilename);
  else if (filter.contains(".pdf"))
    savePDF(outfilename);
  else
    saveMML(outfilename);
}

void CQExpressionMmlStackedWidget::savePDF(const QString& outfilename)
{
  std::ostringstream mml;
  mpExpressionWidget->writeMathML(mml);
  QtMmlDocument doc;
  doc.setBaseFontPointSize(20);
  doc.setFontName(QtMmlWidget::NormalFont, qApp->font().family());
  doc.setContent(FROM_UTF8(mml.str()));

  const QSize &size = doc.size();
  QPrinter printer(QPrinter::ScreenResolution);
  QPainter painter;
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOutputFileName(outfilename);
  painter.setRenderHints(
    QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
#if QT_VERSION < QT_VERSION_CHECK(5,15,0)
  printer.setPaperSize(QSizeF(size.width(), size.height()), QPrinter::Point);
#else
  printer.setPageSize(QPageSize(QSizeF(size.width(), size.height()), QPageSize::Point));
#endif

  painter.begin(&printer);
  doc.paint(&painter, QPoint(0, 0));
  painter.end();
}

void CQExpressionMmlStackedWidget::savePNG(const QString& outfilename)
{
  std::ostringstream mml;
  mpExpressionWidget->writeMathML(mml);
  QtMmlDocument doc;
  doc.setBaseFontPointSize(20);
  doc.setFontName(QtMmlWidget::NormalFont, qApp->font().family());
  doc.setContent(FROM_UTF8(mml.str()));

  const QSize &size = doc.size();
  QPixmap pixmap(size.width(), size.height());
  QPainter painter(&pixmap);
  painter.setRenderHint(QPainter::Antialiasing);
  painter.setRenderHint(QPainter::SmoothPixmapTransform);
  painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
  doc.paint(&painter, QPoint(0, 0));
  pixmap.save(outfilename, "PNG");
}

void CQExpressionMmlStackedWidget::saveMML(const QString& outfilename)
{
  std::ofstream ofile;
  ofile.open(CLocaleString::fromUtf8(TO_UTF8(outfilename)).c_str(), std::ios::trunc);

  ofile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
  ofile << "<!DOCTYPE math PUBLIC \"-//W3C//DTD MathML 2.0//EN\" \"http://www.w3.org/Math/DTD/mathml2/mathml2.dtd\">" << std::endl;
  ofile << "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">" << std::endl;

  mpExpressionWidget->writeMathML(ofile);

  ofile << "</math>" << std::endl;

  ofile.close();
}

void CQExpressionMmlStackedWidget::saveTeX(const QString& outfilename)
{
  std::ostringstream mml;
  mpExpressionWidget->writeMathML(mml);

  QString latexStr(FROM_UTF8(mml.str()));

  CMathMLToTeX::convert(latexStr);

  std::ofstream ofile;
  ofile.open(CLocaleString::fromUtf8(TO_UTF8(outfilename)).c_str(), std::ios::trunc);

  ofile << TO_UTF8(latexStr);

  ofile.close();
}
