/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/FunctionWidget1.cpp,v $
   $Revision: 1.59 $
   $Name:  $
   $Author: chlee $ 
   $Date: 2003/11/07 20:32:44 $
   End CVS Header */

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
#include <qtextbrowser.h>
#include <qmessagebox.h>

#include "copasi.h"
#include "utilities/CCopasiException.h"
#include "FunctionWidget1.h"
#include "model/CMetab.h"
#include "listviews.h"
#include "utilities/CGlobals.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CKinFunction.h"
#include "report/CKeyFactory.h"

#include "./icons/product.xpm"
#include "./icons/substrate.xpm"
#include "./icons/modifier.xpm"
#include "parametertable.h" // just for the table item widgets

#include "MyLineEdit.h"

/*
 *  Constructs a FunctionWidget1 which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
FunctionWidget1::FunctionWidget1(QWidget* parent, const char* name, WFlags fl):
    CopasiWidget(parent, name, fl),
    objKey(""),
    pFunction(NULL)
{
  if (!name)
    setName("FunctionWidget1");
  setCaption(trUtf8("FunctionWidget1"));
  FunctionWidget1Layout = new QGridLayout(this, 1, 1, 11, 6, "FunctionWidget1Layout");

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Description"));

  FunctionWidget1Layout->addWidget(TextLabel2, 1, 0);

  //textBrowser = new QTextBrowser (this, "Text Browser");
  textBrowser = new MyLineEdit(this, "Text Browser");

  FunctionWidget1Layout->addWidget(textBrowser, 1, 1);

  Line2 = new QFrame(this, "Line2");
  Line2->setFrameShape(QFrame::HLine);
  Line2->setFrameShadow(QFrame::Sunken);
  Line2->setFrameShape(QFrame::HLine);

  FunctionWidget1Layout->addMultiCellWidget(Line2, 4, 4, 0, 1);

  Layout1 = new QHBoxLayout(0, 0, 6, "Layout1");

  commitChanges = new QPushButton(this, "commitChanges");
  commitChanges->setText(trUtf8("Commit"));
  Layout1->addWidget(commitChanges);

  cancelChanges = new QPushButton(this, "cancelChanges");
  cancelChanges->setText(trUtf8("Cancel"));
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
  ButtonGroup1->setMinimumHeight(30);
  ButtonGroup1->setMaximumHeight(30);
  ButtonGroup1->setTitle(trUtf8(""));
  ButtonGroup1->setExclusive(TRUE);
  ButtonGroup1->setRadioButtonExclusive(TRUE);

  RadioButton1 = new QRadioButton(ButtonGroup1, "RadioButton1");
  RadioButton1->setGeometry(QRect(21, 7, 85, 18));
  RadioButton1->setText(trUtf8("reversible"));

  RadioButton2 = new QRadioButton(ButtonGroup1, "RadioButton2");
  RadioButton2->setGeometry(QRect(146, 7, 90, 18));
  RadioButton2->setText(trUtf8("irreversible"));

  RadioButton3 = new QRadioButton(ButtonGroup1, "RadioButton3");
  RadioButton3->setGeometry(QRect(280, 7, 85, 18));
  RadioButton3->setText(trUtf8("General"));

  FunctionWidget1Layout->addWidget(ButtonGroup1, 3, 1);

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Function Type"));

  FunctionWidget1Layout->addWidget(TextLabel3, 3, 0);

  setTabOrder(LineEdit1, textBrowser);
  setTabOrder(textBrowser, RadioButton1);
  setTabOrder(RadioButton1, RadioButton2);
  setTabOrder(RadioButton2, RadioButton3);
  setTabOrder(RadioButton3, Table1);
  setTabOrder(Table1, Table2);
  setTabOrder(Table2, commitChanges);
  setTabOrder(commitChanges, cancelChanges);

  // signals and slots connections
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotCancelButtonClicked()));
  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotCommitButtonClicked()));
  connect(Table1, SIGNAL(valueChanged(int, int)), this, SLOT(slotTableValueChanged(int, int)));
  connect(textBrowser, SIGNAL(edited()), this, SLOT(slotFcnDescriptionChanged()));
  // connect(textBrowser, SIGNAL(edited()), this, SLOT(slotFcnDescriptionChanged()));
}

FunctionWidget1::~FunctionWidget1() {pdelete(pFunction);}

bool FunctionWidget1::loadFromFunction(CFunction* func) //TODO: func should be const
{
  if (func)
    {
      pdelete(pFunction);
      pFunction = CFunction::createFunction(func);
    }
  else if (!pFunction)
    fatalError();

  C_INT32 i, j;

  QPixmap * pProduct = new QPixmap((const char**)product_xpm);
  QPixmap * pSubstrate = new QPixmap((const char**)substrate_xpm);
  QPixmap * pModifier = new QPixmap((const char**)modifier_xpm);

  QColor subsColor(255, 210, 210);
  QColor prodColor(210, 255, 210);
  QColor modiColor(250, 250, 190);
  QColor paraColor(210, 210, 255);
  QColor color;

  // list of usages for combobox
  QStringList Usages;
  Usages += "SUBSTRATE";
  Usages += "PRODUCT";
  Usages += "MODIFIER";
  Usages += "PARAMETER";
  QString usage, qUsage;

  // for Name and Description text boxes
  //****************
  //LineEdit1->setText(func->getName().c_str());
  LineEdit1->setText(pFunction->getName().c_str());
  //textBrowser->setText(func->getDescription().c_str());
  textBrowser->setText(pFunction->getDescription().c_str());
  //  Function_Name = new QString(funct->getName().c_str());

  //TODO: the following is unnecessary
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

  // ************
  //const CFunctionParameters &functParam = func->getParameters();
  const CFunctionParameters &functParam = pFunction->getParameters();
  C_INT32 noOffunctParams = functParam.size();
  Table1->setNumRows(noOffunctParams);

  //create list of data types (for combobox)
  QStringList functionType;
  for (i = 0; CFunctionParameter::DataTypeName[i] != ""; i++)
    functionType.push_back(CFunctionParameter::DataTypeName[i].c_str());

  for (j = 0; j < noOffunctParams; j++)
    {
      usage = functParam[j]->getUsage().c_str();
      if (usage == "SUBSTRATE") {qUsage = "Substrate"; color = subsColor;}
      else if (usage == "PRODUCT") {qUsage = "Product"; color = prodColor;}
      else if (usage == "MODIFIER") {qUsage = "Modifier"; color = modiColor;}
      else if (usage == "PARAMETER") {qUsage = "Parameter"; color = paraColor;}
      else {qUsage = "unknown"; color = QColor(255, 20, 20);}

      // col. 0
      Table1->setItem(j, 0, new ColorTableItem(Table1, QTableItem::WhenCurrent, color,
                      functParam[j]->getName().c_str()));

      // col. 1
      QString temp = CFunctionParameter::DataTypeName[functParam[j]->getType()].c_str();
      ComboItem * item = new ComboItem(Table1, QTableItem::WhenCurrent, color, functionType);
      Table1->setItem(j, 1, item);
      item->setText(temp);

      // col. 2
      item = new ComboItem(Table1, QTableItem::WhenCurrent, color, Usages);
      item->setText(usage);
      if (usage == "SUBSTRATE") item->setPixmap(*pSubstrate);
      if (usage == "PRODUCT") item->setPixmap(*pProduct);
      if (usage == "MODIFIER") item->setPixmap(*pModifier);
      Table1->setItem(j, 2, item);
    }

  // for application table
  //**************
  //CCopasiVectorNS < CUsageRange > & functUsage = func->getUsageDescriptions();
  CCopasiVectorNS < CUsageRange > & functUsage = pFunction->getUsageDescriptions();

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
  //*****************
  //if (func->getType() == CFunction::MassAction ||
  //    func->getType() == CFunction::PreDefined)
  if (pFunction->getType() == CFunction::MassAction ||
      pFunction->getType() == CFunction::PreDefined)
    {
      RadioButton1->setEnabled(false);
      RadioButton2->setEnabled(false);
      RadioButton3->setEnabled(false);
      commitChanges->setEnabled(false);
      cancelChanges->setEnabled(false);
      LineEdit1->setReadOnly(true);
      textBrowser->setReadOnly(true);
      Table1->setReadOnly(true);
      Table2->setReadOnly(true);
    }

  /*** if function is user-defined *****/
  else
    {
      RadioButton1->setEnabled(true);
      RadioButton2->setEnabled(true);
      RadioButton3->setEnabled(true);
      LineEdit1->setReadOnly(false);
      textBrowser->setReadOnly(false);
      Table1->setReadOnly(false);
      Table2->setReadOnly(false);
      commitChanges->setEnabled(true);
      cancelChanges->setEnabled(true);
    }
  //*********
  //switch (func->isReversible())
  switch (pFunction->isReversible())
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
  return true;
} //end of function

