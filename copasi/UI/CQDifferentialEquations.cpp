// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
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

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "CQDifferentialEquations.h"

#include <QtCore/QVariant>
#include <QPainter>
#include <QPrinter>

#include "CQDifferentialEquations.h"

#include <sstream>
#include <set>
#include <vector>

#include <QMessageBox>
#include <QRegExp>

#ifdef HAVE_MML
# include <qtmmlwidget.h>
#endif // HAVE_MML

#include "copasi/model/CMMLOutput.h"
#include "copasi/CopasiDataModel/CDataModel.h"
#include "qtUtilities.h"
#include "copasi/utilities/utility.h"
#include "copasi/tex/CMathMLToTeX.h"
#include "copasi/core/CRootContainer.h"
#include "copasi/commandline/CLocaleString.h"

#include "CopasiFileDialog.h"

#ifdef DEBUG_UI
#include <QtCore/QtDebug>
#endif

/*
 *  Constructs a CQDifferentialEquations which is a child of 'parent', with the
 *  name 'name'.'
 */
CQDifferentialEquations::CQDifferentialEquations(QWidget* parent, const char* name)
  : CopasiWidget(parent, name)
{
  setupUi(this);

#ifdef WIN32
  // on windows there ought to be a border around the MML widget
  // otherwise it is difficult to distinguish the formula from the rest of the
  // dialog
  mpScrollView->setFrameShape(QFrame::Panel);
  mpScrollView->setFrameStyle(QFrame::Panel | QFrame::Plain);
#endif

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQDifferentialEquations::~CQDifferentialEquations()
{
  // no need to delete child widgets, Qt does it all for us
}

void CQDifferentialEquations::init()
{
  comboBoxFunctions->setCurrentIndex(1);
}

void CQDifferentialEquations::saveMML(const QString& outfilename)
{
  std::ofstream ofile;
  ofile.open(CLocaleString::fromUtf8(TO_UTF8(outfilename)).c_str(), std::ios::trunc);

  ofile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
  ofile << "<!DOCTYPE math PUBLIC \"-//W3C//DTD MathML 2.0//EN\" \"http://www.w3.org/Math/DTD/mathml2/mathml2.dtd\">" << std::endl;
  ofile << "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">" << std::endl;

  ofile << mml.str();

  ofile << "</math>" << std::endl;

  ofile.close();
}

void CQDifferentialEquations::slotUpdateWidget()
{
  bool hasContents = true;
  //std::ostringstream mml;
  mml.str("");

  bool expand, expandAll;

  switch (comboBoxFunctions->currentIndex())
    {
      case 0:
        expand = false;
        expandAll = false;
        break;

      case 1:
        expand = true;
        expandAll = false;
        break;

      default:
        expand = true;
        expandAll = true;
        break;
    };

  bool parameterAsNumbers = false;

  if (comboBoxParameters->currentIndex() == 0)
    parameterAsNumbers = true;

  assert(mpDataModel != NULL);
  CMMLOutput::writeDifferentialEquations(mml, mpDataModel->getModel(), parameterAsNumbers, expand, expandAll);

  QWidget* tmp = dynamic_cast<QWidget*>(parent());

  if (tmp) tmp->setCursor(Qt::WaitCursor);

  mpMMLWidget->setContent(FROM_UTF8(mml.str()));
  mpMMLWidget->setBaseFontPointSize(qApp->font().pointSize());
  mpMMLWidget->setFontName(QtMmlWidget::NormalFont, qApp->font().family());
  mpMMLWidget->setFixedSize(mpMMLWidget->sizeHint().expandedTo(QSize(0, 0)));

  if (tmp) tmp->unsetCursor();

  mpSaveButton->setEnabled(hasContents);
}

bool CQDifferentialEquations::enterProtected()
{
  slotUpdateWidget();
  return true;
}

void CQDifferentialEquations::newFunction()
{}

void CQDifferentialEquations::saveTeX(const QString& outfilename)
{
  QString latexStr(FROM_UTF8(mml.str()));

#ifdef DEBUG_UI
  qDebug() << latexStr;
#endif

  CMathMLToTeX::convert(latexStr);

  std::ofstream ofile;
  ofile.open(CLocaleString::fromUtf8(TO_UTF8(outfilename)).c_str(), std::ios::trunc);
  ofile << TO_UTF8(latexStr);
  ofile.close();
}

void CQDifferentialEquations::savePDF(const QString& outfilename)
{
  QtMmlDocument doc;
  doc.setBaseFontPointSize(20);
  doc.setFontName(QtMmlWidget::NormalFont, qApp->font().family());
  doc.setContent(FROM_UTF8(mml.str()));

  const QSize &size = doc.size();
  QPrinter printer(QPrinter::ScreenResolution);
  QPainter painter;
  printer.setOutputFormat(QPrinter::PdfFormat);
  printer.setOutputFileName(outfilename);
#if QT_VERSION < QT_VERSION_CHECK(5,15,0)
  printer.setPaperSize(QSizeF(size.width(), size.height()), QPrinter::Point);
#else
  printer.setPageSize(QPageSize(QSizeF(size.width(), size.height()), QPageSize::Point));
#endif
  painter.setRenderHints(
    QPainter::Antialiasing | QPainter::SmoothPixmapTransform);
  painter.begin(&printer);
  doc.paint(&painter, QPoint(0, 0));
  painter.end();
}

void CQDifferentialEquations::savePNG(const QString& outfilename)
{
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

void CQDifferentialEquations::slotSave()
{
  QString outfilename;
  QString filter;

  C_INT32 Answer = QMessageBox::No;

  while (Answer == QMessageBox::No)
    {
      outfilename =
        CopasiFileDialog::getSaveFileName(this,
                                          "Save File Dialog",
                                          CopasiFileDialog::getDefaultFileName(".mml"),
                                          "MathML (*.mml);;TeX (*.tex);;PDF (*.pdf);;PNG (*.png)",
                                          "Save Formula to Disk", &filter);

      if (outfilename.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(this, outfilename);

      if (Answer == QMessageBox::Cancel)
        return;
    }

#ifdef DEBUG_UI
  qDebug() << "outfilename = " << outfilename;
#endif

  QApplication::setOverrideCursor(Qt::WaitCursor);

  if (filter.contains(".tex"))
    {
      saveTeX(outfilename);
    }
  else if (filter.contains(".png"))
    {
      savePNG(outfilename);
    }
  else if (filter.contains(".pdf"))
    {
      savePDF(outfilename);
    }
  else
    {
      saveMML(outfilename);
    }

  QApplication::restoreOverrideCursor();
}
