/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/FunctionWidget1.cpp,v $
   $Revision: 1.85 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/15 08:46:45 $
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
#include <stdlib.h>
#include <algorithm>

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
#include "qtUtilities.h"
#include "parametertable.h" // just for the table item widgets
#include "MyLineEdit.h"

#include "./icons/product.xpm"
#include "./icons/substrate.xpm"
#include "./icons/modifier.xpm"

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

  textBrowser = new QTextBrowser(this, "Text Browser");
  //textBrowser = new MyLineEdit(this, "Text Browser");
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
  cancelChanges->setText(trUtf8("Revert"));
  Layout1->addWidget(cancelChanges);

  newFcn = new QPushButton(this, "newFcn");
  newFcn->setText(trUtf8("New"));
  Layout1->addWidget(newFcn);

  deleteFcn = new QPushButton(this, "deleteFcn");
  deleteFcn->setText(trUtf8("Delete"));
  Layout1->addWidget(deleteFcn);

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
  Table2->setColumnReadOnly (0, true);  //this restricts users from editing usage description name on the application table

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
  Table1->setColumnReadOnly (0, true);  //this restricts users from editing parameter name on the parameter table
  Table1->setColumnReadOnly (1, true);

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
  setTabOrder(cancelChanges, newFcn);
  setTabOrder(newFcn, deleteFcn);

  // signals and slots connections
  connect(cancelChanges, SIGNAL(clicked()), this, SLOT(slotCancelButtonClicked()));
  connect(commitChanges, SIGNAL(clicked()), this, SLOT(slotCommitButtonClicked()));
  connect(newFcn, SIGNAL(clicked()), this, SLOT(slotNewButtonClicked()));
  connect(deleteFcn, SIGNAL(clicked()), this, SLOT(slotDeleteButtonClicked()));
  connect(Table1, SIGNAL(valueChanged(int, int)), this, SLOT(slotTableValueChanged(int, int)));
  connect(Table2, SIGNAL(valueChanged(int, int)), this, SLOT(slotAppTableValueChanged(int, int)));
  connect(textBrowser, SIGNAL(edited()), this, SLOT(slotFcnDescriptionChanged()));
  // connect(textBrowser, SIGNAL(edited()), this, SLOT(slotFcnDescriptionChanged()));
}

FunctionWidget1::~FunctionWidget1() {pdelete(pFunction);}

bool FunctionWidget1::loadParameterTable(const CFunctionParameters & params)
{
  //TODO: memory leak?
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

  unsigned C_INT32 i, j;
  std::string usage;
  QString qUsage;

  //C_INT32 noOffunctParams = functParam.size();
  Table1->setNumRows(params.size());

  //create list of data types (for combobox)
  QStringList functionType;
  for (i = 0; CFunctionParameter::DataTypeName[i] != ""; i++)
    functionType.push_back(FROM_UTF8(CFunctionParameter::DataTypeName[i]));

  for (j = 0; j < params.size(); j++)
    {
      usage = params[j]->getUsage();
      if (usage == "SUBSTRATE") {qUsage = "Substrate"; color = subsColor;}
      else if (usage == "PRODUCT") {qUsage = "Product"; color = prodColor;}
      else if (usage == "MODIFIER") {qUsage = "Modifier"; color = modiColor;}
      else if (usage == "PARAMETER") {qUsage = "Parameter"; color = paraColor;}
      else {qUsage = "unknown"; color = QColor(255, 20, 20);}

      // col. 0
      Table1->setItem(j, 0, new ColorTableItem(Table1, QTableItem::WhenCurrent, color,
                      FROM_UTF8(params[j]->getObjectName())));

      // col. 1
      QString temp = FROM_UTF8(CFunctionParameter::DataTypeName[params[j]->getType()]);
      ComboItem * item = new ComboItem(Table1, QTableItem::WhenCurrent, color, functionType);
      Table1->setItem(j, 1, item);
      item->setText(temp);

      // col. 2
      item = new ComboItem(Table1, QTableItem::WhenCurrent, color, Usages);
      item->setText(qUsage);
      if (usage == "SUBSTRATE") item->setPixmap(*pSubstrate);
      if (usage == "PRODUCT") item->setPixmap(*pProduct);
      if (usage == "MODIFIER") item->setPixmap(*pModifier);
      Table1->setItem(j, 2, item);
    }
  return true;
}

