/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ModesWidget.cpp,v $
   $Revision: 1.45 $
   $Name:  $
   $Author: stupe $ 
   $Date: 2005/02/15 22:41:34 $
   End CVS Header */

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
#include "copasi.h"
#include "elementaryFluxModes/CElementaryFluxModes.h"
#include "ModesWidget.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "qtUtilities.h"
#include "qmessagebox.h"
#include "qapplication.h"
#include "copasiui3window.h"

ModesWidget::ModesWidget(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)

{
  //mModel = NULL;
  modes = NULL;

  binitialized = true;

  listView = new QListView(this, "tblCompartments");
  listView->setSelectionMode(QListView::Single);
  listView->setAllColumnsShowFocus(true);
  listView->setSortColumn(-1);
  listView->addColumn("Reversible/Irreversible");
  listView->addColumn("Reaction Name");
  listView->addColumn("Reaction Equation");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(listView);

  btnCalculate = new QPushButton("&Run", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnCalculate);
  hBoxLayout->addSpacing(50);

  listView->setFocusPolicy(QWidget::WheelFocus);

  connect(listView, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  connect(btnCalculate, SIGNAL(clicked ()), this, SLOT(slotBtnCalculateClicked()));

  loadModes();
}

void ModesWidget::loadModes()
{
  listView->clear();

  CModel* model = dataModel->getModel();
  QListViewItem* item;

  if (modes)
    {
      unsigned C_INT32 const noOfModesRows = modes->getFluxModeSize();
      unsigned C_INT32 j;
      for (j = 0; j < noOfModesRows; j++)
        {
          if (modes->isFluxModeReversible(j) == true)
            {
              item = new QListViewItem(listView, "Reversible");
            }
          else
            {
              item = new QListViewItem(listView, "Irreversible");
            }
          item->setMultiLinesEnabled(true);

          item->setText(1, FROM_UTF8(modes->getFluxModeDescription(j)));
          std::string reactionEq = "";
          unsigned int x, xmax = modes->getFluxModeSize(j);
          //const CFluxMode & mode = modes->getFluxMode(j);
          for (x = 0; x < xmax; x++)
            {
              reactionEq += modes->getReactionEquation(j, x, model);
              reactionEq += "\n";
            }
          item->setText(2, FROM_UTF8(reactionEq).stripWhiteSpace() + "\n");
        }
    }
}

void ModesWidget::slotTableSelectionChanged()
{
  /*  if (!listView->hasFocus())
      {
        listView->setFocus();
      }*/
}

void ModesWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      if (binitialized)
        {
          int newWidth = re->size().width();
          newWidth -= 35; //Accounting for the left (vertical) header width.
          float weight0 = 3.5, weight1 = 6.5;
          float weightSum = weight0 + weight1;
          int w0, w1;
          w0 = newWidth * (weight0 / weightSum);
          //w1 = newWidth - w0 - table->verticalScrollBar()->width();
          w1 = newWidth - w0 - listView->verticalScrollBar()->width();
          //table->setColumnWidth(0, w0);
          //table->setColumnWidth(1, w1);
          listView->setColumnWidth(0, w0);
          listView->setColumnWidth(1, w1);
          binitialized = false;
        }
    }
  CopasiWidget::resizeEvent(re);
}

void ModesWidget::slotBtnCalculateClicked()
{
  if (dataModel->isChanged())
    {
      const QApplication* qApp = dataModel->getQApp();
      if (qApp)
        {
          CopasiUI3Window* mainWidget = dynamic_cast<CopasiUI3Window*>(qApp->mainWidget());
          if (mainWidget)
            {
              dataModel->autoSave();
              /*
                       if (QMessageBox::question(mainWidget, "Model Changed", "Your model contains unsaved changes.\nDo you want to save those changes?", QMessageBox::Yes | QMessageBox::Default, QMessageBox::No | QMessageBox::Escape) == QMessageBox::Yes)
                         {
                           mainWidget->saveFile();
                         }
              */
            }
        }
    }
  pdelete(modes);
  modes = new CElementaryFluxModes();
  modes->calculate(dataModel->getModel());
  loadModes();
}

bool ModesWidget::update(ListViews::ObjectType C_UNUSED(objectType),
                         ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  //TODO: only if necessary

  //pdelete(modes);
  //loadModes();
  return true;
}

bool ModesWidget::enter(const std::string & C_UNUSED(key))
{
  //loadModes();
  return true;
}
