/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/ObjectBrowserDialog.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: jpahle $ 
   $Date: 2004/10/06 16:29:20 $
   End CVS Header */

#include <qlayout.h>
#include "ObjectBrowserWidget.h"

#include "copasi.h"
#include "ObjectBrowserDialog.h"
#include "copasiui3window.h"
#include "report/CCopasiObject.h"

/*
 *  Constructs a ObjectBrowserDialog which is a child of 'parent', with the 
 *  name 'name' and widget flags set to 'f'.
 */
ObjectBrowserDialog::ObjectBrowserDialog(QWidget* parent, const char* name, WFlags fl)
    : QDialog(NULL, name, parent == NULL, fl)
{
  if (!name)
    setName("ObjectBrowser");
  resize(420, 460);
  setCaption(trUtf8("Object Browser"));
  ObjectBrowserDialogLayout = new QGridLayout(this, 1, 1, 0, -1, "ObjectBrowserDialogLayout");

  objectBrowserWidget = new ObjectBrowserWidget(this, name, fl);
  ObjectBrowserDialogLayout->addWidget(objectBrowserWidget, 0, 0);

  connect(objectBrowserWidget, SIGNAL(commitClicked(int)), this, SLOT(nextClicked(int)));

  mparent = (CopasiUI3Window*)parent;
  if (mparent)
    mparent->disable_object_browser_menu();
}

/*
 *  Destroys the object and frees any allocated resources
 */
void ObjectBrowserDialog::closeEvent (QCloseEvent * e)
{
  QWidget::closeEvent(e);
  if (mparent)
    {
      //if not a model dialog, it shall incur this function, when close
      // it shall enable the browser menu
      mparent->enable_object_browser_menu();
      mparent = NULL;
      cleanup();
    }
}

ObjectBrowserDialog::~ObjectBrowserDialog()
{
  cleanup();
}

void ObjectBrowserDialog::cleanup()
{
  if (objectBrowserWidget) objectBrowserWidget->cleanup();
}

void ObjectBrowserDialog::setOutputVector(std::vector<CCopasiObject*>* pObjectVector)
{
  if (objectBrowserWidget) objectBrowserWidget->setOutputVector(pObjectVector);
}

void ObjectBrowserDialog::nextClicked(int)
{
  if (!mparent)
    {
      QDialog::done(QDialog::Accepted);
      return;
    }
}