bool FunctionWidget1::loadUsageTable(const CCopasiVectorNS<CUsageRange>& usages)
{
  unsigned C_INT32 j;

  Table2->setNumRows(usages.size());
  for (j = 0; j < usages.size(); j++)
    {
      Table2->setText(j, 0, FROM_UTF8(usages[j]->getObjectName()));
      Table2->setText(j, 1, QString::number(usages[j]->getLow()));

      switch (usages[j]->getHigh())
        {
        case 0:
          Table2->setText(j, 2, "NA");
          break;

        case - 1:
          Table2->setText(j, 2, "infinity");
          break;

        default:
          Table2->setText(j, 2, QString::number(usages[j]->getHigh()));
        }
    }
  return true;
}

bool FunctionWidget1::loadFromFunction(CFunction* func) //TODO: func should be const
{
  if (func)
    {
      pdelete(pFunction);
      pFunction = CFunction::createFunction(func);
    }
  else if (!pFunction)
    return false;

  // function name
  LineEdit1->setText(FROM_UTF8(pFunction->getObjectName()));

  /* Insert line breaks in the function description */
  std::string desc = pFunction->getDescription();
  int l = 0;
  int n = 0;
  int len = desc.length();
  while (len - l > 65)
    {
      n = l;
      l = l + 65;
      while (l > n)
        {
          char ch = desc.at(l);
          if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/'))
            break;
          l--;
        }
      desc.insert(l, 1, '\n');
    }
  textBrowser->setText(FROM_UTF8(desc));

  //radio buttons
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

  //parameter table
  loadParameterTable(pFunction->getParameters());

  // application table
  loadUsageTable(pFunction->getUsageDescriptions());

  // make dialogue read only for predefined functions
  if (pFunction->getType() == CFunction::MassAction ||
      pFunction->getType() == CFunction::PreDefined)
    {
      RadioButton1->setEnabled(false);
      RadioButton2->setEnabled(false);
      RadioButton3->setEnabled(false);
      commitChanges->setEnabled(false);
      cancelChanges->setEnabled(false);
      deleteFcn->setEnabled(false);
      LineEdit1->setReadOnly(true);
      textBrowser->setReadOnly(true);
      Table1->setReadOnly(true);
      Table2->setReadOnly(true);
    }
  else   /*** if function is user-defined *****/
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
      deleteFcn->setEnabled(true);
    }
  return true;
}

//**** Try to get parameters table to display proper texts
void FunctionWidget1::updateParameters()
{
  if ((const char *)textBrowser->text().utf8() != pFunction->getDescription())
    {
      pFunction->getParameters().cleanup();

      try
        {
          pFunction->setDescription((const char *)textBrowser->text().utf8());
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
            case 0:                                          // The user clicked the Retry again button or pressed Enter
              // try again
              break;
            case 1:                                          // The user clicked the Quit or pressed Escape
              // exit
              break;
            }
        }

      std::vector<CNodeK *> & v = ((CKinFunction*) pFunction)->getNodes();

      for (unsigned C_INT32 i = 0; i < v.size(); i++)
        {
          if (v[i]->isIdentifier())
            pFunction->addParameter(v[i]->getName(),
                                    CFunctionParameter::FLOAT64, "PARAMETER");
        }
    }
}

