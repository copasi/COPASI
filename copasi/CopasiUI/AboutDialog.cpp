/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/AboutDialog.cpp,v $
   $Revision: 1.9 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/06/20 13:18:05 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "AboutDialog.h"

#include "qpushbutton.h"
#include "qpixmap.h"
#include "qtextedit.h"
#include "qlayout.h"
#include "qsizepolicy.h"
#include "copasi.h"
#include "icons/copasi_beta_background.xpm"

const char* AboutDialog::text =
  "COPASI is a simulator for biochemical networks. It is a joint project\n"
  "by the Mendes and Kummer groups at VBI and EML Research, respectively.\n"
  "\n"
  "This is COPASI version 4.0 (Build 18). Please check for\n"
  "new release at http://www.copasi.org where new releases will be made\n"
  "available for download.\n"
  "\n"
  "Please report errors to bugs@copasi.org.\n"
  "\n"
  "COPASI is provided \"AS IS\" without warranty of any kind, either\n"
  "express or implied, including but not limited to the implied\n"
  "warranties of merchantability and fitness for a particular purpose. In\n"
  "no event shall the Authors be liable for any damages whatsoever\n"
  "including direct, indirect, incidental, consequential, loss of\n"
  "business profits or special damages, even if the Authors have been\n"
  "advised of the possibility of such damages.\n"
  "\n"
  "The following software and algorithms are being used by Copasi:\n"
  "  - Qt3 GUI framework\n"
  "  - QWT 5.0 Beta (Snapshot 2006-01-25)\n"
  "  - Expat 1.95.7 XML parser\n"
  "  - libsbml 2.3.2\n"
  "  - CLAPACK 3.0, LAPACK 3.0, or Intel Math Kernel Library\n"
  "  - LSODA from ODEPACK\n"
  "  - Mersenne Twister random number generator,\n"
  "    Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura\n"
;

AboutDialog::AboutDialog(QWidget* parent,
                         const char * text,
                         const int & width,
                         const int & heigth):
    QDialog(parent),
    closeButton(NULL),
    textEdit(NULL),
    backgroundPixmap(NULL),
    mainLayout(NULL)
{
  WFlags f = this->getWFlags();
  f = (f | Qt::WDestructiveClose);
  this->setWFlags(f);
  this->setModal(true);
  this->mainLayout = new QVBoxLayout(this);
  this->mainLayout->setResizeMode(QLayout::Fixed);
  this->mainLayout->setAutoAdd(false);
  this->backgroundPixmap = new QPixmap((const char**)copasi_beta_background_xpm);
  this->textEdit = new QTextEdit(this);
  this->textEdit->setPaletteBackgroundPixmap(*this->backgroundPixmap);
  QFontMetrics FontMetrics = this->fontMetrics();
  int w = width * (FontMetrics.width('W') + FontMetrics.width('I')) / 2;
  int h = heigth * FontMetrics.lineSpacing();
  this->textEdit->setFixedSize(w, h);
  this->textEdit->setReadOnly(true);
  this->textEdit->setText(text);
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
