// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/barChart/qwt3dScale.cpp,v $
//   $Revision: 1.5 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/03/07 19:24:50 $
// End CVS Header

// Copyright (C) 2011 - 2010 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2001 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

#include "qwt3dScale.h"
//#include <iostream>
using namespace Qwt3D;

int LinearAutoScaler2::execute2(double& a, double& b, double start, double stop, int ivals)
{

  return execute(a, b, start, stop, ivals);
}

//! Applies LinearAutoScaler::execute()
int ValueScale::autoscale(double& a, double& b, double start, double stop, int ivals)
{
  return autoscaler_p2.execute2(a, b, start, stop, ivals);
}

//! Creates the major and minor vector for the scale
void ValueScale::calculate()
{
  int i;
  int j;
  majors_p.clear();
  minors_p.clear();

  double interval = mstop_p - mstart_p;

  double runningval;

  // majors

  // first tic
  if (mstart_p < start_p || mstop_p > stop_p)
    return;

  majors_p.push_back(mstart_p);

  // remaining tics
  for (i = 1; i <= majorintervals_p; ++i)
    {
      double t = double(i) / majorintervals_p;
      runningval = mstart_p + t * interval;

      if (runningval > stop_p)
        break;

      if (isPracticallyZero(mstart_p, -t*interval)) // prevent rounding errors near 0
        runningval = 0.0;

      majors_p.push_back(runningval);
    }

  majorintervals_p = (int) majors_p.size();

  if (majorintervals_p)
    --majorintervals_p;

  // minors
  if (!majorintervals_p || !minorintervals_p) // no valid interval
    {
      minorintervals_p = 0;
      return;
    }

  // start_p      mstart_p
  //  |_____________|_____ _ _ _

  double step = (majors_p[1] - majors_p[0]) / minorintervals_p;

  if (isPracticallyZero(step))
    return;

  runningval = mstart_p - step;

  while (runningval > start_p)
    {
      minors_p.push_back(runningval);
      runningval -= step;
    }

  //       mstart_p            mstop_p
  //  ________|_____ _ _ _ _ _ ___|__________

  for (i = 0; i != majorintervals_p; ++i)
    {
      runningval = majors_p[i] + step;

      for (j = 0; j != minorintervals_p; ++j)
        {
          minors_p.push_back(runningval);
          runningval += step;
        }
    }

  //    mstop_p       stop_p
  // _ _ _|_____________|

  runningval = mstop_p + step;

  while (runningval < stop_p)
    {
      minors_p.push_back(runningval);
      runningval += step;
    }
}

QString ValueScale::ticLabel(unsigned int idx) const
{
  if (idx < majors_p.size())
    {
      return QString::number(majors_p[idx]);
    }

  return QString("");
}

RowScale::RowScale(const std::vector<std::string> * vos, int showRow)
    : ValueScale(),
    mpRowsDes(vos),
    showRow(showRow)
{}

QString RowScale::ticLabel(unsigned int idx) const
{
  if (!mpRowsDes) return QString("");

  if ((mpRowsDes->size() - 1) < idx) return QString("");

  if (showRow == (unsigned int) - 1)
    {
      std::string a;
      a = (*mpRowsDes)[idx];
      return (QString(a.c_str()));
    }
  else
    {
      if (showRow == idx)
        {
          std::string a;
          a = (*mpRowsDes)[idx];
          return (QString(a.c_str()));
        }
      else
        {
          return QString("");
        }
    }
}

ColumnScale::ColumnScale(const std::vector<std::string> * vos, int showColumn)
    : ValueScale(),
    mpColumnsDes(vos),
    showColumn(showColumn)
{}

QString ColumnScale::ticLabel(unsigned int idx) const
{
  if (!mpColumnsDes) return QString("");

  if ((mpColumnsDes->size() - 1) < idx) return QString("");

  if (showColumn == (unsigned int) - 1)
    {
      std::string a;
      a = (*mpColumnsDes)[idx];
      return (QString(a.c_str()));
    }
  else
    {
      if (showColumn == idx)
        {
          std::string a;
          a = (*mpColumnsDes)[idx];
          return (QString(a.c_str()));
        }
      else
        {
          return QString("");
        }
    }
}
