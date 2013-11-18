// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2004 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

/*!
    \file AboutDialog.cpp
    \brief Implementation file of class AboutDialog
 */

#include "AboutDialog.h"

#include <QtGui/QPushButton>
#include <QtGui/QPixmap>
#include <QtGui/QTextEdit>
#include <QtGui/QLayout>
#include <QtGui/QSizePolicy>
#include <QtGui/QVBoxLayout>
#include <QtGui/QBrush>
#include <QtGui/QDialogButtonBox>

#include "icons/copasi_beta_background.xpm"

#include "copasi.h"

const char* AboutDialog::text =
  "<h2>COPASI %1</h2>"
  "<p>"
  "COPASI is a simulator for biochemical networks. It is a joint project "
  "by the Mendes group (VBI and University of Manchester) and the Kummer group "
  "(University of Heidelberg)"
  "</p><p>"
  "Please check for new release at http://www.copasi.org, where new releases "
  "will be made available for download."
  "</p><p>"
  "Should you have any questions regarding the use of COPASI please visit our "
  "user support at http://www.copasi.org/UserSupportForum."
  "</p><p>If you find any errors or problem you may email us at bugs@copasi.org or "
  "use our issue tracker at http://www.copasi.org/tracker."
  "</p><p>"
  "COPASI is provided \"AS IS\" without warranty of any kind, either "
  "expressed or implied, including but not limited to the implied "
  "warranties of merchantability and fitness for a particular purpose. In "
  "no event shall the Authors be liable for any damages whatsoever "
  "including direct, indirect, incidental, consequential, loss of "
  "business profits or special damages, even if the Authors have been "
  "advised of the possibility of such damages."
  "</p><p>"
  "The following software and algorithms are being used by COPASI: "
  "<ul>"
  "<li>Qt 4 GUI framework</li>"
  "<li>Qwt 5.2.0</li>"
  "<li>QwtPlot3D 0.2.7</li>"
  "<li>Expat 2.0.1 XML parser</li>"
  "<li>libSBML %2</li>"
  "<li>raptor 1.4.21</li>"
  "<li>Systems Biology Workbench 2.7.10</li>"
  "<li>CLAPACK 3.0, LAPACK 3.1.0, or Intel Math Kernel Library</li>"
  "<li>LSODA and LSODAR from ODEPACK</li>"
  "<li>Mersenne Twister random number generator, "
  "    Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura</li>"
  "</ul>"
  "</p>"
  ;

AboutDialog::AboutDialog(QWidget* parent,
                         const QString & text,
                         const int & width,
                         const int & heigth):
  QDialog(parent),
  textEdit(NULL),
  mainLayout(NULL)
{
  this->setModal(true);
  this->mainLayout = new QVBoxLayout(this);
  this->mainLayout->setSizeConstraint(QLayout::SetFixedSize);
  this->textEdit = new QTextEdit(this);

  QPalette Palette;
  Palette.setBrush(QPalette::Base, QBrush(QPixmap((const char**)copasi_beta_background_xpm)));

  textEdit->setPalette(Palette);

  QFontMetrics FontMetrics = this->fontMetrics();
  int w = width * (FontMetrics.width('W') + FontMetrics.width('I')) / 2;
  int h = heigth * FontMetrics.lineSpacing();
  this->textEdit->setFixedSize(w, h);
  this->textEdit->setReadOnly(true);
  this->textEdit->setText(text);
  //  this->textEdit->setText(QString(text).arg();
  this->mainLayout->addWidget(this->textEdit);
  QDialogButtonBox* box = new QDialogButtonBox(QDialogButtonBox::Close, Qt::Horizontal, this);
  this->mainLayout->addWidget(box);

  connect(box, SIGNAL(rejected()), this, SLOT(closeButton_clicked()));
}

AboutDialog::~AboutDialog()
{
  pdelete(this->textEdit);
  pdelete(this->mainLayout);
}

void AboutDialog::closeButton_clicked()
{
  close();
}
