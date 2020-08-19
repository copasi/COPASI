// Copyright (C) 2019 - 2020 by Pedro Mendes, Rector and Visitors of the
// University of Virginia, University of Heidelberg, and University
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2017 - 2018 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and University of
// of Connecticut School of Medicine.
// All rights reserved.

// Copyright (C) 2013 - 2016 by Pedro Mendes, Virginia Tech Intellectual
// Properties, Inc., University of Heidelberg, and The University
// of Manchester.
// All rights reserved.

#ifndef QLAYOUT_VIEW_H
#define QLAYOUT_VIEW_H

#include <QGraphicsView>

class CQLayoutScene;
class QAction;
class QMenu;
class QToolBar;
class QComboBox;
class CDataModel;
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
  void setDataModel(CDataModel* dataModel, CLayout *layout = NULL);
  CDataModel* getDataModel();

public slots:
  void slotFitOnScreen();
  void slotResetZoom();
  void slotZoomIn();
  void slotZoomOut();
  void slotSaveToFile(const QString& fileName);
  void slotLayoutChanged(int);
  void slotRenderInformationChanged(int);

signals:
  void renderInformationChanged();
  void layoutChanged();

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
  CDataModel* mpDataModel;

private:
  void createActions();
};

#endif