//**** Try to get parameters table to display proper texts
void FunctionWidget1::updateParameters()
{
  if (textBrowser->text().latin1() != pFunction->getDescription())
    {
      pFunction->getParameters().cleanup();

      try
        {
          pFunction->setDescription(textBrowser->text().latin1());
        }
      catch (CCopasiException Exception)
        {
          switch (QMessageBox::warning(this, "Invalid Function Description",
                                       "Could not recognize the function description.\n"
                                       "Please check function and make sure to \n"
                                       "include operators between variables and coefficients.\n\n",
                                       "Retry",
                                       "Quit", 0, 0, 1))
            {
            case 0:                 // The user clicked the Retry again button or pressed Enter
              // try again
              break;
            case 1:                 // The user clicked the Quit or pressed Escape
              // exit
              break;
            }
        }

      std::vector<CNodeK *> & v = ((CKinFunction*) pFunction)->getNodes();

      for (int i = 0; i < v.size(); i++)
        {
          if (v[i]->isIdentifier())
            pFunction->addParameter(v[i]->getName(),
                                    CFunctionParameter::FLOAT64, "PARAMETER");
        }
    }
}

/*bool FunctionWidget1::saveToFunction()
{
  CFunction* func = (CFunction*)(CCopasiContainer*)CKeyFactory::get(objKey);
  if (!func) return false;
 
  C_INT32 i, j;
  bool changed = false;
 
  CFunctionParameter::DataType Type;
  bool ParametersChanged = false;
 
  /**** for Name and Description **** /
  CFunctionParameters &functParam = func->getParameters();
  CCopasiVectorNS < CUsageRange > & functUsage = func->getUsageDescriptions();
 
  if (func->getName() != LineEdit1->text().latin1())
    {
      func->setName(LineEdit1->text().latin1());
      ListViews::notify(ListViews::FUNCTION, ListViews::RENAME, objKey);
    }
 
  /**** For Radio Buttons **** /
  if (RadioButton1->isChecked() == true)
    {
      func->setReversible(TriTrue);
      changed = true;
    }
  else if (RadioButton2->isChecked() == true)
    {
      func->setReversible(TriFalse);
      changed = true;
    }
  else
    {
      func->setReversible(TriUnspecified);
      changed = true;
    }
 
  if (func->getDescription() != textBrowser->text().latin1())
    {
      func->setDescription(textBrowser->text().latin1());
      changed = true;
 
      CUsageRange Application;
      functUsage.cleanup();
 
      Application.setUsage("SUBSTRATES");
      if (functParam.getUsageRanges().getIndex("SUBSTRATE") == C_INVALID_INDEX)
        Application.setRange(0, CRange::Infinity);
      else
        Application.setRange(functParam.getUsageRanges()["SUBSTRATE"]->getLow(),
                             functParam.getUsageRanges()["SUBSTRATE"]->getHigh());
      functUsage.add(Application);
 
      Application.setUsage("PRODUCTS");
      if (functParam.getUsageRanges().getIndex("PRODUCT") == C_INVALID_INDEX)
        Application.setRange(0, CRange::Infinity);
      else
        Application.setRange(functParam.getUsageRanges()["PRODUCT"]->getLow(),
                             functParam.getUsageRanges()["PRODUCT"]->getHigh());
      functUsage.add(Application);
    }
  else
    {
      /***** for Table 1: Parameters table ***** /
      C_INT32 noOffunctParams =
        std::min(functParam.size(), (unsigned C_INT32) Table1->numRows());
 
      for (j = 0; j < noOffunctParams; j++)
        {
          //param_Name = new QString(Table1->text(j,0));
          // param_Name = Table1->text(j, 0);
 
          /****** conv enumerated types ???? ***** /
          //Table1->setText(j, 1, enumname[functParam[j]->getType()]);
          param_Type = Table1->text(j, 1);
 
          //param_Usage = new QString(Table1->text(j,2));
          param_Usage = Table1->text(j, 2);
 
          /***** set new values ***** /
          /**** enum ??? **** /
          //functParam[j]->setType(param_Type);
 
          for (i = 0; i < 4; i++)
            {
              if (param_Type.latin1() == CFunctionParameter::DataTypeName[i])
                Type = (CFunctionParameter::DataType) i;
            }
 
          // functParam[j]->setName(param_Name.latin1());
          if (functParam[j]->getType() != Type)
            {
              functParam[j]->setType(Type);
              ParametersChanged = true;
            }
          if (functParam[j]->getUsage() != param_Usage.latin1())
            {
              functParam[j]->setUsage(param_Usage.latin1());
              ParametersChanged = true;
            }
          functParam.updateUsageRanges();
        }
 
      if (ParametersChanged)
        {
          changed = true;
          updateApplication();
          /*CUsageRange Application;
                functUsage.cleanup();
 
                Application.setUsage("SUBSTRATES");
                if (functParam.getUsageRanges().getIndex("SUBSTRATE") == C_INVALID_INDEX)
                  Application.setRange(0, CRange::Infinity);
                else
                  Application.setRange(functParam.getUsageRanges()["SUBSTRATE"]->getLow(),
                                       functParam.getUsageRanges()["SUBSTRATE"]->getHigh());
                functUsage.add(Application);
 
                Application.setUsage("PRODUCTS");
                if (functParam.getUsageRanges().getIndex("PRODUCT") == C_INVALID_INDEX)
                  Application.setRange(0, CRange::Infinity);
                else
                  Application.setRange(functParam.getUsageRanges()["PRODUCT"]->getLow(),
                                       functParam.getUsageRanges()["PRODUCT"]->getHigh());
                functUsage.add(Application);* / 
          //Write back changed pFunction to current function
          // func = pFunction;
        }
      else
        {
          /***** for Table 2: Applications table ***** /
          C_INT32 noOfApplns =
            std::min(functUsage.size(), (unsigned C_INT32) Table2->numRows());
 
          //  Table2->setNumRows(noOfApplns);
 
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
 
              /***** there is no setName  here ????? ****** /
              functUsage[j]->setUsage(app_Desc.latin1());
 
              functUsage[j]->setLow(int_Low);
 
              functUsage[j]->setHigh(int_High);
            }
        }
    }
 
  enter(objKey); //TODO: check if this is necessary
  if (changed)
    ListViews::notify(ListViews::FUNCTION, ListViews::CHANGE, objKey);
 
  return true;
}*/

