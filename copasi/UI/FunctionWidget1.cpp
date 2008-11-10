// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/FunctionWidget1.cpp,v $
//   $Revision: 1.159.2.1 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2008/11/10 20:23:35 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

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
#include <qhbuttongroup.h>
#include <qcombobox.h>
#include <qpushbutton.h>
#include <qtoolbar.h>
#include <qwidget.h>
#include <qframe.h>
#include <qtextbrowser.h>
#include <qwidgetstack.h>
#include <qvbox.h>
#include <qtoolbutton.h>

#include <sstream>
#include <stdlib.h>
#include <algorithm>

#include "copasi.h"
#include "listviews.h"
#include "CQMessageBox.h"
#include "FunctionWidget1.h"
#include "qtUtilities.h"
#include "parametertable.h" // just for the table item widgets

#ifdef HAVE_MML
# include "mml/qtmmlwidget.h"
#include "tex/CMathMLToTeX.h"
#endif // Have_MML

#include "CopasiDataModel/CCopasiDataModel.h"
#include "model/CMetab.h"
#include "model/CModel.h"
#include "utilities/CCopasiException.h"
#include "function/CFunction.h"
#include "function/CFunctionDB.h"
#include "function/CKinFunction.h"
#include "report/CKeyFactory.h"
#include "utilities/CDimension.h"

#include "CopasiFileDialog.h"
#include "./icons/saveIcon.xpm"
#include "./icons/edit_Icon.xpm"

//#include "./icons/product.xpm"
//#include "./icons/substrate.xpm"
//#include "./icons/modifier.xpm"

#define COL_NAME 0
#define COL_USAGE 1
#define COL_UNIT 2

/*!
   Constructor

   Constructs a FunctionWidget1 which is a child of 'parent', with the
   name 'name' and widget flags set to 'f'.
 */
FunctionWidget1::FunctionWidget1(QWidget* parent, const char* name, WFlags fl):
    CopasiWidget(parent, name, fl),
    objKey(""),
    mpFunction(NULL)
{
  if (!name)
    setName("FunctionWidget1");
  setCaption(trUtf8("FunctionWidget1"));
  FunctionWidget1Layout = new QGridLayout(this, 1, 1, 6, 6, "FunctionWidget1Layout");

  //******** name *************

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText(trUtf8("Function Name"));
  TextLabel1->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  FunctionWidget1Layout->addWidget(TextLabel1, 0, 0);

  LineEdit1 = new QLineEdit(this, "LineEdit1");
  FunctionWidget1Layout->addWidget(LineEdit1, 0, 1);

  //******** description *************

  TextLabel2 = new QLabel(this, "TextLabel2");
  TextLabel2->setText(trUtf8("Formula"));
  TextLabel2->setAlignment(int(QLabel::AlignTop
                               | QLabel::AlignRight));
  FunctionWidget1Layout->addWidget(TextLabel2, 1, 0);

  //the stack
  mStack = new QWidgetStack(this, "Stack");
  mStack->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  textBrowser = new QTextEdit(mStack, "Text Browser");
  textBrowser->setTabChangesFocus(true);
  textBrowser->setTextFormat(PlainText);
  mStack->addWidget(textBrowser, 0);
  mStack->raiseWidget(0);

#ifdef HAVE_MML
  // A box which contains the MathML ScrollView with the Formula,
  //  and - if not ReadOnly -
  //   a button to switch to (editable) plain text view.
  mMmlViewBox = new QVBox(mStack, "Formula View");
  mMmlViewBox->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  mScrollView = new QScrollView(mMmlViewBox, "mmlScrollView");
  mScrollView->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);

  mStack->addWidget(mMmlViewBox, 1);

  mMmlWidget = new QtMmlWidget(mScrollView->viewport());
  mMmlWidget->setBaseFontPointSize(this->fontInfo().pointSize());
  mMmlWidget->setFontName(QtMmlWidget::NormalFont, this->fontInfo().family());

  mScrollView->addChild(mMmlWidget);

  mScrollView->setResizePolicy(QScrollView::AutoOneFit);
  //mScrollView->show();

  // raise mScrollView with mMmmlWidget:
  mStack->raiseWidget(1);

  mpFormulaHBL = new QHBoxLayout(0, 0, 6, "mpFormulaHBL");
  mpFormulaHBL->addWidget(mStack);

  mpFormulaVBL = new QVBoxLayout(0, 0, 6, "mpFormulaVBL");

  //mMmlViewBox->insertChild(mFormulaEditToggleButton);
