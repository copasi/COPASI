/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CQFittingWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/10/05 16:24:07 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CQFittingWidget.ui'
 **
 ** Created: Wed Oct 5 12:16:35 2005
 **      by: The User Interface Compiler ($Id: CQFittingWidget.cpp,v 1.1 2005/10/05 16:24:07 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CQFittingWidget.h"

#include <qvariant.h>
 #include <qframe.h>
 #include <qtable.h>
 #include <qlabel.h>
 #include <qtabwidget.h>
 #include <qwidget.h>
 #include <qcombobox.h>
 #include <qpushbutton.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>
 #include <qimage.h>
 #include <qpixmap.h>

#include "TaskWidget.h"
 #include "CScanContainerWidget.h"
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

  mpLine = new QFrame(this, "mpLine");
  mpLine->setFrameShape(QFrame::HLine);
  mpLine->setFrameShadow(QFrame::Sunken);
  mpLine->setFrameShape(QFrame::HLine);

  mpGridLayout->addMultiCellWidget(mpLine, 2, 2, 0, 3);

  mpTblParameter = new QTable(this, "mpTblParameter");
  mpTblParameter->setNumCols(mpTblParameter->numCols() + 1);
  mpTblParameter->horizontalHeader()->setLabel(mpTblParameter->numCols() - 1, tr("Value"));
  mpTblParameter->setNumRows(mpTblParameter->numRows() + 1);
  mpTblParameter->verticalHeader()->setLabel(mpTblParameter->numRows() - 1, tr("Name"));
  mpTblParameter->setNumRows(mpTblParameter->numRows() + 1);
  mpTblParameter->verticalHeader()->setLabel(mpTblParameter->numRows() - 1, tr("Name"));
  mpTblParameter->setNumRows(mpTblParameter->numRows() + 1);
  mpTblParameter->verticalHeader()->setLabel(mpTblParameter->numRows() - 1, tr("Name"));
  mpTblParameter->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)5, 0, 0, mpTblParameter->sizePolicy().hasHeightForWidth()));
  mpTblParameter->setMinimumSize(QSize(0, 0));
  mpTblParameter->setNumRows(3);
  mpTblParameter->setNumCols(1);

  mpGridLayout->addWidget(mpTblParameter, 1, 1);

  mpLblMethod = new QLabel(this, "mpLblMethod");
  mpLblMethod->setAlignment(int(QLabel::AlignVCenter | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblMethod, 0, 0);

  mpTabWidget = new QTabWidget(this, "mpTabWidget");

  mpParametersPage = new QWidget(mpTabWidget, "mpParametersPage");

  cScanContainerWidget3 = new CScanContainerWidget(mpParametersPage, "cScanContainerWidget3");
  cScanContainerWidget3->setGeometry(QRect(0, 0, 101, 31));
  mpTabWidget->insertTab(mpParametersPage, QString(""));

  mpConstraintsPage = new QWidget(mpTabWidget, "mpConstraintsPage");

  cScanContainerWidget4 = new CScanContainerWidget(mpConstraintsPage, "cScanContainerWidget4");
  cScanContainerWidget4->setGeometry(QRect(0, 0, 101, 31));
  mpTabWidget->insertTab(mpConstraintsPage, QString(""));

  mpGridLayout->addMultiCellWidget(mpTabWidget, 4, 4, 0, 3);

  mpBoxMethod = new QComboBox(FALSE, this, "mpBoxMethod");

  mpGridLayout->addWidget(mpBoxMethod, 0, 1);

  mpBtnAdd = new QPushButton(this, "mpBtnAdd");

  mpGridLayout->addWidget(mpBtnAdd, 3, 0);

  mpLblParameter = new QLabel(this, "mpLblParameter");
  mpLblParameter->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)5, (QSizePolicy::SizeType)5, 0, 0, mpLblParameter->sizePolicy().hasHeightForWidth()));
  mpLblParameter->setMinimumSize(QSize(0, 0));
  mpLblParameter->setAlignment(int(QLabel::AlignTop | QLabel::AlignRight));

  mpGridLayout->addWidget(mpLblParameter, 1, 0);

  mpBtnExperiment = new QPushButton(this, "mpBtnExperiment");

  mpGridLayout->addWidget(mpBtnExperiment, 0, 3);
  spacer8 = new QSpacerItem(40, 20, QSizePolicy::Maximum, QSizePolicy::Minimum);
  mpGridLayout->addItem(spacer8, 0, 2);
  CQFittingWidgetLayout->addLayout(mpGridLayout);
  languageChange();
  resize(QSize(600, 434).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
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
  mpTblParameter->horizontalHeader()->setLabel(0, tr("Value"));
  mpTblParameter->verticalHeader()->setLabel(0, tr("Name"));
  mpTblParameter->verticalHeader()->setLabel(1, tr("Name"));
  mpTblParameter->verticalHeader()->setLabel(2, tr("Name"));
  mpLblMethod->setText(tr("Method"));
  mpTabWidget->changeTab(mpParametersPage, tr("Parameters"));
  mpTabWidget->changeTab(mpConstraintsPage, tr("Constraints"));
  mpBtnAdd->setText(tr("Add Parameter"));
  mpLblParameter->setText(tr("Method Parameter"));
  mpBtnExperiment->setText(tr("Experiment Data"));
}
