/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/TimeSeriesSubwidget.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/09/29 03:40:35 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'TimeSeriesSubwidget.ui'
 **
 ** Created: Tue Sep 28 23:39:48 2004
 **      by: The User Interface Compiler ($Id: TimeSeriesSubwidget.cpp,v 1.3 2004/09/29 03:40:35 shoops Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "TimeSeriesSubwidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
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
  TimeSeriesSubWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "TimeSeriesSubWidgetLayout");

  layout2 = new QHBoxLayout(0, 0, 6, "layout2");
  spacer1 = new QSpacerItem(110, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);
  layout2->addItem(spacer1);

  pushButtonToggle = new QPushButton(this, "pushButtonToggle");
  layout2->addWidget(pushButtonToggle);

  ButtonSaveData = new QPushButton(this, "ButtonSaveData");
  layout2->addWidget(ButtonSaveData);

  TimeSeriesSubWidgetLayout->addLayout(layout2, 0, 0);

  dataTable = new QTable(this, "dataTable");
  dataTable->setNumRows(3);
  dataTable->setNumCols(3);

  TimeSeriesSubWidgetLayout->addWidget(dataTable, 1, 0);
  languageChange();
  resize(QSize(465, 480).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);

  // signals and slots connections
  connect(ButtonSaveData, SIGNAL(clicked()), this, SLOT(saveDataToFile()));
  connect(pushButtonToggle, SIGNAL(clicked()), this, SLOT(toggleView()));
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
  pushButtonToggle->setText(tr("Show Numbers"));
  ButtonSaveData->setText(tr("Save data to file"));
}
