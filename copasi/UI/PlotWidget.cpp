/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/PlotWidget.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: gasingh $ 
   $Date: 2004/01/30 06:38:47 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/PlotWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Plots----It is Basically the First level of Plots
 ********************************************************************/
#include "PlotWidget.h"

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include <qpushbutton.h>

#include "MyTable.h"
#include "model/CModel.h" 
//#include "model/CCompartment.h"
#include "listviews.h"
#include "report/CKeyFactory.h"
#include "plot/CPlotSpec.h"

/**
 */
PlotWidget::PlotWidget(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  binitialized = true;
  table = new MyTable(this, "tblPlots");
  table->setNumCols(2);
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Volume");

  btnOK = new QPushButton("&OK", this);
  btnCancel = new QPushButton("&Cancel", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(50);

  table->sortColumn (0, true, true);
  table->setSorting (true);
  table->setFocusPolicy(QWidget::WheelFocus);

  // signals and slots connections
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)),
          this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  connect(table, SIGNAL(selectionChanged ()),
          this, SLOT(slotTableSelectionChanged ()));
  connect(btnOK, SIGNAL(clicked ()), this,
          SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()), this,
          SLOT(slotBtnCancelClicked()));
  connect(table, SIGNAL(valueChanged(int , int)),
          this, SLOT(tableValueChanged(int, int)));

  //connect(table, SIGNAL(currentChanged(int, int)),
  //        this, SLOT(CurrentValueChanged(int, int)));

  //m_SavedRow = 0;
  //m_SavedCol = 0;
  //prev_row = 0;
  //prev_col = 0;
}

void PlotWidget::fillTable()
{
  const CCopasiVector< CPlotSpec >* objects =
    dataModel->getPlotSpecVectorAddr();

  C_INT32 j, jmax = objects->size();
  table->setNumRows(jmax);
  mKeys.resize(jmax);

  for (j = 0; j < jmax; ++j)
    {
      table->setText(j, 0, (*objects)[j]->getName().c_str());
      //TODO table->setText(j, 1, (*objects)[j]->getComment().c_str());
      mKeys[j] = (*objects)[j]->getKey();
    }
  table->setText(jmax, 1, "");
}

void PlotWidget::createNewObject()
{
  std::string name = "PlotSpec_0";
  int i = 0;
  while (!dataModel->getPlotSpecVectorAddr()->addNewPlotSpec(name))
    {
      i++;
      name = "PlotSpec";
      name += "_";
      name += QString::number(i).latin1();
    }
  table->setText(table->numRows() - 1, 0, name.c_str());
  table->setNumRows(table->numRows());
  ListViews::notify(ListViews::PLOT, ListViews::ADD);
}

void PlotWidget::slotTableCurrentChanged(int row,
    int C_UNUSED(col),
    int C_UNUSED(m) ,
    const QPoint & C_UNUSED(n))
{
  if (row >= table->numRows() || row < 0) return;

  if (row == table->numRows() - 1)
  {createNewObject();}

  pListView->switchToOtherWidget(mKeys[row]);
}

void PlotWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus()) table->setFocus();
}

//void PlotWidget::CurrentValueChanged(int row, int col)
//{
//  at this point you know old values !
//prev_row = m_SavedRow;
//prev_col = m_SavedCol;

//m_SavedCol = col; // Save for a future use
//m_SavedRow = row; // Save for a future use
//}

void PlotWidget::slotBtnOKClicked()
{
  if (dataModel->getPlotSpecVectorAddr())
    {
      //for testing only
      std::ifstream datafile("datafile");
      //datafile.open("datafile", std::ios::in);

      dataModel->getPlotSpecVectorAddr()->setNumColumns(3);
      dataModel->getPlotSpecVectorAddr()->setSourceStream(&datafile);
      dataModel->getPlotSpecVectorAddr()->initPlottingFromStream();

      dataModel->getPlotSpecVectorAddr()->doPlotting();
      dataModel->getPlotSpecVectorAddr()->doPlotting();
    }
}

void PlotWidget::slotBtnCancelClicked()
{
  if (dataModel->getPlotSpecVectorAddr())
    fillTable();
}

void PlotWidget::tableValueChanged(int C_UNUSED(row),
                                   int C_UNUSED(col))
{}

bool PlotWidget::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::STATE:
    case ListViews::METABOLITE:
    case ListViews::COMPARTMENT:
    case ListViews::REPORT:
    case ListViews::PLOT:
      fillTable();
      break;

    default:
      break;
    }
  return true;
}

bool PlotWidget::leave()
{
  //does nothing.
  return true;
}

bool PlotWidget::enter(const std::string & key)
{
  //does nothing.
  return true;
}

void PlotWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      //      repaint_table();
      if (binitialized)
        {
          int newWidth = re->size().width();
          newWidth -= 35; //Accounting for the left (vertical) header width.
          float weight0 = 3.5, weight1 = 6.5;
          float weightSum = weight0 + weight1;
          int w0, w1;
          w0 = newWidth * (weight0 / weightSum);
          w1 = newWidth - w0;
          table->setColumnWidth(0, w0);
          table->setColumnWidth(1, w1);
          binitialized = false;
        }
      else
        {
          table->DisableColWidthUpdate();
          int newWidth = re->size().width() - 35;
          int i;

          int totalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            totalWidth += table->columnWidth(i);

          int minTotalWidth = 0;
          for (i = 0; i < table->numCols(); i++)
            minTotalWidth += table->minColWidth[i];

          //Zoom in
          if (newWidth > (re->oldSize().width() - 35))
            {
              if (newWidth > totalWidth) // can do expansion
                {
                  if (totalWidth < (re->oldSize().width() - 35))
                    for (i = 0; i < table->numCols(); i++) // Do expansion
                      table->setColumnWidth(i, newWidth*table->columnWidth(i) / (re->oldSize().width() - 35));
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
        }
    }
  CopasiWidget::resizeEvent(re);
}