#endif // HAVE_MML

  //  FunctionWidget1Layout->addWidget(mStack, 1, 1);

  // add 21.07.08
  //********************
  mpSaveBtn = new QToolButton(this, "mpSaveBtn");
  mpSaveBtn->setMaximumSize(QSize(20, 20));
  //  mpSaveBtn->setText(trUtf8("Save Formula to Disk"));
  //  mpSaveBtn->setTextLabel(trUtf8("Save Formula to Disk"));
  mpSaveBtn->setIconSet(QIconSet(saveIcon));
  mpFormulaVBL->addWidget(mpSaveBtn);

  //  mFormulaEditToggleButton = new QPushButton("Edit", mMmlViewBox, "Formula Edit Toggle Button");
  mFormulaEditToggleButton = new QToolButton(this, "mFormulaEditToggleButton");
  mFormulaEditToggleButton->setMaximumSize(QSize(20, 20));
  mFormulaEditToggleButton->setIconSet(QIconSet(editIcon));
  mpFormulaVBL->addWidget(mFormulaEditToggleButton);

  mpFormulaSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);
  mpFormulaVBL->addItem(mpFormulaSpacer);

  mpFormulaHBL->addLayout(mpFormulaVBL);

  //  FunctionWidget1Layout->addWidget(mpSaveBtn, 2, 1);
  FunctionWidget1Layout->addLayout(mpFormulaHBL, 1, 1);

  //********************

  TextLabel3 = new QLabel(this, "TextLabel3");
  TextLabel3->setText(trUtf8("Function Type"));
  TextLabel3->setAlignment(int(QLabel::AlignVCenter
                               | QLabel::AlignRight));
  FunctionWidget1Layout->addWidget(TextLabel3, 4, 0);

  ButtonGroup1 = new QHButtonGroup(this, "ButtonGroup1");
  ButtonGroup1->setFlat(true);
  ButtonGroup1->setInsideMargin(0);
  ButtonGroup1->setLineWidth(0);
  ButtonGroup1->setTitle(trUtf8(""));
  ButtonGroup1->setExclusive(true);
  ButtonGroup1->setRadioButtonExclusive(true);

  RadioButton1 = new QRadioButton(ButtonGroup1, "RadioButton1");
  RadioButton1->setText(trUtf8("reversible"));

  RadioButton2 = new QRadioButton(ButtonGroup1, "RadioButton2");
  RadioButton2->setText(trUtf8("irreversible"));

  RadioButton3 = new QRadioButton(ButtonGroup1, "RadioButton3");
  RadioButton3->setText(trUtf8("General"));

  FunctionWidget1Layout->addWidget(ButtonGroup1, 4, 1);

  //***************************************

  // Line2 = new QFrame(this, "Line2");
  // Line2->setFrameShape(QFrame::HLine);
  // FunctionWidget1Layout->addMultiCellWidget(Line2, 4, 4, 0, 1);

  //******* parameters table ********************************

  TextLabel4 = new QLabel(this, "TextLabel4");
  TextLabel4->setText(trUtf8("Parameters"));
  TextLabel4->setAlignment(int(QLabel::AlignTop
                               | QLabel::AlignRight));
  FunctionWidget1Layout->addWidget(TextLabel4, 5, 0);

  Table1 = new QTable(this, "Table1");
  Table1->setNumCols(3);
  Table1->horizontalHeader()->setLabel(COL_NAME, trUtf8("Name"));
  Table1->horizontalHeader()->setLabel(COL_USAGE, trUtf8("Description"));
  Table1->horizontalHeader()->setLabel(COL_UNIT, trUtf8("Unit"));
  Table1->setNumRows(3);
  Table1->setColumnReadOnly (COL_NAME, true);
  Table1->setColumnReadOnly (COL_UNIT, true);
  Table1->verticalHeader()->hide();
  Table1->setLeftMargin(0);
  Table1->setColumnStretchable(COL_NAME, true);
  Table1->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
  FunctionWidget1Layout->addMultiCellWidget(Table1, 5, 5, 1, 1);

  //******** applications table *******************************

  TextLabel5 = new QLabel(this, "TextLabel5");
  TextLabel5->setText(trUtf8("Application\nrestrictions"));
  TextLabel5->setAlignment(int(QLabel::AlignTop
                               | QLabel::AlignRight));
  FunctionWidget1Layout->addWidget(TextLabel5, 7, 0);

  Table2 = new QTable(this, "Table2");
  Table2->setNumCols(2);
  Table2->horizontalHeader()->setLabel(0, trUtf8("Description"));
  Table2->horizontalHeader()->setLabel(1, trUtf8("Min"));
  Table2->setNumRows(1);
  Table2->setColumnReadOnly (0, true);
  Table2->setColumnReadOnly (1, true);
  Table2->verticalHeader()->hide();
  Table2->setLeftMargin(0);
  Table2->horizontalHeader()->hide();
  Table2->setTopMargin(0);
  Table2->setShowGrid(false);
  //Table2->setColumnStretchable(1, true);
  Table2->setSizePolicy(QSizePolicy::Maximum, QSizePolicy::Fixed);
  FunctionWidget1Layout->addMultiCellWidget(Table2, 7, 7, 1, 1);

  QSpacerItem* spacer2 = new QSpacerItem(0, 0, QSizePolicy::Preferred, QSizePolicy::Expanding);
  FunctionWidget1Layout->addItem(spacer2, 10, 1);

  //***************************************

  Line3 = new QFrame(this, "Line3");
  Line3->setFrameShape(QFrame::HLine);
  //Line3->setFrameShadow(QFrame::Sunken);
  //Line3->setFrameShape(QFrame::HLine);
  FunctionWidget1Layout->addMultiCellWidget(Line3, 11, 11, 0, 1);

  //****** buttons *********************************

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

  FunctionWidget1Layout->addMultiCellLayout(Layout1, 12, 12, 0, 1);

  //*******************************************

  //Line4 = new QFrame(this, "Line4");
  //Line4->setFrameShape(QFrame::HLine);
  //Line4->setFrameShadow(QFrame::Sunken);
  //Line4->setFrameShape(QFrame::HLine);
  //FunctionWidget1Layout->addMultiCellWidget(Line4, 7, 7, 0, 1);

  //Line1 = new QFrame(this, "Line1");
  //Line1->setFrameShape(QFrame::HLine);
  //Line1->setFrameShadow(QFrame::Sunken);
  //Line1->setFrameShape(QFrame::HLine);
  //FunctionWidget1Layout->addMultiCellWidget(Line1, 2, 2, 0, 1);

  //***************+

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
  connect(mpSaveBtn, SIGNAL(clicked()), this, SLOT(slotSave()));

  connect(RadioButton1, SIGNAL(toggled(bool)), this, SLOT(slotReversibilityChanged()));
  connect(RadioButton2, SIGNAL(toggled(bool)), this, SLOT(slotReversibilityChanged()));
  connect(RadioButton3, SIGNAL(toggled(bool)), this, SLOT(slotReversibilityChanged()));