bool FunctionWidget1::saveToFunction()
{
  CFunction* func = (CFunction*)(CCopasiContainer*)CKeyFactory::get(objKey);
  if (!func) return false;

  bool changed = false;

  if (func->getName() != pFunction->getName())
    {
      func->setName(pFunction->getName());
    }
  CFunctionParameters &functParam = func->getParameters();
  CFunctionParameters &pfunctParam = pFunction->getParameters();

  /*for (int i=0; i < pfunctParam.size(); i++)
  {
   // check if function parameter exists in pFunctionParameter
   CFunctionParameter *p = functParam[pfunctParam[i]->getName()];
   if (p)  // match found
   //if (functParam[pfunctParam[i]->getName()])
   {
    // update usage and type
    p->setUsage(functParam[i]->getUsage());
    //functParam[pfunctParam[i]->getName()]->setUsage(functParam[i]->getUsage());
   } else {// match not found
    changed = true;
    functParam.add(*pfunctParam[i]);
   }
  }*/
  if (func->getDescription() != pFunction->getDescription())
    {
      changed = true;
      try
        {
          func->setDescription(pFunction->getDescription());
        }
      catch (CCopasiException Exception){}}

  if (changed)
    ListViews::notify(ListViews::FUNCTION, ListViews::CHANGE, objKey);

  return true;
}

