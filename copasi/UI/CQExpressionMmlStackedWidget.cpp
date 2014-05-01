// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQExpressionMmlStackedWidget.h"

#include <QtCore/QString>
#include <QtGui/QPainter>

#include "utilities/CCopasiException.h"

#include "CQMessageBox.h"
#include "qtUtilities.h" // for UTF8
#include "CopasiFileDialog.h"
#include "tex/CMathMLToTeX.h"
#include "commandline/CLocaleString.h"
#include "resourcesUI/CQIconResource.h"

#include <utilities/CCopasiMessage.h>
// turns out that the fatalError definition in copasi message is incompatible
// with the mml widget
#undef fatalError

#ifdef HAVE_MML
# include <qtmmlwidget.h>
#endif // HAVE_MML

#ifdef DEBUG_UI
#include <QtCoe/QtDebug>
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

  mpMmlScrollView->setStyleSheet(QString(mpMmlScrollView->widget()->metaObject()->className()) + "{background-color:" + QColor(Qt::white).name() + ";}");

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
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->text() = " << mpExpressionWidget->text();
#endif

  setCurrentWidget(mpExpressionPage);

#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->text() = " << mpExpressionWidget->text();
  qDebug() << "L" << __LINE__ << " on CQEMSW: activeWidget NEW = " << currentIndex();
#endif
}

void CQExpressionMmlStackedWidget::slotGoMmlWidget()
{
#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->text() = " << mpExpressionWidget->text();
#endif

  setCurrentWidget(mpMmlPage);

#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->text() = " << mpExpressionWidget->text();
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
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->text() = " << mpExpressionWidget->text();
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

void CQExpressionMmlStackedWidget::init()
{
#ifdef DEBUG_UI
  qDebug() << "L" << __LINE__ << " on CQEMSW mpExpressionWidget->text() = " << mpExpressionWidget->text();
  qDebug() << "L" << __LINE__ << " on CQEMSW: activeWidget = " << currentIndex();
#endif

#ifndef HAVE_MML
  mpBtnViewExpression->hide();
#endif // not HAVE_MML
}

void CQExpressionMmlStackedWidget::slotSaveExpression()
{
  QString *filter = new QString;
  QString outfilename;

  C_INT32 Answer = QMessageBox::No;

  while (Answer == QMessageBox::No)
    {
      outfilename =
        CopasiFileDialog::getSaveFileName(this,
                                          "Save File Dialog",
                                          "untitled.mml",
                                          "MathML (*.mml);;TeX (*.tex);;PNG (*.png)",
//                                          "Save Expression to Disk", new QString);
                                          "Save Expression to Disk", filter);

      if (outfilename.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(outfilename);

      if (Answer == QMessageBox::Cancel)
        return;
    }

#ifdef DEBUG_UI
  qDebug() << "\non CQEMSW::slotSaveExpression -> filter = " << *filter << "\n";
#endif

  if (filter->contains(".tex"))
    saveTeX(outfilename);
  else if (filter->contains(".png"))
    savePNG(outfilename);
  else
    saveMML(outfilename);
}

void CQExpressionMmlStackedWidget::savePNG(const QString outfilename)
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
  painter.setRenderHint(QPainter::HighQualityAntialiasing);
  painter.fillRect(0, 0, size.width(), size.height(), Qt::white);
  doc.paint(&painter, QPoint(0, 0));
  pixmap.save(outfilename, "PNG");
}

void CQExpressionMmlStackedWidget::saveMML(const QString outfilename)
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

void CQExpressionMmlStackedWidget::saveTeX(const QString outfilename)
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
