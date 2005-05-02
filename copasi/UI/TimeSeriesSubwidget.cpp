/* Begin CVS Header
   $Source: /home/cvs/copasi_dev/cvs_admin/c++style,v $
   $Revision: 1.16 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/11/05 18:38:04 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'TimeSeriesSubwidget.ui'
 **
 ** Created: Tue Apr 19 17:26:57 2005
 **      by: The User Interface Compiler ($Id: TimeSeriesSubwidget.cpp,v 1.6.6.1 2005/04/19 15:34:59 gauges Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "TimeSeriesSubwidget.h"

#include <qvariant.h>
#include <qregexp.h>
#include <qcombobox.h>
#include <qpushbutton.h>
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
