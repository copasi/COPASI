/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/FunctionWidget1.cpp,v $
   $Revision: 1.88 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/06/17 15:04:44 $
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

  textBrowser = new QTextEdit(this, "Text Browser");
  textBrowser->setTabChangesFocus(true);
  textBrowser->setTextFormat(PlainText);
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
  connect(textBrowser, SIGNAL(textChanged()), this, SLOT(slotFcnDescriptionChanged()));
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
  Usages += "Substrate";
  Usages += "Product";
  Usages += "Modifier";
  Usages += "Parameter";

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

  //TODO: render "MODIFIER" usages differently?
}

bool FunctionWidget1::loadReversibility(TriLogic rev)
{
  switch (rev)
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
}

bool FunctionWidget1::loadFromFunction(const CFunction* func)
{
  if (func)
    {
      pdelete(pFunction);
      pFunction = CFunction::createFunction(func);
      flagChanged = false;
    }
  else if (!pFunction)
    return false;

  // make dialogue read only for predefined functions
  if (pFunction->getType() == CFunction::MassAction ||
      pFunction->getType() == CFunction::PreDefined)
    {
      flagRO = true;
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
      flagRO = false;
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
  loadReversibility(pFunction->isReversible());

  //parameter table
  loadParameterTable(pFunction->getParameters());

  // application table
  loadUsageTable(pFunction->getUsageDescriptions());

  isValid = true;
  return true;
}

bool FunctionWidget1::copyFunctionContentsToFunction(const CFunction* src, CFunction* target)
{
  //Description
  try
    {
      target->setDescription(src->getDescription());
    }
  catch (CCopasiException Exception)
  {}

  //Parameters
  CFunctionParameters &functParam = target->getParameters();
  const CFunctionParameters &pfunctParam = src->getParameters();
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
              //changed = true;
              // update usage
              functParam[index]->setUsage(pfunctParam[i]->getUsage());
              //functParam[pfunctParam[i]->getObjectName()]->setUsage(functParam[i]->getUsage());
            }
          if (functParam[index]->getType() != pfunctParam[i]->getType())
            {
              //changed = true;
              // update type
              functParam[index]->setType(pfunctParam[i]->getType());
            }
        } else
        {// match not found
          //changed = true;
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
              //changed = true;
              // remove the extra parameter in functParam
              functParam.remove(functParam[j]->getObjectName());
            }
        }
    } //TODO: this is propably much too complicated

  //Usages of the function
  CCopasiVectorNS < CUsageRange > & tarU = target->getUsageDescriptions();
  const CCopasiVectorNS < CUsageRange > & srcU = src->getUsageDescriptions();

  tarU.cleanup();
  for (i = 0; i < srcU.size(); i++)
    {
      tarU.add(*srcU[i]);
    }

  return true;
}

bool FunctionWidget1::saveToFunction()
{
  CFunction* func = dynamic_cast<CFunction*>(GlobalKeys.get(objKey));
  if (!func) return false;

  //name
  if (func->getObjectName() != (const char *)LineEdit1->text().utf8())
    {
      func->setName((const char *)LineEdit1->text().utf8());
      ListViews::notify(ListViews::FUNCTION, ListViews::RENAME, objKey);
    }

  //radio buttons
  TriLogic tmpl;
  if (RadioButton1->isChecked() == true)
    {
      tmpl = TriTrue;
    }
  else if (RadioButton2->isChecked() == true)
    {
      tmpl = TriFalse;
    }
  else
    {
      tmpl = TriUnspecified;
    }
  if (tmpl != func->isReversible())
    {
      func->setReversible(tmpl);
      flagChanged = true;
    }

  if (flagChanged)
    {
      copyFunctionContentsToFunction(pFunction, func);

      ListViews::notify(ListViews::FUNCTION, ListViews::CHANGE, objKey);
    }

  flagChanged = false;
  return true;
}

void FunctionWidget1::updateParameters()
{
  //TODO this method messes with the sorting of the parameters
  std::vector<CNodeK*> & v = ((CKinFunction*) pFunction)->getNodes();
  CFunctionParameters & params = pFunction->getParameters();

  unsigned C_INT32 index;
  CFunctionParameter::DataType type;
  std::vector<std::string> paramNames;

  //first create the new parameters
  unsigned C_INT32 i;
  for (i = 0; i < v.size(); i++)
    {
      if (v[i]->isIdentifier())
        {
          paramNames.push_back(v[i]->getName());
          index = params.findParameterByName(v[i]->getName(), type);
          if (index == C_INVALID_INDEX)
            {
              pFunction->addParameter(v[i]->getName(),
                                      CFunctionParameter::FLOAT64, "PARAMETER");
            }
        }
    }

  //next delete the parameters that are not in the node tree
  std::vector<std::string>::const_iterator it, itEnd = paramNames.end();
  bool found;
  for (unsigned C_INT32 i = 0; i < params.size(); i++)
    {
      const std::string & name = params[i]->getObjectName();

      //check if name is in paramNames
      found = false;
      for (it = paramNames.begin(); it != itEnd; ++it)
        if (name == *it)
        {found = true; break;}

      if (!found)
        {
          params.remove(name);
        }
    }
  params.updateUsageRanges();
}