#ifdef HAVE_MML
  connect(mFormulaEditToggleButton, SIGNAL(clicked()), this,
          SLOT(slotToggleFcnDescriptionEdit()));
#endif // HAVE_MML
  connect(textBrowser, SIGNAL(textChanged()), this, SLOT(slotFcnDescriptionChanged()));

  QToolTip::add(mFormulaEditToggleButton, tr("edit formula"));
  QToolTip::add(mpSaveBtn, tr("save formula"));
}

//! Destructor
FunctionWidget1::~FunctionWidget1()
{
  //pdelete(mMmlWidget);
  //pdelete(mScrollView);
  pdelete(mpFunction);
}

bool FunctionWidget1::loadParameterTable()
{
  QColor subsColor(255, 210, 210);
  QColor prodColor(210, 255, 210);
  QColor modiColor(250, 250, 190);
  QColor paraColor(210, 210, 255);
  QColor volColor(210, 210, 255);
  QColor timeColor(210, 210, 210);
  QColor color;

  unsigned C_INT32 i, j;
  CFunctionParameters & params = mpFunction->getVariables();

  // list of usages for combobox
  QStringList Usages;
  for (i = 0; CFunctionParameter::RoleNameDisplay[i] != ""; i++)
    {
      if (dynamic_cast<CKinFunction *>(mpFunction) &&
          CFunctionParameter::VARIABLE == (CFunctionParameter::Role) i) continue;
      Usages += (FROM_UTF8(CFunctionParameter::RoleNameDisplay[i]));
    }

  //create list of data types (for combobox)
  QStringList functionType;
  for (i = 0; CFunctionParameter::DataTypeName[i] != ""; i++)
    functionType += (FROM_UTF8(CFunctionParameter::DataTypeName[i]));

  //find parameter units
  CFindDimensions ddd(mpFunction);
  ddd.setUseHeuristics(true);
  std::vector<std::string> units = ddd.findDimensionsBoth();

  CFunctionParameter::Role usage;
  QString qUsage;

  //C_INT32 noOffunctParams = functParam.size();
  Table1->setNumRows(params.size());

  for (j = 0; j < params.size(); j++)
    {
      usage = params[j]->getUsage();
      if (usage == CFunctionParameter::VARIABLE &&
          dynamic_cast<CKinFunction *>(mpFunction))
        {
          usage = CFunctionParameter::PARAMETER;
          params[j]->setUsage(usage);
        }

      qUsage = FROM_UTF8(CFunctionParameter::RoleNameDisplay[usage]);

      switch (usage)
        {
        case CFunctionParameter::SUBSTRATE:
          color = subsColor;
          break;
        case CFunctionParameter::PRODUCT:
          color = prodColor;
          break;
        case CFunctionParameter::MODIFIER:
          color = modiColor;
          break;
        case CFunctionParameter::PARAMETER:
          color = paraColor;
          break;
        case CFunctionParameter::VOLUME:
          color = volColor;
          break;
        case CFunctionParameter::TIME:
          color = timeColor;
          break;
        case CFunctionParameter::VARIABLE:
          color = QColor(250, 250, 250);
          break;
        default :
          qUsage = "unknown";
          color = QColor(255, 20, 20);
        }

      // col. 0
      QString Name = FROM_UTF8(params[j]->getObjectName());
      if (!params[j]->isUsed())
        Name += " (unused)";

      Table1->setItem(j, COL_NAME, new ColorTableItem(Table1, QTableItem::WhenCurrent, color,
                      Name));

      // col. 1
      //QString temp = FROM_UTF8(CFunctionParameter::DataTypeName[params[j]->getType()]);
      //ComboItem * item = new ComboItem(Table1, QTableItem::WhenCurrent, color, functionType);
      //Table1->setItem(j, 1, item);
      //item->setText(temp);

      // col. 1
      QComboTableItem * item2 = new QComboTableItem(Table1, Usages);
      item2->setCurrentItem(qUsage);
      Table1->setItem(j, COL_USAGE, item2);

      //col. 2 (units)
      Table1->setItem(j, COL_UNIT, new ColorTableItem(Table1, QTableItem::WhenCurrent, color,
                      FROM_UTF8(units[j])));
    }
  Table1->adjustColumn(COL_UNIT);

  return true;
}

