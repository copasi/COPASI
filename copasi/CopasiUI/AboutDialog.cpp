/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/AboutDialog.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: gauges $ 
   $Date: 2004/10/19 07:14:49 $
   End CVS Header */

#include "AboutDialog.h"

#include "qpushbutton.h"
#include "qpixmap.h"
#include "qtextedit.h"
#include "qlayout.h"
#include "qsizepolicy.h"
#include "copasi.h"
#include "icons/copasi_beta_background.xpm"

const char* AboutDialog::text = "COPASI is a simulator for biochemical networks. It is a joint project by the Mendes and Kummer groups at VBI and EML Research, respectively.\n\nThis version of COPASI is a test version. Most likely a new one has already been released and you should download it from www.copasi.org.\nPlease report errors to sahle@eml.org .\n\n\n\nCOPASI is provided \"AS IS\" without warranty of any kind, either express or implied, including but not limited to the implied warranties of merchantability and fitness for a particular purpose. In no event shall the Authors be liable for any damages whatsoever including direct, indirect, incidental, consequential, loss of business profits or special damages, even if the Authors have been advised of the possibility of such damages.\n\nThe following software and algorithms are being used by Copasi:\n\n- Qt3 GUI framework\n- QWT 4.2rc2 plotting framework\n- libsbml 2.2.0\n- CLAPACK\n- LSODA from ODEPACK";

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
