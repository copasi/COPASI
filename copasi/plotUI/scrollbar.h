// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 - 2009 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

// Copyright (C) 2006 - 2007 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc. and EML Research, gGmbH.
// All rights reserved.

// Copyright � 1997   Josef Wilgen
// Copyright � 2002   Uwe Rathmann
//
// This file is published under the Qwt License, Version 1.0.
// You should have received a copy of this licence in the file
// QwtLicense.
//
// Modifications made to the original are
#ifndef _SCROLLBAR_H
#define _SCROLLBAR_H 1

#include <QScrollBar>

class ScrollBar: public QScrollBar
{
  Q_OBJECT

public:
  ScrollBar(QWidget *parent = NULL);
  ScrollBar(Qt::Orientation, QWidget *parent = NULL);
  ScrollBar(double minBase, double maxBase, bool logscale,
            Qt::Orientation o, QWidget *parent = NULL);

  void setInverted(bool);
  bool isInverted() const;

  void setLogScale(bool l);
  bool isLogScale() const;

  double minBaseValue() const;
  double maxBaseValue() const;

  double minSliderValue() const;
  double maxSliderValue() const;

  int extent() const;

signals:
  void sliderMoved(Qt::Orientation, double, double);
  void valueChanged(Qt::Orientation, double, double);

public slots:
  virtual void setBase(double min, double max);
  virtual void moveSlider(double min, double max);

protected:
  void sliderRange(int value, double &min, double &max) const;
  int mapToTick(double) const;
  double mapFromTick(int) const;

private slots:
  void catchValueChanged(int value);
  void catchSliderMoved(int value);

private:
  void init();

  bool d_inverted;
  double d_minBase;
  double d_maxBase;
  int d_baseTicks;
  bool mLogScale;
};

#endif
