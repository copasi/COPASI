// Copyright (C) 2023 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

#include "CQMarchingSquares.h"

#if defined(COPASI_USE_QCUSTOMPLOT)


void CQMarchingSquares::levelPaths::openPoligon(double x, double y)
{
  _current.push_back(QPointF(x, y));
}

void CQMarchingSquares::levelPaths::lineTo(double x, double y)
{
  _current.push_back(QPointF(x, y));
}

void CQMarchingSquares::levelPaths::closePoligon()
{
  if (_current.size() > 0)
    {
      _current.push_back(_current.front());
    }

  push_back(_current);

  _current.clear();
}

CQMarchingSquares::IsoCell::IsoCell()
{
  _flipped = false;
}

CQMarchingSquares::IsoCell::IsoCell(int nInfo, bool isFlipped)
{
  _neighborInfo = nInfo;
  _flipped = isFlipped;
}

void CQMarchingSquares::IsoCell::setFlipped(bool isFlipped)
{
  _flipped = isFlipped;
}
void CQMarchingSquares::IsoCell::setNeighborInfo(int nInfo)
{
  _neighborInfo = nInfo;
}

int CQMarchingSquares::IsoCell::getNeighborInfo()
{
  return _neighborInfo;
}

bool CQMarchingSquares::IsoCell::isFlipped()
{
  return _flipped;
}

/**
     * After Marching Squares determines what kind of crossings go through each
     * cell, this method can be used to save linearly interpolated values that
     * more closely follow data values. So rather than using cell crossing
     * values of, e.g., (0.5, 0), plotting is better if the data indicated, say,
     * (0.83, 0) should be used.
     *
     * @param cellSide which side crossing is wanted.
     * @return crossing based on data and normalized to [0, 1].
     */
QPointF CQMarchingSquares::IsoCell::normalizedPointCCW(side cellSide)
{
  switch (cellSide)
    {
      case BOTTOM:
        return QPointF(_bottom, 0);

      case LEFT:
        return QPointF(0, _left);

      case RIGHT:
        return QPointF(1, _right);

      case TOP:
        return QPointF(_top, 1);
    }
}

/**
     * Depending on this cell's neighbor info, which is an integer in [0, 15],
     * this method determines the first side that would used in a counter-
     * clockwise traversal of an isoline.
     *
     * @param prev previous side, used only for ambiguous cases of 5 and 10.
     * @return side to start with in a CCW traversal.
     */
CQMarchingSquares::IsoCell::side CQMarchingSquares::IsoCell::firstSideCCW(side prev)
{
  switch (_neighborInfo)
    {
      case 1:
      case 3:
      case 7:
        return side::LEFT;

      case 2:
      case 6:
      case 14:
        return side::BOTTOM;

      case 4:
      case 11:
      case 12:
      case 13:
        return side::RIGHT;

      case 8:
      case 9:
        return side::TOP;

      case 5:
        switch (prev)
          {
            case side::LEFT:
              return side::RIGHT;

            case side::RIGHT:
              return side::LEFT;

            default:
              break;
          }

      case 10:
        switch (prev)
          {
            case side::BOTTOM:
              return side::TOP;

            case side::TOP:
              return side::BOTTOM;

            default:
              break;
          }

      default:
        break;
    }

  return side::NONE;
}

/**
     * Depending on this cell's neighbor info, which is an integer in [0, 15],
     * this method determines the second side of a cell that would used in a
     * counter-clockwise traversal of an isoline.
     *
     * @param prev previous side, used only for ambiguous cases of 5 and 10.
     * @return side to finish with in a call during a CCW traversal.
     */
CQMarchingSquares::IsoCell::side CQMarchingSquares::IsoCell::secondSideCCW(side prev)
{

  switch (_neighborInfo)
    {
      case 8:
      case 12:
      case 14:
        return side::LEFT;

      case 1:
      case 9:
      case 13:
        return side::BOTTOM;

      case 2:
      case 3:
      case 11:
        return side::RIGHT;

      case 4:
      case 6:
      case 7:
        return side::TOP;

      case 5:
        switch (prev)
          {
            case side::LEFT: // Normal case 5.
              return _flipped ? side::BOTTOM : side::TOP;

            case side::RIGHT: // Normal case 5.
              return _flipped ? side::TOP : side::BOTTOM;

            default:
              break;
          }

      case 10:
        switch (prev)
          {
            case side::BOTTOM: // Normal case 10
              return _flipped ? side::RIGHT : side::LEFT;

            case side::TOP: // Normal case 10
              return _flipped ? side::LEFT : side::RIGHT;

            default:
              return side::NONE;
          }

      default:
        return side::NONE;
    }
}

