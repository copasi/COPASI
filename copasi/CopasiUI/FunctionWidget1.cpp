/****************************************************************************
 ** Form implementation generated from reading ui file '.\function.ui'
 **
 ** Created: Wed May 29 16:39:16 2002
 **      by:  The User Interface Compiler (uic)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/
#include "FunctionWidget1.h"
#include "model/CMetab.h"
#include <qvariant.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qradiobutton.h>
#include <qtable.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include <qimage.h>
#include <qpixmap.h>
#include <qgroupbox.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include "listviews.h"
#include "utilities/CGlobals.h"
#include "function/function.h" 
/*
 *  Constructs a FunctionWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */ 
/*FunctionWidget1::FunctionWidget1(QWidget* parent,  const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
    
 
    LineEdit1 = new QLineEdit(this, "LineEdit1");
    LineEdit1->setGeometry(QRect(110, 20, 91, 20)); 
 
    TextLabel1 = new QLabel(this, "TextLabel1");
    TextLabel1->setGeometry(QRect(20, 20, 56, 20)); 
    TextLabel1->setText(trUtf8("Name"));
 
    TextLabel2 = new QLabel(this, "TextLabel2");
    TextLabel2->setGeometry(QRect(20, 60, 56, 20)); 
    TextLabel2->setText(trUtf8("Description"));
 
    LineEdit2 = new QLineEdit(this, "LineEdit2");
    LineEdit2->setGeometry(QRect(110, 60, 330, 20)); 
 
    Table1 = new QTable(this, "Table1");
    Table1->setNumCols(Table1->numCols() + 1);    Table1->horizontalHeader()->setLabel(Table1->numCols() - 1, trUtf8("Name"));
    Table1->setNumCols(Table1->numCols() + 1);    Table1->horizontalHeader()->setLabel(Table1->numCols() - 1, trUtf8("Data Type"));
    Table1->setNumCols(Table1->numCols() + 1);    Table1->horizontalHeader()->setLabel(Table1->numCols() - 1, trUtf8("Description"));
    Table1->setNumRows(Table1->numRows() + 1);    Table1->verticalHeader()->setLabel(Table1->numRows() - 1, trUtf8("1"));
    Table1->setNumRows(Table1->numRows() + 1);    Table1->verticalHeader()->setLabel(Table1->numRows() - 1, trUtf8("2"));
    Table1->setNumRows(Table1->numRows() + 1);    Table1->verticalHeader()->setLabel(Table1->numRows() - 1, trUtf8("3"));
    Table1->setGeometry(QRect(110, 160, 335, 104)); 
    Table1->setNumRows(3);
    Table1->setNumCols(3);
 
    Table2 = new QTable(this, "Table2");
    Table2->setNumCols(Table2->numCols() + 1);    Table2->horizontalHeader()->setLabel(Table2->numCols() - 1, trUtf8("Description"));
    Table2->setNumCols(Table2->numCols() + 1);    Table2->horizontalHeader()->setLabel(Table2->numCols() - 1, trUtf8("Min"));
    Table2->setNumCols(Table2->numCols() + 1);    Table2->horizontalHeader()->setLabel(Table2->numCols() - 1, trUtf8("Max"));
    Table2->setNumRows(Table2->numRows() + 1);    Table2->verticalHeader()->setLabel(Table2->numRows() - 1, trUtf8("1"));
    Table2->setNumRows(Table2->numRows() + 1);    Table2->verticalHeader()->setLabel(Table2->numRows() - 1, trUtf8("2"));
    Table2->setNumRows(Table2->numRows() + 1);    Table2->verticalHeader()->setLabel(Table2->numRows() - 1, trUtf8("3"));
    Table2->setGeometry(QRect(110, 300, 335, 104)); 
    Table2->setNumRows(3);
    Table2->setNumCols(3);
 
    TextLabel3 = new QLabel(this, "TextLabel3");
    TextLabel3->setGeometry(QRect(20, 160, 56, 20)); 
    TextLabel3->setText(trUtf8("Parameters"));
 
    TextLabel4 = new QLabel(this, "TextLabel4");
    TextLabel4->setGeometry(QRect(20, 300, 56, 20)); 
    TextLabel4->setText(trUtf8("Application"));
 
    RadioButton1 = new QRadioButton(this, "RadioButton1");
    RadioButton1->setGeometry(QRect(110, 110, 87, 20)); 
    RadioButton1->setText(trUtf8("reversible"));
 
    RadioButton2 = new QRadioButton(this, "RadioButton2");
    RadioButton2->setGeometry(QRect(230, 110, 87, 20)); 
    RadioButton2->setText(trUtf8("irreversible"));
 
    RadioButton3 = new QRadioButton(this, "RadioButton3");
    RadioButton3->setGeometry(QRect(350, 110, 87, 20)); 
    RadioButton3->setText(trUtf8("unknown"));
} */

