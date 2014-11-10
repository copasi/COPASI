// Copyright (C) 2010 - 2014 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2005 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <QtGui/QValidator>

#include "copasi.h"

#include "CScanWidgetRepeat.h"
#include "qtUtilities.h"
#include "CCopasiSelectionDialog.h"

#include "report/CCopasiObjectName.h"

/*
 *  Constructs a CScanWidgetRepeat as a child of 'parent', with the
 *  name 'name' and widget flags set to 'f'.
 */
CScanWidgetRepeat::CScanWidgetRepeat(QWidget* parent) :
  QWidget(parent),
  CScanItemData(CScanProblem::SCAN_REPEAT)
{
  setupUi(this);
  init();
}

CScanWidgetRepeat::CScanWidgetRepeat(const CScanWidgetRepeat & src, QWidget * parent) :
  QWidget(parent),
  CScanItemData(src)
{
  setupUi(this);
  init();
  load(mpData);
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

// virtual
void CScanWidgetRepeat::load(const CCopasiParameterGroup * pItem)
{
  if (pItem == NULL) return;

  *mpData = *pItem;

  C_INT32 * tmp;

  if (!(tmp = mpData->getValue("Type").pINT))
    return;

  if (*(CScanProblem::Type *) tmp != CScanProblem::SCAN_REPEAT)
    return;

  if (!(tmp = mpData->getValue("Number of steps").pINT))
    return;

  lineEditNumber->setText(QString::number(* tmp));

  return;
}

// virtual
bool CScanWidgetRepeat::save(CCopasiParameterGroup * pItem) const
{
  mpData->setValue("Number of steps", lineEditNumber->text().toUInt());

  if (pItem != NULL)
    {
      if (*mpData == *pItem) return false;

      *pItem = *mpData;
      return true;
    }

  return false;
}
