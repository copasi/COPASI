/*******************************************************************
 **  $ CopasiUI/ReactionsWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the  information 
 ** obtained from the data  model about the Reactions----It is Basically
 ** the First level of Reactions.
 ********************************************************************/

#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include "listviews.h"
#include "ReactionsWidget.h"
#include <qfont.h>

/**
 *  Constructs a Widget for the Metabolites subsection of the tree.
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
ReactionsWidget::ReactionsWidget(QWidget *parent, const char * name, WFlags f)
    : QWidget(parent, name, f)
{
  mModel = NULL;
  table = new MyTable(0, 2, this, "tblReactions");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  //Setting table headers
  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Name");
  tableHeader->setLabel(1, "Reaction");

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
  connect(table, SIGNAL(doubleClicked(int, int, int, const QPoint &)), this, SLOT(slotTableCurrentChanged(int, int, int, const QPoint &)));
  connect(this, SIGNAL(name(QString &)), (ListViews*)parent, SLOT(slotReactionTableChanged(QString &)));
  connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  connect(btnOK, SIGNAL(clicked ()), this, SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()), this, SLOT(slotBtnCancelClicked()));
}

void ReactionsWidget::loadReactions(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
      //Emptying the table
      int numberOfRows = table->numRows();

      for (int i = 0; i < numberOfRows; i++)
        {
          table->removeRow(0);
        }

      CCopasiVectorNS < CReaction > & reactions = mModel->getReactions();
      C_INT32 noOfReactionsRows = reactions.size();

      table->setNumRows(noOfReactionsRows);

      // Now filling the table.
      CReaction *reactn;

      for (C_INT32 j = 0; j < noOfReactionsRows; j++)
        {
          reactn = reactions[j];
          table->setText(j, 0, reactn->getName().c_str());
          table->setText(j, 1, reactn->getChemEq().getChemicalEquation().c_str());
        }
    }
}

void ReactionsWidget::slotBtnOKClicked()
{
  //QMessageBox::information(this, "Reactions Widget", "Do you really want to commit changes");
}

void ReactionsWidget::slotBtnCancelClicked()
{
  //QMessageBox::information(this, "Reactions Widget", "Do you really want to cancel changes");
}

void ReactionsWidget::slotTableSelectionChanged()
{
  if (!table->hasFocus())
    {
      table->setFocus();
    }
}

void ReactionsWidget::resizeEvent(QResizeEvent * re)
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

void ReactionsWidget::slotTableCurrentChanged(int row, int col, int m , const QPoint & n)
{
  QString x = table->text(row, col);
  emit name(x);
  //QMessageBox::information(this, "Compartments Widget",x);
}
