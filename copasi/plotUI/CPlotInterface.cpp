// Copyright (C) 2022 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CPlotInterface.h"
#include <copasi/UI/qtUtilities.h>
#include <copasi/utilities/CUnit.h>

#include <QPrinter>
#include <QPixmap>
#include <QPicture>

#include <QtSvg/QtSvg>
#include <QtSvg/QSvgGenerator>


// static
const CEnumAnnotation< std::string, CPlotInterface::Axis > CPlotInterface::AxisNames(
{
  "x axis",
  "y axis",
  "z axis"
});


void CPlotInterface::saveToFile(const QString & fileName, QRect & rect)
{
  if (fileName.endsWith(".png"))
    {
      QPixmap pixmap(rect.width(), rect.height());
      pixmap.fill();
      QPainter painter(&pixmap);
      painter.begin(&pixmap);
      render(&painter, rect);
      painter.end();
      pixmap.save(fileName, "PNG");
    }
  else if (fileName.endsWith(".svg"))
    {
      QSvgGenerator generator;
      generator.setFileName(fileName);
      QPainter painter(&generator);
      painter.begin(&generator);
      render(&painter, rect);
      painter.end();
    }
  else if (fileName.endsWith(".pdf"))
    {
      QPrinter printer;
      printer.setOutputFileName(fileName);
      printer.setOutputFormat(QPrinter::PdfFormat);
      QPainter painter(&printer);
      painter.begin(&printer);
      render(&painter, rect);
      painter.end();
    }
}

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
