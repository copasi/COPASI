/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CScanWidgetRepeat.cpp,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/27 20:27:39 $
   End CVS Header */

/****************************************************************************
 ** Form implementation generated from reading ui file 'CScanWidgetRepeat.ui'
 **
 ** Created: Do Feb 24 23:25:19 2005
 **      by: The User Interface Compiler ($Id: CScanWidgetRepeat.cpp,v 1.1 2005/02/27 20:27:39 ssahle Exp $)
 **
 ** WARNING! All changes made in this file will be lost!
 ****************************************************************************/

#include "CScanWidgetRepeat.h"

#include <qvariant.h>
#include <qframe.h>
#include <qlabel.h>
#include <qlineedit.h>
#include <qlayout.h>
#include <qtooltip.h>
#include <qwhatsthis.h>
#include "CScanWidgetRepeat.ui.h"

/*
 *  Constructs a CScanWidgetRepeat as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetRepeat::CScanWidgetRepeat(QWidget* parent, const char* name, WFlags fl)
    : QWidget(parent, name, fl)
{
  if (!name)
    setName("CScanWidgetRepeat");
  CScanWidgetRepeatLayout = new QVBoxLayout(this, 5, 6, "CScanWidgetRepeatLayout");

  frame = new QFrame(this, "frame");
  frame->setPaletteBackgroundColor(QColor(207, 206, 249));
  frame->setFrameShape(QFrame::StyledPanel);
  frame->setFrameShadow(QFrame::Raised);
  frameLayout = new QHBoxLayout(frame, 6, 6, "frameLayout");

  labelTitle = new QLabel(frame, "labelTitle");
  labelTitle->setAlignment(int(QLabel::WordBreak | QLabel::AlignVCenter));
  frameLayout->addWidget(labelTitle);
  spacer1 = new QSpacerItem(20, 16, QSizePolicy::Maximum, QSizePolicy::Minimum);
  frameLayout->addItem(spacer1);

  labelNumber = new QLabel(frame, "labelNumber");
  frameLayout->addWidget(labelNumber);

  lineEditNumber = new QLineEdit(frame, "lineEditNumber");
  frameLayout->addWidget(lineEditNumber);
  CScanWidgetRepeatLayout->addWidget(frame);
  languageChange();
  resize(QSize(446, 54).expandedTo(minimumSizeHint()));
  clearWState(WState_Polished);
  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetRepeat::~CScanWidgetRepeat()
{
  // no need to delete child widgets, Qt does it all for us
}

/*
 *  Sets the strings of the subwidgets using the current
 *  language.
 */
void CScanWidgetRepeat::languageChange()
{
  setCaption(tr("Form1"));
  labelTitle->setText(tr("<h2>Repeat</h2>"));
  labelNumber->setText(tr("Number of iterations"));
}
