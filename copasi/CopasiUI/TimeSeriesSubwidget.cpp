/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TimeSeriesSubwidget.cpp,v $
   $Revision: 1.6 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/07 16:57:54 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'TimeSeriesSubwidget.ui'
 **
 ** Created: Thu Sep 30 17:54:10 2004
 **      by: The User Interface Compiler ($Id: TimeSeriesSubwidget.cpp,v 1.6 2004/10/07 16:57:54 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "TimeSeriesSubwidget.h"

#include <qvariant.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qfiledialog.h>
#include <qmessagebox.h>
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
  TimeSeriesSubWidgetLayout = new QVBoxLayout(this, 11, 6, "TimeSeriesSubWidgetLayout");

  toplayout = new QHBoxLayout(0, 0, 6, "toplayout");

  comboBox = new QComboBox(FALSE, this, "comboBox");
  toplayout->addWidget(comboBox);
  spacer = new QSpacerItem(170, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  toplayout->addItem(spacer);

  ButtonSaveData = new QPushButton(this, "ButtonSaveData");
  toplayout->addWidget(ButtonSaveData);
  TimeSeriesSubWidgetLayout->addLayout(toplayout);

  dataTable = new CTimeSeriesTable(this, "dataTable");
  TimeSeriesSubWidgetLayout->addWidget(dataTable);
  languageChange();
  resize(QSize(565, 608).expandedTo(minimumSizeHint()));
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
}
