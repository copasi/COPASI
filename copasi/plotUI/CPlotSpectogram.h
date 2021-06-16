// Copyright (C) 2019 - 2021 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2015 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef CPLOTSPECTOGRAM_H
#define CPLOTSPECTOGRAM_H

#include <string>
#include <vector>
#include <fstream>
#include <iostream>

#include <QPainter>
#include <QtCore/QMutex>
#include <QtCore/QWaitCondition>

#include <QRectF>

#include <qwt_plot.h>
#include <qwt_painter.h>

#if QWT_VERSION > QT_VERSION_CHECK(6,0,0)
#include <qwt_compat.h>
#else
#include <qwt_data.h>
#include <qwt_raster_data.h>
#endif

#include <qwt_plot_curve.h>
#include <qwt_plot_spectrogram.h>

#include "copasi/plot/CPlotItem.h"

#include "copasi/core/CDataObject.h"
#include "copasi/output/COutputHandler.h"
#include "copasi/utilities/CopasiTime.h"
#include "copasi/core/CVector.h"
#include "copasi/core/CMatrix.h"

class CPlotSpectogram : public QwtPlotSpectrogram
{
public:
  CPlotSpectogram(QMutex * pMutex,
                  const CPlotItem::Type & type,
                  const COutputInterface::Activity & activity,
                  const QString & title,
                  bool logZ = false,
                  double limitZ = std::numeric_limits<double>::quiet_NaN(),
                  bool bilinear = true);

  void setDataSize(const size_t & size);

  void reallocatedData(const CVector< double > * pX,
                       const CVector< double > * pY,
                       const CVector< double > * pZ);

  const CPlotItem::Type & getType() const;

  const COutputInterface::Activity & getActivity() const;

  bool getLogZ() const;
  void setLogZ(bool logZ);

  double getLimitZ() const;
  void setLimitZ(double limitZ);

  bool getBilinear() const;
  void setBilinear(bool bilinear);

protected:

private:
  QMutex * mpMutex;

  CPlotItem::Type mType;

  COutputInterface::Activity mActivity;

  bool mLogZ;
  double mLimitZ;
  bool mBilinear;
};

#endif
