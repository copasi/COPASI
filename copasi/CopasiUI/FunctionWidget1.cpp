/**********************************************************************
 **  $ CopasiUI/FunctionWidget1.cpp                 
 **  $ Author  : Mrinmayee Kulkarni

 ** This file creates the GUI for the  information about an individual
 ** function obtained from the functions database.It is the second level 
 ** widget for functions.  
 ***********************************************************************/
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
#include "copasi.h"
#include "FunctionWidget1.h"
#include "model/CMetab.h"
#include "listviews.h"
#include "utilities/CGlobals.h"
#include "function/function.h"

/*
 *  Constructs a FunctionWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
FunctionWidget1::FunctionWidget1(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("FunctionWidget1");
  resize(719, 539);
  setCaption(trUtf8("FunctionWidget1"));
  FunctionWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "FunctionWidget1Layout");

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Description"));

  FunctionWidget1Layout->addWidget(TextLabel2, 1, 0);

  LineEdit2 = new QLineEdit(this, "LineEdit2");

  FunctionWidget1Layout->addWidget(LineEdit2, 1, 1);

  Line2 = new QFrame(this, "Line2");
  Line2->setFrameShape(QFrame::HLine);
  Line2->setFrameShadow(QFrame::Sunken);
  Line2->setFrameShape(QFrame::HLine);

  FunctionWidget1Layout->addMultiCellWidget(Line2, 4, 4, 0, 1);

  Layout1 = new QHBoxLayout(0, 0, 6, "Layout1");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit Changes"));
  Layout1->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Cancel Changes"));
  Layout1->addWidget(cancelChanges);

  FunctionWidget1Layout->addMultiCellLayout(Layout1, 11, 11, 0, 1);

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Parameters"));

  FunctionWidget1Layout->addWidget(TextLabel4, 5, 0);

  Line3 = new QFrame(this, "Line3");
  Line3->setFrameShape(QFrame::HLine);
  Line3->setFrameShadow(QFrame::Sunken);
  Line3->setFrameShape(QFrame::HLine);

  FunctionWidget1Layout->addMultiCellWidget(Line3, 10, 10, 0, 1);

  LineEdit1 = new QLineEdit(this, "LineEdit1");

  FunctionWidget1Layout->addWidget(LineEdit1, 0, 1);

  Table2 = new QTable(this, "Table2");
  Table2->setNumCols(Table2->numCols() + 1); Table2->horizontalHeader()->setLabel(Table2->numCols() - 1, trUtf8("Description"));
  Table2->setNumCols(Table2->numCols() + 1); Table2->horizontalHeader()->setLabel(Table2->numCols() - 1, trUtf8("Min"));
  Table2->setNumCols(Table2->numCols() + 1); Table2->horizontalHeader()->setLabel(Table2->numCols() - 1, trUtf8("Max"));
  Table2->setNumRows(3);
  Table2->setNumCols(3);

  FunctionWidget1Layout->addMultiCellWidget(Table2, 8, 9, 1, 1);
  QSpacerItem* spacer = new QSpacerItem(71, 80, QSizePolicy::Minimum, QSizePolicy::Expanding);
  FunctionWidget1Layout->addItem(spacer, 9, 0);

  TextLabel5 = new QLabel(this, "TextLabel5");
  TextLabel5->setText(trUtf8("Application"));

  FunctionWidget1Layout->addWidget(TextLabel5, 8, 0);

  Line4 = new QFrame(this, "Line4");
  Line4->setFrameShape(QFrame::HLine);
  Line4->setFrameShadow(QFrame::Sunken);
  Line4->setFrameShape(QFrame::HLine);

  FunctionWidget1Layout->addMultiCellWidget(Line4, 7, 7, 0, 1);

  Table1 = new QTable(this, "Table1");
  Table1->setNumCols(Table1->numCols() + 1); Table1->horizontalHeader()->setLabel(Table1->numCols() - 1, trUtf8("Name"));
  Table1->setNumCols(Table1->numCols() + 1); Table1->horizontalHeader()->setLabel(Table1->numCols() - 1, trUtf8("Data Type"));
  Table1->setNumCols(Table1->numCols() + 1); Table1->horizontalHeader()->setLabel(Table1->numCols() - 1, trUtf8("Description"));
  Table1->setNumRows(3);
  Table1->setNumCols(3);

  FunctionWidget1Layout->addMultiCellWidget(Table1, 5, 6, 1, 1);

  Line1 = new QFrame(this, "Line1");
  Line1->setFrameShape(QFrame::HLine);
  Line1->setFrameShadow(QFrame::Sunken);
  Line1->setFrameShape(QFrame::HLine);

  FunctionWidget1Layout->addMultiCellWidget(Line1, 2, 2, 0, 1);
  QSpacerItem* spacer_2 = new QSpacerItem(71, 190, QSizePolicy::Minimum, QSizePolicy::Expanding);
  FunctionWidget1Layout->addItem(spacer_2, 6, 0);

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Function Name:"));

  FunctionWidget1Layout->addWidget(TextLabel1, 0, 0);

  ButtonGroup1 = new QButtonGroup(this, "ButtonGroup1");
  ButtonGroup1->setFrameShape(QButtonGroup::WinPanel);
  ButtonGroup1->setTitle(trUtf8(""));
  ButtonGroup1->setExclusive(TRUE);
  ButtonGroup1->setRadioButtonExclusive(TRUE);

  RadioButton1 = new QRadioButton(ButtonGroup1, "RadioButton1");
  RadioButton1->setGeometry(QRect(71, 21, 129, 18));
  RadioButton1->setText(trUtf8("reversible"));

  RadioButton2 = new QRadioButton(ButtonGroup1, "RadioButton2");
  RadioButton2->setGeometry(QRect(206, 21, 128, 18));
  RadioButton2->setText(trUtf8("irreversible"));

  RadioButton3 = new QRadioButton(ButtonGroup1, "RadioButton3");
  RadioButton3->setGeometry(QRect(340, 21, 129, 18));
  RadioButton3->setText(trUtf8("General"));

  FunctionWidget1Layout->addWidget(ButtonGroup1, 3, 1);

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Function Type"));

  FunctionWidget1Layout->addWidget(TextLabel3, 3, 0);

  // signals and slots connections
  /*** For Cancel Button Clicked ***/
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotCancelButtonClicked()));
  connect(this, SIGNAL(signalCancelButtonClicked(const QString &)), (ListViews*)parent, SLOT(slotFunctionTableChanged(const QString &)));
  /*** For Commit Button Clicked ***/
  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotCommitButtonClicked()));
  //connect(this, SIGNAL(signalCancelButtonClicked(QString &)), (ListViews*)parent
}

