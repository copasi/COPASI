/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CScanWidgetRepeat.ui.h,v $
   $Revision: 1.4 $
   $Name:  $
   $Author: shoops $ 
   $Date: 2006/03/28 23:09:05 $
   End CVS Header */

#include <qvalidator.h>
#include "copasi.h"

#include "qtUtilities.h"
#include "CCopasiSelectionDialog.h"

#include "utilities/CCopasiParameterGroup.h"
#include "scan/CScanProblem.h"

void CScanWidgetRepeat::init()
{
  lineEditNumber->setValidator(new QIntValidator(lineEditNumber));
}

#include "report/CCopasiObjectName.h"
bool CScanWidgetRepeat::initFromScanItem(CCopasiParameterGroup * pg)
{
  C_INT32 * tmp;

  if (!(tmp = pg->getValue("Type").pINT)) return false;
  if (* (CScanProblem::Type *) tmp != CScanProblem::SCAN_REPEAT)
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