/**
     * Find the next cell to use in a CCW traversal of an isoline.
     *
     * @param prev previous side, used only for ambiguous cases of 5 and 10.
     * @return next cell to use in a CCW traversal.
     */

CQMarchingSquares::IsoCell::side CQMarchingSquares::IsoCell::nextCellCCW(side prev)
{
  return secondSideCCW(prev);
}

/**
     * Clear neighbor info in this cell. When building up shapes, it is possible
     * to have disjoint isoshapes and holes in them. An easy way to build up a
     * new shape from neighborInfo is to build sub-paths for one isoline at a
     * time. As the shape is built up, it is necessary to erase the line
     * afterward so that subsequent searches for isolines will not loop
     * infinitely.
     *
     * @param prev
     */
void CQMarchingSquares::IsoCell::clearIso()
{
  switch (_neighborInfo)
    {
      case 0:
      case 5:
      case 10:
      case 15:
        break;

      default:
        _neighborInfo = 15;
    }
}

/**
     * @return Get interpolated crossing on left edge of cell.
     */
double CQMarchingSquares::IsoCell::getLeft()
{
  return _left;
}

/**
     * @param left Set interpolated crossing on left edge of cell.
     */
void CQMarchingSquares::IsoCell::setLeft(double left)
{
  _left = left;
}

/**
     * @return Get interpolated crossing on right edge of cell.
     */
double CQMarchingSquares::IsoCell::getRight()
{
  return _right;
}

/**
     * @param right Set interpolated crossing on right edge of cell.
     */
void CQMarchingSquares::IsoCell::setRight(double right)
{
  _right = right;
}

/**
     * @return Get interpolated crossing on top edge of cell.
     */
double CQMarchingSquares::IsoCell::getTop()
{
  return _top;
}

/**
     * @param top Set interpolated crossing on top edge of cell.
     */
void CQMarchingSquares::IsoCell::setTop(double top)
{
  _top = top;
}

/**
     * @return Get interpolated crossing on bottom edge of cell.
     */
double CQMarchingSquares::IsoCell::getBottom()
{
  return _bottom;
}

CQMarchingSquares::CQMarchingSquares(QCPColorMapData *data, double xMin, double xMax, double yMin, double yMax)
{
  _xMin = xMin;
  _xMax = xMax;
  _yMin = yMin;
  _yMax = yMax;

  _ySize = data->valueSize();
  _xSize = data->keySize();

  _xStep = (_xMax - _xMin) / _xSize;
  _yStep = (_yMax - _yMin) / _ySize;

  dataP = padData(data);
}

/**
     * @param bottom Set interpolated crossing on bottom edge of cell.
     */
void CQMarchingSquares::IsoCell::setBottom(double bottom)
{
  _bottom = bottom;
}
/**
     * Typically, mkIsos() is the only method in this class that programs will
     * call.  The caller supplies a 2d array of doubles representing some
     * set of measured data.  Additionally, a 1d array of values is passed
     * whose contents are thresholds corresponding to desired islines.
     * The method returns a 1d array of GeneralPaths representing those
     * isolines.  The GeneralPaths may contain disjoint polygons as well as
     * holes.
     *
     * <p>Sample call:
     * <pre>
     * CQMarchingSquares *CQMarchingSquares = new CQMarchingSquares();
     * GenersalPath[] isolines = CQMarchingSquares.mkIsos(data_mW, levels);
     * </pre>
     * and the isolines can then be filled or drawn as desired.
     *
     * @param data measured data to use for isoline generation.
     * @param levels thresholds to use as iso levels.
     * @return return an array of iso GeneralPaths. Each array element
     * corresponds to the same threshold in the 'levels' input array.
     */

std::vector< CQMarchingSquares::levelPaths > CQMarchingSquares::mkIsos(QList< QVariant > & levels)
{
  // Pad data to guarantee iso GeneralPaths will be closed shapes.

  double superMin = levels[0].toDouble();

  for (int i = 1; i < levels.size(); i++)
    {
      superMin = qMin(superMin, levels[i].toDouble());
    }

  superMin--;

  for (int i = 0; i < p_cols; i++)
    {
      dataP[i] = superMin;
      dataP[(p_rows - 1) * p_cols + i] = superMin;
    }

  for (int i = 0; i < p_rows; i++)
    {
      dataP[i * p_cols] = superMin;
      dataP[i * p_cols + p_cols - 1] = superMin;
    }

  std::vector< levelPaths > isos;
  IsoCell * contour;

  for (int i = 0; i < levels.size(); i++)
    {
      // Create contour for this level using Marching Squares algorithm.
      int rows, cols;
      double currentLevel = levels[i].toDouble();
      contour = mkContour(currentLevel, rows, cols);
      // Convert contour to GeneralPath.
      isos.push_back(mkIso(contour, currentLevel, rows, cols));

      delete[] contour;
    }

  return isos;
}

