/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/AboutDialog.cpp,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2005/04/15 15:16:47 $
   End CVS Header */

#include "AboutDialog.h"

#include "qpushbutton.h"
#include "qpixmap.h"
#include "qtextedit.h"
#include "qlayout.h"
#include "qsizepolicy.h"
#include "copasi.h"
#include "icons/copasi_beta_background.xpm"

const char* AboutDialog::text =
  "COPASI is a simulator for biochemical networks. It is a joint project "
  "by the Mendes and Kummer groups at VBI and EML Research, "
  "respectively.\n"
  "\n"
  "This version of COPASI is a test version. Most likely a new one has "
  "already been released and you should download it from "
  "www.copasi.org.\n"
  "\n"
  "Please report errors to bugs@copasi.org.\n"
  "\n"
  "\n"
  "\n"
  "COPASI is provided \"AS IS\" without warranty of any kind, either "
  "express or implied, including but not limited to the implied "
  "warranties of merchantability and fitness for a particular purpose. In "
  "no event shall the Authors be liable for any damages whatsoever "
  "including direct, indirect, incidental, consequential, loss of "
  "business profits or special damages, even if the Authors have been "
  "advised of the possibility of such damages.\n"
  "\n"
  "The following software and algorithms are being used by Copasi:\n"
  "\n"
  "- Qt3 GUI framework\n"
  "- QWT 4.2.0 plotting framework\n"
  "- Expat 1.95.7 XML parser\n"
  "- libsbml 2.2.0\n"
  "- CLAPACK 3.0 or LAPACK 3.0\n"
  "- LSODA from ODEPACK\n"
  "- Mersenne Twister random number generator,\n"
  "   Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura"
;

AboutDialog::AboutDialog(QWidget* parent): QDialog(parent), closeButton(NULL), textEdit(NULL), backgroundPixmap(NULL), mainLayout(NULL)
{
  WFlags f = this->getWFlags();
  f = (f | Qt::WStyle_Minimize | Qt::WDestructiveClose);
  this->setWFlags(f);
  this->setModal(true);
  this->mainLayout = new QVBoxLayout(this);
  this->mainLayout->setResizeMode(QLayout::Fixed);
  this->mainLayout->setAutoAdd(false);
  this->backgroundPixmap = new QPixmap((const char**)copasi_beta_background_xpm);
  this->textEdit = new QTextEdit(this);
  this->textEdit->setPaletteBackgroundPixmap(*this->backgroundPixmap);
  this->textEdit->setFixedSize(360, 384);
  this->textEdit->setReadOnly(true);
  this->textEdit->setText(AboutDialog::text);
  this->closeButton = new QPushButton(this);
  this->closeButton->setText("close");
  this->mainLayout->addWidget(this->textEdit);
  this->mainLayout->addWidget(this->closeButton);

  connect(this->closeButton, SIGNAL(clicked()), this, SLOT(closeButton_clicked()));
}

AboutDialog::~AboutDialog()
{
  pdelete(this->textEdit);
  pdelete(this->closeButton);
  pdelete(this->backgroundPixmap);
  pdelete(this->mainLayout);
}

void AboutDialog::closeButton_clicked()
{
  close();
}
