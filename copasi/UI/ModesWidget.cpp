/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/ModesWidget.cpp,v $
   $Revision: 1.35 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2004/09/16 20:12:44 $
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

/**
 *  Constructs a Widget for the Compartments subsection of the tree.
 *  This widget is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'. 
 *  @param model The CModel class which contains the metabolites 
 *  to be displayed.
 *  @param parent The widget which this widget is a child of.
 *  @param name The object name is a text that can be used to identify 
 *  this QObject. It's particularly useful in conjunction with the Qt Designer.
 *  You can find an object by name (and type) using child(), and more than one 
 *  using queryList(). 
 *  @param flags Flags for this widget. Redfer Qt::WidgetFlags of Qt documentation 
 *  for more information about these flags.
 */
ModesWidget::ModesWidget(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)

{
  mModel = NULL;
  binitialized = true;

  //table = new MyTable(this, "tblCompartments");
  listView = new QListView(this, "tblCompartments");
  listView->setSelectionMode(QListView::Single);
  listView->setAllColumnsShowFocus(true);
  listView->setSortColumn(-1);
  //table->setNumCols(2);
  //table->setNumRows(-1);
  listView->addColumn("Reversible/Irreversible");
  listView->addColumn("Reaction Name");
  listView->addColumn("Reaction Equation");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  //vBoxLayout->addWidget(table);
  vBoxLayout->addWidget(listView);

  //Setting table headers
  //QHeader *tableHeader = table->horizontalHeader();
  //tableHeader->setLabel(0, "Reversible/Irreversible");
  //tableHeader->setLabel(1, "Elementary Mode");

  btnCalculate = new QPushButton("&Run", this);
  modes = NULL; //new CElementaryFluxModes();

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnCalculate);
  hBoxLayout->addSpacing(50);

  //table->sortColumn (0, true, true);
  //table->setSorting (true);
  //table->setFocusPolicy(QWidget::WheelFocus);
  listView->setFocusPolicy(QWidget::WheelFocus);
  //table->setProtected(true);

  // signals and slots connections
  //  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)), this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  //  connect(this, SIGNAL(name(const QString &)), (ListViews*)parent, SLOT(slotModesTableChanged(QString &)));

  //connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  connect(listView, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  connect(btnCalculate, SIGNAL(clicked ()), this, SLOT(slotBtnCalculateClicked()));
  //  connect(table, SIGNAL(valueChanged(int , int)), this, SLOT(tableValueChanged(int, int)));

  //table -> setVScrollBarMode(QScrollView::AlwaysOn);
}

void ModesWidget::loadModes(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
    }

  //Emptying the table
  /*
  int numberOfRows = table->numRows();
  int i;
  for (i = 0; i < numberOfRows; i++)
    {
      table->removeRow(0);
    }
  */ 
  // Clearing the listview
  QListViewItem* item = listView->firstChild();
  QListViewItem* oldItem;
  while (item)
    {
      listView->takeItem(item);
      oldItem = item;
      item = item->nextSibling();
      delete oldItem;
    }

  /***CL ***/ // fill table with new values
  if (modes)
    {
      unsigned C_INT32 const noOfModesRows = modes->getFluxModeSize();
      //table->setNumRows(noOfModesRows);
      //bool status;
      unsigned C_INT32 j;
      for (j = 0; j < noOfModesRows; j++)
        {
          // status=modes->isFluxModeReversible(j);
          if (modes->isFluxModeReversible(j) == true)
            {
              //table->setText(j, 0, "Reversible");
              item = new QListViewItem(listView, "Reversible");
            }
          else
            {
              //table->setText(j, 0, "Irreversible");
              item = new QListViewItem(listView, "Irreversible");
            }
          item->setMultiLinesEnabled(true);
          //QString y=modes->isFluxModeReversible(j)->;
          //QString x=modes->getFluxModeDescription(j).;
          //QMessageBox::information(this, "recahed ",x);
          //table->setText(j, 0,y);
          //table->setText(j, 0,modes->getFluxModeDescription(j).);
          //table->setText(j, 1, FROM_UTF8(modes->getFluxModeDescription(j)));
          item->setText(1, FROM_UTF8(modes->getFluxModeDescription(j)));
          std::string reactionEq = "";
          unsigned int x;
          CFluxMode mode = modes->getFluxMode(j);
          for (x = 0; x < mode.size(); x++)
            {
              reactionEq += mode.getReactionEquation(x, mModel);
              reactionEq += "\n";
            }
          item->setText(2, QString(reactionEq.c_str()).stripWhiteSpace());
        } /*** CL ***/
    }
}

