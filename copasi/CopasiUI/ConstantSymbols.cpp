/*******************************************************************
 **  $ CopasiUI/ConstantSymbols.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Constant Symbols
 ********************************************************************/
#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include "ConstantSymbols.h"
#include "mathmodel/CMathConstant.h"
#include "mathmodel/CMathModel.h"
#include "listviews.h"
#include <qfont.h>

/**
 *  Constructs a Widget for the Metabolites subsection of the tree for 
 *  displaying the Metabolites in model 'model'.
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
ConstantSymbols::ConstantSymbols(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  mModel = NULL;
  table = new MyTable(0, 4, this, "tblConstantSymbols");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Symbol");
  tableHeader->setLabel(1, "Constant");
  tableHeader->setLabel(2, "Reaction");
  tableHeader->setLabel(3, "Value");

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

  table->sortColumn(2, true, true);
  table->setSorting(true);
  table->setFocusPolicy(QWidget::WheelFocus);
  table->setProtected(true);

  // signals and slots connections
  connect(table, SIGNAL(selectionChanged ()), this, SLOT(slotTableSelectionChanged ()));
  connect(btnOK, SIGNAL(clicked ()), this, SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()), this, SLOT(slotBtnCancelClicked()));
}

void ConstantSymbols::loadConstantSymbols(CMathModel *model)
{
  if (model != NULL)
    {
      mModel = model;
      //Emptying the table
      int numberOfRows = table->numRows();
      for (int i = 0; i < numberOfRows; i++)
        table->removeRow(0);

      CMathConstantParameter * pConstant;
      std::map< std::string, CMathConstantParameter * > & List =
        mModel->getConstantsList();
      std::map< std::string, CMathConstantParameter * >::iterator it =
        List.begin();
      std::map< std::string, CMathConstantParameter * >::iterator end =
        List.end();

      table->setNumRows(List.size());
      int index = 0;
      for (; it != end; ++it)
        {
          pConstant = it->second;
          table->setText(index, 0, it->first.c_str());
#ifdef XXXX
          std::map< std::string, CCopasiObject * > selection = CMathConstantParameter::getSelection();
          std::map<std::string, CCopasiObject * >::iterator it1 = selection.begin();;
          std::map< std::string, CCopasiObject * >::iterator end1 = selection.end();
          CCopasiObject * cConstant;
          QStringList comboEntries1;
          for (; it1 != end1; ++it1)
            {
              cConstant = it1->second;
              comboEntries1.push_back(cConstant->getObjectName().c_str());
            }
          QComboTableItem * item1 = new QComboTableItem(table, comboEntries1, false);
          item1->setCurrentItem(pConstant->getObject()->getName().c_str());
          table->setItem(index, 1, item1);
#endif // XXXX
          table->setText(index, 1, pConstant->getObject()->getName().c_str());
          table->setText(index, 2, pConstant->getReaction().c_str());
          table->setText(index, 3, QString::number(pConstant->getValue()));
          index++;
        }
      table->sortColumn(2, true, true);
    }
}

void ConstantSymbols::slotTableSelectionChanged()
{
  if (!table->hasFocus())
    {
      table->setFocus();
    }
}

/***********ListViews::showMessage(QString caption,QString text)------------------------>
 **
 ** Parameters:- 1. QString :- The Title that needs to be displayed in message box
 **              2. QString :_ The Text that needs to be displayed in the message box
 ** Returns  :-  void(Nothing)
 ** Description:- This method is used to show the message box on the screen
 ****************************************************************************************/

void ConstantSymbols::slotBtnOKClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to commit changes");
}

void ConstantSymbols::slotBtnCancelClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to cancel changes");
}

void ConstantSymbols::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      int newWidth = re->size().width();

      newWidth -= 35; //Accounting for the left (vertical) header width.
      float weight0 = 4.0, weight1 = 3.0, weight2 = 3.0, weight3 = 3.0 , weight4 = 3.0;
      float weightSum = weight0 + weight1 + weight2 + weight3 + weight4;
      int w0, w1, w2, w3 , w4;
      w0 = newWidth * (weight0 / weightSum);
      w1 = newWidth * (weight1 / weightSum);
      w2 = newWidth * (weight2 / weightSum);
      w3 = newWidth * (weight3 / weightSum);
      w4 = newWidth - w0 - w1 - w2 - w3;
      table->setColumnWidth(0, w0);
      table->setColumnWidth(1, w1);
      table->setColumnWidth(2, w2);
      table->setColumnWidth(3, w3);
      table->setColumnWidth(4, w4);
    }
  CopasiWidget::resizeEvent(re);
}