void FunctionWidget1::updateApplication()
{
  //if (textBrowser->text().latin1() != pFunction->getDescription())
  //{
  //CFunction* func = (CFunction*)(CCopasiContainer*)CKeyFactory::get(objKey);
  //CFunctionParameters &functParam = func ->getParameters();
  CFunctionParameters &functParam = pFunction->getParameters();

  //CCopasiVectorNS < CUsageRange > & functUsage = func ->getUsageDescriptions();
  CCopasiVectorNS < CUsageRange > & functUsage = pFunction ->getUsageDescriptions();

  CUsageRange Application;
  functUsage.cleanup();

  Application.setUsage("SUBSTRATES");
  if (functParam.getUsageRanges().getIndex("SUBSTRATE") == C_INVALID_INDEX)
    Application.setRange(0, CRange::Infinity);
  else
    Application.setRange(functParam.getUsageRanges()["SUBSTRATE"]->getLow(),
                         functParam.getUsageRanges()["SUBSTRATE"]->getHigh());
  functUsage.add(Application);

  Application.setUsage("PRODUCTS");
  if (functParam.getUsageRanges().getIndex("PRODUCT") == C_INVALID_INDEX)
    Application.setRange(0, CRange::Infinity);
  else
    Application.setRange(functParam.getUsageRanges()["PRODUCT"]->getLow(),
                         functParam.getUsageRanges()["PRODUCT"]->getHigh());
  functUsage.add(Application);

  // reload
  loadFromFunction();
  //}
}