int FunctionWidget1::isName(QString setValue)
{
  int i;

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

void FunctionWidget1::loadName(QString setValue)
{
  int i, j;

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
          QString temp = CFunctionParameter::DataTypeName[functParam[j]->getType()].c_str();
          QStringList functionType;
          for (i = 0; CFunctionParameter::DataTypeName[i] != ""; i++)
            functionType.push_back(CFunctionParameter::DataTypeName[i].c_str());

          QComboTableItem * item = new QComboTableItem(Table1, functionType, true);
          Table1->setItem(j, 1, item);
          item->setCurrentItem(temp);
          //Table1->setText(j, 1, CFunctionParameter::DataTypeName[functParam[j]->getType()].c_str());
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

            case - 1:
              Table2->setText(j, 2, "infinity");
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
          RadioButton1->setEnabled(false);
          RadioButton2->setEnabled(false);
          RadioButton3->setEnabled(false);
          commitChanges->setEnabled(false);
          cancelChanges->setEnabled(false);
          LineEdit1->setReadOnly(true);
          LineEdit2->setReadOnly(true);
          Table1->setReadOnly(true);
          Table2->setReadOnly(true);
        }

      /*** if function is user-defined *****/
      else
        {
          RadioButton1->setEnabled(true);
          RadioButton2->setEnabled(true);
          RadioButton3->setEnabled(true);
          LineEdit1->setReadOnly(true); //Function Name cannot be changed
          LineEdit2->setReadOnly(false);
          Table1->setReadOnly(false);
          Table2->setReadOnly(false);
          commitChanges->setEnabled(true);
          cancelChanges->setEnabled(true);
        }

      switch (funct->isReversible())
        {
        case TriUnspecified:
          RadioButton3->setEnabled(true);
          RadioButton3->setChecked(true);
          break;

        case TriFalse:
          RadioButton2->setEnabled(true);
          RadioButton2->setChecked(true);
          break;

        case TriTrue:
          RadioButton1->setEnabled(true);
          RadioButton1->setChecked(true);
          break;
        }
    }
} //end of function

void FunctionWidget1::slotCancelButtonClicked()
{
  //QMessageBox::information(this, "Function Widget1", "Cancel changes to Widget");
  emit signalCancelButtonClicked(*Function_Name);
}

void FunctionWidget1::slotCommitButtonClicked()
{
  int i, j;
  //QMessageBox::information(this, "Function Widget1", "Saving changes to Widget");

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

  if (RadioButton1->isChecked() == true)
    {
      funct->setReversible(TriUnspecified);
    }
  else
    if (RadioButton2->isChecked() == true)
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
