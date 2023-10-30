// Copyright (C) 2022 - 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef COPASIPLOT_INTERFACE_H
#define COPASIPLOT_INTERFACE_H

#include <QString>
#include <QPainter>
#include <QRect>

#include <string>
#include "copasi/output/COutputHandler.h"
#include "copasi/plot/CPlotSpecification.h"

class CPlotInterface : public COutputInterface
{

public:

  enum struct Axis
  {
    xAxis = 0,
    yAxis,
    zAxis,
    __SIZE
  };

  static const CEnumAnnotation< std::string, Axis > AxisNames;

  /**
  * Destructor
  */
  virtual ~CPlotInterface();

  /**
     * Initialize the the plot from the specification
     * @param const CPlotSpecification* plotspec
     */
  virtual bool initFromSpec(const CPlotSpecification* plotspec) = 0;

  /**
   * @return the current plot specification
   */
  virtual const CPlotSpecification* getPlotSpecification() const  = 0;

  /**
   * Save tab delimited data to file
   * @param const std::string & filename
   * @return bool success
   */
  virtual bool saveData(const std::string & filename) = 0;

  /**
   * Shows or hide all curves depending on whether visibility is false or true
   * @param const bool & visibility
   */
  virtual void setCurvesVisibility(const bool & visibility) = 0;

  virtual void toggleLogX(bool logX) = 0;
  virtual void toggleLogY(bool logY) = 0;
  virtual void resetZoom() = 0;

  virtual void replot() = 0;

  virtual QString titleText() const = 0;

  virtual void render(QPainter * painter, QRect rect) = 0;

  virtual void saveToFile(const QString & fileName, QRect & rect);

  /**
   * @return a string with supported file filters to save files
   */
  virtual QString getSaveFilters();

  /**
   *
   * @param axis the axis to return the text for
   * @param pObjectInterface the object to return text for
   * @param returnUnit (optional bool, default true) returns the unit of the object rather than its name
   * @return the unit of the specified object
  */
  QString getAxisText(Axis axis, const CObjectInterface * pObjectInterface, bool returnUnit = true);
};

#endif // COPASIPLOT_INTERFACE_H
