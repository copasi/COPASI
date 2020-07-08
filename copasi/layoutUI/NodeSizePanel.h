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

#ifndef NODESIZEPANEL_H__
#define NODESIZEPANEL_H__

#include "ui_NodeSizePanel.h"

class NodeSizePanel : public QDialog, public Ui::NodeSizePanel
{
  Q_OBJECT

public:
  NodeSizePanel(QWidget* parent = 0, bool modal = false, Qt::WindowFlags fl = Qt::WindowFlags());

private slots:
  void setMinAndMaxValues();
  void cancel();
  void setMinValue();
  void setMaxValue();
};

#endif // NODESIZEPANEL_H__