//! Function to generate the text representation of the usage restrictions
bool FunctionWidget1::loadUsageTable()
{
  std::vector<std::string> stringlist;
  bool checkSubstrates = false;
  bool checkProducts = false;

  if (RadioButton1->isChecked() == true)
    {
      stringlist.push_back("Only reversible reactions");
      checkSubstrates = true;
      checkProducts = true;
    }
  else if (RadioButton2->isChecked() == true)
    {
      stringlist.push_back("Only irreversible reactions");
      checkSubstrates = true;
    }

  //substrates
  if (checkSubstrates)
    {
      if (mpFunction->getVariables().isVector(CFunctionParameter::SUBSTRATE))
        {
          stringlist.push_back("At least one substrate");
        }
      else if (mpFunction->getObjectName() != "Constant flux (irreversible)" &&
               mpFunction->getObjectName() != "Constant flux (reversible)")
        {
          std::stringstream ss;

          if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::SUBSTRATE) == 0)
            {
              ss << "No substrate";
            }
          else
            {
              ss << "Exactly "
              << mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::SUBSTRATE)
              << " substrate";
              if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::SUBSTRATE) > 1)
                ss << "s"; //plural
            }
          stringlist.push_back(ss.str());
        }
    }

  //products
  if (checkProducts)
    {
      if (mpFunction->getVariables().isVector(CFunctionParameter::PRODUCT))
        {
          stringlist.push_back("At least one product");
        }
      else if (mpFunction->getObjectName() != "Constant flux (reversible)")
        {
          std::stringstream ss;
          if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::PRODUCT) == 0 &&
              mpFunction->getObjectName() != "Constant flux (reversible)")
            {
              ss << "No product";
            }
          else
            {
              ss << "Exactly "
              << mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::PRODUCT)
              << " product";
              if (mpFunction->getVariables().getNumberOfParametersByUsage(CFunctionParameter::PRODUCT) > 1)
                ss << "s"; //plural
            }
          stringlist.push_back(ss.str());
        }
    }

  if (stringlist.size() == 0)
    stringlist.push_back("None");

  Table2->setNumRows(stringlist.size());
  unsigned C_INT32 row;
  for (row = 0; row < stringlist.size(); ++row)
    {
      Table2->setText(row, 0, FROM_UTF8(stringlist[row]));
    }

  Table2->adjustColumn(0);

  return true;
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
      pdelete(mpFunction);
      mpFunction = dynamic_cast<CFunction *>(CEvaluationTree::copy(*func));
      flagChanged = false;
    }
  else if (!mpFunction)
    return false;

  // function name
  LineEdit1->setText(FROM_UTF8(mpFunction->getObjectName()));

  /* Insert line breaks in the function description */
  std::string desc = mpFunction->getInfix();
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
          if ((ch == '+') || (ch == '-') || (ch == '*') || (ch == '/') || (ch == ',') || (ch == ' '))
            break;
          l--;
        }
      // We did not find a suitable place to break the line
      if (l == n) l += 65;

      desc.insert(l, 1, '\n');
    }
  disconnect(textBrowser, SIGNAL(textChanged()), this, SLOT(slotFcnDescriptionChanged()));
  textBrowser->setText(FROM_UTF8(desc));
  connect(textBrowser, SIGNAL(textChanged()), this, SLOT(slotFcnDescriptionChanged()));

  //radio buttons
  loadReversibility(mpFunction->isReversible());

  //parameter table
  loadParameterTable();

  // application table
  loadUsageTable(/*pFunction->getVariables().getUsageRanges()*/);

  isValid = mpFunction->isUsable();

  // make dialogue read only for predefined functions
  if (mpFunction->getType() == CFunction::MassAction ||
      mpFunction->getType() == CFunction::PreDefined)
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
      commitChanges->setEnabled(isValid);
      cancelChanges->setEnabled(true);
      deleteFcn->setEnabled(true);
    }

  //MathML widget
  updateMmlWidget();

  flagChanged = false;

  return true;
}

bool FunctionWidget1::copyFunctionContentsToFunction(const CFunction* src, CFunction* target)
{
  //Parameters
  CFunctionParameters &functParam = target->getVariables();
  const CFunctionParameters &pfunctParam = src->getVariables();
  CFunctionParameter::DataType Type;
  unsigned C_INT32 index;
  unsigned C_INT32 i, j;

  if (src->getInfix() != target->getInfix())
    target->setInfix(src->getInfix());

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

  return true;
}

bool FunctionWidget1::functionParametersChanged()
{
  CFunction* func = dynamic_cast<CFunction*>(GlobalKeys.get(objKey));
  if (!func) return false;

  return (!(func->getVariables() == mpFunction->getVariables()));
}

