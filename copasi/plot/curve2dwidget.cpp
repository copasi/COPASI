/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/plot/Attic/curve2dwidget.cpp,v $
   $Revision: 1.3 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2004/08/05 12:54:13 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'curve2dwidget.ui'
 **
 ** Created: Wed Aug 4 15:18:58 2004
 **      by: The User Interface Compiler ($Id: curve2dwidget.cpp,v 1.3 2004/08/05 12:54:13 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "curve2dwidget.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qcombobox.h>
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

  line = new QFrame(this, "line");
  line->setFrameShape(QFrame::HLine);
  line->setFrameShadow(QFrame::Sunken);
  line->setFrameShape(QFrame::HLine);

  Curve2DWidgetLayout->addMultiCellWidget(line, 1, 1, 0, 2);

  textLabelTitle = new QLabel(this, "textLabelTitle");

  Curve2DWidgetLayout->addWidget(textLabelTitle, 0, 0);

  lineEditTitle = new QLineEdit(this, "lineEditTitle");

  Curve2DWidgetLayout->addMultiCellWidget(lineEditTitle, 0, 0, 1, 2);

  lineEditXName = new QLineEdit(this, "lineEditXName");

  Curve2DWidgetLayout->addMultiCellWidget(lineEditXName, 2, 2, 1, 2);

  lineEditXCN = new QLineEdit(this, "lineEditXCN");

  Curve2DWidgetLayout->addMultiCellWidget(lineEditXCN, 3, 3, 1, 2);

  lineEditYName = new QLineEdit(this, "lineEditYName");

  Curve2DWidgetLayout->addMultiCellWidget(lineEditYName, 5, 5, 1, 2);

  lineEditYCN = new QLineEdit(this, "lineEditYCN");

  Curve2DWidgetLayout->addMultiCellWidget(lineEditYCN, 6, 6, 1, 2);

  textLabelX = new QLabel(this, "textLabelX");
  textLabelX->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)5, 0, 0, textLabelX->sizePolicy().hasHeightForWidth()));

  Curve2DWidgetLayout->addWidget(textLabelX, 2, 0);

  textLabelY = new QLabel(this, "textLabelY");

  Curve2DWidgetLayout->addWidget(textLabelY, 5, 0);

  comboXAxis = new QComboBox(FALSE, this, "comboXAxis");
  comboXAxis->setSizePolicy(QSizePolicy((QSizePolicy::SizeType)0, (QSizePolicy::SizeType)0, 0, 0, comboXAxis->sizePolicy().hasHeightForWidth()));

  Curve2DWidgetLayout->addWidget(comboXAxis, 4, 1);
  QSpacerItem* spacer = new QSpacerItem(20, 21, QSizePolicy::Minimum, QSizePolicy::Expanding);
  Curve2DWidgetLayout->addItem(spacer, 8, 2);

  comboYAxis = new QComboBox(FALSE, this, "comboYAxis");

  Curve2DWidgetLayout->addWidget(comboYAxis, 7, 1);
  languageChange();
  resize(QSize(655, 380).expandedTo(minimumSizeHint()));
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
  textLabelX->setText(tr("X-Axis"));
  textLabelY->setText(tr("Y-Axis"));
  comboXAxis->clear();
  comboXAxis->insertItem(tr("Top"));
  comboXAxis->insertItem(tr("Bottom"));
  comboXAxis->setCurrentItem(1);
  comboYAxis->clear();
  comboYAxis->insertItem(tr("Left"));
  comboYAxis->insertItem(tr("Right"));
}