FunctionWidget1::FunctionWidget1(QWidget *parent, const char * name, WFlags f)
    : QWidget(parent, name, f)
{
  //This is to make the Main Frame of the page
  //The Main layout used is the Vertical Layout

  QVBoxLayout *vboxLayout = new QVBoxLayout(this, 0);
  Frame1 = new QFrame(this, "Frame1");
  Frame1->setFrameShape(QFrame::Box);
  Frame1->setFrameShadow(QFrame::Plain);
  vboxLayout->addWidget(Frame1);

  //This Frame had to be added because of the border around the frame

  QVBoxLayout *vboxLayout1 = new QVBoxLayout(Frame1, 0);
  vboxLayout1->addSpacing(10);

  // adding frames to each row
  Frame2 = new QFrame(Frame1, "Frame2");
  vboxLayout1->addWidget(Frame2);
  vboxLayout1->addSpacing(10);
  Frame3 = new QFrame(Frame1, "Frame3");
  vboxLayout1->addSpacing(10);
  vboxLayout1->addWidget(Frame3);
  vboxLayout1->addSpacing(20);
  Frame4 = new QFrame(Frame1, "Frame4");
  vboxLayout1->addWidget(Frame4);
  Frame5 = new QFrame(Frame1, "Frame5");
  vboxLayout1->addWidget(Frame5);
  Frame6 = new QFrame(Frame1, "Frame6");
  vboxLayout1->addWidget(Frame6);
  Frame7 = new QFrame(Frame1, "Frame7");
  vboxLayout1->addWidget(Frame7);

  // setting layouts for each row
  //first row
  QHBoxLayout *hBoxLayout2a = new QHBoxLayout(Frame2, 0);
  hBoxLayout2a->addSpacing(15);
  TextLabel1 = new QLabel("Function Name", Frame2);
  hBoxLayout2a->addWidget(TextLabel1);
  hBoxLayout2a->addSpacing(15);
  LineEdit1 = new QLineEdit("", Frame2);
  hBoxLayout2a->addWidget(LineEdit1);
  hBoxLayout2a->addSpacing(15);
  // second row
  QHBoxLayout *hBoxLayout3a = new QHBoxLayout(Frame3, 0);
  hBoxLayout3a->addSpacing(15);
  TextLabel2 = new QLabel("Description", Frame3);
  hBoxLayout3a->addWidget(TextLabel2);
  hBoxLayout3a->addSpacing(20);
  LineEdit2 = new QLineEdit("", Frame3);
  hBoxLayout3a->addWidget(LineEdit2);
  hBoxLayout3a->addSpacing(20);
  // third Row
  QHBoxLayout *hBoxLayout4a = new QHBoxLayout(Frame4, 0);
  hBoxLayout4a->addSpacing(15);

  GroupBox1 = new QGroupBox ("&Function Type", Frame4);
  hBoxLayout4a->addWidget(GroupBox1);
  hBoxLayout4a->addSpacing(20);

  RadioButton1 = new QRadioButton(GroupBox1, "RadioButton1");
  RadioButton1->setGeometry(QRect(110, 15, 87, 20));
  RadioButton1->setText(trUtf8("reversible"));

  RadioButton2 = new QRadioButton(GroupBox1, "RadioButton2");
  RadioButton2->setGeometry(QRect(230, 15, 87, 20));
  RadioButton2->setText(trUtf8("irreversible"));

  RadioButton3 = new QRadioButton(GroupBox1, "RadioButton3");
  RadioButton3->setGeometry(QRect(350, 15, 87, 20));
  RadioButton3->setText(trUtf8("unknown"));

  // fourth Row
  QHBoxLayout *hBoxLayout5a = new QHBoxLayout(Frame5, 0);
  hBoxLayout5a->addSpacing(15);
  Table1 = new QTable(Frame5, "Table1");
  hBoxLayout5a->addWidget(Table1);
  Table1->setNumCols(Table1->numCols() + 1);
  Table1->horizontalHeader()->setLabel(Table1->numCols() - 1, trUtf8("Name"));
  Table1->setNumCols(Table1->numCols() + 1);
  Table1->horizontalHeader()->setLabel(Table1->numCols() - 1, trUtf8("Data Type"));
  Table1->setNumCols(Table1->numCols() + 1);
  Table1->horizontalHeader()->setLabel(Table1->numCols() - 1, trUtf8("Description"));
  Table1->setNumRows(Table1->numRows() + 1);
  Table1->verticalHeader()->setLabel(Table1->numRows() - 1, trUtf8("1"));
  Table1->setNumRows(Table1->numRows() + 1);
  Table1->verticalHeader()->setLabel(Table1->numRows() - 1, trUtf8("2"));
  Table1->setNumRows(Table1->numRows() + 1);
  Table1->verticalHeader()->setLabel(Table1->numRows() - 1, trUtf8("3"));
  Table1->setNumRows(3);
  Table1->setNumCols(3);
  Table1->sortColumn (0, TRUE, TRUE);
  Table1->setFixedSize(335, 104);
  Table1->setFocusPolicy(QWidget::WheelFocus);
  TextLabel3 = new QLabel(Frame5, "TextLabel3");
  TextLabel3->setGeometry(QRect(20, 90, 56, 20));
  TextLabel3->setText(trUtf8("Parameters"));

  // fifth row
  QHBoxLayout *hBoxLayout6a = new QHBoxLayout(Frame6, 0);
  hBoxLayout6a->addSpacing(15);
  Table2 = new QTable(Frame6, "Table2");
  hBoxLayout6a->addWidget(Table2);
  Table2->setNumCols(Table2->numCols() + 1);
  Table2->horizontalHeader()->setLabel(Table2->numCols() - 1, trUtf8("Description"));
  Table2->setNumCols(Table2->numCols() + 1);
  Table2->horizontalHeader()->setLabel(Table2->numCols() - 1, trUtf8("Min"));
  Table2->setNumCols(Table2->numCols() + 1);
  Table2->horizontalHeader()->setLabel(Table2->numCols() - 1, trUtf8("Max"));
  Table2->setNumRows(Table2->numRows() + 1);
  Table2->verticalHeader()->setLabel(Table2->numRows() - 1, trUtf8("1"));
  Table2->setNumRows(Table2->numRows() + 1);
  Table2->verticalHeader()->setLabel(Table2->numRows() - 1, trUtf8("2"));
  Table2->setNumRows(Table2->numRows() + 1);
  Table2->verticalHeader()->setLabel(Table2->numRows() - 1, trUtf8("3"));
  Table2->setNumRows(3);
  Table2->setNumCols(3);
  Table2->sortColumn (0, TRUE, TRUE);
  Table2->setFixedSize(335, 104);
  Table2->setFocusPolicy(QWidget::WheelFocus);
  TextLabel4 = new QLabel(Frame6, "TextLabel4");
  TextLabel4->setGeometry(QRect(20, 90, 56, 20));
  TextLabel4->setText(trUtf8("Application"));

  //sixth row
  QHBoxLayout *hBoxLayout7a = new QHBoxLayout(Frame7, 0);
  hBoxLayout7a->addSpacing(15);
  commitChanges = new QPushButton("&Commit Changes", Frame7);
  cancelChanges = new QPushButton("&Cancel Changes", Frame7);
  hBoxLayout7a->addWidget(commitChanges);
  hBoxLayout7a->addSpacing(15);
  hBoxLayout7a->addWidget(cancelChanges);
}

