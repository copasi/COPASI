// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CQDifferentialEquations.ui.h,v $
//   $Revision: 1.7.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/13 20:32:38 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
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
#include <sstream>
#include <set>
#include <vector>

#include <qmessagebox.h>
#include <qregexp.h>

#include "model/CMMLOutput.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "qtUtilities.h"
#include "utilities/utility.h"
#include "tex/CMathMLToTeX.h"

#ifdef HAVE_MML
# include "mml/qtmmlwidget.h"
#endif // HAVE_MML

#include "CopasiFileDialog.h"

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

  comboBoxFunctions->setCurrentItem(1);
}

void CQDifferentialEquations::saveMML(const QString outfilename)
{
  std::ofstream ofile;
  ofile.open(utf8ToLocale((const char *)outfilename.utf8()).c_str(), std::ios::trunc);

  ofile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
  ofile << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN\" \"HTMLFiles/xhtml-math11-f.dtd\">" << std::endl;
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
  switch (comboBoxFunctions->currentItem())
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
  if (comboBoxParameters->currentItem() == 0)
    parameterAsNumbers = true;

  CMMLOutput::writeDifferentialEquations(mml, CCopasiDataModel::Global->getModel(), parameterAsNumbers, expand, expandAll);

  QWidget* tmp = dynamic_cast<QWidget*>(parent());
  if (tmp) tmp->setCursor(Qt::WaitCursor);

  mpMMLWidget->setContent(FROM_UTF8(mml.str()));
  mpScrollView->resizeContents(mpMMLWidget->sizeHint().width(), mpMMLWidget->sizeHint().height());

  if (tmp) tmp->unsetCursor();

  mpSaveButton->setEnabled(hasContents);
}

bool CQDifferentialEquations::enter(const std::string &)
{
  slotUpdateWidget();
  return true;
}

void CQDifferentialEquations::newFunction()
{}

void CQDifferentialEquations::saveTeX(const QString outfilename)
{
  QString latexStr(FROM_UTF8(mml.str()));

  CMathMLToTeX::convert(latexStr);

  std::ofstream ofile;
  ofile.open(utf8ToLocale((const char *)outfilename.utf8()).c_str(), std::ios::trunc);
  ofile << latexStr;
  ofile.close();
}

void CQDifferentialEquations::slotSave()
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
            "Save Formula to Disk");

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
