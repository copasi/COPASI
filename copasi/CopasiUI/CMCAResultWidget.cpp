/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CMCAResultWidget.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/28 07:47:21 $
   End CVS Header */

#include <qlayout.h>
#include "copasi.h"

#include "CMCAResultWidget.h"
#include "CMCAResultSubwidget.h"
#include "DataModelGUI.h"
#include "steadystate/CMCATask.h"
#include "steadystate/CMCAMethod.h"
#include "qtUtilities.h"

/*
 *  Constructs a CMCAResultWidget which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
CMCAResultWidget::CMCAResultWidget(QWidget* parent, const char* name, WFlags fl)
    : CopasiWidget(parent, name, fl),
    objKey("")
{
  if (!name)
    setName("CMCAResultWidget");
  setCaption(trUtf8("CMCAResultWidget"));

  mWidgetLayout = new QGridLayout(this, 1, 1, 0, -1, "Layout");

  mCentralWidget = new CMCAResultSubwidget(this, "CMCAResultSubwidget");
  mWidgetLayout->addWidget(mCentralWidget, 0, 0);
}

/*
 *  Destroys the object and frees any allocated resources
 */
CMCAResultWidget::~CMCAResultWidget()
{}

/* This function loads the compartments widget when its name is
  clicked in the tree   */
bool CMCAResultWidget::loadFromBackend()
{
  mCentralWidget->loadAll(dynamic_cast<CMCAMethod*>(dataModel->getMCATask()->getMethod()));
  return true;
}

bool CMCAResultWidget::saveToBackend()
{
  return true;
}

bool CMCAResultWidget::update(ListViews::ObjectType C_UNUSED(objectType), ListViews::Action C_UNUSED(action), const std::string & C_UNUSED(key))
{
  return true;
}

bool CMCAResultWidget::leave()
{
  return true;
}

bool CMCAResultWidget::enter(const std::string & C_UNUSED(key))
{
  return loadFromBackend();
}
