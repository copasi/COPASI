// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQDifferentialEquations.cpp,v $
//   $Revision: 1.9 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2009/07/16 15:47:26 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "CQDifferentialEquations.h"

#include <qvariant.h>
/*
#include <q3scrollview.h>
#include "CQDifferentialEquations.ui.h"
 */
#include "CQDifferentialEquations.h"

#include <sstream>
#include <set>
#include <vector>

#include <qmessagebox.h>
#include <qregexp.h>
//#include "Qt3Support/Q3ScrollView"

#ifdef HAVE_MML
# include "mml/qtmmlwidget.h"
#endif // HAVE_MML

#include "model/CMMLOutput.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "qtUtilities.h"
#include "utilities/utility.h"
#include "tex/CMathMLToTeX.h"
#include "report/CCopasiRootContainer.h"

#include "CopasiFileDialog.h"

#ifdef DEBUG_UI
#include <QtDebug>
#endif

/*
 *  Constructs a CQDifferentialEquations which is a child of 'parent', with the
 *  name 'name'.'
 */
CQDifferentialEquations::CQDifferentialEquations(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQDifferentialEquations::~CQDifferentialEquations()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQDifferentialEquations::languageChange()
{
  retranslateUi(this);
}

void CQDifferentialEquations::init()
{
  mpScrollView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mpScrollView->setResizePolicy(Q3ScrollView::AutoOneFit);

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
  ofile.open(utf8ToLocale(TO_UTF8(outfilename)).c_str(), std::ios::trunc);

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

  assert(CCopasiRootContainer::getDatamodelList()->size() > 0);
  CMMLOutput::writeDifferentialEquations(mml, (*CCopasiRootContainer::getDatamodelList())[0]->getModel(), parameterAsNumbers, expand, expandAll);

  QWidget* tmp = dynamic_cast<QWidget*>(parent());

  if (tmp) tmp->setCursor(Qt::WaitCursor);

  mpMMLWidget->setContent(FROM_UTF8(mml.str()));
  mpScrollView->resizeContents(mpMMLWidget->sizeHint().width(), mpMMLWidget->sizeHint().height());

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

void CQDifferentialEquations::saveTeX(const QString outfilename)
{
  QString latexStr(FROM_UTF8(mml.str()));

#ifdef DEBUG_UI
  qDebug() << latexStr;
#endif

  CMathMLToTeX::convert(latexStr);

  std::ofstream ofile;
  ofile.open(utf8ToLocale(TO_UTF8(outfilename)).c_str(), std::ios::trunc);
  ofile << TO_UTF8(latexStr);
  ofile.close();
}

void CQDifferentialEquations::slotSave()
{
  QString outfilename;

  C_INT32 Answer = QMessageBox::No;

  while (Answer == QMessageBox::No)
    {
      outfilename =
        CopasiFileDialog::getSaveFileName(this,
                                          "Save File Dialog",
                                          "untitled.mml",
                                          "MathML (*.mml);;TeX (*.tex)",
                                          "Save Formula to Disk", new QString);

      if (outfilename.isEmpty()) return;

      // Checks whether the file exists
      Answer = checkSelection(outfilename);

      if (Answer == QMessageBox::Cancel)
        return;
    }

#ifdef DEBUG_UI
  qDebug() << "outfilename = " << outfilename;
#endif

  if (outfilename.contains(".tex"))
    saveTeX(outfilename);
  else
    saveMML(outfilename);
}