/*void ModesWidget::slotTableCurrentChanged(int row,int col,int C_UNUSED(m) ,const QPoint & C_UNUSED(n))
{
  QString x = table->text(row, col);
  emit name(x);
  //QMessageBox::information(this, "Compartments Widget",x);
}
 */
void ModesWidget::slotTableSelectionChanged()
{/*
      if (!table->hasFocus())
        {
          table->setFocus();
        }
        */
  if (!listView->hasFocus())
    {
      listView->setFocus();
    }
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
      /* else
         {
           table->DisableColWidthUpdate();
           int newWidth = re->size().width();
           int i;

           int totalWidth = 0;
           for (i = 0; i < table->numCols(); i++)
             totalWidth += table->columnWidth(i);

           int minTotalWidth = 0;
           for (i = 0; i < table->numCols(); i++)
             minTotalWidth += table->minColWidth[i];

           //Zoom in
           if (newWidth > re->oldSize().width())
             {
               if (newWidth > totalWidth) // can do expansion
                 {
                   if (totalWidth < re->oldSize().width())
                     for (i = 0; i < table->numCols(); i++) // Do expansion
                       table->setColumnWidth(i, newWidth*table->columnWidth(i) / re->oldSize().width());
                   else
                     for (i = 0; i < table->numCols(); i++) // Do expansion
                       table->setColumnWidth(i, float(newWidth)*float(table->columnWidth(i)) / float(totalWidth));
                 }
               else
                 for (i = 0; i < table->numCols(); i++) // Do not expand
                   table->setColumnWidth(i, table->columnWidth(i));

               table->EnableColWidthUpdate();
               return;
             }
           //Zoom out
           //calculate total Width
           if (newWidth >= totalWidth)    //will not decrease any column width
             {
               for (i = 0; i < table->numCols(); i++)
                 table->setColumnWidth(i, table->columnWidth(i));
               table->EnableColWidthUpdate();
               return;
             }
           //will decrease only those larger than the minimum width
           //Less than the user specified total width
           if (newWidth <= minTotalWidth)
             {
               for (i = 0; i < table->numCols(); i++)
                 table->setColumnWidth(i, table->minColWidth[i]);
               table->EnableColWidthUpdate();
               return;
             }
           //Bigger than the user specified total width
           for (i = 0; i < table->numCols(); i++) // Do Expansion
             table->setColumnWidth(i, (newWidth - minTotalWidth)*(table->columnWidth(i) - table->minColWidth[i]) / (totalWidth - minTotalWidth) + table->minColWidth[i]);
           table->EnableColWidthUpdate();
           return;
         }*/
    }
  CopasiWidget::resizeEvent(re);
}

void ModesWidget::slotBtnCalculateClicked()
{
  // QMessageBox::information(this, "Compartments Widget", "Do you really want to cancel changes");
  // emit signal_emitted(*Compartment_Name);

  //Emptying the table
  /****CL***int numberOfRows = table->numRows();
  int i;
  for (i = 0; i < numberOfRows; i++)
    {
      table->removeRow(0);
    }******CL***/

  pdelete(modes);
  modes = new CElementaryFluxModes();
  modes->calculate(mModel);
  loadModes(mModel);
  /***CL***unsigned C_INT32 const noOfModesRows = modes->getFluxModeSize();
  //QString y=QString::number(noOfModesRows);

  //QMessageBox::information(this, "recahed ",y);
  table->setNumRows(noOfModesRows);
  //bool status;
  C_INT32 j;
  for (j = 0; j < noOfModesRows; j++)
    {
      // status=modes->isFluxModeReversible(j);
      if (modes->isFluxModeReversible(j) == true)
        {
          table->setText(j, 0, "Reversible");
        }
      else
        {
          table->setText(j, 0, "Irreversible");
        }
      //QString y=modes->isFluxModeReversible(j)->;
      //QString x=modes->getFluxModeDescription(j).;
      //QMessageBox::information(this, "recahed ",x);
      //table->setText(j, 0,y);
      //table->setText(j, 0,modes->getFluxModeDescription(j).);
      table->setText(j, 1, modes->getFluxModeDescription(j).);
    }***CL***/
}

bool ModesWidget::update(ListViews::ObjectType C_UNUSED(objectType),
                         ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  pdelete(modes);
  return true;
}

bool ModesWidget::enter(const std::string & C_UNUSED(key))
{
  loadModes(dataModel->getModel());
  return true;
}
