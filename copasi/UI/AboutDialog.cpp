// Copyright (C) 2019 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
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

#include <QPushButton>
#include <QPixmap>
#include <QTextEdit>
#include <QLayout>
#include <QSizePolicy>
#include <QVBoxLayout>
#include <QBrush>
#include <QDialogButtonBox>
#include <QApplication>

#include "icons/copasi_beta_background.xpm"

#include "copasi/copasi.h"
#include "copasi/config.h"
#include <copasi/UI/qtUtilities.h>
#include <copasi/math/CJitCompiler.h>
#include <copasi/utilities/CVersion.h>
#include "copasi/OpenMP/CContext.h"

#ifdef QWT_VERSION
#include <qwt_global.h>
#endif

const char *AboutDialog::text =
  "<h2>COPASI %1</h2>"
  "<p>"
  "COPASI is a simulator for biochemical networks. It is a joint project "
  "by the Hoops group (Biocomplexity Institute of Virginia Tech), the "
  "Mendes group (UCONN School of Medicine), the Kummer, and Sahle groups "
  "(University of Heidelberg)."
  "</p><p>"
  "Please check for new release at http://www.copasi.org, where new releases "
  "will be made available for download."
  "</p><p>"
  "Should you have any questions regarding the use of COPASI please visit our "
  "user support at http://www.copasi.org/UserSupportForum."
  "</p><p>If you find any errors or problem you may email us at bugs@copasi.org or "
  "use our issue tracker at http://tracker..copasi.org."
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
  "<li>Qt %2 GUI framework</li>"
  "<li>Qwt %3</li>"
  "<li>QwtPlot3D 0.2.7</li>"
  "<li>Expat %4 XML parser</li>"
  "<li>libSBML %5</li>"
  "<li>libSEDML %6</li>"
  "<li>libCombine %7</li>"
  "<li>raptor %8</li>"
  "<li>Systems Biology Workbench %9</li>"
  "<li>CLAPACK 3.0, LAPACK 3.1.0, or Intel Math Kernel Library</li>"
  "<li>LSODA and LSODAR from ODEPACK</li>"
  "<li>Mersenne Twister random number generator, "
  "    Copyright (C) 1997 - 2002, Makoto Matsumoto and Takuji Nishimura</li>"
  "<li>NativeJIT just in time compiler (%10)</li>"
  "<li>cpu_features to determine JIT support</li>"
  "</ul>"
  "</p>"
  ;

QString AboutDialog::getDefaultVersionText()
{
  return QString(AboutDialog::text)
         .arg(FROM_UTF8(CVersion::VERSION.getVersion() + omp_info()()))            // 1
         .arg(QT_VERSION_STR)                                       // 2
         .arg(QWT_VERSION_STR)                                      // 3
         .arg(COPASI_EXPAT_VERSION)                                 // 4
         .arg(COPASI_LIBSBML_VERSION)                               // 5
         .arg(COPASI_LIBSEDML_VERSION)                              // 6
         .arg(COPASI_LIBCOMBINE_VERSION)                            // 7
         .arg(COPASI_RAPTOR_VERSION)                                // 8
         .arg(COPASI_SBW_VERSION)                                   // 9
         .arg(CJitCompiler::JitEnabled() ? "enabled" : "disabled"); //10
}

AboutDialog::AboutDialog(QWidget *parent,
                         const QString &text,
                         const int &width,
                         const int &height):
  QDialog(parent),
  textEdit(NULL),
  mainLayout(NULL)
{
#if QT_VERSION >= QT_VERSION_CHECK(5,0,0)
  QPalette Palette = QGuiApplication::palette();
#else
  QPalette Palette = QApplication::palette();
#endif
  QColor Foreground = Palette.color(QPalette::Active, QPalette::Text);
  QColor Background = Palette.color(QPalette::Active, QPalette::Base);

  bool isDarkTheme = (Foreground.redF() + Foreground.greenF() + Foreground.blueF() > Background.redF() + Background.greenF() + Background.blueF());

  this->setModal(true);
  this->mainLayout = new QVBoxLayout(this);
  this->mainLayout->setSizeConstraint(QLayout::SetFixedSize);
  this->textEdit = new QTextEdit(this);

  Palette.setBrush(QPalette::Base, QBrush(QPixmap((const char **)copasi_beta_background_xpm)));

  if (isDarkTheme)
    Palette.setColor(QPalette::Text, Background);

  textEdit->setPalette(Palette);

  QFontMetrics FontMetrics = this->fontMetrics();
#if QT_VERSION >= QT_VERSION_CHECK(5,11,0)
  int w = width * (FontMetrics.horizontalAdvance('W') + FontMetrics.horizontalAdvance('I')) / 2;
#else
  int w = width * (FontMetrics.width('W') + FontMetrics.width('I')) / 2;
#endif

  int h = height * FontMetrics.lineSpacing();
  this->textEdit->setFixedSize(w, h);
  this->textEdit->setReadOnly(true);
  this->textEdit->setText(text);
  //  this->textEdit->setText(QString(text).arg();
  this->mainLayout->addWidget(this->textEdit);
  QDialogButtonBox *box = new QDialogButtonBox(QDialogButtonBox::Close, Qt::Horizontal, this);
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
