/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/DifferentialEquations.cpp,v $
   $Revision: 1.29.2.1 $
   $Name:  $
   $Author: nsimus $
   $Date: 2006/05/18 10:04:13 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*******************************************************************
 **  $ CopasiUI/DifferentialEquations.cpp
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the
 ** information obtained from the data model about the
 ** Differential Equations
 ********************************************************************/
#include <qlayout.h>
#include <qwidget.h>
#include <qscrollview.h>
#include <qmessagebox.h>
#include <qlayout.h>

#include <sstream>

//#include <qfont.h>
//#include <qtextbrowser.h>
//#include <qstylesheet.h>

#include "DifferentialEquations.h"
//#include "mathmodel/CMathModel.h"
//#include "mathmodel/CMathVariable.h"
//#include "mathmodel/CMathEq.h"
#include "listviews.h"
//#include "DataModelGUI.h"
#include "CopasiDataModel/CCopasiDataModel.h"
#include "qtUtilities.h"
#include "model/CModel.h"
#include "report/CKeyFactory.h"

#include "mml/qtmmlwidget.h"

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
DifferentialEquations::DifferentialEquations(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)
{
  //textBrowser = new QTextBrowser (this, "Text Browser");
  //QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  QGridLayout* layout = new QGridLayout(this, 1, 1, 11, 6, "DEWidgetLayout");

  //vBoxLayout->addWidget(textBrowser);

  /*QStyleSheet * Style = new QStyleSheet;
  QStyleSheetItem * lhs = new QStyleSheetItem(Style, "lhs");
  lhs->setDisplayMode(QStyleSheetItem::DisplayBlock);
  QStyleSheetItem * rhs = new QStyleSheetItem(Style, "rhs");
  rhs->setDisplayMode(QStyleSheetItem::DisplayBlock);
  rhs->setMargin(QStyleSheetItem::MarginLeft, 20);
  rhs->setMargin(QStyleSheetItem::MarginBottom, 10);
  QStyleSheetItem * emp = new QStyleSheetItem(Style, "emp");
  emp->setDisplayMode(QStyleSheetItem::DisplayInline);
  emp->setFontItalic(true);

  textBrowser->setStyleSheet(Style);
  textBrowser->setTextFormat(Qt::RichText);*/

  mScrollView = new QScrollView(this);
  layout->addWidget(mScrollView, 0, 0);

  mScrollView->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mScrollView->setResizePolicy(QScrollView::AutoOneFit);

  mMmlWidget = new QtMmlWidget(mScrollView->viewport());
  mMmlWidget->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::Expanding);
  mMmlWidget->setBaseFontPointSize(this->fontInfo().pointSize());
  mMmlWidget->setFontName(QtMmlWidget::NormalFont, this->fontInfo().family());

  mScrollView->addChild(mMmlWidget);

  //btnOK = new QPushButton("&OK", this);
  //btnCancel = new QPushButton("&Cancel", this);

  //QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  //hBoxLayout->addSpacing(32);

  /*hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(50);*/

  //connect(btnOK, SIGNAL(clicked ()), this, SLOT(slotBtnOKClicked()));
  //connect(btnCancel, SIGNAL(clicked ()), this, SLOT(slotBtnCancelClicked()));
}

#include "utilities/copasimathml.h"

void DifferentialEquations::writeLHS(std::ostream & out,
                                     const std::string & metabName,
                                     const std::string & compName, unsigned C_INT32 l)
{
  out << SPC(l + 0) << "<mfrac>" << std::endl;
  out << SPC(l + 1) << "<mrow>" << std::endl;
  out << SPC(l + 2) << "<mo>d</mo>" << std::endl;
  out << SPC(l + 2) << "<mfenced>" << std::endl;
  out << SPC(l + 3) << "<mrow>" << std::endl;
  //out << SPC(l + 4) << "<mi>" << CMathMl::fixName(metabName) << "</mi>" << std::endl;
  out << SPC(l + 4) << "<mi>[" << metabName << "]</mi>" << std::endl;
  out << SPC(l + 4) << "<mo>" << "&CenterDot;" << "</mo>" << std::endl;
  out << SPC(l + 4) << "<msub><mi>V</mi><mi>" << CMathMl::fixName(compName) << "</mi></msub>" << std::endl;

  out << SPC(l + 3) << "</mrow>" << std::endl;

  out << SPC(l + 2) << "</mfenced>" << std::endl;
  out << SPC(l + 1) << "</mrow>" << std::endl;
  out << SPC(l + 1) << "<mrow>" << std::endl;
  out << SPC(l + 2) << "<mo>d</mo><mi>t</mi>" << std::endl;
  out << SPC(l + 1) << "</mrow>" << std::endl;
  out << SPC(l + 0) << "</mfrac>" << std::endl;
}

