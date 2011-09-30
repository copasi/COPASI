// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/ParaPanel.h,v $
//   $Revision: 1.10 $
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

#ifndef PARAPANEL_H__
#define PARAPANEL_H__

#include <QWidget>

#include "copasi/layoutUI/ui_ParaPanel.h"

class CQParaPanel : public QWidget, public Ui::CQParaPanel
{
  Q_OBJECT

public:
  CQParaPanel(QWidget* parent = 0);

public slots:
  void enableStepNumberChoice();
  void enableParameterChoice();
  void enableModeChoice();
  void disableParameterChoice();
  void disableStepNumberChoice();
  void disableModeChoice();
  void setStepNumber(int i);

private slots:
  void changeFrameRate();
  void setGlobalScaling();
  void setIndividualScaling();
  void stepEdit_returnPressed();
  void setSizeMode();
  void setColorMode();
};

#endif // PARAPANEL_H__
