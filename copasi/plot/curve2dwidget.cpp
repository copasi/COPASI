/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/curve2dwidget.cpp,v $
   $Revision: 1.2 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/05/06 20:03:18 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'curve2dwidget.ui'
 **
 ** Created: Wed May 5 20:22:59 2004
 **      by: The User Interface Compiler ($Id: curve2dwidget.cpp,v 1.2 2004/05/06 20:03:18 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "curve2dwidget.h"

#include <qvariant.h>
#include <qpushbutton.h>
#include <qlabel.h>
#include <qframe.h>
#include <qcombobox.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "curve2dwidget.ui.h"

/*
 *  Constructs a Curve2DWidget as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
Curve2DWidget::Curve2DWidget(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("Curve2DWidget");
  Curve2DWidgetLayout = new QGridLayout(this, 1, 1, 11, 6, "Curve2DWidgetLayout");

  layout1 = new QGridLayout(0, 1, 1, 0, 6, "layout1");

  textLabelTitle = new QLabel(this, "textLabelTitle");

  layout1->addWidget(textLabelTitle, 0, 0);

  line = new QFrame(this, "line");
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  line->setFrameShape(QFrame::HLine);

  layout1->addMultiCellWidget(line, 1, 1, 0, 2);

  comboXAxis = new QComboBox(FALSE, this, "comboXAxis");
  comboXAxis->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, comboXAxis->sizePolicy().hasHeightForWidth()));

  layout1->addWidget(comboXAxis, 2, 2);

  comboXData = new QComboBox(FALSE, this, "comboXData");
  comboXData->setMinimumSize(QSize(200, 0));
  comboXData->setEditable(TRUE);

  layout1->addWidget(comboXData, 2, 1);

  textLabelX = new QLabel(this, "textLabelX");
  textLabelX->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, textLabelX->sizePolicy().hasHeightForWidth()));

  layout1->addWidget(textLabelX, 2, 0);

  lineEditTitle = new QLineEdit(this, "lineEditTitle");

  layout1->addMultiCellWidget(lineEditTitle, 0, 0, 1, 2);

  comboYData = new QComboBox(FALSE, this, "comboYData");
  comboYData->setEditable(TRUE);

  layout1->addWidget(comboYData, 3, 1);

  comboYAxis = new QComboBox(FALSE, this, "comboYAxis");

  layout1->addWidget(comboYAxis, 3, 2);

  textLabelY = new QLabel(this, "textLabelY");

  layout1->addWidget(textLabelY, 3, 0);

  Curve2DWidgetLayout->addLayout(layout1, 0, 0);
  languageChange();
  resize(QSize(540, 407).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
}

/*
 *  Destroys the object and frees any allocated resources
 */
Curve2DWidget::~Curve2DWidget()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void Curve2DWidget::languageChange()
{
  setCaption(tr("Form2"));
  textLabelTitle->setText(tr("Title"));
  comboXAxis->clear();
  comboXAxis->insertItem(tr("Top"));
  comboXAxis->insertItem(tr("Bottom"));
  comboXAxis->setCurrentItem(1);
  textLabelX->setText(tr("X-Axis"));
  comboYAxis->clear();
  comboYAxis->insertItem(tr("Left"));
  comboYAxis->insertItem(tr("Right"));
  textLabelY->setText(tr("Y-Axis"));
}
