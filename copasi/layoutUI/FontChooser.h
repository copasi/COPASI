// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2010 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef FONTCHOOSER_H__
#define FONTCHOOSER_H__

#include <QDialog>

#include "copasi/layoutUI/ui_FontChooser.h"

class QWidget;

class FontChooser : public QDialog, public Ui::FontChooser
{
  Q_OBJECT

public:
  FontChooser(QWidget* parent = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());

private slots:
  void changeFontSize();
  void cancel();
};

#endif // FONTCHOOSER_H__
