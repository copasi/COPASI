/**********************************************************************
 **  $ CopasiUI/FunctionWidget1.cpp                 
 **  $ Author  : Mrinmayee Kulkarni

 ** This file creates the GUI for the  information about an individual
 ** function obtained from the functions database.It is the second level 
 ** widget for functions.  
 ***********************************************************************/
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
#include <qbuttongroup.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include <qmessagebox.h>
#include "listviews.h"
#include "utilities/CGlobals.h"
#include "function/function.h"

/*
 *  Constructs a FunctionWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */

FunctionWidget1::FunctionWidget1(QWidget *parent, const char * name, WFlags f)
    : QWidget(parent, name, f)
{
  //This is to make the Main Frame of the page
  //The Main layout used is the Vertical Layout

  QVBoxLayout *vboxLayout = new QVBoxLayout(this, 0);
  Frame0 = new QFrame(this, "Frame0");
  Frame0->setFrameShape(QFrame::Box);
  Frame0->setFrameShadow(QFrame::Plain);
  vboxLayout->addWidget(Frame0);

  //This Frame had to be added because of the border around the frame

  QVBoxLayout *vboxLayout0 = new QVBoxLayout(Frame0, 0);
  vboxLayout0->addSpacing(1);
  Frame1 = new QFrame(Frame0, "Frame1");
  vboxLayout0->addWidget(Frame1);
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

  ButtonGroup1 = new QButtonGroup ("&Function Type", Frame4);
  hBoxLayout4a->addWidget(ButtonGroup1);
  hBoxLayout4a->addSpacing(20);
  ButtonGroup1->setExclusive(TRUE);

  RadioButton1 = new QRadioButton(ButtonGroup1, "RadioButton1");
  RadioButton1->setGeometry(QRect(110, 15, 87, 20));
  RadioButton1->setText(trUtf8("reversible"));

  RadioButton2 = new QRadioButton(ButtonGroup1, "RadioButton2");
  RadioButton2->setGeometry(QRect(230, 15, 87, 20));
  RadioButton2->setText(trUtf8("irreversible"));

  RadioButton3 = new QRadioButton(ButtonGroup1, "RadioButton3");
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

  // signals and slots connections
  /*** For Cancel Button Clicked ***/
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotCancelButtonClicked()));
  connect(this, SIGNAL(signalCancelButtonClicked(QString &)), (ListViews*)parent, SLOT(slotFunctionTableChanged(QString &)));

  /*** For Commit Button Clicked ***/
  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotCommitButtonClicked()));
  //connect(this, SIGNAL(signalCancelButtonClicked(QString &)), (ListViews*)parent
}

int FunctionWidget1::isName(QString setValue)
{
  int i;

  if (mModel == NULL)
    {
      return 0;
    }

  CCopasiVectorNS< CFunction > & Functions = Copasi->FunctionDB.loadedFunctions();
  C_INT32 noOfFunctionsRows = Functions.size();
  //Now filling the table.

  CFunction *funct1;
  //int i = 0;
  myValue = -1;

  for (i = 0; i < Functions.size(); i++)
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
  int i, j;

  if (mModel == NULL)
    {
      return ;
    }

  CCopasiVectorNS< CFunction > & Functions = Copasi->FunctionDB.loadedFunctions();

  //Now filling the table.

  CFunction *funct;
  //int i = 0;
  //int myValue=-1;
  myValue = -1;

  for (i = 0; i < Functions.size(); i++)
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
      Function_Name = new QString(funct->getName().c_str());

      //Emptying the tables
      int numberOfRows1 = Table1->numRows();
      int numberOfRows2 = Table2->numRows();

      for (i = 0; i < numberOfRows1; i++)
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

      //int j;

      for (j = 0; j < noOffunctParams; j++)
        {
          Table1->setText(j, 0, functParam[j]->getName().c_str());
          Table1->setText(j, 1, CFunctionParameter::DataTypeName[functParam[j]->getType()].c_str());
          Table1->setText(j, 2, functParam[j]->getUsage().c_str());
        }

      // for application table
      CCopasiVectorNS < CUsageRange > & functUsage = funct2.getUsageDescriptions();

      C_INT32 noOfApplns = functUsage.size();

      Table2->setNumRows(noOfApplns);

      for (j = 0; j < noOfApplns; j++)
        {
          Table2->setText(j, 0, functUsage[j]->getName().c_str());
          Table2->setText(j, 1, QString::number(functUsage[j]->getLow()));

          switch (functUsage[j]->getHigh())
            {
            case 0:
              Table2->setText(j, 2, "NA");
              break;

            default:
              Table2->setText(j, 2, QString::number(functUsage[j]->getHigh()));
            }
        }

      /***********  RADIO BUTTONS ***********************/
      /*** if function is predefined ****/
      /*** disables some widgets so user cannot make changes **/
      if (funct->getType() == 1 || funct->getType() == 2)
        {
          RadioButton1->setEnabled(FALSE);
          RadioButton2->setEnabled(FALSE);
          RadioButton3->setEnabled(FALSE);
          commitChanges->setEnabled(FALSE);
          cancelChanges->setEnabled(FALSE);
          LineEdit1->setReadOnly(TRUE);
          LineEdit2->setReadOnly(TRUE);
          Table1->setReadOnly(TRUE);
          Table2->setReadOnly(TRUE);
        }

      /*** if function is user-defined *****/
      else
        {
          RadioButton1->setEnabled(TRUE);
          RadioButton2->setEnabled(TRUE);
          RadioButton3->setEnabled(TRUE);
          LineEdit1->setReadOnly(FALSE);
          LineEdit2->setReadOnly(FALSE);
          Table1->setReadOnly(FALSE);
          Table2->setReadOnly(FALSE);
          commitChanges->setEnabled(TRUE);
          cancelChanges->setEnabled(TRUE);
        }

      if (funct->isReversible() == -1)
        {
          RadioButton1->setEnabled(TRUE);
          RadioButton1->setChecked(TRUE);
        }
      else
        if (funct->isReversible() == TRUE)
          {
            RadioButton2->setEnabled(TRUE);
            RadioButton2->setChecked(TRUE);
          }
        else
          if (funct->isReversible() == FALSE)
            {
              RadioButton3->setEnabled(TRUE);
              RadioButton3->setChecked(TRUE);
            }
    }

} //end of function

