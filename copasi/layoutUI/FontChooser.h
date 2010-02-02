// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/FontChooser.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/02/02 16:45:22 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef FONTCHOOSER_H__
#define FONTCHOOSER_H__

#include <QDialog>

#include <copasi/layoutUI/ui_FontChooser.h>

class QWidget;

class FontChooser : public QDialog, public Ui::FontChooser
{
  Q_OBJECT

public:
  FontChooser(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);

private slots:
  void changeFontSize();
  void cancel();
};

#endif // FONTCHOOSER_H__