/*This function is called when the Function Description LineEdit is changed.*/
void FunctionWidget1::slotFcnDescriptionChanged()
{
  // update the parameter widget
  updateParameters();
  // update the application widget
  updateApplication();

  loadFromFunction();
}

void FunctionWidget1::slotCancelButtonClicked()
{
  //TODO: let the user confirm
  enter(objKey); // reload
}

void FunctionWidget1::slotCommitButtonClicked()
{
  //update pFunction values
  if (pFunction->getName() != LineEdit1->text().latin1())
    pFunction->setName(LineEdit1->text().latin1());
  // update RadioButtons also ?? in savetoFcn, func obtains radio button values
  /**** For Radio Buttons ****/
  if (RadioButton1->isChecked() == true)
    {
      pFunction->setReversible(TriTrue);
    }
  else if (RadioButton2->isChecked() == true)
    {
      pFunction->setReversible(TriFalse);
    }
  else
    {
      pFunction->setReversible(TriUnspecified);
    }
  if (pFunction->getDescription() != textBrowser->text().latin1())
    {
      pFunction->setDescription(textBrowser->text().latin1());
      updateParameters();
      updateApplication();
    }
  //let the user confirm?
  saveToFunction();
}

void FunctionWidget1::slotTableValueChanged(int row, int col)
{
  std::cout << "table changed " << row << " " << col << std::endl;

  CFunctionParameters &functParam = pFunction->getParameters();
  CFunctionParameter::DataType Type;

  if (col == 1)
    {
      param_Type = Table1->text(row, col);
      //functParam[row]->setType(Table1->text(row, col).latin1());
      for (int i = 0; i < 4; i++)
        {
          if (param_Type.latin1() == CFunctionParameter::DataTypeName[i])
            Type = (CFunctionParameter::DataType) i;
        }

      functParam[row]->setType(Type);
    }

  if (col == 2)
    {
      QColor subsColor(255, 210, 210);
      QColor prodColor(210, 255, 210);
      QColor modiColor(250, 250, 190);
      QColor paraColor(210, 210, 255);
      QColor color;

      QString usage = Table1->text(row, col);
      if (usage == "SUBSTRATE") {color = subsColor;}
      else if (usage == "PRODUCT") {color = prodColor;}
      else if (usage == "MODIFIER") {color = modiColor;}
      else if (usage == "PARAMETER") {color = paraColor;}
      else {color = QColor(255, 20, 20);}

      QPixmap * pPixMap;
      if (usage == "SUBSTRATE") pPixMap = new QPixmap((const char**)substrate_xpm);
      else if (usage == "PRODUCT") pPixMap = new QPixmap((const char**)product_xpm);
      else if (usage == "MODIFIER") pPixMap = new QPixmap((const char**)modifier_xpm);
      else pPixMap = new QPixmap();

      ((ColorTableItem*)Table1->item(row, 0))->setColor(color);
      ((ComboItem*)Table1->item(row, 1))->setColor(color);
      ((ComboItem*)Table1->item(row, 2))->setColor(color);
      Table1->setPixmap(row, 2, *pPixMap);
      Table1->setRowHeight(row, Table1->rowHeight(row)); // updateCell()

      functParam[row]->setUsage(usage.latin1());
    }
  // Update the usage range to get proper min and max values
  functParam.updateUsageRanges();

  updateApplication();
  //saveToFunction();
}

bool FunctionWidget1::update(ListViews::ObjectType objectType, ListViews::Action action, const std::string & key)
{
  switch (objectType)
    {
    case ListViews::MODEL:
      //TODO: check if it really is a compartment
      if (CKeyFactory::get(objKey)) return loadFromFunction((CFunction*)(CCopasiContainer*)CKeyFactory::get(objKey));
      break;

    default:
      break;
    }
  return true;
}

bool FunctionWidget1::leave()
{
  //let the user confirm?
  return saveToFunction();
}

bool FunctionWidget1::enter(const std::string & key)
{
  objKey = key;
  CFunction* func = (CFunction*)(CCopasiContainer*)CKeyFactory::get(key);
  //TODO: check if it really is a compartment

  if (func) return loadFromFunction(func);
  else return false;
}