/**
     * Create neighbor info for a single threshold. Neighbor info indicates
     * which of the 4 surrounding data values are above or below the threshold.
     *
     * @param data measured data to use for isoline generation.
     * @param level threshold to use as iso levels.
     * @return return an array of iso GeneralPaths. Each array element
     * corresponds to the same threshold in the 'levels' input array.
     */

CQMarchingSquares::IsoCell * CQMarchingSquares::mkContour(double & level, int & numRows, int & numCols)
{

  // Pad data to guarantee iso GeneralPaths will be closed shapes.
  numRows = p_rows - 1;
  numCols = p_cols - 1;

  // Create array indicating iso cell neighbor info.
  //vector <vector<IsoCell>> contours = new IsoCell[numRows - 1][numCols - 1];

  IsoCell * contours = new IsoCell[numRows * numCols];

  for (int r = 0; r < numRows; r++)
    {
      for (int c = 0; c < numCols; c++)
        {
          // Determine if neighbors are above or below threshold.
          int ll = dataP[r * p_cols + c] > level ? 0 : 1;
          int lr = dataP[r * p_cols + c + 1] > level ? 0 : 2;
          int ur = dataP[(r + 1) * p_cols + c + 1] > level ? 0 : 4;
          int ul = dataP[(r + 1) * p_cols + c] > level ? 0 : 8;
          int nInfo = ll | lr | ur | ul;
          bool isFlipped = false;

          // Deal with ambiguous cases.
          if (nInfo == 5 || nInfo == 10)
            {
              // Calculate average of 4 surrounding values.
              double center = (dataP[r * p_cols + c] + dataP[r * p_cols + c + 1]
                               + dataP[(r + 1) * p_cols + c + 1] + dataP[(r + 1) * p_cols + c])
                              / 4;

              if (nInfo == 5 && center < level)
                {
                  isFlipped = true;
                }
              else if (nInfo == 10 && center < level)
                {
                  isFlipped = true;
                }
            }

          // Store neighbor info as one number.

          contours[r * numCols + c].setNeighborInfo(nInfo);
          contours[r * numCols + c].setFlipped(isFlipped);
        }
    }

  return contours;
}

/**
     * Build up a Shape corresponding to the isoline, and erase isoline at same
     * time. Erasing isoline is important because it is expected that this
     * method will be called repeatedly until no more isolines exist for a given
     * threshold.
     *
     * @param isoData info indicating which adjacent neighbors are above or
     * below threshold.
     * @param data measured data.
     * @param threshold this isoline's threshold value.
     * @return GeneralPath, possibly with disjoint areas and holes,
     * representing isolines.  Shape is guaranteed closed and can be filled.
     */
/* private */
CQMarchingSquares::levelPaths CQMarchingSquares::mkIso(IsoCell * isoData, double threshold, int & numRows, int & numCols)
{
  int r, c;

  for (r = 0; r < numRows; r++)
    {
      for (c = 0; c < numCols; c++)
        {
          interpolateCrossing(isoData, r, c, threshold, numRows, numCols);
        }
    }

  levelPaths isoPath;

  for (r = 0; r < numRows; r++)
    {
      for (c = 0; c < numCols; c++)
        {
          if (isoData[r * numCols + c].getNeighborInfo() != 0
              && isoData[r * numCols + c].getNeighborInfo() != 5
              && isoData[r * numCols + c].getNeighborInfo() != 10
              && isoData[r * numCols + c].getNeighborInfo() != 15)
            {
              isoSubpath(isoData, r, c, isoPath, numRows, numCols);
            }
        }
    }

  return isoPath;
}

/**
     * A given iso level can be made up of multiple disconnected regions and
     * each region can have multiple holes. Both regions and holes are captured
     * as individual iso subpaths. An existing GeneralPath is passed to this
     * method so that a new subpath, which is a collection of one moveTo and
     * multiple lineTo calls, can be added to it.
     *
     * @param isoData info indicating which adjacent neighbors are above or
     * below threshold.
     * @param r row in isoData to start new sub-path.
     * @param c column is isoData to start new sub-path.
     * @param iso existing GeneralPath to which sub-path will be added.
     */
// private