#ifdef aaa
bool FunctionWidget1::saveToFunction()
{
  CFunction* func = (CFunction*)(CCopasiContainer*)CKeyFactory::get(objKey);
  if (!func) return false;

  C_INT32 i, j;
  bool changed = false;

  CFunctionParameter::DataType Type;
  bool ParametersChanged = false;

  /**** for Name and Description ****/
  CFunctionParameters &functParam = func->getParameters();
  CCopasiVectorNS < CUsageRange > & functUsage = func->getUsageDescriptions();

  if (func->getObjectName() != (const char *)LineEdit1->text().utf8())
    {
      func->setName((const char *)LineEdit1->text().utf8());
      ListViews::notify(ListViews::FUNCTION, ListViews::RENAME, objKey);
    }

  /**** For Radio Buttons ****/
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

  if (func->getDescription() != (const char *)textBrowser->text().utf8())
    {
      func->setDescription((const char *)textBrowser->text().utf8());
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
      /***** for Table 1: Parameters table *****/
      C_INT32 noOffunctParams =
        std::min(functParam.size(), (unsigned C_INT32) Table1->numRows());

      for (j = 0; j < noOffunctParams; j++)
        {
          //param_Name = new QString(Table1->text(j,0));
          // param_Name = Table1->text(j, 0);

          /****** conv enumerated types ???? *****/
          //Table1->setText(j, 1, enumname[functParam[j]->getType()]);
          param_Type = Table1->text(j, 1);

          //param_Usage = new QString(Table1->text(j,2));
          param_Usage = Table1->text(j, 2);

          /***** set new values *****/
          /**** enum ??? ****/
          //functParam[j]->setType(param_Type);

          for (i = 0; i < 4; i++)
            {
              if ((const char *)param_Type.utf8() == CFunctionParameter::DataTypeName[i])
                Type = (CFunctionParameter::DataType) i;
            }

          // functParam[j]->setName(param_Name.utf8());
          if (functParam[j]->getType() != Type)
            {
              functParam[j]->setType(Type);
              ParametersChanged = true;
            }
          if (functParam[j]->getUsage() != (const char *)param_Usage.utf8())
            {
              functParam[j]->setUsage((const char *)param_Usage.utf8());
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
                functUsage.add(Application);*/ 
          //Write back changed pFunction to current function
          // func = pFunction;
        }
      else
        {
          /***** for Table 2: Applications table *****/
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

              /***** there is no setName  here ????? ******/
              functUsage[j]->setUsage((const char *)app_Desc.utf8());

              functUsage[j]->setLow(int_Low);

              functUsage[j]->setHigh(int_High);
            }
        }
    }

  enter(objKey); //TODO: check if this is necessary
  if (changed)
    ListViews::notify(ListViews::FUNCTION, ListViews::CHANGE, objKey);

  return true;
}
#endif  //end of commenting for ifndef aaa