/********* changes *********************/

int FunctionWidget1::isName(QString setValue)
{
  if (mModel == NULL)
    {
      return 0;
    }

  CCopasiVectorNS< CFunction > & Functions = Copasi->FunctionDB.loadedFunctions();
  C_INT32 noOfFunctionsRows = Functions.size();

  //Now filling the table.

  //CFunction *funct1 = Copasi->FunctionDB.loadedFunctions()["name"];
  CFunction *funct1;
  int i = 0;
  int myValue = -1;

  for (; i < Functions.size(); i++)
    {
      funct1 = Functions[i];
      int value = QString::compare(funct1->getName().c_str(), setValue);

      if (!value)
        {
          myValue = i;
          break;
        }
    }

  if (myValue != -1)
    {
      funct1 = Functions[myValue];

      if (funct1 != NULL)
        {
          loadName(setValue);

          return 1;
        }
      else
        return 0;
    }

  return 0;
}

void FunctionWidget1::loadFunction(CModel *model)
{
  if (model != NULL)
    {
      mModel = model;
    }
}

void FunctionWidget1::loadName(QString setValue)
{
  if (mModel == NULL)
    {
      return ;
    }

  CCopasiVectorNS< CFunction > & Functions = Copasi->FunctionDB.loadedFunctions();

  //Now filling the table.

  CFunction *funct;
  //CFunction *funct2 = Copasi->FunctionDB.loadedFunctions()["name"]
  int i = 0;
  int myValue = -1;

  for (; i < Functions.size(); i++)
    {
      funct = Functions[i];
      int value = QString::compare(funct->getName().c_str(), setValue);

      if (!value)
        {
          myValue = i;
          break;
        }
    }

  if (myValue != -1)
    {
      funct = Functions[myValue];

      // for Name and Description text boxes
      LineEdit1->setText(funct->getName().c_str());
      LineEdit2->setText(funct->getDescription().c_str());

      //Emptying the tables
      int numberOfRows1 = Table1->numRows();
      int numberOfRows2 = Table2->numRows();

      for (int i = 0; i < numberOfRows1; i++)
        {
          Table1->removeRow(0);
        }

      for (i = 0; i < numberOfRows2; i++)
        {
          Table2->removeRow(0);
        }

      CFunction &funct2 = *Copasi->FunctionDB.loadedFunctions()[funct->getName()];
      CFunctionParameters &functParam = funct2.getParameters();
      C_INT32 noOffunctParams = functParam.size();
      Table1->setNumRows(noOffunctParams);
      // for parameters table

      for (int j = 0; j < noOffunctParams; j++)
        {
          Table1->setText(j, 0, functParam[j]->getName().c_str());
          //Table1->setText(j,1,functParam[j]->getType());
          /**** print enum value as string ***/
          Table1->setText(j, 1, QString::number((functParam[j]->getType())));
          Table1->setText(j, 2, functParam[j]->getUsage().c_str());
        }

      CCopasiVectorNS < CUsageRange > & functUsage = funct2.getUsageDescriptions();
      C_INT32 noOfApplns = functUsage.size();
      Table2->setNumRows(noOfApplns);

      for (j = 0; j < noOfApplns; j++)
        {
          Table2->setText(j, 0, functUsage[j]->getName().c_str());
          Table2->setText(j, 1, QString::number(functUsage[j]->getLow()));
          Table2->setText(j, 2, QString::number(functUsage[j]->getHigh()));
          //functUsage[j]->getType();
          //functUsage[j]->getUsage();
        }

      /******** make changes here **********************/
      /*********** FOR RADIO BUTTONS ***********************/
      /*if(QString::number(metab->getStatus())=="0")
      {
      RadioButton1->setChecked(true);
      RadioButton3->setChecked(true);
      }
      else if(QString::number(metab->getStatus())=="1")
      {
      RadioButton2->setChecked(true);
      RadioButton4->setChecked(true);
      }
      else if(QString::number(metab->getStatus())=="2")
      {
      RadioButton2->setChecked(true);
      RadioButton5->setChecked(true);
      }

      ComboBox1->insertStringList((metab->getCompartment())->getName().c_str(),-1);

      if((metab->getCompartment())->getName()=="Glycosome")
      {
      ComboBox1->insertItem("Cytosol",1);
      ComboBox1->insertItem("Exterior",2);
      }
      else if((metab->getCompartment())->getName()=="Cytosol")
      {
      ComboBox1->insertItem("Glycosome",1);
      ComboBox1->insertItem("Exterior",2);
      }
      else
      {
      ComboBox1->insertItem("Glycosome",1);
      ComboBox1->insertItem("Cytosol",2);

      } */
    }

} //end of function
