// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/CScanWidgetRepeat.cpp,v $
//   $Revision: 1.8 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:39:37 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#include "copasi.h"

#include "CScanWidgetRepeat.h"

//#include <QtCore/QVariant>
//#include "CScanWidgetRepeat.ui.h"

#include <qvalidator.h>

#include "UI/qtUtilities.h"
#include "UI/CCopasiSelectionDialog.h"

/*
 *  Constructs a CScanWidgetRepeat as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetRepeat::CScanWidgetRepeat(QWidget* parent, const char* name, Qt::WindowFlags fl)
    : QWidget(parent, fl)
{
  setObjectName(QString::fromUtf8(name));
  setupUi(this);

  init();
}

/*
 *  Destroys the object and frees any allocated resources
 */
CScanWidgetRepeat::~CScanWidgetRepeat()
{
  // no need to delete child widgets, Qt does it all for us
}

void CScanWidgetRepeat::init()
{
  lineEditNumber->setValidator(new QIntValidator(lineEditNumber));
}

#include "report/CCopasiObjectName.h"
bool CScanWidgetRepeat::initFromScanItem(CCopasiParameterGroup * pg)
{
  C_INT32 * tmp;

  if (!(tmp = pg->getValue("Type").pINT)) return false;

  if (*(CScanProblem::Type *) tmp != CScanProblem::SCAN_REPEAT)
    return false;

  if (!(tmp = pg->getValue("Number of steps").pINT)) return false;

  lineEditNumber->setText(QString::number(* tmp));

  return true;
}

bool CScanWidgetRepeat::saveToScanItem(CScanProblem * pg) const
{
  CScanProblem::Type type = CScanProblem::SCAN_REPEAT;

  unsigned C_INT32 steps = lineEditNumber->text().toUInt();

  CCopasiParameterGroup* tmp = pg->createScanItem(type, steps);
  assert(tmp);

  return true;
}