void FunctionWidget1::updateApplication()
{
  CFunctionParameters &functParam = pFunction->getParameters();

  CCopasiVectorNS < CUsageRange > & functUsage = pFunction ->getUsageDescriptions();

  CUsageRange Application;
  functUsage.cleanup();

  Application.setUsage("SUBSTRATES");
  if (functParam.getUsageRanges().getIndex("SUBSTRATE") != C_INVALID_INDEX)
    {
      Application.setRange(functParam.getUsageRanges()["SUBSTRATE"]->getLow(),
                           functParam.getUsageRanges()["SUBSTRATE"]->getHigh());
      functUsage.add(Application);
    }

  Application.setUsage("PRODUCTS");
  if (functParam.getUsageRanges().getIndex("PRODUCT") != C_INVALID_INDEX)
    {
      Application.setRange(functParam.getUsageRanges()["PRODUCT"]->getLow(),
                           functParam.getUsageRanges()["PRODUCT"]->getHigh());
      functUsage.add(Application);
    }

  Application.setUsage("MODIFIERS");
  if (functParam.getUsageRanges().getIndex("MODIFIER") != C_INVALID_INDEX)
    {
      Application.setRange(functParam.getUsageRanges()["MODIFIER"]->getLow(),
                           functParam.getUsageRanges()["MODIFIER"]->getHigh());
      functUsage.add(Application);
    }
}

//************** slots for changes in the widgets *************************************

/*This function is called when the Function Description is changed.*/
void FunctionWidget1::slotFcnDescriptionChanged()
{
  if (flagRO) return;
  std::cout << "*:" << (const char *)textBrowser->text().utf8() << ":*" << std::endl;
  flagChanged = true;

  //just set the description (with implicit compile()) and update parameters.
  try
    {
      pFunction->setDescription((const char *)textBrowser->text().utf8());
    }
  catch (CCopasiException Exception)
  {}
  updateParameters();

  //try again (to see if the description is valid)
  //the first call to setDescription would have thrown an exc. even if a param name has changed
  isValid = true;
  try
    {
      pFunction->setDescription((const char *)textBrowser->text().utf8());
    }
  catch (CCopasiException Exception)
    {
      std::cout << "error in function" << std::endl;
      isValid = false;
    }

  if (isValid)
    {
      commitChanges->setEnabled(true);
    }
  else
    {
      commitChanges->setEnabled(false);
    }

  //parameter table
  loadParameterTable(pFunction->getParameters());

  // application table
  updateApplication();
  loadUsageTable(pFunction->getUsageDescriptions());
}

void FunctionWidget1::slotTableValueChanged(int row, int col)
{
  std::cout << "table changed " << row << " " << col << std::endl;
  flagChanged = true;

  CFunctionParameters &functParam = pFunction->getParameters();

  if (col == 2) //Usage
    {
      QString qUsage = Table1->text(row, col);
      std::string usage;
      if (qUsage == "Substrate") {usage = "SUBSTRATE";}
      else if (qUsage == "Product") {usage = "PRODUCT";}
      else if (qUsage == "Modifier") {usage = "MODIFIER";}
      else if (qUsage == "Parameter") {usage = "PARAMETER";}
      else {fatalError();}

      functParam[row]->setUsage(usage);
      functParam.updateUsageRanges();
    }

  //update tables
  loadParameterTable(pFunction->getParameters());
  updateApplication();
  loadUsageTable(pFunction->getUsageDescriptions());
}

void FunctionWidget1::slotAppTableValueChanged(int C_UNUSED(row), int C_UNUSED(col))
{
  //this table is read only at the moment
}

//**************** slots for buttons *********************************************

void FunctionWidget1::slotCancelButtonClicked()
{
  enter(objKey); // reload
}

void FunctionWidget1::slotCommitButtonClicked()
{
  if (isValid)
    saveToFunction();
  //update pFunction values

  /* Remove line breaks from the function description */
  /*std::string desc = (const char *)textBrowser->text().utf8();
  unsigned int loc = 0;
  while (1)
    {
      loc = desc.find('\n', loc);
      if (loc == std::string::npos)
        break;
      desc.erase(loc, 1);
    }
  textBrowser->setText(FROM_UTF8(desc));*/
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
  ListViews::notify(ListViews::FUNCTION, ListViews::ADD);
  enter(pFunc->getKey());
}

void FunctionWidget1::slotDeleteButtonClicked()
{}

//************************  standard interface to copasi widgets *********************************

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
  if (isValid)
    saveToFunction();
  return true;
}

bool FunctionWidget1::enter(const std::string & key)
{
  objKey = key;
  CFunction* func = dynamic_cast<CFunction*>(GlobalKeys.get(key));

  if (func) return loadFromFunction(func);
  else return false;
}
