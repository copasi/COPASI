// Copyright (C) 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#ifndef CQMARCHING_SQUARES_H
#define CQMARCHING_SQUARES_H

#include <copasi/config.h>

#if defined(COPASI_USE_QCUSTOMPLOT)

#  include <vector>
#  include <algorithm>
#  include <iostream>
#  include <QPointF>
#  include <QPolygonF>
#  include <QList>
#  include <QVariant>

#  include "qcustomplot.h"

/**
 * @brief CQMarchingSquares
 *
 * This class implements the marching squares algorithm, to enable
 * contours on the colormaps. The original code comes from:
 *
 * https://www.qcustomplot.com/index.php/support/forum/1245
 *
 * which includes a c++ reimplementation of:
 *
 * http://udel.edu/~mm/code/marchingSquares/
 *
 * (originally released under the GPL)
 */
class CQMarchingSquares
{
public:
  class levelPaths : public std::vector< QPolygonF >
  {
  public:
    void openPoligon(double x, double y);
    void lineTo(double x, double y);
    void closePoligon();

  private:
    QPolygonF _current;
  };

  CQMarchingSquares(QCPColorMapData * data,
                    double xMin,
                    double xMax,
                    double yMin,
                    double yMax);

  std::vector< levelPaths > mkIsos(QList< QVariant > & levels);

  static constexpr double epsilon = 1e-10;

  ~CQMarchingSquares()
  {
    delete dataP;
  }

private:
  class IsoCell
  {
  public:
    enum side
    {
      LEFT,
      RIGHT,
      TOP,
      BOTTOM,
      NONE
    };
    IsoCell();
    IsoCell(int nInfo, bool isFlipped);
    void setFlipped(bool isFlipped);
    void setNeighborInfo(int nInfo);
    int getNeighborInfo();
    bool isFlipped();
    QPointF normalizedPointCCW(side cellSide);
    side firstSideCCW(side prev);
    side secondSideCCW(side prev);
    side nextCellCCW(side prev);
    void clearIso();
    double getLeft();
    void setLeft(double left);
    double getRight();
    void setRight(double right);
    double getTop();
    void setTop(double top);
    double getBottom();
    void setBottom(double bottom);

  private:
    bool _flipped;
    int _neighborInfo;
    double _left, _right, _top, _bottom;
  };

  /**
     * Coordinates within this distance of each other are considered identical.
     * This affects whether new segments are or are not created in an iso
     * shape GeneralPath, in particular whether or not to generate a call
     * to lineTo().
     */
  double * padData(QCPColorMapData * data);
  IsoCell * mkContour(double & level, int & numRows, int & numCols);
  levelPaths mkIso(IsoCell * isoData, double threshold, int & numRows, int & numCols);
  void interpolateCrossing(IsoCell * isoData, int r, int c, double threshold, int rows, int cols);
  void isoSubpath(IsoCell * isoData, int r, int c, levelPaths & iso, int & numRows, int & numCols);

  int p_rows, p_cols;
  double * dataP;
  double _xMin, _xMax, _yMin, _yMax;
  double _xStep, _yStep;
  int _ySize, _xSize;
};

#endif // #if defined(COPASI_USE_QCUSTOMPLOT)
#endif // CQMARCHING_SQUARES_H
