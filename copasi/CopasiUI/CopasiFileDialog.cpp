/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CopasiFileDialog.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/08/22 14:07:14 $
   End CVS Header */

#include <qapplication.h>
#include <qlayout.h>
#include <qbuttongroup.h>
#include <qpixmap.h>
#include <qimage.h>

#include "copasi.h"

#include "commandline/COptions.h"
#include "CopasiFileDialog.h"
#include "qtUtilities.h"

void CopasiFileDialog::addLocation(QWidget* w)
{
  addLeftWidget(w);
}

CopasiFileDialog::CopasiFileDialog(QWidget * parent , const char * name , bool modal)
    : QFileDialog(parent , name , modal)
{
  const width = 30, length = 30;

  QButtonGroup * grp = new QButtonGroup(this);

  exampleDirButton = new QPushButton("Examples directory", grp, "exampleDirButton");
  QImage exampleDirImage;
  exampleDirImage.load("./icons/examples.bmp");
  QPixmap * exampleDirPixmap = new QPixmap(exampleDirImage.scale(width, length));
  exampleDirButton->setPixmap(*exampleDirPixmap);

  homeDirButton = new QPushButton("home directory", grp, "homeDirButton");
  QImage homeDirImage;
  homeDirImage.load("./icons/home.bmp");
  QPixmap * homeDirPixmap = new QPixmap(homeDirImage.scale(width, length));
  homeDirButton->setPixmap(*homeDirPixmap);

  copasiDirButton = new QPushButton("copasi directory", grp, "copasiDirButton");
  QImage copasiDirImage;
  copasiDirImage.load("./icons/copasi_icon_small.png");
  QPixmap * copasiDirPixmap = new QPixmap(copasiDirImage.scale(width, length));
  copasiDirButton->setPixmap(*copasiDirPixmap);

  QVBoxLayout *layout = new QVBoxLayout(grp);

  QSpacerItem * spacer = new QSpacerItem(width, 50);

  layout->setMargin(2);

  layout->addWidget(exampleDirButton);
  layout->addWidget(homeDirButton);
  layout->addWidget(copasiDirButton);
  layout->addItem(spacer);

  addLocation(grp);

  connect(exampleDirButton, SIGNAL(pressed()), this, SLOT(slotExampleDir()));
  connect(homeDirButton, SIGNAL(pressed()), this, SLOT(slotHomeDir()));
  connect(copasiDirButton, SIGNAL(pressed()), this, SLOT(slotCopasiDir()));
}

void CopasiFileDialog::slotExampleDir()
{
  std::string ExampleDir;
  COptions::getValue("ExampleDir", ExampleDir);
  setDir(FROM_UTF8(ExampleDir));
}

void CopasiFileDialog::slotHomeDir()
{
  std::string HomeDir;
  COptions::getValue("Home", HomeDir);
  setDir(FROM_UTF8(HomeDir));
}

void CopasiFileDialog::slotCopasiDir()
{
  std::string CopasiDir;
  COptions::getValue("CopasiDir", CopasiDir);
  setDir(FROM_UTF8(CopasiDir));
}
