/***********************************************************************
 **  $ CopasiUI/MetabolitesWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the  information
 ** obtained from the data model about the Metabolites----It is 
 ** Basically the First level of Metabolites.
 ************************************************************************/
#include <qlayout.h>
#include <qwidget.h>
#include <qmessagebox.h>
#include "DifferentialEquations.h"
#include "listviews.h"
#include <qfont.h>
#include <qtextbrowser.h>

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
    : QWidget(parent, name, f)
{
  textBrowser = new QTextBrowser (this, "Text Browser");
  QVBoxLayout *vBoxLayout = new QVBoxLayout(this, 0);
  vBoxLayout->addWidget(textBrowser);
  textBrowser->setText("This is the text browser for entering ascii text....enter text...");
  textBrowser->setReadOnly(false);
  btnOK = new QPushButton("&OK", this);
  btnCancel = new QPushButton("&Cancel", this);

  QHBoxLayout *hBoxLayout = new QHBoxLayout(vBoxLayout, 0);

  //To match the Table left Vertical Header Column Width.
  hBoxLayout->addSpacing(32);

  hBoxLayout->addSpacing(50);
  hBoxLayout->addWidget(btnOK);
  hBoxLayout->addSpacing(5);
  hBoxLayout->addWidget(btnCancel);
  hBoxLayout->addSpacing(50);

  connect(btnOK, SIGNAL(clicked ()), this, SLOT(slotBtnOKClicked()));
  connect(btnCancel, SIGNAL(clicked ()), this, SLOT(slotBtnCancelClicked()));
}

void DifferentialEquations::loadDifferentialEquations()
{
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
