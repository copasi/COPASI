/* Begin CVS Header
   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/CopasiUI/Attic/CScanWidgetRepeat.ui.h,v $
   $Revision: 1.1 $
   $Name:  $
   $Author: ssahle $ 
   $Date: 2005/02/27 20:27:39 $
   End CVS Header */

#include <qvalidator.h>
#include <CCopasiSelectionDialog.h>
#include "qtUtilities.h"

void CScanWidgetRepeat::init()
{
  lineEditNumber->setValidator(new QIntValidator(lineEditNumber));
}

#include "report/CCopasiObjectName.h"
bool CScanWidgetRepeat::initFromScanItem(CCopasiParameterGroup * pg)
{
  void* tmp;

  if (!(tmp = pg->getValue("Type"))) return false;
  CScanProblem::Type type = *(CScanProblem::Type*)tmp;
  if (type != CScanProblem::SCAN_REPEAT)
    return false;

  if (!(tmp = pg->getValue("Number of steps"))) return false;
  lineEditNumber->setText(QString::number(*(C_INT32*)tmp));

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