void FunctionWidget1::slotCancelButtonClicked()
{
  QMessageBox::information(this, "Function Widget1", "Cancel changes to Widget");
  emit signalCancelButtonClicked(*Function_Name);
}

void FunctionWidget1::slotCommitButtonClicked()
{
  int i, j;
  QMessageBox::information(this, "Function Widget1", "Saving changes to Widget");

  CWriteConfig * sFunctionDB = new CWriteConfig("FunctionDB1.gps");

  CCopasiVectorNS< CFunction > & Functions = Copasi->FunctionDB.loadedFunctions();
  CFunction *funct;
  funct = Functions[myValue];
  /**** for Name and Description ****/
  new_Name = new QString(LineEdit1->text());
  new_Description = new QString(LineEdit2->text());
  funct->setName(new_Name->latin1());
  funct->setDescription(new_Description->latin1());
  /**** For Radio Buttons ****/

  if (RadioButton1->isChecked() == TRUE)
    {
      funct->setReversible(TriUnspecified);
    }
  else
    if (RadioButton2->isChecked() == TRUE)
      {
        funct->setReversible(TriTrue);
      }
    else
      funct->setReversible(TriFalse);

  /***** for Table 1: Parameters table *****/
  CFunction &funct2 = *Copasi->FunctionDB.loadedFunctions()[funct->getName()];

  CFunctionParameters &functParam = funct2.getParameters();

  C_INT32 noOffunctParams = functParam.size();

  Table1->setNumRows(noOffunctParams);

  // for parameters table

  //int j;

  for (j = 0; j < noOffunctParams; j++)
    {
      //param_Name = new QString(Table1->text(j,0));
      param_Name = Table1->text(j, 0);

      /****** conv enumerated types ???? *****/
      //Table1->setText(j, 1, enumname[functParam[j]->getType()]);
      param_Type = Table1->text(j, 1);

      //param_Usage = new QString(Table1->text(j,2));
      param_Usage = Table1->text(j, 2);

      /***** set new values *****/
      functParam[j]->setName(param_Name.latin1());
      /**** enum ??? ****/
      //functParam[j]->setType(param_Type);

      for (i = 0; i < 11; i++)
        {
          if (QString:: compare(param_Type,
                                CFunctionParameter::DataTypeName[i].c_str()))
            enum_Type = i;
        }

      functParam[j]->setType((CFunctionParameter::DataType) enum_Type);
      functParam[j]->setUsage(param_Usage.latin1());
    }

  /***** for Table 2: Applications table *****/
  CCopasiVectorNS < CUsageRange > & functUsage = funct2.getUsageDescriptions();

  C_INT32 noOfApplns = functUsage.size();

  Table2->setNumRows(noOfApplns);

  for (j = 0; j < noOfApplns; j++)
    {
      //app_Desc = new QString(Table2->text(j,0));
      app_Desc = Table2->text(j, 0);
      //app_Low=new QString(Table2->text(j,1));
      app_Low = Table2->text(j, 1);
      int_Low = app_Low.toInt();
      app_High = Table2->text(j, 2);
      //app_High = new QString(Table2->text(j,2));

      if (QString::compare(app_High, "NA") == 0)
        {
          int_High = 0;
        }
      else
        {
          int_High = app_High.toInt();
        }

      /***** there is no setName  here ????? ******/
      functUsage[j]->setUsage(app_Desc.latin1());

      functUsage[j]->setLow(int_Low);

      functUsage[j]->setHigh(int_High);
    }

  Copasi->FunctionDB.save(*sFunctionDB);
  delete sFunctionDB;
}