void DifferentialEquations::writeRHS(std::ostream & out,
                                     const CMetab* pMetab, const CReaction* pReac,
                                     bool expand, bool expandFull,
                                     unsigned C_INT32 l)
{
  if (!pMetab)
    {
      out << SPC(l + 0) << "Error: invalid metabolite" << std::endl;
      return;
    }
  if (!pReac)
    {
      out << SPC(l + 0) << "Error: invalid reaction" << std::endl;
      return;
    }

  const CCopasiVector < CChemEqElement > & balances = pReac->getChemEq().getBalances();
  C_FLOAT64 balance = 0;
  unsigned C_INT32 i, imax = balances.size();
  for (i = 0; i < imax; ++i)
    {
      if (balances[i]->getMetaboliteKey() == pMetab->getKey())
        {
          balance = balances[i]->getMultiplicity();
          break;
        }
    }

  if (0 == balance) return;

  out << SPC(l + 0) << "<mrow>" << std::endl;

  //balance
  if (balance == 1.0)
    {
      out << SPC(l + 1) << "<mo>" << "+" << "</mo>" << std::endl;
    }
  else if (balance == -1.0)
    {
      out << SPC(l + 1) << "<mo>" << "-" << "</mo>" << std::endl;
    }
  else if (balance < 0.0)
    {
      out << SPC(l + 1) << "<mo>" << "-" << "</mo><mn>" << -balance << "</mn>"
      << "<mo>" << "&CenterDot;" << "</mo>" << std::endl;
    }
  else // >0
    {
      out << SPC(l + 1) << "<mo>" << "+" << "</mo><mn>" << balance << "</mn>"
      << "<mo>" << "&CenterDot;" << "</mo>" << std::endl;
    }

  //compartment volume?
  if (pReac->getCompartmentNumber() == 1)
    {
      std::string compName = pMetab->getCompartment()->getObjectName();
      out << SPC(l + 1) << "<msub><mi>V</mi><mi>" << CMathMl::fixName(compName)
      << "</mi></msub>" << std::endl;
      out << SPC(l + 1) << "<mo>" << "&CenterDot;" << "</mo>" << std::endl;
    }

  //kinetic function
  if (pReac->getFunction())
    {
      std::vector<std::vector<std::string> > params;
      createParameterMapping(pReac, params);
      if (expand) out << SPC(l + 1) << "<mfenced>" << std::endl;
      pReac->getFunction()->writeMathML(out, params, expand, expandFull, l + 1);
      if (expand) out << SPC(l + 1) << "</mfenced>" << std::endl;
    }

  out << SPC(l + 0) << "</mrow>" << std::endl;
}

void DifferentialEquations::createParameterMapping(const CReaction* pReac,
    std::vector<std::vector<std::string> > & params)
{
  assert(pReac);
  assert(pReac->getFunction());

  const CFunctionParameters & functionParams = pReac->getFunctionParameters();
  unsigned C_INT32 j, jmax;
  unsigned C_INT32 i, imax = functionParams.size();
  params.resize(imax);
  for (i = 0; i < imax; ++i)
    {
      params[i].resize(1);

      std::string name;
      //std::ostringstream number;
      switch (functionParams[i]->getUsage())
        {
        case CFunctionParameter::SUBSTRATE:
        case CFunctionParameter::PRODUCT:
        case CFunctionParameter::MODIFIER:
          if (functionParams[i]->getType() == CFunctionParameter::FLOAT64)
            {
              name = GlobalKeys.get(pReac->getParameterMappings()[i][0])->getObjectDisplayName();
              //params[i][0] = "<mi>"+ CMathMl::fixName(name)+"</mi>";
              params[i][0] = "<mi>[" + name + "]</mi>";
            }
          else if (functionParams[i]->getType() == CFunctionParameter::VFLOAT64)
            {
              jmax = pReac->getParameterMappings()[i].size();
              params[i].resize(jmax);
              for (j = 0; j < jmax; ++j)
                {
                  name = GlobalKeys.get(pReac->getParameterMappings()[i][j])->getObjectDisplayName();
                  //params[i][j] = "<mi>"+ CMathMl::fixName(name)+"</mi>";
                  params[i][j] = "<mi>[" + name + "]</mi>";
                }
            }
          else assert(false);
          break;

        case CFunctionParameter::PARAMETER:
          if (pReac->isLocalParameter(i))
            {
              std::ostringstream number;
              number << pReac->getParameterValue(functionParams[i]->getObjectName());
              params[i][0] = "<mn>" + number.str() + "</mn>";
            }
          else
            {
              name = GlobalKeys.get(pReac->getParameterMappings()[i][0])->getObjectName();
              params[i][0] = "<mi>" + CMathMl::fixName(name) + "</mi>";
              //params[i][0] = "<mi>ggg</mi>";
            }
          break;

        case CFunctionParameter::VOLUME:
          name = GlobalKeys.get(pReac->getParameterMappings()[i][0])->getObjectName();
          params[i][0] = "<msub><mi>V</mi><mi>" + CMathMl::fixName(name)
                         + "</mi></msub>";
          break;

        case CFunctionParameter::TIME:
          params[i][0] = "<mi>time</mi>";
          break;

        default:
          break;
        }
    }
}

