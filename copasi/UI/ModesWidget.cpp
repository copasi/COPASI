/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ModesWidget.cpp,v $
   $Revision: 1.53 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/08/29 20:27:28 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*******************************************************************
 **  $ CopasiUI/ModesWidget.cpp
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the
 ** information obtained from the data model about the
 ** Modes Widget
 ********************************************************************/

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qmessagebox.h>
#include <qapplication.h>

#include "copasi.h"

#include "ModesWidget.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "copasiui3window.h"

#include "elementaryFluxModes/CEFMTask.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "utilities/CCopasiVector.h"

ModesWidget::ModesWidget(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)

{
  binitialized = true;

  listView = new QListView(this, "tblCompartments");
  listView->setSelectionMode(QListView::Single);
  listView->setAllColumnsShowFocus(true);
  listView->setSortColumn(-1);
  listView->addColumn("Reversibility");
  listView->addColumn("Reaction Name");
  listView->addColumn("Reaction Equation");

  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 6);
  vBoxLayout->addWidget(listView);

  btnCalculate = new QPushButton("&Calculate", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  //hBoxLayout->addSpacing(50);
  hBoxLayout->addStretch();
  hBoxLayout->addWidget(btnCalculate);
  //hBoxLayout->addSpacing(50);

  listView->setFocusPolicy(QWidget::WheelFocus);

  connect(listView, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  connect(btnCalculate, SIGNAL(clicked ()), this, SLOT(slotBtnCalculateClicked()));

  loadModes();
}

void ModesWidget::loadModes()
{
  listView->clear();

  QListViewItem* item;

  CEFMTask * pTask =
    dynamic_cast< CEFMTask * >((*CCopasiDataModel::Global->getTaskList())["Elementary Flux Modes"]);

  if (pTask)
    {
      unsigned C_INT32 const noOfModesRows = pTask->getFluxModeSize();
      unsigned C_INT32 j;
      for (j = 0; j < noOfModesRows; j++)
        {
          if (pTask->isFluxModeReversible(j) == true)
            {
              item = new QListViewItem(listView, "Reversible");
            }
          else
            {
              item = new QListViewItem(listView, "Irreversible");
            }
          item->setMultiLinesEnabled(true);

          item->setText(1, FROM_UTF8(pTask->getFluxModeDescription(j)));
          std::string reactionEq = "";
          unsigned int x, xmax = pTask->getFluxModeSize(j);
          //const CFluxMode & mode = pTask->getFluxMode(j);
          for (x = 0; x < xmax; x++)
            {
              reactionEq += pTask->getReactionEquation(j, x);
              reactionEq += "\n";
            }
          item->setText(2, FROM_UTF8(reactionEq).stripWhiteSpace() + "\n");
        }
    }
}

void ModesWidget::slotTableSelectionChanged()
{}

void ModesWidget::slotBtnCalculateClicked()
{
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->autoSave();
  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(true);

  CEFMTask * pTask =
    dynamic_cast< CEFMTask * >((*CCopasiDataModel::Global->getTaskList())["Elementary Flux Modes"]);

  pTask->initialize(CCopasiTask::OUTPUT_COMPLETE, NULL);
  pTask->process(false);
  pTask->restore();

  loadModes();

  static_cast<CopasiUI3Window *>(qApp->mainWidget())->suspendAutoSave(false);
}

bool ModesWidget::update(ListViews::ObjectType C_UNUSED(objectType),
                         ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  //TODO: only if necessary

  return true;
}

bool ModesWidget::enter(const std::string & C_UNUSED(key))
{
  return true;
}
