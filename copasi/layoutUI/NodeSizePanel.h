// Begin CVS Header
//   $Source: /Volumes/Home/Users/shoops/cvs/copasi_dev/copasi/layoutUI/NodeSizePanel.h,v $
//   $Revision: 1.1 $
//   $Name:  $
//   $Author: gauges $
//   $Date: 2010/02/02 16:45:22 $
// End CVS Header

// Copyright (C) 2008 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., EML Research, gGmbH, University of Heidelberg,
// and The University of Manchester.
// All rights reserved.

#ifndef NODESIZEPANEL_H__
#define NODESIZEPANEL_H__

#include "ui_NodeSizePanel.h"

class NodeSizePanel : public QDialog, public Ui::NodeSizePanel
{
  Q_OBJECT

public:
  NodeSizePanel(QWidget* parent = 0, const char* name = 0, bool modal = false, Qt::WindowFlags fl = 0);

private slots:
  void setMinAndMaxValues();
  void cancel();
  void setMinValue();
  void setMaxValue();
};

#endif // NODESIZEPANEL_H__