bool FunctionWidget1::saveToFunction()
{
  CFunction* func = dynamic_cast<CFunction*>(GlobalKeys.get(objKey));
  if (!func) return false;

  //name
  QString name(LineEdit1->text());
  if (func->getObjectName() != (const char *)name.utf8())
    {
      // We need to check whether other trees call the current one.
      std::set<std::string> dependentTrees;
      if (CCopasiDataModel::Global->getModel())
        {
          dependentTrees =
            CCopasiDataModel::Global->getFunctionList()->listDependentTrees(func->getObjectName());
        }

      if (dependentTrees.size() > 0)
        {
          std::set<std::string>::iterator it = dependentTrees.begin();
          std::set<std::string>::iterator end = dependentTrees.end();

          QString trees;
          for (; it != end; it++)
            {
              trees.append(FROM_UTF8(*it));
              trees.append(" ---> ");
              trees.append(FROM_UTF8(mpFunction->getObjectName()));
              trees.append("\n");
            }

          QString msg1 = "Cannot change Function. ";
          msg1.append("Following dependencies with listed Function(s) exist:\n");
          msg1.append(trees);

          CQMessageBox::information(this, "Delete not possible",
                                    msg1, "OK", 0, 0, 0, 1);
          return false;
        }

      if (!func->setObjectName((const char *)name.utf8()))
        {
          QString msg;
          msg = "Unable to rename function '" + FROM_UTF8(func->getObjectName()) + "'\n"
                + "to '" + name + "' since a function with that name already exists.";

          CQMessageBox::information(this,
                                    "Unable to rename Function",
                                    msg,
                                    QMessageBox::Ok, QMessageBox::NoButton, QMessageBox::NoButton);

          LineEdit1->setText(FROM_UTF8(func->getObjectName()));
        }
      else
        protectedNotify(ListViews::FUNCTION, ListViews::RENAME, objKey);
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
      copyFunctionContentsToFunction(mpFunction, func);

      protectedNotify(ListViews::FUNCTION, ListViews::CHANGE, objKey);
    }

  func->compile();
  // :TODO: Bug 404 Create a message that the function is not valid by itself.

  // :TODO Bug 322: This should only be called when actual changes have been saved.
  CCopasiDataModel::Global->changed();

  flagChanged = false;
  return true;
}

//************** slots for changes in the widgets *************************************

//! Slot for changing the function description

/*!
   This slot function is called whenever the function description is changed.
 */
void FunctionWidget1::slotFcnDescriptionChanged()
{
  if (flagRO) return;

  flagChanged = true;

  try
    {
      if (mpFunction->setInfix((const char *)textBrowser->text().utf8()) &&
          mpFunction->compile())
        isValid = true;
      else
        isValid = false;
    }
  catch (CCopasiException Exception)
    {
      isValid = false;
    }

  if (isValid)
    {
      commitChanges->setEnabled(true);
    }
  else
    {
      if (CCopasiMessage::peekLastMessage().getNumber() == MCFunction + 4)
        {
          CQMessageBox::critical(this, "Function Error",
                                 CCopasiMessage::getLastMessage().getText().c_str(),
                                 QMessageBox::Ok | QMessageBox::Default,
                                 QMessageBox::NoButton);
          CCopasiMessage::clearDeque();
        }

      commitChanges->setEnabled(false);
    }

  //parameter table
  loadParameterTable();

  // application table
  //updateApplication();
  loadUsageTable();

  textBrowser->setFocus();
}

//! Slot for changing the table value
void FunctionWidget1::slotTableValueChanged(int row, int col)
{
  flagChanged = true;

  CFunctionParameters &functParam = mpFunction->getVariables();

  if (col == COL_USAGE) //Usage
    {
      QComboTableItem * tmpItem = dynamic_cast<QComboTableItem *>(Table1->item(row, col));
      if (!tmpItem) fatalError();
      CFunctionParameter::Role usage = (CFunctionParameter::Role)tmpItem->currentItem();

      functParam[row]->setUsage(usage);
    }

  //update tables
  loadParameterTable();
  loadUsageTable();
}

//! Slot for changing the reversibility of the function
void FunctionWidget1::slotReversibilityChanged()
{
  loadUsageTable();
}

//**************** slots for buttons *********************************************

//! Slot for being activated wehenver Cancel button is clicked
void FunctionWidget1::slotCancelButtonClicked()
{
  enter(objKey); // reload
}