void DifferentialEquations::loadDifferentialEquations(CModel * model)
{
  std::ostringstream mml;
  unsigned C_INT32 l = 0;
  //pFunction->writeMathML(mml);
  mml << SPC(l) << "<mtable>" << std::endl;

  C_INT32 i, imax = model->getMetabolites().size();
  for (i = 0; i < imax; i++)
    {
      std::set<std::string> reacKeys = listReactionsForMetab(model, model->getMetabolites()[i]->getKey());
      std::set<std::string>::const_iterator it, itEnd = reacKeys.end();
      for (it = reacKeys.begin(); it != itEnd; ++it)
        {
          mml << SPC(l + 1) << "<mtr>" << std::endl;

          //first column (lhs)
          mml << SPC(l + 2) << "<mtd>" << std::endl;
          if (it == reacKeys.begin())
            writeLHS(mml, model->getMetabolites()[i]->getObjectDisplayName(),
                     model->getMetabolites()[i]->getCompartment()->getObjectName(), l + 3);
          mml << SPC(l + 2) << "</mtd>" << std::endl;

          //second column ("=")
          mml << SPC(l + 2) << "<mtd>" << std::endl;
          if (it == reacKeys.begin())
            mml << SPC(l + 3) << "<mo>=</mo>" << std::endl;
          mml << SPC(l + 2) << "</mtd>" << std::endl;

          //third column (rhs)
          mml << SPC(l + 2) << "<mtd columnalign='left'>" << std::endl;
          writeRHS(mml, model->getMetabolites()[i],
                   dynamic_cast<CReaction*>(GlobalKeys.get(*it)) ,
                   true, false, l + 3); //TODO make configurable
          mml << SPC(l + 2) << "</mtd>" << std::endl;

          mml << SPC(l + 1) << "</mtr>" << std::endl;
        }
    }

  mml << SPC(l) << "</mtable>" << std::endl;

  mMmlWidget->setContent(FROM_UTF8(mml.str()));
  mScrollView->resizeContents(mMmlWidget->sizeHint().width(), mMmlWidget->sizeHint().height());
  //std::cout << mml.str() << std::endl;
}

std::set<std::string> DifferentialEquations::listReactionsForMetab(const CModel* model,
    const std::string & key)
{
  std::set<std::string> Keys;
  const CCopasiVectorN<CReaction> & Reactions = model->getReactions();
  C_INT32 j, jmax = Reactions.size();

  for (j = 0; j < jmax; j++)
    {
      const CCopasiVector <CChemEqElement> &Balances = Reactions[j]->getChemEq().getBalances();
      C_INT32 i, imax = Balances.size();
      for (i = 0; i < imax; i++)
        if (key == Balances[i]->getMetaboliteKey())
          {
            Keys.insert(Reactions[j]->getKey());
            break;
          }
    }

  return Keys;
}

//void DifferentialEquations::slotBtnOKClicked()
//{}

//void DifferentialEquations::slotBtnCancelClicked()
//{}

bool DifferentialEquations::update(ListViews::ObjectType objectType,
                                   ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  if (mIgnoreUpdates) return true;

  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
    case ListViews::REACTION:
    case ListViews::FUNCTION:
      loadDifferentialEquations(CCopasiDataModel::Global->getModel());
      break;

    default:
      break;
    }
  return true;
}

bool DifferentialEquations::enter(const std::string & C_UNUSED(key))
{
  loadDifferentialEquations(CCopasiDataModel::Global->getModel());
  return true;
}