void CQMarchingSquares::isoSubpath(IsoCell * input, int r, int c, levelPaths & iso, int & numRows, int & numCols)
{

  // Found an iso line at [r][c], so start there.
  IsoCell::side prevSide = IsoCell::side::NONE;

  IsoCell * start = &input[r * numCols + c];

  QPointF pt = start->normalizedPointCCW(start->firstSideCCW(prevSide));
  double x = c + pt.x();
  double y = r + pt.y();
  iso.openPoligon(x * _xStep + _xMin, y * _yStep + _yMin);
  pt = start->normalizedPointCCW(start->secondSideCCW(prevSide));
  double xPrev = c + pt.x();
  double yPrev = r + pt.y();

  if (abs(x - xPrev) > epsilon && abs(y - yPrev) > epsilon)
    {
      iso.lineTo(x * _xStep + _xMin, y * _yStep + _yMin);
    }

  prevSide = start->nextCellCCW(prevSide);

  switch (prevSide)
    {
      case IsoCell::side::BOTTOM:
        r -= 1;
        break;

      case IsoCell::side::LEFT:
        c -= 1;
        break;

      case IsoCell::side::RIGHT:
        c += 1;
        break;

      case IsoCell::side::TOP:
        r += 1;
    }

  start->clearIso(); // Erase this isoline.

  IsoCell * curCell = &input[r * numCols + c];

  while (curCell != start)
    {
      pt = curCell->normalizedPointCCW(curCell->secondSideCCW(prevSide));
      x = c + pt.x();
      y = r + pt.y();

      if (abs(x - xPrev) > epsilon && abs(y - yPrev) > epsilon)
        {
          iso.lineTo(x * _xStep + _xMin, y * _yStep + _yMin);
        }

      xPrev = x;
      yPrev = y;
      prevSide = curCell->nextCellCCW(prevSide);

      switch (prevSide)
        {
          case IsoCell::BOTTOM:
            r -= 1;
            break;

          case IsoCell::LEFT:
            c -= 1;
            break;

          case IsoCell::RIGHT:
            c += 1;
            break;

          case IsoCell::TOP:
            r += 1;
            break;
        }

      curCell->clearIso(); // Erase this isoline.
      curCell = &input[r * numCols + c];
    }

  iso.closePoligon();
}

/**
     * Surround data with values less than any in the data to guarantee Marching
     * Squares will find complete polygons and not march off the edge of the
     * data area.
     *
     * @param data 2d data array to be padded
     * @return array which is a copy of input padded with top/bottom rows and
     * left/right columns of values 1 less than smallest value in array.
     */
// private

double * CQMarchingSquares::padData(QCPColorMapData * data)
{

  int rows = data->valueSize();
  int cols = data->keySize();

  p_cols = cols + 2;
  p_rows = rows + 2;

  double * padded = new double[p_cols * p_rows];

  for (int i = 0; i < rows; i++)
    {
      for (int j = 0; j < cols; j++)
        {
          padded[(i + 1) * p_cols + j + 1] = data->cell(j, i);
        }
    }

  return padded;
}

/**
     * Once Marching Squares has determined the kinds of lines crossing a cell,
     * this method uses linear interpolation to make the crossings more
     * representative of the data.
     *
     * @param isoData array of values of 0-15 indicating contour type.
     * @param data original data needed for linear interpolation.
     * @param r current row index.
     * @param c current column index.
     * @param threshold threshold for this iso level.
     */
// private

void CQMarchingSquares::interpolateCrossing(IsoCell * isoData, int r, int c, double threshold, int rows, int cols)
{

  double a, b;

  IsoCell * cell = &isoData[r * cols + c];
  double ll = dataP[r * p_cols + c];
  double lr = dataP[r * p_cols + c + 1];
  double ul = dataP[(r + 1) * p_cols + c];
  double ur = dataP[(r + 1) * p_cols + c + 1];

  // Left side of iso cell.
  switch (cell->getNeighborInfo())
    {
      case 1:
      case 3:
      case 5:
      case 7:
      case 8:
      case 10:
      case 12:
      case 14:
        a = ll;
        b = ul;
        cell->setLeft((threshold - a) / (b - a)); // frac from LL
        break;

      default:
        break;
    }

  // Bottom side of iso cell.
  switch (cell->getNeighborInfo())
    {
      case 1:
      case 2:
      case 5:
      case 6:
      case 9:
      case 10:
      case 13:
      case 14:
        a = ll;
        b = lr;
        cell->setBottom((threshold - a) / (b - a)); // frac from LL
        break;

      default:
        break;
    }

  // Top side of iso cell.
  switch (cell->getNeighborInfo())
    {
      case 4:
      case 5:
      case 6:
      case 7:
      case 8:
      case 9:
      case 10:
      case 11:
        a = ul;
        b = ur;
        cell->setTop((threshold - a) / (b - a)); // frac from UL
        break;

      default:
        break;
    }

  // Right side of iso cell.
  switch (cell->getNeighborInfo())
    {
      case 2:
      case 3:
      case 4:
      case 5:
      case 10:
      case 11:
      case 12:
      case 13:
        a = lr;
        b = ur;
        cell->setRight((threshold - a) / (b - a)); // frac from LR
        break;

      default:
        break;
    }
}

#endif // COPASI_USE_QCUSTOMPLOT