//! Slot for being activated wehenver Commit button is clicked
void FunctionWidget1::slotCommitButtonClicked()
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;

  // :TODO: We should check what changes have been done to the function //
  CFunctionDB * pFunctionDB = CCopasiDataModel::Global->getFunctionList();
  if (pFunctionDB == NULL)
    return;

  CEvaluationTree * pFunction = dynamic_cast<CEvaluationTree *>(GlobalKeys.get(objKey));
  if (pFunction == NULL) return;

  if (functionParametersChanged())
    {
      QString functionList;
      QString effectedFunctionList = "Following FUNCTION(S) reference above FUNCTION(S) -\n";
      QString effectedReactionList = "Following REACTION(S) reference above FUNCTION(S) -\n";
      QString effectedMetaboliteList = "Following SPECIES reference above FUNCTION(S) -\n";
      QString effectedCompartmentList = "Following COMPARTMENT(S) reference above FUNCTION(S) -\n";
      QString effectedValueList = "Following MODEL QUANTIT(S) reference above FUNCTION(S) -\n";

      std::set< const CCopasiObject * > Reactions;
      std::set< const CCopasiObject * > Metabolites;
      std::set< const CCopasiObject * > Values;
      std::set< const CCopasiObject * > Compartments;

      bool functionFound = false;
      bool reactionFound = false;
      bool metaboliteFound = false;
      bool compartmentFound = false;
      bool valueFound = false;

      std::set< const CCopasiObject * > ToBeDeleted;
      ToBeDeleted.insert(pFunction);
      ToBeDeleted.insert(pFunction->getObject(CCopasiObjectName("Reference=Value")));

      functionList.append(FROM_UTF8(pFunction->getObjectName()));
      functionList.append(", ");

      std::set< const CCopasiObject * > Functions;
      pFunctionDB->appendDependentFunctions(ToBeDeleted, Functions);

      if (Functions.size() > 0)
        {
          functionFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Functions.end();
          for (it = Functions.begin(); it != itEnd; ++it)
            {
              effectedFunctionList.append(FROM_UTF8((*it)->getObjectName()));
              effectedFunctionList.append(", ");
            }

          effectedFunctionList.remove(effectedFunctionList.length() - 2, 2);
          effectedFunctionList.append("  ---> ");
          effectedFunctionList.append(FROM_UTF8(pFunction->getObjectName()));
          effectedFunctionList.append("\n");
        }

      pModel->appendDependentModelObjects(ToBeDeleted,
                                          Reactions, Metabolites, Compartments, Values);

      if (Reactions.size() > 0)
        {
          reactionFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Reactions.end();
          for (it = Reactions.begin(); it != itEnd; ++it)
            {
              effectedReactionList.append(FROM_UTF8((*it)->getObjectName()));
              effectedReactionList.append(", ");
            }

          effectedReactionList.remove(effectedReactionList.length() - 2, 2);
          effectedReactionList.append("  ---> ");
          effectedReactionList.append(FROM_UTF8(pFunction->getObjectName()));
          effectedReactionList.append("\n");
        }

      if (Metabolites.size() > 0)
        {
          metaboliteFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Metabolites.end();
          for (it = Metabolites.begin(); it != itEnd; ++it)
            {
              effectedMetaboliteList.append(FROM_UTF8((*it)->getObjectName()));
              effectedMetaboliteList.append(", ");
            }

          effectedMetaboliteList.remove(effectedMetaboliteList.length() - 2, 2);
          effectedMetaboliteList.append("  ---> ");
          effectedMetaboliteList.append(FROM_UTF8(pFunction->getObjectName()));
          effectedMetaboliteList.append("\n");
        }

      if (Compartments.size() > 0)
        {
          compartmentFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Compartments.end();
          for (it = Compartments.begin(); it != itEnd; ++it)
            {
              effectedCompartmentList.append(FROM_UTF8((*it)->getObjectName()));
              effectedCompartmentList.append(", ");
            }

          effectedCompartmentList.remove(effectedCompartmentList.length() - 2, 2);
          effectedCompartmentList.append("  ---> ");
          effectedCompartmentList.append(FROM_UTF8(pFunction->getObjectName()));
          effectedCompartmentList.append("\n");
        }

      if (Values.size() > 0)
        {
          valueFound = true;
          std::set< const CCopasiObject * >::const_iterator it, itEnd = Values.end();
          for (it = Values.begin(); it != itEnd; ++it)
            {
              effectedValueList.append(FROM_UTF8((*it)->getObjectName()));
              effectedValueList.append(", ");
            }

          effectedValueList.remove(effectedValueList.length() - 2, 2);
          effectedValueList.append("  ---> ");
          effectedValueList.append(FROM_UTF8(pFunction->getObjectName()));
          effectedValueList.append("\n");
        }

      functionList.remove(functionList.length() - 2, 2);

      QString msg;

      if (functionFound || reactionFound || metaboliteFound || compartmentFound || valueFound)
        {
          msg = "Cannot modify FUNCTION(S).\n" + functionList;

          if (functionFound)
            {
              msg.append("\n \n");
              msg.append(effectedFunctionList);
            }

          if (reactionFound)
            {
              msg.append("\n \n");
              msg.append(effectedReactionList);
            }

          if (metaboliteFound)
            {
              msg.append("\n \n");
              msg.append(effectedMetaboliteList);
            }

          if (compartmentFound)
            {
              msg.append("\n \n");
              msg.append(effectedCompartmentList);
            }

          if (valueFound)
            {
              msg.append("\n \n");
              msg.append(effectedValueList);
            }

          CQMessageBox::information(this, "Modification not possible",
                                    msg, "OK", 0, 0, 0, 1);

          return;
        }
    }

  if (isValid)
    {
      saveToFunction();
      updateMmlWidget();
    }

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

//! Slot for being activated wehenver New button is clicked
void FunctionWidget1::slotNewButtonClicked()
{
  slotCommitButtonClicked();

  std::string name = "function";
  int i = 0;
  CFunction* pFunc;
  CCopasiVectorN<CEvaluationTree>& FunctionList
  = CCopasiDataModel::Global->getFunctionList()->loadedFunctions();

  while (FunctionList.getIndex(name) != C_INVALID_INDEX)
    {
      i++;
      name = "function_";
      name += (const char *)QString::number(i).utf8();
    }

  CCopasiDataModel::Global->getFunctionList()->add(pFunc = new CKinFunction(name), true);

  protectedNotify(ListViews::FUNCTION, ListViews::ADD);
  enter(pFunc->getKey());

  mFormulaEditToggleButton->hide();

  mpSaveBtn->setEnabled(false);
}

