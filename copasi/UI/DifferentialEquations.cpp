/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/DifferentialEquations.cpp,v $
   $Revision: 1.20 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/02 13:47:32 $
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
#include <qmessagebox.h>
#include <qfont.h>
#include <qtextbrowser.h>
#include <qstylesheet.h>

#include "DifferentialEquations.h"
#include "mathmodel/CMathModel.h"
#include "mathmodel/CMathVariable.h"
#include "mathmodel/CMathEq.h"
#include "listviews.h"
#include "DataModelGUI.h"
#include "qtUtilities.h"

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
  textBrowser = new QTextBrowser (this, "Text Browser");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(textBrowser);

  QStyleSheet * Style = new QStyleSheet;
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
  textBrowser->setTextFormat(Qt::RichText);

  //btnOK = new QPushButton("&OK", this);
  //btnCancel = new QPushButton("&Cancel", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  /*hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(50);*/

  //connect(btnOK, SIGNAL(clicked ()), this, SLOT(slotBtnOKClicked()));
  //connect(btnCancel, SIGNAL(clicked ()), this, SLOT(slotBtnCancelClicked()));
}

void DifferentialEquations::loadDifferentialEquations(CMathModel * mathModel)
{
  dataModel->updateMathModel();

  if (mathModel != NULL)
    {
      std::map< std::string, CMathVariableMetab * > & MetabList =
        mathModel->getMetabList();
      std::map< std::string, CMathVariableMetab * >::iterator it =
        MetabList.begin();
      std::map< std::string, CMathVariableMetab * >::iterator end =
        MetabList.end();

      QString Text;
      CMathEq *pMathEq = NULL;
      for (; it != end; ++it)
        {
          pMathEq = it->second->getEq();
          Text += QString::fromUtf8("<lhs>");
          Text += FROM_UTF8(pMathEq->getLeft().getData());
          Text += QString::fromUtf8(" =</lhs>");

          Text += QString::fromUtf8("<rhs>");
          Text += FROM_UTF8(pMathEq->getRight().getData());
          Text += QString::fromUtf8("</rhs>");
        }

      textBrowser->setText(Text);
    }
}

/***********ListViews::showMessage(QString caption,QString text)------------------------>
 **
 ** Parameters:- 1. QString :- The Title that needs to be displayed in message box
 **              2. QString :_ The Text that needs to be displayed in the message box
 ** Returns  :-  void(Nothing)
 ** Description:- This method is used to show the message box on the screen
 ****************************************************************************************/

void DifferentialEquations::slotBtnOKClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to commit changes");
}

void DifferentialEquations::slotBtnCancelClicked()
{
  //QMessageBox::information(this, "Metabolites Widget", "Do you really want to cancel changes");
}

bool DifferentialEquations::update(ListViews::ObjectType objectType,
                                   ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  switch (objectType)
    {
    case ListViews::MODEL:
    case ListViews::COMPARTMENT:
    case ListViews::METABOLITE:
    case ListViews::REACTION:
    case ListViews::FUNCTION:
      loadDifferentialEquations(dataModel->getMathModel());
      break;

    default:
      break;
    }
  return true;
}

bool DifferentialEquations::enter(const std::string & C_UNUSED(key))
{
  loadDifferentialEquations(dataModel->getMathModel());
  return true;
}
