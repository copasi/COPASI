/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/FunctionSymbols.cpp,v $
   $Revision: 1.17 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2003/10/30 17:57:33 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/FunctionSymbols.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the 
 ** information obtained from the data model about the 
 ** Function Symbols
 ********************************************************************/
#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include <qfont.h>

#include "FunctionSymbols.h"
#include "mathmodel/CMathModel.h"
#include "mathmodel/CMathSymbol.h"
#include "utilities/CGlobals.h"
#include "listviews.h"
#include "function/CFunctionDB.h"
#include "function/CFunction.h" 
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
FunctionSymbols::FunctionSymbols(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  mModel = NULL;
  table = new MyTable(this, "tblFunctionSymbols");
  table->setNumCols(3);
  table->setNumRows(-1);
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(table);

  QHeader *tableHeader = table->horizontalHeader();
  tableHeader->setLabel(0, "Symbol");
  tableHeader->setLabel(1, "Function");
  tableHeader->setLabel(2, "Parameters");

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
  table->setProtected(true);

  // signals and slots connections
  connect(table, SIGNAL(selectionChanged ()),
          this, SLOT(slotTableSelectionChanged ()));
  connect(btnOK, SIGNAL(clicked ()),
          this, SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()),
          this, SLOT(slotBtnCancelClicked()));
}

void FunctionSymbols::loadFunctionSymbols(CMathModel *model)
{
  if (model != NULL)
    {
      mModel = model;

      int numberOfRows = table->numRows();

      for (int i = 0; i < numberOfRows; i++)
        {
          table->removeRow(0);
        }

      Copasi->pFunctionDB->loadedFunctions();

      std::map< std::string, CMathSymbol * > functionList = mModel->getFunctionList();
      std::map<std::string, CMathSymbol * >::iterator it;
      CMathSymbol * mathSymbol;

      table->setNumRows(functionList.size());
      int index = 0;
      for (it = functionList.begin(); it != functionList.end();++it)
        {
          mathSymbol = it->second;
          table->setText(index, 0, it->first.c_str());

          CFunction *metabObject = (CFunction *)mathSymbol->getObject();
          table->setText(index, 1, metabObject->getName().c_str());
          QStringList functionType;
          CFunctionParameters &functParam = metabObject->getParameters();
          for (int j = 0; j < functParam.size(); j++)
            {
              functionType.push_back(functParam[j]->getName().c_str());
            }
          QComboTableItem * item = new QComboTableItem(table, functionType, false);
          table->setItem(index, 2, item);
          //item->setCurrentItem(temp);
          index++;
        }
    }
}

void FunctionSymbols::slotTableSelectionChanged()
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

void FunctionSymbols::slotBtnOKClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to commit changes");
}

void FunctionSymbols::slotBtnCancelClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to cancel changes");
}

void FunctionSymbols::resizeEvent(QResizeEvent * re)
{
  if (isVisible())
    {
      int newWidth = re->size().width();
      newWidth -= 35; //Accounting for the left (vertical) header width.
      float weight0 = 4.0, weight1 = 3.0, weight2 = 3.0;
      float weightSum = weight0 + weight1 + weight2;
      int w0, w1, w2;
      w0 = newWidth * (weight0 / weightSum);
      w1 = newWidth * (weight1 / weightSum);
      w2 = newWidth - w0 - w1;
      table->setColumnWidth(0, w0);
      table->setColumnWidth(1, w1);
      table->setColumnWidth(2, w2);
    }
  CopasiWidget::resizeEvent(re);
}