//! Slot for being activated wehenver Delete button is clicked
void FunctionWidget1::slotDeleteButtonClicked()
{
  CModel * pModel = CCopasiDataModel::Global->getModel();
  if (pModel == NULL)
    return;

  CFunctionDB * pFunctionDB = CCopasiDataModel::Global->getFunctionList();
  if (pFunctionDB == NULL)
    return;

  CEvaluationTree * pFunction = dynamic_cast<CEvaluationTree *>(GlobalKeys.get(objKey));
  if (pFunction == NULL)
    return;

  QString functionList;
  QString effectedFunctionList = "Following FUNCTION(S) reference above FUNCTION(S) -\n";
  QString effectedReactionList = "Following REACTION(S) reference above FUNCTION(S) -\n";
  QString effectedMetaboliteList = "Following SPECIES reference above FUNCTION(S) -\n";
  QString effectedCompartmentList = "Following COMPARTMENT(S) reference above FUNCTION(S) -\n";
  QString effectedValueList = "Following MODEL QUANTIT(S) reference above FUNCTION(S) -\n";

  bool functionFound = false;
  bool reactionFound = false;
  bool metaboliteFound = false;
  bool compartmentFound = false;
  bool valueFound = false;

  std::set< const CCopasiObject * > ToBeDeleted;
  ToBeDeleted.insert(pFunction);
  ToBeDeleted.insert(pFunction->getObject(CCopasiObjectName("Reference=Value")));

  functionList.append(FROM_UTF8(pFunction->getObjectName()));
  functionList.append(", ");

  std::set< const CCopasiObject * > Functions;
  pFunctionDB->appendDependentFunctions(ToBeDeleted, Functions);

  if (Functions.size() > 0)
    {
      functionFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Functions.end();
      for (it = Functions.begin(); it != itEnd; ++it)
        {
          effectedFunctionList.append(FROM_UTF8((*it)->getObjectName()));
          effectedFunctionList.append(", ");
        }

      effectedFunctionList.remove(effectedFunctionList.length() - 2, 2);
      effectedFunctionList.append("  ---> ");
      effectedFunctionList.append(FROM_UTF8(pFunction->getObjectName()));
      effectedFunctionList.append("\n");
    }

  std::set< const CCopasiObject * > Reactions;
  std::set< const CCopasiObject * > Metabolites;
  std::set< const CCopasiObject * > Values;
  std::set< const CCopasiObject * > Compartments;

  pModel->appendDependentModelObjects(ToBeDeleted,
                                      Reactions, Metabolites, Compartments, Values);

  if (Reactions.size() > 0)
    {
      reactionFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Reactions.end();
      for (it = Reactions.begin(); it != itEnd; ++it)
        {
          effectedReactionList.append(FROM_UTF8((*it)->getObjectName()));
          effectedReactionList.append(", ");
        }

      effectedReactionList.remove(effectedReactionList.length() - 2, 2);
      effectedReactionList.append("  ---> ");
      effectedReactionList.append(FROM_UTF8(pFunction->getObjectName()));
      effectedReactionList.append("\n");
    }

  if (Metabolites.size() > 0)
    {
      metaboliteFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Metabolites.end();
      for (it = Metabolites.begin(); it != itEnd; ++it)
        {
          effectedMetaboliteList.append(FROM_UTF8((*it)->getObjectName()));
          effectedMetaboliteList.append(", ");
        }

      effectedMetaboliteList.remove(effectedMetaboliteList.length() - 2, 2);
      effectedMetaboliteList.append("  ---> ");
      effectedMetaboliteList.append(FROM_UTF8(pFunction->getObjectName()));
      effectedMetaboliteList.append("\n");
    }

  if (Compartments.size() > 0)
    {
      compartmentFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Compartments.end();
      for (it = Compartments.begin(); it != itEnd; ++it)
        {
          effectedCompartmentList.append(FROM_UTF8((*it)->getObjectName()));
          effectedCompartmentList.append(", ");
        }

      effectedCompartmentList.remove(effectedCompartmentList.length() - 2, 2);
      effectedCompartmentList.append("  ---> ");
      effectedCompartmentList.append(FROM_UTF8(pFunction->getObjectName()));
      effectedCompartmentList.append("\n");
    }

  if (Values.size() > 0)
    {
      valueFound = true;
      std::set< const CCopasiObject * >::const_iterator it, itEnd = Values.end();
      for (it = Values.begin(); it != itEnd; ++it)
        {
          effectedValueList.append(FROM_UTF8((*it)->getObjectName()));
          effectedValueList.append(", ");
        }

      effectedValueList.remove(effectedValueList.length() - 2, 2);
      effectedValueList.append("  ---> ");
      effectedValueList.append(FROM_UTF8(pFunction->getObjectName()));
      effectedValueList.append("\n");
    }

  functionList.remove(functionList.length() - 2, 2);

  QString msg;

  if (functionFound || reactionFound || metaboliteFound || compartmentFound || valueFound)
    {
      msg = "Cannot delete FUNCTION(S).\n" + functionList;

      if (functionFound)
        {
          msg.append("\n \n");
          msg.append(effectedFunctionList);
        }

      if (reactionFound)
        {
          msg.append("\n \n");
          msg.append(effectedReactionList);
        }

      if (metaboliteFound)
        {
          msg.append("\n \n");
          msg.append(effectedMetaboliteList);
        }

      if (compartmentFound)
        {
          msg.append("\n \n");
          msg.append(effectedCompartmentList);
        }

      if (valueFound)
        {
          msg.append("\n \n");
          msg.append(effectedValueList);
        }

      CQMessageBox::information(this, "Delete not possible",
                                msg, "OK", 0, 0, 0, 1);

      return;
    }

  msg = "Are you sure to delete listed Function(s)?\n" + functionList;

  int choice = CQMessageBox::question(this,
                                      "CONFIRM DELETE",
                                      msg,
                                      "Continue", "Cancel", 0, 1, 1);

  /* Check if user chooses to deleted Functions */
  switch (choice)
    {
    case 0:                                                    // Yes or Enter
      {
        unsigned C_INT32 index =
          CCopasiDataModel::Global->getFunctionList()->loadedFunctions().getIndex(mpFunction->getObjectName());

        CCopasiDataModel::Global->getFunctionList()->removeFunction(objKey);

        unsigned C_INT32 size =
          CCopasiDataModel::Global->getFunctionList()->loadedFunctions().size();

        if (size > 0)
          enter(CCopasiDataModel::Global->getFunctionList()->loadedFunctions()[std::min(index, size - 1)]->getKey());
        else
          enter("");

        protectedNotify(ListViews::FUNCTION, ListViews::DELETE, objKey);

        break;
      }

    default:                                                    // No or Escape
      break;
    }
}