bool FunctionWidget1::saveToFunction()
{
  CFunction* func = dynamic_cast< CFunction * >(GlobalKeys.get(objKey));
  if (!func) return false;

  bool changed = false;

  if (func->getObjectName() != pFunction->getObjectName())
    {
      changed = true;
      func->setName(pFunction->getObjectName());
    }
  if (func->isReversible() != pFunction->isReversible())
    {
      changed = true;
      func->setReversible(pFunction->isReversible());
    }
  if (func->getDescription() != pFunction->getDescription())
    {
      changed = true;
      try
        {
          func->setDescription(pFunction->getDescription());
        }
      catch (CCopasiException Exception)
        {
          // handle exception
        }
    }

  // ** Parameter Table update of function **
  CFunctionParameters &functParam = func->getParameters();
  CFunctionParameters &pfunctParam = pFunction->getParameters();
  CFunctionParameter::DataType Type;
  unsigned C_INT32 index;
  unsigned C_INT32 i, j;

  for (i = 0; i < pfunctParam.size(); i++)
    {
      // check if function parameter exists in pFunctionParameter
      if ((index = functParam.findParameterByName(pfunctParam[i]->getObjectName(),
                   Type)) != C_INVALID_INDEX)
        // match found
        {
          if (functParam[index]->getUsage() != pfunctParam[i]->getUsage())
            {
              changed = true;
              // update usage
              functParam[index]->setUsage(pfunctParam[i]->getUsage());
              //functParam[pfunctParam[i]->getObjectName()]->setUsage(functParam[i]->getUsage());
            }
          if (functParam[index]->getType() != pfunctParam[i]->getType())
            {
              changed = true;
              // update type
              functParam[index]->setType(pfunctParam[i]->getType());
            }
        } else
        {// match not found
          changed = true;
          functParam.add(*pfunctParam[i]);
        }
    }
  // remove extra parameters existing in functParam, compare functParam to pfunctParam
  if (pfunctParam.size() != functParam.size())
    {
      for (j = 0; j < functParam.size(); j++)
        {
          if ((index = pfunctParam.findParameterByName(functParam[j]->getObjectName(),
                       Type)) == C_INVALID_INDEX)
            // the lines below occurs if new functionParameter does not exist in pfunctParam
            {
              changed = true;
              // remove the extra parameter in functParam
              functParam.remove(functParam[j]->getObjectName());
            }
        }
    }

  // ** Application Table update of function **
  CCopasiVectorNS < CUsageRange > & functUsage = func->getUsageDescriptions();
  CCopasiVectorNS < CUsageRange > & pfunctUsage = pFunction->getUsageDescriptions();

  for (i = 0; i < pfunctUsage.size(); i++)
    {
      // check if function usage exists in pFunctionUsage
      if ((index = functUsage.getIndex(pfunctUsage[i]->getObjectName())) != C_INVALID_INDEX)
        // match found
        {
          // update min and max values for corresponding usage descriptions
          if (pfunctUsage[i]->getLow() != functUsage[pfunctUsage[i]->getObjectName()]->getLow())
            {
              changed = true;
              functUsage[pfunctUsage[i]->getObjectName()]->setLow(pfunctUsage[i]->getLow());
              // same as
              // functUsage[index]->setLow(pfunctUsage[i]->getLow());
            }
          if (pfunctUsage[i]->getHigh() != functUsage[pfunctUsage[i]->getObjectName()]->getHigh())
            {
              changed = true;
              functUsage[pfunctUsage[i]->getObjectName()]->setHigh(pfunctUsage[i]->getHigh());
              // same as
              // functUsage[index]->setHigh(pfunctUsage[i]->getHigh());
            }
        } else
        {// match not found
          changed = true;
          functUsage.add(*pfunctUsage[i]);
        }
    }
  // remove extra usage existing in functUsage, compare functUsage to pfunctUsage
  if (pfunctUsage.size() != functUsage.size())
    {
      for (j = 0; j < functUsage.size(); j++)
        {
          if ((index = pfunctUsage.getIndex(functUsage[j]->getObjectName())) == C_INVALID_INDEX)
            // the lines below occurs if new functionParameter does not exist in pfunctParam
            {
              changed = true;
              // remove the extra parameter in functParam
              functUsage.CCopasiVector<CUsageRange>::remove(index);
            }
        }
    }

  if (changed)
    {
      ListViews::notify(ListViews::FUNCTION, ListViews::CHANGE, objKey);
    }
  return true;
}

void FunctionWidget1::updateApplication()
{
  CFunctionParameters &functParam = pFunction->getParameters();

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
  if (pFunction->getObjectName() != (const char *)LineEdit1->text().utf8())
    pFunction->setName((const char *)LineEdit1->text().utf8());
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

  /* Remove line breaks from the function description */
  std::string desc = (const char *)textBrowser->text().utf8();
  unsigned int loc = 0;
  while (1)
    {
      loc = desc.find('\n', loc);
      if (loc == std::string::npos)
        break;
      desc.erase(loc, 1);
    }
  textBrowser->setText(FROM_UTF8(desc));

  if (pFunction->getDescription() != (const char *)textBrowser->text().utf8())
    {
      //pFunction->setDescription((const char *)textBrowser->text().utf8()); //updateParameters sets the description
      updateParameters();
      updateApplication();
    }
  // update if Parameters changed... slotTableValueChanged updates Params and calls updateApps
  // update if Application Table changed.  create a slotAppTableValueChanged??

  //let the user confirm?
  saveToFunction();
}

