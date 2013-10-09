// Copyright (C) 2013 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QLAYOUT_VIEW_H
#define QLAYOUT_VIEW_H

#include <QtGui/QGraphicsView>

class CQLayoutScene;
class QAction;
class QMenu;
class QToolBar;
class QComboBox;
class CCopasiDataModel;
class CLayout;

class CQLayoutView: public QGraphicsView
{
  Q_OBJECT
public:
  CQLayoutView(QWidget*parent = NULL);
  CQLayoutView(CQLayoutScene *scene);
  virtual ~CQLayoutView();
  void fillZoomMenu(QMenu* menu);
  void fillZoomTooBar(QToolBar* toolBar);
  void fillSelectionToolBar(QToolBar* toolBar);
  void setDataModel(CCopasiDataModel* dataModel, CLayout *layout = NULL);
  CCopasiDataModel* getDataModel();

public slots:
  void slotFitOnScreen();
  void slotResetZoom();
  void slotZoomIn();
  void slotZoomOut();
  void slotSaveToFile(const QString& fileName);
  void slotLayoutChanged(int);
  void slotRenderInformationChanged(int);

protected:
  void wheelEvent(QWheelEvent* event);

  QAction* mpActZoomIn;
  QAction* mpActZoomOut;
  QAction* mpActFitOnScreen;
  QAction* mpActResetZoom;
  double   mScaleFactor;
  QComboBox* mpLayoutDropdown;
  QComboBox* mpRenderDropdown;
  bool mIgnoreEvents;
  CCopasiDataModel* mpDataModel;

private:
  void createActions();
};

#endif