//***********  slot for editing requests on the function formula (mMmlWidget) *****

//! Slot for being activated wehenver Edit button under Functions display is clicked
void FunctionWidget1::slotToggleFcnDescriptionEdit()
{
  mStack->raiseWidget(textBrowser);

  mFormulaEditToggleButton->hide();

  mpSaveBtn->setEnabled(false);
}

//! Function to update the function formula
void FunctionWidget1::updateMmlWidget()
{
#ifdef HAVE_MML
  std::ostringstream mml;
  std::vector<std::vector<std::string> > params;

  if (textBrowser->isReadOnly())
    mFormulaEditToggleButton->hide();
  else
    mFormulaEditToggleButton->show();

  mStack->raiseWidget(mMmlViewBox);

  mpSaveBtn->setEnabled(true);

  mpFunction->createListOfParametersForMathML(params);

  if (textBrowser->text().isEmpty())
    {
      mStack->raiseWidget(textBrowser);

      mpSaveBtn->setEnabled(false);
    }
  else
    mpFunction->writeMathML(mml, params, true, false, 0);

  MMLStr = FROM_UTF8(mml.str());

  //  mMmlWidget->setContent(FROM_UTF8(mml.str()));
  mMmlWidget->setContent(MMLStr);

  mScrollView->resizeContents(mMmlWidget->sizeHint().width(), mMmlWidget->sizeHint().height());
  mScrollView->setMinimumHeight(mMmlWidget->sizeHint().height() + 30);

#endif // HAVE_MML
}

//************************  standard interface to copasi widgets ******************

//! Function to update the COPASI widgets
bool FunctionWidget1::update(ListViews::ObjectType objectType, ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::FUNCTION:
      return loadFromFunction(dynamic_cast< CFunction * >(GlobalKeys.get(objKey)));
      break;

    default:
      break;
    }
  return true;
}

bool FunctionWidget1::leave()
{
  slotCommitButtonClicked();

  //mScrollView->hide();
  return true;
}

bool FunctionWidget1::enter(const std::string & key)
{
  objKey = key;
  CFunction* func = dynamic_cast<CFunction*>(GlobalKeys.get(key));

  if (func)
    return loadFromFunction(func);

  mpListView->switchToOtherWidget(5, "");
  return false;
}

// add 21.07.08
void FunctionWidget1::slotSave()
{
  QString filter;
  QString outfilename;

  C_INT32 Answer = QMessageBox::No;

  while (Answer == QMessageBox::No)
    {
      outfilename =
        CopasiFileDialog::getSaveFileNameAndFilter(filter,
            this,
            "Save File Dialog",
            QString::null,
            "MathML (*.mml);;XML (*.xml);;TeX (*.tex);;",
            "Save Formula to Disk");

      if (!outfilename) return;

      // Checks whether the file exists
      Answer = checkSelection(outfilename);

      if (Answer == QMessageBox::Cancel)
        return;
    }

  if (filter.contains("tex"))
    saveTeX(outfilename);
  else
    saveMML(outfilename);
}

// add 21.07.08
void FunctionWidget1::saveMML(const QString outfilename)
{
  std::ofstream ofile;
  ofile.open(utf8ToLocale((const char *)outfilename.utf8()).c_str(), std::ios::trunc);

  ofile << "<?xml version=\"1.0\" encoding=\"UTF-8\"?>" << std::endl;
  ofile << "<!DOCTYPE html PUBLIC \"-//W3C//DTD XHTML 1.1 plus MathML 2.0//EN\" \"HTMLFiles/xhtml-math11-f.dtd\">" << std::endl;
  ofile << "<math xmlns=\"http://www.w3.org/1998/Math/MathML\">" << std::endl;

  //  ofile << mml.str();
  ofile << MMLStr.latin1();

  ofile << "</math>" << std::endl;

  ofile.close();
}

// add 21.07.08
void FunctionWidget1::saveTeX(const QString outfilename)
{
  QString latexStr(MMLStr.latin1());

  CMathMLToTeX::convert(latexStr);

  std::ofstream ofile;
  ofile.open(utf8ToLocale((const char *)outfilename.utf8()).c_str(), std::ios::trunc);
  ofile << latexStr;
  //  ofile << mml.str() << std::endl;
  ofile.close();
}
