/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CopasiDefaultWidget.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/07/04 15:48:20 $
   End CVS Header */

/*******************************************************************
 **  $ CopasiUI/CopasiDefaultWidget.cpp                 
 **  $ Author  : Mudita Singhal
 **
 ** This file is used to create the GUI FrontPage for the  information 
 ** obtained from the data model about the Moiety----It is 
 ** the Second level of Moieties.
 ********************************************************************/
#include <qlabel.h> 
//#include <qlistbox.h>
//#include <qlineedit.h>
//#include <qpushbutton.h>
#include <qlayout.h> 
//#include <qtoolbar.h>
#include <qwidget.h> 
//#include <qframe.h>

#include "copasi.h" 
//#include "utilities/CCopasiVector.h"
#include "CopasiDefaultWidget.h" 
//#include "model/CModel.h"
//#include "model/CMoiety.h"
//#include "listviews.h"
//#include "DataModelGUI.h"
#include "qtUtilities.h" 
//#include "report/CKeyFactory.h"

/*
 *  Constructs a MoietyWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 *
 */

CopasiDefaultWidget::CopasiDefaultWidget(QWidget *parent, const char * name, WFlags f)
    : CopasiWidget(parent, name, f)

{
  if (!name)
    setName("CopasiDefaultWidget");
  //setCaption("CopasiDefaultWidget");
  CopasiDefaultWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "CopasiDefaultWidgetLayout");

  TextLabel1 = new QLabel(this, "TextLabel1");
  TextLabel1->setText("empty");

  CopasiDefaultWidgetLayout->addWidget(TextLabel1, 2, 0);

  // signals and slots connections
}

CopasiDefaultWidget::~CopasiDefaultWidget()
{}

bool CopasiDefaultWidget::update(ListViews::ObjectType objectType,
                                 ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  return true;
}

bool CopasiDefaultWidget::leave()
{
  return true;
}

bool CopasiDefaultWidget::enter(const std::string & key)
{
  return true;
}
