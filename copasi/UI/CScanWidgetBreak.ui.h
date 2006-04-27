/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/UI/Attic/CScanWidgetBreak.ui.h,v $
   $Revision: 1.5 $
   $Name:  $
   $Author: shoops $
   $Date: 2006/04/27 01:27:42 $
   End CVS Header */

// Copyright © 2005 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include <qvalidator.h>

#include "copasi.h"

#include "qtUtilities.h"

#include "CCopasiSelectionDialog.h"

#include "utilities/CCopasiParameterGroup.h"
#include "scan/CScanProblem.h"

void CScanWidgetBreak::init()
{}

//comboBoxReport  line|page|file|no
//comboBoxPlot   curve|window|no

#include "report/CCopasiObjectName.h"
bool CScanWidgetBreak::initFromScanItem(CCopasiParameterGroup * pg)
{
  unsigned C_INT32 * tmp;

  if (!(tmp = pg->getValue("Type").pUINT)) return false;
  if (* (CScanProblem::Type *) tmp != CScanProblem::SCAN_BREAK)
    return false;

  if (!(tmp = pg->getValue("Report break").pUINT)) return false;
  comboBoxReport->setCurrentItem(*tmp);

  if (!(tmp = pg->getValue("Plot break").pUINT)) return false;
  comboBoxPlot->setCurrentItem(*tmp);

  return true;
}

bool CScanWidgetBreak::saveToScanItem(CScanProblem * pg) const
  {
    CScanProblem::Type type = CScanProblem::SCAN_BREAK;

    unsigned C_INT32 steps = 1;

    CCopasiParameterGroup* tmp = pg->createScanItem(type, steps);
    assert(tmp);

    tmp->setValue("Report break", (unsigned C_INT32)comboBoxReport->currentItem());
    tmp->setValue("Plot break", (unsigned C_INT32)comboBoxPlot->currentItem());

    return true;
  }
