/*******************************************************************
 **  $ CopasiUI/ModesWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Compartments----It is Basically the First level of Compartments
 ********************************************************************/

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>
#include "copasi.h"
#include "elementaryFluxModes/CElementaryFluxModes.h"
#include "ModesWidget.h"
#include "listviews.h"

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
    : QWidget(parent, name, f)

{
  mModel = NULL;
  table = new MyTable(0, 2, this, "tblCompartments");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Reversible/Irreversible");
  tableHeader->setLabel(1, "Elementary Mode");

  btnCalculate = new QPushButton("&Run", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnCalculate);
  hBoxLayout->addSpacing(50);

  table->sortColumn (0, true, true);
  table->setSorting (true);
  table->setFocusPolicy(QWidget::WheelFocus);

  // signals and slots connections
  //connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)), this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  //connect(this, SIGNAL(name(QString &)), (ListViews*)parent, SLOT(slotCompartmentTableChanged(QString &)));

  connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  connect(btnCalculate, SIGNAL(clicked ()), this, SLOT(slotBtnCalculateClicked()));
  //connect(table, SIGNAL(valueChanged(int , int)), this, SLOT(tableValueChanged(int, int)));
}

void ModesWidget::loadModes(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
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
{
  if (!table->hasFocus())
    {
      table->setFocus();
    }
}

void ModesWidget::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
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
    }
}

void ModesWidget::slotBtnCalculateClicked()
{
  // QMessageBox::information(this, "Compartments Widget", "Do you really want to cancel changes");
  // emit signal_emitted(*Compartment_Name);

  //Emptying the table
  int numberOfRows = table->numRows();

  for (int i = 0; i < numberOfRows; i++)
    {
      table->removeRow(0);
    }

  CElementaryFluxModes *modes = new CElementaryFluxModes();
  modes->calculate(mModel);
  unsigned C_INT32 const noOfModesRows = modes->getFluxModeSize();
  //QString y=QString::number(noOfModesRows);

  //QMessageBox::information(this, "recahed ",y);
  table->setNumRows(noOfModesRows);
  //bool status;
  for (C_INT32 j = 0; j < noOfModesRows; j++)
    {
      // status=modes->isFluxModeReversible(j);
      if (modes->isFluxModeReversible(j) == true)
        {
          table->setText(j, 0, "Reversible");
        }
      else
        {
          table->setText(j, 0, "Irrversible");
        }
      //QString y=modes->isFluxModeReversible(j)->c_str();
      //QString x=modes->getFluxModeDescription(j).c_str();
      //QMessageBox::information(this, "recahed ",x);
      //table->setText(j, 0,y);
      //table->setText(j, 0,modes->getFluxModeDescription(j).c_str());
      table->setText(j, 1, modes->getFluxModeDescription(j).c_str());
    }
}

/*void ModesWidget::tableValueChanged(int C_UNUSED(row),
    int C_UNUSED(col))
{
  /*CWriteConfig *Mod = new CWriteConfig("try.gps");
 
  CCopasiVectorNS < CCompartment > & compartments1 = mModel->getCompartments();
  CCompartment *compartn1;
  compartn1 = compartments1[row];
 
  string x = table->text(row, col).latin1();
 
  if (col == 0)
    {
      compartn1->setName(x);
    }
  else
    {
      compartn1->setVolume(int(x.c_str()));
    }
 
  compartn1->save(*Mod);
  //Copasi->Compartmentfile.save(*Mod);
  delete Mod; 
}*/
