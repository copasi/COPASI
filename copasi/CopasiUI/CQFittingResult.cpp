/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingResult.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/22 17:22:56 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQFittingResult.ui'
 **
 ** Created: Wed Mar 22 12:21:31 2006
 **      by: The User Interface Compiler ($Id: CQFittingResult.cpp,v 1.2 2006/03/22 17:22:56 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQFittingResult.h"

#include <qvariant.h>
 #include <qtabwidget.h>
 #include <qtable.h>
 #include <qpushbutton.h>
 #include <qlabel.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>
 #include "CQFittingResult.ui.h"

/*
 *  Constructs a CQFittingResult which is a child of 'parent', with the
 *  name 'name'.' 
 */
CQFittingResult::CQFittingResult(QWidget* parent, const char* name)
    : CopasiWidget(parent, name)
{
  if (!name)
    setName("CQFittingResult");
  CQFittingResultLayout = new QGridLayout(this, 1, 1, 11, 6, "CQFittingResultLayout");

  mpTabWidget = new QTabWidget(this, "mpTabWidget");
  mpTabWidget->setGeometry(QRect(10, 50, 380, 190));
  mpTabWidget->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpTabWidget->sizePolicy().hasHeightForWidth()));
  mpTabWidget->setMinimumSize(QSize(210, 180));

  mpMain = new CQFittingResultTab1(mpTabWidget, "mpMain");
  mpTabWidget->insertTab(mpMain, QString::fromLatin1(""));

  mpParameters = new QTable(mpTabWidget, "mpParameters");
  mpTabWidget->insertTab(mpParameters, QString::fromLatin1(""));

  mpExperiments = new QTable(mpTabWidget, "mpExperiments");
  mpTabWidget->insertTab(mpExperiments, QString::fromLatin1(""));

  mpValues = new QTable(mpTabWidget, "mpValues");
  mpTabWidget->insertTab(mpValues, QString::fromLatin1(""));

  mpCorrelations = new QTable(mpTabWidget, "mpCorrelations");
  mpTabWidget->insertTab(mpCorrelations, QString::fromLatin1(""));

  CQFittingResultLayout->addMultiCellWidget(mpTabWidget, 1, 1, 0, 1);

  mpBtnSave = new QPushButton(this, "mpBtnSave");
  mpBtnSave->setGeometry(QRect(290, 10, 101, 31));

  CQFittingResultLayout->addWidget(mpBtnSave, 0, 1);

  mpLblResult = new QLabel(this, "mpLblResult");
  mpLblResult->setGeometry(QRect(10, 10, 260, 31));
  mpLblResult->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)3, (QSizePolicy::SizeType)5, 0, 0, mpLblResult->sizePolicy().hasHeightForWidth()));

  CQFittingResultLayout->addWidget(mpLblResult, 0, 0);
  languageChange();
  resize(QSize(401, 253).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingResult::~CQFittingResult()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingResult::languageChange()
{
  setCaption(tr("Fitting Result"));
  mpTabWidget->changeTab(mpMain, tr("Main"));
  mpTabWidget->changeTab(mpParameters, tr("Parameters"));
  mpTabWidget->changeTab(mpExperiments, tr("Experiments"));
  mpTabWidget->changeTab(mpValues, tr("Fitted Values"));
  mpTabWidget->changeTab(mpCorrelations, tr("Correlation Matrix"));
  mpBtnSave->setText(tr("save data"));
  mpLblResult->setText(tr("<h2>Parameter Estimation Result</h2>"));
}
