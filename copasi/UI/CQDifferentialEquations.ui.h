// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQDifferentialEquations.ui.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: ssahle $
//   $Date: 2007/08/05 10:00:19 $
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

//#include <sstream>
#include <model/CMMLOutput.h>
#include <CopasiDataModel/CCopasiDataModel.h>
#include "qtUtilities.h"
#include "utilities/utility.h"

#ifdef HAVE_MML
# include "mml/qtmmlwidget.h"
#endif // Have_MML

#include "CopasiFileDialog.h"
#include <qmessagebox.h>
#include <qregexp.h>

void CQDifferentialEquations::init()
{
  mpScrollView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mpScrollView->setResizePolicy(QScrollView::AutoOneFit);

  mpMMLWidget = new QtMmlWidget(mpScrollView->viewport());
  mpMMLWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mpMMLWidget->setBaseFontPointSize(this->fontInfo().pointSize());
  mpMMLWidget->setFontName(QtMmlWidget::NormalFont, this->fontInfo().family());
  mpMMLWidget->show();

  mpScrollView->addChild(mpMMLWidget);
}

void CQDifferentialEquations::slotSaveMML()
{
  QString outfilename;

  C_INT32 Answer = QMessageBox::No;

  while (Answer == QMessageBox::No)
    {
      outfilename =
        CopasiFileDialog::getSaveFileName(this,
                                          "Save File Dialog",
                                          QString::null,
                                          "MathML (*.mml);;XML (*.xml);;All Files (*);;",
                                          "Save Differential Equations to MathML File");

      if (!outfilename) return;

      if (!outfilename.endsWith(".mml") &&
          !outfilename.endsWith(".xml") &&
          !outfilename.endsWith("."))
        outfilename += ".mml";

      outfilename = outfilename.remove(QRegExp("\\.$"));

      Answer = checkSelection(outfilename);

      if (Answer == QMessageBox::Cancel)
        return;
    }

  std::ofstream ofile;
  ofile.open(utf8ToLocale((const char *)outfilename.utf8()).c_str(), std::ios::trunc);
  ofile << mml.str();

  ofile.close();
}

void CQDifferentialEquations::slotUpdateWidget()
{
  bool hasContents = true;
  //std::ostringstream mml;
  mml.str("");

  CMMLOutput::writeDifferentialEquations(mml, CCopasiDataModel::Global->getModel(), true, true, false);

  QWidget* tmp = dynamic_cast<QWidget*>(parent());
  if (tmp) tmp->setCursor(Qt::WaitCursor);

  mpMMLWidget->setContent(FROM_UTF8(mml.str()));
  mpScrollView->resizeContents(mpMMLWidget->sizeHint().width(), mpMMLWidget->sizeHint().height());
  //std::cout << mml.str() << std::endl;

  if (tmp) tmp->unsetCursor();

  mpSaveButton->setEnabled(hasContents);
}

bool CQDifferentialEquations::enter(const std::string &)
{
  slotUpdateWidget();
  return true;
}

void CQDifferentialEquations::newFunction()
{
}
