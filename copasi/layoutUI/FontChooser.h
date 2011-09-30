// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/FontChooser.h,v $
//   $Revision: 1.3 $
//   $Name:  $
//   $Author: shoops $
//   $Date: 2011/09/30 16:35:56 $
// End CVS Header

// Copyright (C) 2011 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
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
  FontChooser(QWidget* parent = 0, bool modal = false, Qt::WindowFlags fl = 0);

private slots:
  void changeFontSize();
  void cancel();
};

#endif // FONTCHOOSER_H__
