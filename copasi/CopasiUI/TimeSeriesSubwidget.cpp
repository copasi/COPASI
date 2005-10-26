/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TimeSeriesSubwidget.cpp,v $
   $Revision: 1.8 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2005/10/26 15:43:18 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'TimeSeriesSubwidget.ui'
 **
 ** Created: Mon Oct 24 12:45:57 2005
 **      by: The User Interface Compiler ($Id: TimeSeriesSubwidget.cpp,v 1.8 2005/10/26 15:43:18 stupe Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "TimeSeriesSubwidget.h"

#include <qvariant.h>
 #include <qregexp.h>
 #include <qpushbutton.h>
 #include <qcombobox.h>
 #include <qtabwidget.h>
 #include <qtextedit.h>
 #include <qlayout.h>
 #include <qtooltip.h>
 #include <qwhatsthis.h>
 #include "qmessagebox.h"
 #include "qfiledialog.h"
 #include "CTimeSeriesTable.h"
 #include "TimeSeriesSubwidget.ui.h"

/*
 *  Constructs a TimeSeriesSubWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
TimeSeriesSubWidget::TimeSeriesSubWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("TimeSeriesSubWidget");
  setSizePolicy(QSizePolicy((QSizePolicy::SizeType)7, (QSizePolicy::SizeType)7, 0, 0, sizePolicy().hasHeightForWidth()));
  TimeSeriesSubWidgetLayout = new QVBoxLayout(this, 11, 6, "TimeSeriesSubWidgetLayout");

  toplayout = new QHBoxLayout(0, 1, 1, "toplayout");

  comboBox = new QComboBox(FALSE, this, "comboBox");
  comboBox->setMinimumSize(QSize(0, 20));
  toplayout->addWidget(comboBox);
  spacer = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  toplayout->addItem(spacer);

  ButtonSaveData = new QPushButton(this, "ButtonSaveData");
  ButtonSaveData->setMinimumSize(QSize(0, 20));
  toplayout->addWidget(ButtonSaveData);
  TimeSeriesSubWidgetLayout->addLayout(toplayout);

  tabWidget2 = new QTabWidget(this, "tabWidget2");
  tabWidget2->setGeometry(QRect(10, 40, 550, 510));

  tab = new QWidget(tabWidget2, "tab");
  tabLayout = new QVBoxLayout(tab, 11, 6, "tabLayout");

  optimizationResultText = new QTextEdit(tab, "optimizationResultText");
  optimizationResultText->setReadOnly(TRUE);
  tabLayout->addWidget(optimizationResultText);
  tabWidget2->insertTab(tab, QString(""));

  tab_2 = new QWidget(tabWidget2, "tab_2");
  tabLayout_2 = new QVBoxLayout(tab_2, 11, 6, "tabLayout_2");

  dataTable = new CTimeSeriesTable(tab_2, "dataTable");
  dataTable->setReadOnly(TRUE);
  tabLayout_2->addWidget(dataTable);
  tabWidget2->insertTab(tab_2, QString(""));
  TimeSeriesSubWidgetLayout->addWidget(tabWidget2);
  languageChange();
  resize(QSize(600, 497).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(ButtonSaveData, SIGNAL(clicked()), this, SLOT(saveDataToFile()));
  connect(comboBox, SIGNAL(activated(const QString&)), this, SLOT(toggleView()));
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
TimeSeriesSubWidget::~TimeSeriesSubWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void TimeSeriesSubWidget::languageChange()
{
  setCaption(tr("Form1"));
  comboBox->clear();
  comboBox->insertItem(tr("Concentrations"));
  comboBox->insertItem(tr("Particle Numbers"));
  ButtonSaveData->setText(tr("Save data to file"));
  tabWidget2->changeTab(tab, tr("OptimizationResult"));
  tabWidget2->changeTab(tab_2, tr("TimeSeries"));
}
