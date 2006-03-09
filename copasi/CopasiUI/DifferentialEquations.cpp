/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/DifferentialEquations.cpp,v $
   $Revision: 1.23 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2006/03/09 12:55:32 $
   End CVS Header */

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
  out << SPC(l + 2) << "<mi>d</mi>" << std::endl;
  out << SPC(l + 2) << "<mfenced>" << std::endl;
  out << SPC(l + 3) << "<mrow>" << std::endl;
  out << SPC(l + 4) << "<mi>" << CMathMl::fixName(metabName) << "</mi>" << std::endl;
  out << SPC(l + 4) << "<mo>" << "&CenterDot;" << "</mo>" << std::endl;
  out << SPC(l + 4) << "<msub><mi>V</mi><mi>" << CMathMl::fixName(compName) << "</mi></msub>" << std::endl;

  out << SPC(l + 3) << "</mrow>" << std::endl;

  out << SPC(l + 2) << "</mfenced>" << std::endl;
  out << SPC(l + 1) << "</mrow>" << std::endl;
  out << SPC(l + 1) << "<mi>dt</mi>" << std::endl;
  out << SPC(l + 0) << "</mfrac>" << std::endl;
}

void DifferentialEquations::writeRHS(std::ostream & out,
                                     const CMetab* pMetab, const CReaction* pReac,
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
  if (&pReac->getFunction())
    pReac->getFunction().writeMathML(out, l + 1);

  out << SPC(l + 0) << "</mrow>" << std::endl;
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
      std::set<std::string> reacKeys = model->listReactionsDependentOnMetab(model->getMetabolites()[i]->getKey());
      std::set<std::string>::const_iterator it, itEnd = reacKeys.end();
      for (it = reacKeys.begin(); it != itEnd; ++it)
        {
          mml << SPC(l + 1) << "<mtr>" << std::endl;

          //first column (lhs)
          mml << SPC(l + 2) << "<mtd>" << std::endl;
          if (it == reacKeys.begin())
            writeLHS(mml, model->getMetabolites()[i]->getObjectName(),
                     model->getMetabolites()[i]->getCompartment()->getObjectName(), l + 3);
          mml << SPC(l + 2) << "</mtd>" << std::endl;

          //second column ("=")
          mml << SPC(l + 2) << "<mtd>" << std::endl;
          if (it == reacKeys.begin())
            mml << SPC(l + 3) << "=" << std::endl;
          mml << SPC(l + 2) << "</mtd>" << std::endl;

          //third column (rhs)
          mml << SPC(l + 2) << "<mtd columnalign='left'>" << std::endl;
          writeRHS(mml, model->getMetabolites()[i],
                   dynamic_cast<CReaction*>(GlobalKeys.get(*it)) , l + 3);
          mml << SPC(l + 2) << "</mtd>" << std::endl;

          mml << SPC(l + 1) << "</mtr>" << std::endl;
        }
    }

  mml << SPC(l) << "</mtable>" << std::endl;

  mMmlWidget->setContent(FROM_UTF8(mml.str()));
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
