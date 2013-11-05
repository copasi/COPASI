// Copyright (C) 2010 - 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef FONTCHOOSER_H__
#define FONTCHOOSER_H__

#include <QtGui/QDialog>

#include "copasi/layoutUI/ui_FontChooser.h"

class QWidget;

class FontChooser : public QDialog, public Ui::FontChooser
{
  Q_OBJECT

public:
  FontChooser(QWidget* parent = 0, bool modal = false, Qt::WindowFlags fl = 0);

private slots:
  void changeFontSize();
  void cancel();
};

#endif // FONTCHOOSER_H__
