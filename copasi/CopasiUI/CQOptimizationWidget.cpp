/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CQOptimizationWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/14 16:27:00 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQOptimizationWidget.ui'
 **
 ** Created: Fri Oct 14 08:43:07 2005
 **      by: The User Interface Compiler ($Id: CQOptimizationWidget.cpp,v 1.1 2005/10/14 16:27:00 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQOptimizationWidget.h"

#include <qvariant.h>
 #include <qpushbutton.h>
 #include <qtoolbutton.h>
 #include <qlabel.h>
 #include <qtextedit.h>
 #include <qbuttongroup.h>
 #include <qradiobutton.h>
 #include <qtabwidget.h>
 #include <qwidget.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>
 #include "TaskWidget.h"
 #include "CQOptimizationWidget.ui.h"

/*
 *  Constructs a CQOptimizationWidget which is a child of 'parent', with the
 *  name 'name'.' 
 */
CQOptimizationWidget::CQOptimizationWidget(QWidget* parent, const char* name)
    : TaskWidget(parent, name)
{
  if (!name)
    setName("CQOptimizationWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, sizePolicy().hasHeightForWidth()));
  setMinimumSize(QSize(0, 0));
  CQOptimizationWidgetLayout = new QVBoxLayout(this, 11, 6, "CQOptimizationWidgetLayout");

  mpGridLayout = new QGridLayout(0, 1, 1, 0, 6, "mpGridLayout");

  mpBtnObject = new QToolButton(this, "mpBtnObject");
  mpBtnObject->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)4, (QSizePolicy::SizeType)4, 0, 0, mpBtnObject->sizePolicy().hasHeightForWidth()));

  mpGridLayout->addWidget(mpBtnObject, 0, 2);

  mpLblExpression = new QLabel(this, "mpLblExpression");
  mpLblExpression->setAlignment(int(QLabel::AlignTop));

  mpGridLayout->addWidget(mpLblExpression, 0, 0);

  mpEditExpression = new QTextEdit(this, "mpEditExpression");
  mpEditExpression->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)0, 0, 0, mpEditExpression->sizePolicy().hasHeightForWidth()));
  mpEditExpression->setMaximumSize(QSize(32767, 71));

  mpGridLayout->addMultiCellWidget(mpEditExpression, 0, 2, 1, 1);

  mpBtnGroup = new QButtonGroup(this, "mpBtnGroup");
  mpBtnGroup->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)4, 0, 0, mpBtnGroup->sizePolicy().hasHeightForWidth()));
  mpBtnGroup->setFrameShape(QButtonGroup::NoFrame);
  mpBtnGroup->setAlignment(int(QButtonGroup::AlignTop));
  mpBtnGroup->setColumnLayout(0, Qt::Vertical);
  mpBtnGroup->layout()->setSpacing(6);
  mpBtnGroup->layout()->setMargin(0);
  mpBtnGroupLayout = new QVBoxLayout(mpBtnGroup->layout());
  mpBtnGroupLayout->setAlignment(Qt::AlignTop);

  mpBtnSteadystate = new QRadioButton(mpBtnGroup, "mpBtnSteadystate");
  mpBtnGroupLayout->addWidget(mpBtnSteadystate);

  mpBtnTimeCourse = new QRadioButton(mpBtnGroup, "mpBtnTimeCourse");
  mpBtnGroupLayout->addWidget(mpBtnTimeCourse);

  mpGridLayout->addMultiCellWidget(mpBtnGroup, 0, 1, 3, 3);

  mpBtnAdd = new QPushButton(this, "mpBtnAdd");

  mpGridLayout->addWidget(mpBtnAdd, 3, 0);
  mpSpacer = new QSpacerItem(20, 43, QSizePolicy::Minimum, QSizePolicy::Preferred);
  mpGridLayout->addItem(mpSpacer, 1, 2);
  CQOptimizationWidgetLayout->addLayout(mpGridLayout);

  mpTabWidget = new QTabWidget(this, "mpTabWidget");
  mpTabWidget->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, mpTabWidget->sizePolicy().hasHeightForWidth()));

  mpParametersPage = new QWidget(mpTabWidget, "mpParametersPage");
  mpTabWidget->insertTab(mpParametersPage, QString(""));

  mpConstraintsPage = new QWidget(mpTabWidget, "mpConstraintsPage");
  mpTabWidget->insertTab(mpConstraintsPage, QString(""));
  CQOptimizationWidgetLayout->addWidget(mpTabWidget);
  languageChange();
  resize(QSize(523, 394).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(mpTabWidget, SIGNAL(currentChanged(QWidget*)), this, SLOT(slotPageChange(QWidget*)));
  connect(mpBtnAdd, SIGNAL(clicked()), this, SLOT(slotBtnAdd()));
  connect(mpBtnSteadystate, SIGNAL(toggled(bool)), this, SLOT(slotTypeChanged(bool)));
  connect(mpBtnObject, SIGNAL(clicked()), this, SLOT(slotExpression()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CQOptimizationWidget::~CQOptimizationWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CQOptimizationWidget::languageChange()
{
  setCaption(tr("Optimization"));
  mpBtnObject->setText(tr("..."));
  mpLblExpression->setText(tr("Expression"));
  mpBtnGroup->setTitle(tr("Simulation Type"));
  mpBtnSteadystate->setText(tr("Steady State"));
  mpBtnTimeCourse->setText(tr("Time Course"));
  mpBtnAdd->setText(tr("Add Parameter"));
  mpTabWidget->changeTab(mpParametersPage, tr("Parameters (0)"));
  mpTabWidget->changeTab(mpConstraintsPage, tr("Constraints (0)"));
}
