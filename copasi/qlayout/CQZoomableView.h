// Copyright (C) 2017 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QZOOMABLE_VIEW_H
#define QZOOMABLE_VIEW_H

#include <QGraphicsView>

class QAction;
class QMenu;
class QToolBar;
class QComboBox;
class CDataModel;

class CQZoomableView: public QGraphicsView
{
  Q_OBJECT
public:
  CQZoomableView(QWidget*parent = NULL);
  CQZoomableView(QGraphicsView *scene);
  virtual ~CQZoomableView();
  void fillZoomMenu(QMenu* menu);
  void fillZoomTooBar(QToolBar* toolBar);
  void fillSelectionToolBar(QToolBar* toolBar);

public slots:
  void slotFitOnScreen();
  void slotResetZoom();
  void slotZoomIn();
  void slotZoomOut();

protected:
  void wheelEvent(QWheelEvent* event);
  void createActions();

  QAction* mpActZoomIn;
  QAction* mpActZoomOut;
  QAction* mpActFitOnScreen;
  QAction* mpActResetZoom;
  double   mScaleFactor;
  bool mIgnoreEvents;
};

#endif