void FunctionWidget1::slotNewButtonClicked()
{
  std::string name = "function_0";
  int i = 0;
  CFunction* pFunc;
  while (!(pFunc = Copasi->pFunctionDB->createFunction(name, CFunction::UserDefined)))
    {
      i++;
      name = "function_";
      name += QString::number(i).utf8();
    }
  //table->setText(table->numRows() - 1, 0, FROM_UTF8(name));
  //table->setNumRows(table->numRows());
  //emit updated();
  //emit leaf(mModel);
  ListViews::notify(ListViews::FUNCTION, ListViews::ADD);
  enter(pFunc->getKey());
}

void FunctionWidget1::slotDeleteButtonClicked()
{
  //TODO: let the user confirm
  const CCopasiVectorN < CReaction > * pReactions = NULL;
  unsigned C_INT32 k, kmax, i = 0;
  unsigned C_INT32 imax = 1;

  if (Copasi->pModel)
    {
      pReactions = &Copasi->pModel->getReactions();
      kmax = pReactions->size();
    }

  QString msg1 = "Cannot delete Function(s). ";
  msg1.append("Following dependencies with listed Reaction(s) exist:\n");
  QString msg2 = "Are you sure to delete listed Function(s)?\n";
  int msg1Empty = 1;
  int msg2Empty = 1;
  //int *reacFound = new int[imax];
  int reacFound;

  //for (i = 0; i < imax; i++)
  //  {
  //reacFound[i] = 0;
  reacFound = 0;

  /* Check if Reactions are dependent on Functions to be deleted */
  if (kmax > 0)
    {
      const CFunction* func =
        dynamic_cast< CFunction * >(GlobalKeys.get(objKey));

      for (k = 0; k < kmax; k++)
        {
          const CFunction *reacFunc = &((*pReactions)[k]->getFunction());
          if (func == reacFunc)
            {
              //reacFound[i] = 1;
              reacFound = 1;
              msg1.append(FROM_UTF8((*pReactions)[k]->getObjectName()));
              msg1.append(" ---> ");
              //msg1.append(table->text(ToBeDeleted[i], 0));
              msg1.append(FROM_UTF8(pFunction->getObjectName()));
              msg1.append("\n");
              msg1Empty = 0;
              break;
            }
        }
    }

  /* Make a list of Functions on which no Reaction is dependent */
  //if (reacFound[i] == 0)
  if (reacFound == 0)
    {
      //msg2.append(table->text(ToBeDeleted[i], 0));
      msg2.append(FROM_UTF8(pFunction->getObjectName()));
      msg2.append("\n");
      msg2Empty = 0;
    }
  //}

  if (msg2Empty == 0)
    {
      int choice = QMessageBox::warning(this,
                                        "CONFIRM DELETE",
                                        msg2,
                                        "Continue", "Cancel", 0, 0, 1);

      /* Check if user chooses to deleted Functions */
      switch (choice)
        {
        case 0:                  // Yes or Enter
          {
            /* Delete the Functions on which no Reactions are dependent */
            //for (i = 0; i < imax; i++)
            // {
            //if (reacFound[i] == 0)
            if (reacFound == 0)
              {
                unsigned C_INT32 size = Copasi->pFunctionDB->loadedFunctions().size();
                unsigned C_INT32 index = Copasi->pFunctionDB->loadedFunctions().getIndex(pFunction->getObjectName());
                //if ((index != NULL) && (size != NULL)) {
                Copasi->pFunctionDB->removeFunction(objKey);
                //Copasi->pFunctionDB->loadedFunctions()[min(index,20 - 1)];
                // enter(Copasi->pFunctionDB->loadedFunctions()[std::min(index,size-1,less<double>())]->getKey());
                // two values from min should work but it doesn't asks for 3 values, sample API http://wwwasd.web.cern.ch/wwwasd/lhc++/RW/stdlibcr/min_9233.htm
                enter(Copasi->pFunctionDB->loadedFunctions()[std::min(index, size - 2)]->getKey());
                //pListView->switchToOtherWidget(Copasi->pFunctionDB->loadedFunctions()[min(index,size - 1)]);
                //table->removeRow(ToBeDeleted[i]);
                //}
              }
            //}

            /* Send notifications for Functions which have been deleted */
            //for (i = 0; i < imax; i++)
            //  {
            //if (reacFound[i] == 0)
            if (reacFound == 0) //changed from "=" to "=="
              ListViews::notify(ListViews::FUNCTION, ListViews::DELETE, objKey);

            //}
            break;
          }
        case 1:                  // No or Escape
          break;
        }
    }

  if (msg1Empty == 0)
    {
      QMessageBox::warning(this, "Sorry, Cannot Delete",
                           msg1,
                           "OK", 0, 0, 0, 1);

      //int choice = QMessageBox::warning(this, "Sorry, Cannot Delete",
      //                   msg1,
      //                 "OK", "Navigate to Reaction Widget", 0, 0, 1);
    }

  //delete[] reacFound;
}

