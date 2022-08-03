// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CPlotInterface.h"
#include <copasi/UI/qtUtilities.h>
#include <copasi/utilities/CUnit.h>

// static
const CEnumAnnotation< std::string, CPlotInterface::Axis > CPlotInterface::AxisNames(
{
  "x axis",
  "y axis",
  "z axis"
});


QString CPlotInterface::getAxisText(Axis axis, const CObjectInterface * pObjectInterface)
{
  auto * pPlotSpec = getPlotSpecification();
  QString text = getParameterValue(pPlotSpec, AxisNames[axis]).toString();

  if (!text.isEmpty())
    return text;

  const CDataObject * pObject = CObjectInterface::DataObject(pObjectInterface);

  if (pObject == NULL)
    return "";

  std::string Units = CUnit::prettyPrint(pObject->getUnits());

  if (Units == "?")
    {
      Units.clear();
    }

  return FROM_UTF8(Units);
}
