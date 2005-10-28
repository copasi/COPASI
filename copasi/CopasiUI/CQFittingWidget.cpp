/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQFittingWidget.cpp,v $
   $Revision: 1.7 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/28 16:01:45 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQFittingWidget.ui'
 **
 ** Created: Fri Oct 28 12:00:59 2005
 **      by: The User Interface Compiler ($Id: CQFittingWidget.cpp,v 1.7 2005/10/28 16:01:45 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQFittingWidget.h"

#include <qvariant.h>
 #include <qpushbutton.h>
 #include <qtabwidget.h>
 #include <qwidget.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>
 #include "TaskWidget.h"
 #include "CQFittingWidget.ui.h"

/*
 *  Constructs a CQFittingWidget which is a child of 'parent', with the
 *  name 'name'.' 
 */
CQFittingWidget::CQFittingWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  if (!name)
    setName("CQFittingWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  setMinimumSize(QSize(0, 0));
  CQFittingWidgetLayout = new QVBoxLayout(this, 11, 6, "CQFittingWidgetLayout");

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpBtnExperiment = new QPushButton(this, "mpBtnExperiment");

  mpGridLayout->addWidget(mpBtnExperiment, 0, 2);

  mpBtnAdd = new QPushButton(this, "mpBtnAdd");

  mpGridLayout->addWidget(mpBtnAdd, 0, 0);
  mpSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  mpGridLayout->addItem(mpSpacer, 0, 1);

  mpTabWidget = new QTabWidget(this, "mpTabWidget");

  mpParametersPage = new QWidget(mpTabWidget, "mpParametersPage");
  mpTabWidget->insertTab(mpParametersPage, QString(""));

  mpConstraintsPage = new QWidget(mpTabWidget, "mpConstraintsPage");
  mpTabWidget->insertTab(mpConstraintsPage, QString(""));

  mpGridLayout->addMultiCellWidget(mpTabWidget, 1, 1, 0, 2);
  CQFittingWidgetLayout->addLayout(mpGridLayout);
  languageChange();
  resize(QSize(523, 352).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpBtnAdd, SIGNAL(clicked()), this, SLOT(slotBtnAdd()));
  connect(mpBtnExperiment, SIGNAL(clicked()), this, SLOT(slotExperimentData()));
  connect(mpTabWidget, SIGNAL(currentChanged(QWidget*)), this, SLOT(slotPageChange(QWidget*)));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQFittingWidget::~CQFittingWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQFittingWidget::languageChange()
{
  setCaption(tr("Fitting"));
  mpBtnExperiment->setText(tr("Experimental Data"));
  mpBtnAdd->setText(tr("Add Parameter"));
  mpTabWidget->changeTab(mpParametersPage, tr("Parameters (0)"));
  mpTabWidget->changeTab(mpConstraintsPage, tr("Constraints (0)"));
}