void FunctionWidget1::slotTableValueChanged(int row, int col)
{
  std::cout << "table changed " << row << " " << col << std::endl;

  CFunctionParameters &functParam = pFunction->getParameters();
  CFunctionParameter::DataType Type;

  QString param_Type;

  if (col == 1)
    {
      param_Type = Table1->text(row, col);
      //functParam[row]->setType((const char *)Table1->text(row, col).utf8());
      for (int i = 0; i < 4; i++)
        {
          if ((const char *)param_Type.utf8() == CFunctionParameter::DataTypeName[i])
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

      functParam[row]->setUsage((const char *)usage.utf8());
    }
  // Update the usage range to get proper min and max values
  functParam.updateUsageRanges();

  updateApplication();
  //saveToFunction();
}

void FunctionWidget1::slotAppTableValueChanged(int row, int col)
{
  std::cout << "table changed " << row << " " << col << std::endl;

  CFunctionParameters &functParam = pFunction->getParameters();
  CCopasiVectorNS < CUsageRange > & functUsage = pFunction->getUsageDescriptions();

  /*if (col == 0)
    {
      app_Desc = Table2->text(row, col);
      functUsage[row]->setUsage((const char *)app_Desc.utf8());
    }*/ // Application Description should be restricted from change 

  QString app_Low, app_High;
  C_INT32 int_Low, int_High;

  if (col == 1)
    {
      app_Low = Table2->text(row, col);
      int_Low = app_Low.toInt();
      functUsage[row]->setLow(int_Low);
    }

  if (col == 2)
    {
      app_High = Table2->text(row, col);

      if (QString::compare(app_High, "NA") == 0)
        {
          int_High = 0;
        }
      else
        {
          int_High = app_High.toInt();
        }
      functUsage[row]->setHigh(int_High);
    }
}

bool FunctionWidget1::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  switch (objectType)
    {
    case ListViews::MODEL:
      //TODO: check if it really is a compartment
      return loadFromFunction(dynamic_cast< CFunction * >(GlobalKeys.get(objKey)));
      break;

    default:
      break;
    }
  return true;
}

bool FunctionWidget1::leave()
{
  // slot commit called to ensure that pFunction has proper values
  slotCommitButtonClicked();
  //let the user confirm?
  return true;  // slotCommit calls saveToFcn
}

bool FunctionWidget1::enter(const std::string & key)
{
  objKey = key;
  CFunction* func = dynamic_cast<CFunction*>(GlobalKeys.get(key));

  if (func) return loadFromFunction(func);
  else return false;
}
